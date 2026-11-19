#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core__Goobert.hpp"
#include "../hdrs/Gd__gd_core__ClawsofAttack.hpp"
#include "../hdrs/Gd__gd_core__CoreItem__INNER__CoreSignalConnection.hpp"
#include "../hdrs/Gd__gd_core__CoreItem.hpp"
#include "../hdrs/Gd__gd_core__DancingDragon.hpp"
#include "../hdrs/Gd__gd_core__FannyPack.hpp"
#include "../hdrs/Gd__gd_core__HolyArmor.hpp"
#include "../hdrs/Gd__gd_core__ManaOrb.hpp"
#include "../hdrs/Gd__gd_core__PoisonGoobert.hpp"
#include "../hdrs/Gd__gd_core__SpectralDagger.hpp"
#include "../hdrs/Gd__gd_core_items__StoneSkinPotion.hpp"
#include "../hdrs/Gd__gd_core__WoodenSword.hpp"
#include "../hdrs/Gd__gd_core_items__Dagger.hpp"
#include "../hdrs/Gd__gd_core_items__Crown.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__AmethystWhelp.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ArmoredCouragePuppy.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Bewitchment.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BrassKnuckles.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Cheese.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ChessMaster.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Daggerang.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DragonscaleArmor.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Everburning.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__FriendlyFire.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Hardwood.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__InnerPower.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__LightningStaff.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Markswoman.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__OilLamp.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Pop.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__RainbowGoobertEngineer.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SapphireEgg.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SliceofBread.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SpellScrollIce.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__StoneBadge.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ThunderDrake.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Wand.hpp"
#include "../hdrs/Gd__gd_core_items__FlyAgaric.hpp"
#include "../hdrs/Gd__gd_core_items__HeroicPotion.hpp"
#include "../hdrs/Gd__gd_core_items__ManaOrb.hpp"
#include "../hdrs/Gd__gd_core_items__ProtectivePurse.hpp"
#include "../hdrs/Gd__gd_core_items__StrongDemonicFlask.hpp"
#include "../hdrs/Gd__gd_core_items__WoodenSword.hpp"

void Gd__gd_core__Goobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_activations = gd::GdVal::from_int(0);
    this->f_goobertAnimation = gd::GdVal::null();
    this->f_activationsToTrigger = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__Goobert::meta() const { return &META_Gd__gd_core__Goobert; }
gd::GdVal Gd__gd_core__Goobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Goobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Goobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activations_931: out = this->f_activations; return true;
        case SYM_GEN_goobertAnimation_932: out = this->f_goobertAnimation; return true;
        case SYM_GEN_activationsToTrigger_933: out = this->f_activationsToTrigger; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Goobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activations_931: this->f_activations = gd::gd_coerce_int(val); return true;
        case SYM_GEN_goobertAnimation_932: this->f_goobertAnimation = val; return true;
        case SYM_GEN_activationsToTrigger_933: this->f_activationsToTrigger = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Goobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_logCooldown_755: return true;
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_prepare_120: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onItemActivated_934: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Goobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_logCooldown_755: out = fn_logCooldown(args, argc); return true;
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_prepare_120: out = fn_prepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onItemActivated_934: out = fn_onItemActivated(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Goobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Goobert::fn_logCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Goobert::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canActivate_89, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Goobert::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_activations = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_iterationCooldown = gd::gd_coerce_float(this->f_activationsToTrigger);
    this->f_triggerTime = gd::gd_coerce_float(this->f_iterationCooldown);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1365), SYM_GEN_Cooldown_2545)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1377), SYM_GEN_snapshotItemTooltipStat_1351, _ca, 2); })();
    {
        gd::GdVal _t1822 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1823 = (_t1822.kind == gd::GdVal::Kind::Arr) ? _t1822.arr : nullptr;
        uint32_t _len__t1824 = _t1823 ? _t1823->len : 0u;
        for (uint32_t _t1824 = 0; _t1824 < _len__t1824; ++_t1824) {
            gd::GdVal lv_item = _t1823->data[_t1824];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onItemActivated", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        }
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_prepare_120, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Goobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Goobert::fn_onItemActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__gsrc = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "?", 1u));
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_event, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_event, SYM_GEN_origin_1453), gd::GdVal::null())))) : gd::GdVal::from_bool(false)))) {
        lv__gsrc = gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv_event, SYM_GEN_origin_1453), SYM_GEN_name_7)));
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "GACT", 4u)), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1575))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "/ot", 3u))), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(this->f_ownerType)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_activations, gd::GdVal::from_int(1LL))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "/", 1u))), ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "src=", 4u)), lv__gsrc)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), SYM_GEN_trace_diag_1643, _ca, 4); })();
    this->f_activations = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_activations, gd::GdVal::from_int(1LL)));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_activations, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0))))) {
        this->f_activations = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCooldownEffect_142, nullptr, 0);
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_doubleActivationChance, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_doubleActivationChance}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_flip_1637, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCooldownEffect_142, nullptr, 0);
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, this->f_activations, this->f_activationsToTrigger), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_789, _ca, 2); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, this->f_activations, this->f_activationsToTrigger), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_789, _ca, 2); })();
    }
    this->f_triggerTime = gd::gd_coerce_float(gd::gd_sub(this->f_activationsToTrigger, this->f_activations));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1365), SYM_GEN_Cooldown_2545), gd::GdVal::null(), gd::GdVal::from_bool(false), lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1377), SYM_GEN_snapshotItemTooltipStat_1351, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Goobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_activationsToTrigger = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Goobert(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Goobert>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Goobert = {CLS_Gd__gd_core__Goobert, "Goobert", "res://gd_core/Goobert.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__Goobert, &Gd__gd_core__Goobert::get_static_prop_fn, &Gd__gd_core__Goobert::call_static_fn};

void Gd__gd_core__ClawsofAttack::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
    this->f_attackCounter = gd::GdVal::from_int(0LL);
    this->f_lastSpeedBonus = gd::GdVal::from_float(0.0);
    this->f_speedPerSpike = gd::GdVal::null();
    this->f_numHits = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__ClawsofAttack::meta() const { return &META_Gd__gd_core__ClawsofAttack; }
gd::GdVal Gd__gd_core__ClawsofAttack::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__ClawsofAttack::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__ClawsofAttack::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_attackCounter_997: out = this->f_attackCounter; return true;
        case SYM_GEN_lastSpeedBonus_998: out = this->f_lastSpeedBonus; return true;
        case SYM_GEN_speedPerSpike_999: out = this->f_speedPerSpike; return true;
        case SYM_GEN_numHits_1000: out = this->f_numHits; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__ClawsofAttack::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_attackCounter_997: this->f_attackCounter = val; return true;
        case SYM_GEN_lastSpeedBonus_998: this->f_lastSpeedBonus = val; return true;
        case SYM_GEN_speedPerSpike_999: this->f_speedPerSpike = val; return true;
        case SYM_GEN_numHits_1000: this->f_numHits = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__ClawsofAttack::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onSpikesChanged_940: return true;
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__ClawsofAttack::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onSpikesChanged_940: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__ClawsofAttack::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__ClawsofAttack::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_spikes_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onSpikesChanged", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ClawsofAttack::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_clawsBonus = gd::gd_min(gd::gd_mul(this->f_speedPerSpike, gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getSpikes_1203, nullptr, 0)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0));
    lv_clawsBonus = gd::gd_div(gd_ctx, lv_clawsBonus, gd::GdVal::from_float(100.0));
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(lv_clawsBonus, this->f_lastSpeedBonus)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    this->f_lastSpeedBonus = lv_clawsBonus;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ClawsofAttack::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        this->f_attackCounter = gd::gd_add(gd_ctx, this->f_attackCounter, gd::GdVal::from_int(1LL));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_attackCounter, this->f_numHits)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 1); })();
            this->f_attackCounter = gd::GdVal::from_int(0LL);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ClawsofAttack::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_lastSpeedBonus = gd::GdVal::from_float(0.0);
    this->f_attackCounter = gd::GdVal::from_int(0LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ClawsofAttack::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_speedPerSpike = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0);
    this->f_numHits = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__ClawsofAttack(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__ClawsofAttack>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__ClawsofAttack = {CLS_Gd__gd_core__ClawsofAttack, "ClawsofAttack", "res://gd_core/ClawsofAttack.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__ClawsofAttack, &Gd__gd_core__ClawsofAttack::get_static_prop_fn, &Gd__gd_core__ClawsofAttack::call_static_fn};

void Gd__gd_core__CoreItem__INNER__CoreSignalConnection::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_emitter = gd::GdVal::null();
    this->f_signalName = gd::GdVal::null();
    this->f_receiver = gd::GdVal::null();
    this->f_methodName = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__CoreItem__INNER__CoreSignalConnection::meta() const { return &META_Gd__gd_core__CoreItem__INNER__CoreSignalConnection; }
gd::GdVal Gd__gd_core__CoreItem__INNER__CoreSignalConnection::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreItem__INNER__CoreSignalConnection::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreItem__INNER__CoreSignalConnection::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_emitter_1556: out = this->f_emitter; return true;
        case SYM_GEN_signalName_1009: out = this->f_signalName; return true;
        case SYM_GEN_receiver_1557: out = this->f_receiver; return true;
        case SYM_GEN_methodName_1558: out = this->f_methodName; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItem__INNER__CoreSignalConnection::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_emitter_1556: this->f_emitter = val; return true;
        case SYM_GEN_signalName_1009: this->f_signalName = val; return true;
        case SYM_GEN_receiver_1557: this->f_receiver = val; return true;
        case SYM_GEN_methodName_1558: this->f_methodName = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItem__INNER__CoreSignalConnection::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_destroy_1559: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItem__INNER__CoreSignalConnection::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_destroy_1559: out = fn_destroy(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItem__INNER__CoreSignalConnection::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core__CoreItem__INNER__CoreSignalConnection::fn__init(const gd::GdVal* _args, int _argc) {
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
    (void)([&]() { gd::GdVal _ca[] = {this->f_emitter, this->f_signalName, this->f_receiver, this->f_methodName}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_receiver, SYM_GEN_ctx_3), SYM_GEN_bus_1375), SYM_GEN_connectEvent_1502, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem__INNER__CoreSignalConnection::fn_destroy(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreItem__INNER__CoreSignalConnection(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreItem__INNER__CoreSignalConnection>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__CoreItem__INNER__CoreSignalConnection = {CLS_Gd__gd_core__CoreItem__INNER__CoreSignalConnection, "CoreSignalConnection", "", nullptr, false, _alloc_Gd__gd_core__CoreItem__INNER__CoreSignalConnection, &Gd__gd_core__CoreItem__INNER__CoreSignalConnection::get_static_prop_fn, &Gd__gd_core__CoreItem__INNER__CoreSignalConnection::call_static_fn};

void Gd__gd_core__DancingDragon::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__DancingDragon::meta() const { return &META_Gd__gd_core__DancingDragon; }
gd::GdVal Gd__gd_core__DancingDragon::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__DancingDragon::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__DancingDragon::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__DancingDragon::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__DancingDragon::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_onHeatChanged_909: return true;
        case SYM_GEN_onLuckyChanged_897: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__DancingDragon::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onHeatChanged_909: out = fn_onHeatChanged(args, argc); return true;
        case SYM_GEN_onLuckyChanged_897: out = fn_onLuckyChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__DancingDragon::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__DancingDragon::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Magic_2721)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DancingDragon::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_heat_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onHeatChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_lucky_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onLuckyChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DancingDragon::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numAffected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numAffected, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0), lv_numAffected)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0), lv_numAffected)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DancingDragon::fn_onHeatChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0), lv_amount)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_160, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DancingDragon::fn_onLuckyChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0), lv_amount)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeDebuffResistChances_1200, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DancingDragon::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__DancingDragon(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__DancingDragon>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__DancingDragon = {CLS_Gd__gd_core__DancingDragon, "DancingDragon", "res://gd_core/DancingDragon.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__DancingDragon, &Gd__gd_core__DancingDragon::get_static_prop_fn, &Gd__gd_core__DancingDragon::call_static_fn};

void Gd__gd_core__FannyPack::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Bag::init_fields(gd_ctx);
    this->f_speedBonus = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__FannyPack::meta() const { return &META_Gd__gd_core__FannyPack; }
gd::GdVal Gd__gd_core__FannyPack::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__FannyPack::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__FannyPack::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_speedBonus_1781: out = this->f_speedBonus; return true;
        default: break;
    }
    return Gd__gd_core__Bag::get_prop(prop, out);
}
bool Gd__gd_core__FannyPack::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_speedBonus_1781: this->f_speedBonus = val; return true;
        default: break;
    }
    return Gd__gd_core__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__FannyPack::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_canApplyEffect_916: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Bag::has_own_method(m);
}
bool Gd__gd_core__FannyPack::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_canApplyEffect_916: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__FannyPack::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__FannyPack::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = gd::GdVal::from_bool(false);
    gd::GdVal lv_totalSpeed = this->f_speedBonus;
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Bagtacular", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isTypeInInventory_801, _ca, 1); })())) {
        lv_totalSpeed = gd::gd_add(gd_ctx, lv_totalSpeed, gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Bagtacular", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })(), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0)));
    }
    {
        gd::GdVal _t1825 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_920, nullptr, 0));
        gd::GdArr* _t1826 = (_t1825.kind == gd::GdVal::Kind::Arr) ? _t1825.arr : nullptr;
        uint32_t _len__t1827 = _t1826 ? _t1826->len : 0u;
        for (uint32_t _t1827 = 0; _t1827 < _len__t1827; ++_t1827) {
            gd::GdVal lv_item = _t1826->data[_t1827];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_916, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_totalSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
                lv_active = gd::GdVal::from_bool(true);
            }
        }
    }
    if (gd::gd_truth(lv_active)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__FannyPack::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::call_method(gd_ctx, lv_toItem, SYM_GEN_hasCooldown_93, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_toItem, SYM_GEN_isBag_81, nullptr, 0))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__FannyPack::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bag::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_speedBonus = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0), gd::GdVal::from_int(100LL));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__FannyPack(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__FannyPack>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__FannyPack = {CLS_Gd__gd_core__FannyPack, "FannyPack", "res://gd_core/FannyPack.gd", &META_Gd__gd_core__Bag, false, _alloc_Gd__gd_core__FannyPack, &Gd__gd_core__FannyPack::get_static_prop_fn, &Gd__gd_core__FannyPack::call_static_fn};

void Gd__gd_core__HolyArmor::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__HolyArmor::meta() const { return &META_Gd__gd_core__HolyArmor; }
gd::GdVal Gd__gd_core__HolyArmor::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__HolyArmor::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__HolyArmor::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__HolyArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__HolyArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__HolyArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__HolyArmor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__HolyArmor::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolyArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, nullptr, 0);
    gd::GdVal lv_numAffected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numAffected, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_numAffected, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolyArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleansePoison_340, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolyArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__HolyArmor(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__HolyArmor>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__HolyArmor = {CLS_Gd__gd_core__HolyArmor, "HolyArmor", "res://gd_core/HolyArmor.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__HolyArmor, &Gd__gd_core__HolyArmor::get_static_prop_fn, &Gd__gd_core__HolyArmor::call_static_fn};

void Gd__gd_core__ManaOrb::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_stackTypes = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_activated = gd::GdVal::from_bool(false);
    this->f_bonusBuffs = gd::GdVal::from_int(0);
    this->f_mana = gd::GdVal::null();
    this->f_manaNeeded = gd::GdVal::from_int(0);
    this->f_buffs = gd::GdVal::null();
    this->f_light = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__ManaOrb::meta() const { return &META_Gd__gd_core__ManaOrb; }
gd::GdVal Gd__gd_core__ManaOrb::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__ManaOrb::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__ManaOrb::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_stackTypes_1830: out = this->f_stackTypes; return true;
        case SYM_GEN_activated_1292: out = this->f_activated; return true;
        case SYM_GEN_bonusBuffs_1831: out = this->f_bonusBuffs; return true;
        case SYM_GEN_mana_1832: out = this->f_mana; return true;
        case SYM_GEN_manaNeeded_1785: out = this->f_manaNeeded; return true;
        case SYM_GEN_buffs_1044: out = this->f_buffs; return true;
        case SYM_GEN_light_945: out = this->f_light; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__ManaOrb::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stackTypes_1830: this->f_stackTypes = val; return true;
        case SYM_GEN_activated_1292: this->f_activated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_bonusBuffs_1831: this->f_bonusBuffs = gd::gd_coerce_int(val); return true;
        case SYM_GEN_mana_1832: this->f_mana = val; return true;
        case SYM_GEN_manaNeeded_1785: this->f_manaNeeded = gd::gd_coerce_int(val); return true;
        case SYM_GEN_buffs_1044: this->f_buffs = val; return true;
        case SYM_GEN_light_945: this->f_light = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__ManaOrb::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onItemActivated_934: return true;
        case SYM_GEN_onManaChanged_1833: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_addBonusRandomBuffs_1834: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__ManaOrb::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemActivated_934: out = fn_onItemActivated(args, argc); return true;
        case SYM_GEN_onManaChanged_1833: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_addBonusRandomBuffs_1834: out = fn_addBonusRandomBuffs(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__ManaOrb::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__ManaOrb::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canActivate_89, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaOrb::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_bonusBuffs = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    {
        gd::GdVal _t1828 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1829 = (_t1828.kind == gd::GdVal::Kind::Arr) ? _t1828.arr : nullptr;
        uint32_t _len__t1830 = _t1829 ? _t1829->len : 0u;
        for (uint32_t _t1830 = 0; _t1830 < _len__t1830; ++_t1830) {
            gd::GdVal lv_item = _t1829->data[_t1830];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onItemActivated", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_mana_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onManaChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaOrb::fn_onItemActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaOrb::fn_onManaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getMana_1224, nullptr, 0), this->f_manaNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_330, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_buffs, this->f_bonusBuffs), lv_event, this->f_stackTypes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_367, _ca, 3); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaOrb::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaOrb::fn_addBonusRandomBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    this->f_bonusBuffs = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_bonusBuffs, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaOrb::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__activated = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__activated = gd::gd_coerce_bool(lv__activated);
    this->f_activated = gd::gd_coerce_bool(lv__activated);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaOrb::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_mana = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0));
    this->f_manaNeeded = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0));
    this->f_buffs = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0));
    this->f_stackTypes = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1357, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Mana_2570)}; return gd::call_method(gd_ctx, this->f_stackTypes, gd::SYM_erase, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__ManaOrb(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__ManaOrb>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__ManaOrb = {CLS_Gd__gd_core__ManaOrb, "ManaOrb", "res://gd_core/ManaOrb.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__ManaOrb, &Gd__gd_core__ManaOrb::get_static_prop_fn, &Gd__gd_core__ManaOrb::call_static_fn};

void Gd__gd_core__PoisonGoobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Goobert::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__PoisonGoobert::meta() const { return &META_Gd__gd_core__PoisonGoobert; }
gd::GdVal Gd__gd_core__PoisonGoobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__PoisonGoobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__PoisonGoobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Goobert::get_prop(prop, out);
}
bool Gd__gd_core__PoisonGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__PoisonGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Goobert::has_own_method(m);
}
bool Gd__gd_core__PoisonGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__PoisonGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__PoisonGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_209, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PoisonGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__PoisonGoobert(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__PoisonGoobert>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__PoisonGoobert = {CLS_Gd__gd_core__PoisonGoobert, "PoisonGoobert", "res://gd_core/PoisonGoobert.gd", &META_Gd__gd_core__Goobert, false, _alloc_Gd__gd_core__PoisonGoobert, &Gd__gd_core__PoisonGoobert::get_static_prop_fn, &Gd__gd_core__PoisonGoobert::call_static_fn};

void Gd__gd_core__SpectralDagger::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Dagger::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__SpectralDagger::meta() const { return &META_Gd__gd_core__SpectralDagger; }
gd::GdVal Gd__gd_core__SpectralDagger::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Dagger::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__SpectralDagger::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__SpectralDagger::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Dagger::get_prop(prop, out);
}
bool Gd__gd_core__SpectralDagger::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Dagger::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__SpectralDagger::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Dagger::has_own_method(m);
}
bool Gd__gd_core__SpectralDagger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Dagger::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__SpectralDagger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Dagger::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__SpectralDagger::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_331, _ca, 1); })();
        if (gd::gd_truth(lv_event)) {
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1425, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1425), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0)));
            (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_makeSpectral_1471, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__SpectralDagger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Dagger::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__SpectralDagger(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__SpectralDagger>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__SpectralDagger = {CLS_Gd__gd_core__SpectralDagger, "SpectralDagger", "res://gd_core/SpectralDagger.gd", &META_Gd__gd_core__Dagger, false, _alloc_Gd__gd_core__SpectralDagger, &Gd__gd_core__SpectralDagger::get_static_prop_fn, &Gd__gd_core__SpectralDagger::call_static_fn};

void Gd__gd_core_items__StoneSkinPotion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Potion::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__StoneSkinPotion::meta() const { return &META_Gd__gd_core_items__StoneSkinPotion; }
gd::GdVal Gd__gd_core_items__StoneSkinPotion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Potion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__StoneSkinPotion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__StoneSkinPotion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Potion::get_prop(prop, out);
}
bool Gd__gd_core_items__StoneSkinPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__StoneSkinPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1753: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onBlockChanged_1890: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::has_own_method(m);
}
bool Gd__gd_core_items__StoneSkinPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1753: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBlockChanged_1890: out = fn_onBlockChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__StoneSkinPotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Potion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__StoneSkinPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_202, nullptr, 0), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_healthToBlock_326, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StoneSkinPotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_block_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBlockChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StoneSkinPotion::fn_onBlockChanged(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__StoneSkinPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Potion::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__StoneSkinPotion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__StoneSkinPotion>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__StoneSkinPotion = {CLS_Gd__gd_core_items__StoneSkinPotion, "StoneSkinPotion", "res://gd_core_items/StoneSkinPotion.gd", &META_Gd__gd_core_items__Potion, true, _alloc_Gd__gd_core_items__StoneSkinPotion, &Gd__gd_core_items__StoneSkinPotion::get_static_prop_fn, &Gd__gd_core_items__StoneSkinPotion::call_static_fn};

void Gd__gd_core__WoodenSword::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__WoodenSword::meta() const { return &META_Gd__gd_core__WoodenSword; }
gd::GdVal Gd__gd_core__WoodenSword::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__WoodenSword::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__WoodenSword::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__WoodenSword::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__WoodenSword::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__WoodenSword::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__WoodenSword::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__WoodenSword::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_114, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1276), SYM_GEN_Sufficient_2603))))) {
        gd::GdVal lv_res = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_218, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__WoodenSword::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1457, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__WoodenSword(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__WoodenSword>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__WoodenSword = {CLS_Gd__gd_core__WoodenSword, "WoodenSword", "res://gd_core/WoodenSword.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__WoodenSword, &Gd__gd_core__WoodenSword::get_static_prop_fn, &Gd__gd_core__WoodenSword::call_static_fn};

void Gd__gd_core_items__Dagger::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Dagger::meta() const { return &META_Gd__gd_core_items__Dagger; }
gd::GdVal Gd__gd_core_items__Dagger::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Dagger::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Dagger::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Dagger::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Dagger::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepare_120: return true;
        case SYM_GEN_onStun_942: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Dagger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepare_120: out = fn_prepare(args, argc); return true;
        case SYM_GEN_onStun_942: out = fn_onStun(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Dagger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Dagger::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_prepare_120, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_stunned", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onStun", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Dagger::fn_onStun(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_attack_937, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Dagger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Dagger(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Dagger>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Dagger = {CLS_Gd__gd_core_items__Dagger, "Dagger", "res://gd_core_items/Dagger.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Dagger, &Gd__gd_core_items__Dagger::get_static_prop_fn, &Gd__gd_core_items__Dagger::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Crown_CrownState[] = {{"Inactive", 0LL}, {"Active", 1LL}, {"Used", 2LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Crown_CrownState = {"CrownState", _ekv_Gd__gd_core_items__Crown_CrownState, 3u};
void Gd__gd_core_items__Crown::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_crownState = gd::GdVal::from_int(0);
    this->f_activationParticles = gd::GdVal::null();
    this->f_buffTimer = gd::GdVal::null();
    this->f_manaCost = gd::GdVal::null();
    this->f_light = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Crown::meta() const { return &META_Gd__gd_core_items__Crown; }
gd::GdVal Gd__gd_core_items__Crown::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_CrownState_1726: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Crown_CrownState);
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Crown::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Crown::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_crownState_1722: out = this->f_crownState; return true;
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        case SYM_GEN_buffTimer_1723: out = this->f_buffTimer; return true;
        case SYM_GEN_manaCost_1719: out = this->f_manaCost; return true;
        case SYM_GEN_light_945: out = this->f_light; return true;
        case SYM_GEN_CrownState_1726: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Crown_CrownState); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Crown::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_crownState_1722: this->f_crownState = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        case SYM_GEN_buffTimer_1723: this->f_buffTimer = val; return true;
        case SYM_GEN_manaCost_1719: this->f_manaCost = val; return true;
        case SYM_GEN_light_945: this->f_light = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Crown::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onInvuEnded_1724: return true;
        case SYM_GEN_checkTrigger_1725: return true;
        case SYM_GEN_buffEnded_1721: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Crown::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onInvuEnded_1724: out = fn_onInvuEnded(args, argc); return true;
        case SYM_GEN_checkTrigger_1725: out = fn_checkTrigger(args, argc); return true;
        case SYM_GEN_buffEnded_1721: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Crown::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Crown::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Crown::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1726), SYM_GEN_Inactive_2593)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_mana_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkTrigger", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_invulnerable_end", 26u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onInvuEnded", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Crown::fn_onInvuEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkTrigger_1725, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Crown::fn_checkTrigger(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_crownState, gd::get_prop(gd_ctx, Gd__gd_core_items__Crown::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1726), SYM_GEN_Inactive_2593)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_isVulnerable_1271, nullptr, 0))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkMana_329, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Crown::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1726), SYM_GEN_Active_2594), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 2); })();
        gd::GdVal lv_invuDur = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_invu", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })();
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_invuDur, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_makeInvulnerable_1191, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_invuDur}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1683, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_manaCost, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_330, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Crown::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Crown::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1726), SYM_GEN_Used_2595), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Crown::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseBlind_342, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Crown::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Crown::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Crown::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1726), SYM_GEN_Inactive_2593)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Crown::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__crownState = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__crownState, gd::get_prop(gd_ctx, Gd__gd_core_items__Crown::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1726), SYM_GEN_Inactive_2593))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__crownState, gd::get_prop(gd_ctx, Gd__gd_core_items__Crown::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1726), SYM_GEN_Active_2594))))) {
    }
    else {
    }
    this->f_crownState = gd::gd_coerce_int(lv__crownState);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Crown::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BuffTimer", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffEnded", 9u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_133, _ca, 3); })();
    this->f_manaCost = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Crown(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Crown>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Crown = {CLS_Gd__gd_core_items__Crown, "Crown", "res://gd_core_items/Crown.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Crown, &Gd__gd_core_items__Crown::get_static_prop_fn, &Gd__gd_core_items__Crown::call_static_fn};

void Gd__gd_core_items__Exclusive__AmethystWhelp::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__AmethystWhelp::meta() const { return &META_Gd__gd_core_items__Exclusive__AmethystWhelp; }
gd::GdVal Gd__gd_core_items__Exclusive__AmethystWhelp::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__AmethystWhelp::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__AmethystWhelp::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__AmethystWhelp::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__AmethystWhelp::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AmethystWhelp::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__AmethystWhelp::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__AmethystWhelp::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictRandomDebuffs_355, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmethystWhelp::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeRandomBuffs_370, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmethystWhelp::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__AmethystWhelp(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__AmethystWhelp>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmethystWhelp = {CLS_Gd__gd_core_items__Exclusive__AmethystWhelp, "AmethystWhelp", "res://gd_core_items/Exclusive/AmethystWhelp.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__AmethystWhelp, &Gd__gd_core_items__Exclusive__AmethystWhelp::get_static_prop_fn, &Gd__gd_core_items__Exclusive__AmethystWhelp::call_static_fn};

void Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__CouragePuppy::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::meta() const { return &META_Gd__gd_core_items__Exclusive__ArmoredCouragePuppy; }
gd::GdVal Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__CouragePuppy::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Exclusive__CouragePuppy::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Exclusive__CouragePuppy::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__CouragePuppy::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__CouragePuppy::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__CouragePuppy::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__CouragePuppy::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Flags_1472), SYM_GEN_CanTriggerItems_2760)}; return gd::call_method(gd_ctx, this->f_damageSource, SYM_GEN_unsetFlag_1463, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Flags_1472), SYM_GEN_CanTriggerSpikes_2763)}; return gd::call_method(gd_ctx, this->f_damageSource, SYM_GEN_unsetFlag_1463, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ArmoredCouragePuppy(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ArmoredCouragePuppy>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ArmoredCouragePuppy = {CLS_Gd__gd_core_items__Exclusive__ArmoredCouragePuppy, "ArmoredCouragePuppy", "res://gd_core_items/Exclusive/ArmoredCouragePuppy.gd", &META_Gd__gd_core_items__Exclusive__CouragePuppy, true, _alloc_Gd__gd_core_items__Exclusive__ArmoredCouragePuppy, &Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::call_static_fn};

void Gd__gd_core_items__Exclusive__Bewitchment::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_typesDict = gd::GdVal::null();
    this->f_manaNeeded = gd::GdVal::null();
    this->f_numDebuffs = gd::GdVal::null();
    this->f_bonusPoison = gd::GdVal::null();
    this->f_bonusBlind = gd::GdVal::null();
    this->f_bonusCold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Bewitchment::meta() const { return &META_Gd__gd_core_items__Exclusive__Bewitchment; }
gd::GdVal Gd__gd_core_items__Exclusive__Bewitchment::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Bewitchment::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Bewitchment::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_typesDict_1972: out = this->f_typesDict; return true;
        case SYM_GEN_manaNeeded_1785: out = this->f_manaNeeded; return true;
        case SYM_GEN_numDebuffs_1952: out = this->f_numDebuffs; return true;
        case SYM_GEN_bonusPoison_1973: out = this->f_bonusPoison; return true;
        case SYM_GEN_bonusBlind_1974: out = this->f_bonusBlind; return true;
        case SYM_GEN_bonusCold_1975: out = this->f_bonusCold; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Bewitchment::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_typesDict_1972: this->f_typesDict = val; return true;
        case SYM_GEN_manaNeeded_1785: this->f_manaNeeded = val; return true;
        case SYM_GEN_numDebuffs_1952: this->f_numDebuffs = val; return true;
        case SYM_GEN_bonusPoison_1973: this->f_bonusPoison = val; return true;
        case SYM_GEN_bonusBlind_1974: this->f_bonusBlind = val; return true;
        case SYM_GEN_bonusCold_1975: this->f_bonusCold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Bewitchment::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_getDescription_638: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Bewitchment::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_getDescription_638: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Bewitchment::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Bewitchment::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Nature_2596)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Dark_2600)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Ice_2722)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Bewitchment::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_typesDict = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countTypes_493, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Bewitchment::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_638, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_placed)))) {
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$n_nature", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$n_dark", 7u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$n_ice", 6u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        return lv_descr;
    }
    this->f_typesDict = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countTypes_493, _ca, 1); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n_nature", 8u)), gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Nature_2596))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_450, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n_dark", 6u)), gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Dark_2600))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_450, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n_ice", 5u)), gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Ice_2722))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_450, _ca, 3); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Bewitchment::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getMana_1224, nullptr, 0), this->f_manaNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_330, _ca, 1); })();
        gd::GdVal lv_leastStacks = ([&]() { gd::GdVal _ca[] = {this->f_numDebuffs, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1358, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getLeastStacks_358, _ca, 3); })();
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0), gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Nature_2596)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {lv_leastStacks, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Poison_2566), this->f_bonusPoison}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_dictAdd_1693, _ca, 3); })();
        }
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0), gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Dark_2600)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {lv_leastStacks, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Blind_2567), this->f_bonusBlind}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_dictAdd_1693, _ca, 3); })();
        }
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0), gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Ice_2722)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {lv_leastStacks, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Cold_2573), this->f_bonusCold}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_dictAdd_1693, _ca, 3); })();
        }
        {
            gd::GdVal _t1831 = gd::gd_iter_seq(gd_ctx.arena, lv_leastStacks);
            gd::GdArr* _t1832 = (_t1831.kind == gd::GdVal::Kind::Arr) ? _t1831.arr : nullptr;
            uint32_t _len__t1833 = _t1832 ? _t1832->len : 0u;
            for (uint32_t _t1833 = 0; _t1833 < _len__t1833; ++_t1833) {
                gd::GdVal lv_debuffType = _t1832->data[_t1833];
                (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), lv_debuffType, gd::get_index(gd_ctx, lv_leastStacks, lv_debuffType), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_199, _ca, 4); })();
            }
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Bewitchment::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "manat", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_numDebuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "debuffs", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_bonusPoison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "poison", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_bonusBlind = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blind", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_bonusCold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Bewitchment(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Bewitchment>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Bewitchment = {CLS_Gd__gd_core_items__Exclusive__Bewitchment, "Bewitchment", "res://gd_core_items/Exclusive/Bewitchment.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Bewitchment, &Gd__gd_core_items__Exclusive__Bewitchment::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Bewitchment::call_static_fn};

void Gd__gd_core_items__Exclusive__BrassKnuckles::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_extraAccuracy = gd::GdVal::null();
    this->f_battleRageSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__BrassKnuckles::meta() const { return &META_Gd__gd_core_items__Exclusive__BrassKnuckles; }
gd::GdVal Gd__gd_core_items__Exclusive__BrassKnuckles::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__BrassKnuckles::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__BrassKnuckles::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_extraAccuracy_2005: out = this->f_extraAccuracy; return true;
        case SYM_GEN_battleRageSpeed_1969: out = this->f_battleRageSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BrassKnuckles::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_extraAccuracy_2005: this->f_extraAccuracy = val; return true;
        case SYM_GEN_battleRageSpeed_1969: this->f_battleRageSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BrassKnuckles::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onDealtDamage_904: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onBattleRageStarted_1970: return true;
        case SYM_GEN_onBattleRageEnded_1971: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BrassKnuckles::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onDealtDamage_904: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_1970: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN_onBattleRageEnded_1971: out = fn_onBattleRageEnded(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BrassKnuckles::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BrassKnuckles::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canDamage_87, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BrassKnuckles::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_170, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addCritChancePercent_177, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_extraAccuracy}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addAccuracy_175, _ca, 1); })();
        {
            gd::GdVal _t1834 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
            gd::GdArr* _t1835 = (_t1834.kind == gd::GdVal::Kind::Arr) ? _t1834.arr : nullptr;
            uint32_t _len__t1836 = _t1835 ? _t1835->len : 0u;
            for (uint32_t _t1836 = 0; _t1836 < _len__t1836; ++_t1836) {
                gd::GdVal lv_item = _t1835->data[_t1836];
                (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_170, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addCritChancePercent_177, _ca, 1); })();
                if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isWeapon_80, nullptr, 0))) {
                    (void)([&]() { gd::GdVal _ca[] = {this->f_extraAccuracy}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addAccuracy_175, _ca, 1); })();
                }
            }
        }
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_stun", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_328, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BrassKnuckles::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_started", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageStarted", 19u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_ended", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageEnded", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BrassKnuckles::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_battleRageSpeed}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BrassKnuckles::fn_onBattleRageEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_battleRageSpeed}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_reduceSpeed_272, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BrassKnuckles::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_extraAccuracy = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0);
    this->f_battleRageSpeed = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BrassKnuckles(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__BrassKnuckles>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BrassKnuckles = {CLS_Gd__gd_core_items__Exclusive__BrassKnuckles, "BrassKnuckles", "res://gd_core_items/Exclusive/BrassKnuckles.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__BrassKnuckles, &Gd__gd_core_items__Exclusive__BrassKnuckles::get_static_prop_fn, &Gd__gd_core_items__Exclusive__BrassKnuckles::call_static_fn};

void Gd__gd_core_items__Exclusive__Cheese::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Cheese::meta() const { return &META_Gd__gd_core_items__Exclusive__Cheese; }
gd::GdVal Gd__gd_core_items__Exclusive__Cheese::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Cheese::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Cheese::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Cheese::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Cheese::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Cheese::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Cheese::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Cheese::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_315, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_367, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cheese::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Cheese(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Cheese>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Cheese = {CLS_Gd__gd_core_items__Exclusive__Cheese, "Cheese", "res://gd_core_items/Exclusive/Cheese.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Exclusive__Cheese, &Gd__gd_core_items__Exclusive__Cheese::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Cheese::call_static_fn};

void Gd__gd_core_items__Exclusive__ChessMaster::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_speed_v = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ChessMaster::meta() const { return &META_Gd__gd_core_items__Exclusive__ChessMaster; }
gd::GdVal Gd__gd_core_items__Exclusive__ChessMaster::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_firstKnightRound_2079: return gd::GdVal::from_int(1LL);
        case SYM_GEN_firstRookRound_2080: return gd::GdVal::from_int(6LL);
        case SYM_GEN_firstQueenRound_2081: return gd::GdVal::from_int(14LL);
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ChessMaster::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ChessMaster::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_speed_v_2082: out = this->f_speed_v; return true;
        case SYM_GEN_firstKnightRound_2079: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_firstRookRound_2080: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_firstQueenRound_2081: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ChessMaster::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_speed_v_2082: this->f_speed_v = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ChessMaster::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ChessMaster::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ChessMaster::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ChessMaster::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chessboards = ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Chess Board", 11u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAllInInventoryOfType_799, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_chessboards, gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_speed_v}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, lv_chessboards, gd::GdVal::from_int(0LL)), SYM_GEN_addSpeed_271, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ChessMaster::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ChessMaster::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_speed_v = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ChessMaster(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ChessMaster>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ChessMaster = {CLS_Gd__gd_core_items__Exclusive__ChessMaster, "ChessMaster", "res://gd_core_items/Exclusive/ChessMaster.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__ChessMaster, &Gd__gd_core_items__Exclusive__ChessMaster::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ChessMaster::call_static_fn};

void Gd__gd_core_items__Exclusive__Daggerang::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Dagger::init_fields(gd_ctx);
    this->f_staminaReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Daggerang::meta() const { return &META_Gd__gd_core_items__Exclusive__Daggerang; }
gd::GdVal Gd__gd_core_items__Exclusive__Daggerang::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Dagger::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Daggerang::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Daggerang::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_staminaReduction_1917: out = this->f_staminaReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Daggerang::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaReduction_1917: this->f_staminaReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Daggerang::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Daggerang::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Daggerang::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Dagger::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Daggerang::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_staminaReduction)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeStaminaFactor_303, _ca, 1); })();
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_371, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Daggerang::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Dagger::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_staminaReduction = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Daggerang(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Daggerang>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Daggerang = {CLS_Gd__gd_core_items__Exclusive__Daggerang, "Daggerang", "res://gd_core_items/Exclusive/Daggerang.gd", &META_Gd__gd_core_items__Dagger, true, _alloc_Gd__gd_core_items__Exclusive__Daggerang, &Gd__gd_core_items__Exclusive__Daggerang::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Daggerang::call_static_fn};

void Gd__gd_core_items__Exclusive__DragonscaleArmor::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__DragonscaleArmor::meta() const { return &META_Gd__gd_core_items__Exclusive__DragonscaleArmor; }
gd::GdVal Gd__gd_core_items__Exclusive__DragonscaleArmor::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__DragonscaleArmor::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__DragonscaleArmor::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DragonscaleArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DragonscaleArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onBattleRageStarted_1970: return true;
        case SYM_GEN_onBattleRageEnded_1971: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DragonscaleArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_1970: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN_onBattleRageEnded_1971: out = fn_onBattleRageEnded(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DragonscaleArmor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonscaleArmor::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_started", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageStarted", 19u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_ended", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageEnded", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonscaleArmor::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_202, nullptr, 0), gd::GdVal::from_bool(true), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeDamageResistance_1259, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonscaleArmor::fn_onBattleRageEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeDamageResistance_1259, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonscaleArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DragonscaleArmor(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__DragonscaleArmor>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DragonscaleArmor = {CLS_Gd__gd_core_items__Exclusive__DragonscaleArmor, "DragonscaleArmor", "res://gd_core_items/Exclusive/DragonscaleArmor.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__DragonscaleArmor, &Gd__gd_core_items__Exclusive__DragonscaleArmor::get_static_prop_fn, &Gd__gd_core_items__Exclusive__DragonscaleArmor::call_static_fn};

void Gd__gd_core_items__Exclusive__Everburning::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_numFlames = gd::GdVal::null();
    this->f_burningSwordDescr = gd::GdVal::null();
    this->f_burningBladeDescr = gd::GdVal::null();
    this->f_staminaReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Everburning::meta() const { return &META_Gd__gd_core_items__Exclusive__Everburning; }
gd::GdVal Gd__gd_core_items__Exclusive__Everburning::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Everburning::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Everburning::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_numFlames_2152: out = this->f_numFlames; return true;
        case SYM_GEN_burningSwordDescr_2153: out = this->f_burningSwordDescr; return true;
        case SYM_GEN_burningBladeDescr_2154: out = this->f_burningBladeDescr; return true;
        case SYM_GEN_staminaReduction_1917: out = this->f_staminaReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Everburning::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numFlames_2152: this->f_numFlames = val; return true;
        case SYM_GEN_burningSwordDescr_2153: this->f_burningSwordDescr = val; return true;
        case SYM_GEN_burningBladeDescr_2154: this->f_burningBladeDescr = val; return true;
        case SYM_GEN_staminaReduction_1917: this->f_staminaReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Everburning::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_canAffect_global_1918: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Everburning::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_canAffect_global_1918: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Everburning::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Everburning::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_numFlames = ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Flame", 5u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countAllInInventoryOfType_800, _ca, 1); })();
    {
        gd::GdVal _t1837 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {this->f_burningSwordDescr}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAllInInventoryOfType_799, _ca, 1); })());
        gd::GdArr* _t1838 = (_t1837.kind == gd::GdVal::Kind::Arr) ? _t1837.arr : nullptr;
        uint32_t _len__t1839 = _t1838 ? _t1838->len : 0u;
        for (uint32_t _t1839 = 0; _t1839 < _len__t1839; ++_t1839) {
            gd::GdVal lv_item = _t1838->data[_t1839];
            (void)([&]() { gd::GdVal _ca[] = {this->f_staminaReduction}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeStaminaFactor_303, _ca, 1); })();
        }
    }
    {
        gd::GdVal _t1840 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {this->f_burningBladeDescr}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAllInInventoryOfType_799, _ca, 1); })());
        gd::GdArr* _t1841 = (_t1840.kind == gd::GdVal::Kind::Arr) ? _t1840.arr : nullptr;
        uint32_t _len__t1842 = _t1841 ? _t1841->len : 0u;
        for (uint32_t _t1842 = 0; _t1842 < _len__t1842; ++_t1842) {
            gd::GdVal lv_item = _t1841->data[_t1842];
            (void)([&]() { gd::GdVal _ca[] = {this->f_staminaReduction}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeStaminaFactor_303, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Everburning::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_numFlames, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), this->f_numFlames)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_143, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Everburning::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Flame", 5u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })()}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_243, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_burningBladeDescr}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_243, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_burningSwordDescr}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_243, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Everburning::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_burningSwordDescr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Burning Sword", 13u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })();
    this->f_burningBladeDescr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Burning Blade", 13u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })();
    this->f_staminaReduction = gd::gd_neg(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Everburning(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Everburning>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Everburning = {CLS_Gd__gd_core_items__Exclusive__Everburning, "Everburning", "res://gd_core_items/Exclusive/Everburning.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Everburning, &Gd__gd_core_items__Exclusive__Everburning::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Everburning::call_static_fn};

void Gd__gd_core_items__Exclusive__FriendlyFire::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_maxHeatReached = gd::GdVal::from_int(0);
    this->f_manaNeeded = gd::GdVal::from_int(0);
    this->f_threshold1 = gd::GdVal::from_int(0);
    this->f_threshold2 = gd::GdVal::from_int(0);
    this->f_threshold3 = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__FriendlyFire::meta() const { return &META_Gd__gd_core_items__Exclusive__FriendlyFire; }
gd::GdVal Gd__gd_core_items__Exclusive__FriendlyFire::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__FriendlyFire::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__FriendlyFire::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_maxHeatReached_2168: out = this->f_maxHeatReached; return true;
        case SYM_GEN_manaNeeded_1785: out = this->f_manaNeeded; return true;
        case SYM_GEN_threshold1_2169: out = this->f_threshold1; return true;
        case SYM_GEN_threshold2_2170: out = this->f_threshold2; return true;
        case SYM_GEN_threshold3_2171: out = this->f_threshold3; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__FriendlyFire::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_maxHeatReached_2168: this->f_maxHeatReached = gd::gd_coerce_int(val); return true;
        case SYM_GEN_manaNeeded_1785: this->f_manaNeeded = gd::gd_coerce_int(val); return true;
        case SYM_GEN_threshold1_2169: this->f_threshold1 = gd::gd_coerce_int(val); return true;
        case SYM_GEN_threshold2_2170: this->f_threshold2 = gd::gd_coerce_int(val); return true;
        case SYM_GEN_threshold3_2171: this->f_threshold3 = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__FriendlyFire::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onHeatChanged_909: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__FriendlyFire::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onHeatChanged_909: out = fn_onHeatChanged(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__FriendlyFire::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__FriendlyFire::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Fire_2599)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FriendlyFire::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Fire_2599)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffected_type_427, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0)), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    this->f_maxHeatReached = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_heat_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onHeatChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FriendlyFire::fn_onHeatChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_newMaxHeat = gd::gd_max(this->f_maxHeatReached, gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getHeat_1231, nullptr, 0));
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_newMaxHeat, this->f_threshold3))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_maxHeatReached, this->f_threshold3)))) : gd::GdVal::from_bool(false)))) {
        this->f_maxHeatReached = gd::gd_coerce_int(lv_newMaxHeat);
        gd::GdVal lv_dam = gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1577);
        gd::GdVal lv_damageRes = ([&]() { gd::GdVal _ca[] = {lv_dam, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealEffectDamage_219, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    }
    else if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_newMaxHeat, this->f_threshold2))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_maxHeatReached, this->f_threshold2)))) : gd::GdVal::from_bool(false)))) {
        this->f_maxHeatReached = gd::gd_coerce_int(lv_newMaxHeat);
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP7_267, nullptr, 0), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    }
    else if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_newMaxHeat, this->f_threshold1))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_maxHeatReached, this->f_threshold1)))) : gd::GdVal::from_bool(false)))) {
        this->f_maxHeatReached = gd::gd_coerce_int(lv_newMaxHeat);
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_265, nullptr, 0), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FriendlyFire::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getMana_1224, nullptr, 0), this->f_manaNeeded)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_330, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FriendlyFire::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0));
    this->f_threshold1 = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0));
    this->f_threshold2 = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP6_266, nullptr, 0));
    this->f_threshold3 = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP8_268, nullptr, 0));
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1457, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__FriendlyFire(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__FriendlyFire>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FriendlyFire = {CLS_Gd__gd_core_items__Exclusive__FriendlyFire, "FriendlyFire", "res://gd_core_items/Exclusive/FriendlyFire.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__FriendlyFire, &Gd__gd_core_items__Exclusive__FriendlyFire::get_static_prop_fn, &Gd__gd_core_items__Exclusive__FriendlyFire::call_static_fn};

void Gd__gd_core_items__Exclusive__Hardwood::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_hasCommonMeleeWeapon = gd::GdVal::from_bool(false);
    this->f_numCommons = gd::GdVal::from_int(0);
    this->f_commonDam = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Hardwood::meta() const { return &META_Gd__gd_core_items__Exclusive__Hardwood; }
gd::GdVal Gd__gd_core_items__Exclusive__Hardwood::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Hardwood::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Hardwood::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_hasCommonMeleeWeapon_2198: out = this->f_hasCommonMeleeWeapon; return true;
        case SYM_GEN_numCommons_2199: out = this->f_numCommons; return true;
        case SYM_GEN_commonDam_2200: out = this->f_commonDam; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Hardwood::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hasCommonMeleeWeapon_2198: this->f_hasCommonMeleeWeapon = val; return true;
        case SYM_GEN_numCommons_2199: this->f_numCommons = gd::gd_coerce_int(val); return true;
        case SYM_GEN_commonDam_2200: this->f_commonDam = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Hardwood::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_isMeleeWeapon_1624: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_onItemsCounted_2201: return true;
        case SYM_GEN_onItemRoll_1922: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Hardwood::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_isMeleeWeapon_1624: out = fn_isMeleeWeapon(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onItemsCounted_2201: out = fn_onItemsCounted(args, argc); return true;
        case SYM_GEN_onItemRoll_1922: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Hardwood::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Hardwood::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, lv_item, SYM_GEN_getRarity_234, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Rarity_858), SYM_GEN_Common_2734)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hardwood::fn_isMeleeWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), SYM_GEN_isMeleeWeapon_1624, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hardwood::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_numCommons = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    {
        gd::GdVal _t1843 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1844 = (_t1843.kind == gd::GdVal::Kind::Arr) ? _t1843.arr : nullptr;
        uint32_t _len__t1845 = _t1844 ? _t1844->len : 0u;
        for (uint32_t _t1845 = 0; _t1845 < _len__t1845; ++_t1845) {
            gd::GdVal lv_item = _t1844->data[_t1845];
            this->f_numCommons = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numCommons, gd::GdVal::from_int(1LL)));
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isMeleeWeapon_1624, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_commonDam}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamageFactor_304, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hardwood::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_numCommons, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_202, nullptr, 0), this->f_numCommons)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hardwood::fn_onItemsCounted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hardwood::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hardwood::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_commonDam = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Hardwood(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Hardwood>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Hardwood = {CLS_Gd__gd_core_items__Exclusive__Hardwood, "Hardwood", "res://gd_core_items/Exclusive/Hardwood.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Hardwood, &Gd__gd_core_items__Exclusive__Hardwood::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Hardwood::call_static_fn};

void Gd__gd_core_items__Exclusive__InnerPower::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_healAmpAcc = gd::GdVal::from_float(0.0);
    this->f_speedAcc = gd::GdVal::from_float(0.0);
    this->f_luck = gd::GdVal::null();
    this->f_empower = gd::GdVal::null();
    this->f_healAmpPerLuck = gd::GdVal::null();
    this->f_speedPerEmpower = gd::GdVal::null();
    this->f_healAmpMax = gd::GdVal::null();
    this->f_speedMax = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__InnerPower::meta() const { return &META_Gd__gd_core_items__Exclusive__InnerPower; }
gd::GdVal Gd__gd_core_items__Exclusive__InnerPower::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__InnerPower::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__InnerPower::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_healAmpAcc_2222: out = this->f_healAmpAcc; return true;
        case SYM_GEN_speedAcc_2223: out = this->f_speedAcc; return true;
        case SYM_GEN_luck_893: out = this->f_luck; return true;
        case SYM_GEN_empower_994: out = this->f_empower; return true;
        case SYM_GEN_healAmpPerLuck_2224: out = this->f_healAmpPerLuck; return true;
        case SYM_GEN_speedPerEmpower_2225: out = this->f_speedPerEmpower; return true;
        case SYM_GEN_healAmpMax_2226: out = this->f_healAmpMax; return true;
        case SYM_GEN_speedMax_2227: out = this->f_speedMax; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__InnerPower::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_healAmpAcc_2222: this->f_healAmpAcc = gd::gd_coerce_float(val); return true;
        case SYM_GEN_speedAcc_2223: this->f_speedAcc = gd::gd_coerce_float(val); return true;
        case SYM_GEN_luck_893: this->f_luck = val; return true;
        case SYM_GEN_empower_994: this->f_empower = val; return true;
        case SYM_GEN_healAmpPerLuck_2224: this->f_healAmpPerLuck = val; return true;
        case SYM_GEN_speedPerEmpower_2225: this->f_speedPerEmpower = val; return true;
        case SYM_GEN_healAmpMax_2226: this->f_healAmpMax = val; return true;
        case SYM_GEN_speedMax_2227: this->f_speedMax = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__InnerPower::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onLuckChanged_1968: return true;
        case SYM_GEN_onEmpowerChanged_2017: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__InnerPower::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onLuckChanged_1968: out = fn_onLuckChanged(args, argc); return true;
        case SYM_GEN_onEmpowerChanged_2017: out = fn_onEmpowerChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__InnerPower::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__InnerPower::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_93, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canHealOrLifesteal_290, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__InnerPower::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_empower}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__InnerPower::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_healAmpAcc = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    this->f_speedAcc = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_lucky_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onLuckChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_empower_changed", 25u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onEmpowerChanged", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__InnerPower::fn_onLuckChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_before = gd::gd_min(this->f_healAmpAcc, this->f_healAmpMax);
    gd::GdVal lv_dif = gd::gd_mul(lv_amount, this->f_healAmpPerLuck);
    this->f_healAmpAcc = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_healAmpAcc, lv_dif));
    gd::GdVal lv_healAmpToGive = gd::gd_sub(gd::gd_min(this->f_healAmpAcc, this->f_healAmpMax), lv_before);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_healAmpToGive, gd::GdVal::from_int(0LL))))) {
        {
            gd::GdVal _t1846 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
            gd::GdArr* _t1847 = (_t1846.kind == gd::GdVal::Kind::Arr) ? _t1846.arr : nullptr;
            uint32_t _len__t1848 = _t1847 ? _t1847->len : 0u;
            for (uint32_t _t1848 = 0; _t1848 < _len__t1848; ++_t1848) {
                gd::GdVal lv_item = _t1847->data[_t1848];
                (void)([&]() { gd::GdVal _ca[] = {lv_healAmpToGive}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeHealAmp_302, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__InnerPower::fn_onEmpowerChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_before = gd::gd_min(this->f_speedAcc, this->f_speedMax);
    gd::GdVal lv_dif = gd::gd_mul(lv_amount, this->f_speedPerEmpower);
    this->f_speedAcc = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_speedAcc, lv_dif));
    gd::GdVal lv_speedToGive = gd::gd_sub(gd::gd_min(this->f_speedAcc, this->f_speedMax), lv_before);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_speedToGive, gd::GdVal::from_int(0LL))))) {
        {
            gd::GdVal _t1849 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
            gd::GdArr* _t1850 = (_t1849.kind == gd::GdVal::Kind::Arr) ? _t1849.arr : nullptr;
            uint32_t _len__t1851 = _t1850 ? _t1850->len : 0u;
            for (uint32_t _t1851 = 0; _t1851 < _len__t1851; ++_t1851) {
                gd::GdVal lv_item = _t1850->data[_t1851];
                (void)([&]() { gd::GdVal _ca[] = {lv_speedToGive}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__InnerPower::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_healAmpPerLuck = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healamp", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_speedPerEmpower = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_healAmpMax = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "max1", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_speedMax = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "max2", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__InnerPower(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__InnerPower>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__InnerPower = {CLS_Gd__gd_core_items__Exclusive__InnerPower, "InnerPower", "res://gd_core_items/Exclusive/InnerPower.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__InnerPower, &Gd__gd_core_items__Exclusive__InnerPower::get_static_prop_fn, &Gd__gd_core_items__Exclusive__InnerPower::call_static_fn};

void Gd__gd_core_items__Exclusive__LightningStaff::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_attackCounter = gd::GdVal::from_int(0LL);
    this->f_manaCost = gd::GdVal::null();
    this->f_permDamBonus = gd::GdVal::null();
    this->f_chargeDamBase = gd::GdVal::null();
    this->f_chargeDamPerTile = gd::GdVal::null();
    this->f_numAttacks = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__LightningStaff::meta() const { return &META_Gd__gd_core_items__Exclusive__LightningStaff; }
gd::GdVal Gd__gd_core_items__Exclusive__LightningStaff::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_chargeCells_1959: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(2LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(2LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(2LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(3LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(2LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(4LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(5LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(4LL)).as_float(), (gd::GdVal::from_int(1LL)).as_float())}));
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__LightningStaff::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__LightningStaff::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_attackCounter_997: out = this->f_attackCounter; return true;
        case SYM_GEN_manaCost_1719: out = this->f_manaCost; return true;
        case SYM_GEN_permDamBonus_993: out = this->f_permDamBonus; return true;
        case SYM_GEN_chargeDamBase_2251: out = this->f_chargeDamBase; return true;
        case SYM_GEN_chargeDamPerTile_2252: out = this->f_chargeDamPerTile; return true;
        case SYM_GEN_numAttacks_2253: out = this->f_numAttacks; return true;
        case SYM_GEN_chargeCells_1959: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__LightningStaff::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_attackCounter_997: this->f_attackCounter = val; return true;
        case SYM_GEN_manaCost_1719: this->f_manaCost = val; return true;
        case SYM_GEN_permDamBonus_993: this->f_permDamBonus = val; return true;
        case SYM_GEN_chargeDamBase_2251: this->f_chargeDamBase = val; return true;
        case SYM_GEN_chargeDamPerTile_2252: this->f_chargeDamPerTile = val; return true;
        case SYM_GEN_numAttacks_2253: this->f_numAttacks = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__LightningStaff::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN_canAffect_lightning_287: return true;
        case SYM_GEN_emitCharge_1962: return true;
        case SYM_GEN_onChargeEnteredCell_1963: return true;
        case SYM_GEN_chargedItemStatChange_1964: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__LightningStaff::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_canAffect_lightning_287: out = fn_canAffect_lightning(args, argc); return true;
        case SYM_GEN_emitCharge_1962: out = fn_emitCharge(args, argc); return true;
        case SYM_GEN_onChargeEnteredCell_1963: out = fn_onChargeEnteredCell(args, argc); return true;
        case SYM_GEN_chargedItemStatChange_1964: out = fn_chargedItemStatChange(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__LightningStaff::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__LightningStaff::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_attackCounter = gd::GdVal::from_int(0LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LightningStaff::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_331, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_event, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_permDamBonus}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_159, _ca, 1); })();
    }
    this->f_attackCounter = gd::gd_add(gd_ctx, this->f_attackCounter, gd::GdVal::from_int(1LL));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_attackCounter, this->f_numAttacks)))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_emitCharge_1962, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "charge_emitted", 14u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_obj(this)}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1375), SYM_GEN_emitSignal_1499, _ca, 3); })();
        this->f_attackCounter = gd::GdVal::from_int(0LL);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LightningStaff::fn_canAffect_lightning(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_reactsToCharges_297, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LightningStaff::fn_emitCharge(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_speedFactor = (_argc > 0) ? _args[0] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), Gd__gd_core_items__Exclusive__LightningStaff::get_static_const_or_enum(gd_ctx, SYM_GEN_chargeCells_1959), lv_speedFactor, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_sendCharge_318, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LightningStaff::fn_onChargeEnteredCell(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cellIndex = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_charge, lv_cellIndex, this->f_chargeDamBase, this->f_chargeDamPerTile}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeChargedItemStat_324, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LightningStaff::fn_chargedItemStatChange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_value, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_159, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LightningStaff::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_manaCost = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "manat", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_permDamBonus = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_chargeDamBase = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam_flat", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_chargeDamPerTile = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam_tile", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_numAttacks = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "num", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__LightningStaff(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__LightningStaff>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__LightningStaff = {CLS_Gd__gd_core_items__Exclusive__LightningStaff, "LightningStaff", "res://gd_core_items/Exclusive/LightningStaff.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__LightningStaff, &Gd__gd_core_items__Exclusive__LightningStaff::get_static_prop_fn, &Gd__gd_core_items__Exclusive__LightningStaff::call_static_fn};

void Gd__gd_core_items__Exclusive__Markswoman::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_rangedBonusDam = gd::GdVal::null();
    this->f_rangedBonusSpeed = gd::GdVal::null();
    this->f_rangedBonusAcc = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Markswoman::meta() const { return &META_Gd__gd_core_items__Exclusive__Markswoman; }
gd::GdVal Gd__gd_core_items__Exclusive__Markswoman::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Markswoman::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Markswoman::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_rangedBonusDam_2298: out = this->f_rangedBonusDam; return true;
        case SYM_GEN_rangedBonusSpeed_2299: out = this->f_rangedBonusSpeed; return true;
        case SYM_GEN_rangedBonusAcc_2300: out = this->f_rangedBonusAcc; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Markswoman::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_rangedBonusDam_2298: this->f_rangedBonusDam = val; return true;
        case SYM_GEN_rangedBonusSpeed_2299: this->f_rangedBonusSpeed = val; return true;
        case SYM_GEN_rangedBonusAcc_2300: this->f_rangedBonusAcc = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Markswoman::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Markswoman::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Markswoman::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Markswoman::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), SYM_GEN_isRangedWeapon_1625, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Markswoman::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1852 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1853 = (_t1852.kind == gd::GdVal::Kind::Arr) ? _t1852.arr : nullptr;
        uint32_t _len__t1854 = _t1853 ? _t1853->len : 0u;
        for (uint32_t _t1854 = 0; _t1854 < _len__t1854; ++_t1854) {
            gd::GdVal lv_item = _t1853->data[_t1854];
            (void)([&]() { gd::GdVal _ca[] = {this->f_rangedBonusSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_rangedBonusDam}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamageFactor_304, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {this->f_rangedBonusAcc}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addAccuracy_175, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Markswoman::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_rangedBonusDam = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_rangedBonusSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_rangedBonusAcc = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "acc", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Markswoman(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Markswoman>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Markswoman = {CLS_Gd__gd_core_items__Exclusive__Markswoman, "Markswoman", "res://gd_core_items/Exclusive/Markswoman.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Markswoman, &Gd__gd_core_items__Exclusive__Markswoman::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Markswoman::call_static_fn};

void Gd__gd_core_items__Exclusive__OilLamp::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_bonusDam = gd::GdVal::null();
    this->f_bonusAcc = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__OilLamp::meta() const { return &META_Gd__gd_core_items__Exclusive__OilLamp; }
gd::GdVal Gd__gd_core_items__Exclusive__OilLamp::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__OilLamp::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__OilLamp::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_bonusDam_1779: out = this->f_bonusDam; return true;
        case SYM_GEN_bonusAcc_2321: out = this->f_bonusAcc; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__OilLamp::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusDam_1779: this->f_bonusDam = val; return true;
        case SYM_GEN_bonusAcc_2321: this->f_bonusAcc = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__OilLamp::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__OilLamp::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__OilLamp::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__OilLamp::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OilLamp::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OilLamp::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1855 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1856 = (_t1855.kind == gd::GdVal::Kind::Arr) ? _t1855.arr : nullptr;
        uint32_t _len__t1857 = _t1856 ? _t1856->len : 0u;
        for (uint32_t _t1857 = 0; _t1857 < _len__t1857; ++_t1857) {
            gd::GdVal lv_item = _t1856->data[_t1857];
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusDam}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_159, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusAcc}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addAccuracy_175, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OilLamp::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_bonusDam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_bonusAcc = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "accuracy", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__OilLamp(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__OilLamp>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__OilLamp = {CLS_Gd__gd_core_items__Exclusive__OilLamp, "OilLamp", "res://gd_core_items/Exclusive/OilLamp.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__OilLamp, &Gd__gd_core_items__Exclusive__OilLamp::get_static_prop_fn, &Gd__gd_core_items__Exclusive__OilLamp::call_static_fn};

void Gd__gd_core_items__Exclusive__Pop::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_previousSpeedBonus = gd::GdVal::from_float(0.0);
    this->f_speedPerMana = gd::GdVal::null();
    this->f_maxSpeedBonus = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Pop::meta() const { return &META_Gd__gd_core_items__Exclusive__Pop; }
gd::GdVal Gd__gd_core_items__Exclusive__Pop::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Pop::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Pop::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_previousSpeedBonus_2336: out = this->f_previousSpeedBonus; return true;
        case SYM_GEN_speedPerMana_2337: out = this->f_speedPerMana; return true;
        case SYM_GEN_maxSpeedBonus_2001: out = this->f_maxSpeedBonus; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Pop::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_previousSpeedBonus_2336: this->f_previousSpeedBonus = gd::gd_coerce_float(val); return true;
        case SYM_GEN_speedPerMana_2337: this->f_speedPerMana = val; return true;
        case SYM_GEN_maxSpeedBonus_2001: this->f_maxSpeedBonus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Pop::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onManaChanged_1833: return true;
        case SYM_GEN_playPickupSound_732: return true;
        case SYM_GEN_playDropSound_147: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Pop::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onManaChanged_1833: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN_playPickupSound_732: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_147: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Pop::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Pop::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_previousSpeedBonus = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_mana_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onManaChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pop::fn_onManaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_speed = gd::gd_min(this->f_maxSpeedBonus, gd::gd_mul(this->f_speedPerMana, gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getMana_1224, nullptr, 0)));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::gd_sub(lv_speed, this->f_previousSpeedBonus), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(lv_speed, this->f_previousSpeedBonus)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
        this->f_previousSpeedBonus = gd::gd_coerce_float(lv_speed);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pop::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pop::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pop::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_speedPerMana = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_maxSpeedBonus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "max", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Pop(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Pop>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Pop = {CLS_Gd__gd_core_items__Exclusive__Pop, "Pop", "res://gd_core_items/Exclusive/Pop.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__Pop, &Gd__gd_core_items__Exclusive__Pop::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Pop::call_static_fn};

void Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Goobert::init_fields(gd_ctx);
    this->f_vampirism = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
    this->f_stamina = gd::GdVal::null();
    this->f_blind = gd::GdVal::null();
    this->f_dambonus = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::meta() const { return &META_Gd__gd_core_items__Exclusive__RainbowGoobertEngineer; }
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_vampirism_936: out = this->f_vampirism; return true;
        case SYM_GEN_regen_1903: out = this->f_regen; return true;
        case SYM_GEN_stamina_2059: out = this->f_stamina; return true;
        case SYM_GEN_blind_1815: out = this->f_blind; return true;
        case SYM_GEN_dambonus_2356: out = this->f_dambonus; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_vampirism_936: this->f_vampirism = val; return true;
        case SYM_GEN_regen_1903: this->f_regen = val; return true;
        case SYM_GEN_stamina_2059: this->f_stamina = val; return true;
        case SYM_GEN_blind_1815: this->f_blind = val; return true;
        case SYM_GEN_dambonus_2356: this->f_dambonus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {this->f_stamina}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_316, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_vampirism}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_208, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_blind}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_211, _ca, 1); })();
    {
        gd::GdVal _t1858 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1859 = (_t1858.kind == gd::GdVal::Kind::Arr) ? _t1858.arr : nullptr;
        uint32_t _len__t1860 = _t1859 ? _t1859->len : 0u;
        for (uint32_t _t1860 = 0; _t1860 < _len__t1860; ++_t1860) {
            gd::GdVal lv_item = _t1859->data[_t1860];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_dambonus}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_159, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_vampirism = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vampirism", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_blind = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blind", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_dambonus = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dambonus", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__RainbowGoobertEngineer(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__RainbowGoobertEngineer>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RainbowGoobertEngineer = {CLS_Gd__gd_core_items__Exclusive__RainbowGoobertEngineer, "RainbowGoobertEngineer", "res://gd_core_items/Exclusive/RainbowGoobertEngineer.gd", &META_Gd__gd_core_items__Goobert, true, _alloc_Gd__gd_core_items__Exclusive__RainbowGoobertEngineer, &Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::get_static_prop_fn, &Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::call_static_fn};

void Gd__gd_core_items__Exclusive__SapphireEgg::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__DragonEgg::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SapphireEgg::meta() const { return &META_Gd__gd_core_items__Exclusive__SapphireEgg; }
gd::GdVal Gd__gd_core_items__Exclusive__SapphireEgg::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__DragonEgg::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SapphireEgg::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SapphireEgg::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__DragonEgg::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SapphireEgg::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__DragonEgg::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SapphireEgg::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__DragonEgg::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SapphireEgg::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__DragonEgg::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SapphireEgg::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__DragonEgg::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SapphireEgg::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCooldownEffect_142, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SapphireEgg::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SapphireEgg::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__DragonEgg::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SapphireEgg(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SapphireEgg>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SapphireEgg = {CLS_Gd__gd_core_items__Exclusive__SapphireEgg, "SapphireEgg", "res://gd_core_items/Exclusive/SapphireEgg.gd", &META_Gd__gd_core_items__DragonEgg, true, _alloc_Gd__gd_core_items__Exclusive__SapphireEgg, &Gd__gd_core_items__Exclusive__SapphireEgg::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SapphireEgg::call_static_fn};

void Gd__gd_core_items__Exclusive__SliceofBread::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
    this->f_staminaThreshold = gd::GdVal::null();
    this->f_stamina = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SliceofBread::meta() const { return &META_Gd__gd_core_items__Exclusive__SliceofBread; }
gd::GdVal Gd__gd_core_items__Exclusive__SliceofBread::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SliceofBread::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SliceofBread::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_staminaThreshold_1979: out = this->f_staminaThreshold; return true;
        case SYM_GEN_stamina_2059: out = this->f_stamina; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SliceofBread::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaThreshold_1979: this->f_staminaThreshold = val; return true;
        case SYM_GEN_stamina_2059: this->f_stamina = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SliceofBread::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SliceofBread::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SliceofBread::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SliceofBread::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getCurrentStamina_1242, nullptr, 0), this->f_staminaThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_stamina}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_316, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SliceofBread::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_staminaThreshold = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "staminat", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SliceofBread(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SliceofBread>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SliceofBread = {CLS_Gd__gd_core_items__Exclusive__SliceofBread, "SliceofBread", "res://gd_core_items/Exclusive/SliceofBread.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Exclusive__SliceofBread, &Gd__gd_core_items__Exclusive__SliceofBread::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SliceofBread::call_static_fn};

void Gd__gd_core_items__Exclusive__SpellScrollIce::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_activated = gd::GdVal::from_bool(false);
    this->f_coldInflicted = gd::GdVal::from_int(0);
    this->f_cold = gd::GdVal::null();
    this->f_maxCold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SpellScrollIce::meta() const { return &META_Gd__gd_core_items__Exclusive__SpellScrollIce; }
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollIce::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SpellScrollIce::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SpellScrollIce::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activated_1292: out = this->f_activated; return true;
        case SYM_GEN_coldInflicted_2185: out = this->f_coldInflicted; return true;
        case SYM_GEN_cold_1949: out = this->f_cold; return true;
        case SYM_GEN_maxCold_2431: out = this->f_maxCold; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SpellScrollIce::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1292: this->f_activated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_coldInflicted_2185: this->f_coldInflicted = gd::gd_coerce_int(val); return true;
        case SYM_GEN_cold_1949: this->f_cold = val; return true;
        case SYM_GEN_maxCold_2431: this->f_maxCold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SpellScrollIce::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCharacterAttacked_1849: return true;
        case SYM_GEN_onShieldOrArmorActivated_2221: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SpellScrollIce::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCharacterAttacked_1849: out = fn_onCharacterAttacked(args, argc); return true;
        case SYM_GEN_onShieldOrArmorActivated_2221: out = fn_onShieldOrArmorActivated(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SpellScrollIce::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollIce::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Shield_2753)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Armor_2750)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canActivate_89, nullptr, 0))) : gd::GdVal::from_bool(false)))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollIce::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pre_take_damage_late", 20u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onCharacterAttacked", 19u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    {
        gd::GdVal _t1861 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1862 = (_t1861.kind == gd::GdVal::Kind::Arr) ? _t1861.arr : nullptr;
        uint32_t _len__t1863 = _t1862 ? _t1862->len : 0u;
        for (uint32_t _t1863 = 0; _t1863 < _len__t1863; ++_t1863) {
            gd::GdVal lv_item = _t1862->data[_t1863];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onShieldOrArmorActivated", 24u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        }
    }
    this->f_coldInflicted = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollIce::fn_onCharacterAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated)))) {
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0)}; return gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_willBeLethal_1441, _ca, 1); })())) {
            gd::GdVal lv_opponentCold = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_getCold_1234, nullptr, 0);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_opponentCold, gd::GdVal::from_int(0LL))))) {
                this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
                (void)([&]() { gd::GdVal _ca[] = {lv_opponentCold, gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_loseCold_1237, _ca, 3); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_round(gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_202, nullptr, 0), lv_opponentCold)), gd::GdVal::from_bool(true), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, _ca, 3); })();
                (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_379, nullptr, 0);
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollIce::fn_onShieldOrArmorActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_coldInflicted, this->f_maxCold))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        this->f_coldInflicted = gd::gd_coerce_int(gd::gd_min(this->f_cold, gd::gd_sub(this->f_maxCold, this->f_coldInflicted)));
        (void)([&]() { gd::GdVal _ca[] = {this->f_cold, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_349, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollIce::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_cold = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_maxCold = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "max", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SpellScrollIce(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SpellScrollIce>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpellScrollIce = {CLS_Gd__gd_core_items__Exclusive__SpellScrollIce, "SpellScrollIce", "res://gd_core_items/Exclusive/SpellScrollIce.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__SpellScrollIce, &Gd__gd_core_items__Exclusive__SpellScrollIce::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SpellScrollIce::call_static_fn};

void Gd__gd_core_items__Exclusive__StoneBadge::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_goldValue = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__StoneBadge::meta() const { return &META_Gd__gd_core_items__Exclusive__StoneBadge; }
gd::GdVal Gd__gd_core_items__Exclusive__StoneBadge::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__StoneBadge::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__StoneBadge::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_goldValue_2454: out = this->f_goldValue; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__StoneBadge::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_goldValue_2454: this->f_goldValue = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__StoneBadge::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onAddToInventory_417: return true;
        case SYM_GEN_onAddedToStorageBox_677: return true;
        case SYM_GEN_discard_760: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_getItemsMaxCost_2455: return true;
        case SYM_GEN_getRelatedItems_457: return true;
        case SYM_GEN_getRelatedItemColumns_695: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__StoneBadge::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onAddToInventory_417: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onAddedToStorageBox_677: out = fn_onAddedToStorageBox(args, argc); return true;
        case SYM_GEN_discard_760: out = fn_discard(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_getItemsMaxCost_2455: out = fn_getItemsMaxCost(args, argc); return true;
        case SYM_GEN_getRelatedItems_457: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_695: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__StoneBadge::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneBadge::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneBadge::fn_onAddedToStorageBox(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneBadge::fn_discard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_discardGems = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    (void)([&]() { gd::GdVal _ca[] = {lv_discardGems}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_discard_760, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneBadge::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneBadge::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneBadge::fn_getItemsMaxCost(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_maxCost = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneBadge::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {this->f_goldValue}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsMaxCost_2455, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneBadge::fn_getRelatedItemColumns(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(4LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneBadge::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_goldValue = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "goldvalue", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__StoneBadge(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__StoneBadge>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StoneBadge = {CLS_Gd__gd_core_items__Exclusive__StoneBadge, "StoneBadge", "res://gd_core_items/Exclusive/StoneBadge.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__StoneBadge, &Gd__gd_core_items__Exclusive__StoneBadge::get_static_prop_fn, &Gd__gd_core_items__Exclusive__StoneBadge::call_static_fn};

void Gd__gd_core_items__Exclusive__ThunderDrake::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_active = gd::GdVal::from_bool(false);
    this->f_curHitCount = gd::GdVal::from_int(0);
    this->f_lightningMultiplicity = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_numHits = gd::GdVal::null();
    this->f_buffSpeed = gd::GdVal::null();
    this->f_buffTimer = gd::GdVal::null();
    this->f_buffParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ThunderDrake::meta() const { return &META_Gd__gd_core_items__Exclusive__ThunderDrake; }
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ThunderDrake::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ThunderDrake::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_active_2128: out = this->f_active; return true;
        case SYM_GEN_curHitCount_2490: out = this->f_curHitCount; return true;
        case SYM_GEN_lightningMultiplicity_2491: out = this->f_lightningMultiplicity; return true;
        case SYM_GEN_numHits_1000: out = this->f_numHits; return true;
        case SYM_GEN_buffSpeed_2492: out = this->f_buffSpeed; return true;
        case SYM_GEN_buffTimer_1723: out = this->f_buffTimer; return true;
        case SYM_GEN_buffParticles_1788: out = this->f_buffParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ThunderDrake::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_active_2128: this->f_active = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_curHitCount_2490: this->f_curHitCount = gd::gd_coerce_int(val); return true;
        case SYM_GEN_lightningMultiplicity_2491: this->f_lightningMultiplicity = val; return true;
        case SYM_GEN_numHits_1000: this->f_numHits = val; return true;
        case SYM_GEN_buffSpeed_2492: this->f_buffSpeed = val; return true;
        case SYM_GEN_buffTimer_1723: this->f_buffTimer = val; return true;
        case SYM_GEN_buffParticles_1788: this->f_buffParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ThunderDrake::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_lightning_287: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onDealtDamage_904: return true;
        case SYM_GEN_zapItem_2493: return true;
        case SYM_GEN_onBuffEnded_2494: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN_getCraftingOffset_846: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ThunderDrake::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_lightning_287: out = fn_canAffect_lightning(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDealtDamage_904: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_zapItem_2493: out = fn_zapItem(args, argc); return true;
        case SYM_GEN_onBuffEnded_2494: out = fn_onBuffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_getCraftingOffset_846: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ThunderDrake::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::fn_canAffect_lightning(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_93, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_reactsToCharges_297, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    this->f_curHitCount = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_lightningMultiplicity = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Lightning_2611)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countItemsInAffectedCells_cached_422, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        this->f_curHitCount = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_curHitCount, gd::GdVal::from_int(1LL)));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_curHitCount, this->f_numHits)))) {
            if (gd::gd_truth(this->f_active)) {
                {
                    gd::GdVal _t1864 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Lightning_2611)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, _ca, 1); })());
                    gd::GdArr* _t1865 = (_t1864.kind == gd::GdVal::Kind::Arr) ? _t1864.arr : nullptr;
                    uint32_t _len__t1866 = _t1865 ? _t1865->len : 0u;
                    for (uint32_t _t1866 = 0; _t1866 < _len__t1866; ++_t1866) {
                        gd::GdVal lv_item = _t1865->data[_t1866];
                        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_chargeLeft_323, _ca, 1); })();
                        (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_zapItem_2493, _ca, 1); })();
                    }
                }
            }
            else {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
                {
                    gd::GdVal _t1867 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Lightning_2611)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, _ca, 1); })());
                    gd::GdArr* _t1868 = (_t1867.kind == gd::GdVal::Kind::Arr) ? _t1867.arr : nullptr;
                    uint32_t _len__t1869 = _t1868 ? _t1868->len : 0u;
                    for (uint32_t _t1869 = 0; _t1869 < _len__t1869; ++_t1869) {
                        gd::GdVal lv_item = _t1868->data[_t1869];
                        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_buffSpeed, gd::get_index(gd_ctx, this->f_lightningMultiplicity, lv_item))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
                        (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_zapItem_2493, _ca, 1); })();
                    }
                }
            }
            (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1684, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1683, _ca, 1); })();
            this->f_curHitCount = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::fn_zapItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_chargeReceived_322, _ca, 1); })();
    if (gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_hasOnChargeReceivedEffect_63))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(4.0), gd::GdVal::from_float(4.02)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), gd::SYM_randf_range, _ca, 2); })();
        gd::GdVal lv_targetPos = gd::call_method(gd_ctx, lv_item, SYM_GEN_getGlobalCenter_780, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::fn_onBuffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    {
        gd::GdVal _t1870 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Lightning_2611)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, _ca, 1); })());
        gd::GdArr* _t1871 = (_t1870.kind == gd::GdVal::Kind::Arr) ? _t1870.arr : nullptr;
        uint32_t _len__t1872 = _t1871 ? _t1871->len : 0u;
        for (uint32_t _t1872 = 0; _t1872 < _len__t1872; ++_t1872) {
            gd::GdVal lv_item = _t1871->data[_t1872];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_buffSpeed, gd::get_index(gd_ctx, this->f_lightningMultiplicity, lv_item))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_272, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_chargeLeft_323, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chargeActive = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_active = gd::gd_coerce_bool(lv_chargeActive);
    if (gd::gd_truth(lv_chargeActive)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1873 = lv_forDirection;
        if (gd::gd_eq(_t1873, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
        else if (gd::gd_eq(_t1873, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
        else if (gd::gd_eq(_t1873, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::gd_eq(_t1873, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_numHits = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "hits", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_buffSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BuffTimer", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBuffEnded", 11u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_133, _ca, 3); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ThunderDrake(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ThunderDrake>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ThunderDrake = {CLS_Gd__gd_core_items__Exclusive__ThunderDrake, "ThunderDrake", "res://gd_core_items/Exclusive/ThunderDrake.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__ThunderDrake, &Gd__gd_core_items__Exclusive__ThunderDrake::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ThunderDrake::call_static_fn};

void Gd__gd_core_items__Exclusive__Wand::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_buffs = gd::GdVal::null();
    this->f_manaNeeded = gd::GdVal::null();
    this->f_luckNeeded = gd::GdVal::null();
    this->f_regenNeeded = gd::GdVal::null();
    this->f_empower = gd::GdVal::null();
    this->f_buffsToUse = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Wand::meta() const { return &META_Gd__gd_core_items__Exclusive__Wand; }
gd::GdVal Gd__gd_core_items__Exclusive__Wand::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Wand::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Wand::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_buffs_1044: out = this->f_buffs; return true;
        case SYM_GEN_manaNeeded_1785: out = this->f_manaNeeded; return true;
        case SYM_GEN_luckNeeded_1778: out = this->f_luckNeeded; return true;
        case SYM_GEN_regenNeeded_938: out = this->f_regenNeeded; return true;
        case SYM_GEN_empower_994: out = this->f_empower; return true;
        case SYM_GEN_buffsToUse_2350: out = this->f_buffsToUse; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Wand::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffs_1044: this->f_buffs = val; return true;
        case SYM_GEN_manaNeeded_1785: this->f_manaNeeded = val; return true;
        case SYM_GEN_luckNeeded_1778: this->f_luckNeeded = val; return true;
        case SYM_GEN_regenNeeded_938: this->f_regenNeeded = val; return true;
        case SYM_GEN_empower_994: this->f_empower = val; return true;
        case SYM_GEN_buffsToUse_2350: this->f_buffsToUse = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Wand::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Wand::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Wand::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Wand::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::null(), this->f_buffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLeastBuffs_364, _ca, 4); })();
    gd::GdVal lv_mana = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getMana_1224, nullptr, 0);
    gd::GdVal lv_luck = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getLucky_1217, nullptr, 0);
    gd::GdVal lv_regen = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getRegeneration_1213, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_mana, this->f_manaNeeded))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_luck, this->f_luckNeeded)))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_regen, this->f_regenNeeded))))))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_buffsToUse, gd::GdVal::null(), gd::GdVal::from_bool(true), this->f_buffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeMostBuffs_366, _ca, 4); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_empower, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wand::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_buffs = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Mana_2570), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Lucky_2569), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Regeneration_2568)}));
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "manat", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luckt", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_regenNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regent", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_buffsToUse = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "use", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Wand(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Wand>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Wand = {CLS_Gd__gd_core_items__Exclusive__Wand, "Wand", "res://gd_core_items/Exclusive/Wand.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Wand, &Gd__gd_core_items__Exclusive__Wand::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Wand::call_static_fn};

void Gd__gd_core_items__FlyAgaric::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__FlyAgaric::meta() const { return &META_Gd__gd_core_items__FlyAgaric; }
gd::GdVal Gd__gd_core_items__FlyAgaric::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__FlyAgaric::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__FlyAgaric::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__FlyAgaric::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__FlyAgaric::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__FlyAgaric::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__FlyAgaric::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__FlyAgaric::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_209, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__FlyAgaric::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__FlyAgaric(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__FlyAgaric>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__FlyAgaric = {CLS_Gd__gd_core_items__FlyAgaric, "FlyAgaric", "res://gd_core_items/FlyAgaric.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__FlyAgaric, &Gd__gd_core_items__FlyAgaric::get_static_prop_fn, &Gd__gd_core_items__FlyAgaric::call_static_fn};

void Gd__gd_core_items__HeroicPotion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Potion::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__HeroicPotion::meta() const { return &META_Gd__gd_core_items__HeroicPotion; }
gd::GdVal Gd__gd_core_items__HeroicPotion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Potion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__HeroicPotion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__HeroicPotion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Potion::get_prop(prop, out);
}
bool Gd__gd_core_items__HeroicPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__HeroicPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1753: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_checkStamina_1797: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::has_own_method(m);
}
bool Gd__gd_core_items__HeroicPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1753: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_checkStamina_1797: out = fn_checkStamina(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__HeroicPotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Potion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__HeroicPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_316, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeroicPotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_pre_use_stamina", 25u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkStamina", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeroicPotion::fn_checkStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_919, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getCurrentStamina_1242, nullptr, 0), lv_amount)))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1752, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeroicPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Potion::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__HeroicPotion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__HeroicPotion>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__HeroicPotion = {CLS_Gd__gd_core_items__HeroicPotion, "HeroicPotion", "res://gd_core_items/HeroicPotion.gd", &META_Gd__gd_core_items__Potion, true, _alloc_Gd__gd_core_items__HeroicPotion, &Gd__gd_core_items__HeroicPotion::get_static_prop_fn, &Gd__gd_core_items__HeroicPotion::call_static_fn};

void Gd__gd_core_items__ManaOrb::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_stackTypes = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_activated = gd::GdVal::from_bool(false);
    this->f_bonusBuffs = gd::GdVal::from_int(0);
    this->f_mana = gd::GdVal::null();
    this->f_manaNeeded = gd::GdVal::from_int(0);
    this->f_buffs = gd::GdVal::null();
    this->f_light = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__ManaOrb::meta() const { return &META_Gd__gd_core_items__ManaOrb; }
gd::GdVal Gd__gd_core_items__ManaOrb::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__ManaOrb::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__ManaOrb::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_stackTypes_1830: out = this->f_stackTypes; return true;
        case SYM_GEN_activated_1292: out = this->f_activated; return true;
        case SYM_GEN_bonusBuffs_1831: out = this->f_bonusBuffs; return true;
        case SYM_GEN_mana_1832: out = this->f_mana; return true;
        case SYM_GEN_manaNeeded_1785: out = this->f_manaNeeded; return true;
        case SYM_GEN_buffs_1044: out = this->f_buffs; return true;
        case SYM_GEN_light_945: out = this->f_light; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__ManaOrb::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stackTypes_1830: this->f_stackTypes = val; return true;
        case SYM_GEN_activated_1292: this->f_activated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_bonusBuffs_1831: this->f_bonusBuffs = gd::gd_coerce_int(val); return true;
        case SYM_GEN_mana_1832: this->f_mana = val; return true;
        case SYM_GEN_manaNeeded_1785: this->f_manaNeeded = gd::gd_coerce_int(val); return true;
        case SYM_GEN_buffs_1044: this->f_buffs = val; return true;
        case SYM_GEN_light_945: this->f_light = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__ManaOrb::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onItemActivated_934: return true;
        case SYM_GEN_onManaChanged_1833: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_addBonusRandomBuffs_1834: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__ManaOrb::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemActivated_934: out = fn_onItemActivated(args, argc); return true;
        case SYM_GEN_onManaChanged_1833: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_addBonusRandomBuffs_1834: out = fn_addBonusRandomBuffs(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__ManaOrb::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__ManaOrb::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canActivate_89, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaOrb::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), SYM_GEN_oracle_trace_1631)) ? gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), SYM_GEN__stacktrace_1633))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv__cells = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsInInventory_412, nullptr, 0);
        gd::GdVal lv__hit = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u));
        {
            gd::GdVal _t1874 = gd::gd_iter_seq(gd_ctx.arena, lv__cells);
            gd::GdArr* _t1875 = (_t1874.kind == gd::GdVal::Kind::Arr) ? _t1874.arr : nullptr;
            uint32_t _len__t1876 = _t1875 ? _t1875->len : 0u;
            for (uint32_t _t1876 = 0; _t1876 < _len__t1876; ++_t1876) {
                gd::GdVal lv__c = _t1875->data[_t1876];
                gd::GdVal lv__it = ([&]() { gd::GdVal _ca[] = {lv__c}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getOwnOrPlayerInventory_398, nullptr, 0), SYM_GEN_getItemInCell_1514, _ca, 1); })();
                lv__hit = gd::gd_add(gd_ctx, lv__hit, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "[", 1u)), ([&]() { gd::GdVal _ca[] = {lv__c}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "=", 1u))), (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__it, gd::GdVal::null()))) ? (gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "null", 4u))) : (gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv__it, SYM_GEN_descriptor_2), SYM_GEN_identifier_1575))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "/ot", 3u))), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(gd::get_prop(gd_ctx, lv__it, SYM_GEN_ownerType_47))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " p", 2u))), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(gd::get_prop(gd_ctx, lv__it, SYM_GEN_placed_6))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "]", 1u))));
            }
        }
        gd::GdVal lv__aff = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0);
        gd::GdVal lv__aff_names = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u));
        {
            gd::GdVal _t1877 = gd::gd_iter_seq(gd_ctx.arena, lv__aff);
            gd::GdArr* _t1878 = (_t1877.kind == gd::GdVal::Kind::Arr) ? _t1877.arr : nullptr;
            uint32_t _len__t1879 = _t1878 ? _t1878->len : 0u;
            for (uint32_t _t1879 = 0; _t1879 < _len__t1879; ++_t1879) {
                gd::GdVal lv__a = _t1878->data[_t1879];
                lv__aff_names = gd::gd_add(gd_ctx, lv__aff_names, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv__a, SYM_GEN_descriptor_2), SYM_GEN_identifier_1575))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, ",", 1u))));
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "AFFL", 4u)), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1575))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "/ot", 3u))), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(this->f_ownerType)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), ([&]() { gd::GdVal _ca[] = {lv__cells}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, lv__hit, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " aff=", 5u))), lv__aff_names)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), SYM_GEN_trace_diag_1643, _ca, 4); })();
    }
    this->f_bonusBuffs = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    {
        gd::GdVal _t1880 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1881 = (_t1880.kind == gd::GdVal::Kind::Arr) ? _t1880.arr : nullptr;
        uint32_t _len__t1882 = _t1881 ? _t1881->len : 0u;
        for (uint32_t _t1882 = 0; _t1882 < _len__t1882; ++_t1882) {
            gd::GdVal lv_item = _t1881->data[_t1882];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onItemActivated", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_mana_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onManaChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaOrb::fn_onItemActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaOrb::fn_onManaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getMana_1224, nullptr, 0), this->f_manaNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_330, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_buffs, this->f_bonusBuffs), lv_event, this->f_stackTypes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_367, _ca, 3); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaOrb::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaOrb::fn_addBonusRandomBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    this->f_bonusBuffs = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_bonusBuffs, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaOrb::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__activated = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__activated = gd::gd_coerce_bool(lv__activated);
    this->f_activated = gd::gd_coerce_bool(lv__activated);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaOrb::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_mana = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0));
    this->f_manaNeeded = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0));
    this->f_buffs = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0));
    this->f_stackTypes = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1357, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Mana_2570)}; return gd::call_method(gd_ctx, this->f_stackTypes, gd::SYM_erase, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__ManaOrb(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__ManaOrb>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__ManaOrb = {CLS_Gd__gd_core_items__ManaOrb, "ManaOrb", "res://gd_core_items/ManaOrb.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__ManaOrb, &Gd__gd_core_items__ManaOrb::get_static_prop_fn, &Gd__gd_core_items__ManaOrb::call_static_fn};

void Gd__gd_core_items__ProtectivePurse::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bag::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__ProtectivePurse::meta() const { return &META_Gd__gd_core_items__ProtectivePurse; }
gd::GdVal Gd__gd_core_items__ProtectivePurse::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__ProtectivePurse::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__ProtectivePurse::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__ProtectivePurse::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__ProtectivePurse::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__ProtectivePurse::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__ProtectivePurse::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__ProtectivePurse::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_totalBlock = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_202, nullptr, 0);
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Bagtacular", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isTypeInInventory_801, _ca, 1); })())) {
        lv_totalBlock = gd::gd_add(gd_ctx, lv_totalBlock, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "block", 5u))}; return gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Bagtacular", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })(), SYM_GEN_getP_186, _ca, 1); })());
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_totalBlock}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ProtectivePurse::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__ProtectivePurse(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__ProtectivePurse>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__ProtectivePurse = {CLS_Gd__gd_core_items__ProtectivePurse, "ProtectivePurse", "res://gd_core_items/ProtectivePurse.gd", &META_Gd__gd_core_items__Bag, true, _alloc_Gd__gd_core_items__ProtectivePurse, &Gd__gd_core_items__ProtectivePurse::get_static_prop_fn, &Gd__gd_core_items__ProtectivePurse::call_static_fn};

void Gd__gd_core_items__StrongDemonicFlask::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Potion::init_fields(gd_ctx);
    this->f_healingReductionTimer = gd::GdVal::null();
    this->f_healingDebuff = gd::GdVal::null();
    this->f_damPerDebuff = gd::GdVal::null();
    this->f_playerHealthThreshold = gd::GdVal::null();
    this->f_opponentHealthThreshold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__StrongDemonicFlask::meta() const { return &META_Gd__gd_core_items__StrongDemonicFlask; }
gd::GdVal Gd__gd_core_items__StrongDemonicFlask::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Potion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__StrongDemonicFlask::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__StrongDemonicFlask::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_healingReductionTimer_1891: out = this->f_healingReductionTimer; return true;
        case SYM_GEN_healingDebuff_1892: out = this->f_healingDebuff; return true;
        case SYM_GEN_damPerDebuff_1731: out = this->f_damPerDebuff; return true;
        case SYM_GEN_playerHealthThreshold_1893: out = this->f_playerHealthThreshold; return true;
        case SYM_GEN_opponentHealthThreshold_1894: out = this->f_opponentHealthThreshold; return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::get_prop(prop, out);
}
bool Gd__gd_core_items__StrongDemonicFlask::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_healingReductionTimer_1891: this->f_healingReductionTimer = val; return true;
        case SYM_GEN_healingDebuff_1892: this->f_healingDebuff = val; return true;
        case SYM_GEN_damPerDebuff_1731: this->f_damPerDebuff = val; return true;
        case SYM_GEN_playerHealthThreshold_1893: this->f_playerHealthThreshold = val; return true;
        case SYM_GEN_opponentHealthThreshold_1894: this->f_opponentHealthThreshold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__StrongDemonicFlask::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canDamage_87: return true;
        case SYM_GEN_onTriggerPotion_1753: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onPlayerDamaged_1895: return true;
        case SYM_GEN_onOpponentDamaged_1896: return true;
        case SYM_GEN_drinkStrongDemonicFlask_1897: return true;
        case SYM_GEN_healingReductionTimeout_1898: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::has_own_method(m);
}
bool Gd__gd_core_items__StrongDemonicFlask::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canDamage_87: out = fn_canDamage(args, argc); return true;
        case SYM_GEN_onTriggerPotion_1753: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPlayerDamaged_1895: out = fn_onPlayerDamaged(args, argc); return true;
        case SYM_GEN_onOpponentDamaged_1896: out = fn_onOpponentDamaged(args, argc); return true;
        case SYM_GEN_drinkStrongDemonicFlask_1897: out = fn_drinkStrongDemonicFlask(args, argc); return true;
        case SYM_GEN_healingReductionTimeout_1898: out = fn_healingReductionTimeout(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__StrongDemonicFlask::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Potion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__StrongDemonicFlask::fn_canDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongDemonicFlask::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {this->f_healingDebuff}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_reduceHealingEfficiency_1163, _ca, 1); })();
    gd::GdVal lv_dam = gd::gd_mul(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_getDebuffStacks_1196, nullptr, 0), this->f_damPerDebuff);
    lv_dam = gd::gd_ceil(lv_dam);
    (void)([&]() { gd::GdVal _ca[] = {lv_dam, gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lifesteal", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), gd::GdVal::from_float(100.0)), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealLife_327, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_healingReductionTimer, SYM_GEN_start_1683, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongDemonicFlask::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onPlayerDamaged", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentDamaged", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongDemonicFlask::fn_onPlayerDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_healthChange = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_919, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getRelativeHealth_300, nullptr, 0), this->f_playerHealthThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drinkStrongDemonicFlask_1897, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongDemonicFlask::fn_onOpponentDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_healthChange = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_919, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_getRelativeHealth_300, nullptr, 0), this->f_opponentHealthThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drinkStrongDemonicFlask_1897, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongDemonicFlask::fn_drinkStrongDemonicFlask(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__aff = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0);
    gd::GdVal lv__aff_names = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u));
    {
        gd::GdVal _t1883 = gd::gd_iter_seq(gd_ctx.arena, lv__aff);
        gd::GdArr* _t1884 = (_t1883.kind == gd::GdVal::Kind::Arr) ? _t1883.arr : nullptr;
        uint32_t _len__t1885 = _t1884 ? _t1884->len : 0u;
        for (uint32_t _t1885 = 0; _t1885 < _len__t1885; ++_t1885) {
            gd::GdVal lv__a = _t1884->data[_t1885];
            lv__aff_names = gd::gd_add(gd_ctx, lv__aff_names, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv__a, SYM_GEN_descriptor_2), SYM_GEN_identifier_1575))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, ",", 1u))));
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "AFFL", 4u)), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1575))), gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n=", 2u)), ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, lv__aff, gd::SYM_size, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), lv__aff_names}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), SYM_GEN_trace_diag_1643, _ca, 4); })();
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
gd::GdVal Gd__gd_core_items__StrongDemonicFlask::fn_healingReductionTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_healingDebuff}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_addHealingEfficiency_1162, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongDemonicFlask::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_healingReductionTimer, SYM_GEN_stop_1684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongDemonicFlask::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Potion::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_healingReductionTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "HealingReductionTimer", 21u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healingReductionTimeout", 23u)), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_133, _ca, 3); })();
    this->f_healingDebuff = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0), gd::GdVal::from_float(100.0));
    this->f_damPerDebuff = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_playerHealthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "ownhpt", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    this->f_opponentHealthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "opphpt", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__StrongDemonicFlask(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__StrongDemonicFlask>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__StrongDemonicFlask = {CLS_Gd__gd_core_items__StrongDemonicFlask, "StrongDemonicFlask", "res://gd_core_items/StrongDemonicFlask.gd", &META_Gd__gd_core_items__Potion, true, _alloc_Gd__gd_core_items__StrongDemonicFlask, &Gd__gd_core_items__StrongDemonicFlask::get_static_prop_fn, &Gd__gd_core_items__StrongDemonicFlask::call_static_fn};

void Gd__gd_core_items__WoodenSword::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__WoodenSword::meta() const { return &META_Gd__gd_core_items__WoodenSword; }
gd::GdVal Gd__gd_core_items__WoodenSword::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__WoodenSword::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__WoodenSword::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__WoodenSword::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__WoodenSword::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__WoodenSword::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__WoodenSword::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__WoodenSword::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_114, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1276), SYM_GEN_Sufficient_2603))))) {
        gd::GdVal lv_res = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_218, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__WoodenSword::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1457, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__WoodenSword(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__WoodenSword>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__WoodenSword = {CLS_Gd__gd_core_items__WoodenSword, "WoodenSword", "res://gd_core_items/WoodenSword.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__WoodenSword, &Gd__gd_core_items__WoodenSword::get_static_prop_fn, &Gd__gd_core_items__WoodenSword::call_static_fn};
