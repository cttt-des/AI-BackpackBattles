#include "../../native_inline_dispatch.hpp"
#include "../../native_scalar_equal.hpp"
#include "../../native_array_index.hpp"
#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core__BloodAmulet.hpp"
#include "../hdrs/Gd__gd_core__CarrotGoobert.hpp"
#include "../hdrs/Gd__gd_core__CoreHooks.hpp"
#include "../hdrs/Gd__gd_core__CursedHairComb.hpp"
#include "../hdrs/Gd__gd_core__FancyFencingRapier.hpp"
#include "../hdrs/Gd__gd_core__HeroSword.hpp"
#include "../hdrs/Gd__gd_core__MagicStaff.hpp"
#include "../hdrs/Gd__gd_core__PoisonBow.hpp"
#include "../hdrs/Gd__gd_core__Shovel.hpp"
#include "../hdrs/Gd__gd_core_items__PestilenceFlask.hpp"
#include "../hdrs/Gd__gd_core__Wolpertinger.hpp"
#include "../hdrs/Gd__gd_core_items__BloodGoobert.hpp"
#include "../hdrs/Gd__gd_core_items__CritwoodStaff.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__AcornAce.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ArcaneIntellect.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Bazooka.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BowlofTreats.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ChainWhip.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Chess__WhiteRook.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__CupcakeGoobert.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DragonKnight.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__EngineerBag2.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ForgingHammer.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__GoldCube.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__IceDragon.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__LightFlower.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ManaMastery.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__NullBlade.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PoisonShortbow.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Rope.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ShinyShell.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SpellScrollDark.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SteelDragon.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ThornShortbow.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__VampiricCollar.hpp"
#include "../hdrs/Gd__gd_core_items__FannyPack.hpp"
#include "../hdrs/Gd__gd_core_items__HeartContainer.hpp"
#include "../hdrs/Gd__gd_core_items__MagicStaff.hpp"
#include "../hdrs/Gd__gd_core_items__PotionBelt.hpp"
#include "../hdrs/Gd__gd_core_items__StoneHelm.hpp"
#include "../hdrs/Gd__gd_core_items__White_EyesBlueDragon.hpp"

namespace {
constexpr gd::GdStr battle_string_literals[] = {
    {"dur", 3u, 3509645056u},
    {"ParticleTimer", 13u, 758126900u},
    {"onParticleTimeout", 17u, 3801482653u},
    {"attacked", 8u, 3381721668u},
    {"onAffectedAttacked", 18u, 2827661201u},
    {"lifesteal_scaling", 17u, 610492256u},
    {"lifesteal", 9u, 1515578962u},
    {"luckt", 5u, 4061892428u},
    {"dam", 3u, 4031722721u},
    {"luck", 4u, 4145017712u},
    {"character_poison_changed", 24u, 65736246u},
    {"onOpponentPoisonChanged", 23u, 839266911u},
    {"Stone", 5u, 1842662042u},
    {"Garlic", 6u, 137760495u},
    {"Blueberries", 11u, 2219831599u},
    {"Lump of Coal", 12u, 3714852271u},
    {"Pocket Sand", 11u, 2798336099u},
    {"Chipped Ruby", 12u, 2897786156u},
    {"Chipped Sapphire", 16u, 1114960190u},
    {"Chipped Emerald", 15u, 3370259324u},
    {"Chipped Topaz", 13u, 3927784128u},
    {"Chipped Amethyst", 16u, 1827871523u},
    {"Healing Herbs", 13u, 4012018613u},
    {"Bag of Stones", 13u, 3970243028u},
    {"Walrus Tusk", 11u, 3833022644u},
    {"Whetstone", 9u, 3932146392u},
    {"Piggybank", 9u, 3591778217u},
    {"Pan", 3u, 3025858444u},
    {"Customer Card", 13u, 3033338573u},
    {"Gloves of Haste", 15u, 3287234075u},
    {"Dagger", 6u, 1838682075u},
    {"Protective Purse", 16u, 3560043597u},
    {"Flawed Ruby", 11u, 3343752746u},
    {"Flawed Sapphire", 15u, 2380345052u},
    {"Flawed Emerald", 14u, 2494623442u},
    {"Flawed Topaz", 12u, 3749698898u},
    {"Flawed Amethyst", 15u, 2305097573u},
    {"character_healed", 16u, 2989261042u},
    {"onOpponentHeal", 14u, 3525706027u},
    {"", 0u, 2166136261u},
    {",", 1u, 688690635u},
    {"AFFL", 4u, 292489516u},
    {"n=", 2u, 271970020u},
    {"onBuffChanged", 13u, 3423803215u},
    {"vampirism", 9u, 773404377u},
    {"CritBuffTimer", 13u, 700944069u},
    {"buffEnded", 9u, 3457903416u},
    {"onAddToInventory_deferred", 25u, 2321074728u},
    {"onRemoveFromInventory_deferred", 30u, 3375124494u},
    {"Acorn Collar", 12u, 982085103u},
    {"Magic Collar", 12u, 1893589725u},
    {"Holy Collar", 11u, 3589099080u},
    {"Vampiric Collar", 15u, 4172663655u},
    {"Critwood Staff", 14u, 1632557502u},
    {"stamina2", 8u, 2620452172u},
    {"speed", 5u, 2072037248u},
    {"character_lucky_changed", 23u, 2259242176u},
    {"onLuckChanged", 13u, 1398589215u},
    {"dur_stun", 8u, 1388942617u},
    {"dur_stunself", 12u, 1896133571u},
    {"heatt", 5u, 312156581u},
    {"max", 3u, 3617776409u},
    {"Rat", 3u, 2743707096u},
    {"Squirrel", 8u, 1290664062u},
    {"Hedgehog", 8u, 2199372732u},
    {"onOpponentBuffsChanged", 22u, 3002324355u},
    {"BuffTimer", 9u, 194754125u},
    {"buffs", 5u, 2149256365u},
    {"activated", 9u, 2866667388u},
    {"onItemActivated", 15u, 1109670618u},
    {"heal", 4u, 979982427u},
    {"advance", 7u, 667710333u},
    {"Cog", 3u, 1243110080u},
    {"character_empower_changed", 25u, 2356601027u},
    {"onEmpowerChanged", 16u, 1778241301u},
    {"character_damaged", 17u, 745527748u},
    {"onDamaged", 9u, 2303747743u},
    {"heal_regen", 10u, 1259722877u},
    {"healtht", 7u, 1555997217u},
    {"character_cold_changed", 22u, 3066049132u},
    {"onOpponentColdChanged", 21u, 3656074605u},
    {"cold", 4u, 3930381583u},
    {"coldt", 5u, 1164486817u},
    {"damfactor", 9u, 2846421882u},
    {"manat", 5u, 126091098u},
    {"debuffs", 7u, 504032524u},
    {"regen", 5u, 16724762u},
    {"mana", 4u, 3650585354u},
    {"Mana Orb", 8u, 293290099u},
    {"regent", 6u, 4290639402u},
    {"onTriggerItemActivated", 22u, 1568326382u},
    {"SpeedTimer", 10u, 767231377u},
    {"onSpeedTimeout", 14u, 200718086u},
    {"heal_bonus", 10u, 2830162243u},
    {"speed_dark", 10u, 3672873405u},
    {"reflect", 7u, 2462546090u},
    {"blockfactor", 11u, 4227576901u},
    {"character_vampirism_changed", 27u, 75150398u},
    {"onVampirismChanged", 18u, 3624660862u},
    {"character_attacked", 18u, 2439462988u},
    {"onOpponentAttacked", 18u, 21269012u},
    {"Bagtacular", 10u, 2131747329u},
    {"character_regeneration_changed", 30u, 2797934681u},
    {"onRegenChanged", 14u, 661197895u},
    {"maxhealth", 9u, 429334299u},
    {"potion_emptied", 14u, 70999789u},
    {"onPotionEmptied", 15u, 4255313949u},
};
}

void Gd__gd_core__BloodAmulet::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__BloodAmulet::meta() const { return &META_Gd__gd_core__BloodAmulet; }
gd::GdVal Gd__gd_core__BloodAmulet::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__BloodAmulet::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__BloodAmulet::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__BloodAmulet::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__BloodAmulet::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__BloodAmulet::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__BloodAmulet::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__BloodAmulet::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BloodAmulet::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__BloodAmulet(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__BloodAmulet>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__BloodAmulet = {CLS_Gd__gd_core__BloodAmulet, "BloodAmulet", "res://gd_core/BloodAmulet.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__BloodAmulet, &Gd__gd_core__BloodAmulet::get_static_prop_fn, &Gd__gd_core__BloodAmulet::call_static_fn};

void Gd__gd_core__CarrotGoobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Goobert::init_fields(gd_ctx);
    this->f_empower = gd::GdVal::null();
    this->f_particleTimer = gd::GdVal::null();
    this->f_activationParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__CarrotGoobert::meta() const { return &META_Gd__gd_core__CarrotGoobert; }
gd::GdVal Gd__gd_core__CarrotGoobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__CarrotGoobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CarrotGoobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        case SYM_GEN_particleTimer_999: out = this->f_particleTimer; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core__Goobert::get_prop(prop, out);
}
bool Gd__gd_core__CarrotGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        case SYM_GEN_particleTimer_999: this->f_particleTimer = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__CarrotGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN_onParticleTimeout_1000: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Goobert::has_own_method(m);
}
bool Gd__gd_core__CarrotGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onParticleTimeout_1000: out = fn_onParticleTimeout(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__CarrotGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__CarrotGoobert::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CarrotGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_356, _ca, 1); })();
    gd::GdVal lv_duration = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[0])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_int(106LL), this->f_empower, lv_duration}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacksTemporary_202, _ca, 4); })();
    (void)gd::native_inline_call(gd_ctx, this->f_particleTimer, SYM_GEN_stop_1780, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {lv_duration}; return gd::native_inline_call(gd_ctx, this->f_particleTimer, SYM_GEN_start_1779, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CarrotGoobert::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_particleTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CarrotGoobert::fn_onParticleTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CarrotGoobert::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CarrotGoobert::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv_active)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CarrotGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_empower = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0);
    this->f_particleTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[1]), gd::GdVal::from_str(&battle_string_literals[2]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CarrotGoobert(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CarrotGoobert>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__CarrotGoobert = {CLS_Gd__gd_core__CarrotGoobert, "CarrotGoobert", "res://gd_core/CarrotGoobert.gd", &META_Gd__gd_core__Goobert, false, _alloc_Gd__gd_core__CarrotGoobert, &Gd__gd_core__CarrotGoobert::get_static_prop_fn, &Gd__gd_core__CarrotGoobert::call_static_fn};

void Gd__gd_core__CoreHooks::init_fields(gd::BattleCtx& gd_ctx) {
}
const gd::GdClassMeta* Gd__gd_core__CoreHooks::meta() const { return &META_Gd__gd_core__CoreHooks; }
gd::GdVal Gd__gd_core__CoreHooks::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreHooks::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreHooks::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return false;
}
bool Gd__gd_core__CoreHooks::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return false;
}
bool Gd__gd_core__CoreHooks::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_showCooldown_794: return true;
        case SYM_GEN_showCooldownSmooth_793: return true;
        case SYM_GEN_resetZ_450: return true;
        case SYM_GEN_playActivationAnimation_778: return true;
        case SYM_GEN_playActivationSound_148: return true;
        case SYM_GEN_playDropSound_149: return true;
        case SYM_GEN_spawnLabel_379: return true;
        case SYM_GEN_queueTooltipUpdate_708: return true;
        case SYM_GEN_activateBuffCounter_1623: return true;
        case SYM_GEN_playOutOfStaminaAnimation_118: return true;
        case SYM_GEN_playStunAnimation_1624: return true;
        case SYM_GEN_playFatigueAnimation_1625: return true;
        case SYM_GEN_playFatigueSound_1626: return true;
        case SYM_GEN_playAttackAnimation_1139: return true;
        case SYM_GEN_playActivateAnimation_1142: return true;
        case SYM_GEN_playAffectedPlacedAnimation_663: return true;
        case SYM_GEN_playWinLoseAnimation_1627: return true;
        case SYM_GEN_onClassChanged_1628: return true;
        case SYM_GEN_playBattleRageAnimation_1209: return true;
        case SYM_GEN_playInvulnerableAnimation_1629: return true;
        case SYM_GEN_onItemRotated_1630: return true;
        case SYM_GEN_previewCellCollision_471: return true;
        case SYM_GEN_previewCells_472: return true;
        case SYM_GEN_previewCanAffect_473: return true;
        case SYM_GEN_spawnLabel_character_1631: return true;
        case SYM_GEN_spawnReflectLabel_1632: return true;
        case SYM_GEN_spawnResistedLabel_1633: return true;
        case SYM_GEN_spawnProtectedLabel_1634: return true;
        case SYM_GEN_spawnBuffLabel_item_1635: return true;
        case SYM_GEN_spawnBuffLabel_1636: return true;
        case SYM_GEN_spawnNumberLabel_1637: return true;
        case SYM_GEN_spawnMissLabel_1638: return true;
        case SYM_GEN_damageAnimation_1639: return true;
        case SYM_GEN_playCharacterSound_1640: return true;
        case SYM_GEN_onHealthChangedUI_1641: return true;
        case SYM_GEN_onMaxStaminaChangedUI_1642: return true;
        case SYM_GEN_spawnLabelOnItem_1643: return true;
        case SYM_GEN_onItemTypeChanged_458: return true;
        case SYM_GEN_sendCharge_320: return true;
        case SYM_GEN_applyImpulse_1644: return true;
        case SYM_GEN_addMetric_230: return true;
        case SYM_GEN_snapshotItemTooltipStat_1384: return true;
        case SYM_GEN_snapshotItemState_1385: return true;
        case SYM_GEN_snapshotItemMetric_1383: return true;
        case SYM_GEN_snapshotCharacterStat_1387: return true;
        case SYM_GEN_snapshotStack_1388: return true;
        case SYM_GEN_snapshotDamageDealt_1645: return true;
        case SYM_GEN_snapshotGlobalStat_1386: return true;
        case SYM_GEN_snapshotMetric_1382: return true;
        case SYM_GEN_updateDamageMeter_1646: return true;
        case SYM_GEN_logEvent_1357: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreHooks::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_showCooldown_794: out = fn_showCooldown(args, argc); return true;
        case SYM_GEN_showCooldownSmooth_793: out = fn_showCooldownSmooth(args, argc); return true;
        case SYM_GEN_resetZ_450: out = fn_resetZ(args, argc); return true;
        case SYM_GEN_playActivationAnimation_778: out = fn_playActivationAnimation(args, argc); return true;
        case SYM_GEN_playActivationSound_148: out = fn_playActivationSound(args, argc); return true;
        case SYM_GEN_playDropSound_149: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN_spawnLabel_379: out = fn_spawnLabel(args, argc); return true;
        case SYM_GEN_queueTooltipUpdate_708: out = fn_queueTooltipUpdate(args, argc); return true;
        case SYM_GEN_activateBuffCounter_1623: out = fn_activateBuffCounter(args, argc); return true;
        case SYM_GEN_playOutOfStaminaAnimation_118: out = fn_playOutOfStaminaAnimation(args, argc); return true;
        case SYM_GEN_playStunAnimation_1624: out = fn_playStunAnimation(args, argc); return true;
        case SYM_GEN_playFatigueAnimation_1625: out = fn_playFatigueAnimation(args, argc); return true;
        case SYM_GEN_playFatigueSound_1626: out = fn_playFatigueSound(args, argc); return true;
        case SYM_GEN_playAttackAnimation_1139: out = fn_playAttackAnimation(args, argc); return true;
        case SYM_GEN_playActivateAnimation_1142: out = fn_playActivateAnimation(args, argc); return true;
        case SYM_GEN_playAffectedPlacedAnimation_663: out = fn_playAffectedPlacedAnimation(args, argc); return true;
        case SYM_GEN_playWinLoseAnimation_1627: out = fn_playWinLoseAnimation(args, argc); return true;
        case SYM_GEN_onClassChanged_1628: out = fn_onClassChanged(args, argc); return true;
        case SYM_GEN_playBattleRageAnimation_1209: out = fn_playBattleRageAnimation(args, argc); return true;
        case SYM_GEN_playInvulnerableAnimation_1629: out = fn_playInvulnerableAnimation(args, argc); return true;
        case SYM_GEN_onItemRotated_1630: out = fn_onItemRotated(args, argc); return true;
        case SYM_GEN_previewCellCollision_471: out = fn_previewCellCollision(args, argc); return true;
        case SYM_GEN_previewCells_472: out = fn_previewCells(args, argc); return true;
        case SYM_GEN_previewCanAffect_473: out = fn_previewCanAffect(args, argc); return true;
        case SYM_GEN_spawnLabel_character_1631: out = fn_spawnLabel_character(args, argc); return true;
        case SYM_GEN_spawnReflectLabel_1632: out = fn_spawnReflectLabel(args, argc); return true;
        case SYM_GEN_spawnResistedLabel_1633: out = fn_spawnResistedLabel(args, argc); return true;
        case SYM_GEN_spawnProtectedLabel_1634: out = fn_spawnProtectedLabel(args, argc); return true;
        case SYM_GEN_spawnBuffLabel_item_1635: out = fn_spawnBuffLabel_item(args, argc); return true;
        case SYM_GEN_spawnBuffLabel_1636: out = fn_spawnBuffLabel(args, argc); return true;
        case SYM_GEN_spawnNumberLabel_1637: out = fn_spawnNumberLabel(args, argc); return true;
        case SYM_GEN_spawnMissLabel_1638: out = fn_spawnMissLabel(args, argc); return true;
        case SYM_GEN_damageAnimation_1639: out = fn_damageAnimation(args, argc); return true;
        case SYM_GEN_playCharacterSound_1640: out = fn_playCharacterSound(args, argc); return true;
        case SYM_GEN_onHealthChangedUI_1641: out = fn_onHealthChangedUI(args, argc); return true;
        case SYM_GEN_onMaxStaminaChangedUI_1642: out = fn_onMaxStaminaChangedUI(args, argc); return true;
        case SYM_GEN_spawnLabelOnItem_1643: out = fn_spawnLabelOnItem(args, argc); return true;
        case SYM_GEN_onItemTypeChanged_458: out = fn_onItemTypeChanged(args, argc); return true;
        case SYM_GEN_sendCharge_320: out = fn_sendCharge(args, argc); return true;
        case SYM_GEN_applyImpulse_1644: out = fn_applyImpulse(args, argc); return true;
        case SYM_GEN_addMetric_230: out = fn_addMetric(args, argc); return true;
        case SYM_GEN_snapshotItemTooltipStat_1384: out = fn_snapshotItemTooltipStat(args, argc); return true;
        case SYM_GEN_snapshotItemState_1385: out = fn_snapshotItemState(args, argc); return true;
        case SYM_GEN_snapshotItemMetric_1383: out = fn_snapshotItemMetric(args, argc); return true;
        case SYM_GEN_snapshotCharacterStat_1387: out = fn_snapshotCharacterStat(args, argc); return true;
        case SYM_GEN_snapshotStack_1388: out = fn_snapshotStack(args, argc); return true;
        case SYM_GEN_snapshotDamageDealt_1645: out = fn_snapshotDamageDealt(args, argc); return true;
        case SYM_GEN_snapshotGlobalStat_1386: out = fn_snapshotGlobalStat(args, argc); return true;
        case SYM_GEN_snapshotMetric_1382: out = fn_snapshotMetric(args, argc); return true;
        case SYM_GEN_updateDamageMeter_1646: out = fn_updateDamageMeter(args, argc); return true;
        case SYM_GEN_logEvent_1357: out = fn_logEvent(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreHooks::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core__CoreHooks::fn_showCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_progress = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_progress = gd::gd_coerce_float(lv_progress);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_showCooldownSmooth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_progress = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_progress = gd::gd_coerce_float(lv_progress);
    gd::GdVal lv_fill = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    lv_fill = gd::gd_coerce_bool(lv_fill);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_resetZ(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_playActivationAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_aniType = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_consume = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_consume = gd::gd_coerce_bool(lv_consume);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_playActivationSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_volume = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_spawnLabel(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_type = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_damage = (_argc > 2) ? _args[2] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_queueTooltipUpdate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_activateBuffCounter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_type = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_playOutOfStaminaAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_playStunAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_playFatigueAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_name = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_playFatigueSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_playAttackAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_distance = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_playActivateAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_playAffectedPlacedAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_newItemIsAffected = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_playWinLoseAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_isWin = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_isWin = gd::gd_coerce_bool(lv_isWin);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_onClassChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_classResource = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_playBattleRageAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_rageStart = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_rageStart = gd::gd_coerce_bool(lv_rageStart);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_playInvulnerableAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_invu = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_invu = gd::gd_coerce_bool(lv_invu);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_onItemRotated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_previewCellCollision(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_previewCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_previewCanAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_spawnLabel_character(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_type = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_damage = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_spawnReflectLabel(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_reflected = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_spawnResistedLabel(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_resisted = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_spawnProtectedLabel(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_protected = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_spawnBuffLabel_item(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_appliedToOpponent = (_argc > 3) ? _args[3] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_spawnBuffLabel(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_pos = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_spawnNumberLabel(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_pos = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_direction = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_damage = (_argc > 3) ? _args[3] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_spawnMissLabel(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_pos = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_direction = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_damageAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_kind = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_speed = (_argc > 2) ? _args[2] : (gd::GdVal::from_float(1.0));
    lv_speed = gd::gd_coerce_float(lv_speed);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_playCharacterSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_stream = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_volume = (_argc > 2) ? _args[2] : (gd::GdVal::from_int(0LL));
    gd::GdVal lv_pitch = (_argc > 3) ? _args[3] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_force = (_argc > 4) ? _args[4] : (gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_onHealthChangedUI(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_onMaxStaminaChangedUI(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_spawnLabelOnItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 2) ? _args[2] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_onItemTypeChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_sendCharge(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 3) ? _args[3] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_applyImpulse(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_offset = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_impulse = (_argc > 2) ? _args[2] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_addMetric(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_metricIndex = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_metricIndex = gd::gd_coerce_int(lv_metricIndex);
    gd::GdVal lv_amount = (_argc > 2) ? _args[2] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_snapshotItemTooltipStat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_statType = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_withNextEvent = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(false));
    gd::GdVal lv_event = (_argc > 4) ? _args[4] : (gd::GdVal::null());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_snapshotItemState(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_state = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_withNextEvent = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_withNextEvent = gd::gd_coerce_bool(lv_withNextEvent);
    gd::GdVal lv_event = (_argc > 3) ? _args[3] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_snapshotItemMetric(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_metricIndex = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_metricIndex = gd::gd_coerce_int(lv_metricIndex);
    gd::GdVal lv_playerId = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_withNextEvent = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_snapshotCharacterStat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_statType = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_withNextEvent = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    lv_withNextEvent = gd::gd_coerce_bool(lv_withNextEvent);
    gd::GdVal lv_event = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_snapshotStack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_type = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_snapshotDamageDealt(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_playerId = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_type = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_damage = (_argc > 2) ? _args[2] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_snapshotGlobalStat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stat = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_stat = gd::gd_coerce_int(lv_stat);
    gd::GdVal lv_newValue = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_snapshotMetric(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_playerId = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_metric = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_eventType = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 3) ? _args[3] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_updateDamageMeter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_playerId = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreHooks::fn_logEvent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreHooks(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreHooks>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__CoreHooks = {CLS_Gd__gd_core__CoreHooks, "CoreHooks", "res://gd_core/CoreHooks.gd", nullptr, false, _alloc_Gd__gd_core__CoreHooks, &Gd__gd_core__CoreHooks::get_static_prop_fn, &Gd__gd_core__CoreHooks::call_static_fn};

void Gd__gd_core__CursedHairComb::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__CursedHairComb::meta() const { return &META_Gd__gd_core__CursedHairComb; }
gd::GdVal Gd__gd_core__CursedHairComb::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__CursedHairComb::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CursedHairComb::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__CursedHairComb::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__CursedHairComb::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onAffectedAttacked_1824: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__CursedHairComb::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onAffectedAttacked_1824: out = fn_onAffectedAttacked(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__CursedHairComb::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__CursedHairComb::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CursedHairComb::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(24LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CursedHairComb::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_addHealingEfficiency_1182, _ca, 1); })();
    {
        gd::GdVal _t1824 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1825 = (_t1824.kind == gd::GdVal::Kind::Arr) ? _t1824.arr : nullptr;
        uint32_t _len__t1826 = _t1825 ? _t1825->len : 0u;
        for (uint32_t _t1826 = 0; _t1826 < _len__t1826; ++_t1826) {
            gd::GdVal lv_weapon = _t1825->data[_t1826];
            (void)([&]() { gd::GdVal _ca[] = {lv_weapon, gd::GdVal::from_str(&battle_string_literals[3]), gd::GdVal::from_str(&battle_string_literals[4])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CursedHairComb::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CursedHairComb::fn_onAffectedAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        gd::GdVal lv_bonusLifesteal = gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[5])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })());
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_ceil(gd::gd_div(gd_ctx, gd::gd_mul(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), lv_bonusLifesteal)), gd::GdVal::from_float(100.0))), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CursedHairComb::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CursedHairComb(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CursedHairComb>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__CursedHairComb = {CLS_Gd__gd_core__CursedHairComb, "CursedHairComb", "res://gd_core/CursedHairComb.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__CursedHairComb, &Gd__gd_core__CursedHairComb::get_static_prop_fn, &Gd__gd_core__CursedHairComb::call_static_fn};

void Gd__gd_core__FancyFencingRapier::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
    this->f_luckNeeded = gd::GdVal::null();
    this->f_bonusDam = gd::GdVal::null();
    this->f_luck = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__FancyFencingRapier::meta() const { return &META_Gd__gd_core__FancyFencingRapier; }
gd::GdVal Gd__gd_core__FancyFencingRapier::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__FancyFencingRapier::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__FancyFencingRapier::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_luckNeeded_1874: out = this->f_luckNeeded; return true;
        case SYM_GEN_bonusDam_1875: out = this->f_bonusDam; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__FancyFencingRapier::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_luckNeeded_1874: this->f_luckNeeded = val; return true;
        case SYM_GEN_bonusDam_1875: this->f_bonusDam = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__FancyFencingRapier::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__FancyFencingRapier::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__FancyFencingRapier::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__FancyFencingRapier::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_luckNeeded, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseLucky_347, _ca, 2); })())) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusDam}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
        }
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__FancyFencingRapier::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_bonusDam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[8])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[9])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__FancyFencingRapier(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__FancyFencingRapier>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__FancyFencingRapier = {CLS_Gd__gd_core__FancyFencingRapier, "FancyFencingRapier", "res://gd_core/FancyFencingRapier.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__FancyFencingRapier, &Gd__gd_core__FancyFencingRapier::get_static_prop_fn, &Gd__gd_core__FancyFencingRapier::call_static_fn};

void Gd__gd_core__HeroSword::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__HeroSword::meta() const { return &META_Gd__gd_core__HeroSword; }
gd::GdVal Gd__gd_core__HeroSword::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__HeroSword::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__HeroSword::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__HeroSword::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__HeroSword::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__HeroSword::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__HeroSword::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__HeroSword::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeroSword::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1827 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1828 = (_t1827.kind == gd::GdVal::Kind::Arr) ? _t1827.arr : nullptr;
        uint32_t _len__t1829 = _t1828 ? _t1828->len : 0u;
        for (uint32_t _t1829 = 0; _t1829 < _len__t1829; ++_t1829) {
            gd::GdVal lv_item = _t1828->data[_t1829];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false), gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, Gd__gd_core__HeroSword::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Jump_2736)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeroSword::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__HeroSword(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__HeroSword>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__HeroSword = {CLS_Gd__gd_core__HeroSword, "HeroSword", "res://gd_core/HeroSword.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__HeroSword, &Gd__gd_core__HeroSword::get_static_prop_fn, &Gd__gd_core__HeroSword::call_static_fn};

void Gd__gd_core__MagicStaff::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
    this->f_manaCost = gd::GdVal::null();
    this->f_tempDamBonus = gd::GdVal::null();
    this->f_permDamBonus = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__MagicStaff::meta() const { return &META_Gd__gd_core__MagicStaff; }
gd::GdVal Gd__gd_core__MagicStaff::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__MagicStaff::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__MagicStaff::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_manaCost_1815: out = this->f_manaCost; return true;
        case SYM_GEN_tempDamBonus_1816: out = this->f_tempDamBonus; return true;
        case SYM_GEN_permDamBonus_997: out = this->f_permDamBonus; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__MagicStaff::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaCost_1815: this->f_manaCost = val; return true;
        case SYM_GEN_tempDamBonus_1816: this->f_tempDamBonus = val; return true;
        case SYM_GEN_permDamBonus_997: this->f_permDamBonus = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__MagicStaff::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__MagicStaff::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__MagicStaff::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__MagicStaff::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_333, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_event, gd::GdVal::null())))) {
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), this->f_tempDamBonus));
        (void)([&]() { gd::GdVal _ca[] = {this->f_permDamBonus}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MagicStaff::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_manaCost = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0);
    this->f_tempDamBonus = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0);
    this->f_permDamBonus = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__MagicStaff(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__MagicStaff>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__MagicStaff = {CLS_Gd__gd_core__MagicStaff, "MagicStaff", "res://gd_core/MagicStaff.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__MagicStaff, &Gd__gd_core__MagicStaff::get_static_prop_fn, &Gd__gd_core__MagicStaff::call_static_fn};

void Gd__gd_core__PoisonBow::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Bow::init_fields(gd_ctx);
    this->f_damageAcc = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_damagePerPoison = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core__PoisonBow::meta() const { return &META_Gd__gd_core__PoisonBow; }
gd::GdVal Gd__gd_core__PoisonBow::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Bow::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__PoisonBow::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__PoisonBow::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_damageAcc_1960: out = this->f_damageAcc; return true;
        case SYM_GEN_damagePerPoison_1961: out = this->f_damagePerPoison; return true;
        default: break;
    }
    return Gd__gd_core__Bow::get_prop(prop, out);
}
bool Gd__gd_core__PoisonBow::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damageAcc_1960: this->f_damageAcc = gd::gd_coerce_int(val); return true;
        case SYM_GEN_damagePerPoison_1961: this->f_damagePerPoison = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core__Bow::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__PoisonBow::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_hasAttackEffect_295: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onWeaponAttacked_950: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onOpponentPoisonChanged_1831: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Bow::has_own_method(m);
}
bool Gd__gd_core__PoisonBow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_hasAttackEffect_295: out = fn_hasAttackEffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_950: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onOpponentPoisonChanged_1831: out = fn_onOpponentPoisonChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Bow::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__PoisonBow::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Bow::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__PoisonBow::fn_hasAttackEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PoisonBow::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[10]), gd::GdVal::from_str(&battle_string_literals[11])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    this->f_damageAcc = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PoisonBow::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        gd::GdVal lv_attackEffectCount = gd::gd_add(gd_ctx, gd::GdVal::from_int(1LL), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollDoubleAttackEffect_187, nullptr, 0));
        {
            gd::GdVal _t1830 = gd::gd_iter_seq(gd_ctx.arena, lv_attackEffectCount);
            gd::GdArr* _t1831 = (_t1830.kind == gd::GdVal::Kind::Arr) ? _t1830.arr : nullptr;
            uint32_t _len__t1832 = _t1831 ? _t1831->len : 0u;
            for (uint32_t _t1832 = 0; _t1832 < _len__t1832; ++_t1832) {
                gd::GdVal lv_i = _t1831->data[_t1832];
                this->f_damageAcc = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_damageAcc, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518)));
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {this->f_damageAcc, gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PoisonBow::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_poisonStacks = gd::gd_div(gd_ctx, this->f_damageAcc, this->f_damagePerPoison);
        gd::GdVal lv_poisonEvent = ([&]() { gd::GdVal _ca[] = {lv_poisonStacks}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 1); })();
        this->f_damageAcc = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_damageAcc, this->f_damagePerPoison));
        (void)([&]() { gd::GdVal _ca[] = {this->f_damageAcc, gd::GdVal::from_bool(false), lv_poisonEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 3); })();
        gd::GdVal lv_res = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_220, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PoisonBow::fn_onOpponentPoisonChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_162, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PoisonBow::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PoisonBow::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damageAcc = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv__damageAcc, this->f_damagePerPoison)))) {
    }
    else {
        gd::GdVal lv_poisonStacks = gd::gd_div(gd_ctx, lv__damageAcc, this->f_damagePerPoison);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PoisonBow::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bow::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_damagePerPoison = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__PoisonBow(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__PoisonBow>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__PoisonBow = {CLS_Gd__gd_core__PoisonBow, "PoisonBow", "res://gd_core/PoisonBow.gd", &META_Gd__gd_core__Bow, false, _alloc_Gd__gd_core__PoisonBow, &Gd__gd_core__PoisonBow::get_static_prop_fn, &Gd__gd_core__PoisonBow::call_static_fn};

void Gd__gd_core__Shovel::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
    this->f_digUpItems = ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 25); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[12]), gd::GdVal::from_int(4LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[13]), gd::GdVal::from_int(3LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[14]), gd::GdVal::from_int(2LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[15]), gd::GdVal::from_int(3LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[16]), gd::GdVal::from_int(3LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[17]), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[18]), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[19]), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[20]), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[21]), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[22]), gd::GdVal::from_float(0.5)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[23]), gd::GdVal::from_float(0.5)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[24]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[25]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[26]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[27]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[28]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[29]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[30]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[31]), gd::GdVal::from_float(0.1)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[32]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[33]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[34]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[35]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[36]), gd::GdVal::from_float(0.2)); return gd::GdVal::from_dict(d); })();
    this->f_digParticles = gd::GdVal::null();
    this->f_spawnPos = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__Shovel::meta() const { return &META_Gd__gd_core__Shovel; }
gd::GdVal Gd__gd_core__Shovel::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Shovel::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Shovel::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_digUpItems_1978: out = this->f_digUpItems; return true;
        case SYM_GEN_digParticles_1979: out = this->f_digParticles; return true;
        case SYM_GEN_spawnPos_1980: out = this->f_spawnPos; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__Shovel::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_digUpItems_1978: this->f_digUpItems = val; return true;
        case SYM_GEN_digParticles_1979: this->f_digParticles = val; return true;
        case SYM_GEN_spawnPos_1980: this->f_spawnPos = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Shovel::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Shovel::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Shovel::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Shovel::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Shovel::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_213, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Shovel::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Shovel(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Shovel>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Shovel = {CLS_Gd__gd_core__Shovel, "Shovel", "res://gd_core/Shovel.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__Shovel, &Gd__gd_core__Shovel::get_static_prop_fn, &Gd__gd_core__Shovel::call_static_fn};

void Gd__gd_core_items__PestilenceFlask::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Potion::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__PestilenceFlask::meta() const { return &META_Gd__gd_core_items__PestilenceFlask; }
gd::GdVal Gd__gd_core_items__PestilenceFlask::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Potion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__PestilenceFlask::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__PestilenceFlask::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Potion::get_prop(prop, out);
}
bool Gd__gd_core_items__PestilenceFlask::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__PestilenceFlask::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onOpponentHeal_1957: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::has_own_method(m);
}
bool Gd__gd_core_items__PestilenceFlask::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onOpponentHeal_1957: out = fn_onOpponentHeal(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__PestilenceFlask::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Potion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__PestilenceFlask::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_selfInflictPoison_212, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PestilenceFlask::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[37]), gd::GdVal::from_str(&battle_string_literals[38])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PestilenceFlask::fn_onOpponentHeal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv__aff = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0);
    gd::GdVal lv__aff_names = gd::GdVal::from_str(&battle_string_literals[39]);
    {
        gd::GdVal _t1833 = gd::gd_iter_seq(gd_ctx.arena, lv__aff);
        gd::GdArr* _t1834 = (_t1833.kind == gd::GdVal::Kind::Arr) ? _t1833.arr : nullptr;
        uint32_t _len__t1835 = _t1834 ? _t1834->len : 0u;
        for (uint32_t _t1835 = 0; _t1835 < _len__t1835; ++_t1835) {
            gd::GdVal lv__a = _t1834->data[_t1835];
            lv__aff_names = gd::gd_add(gd_ctx, lv__aff_names, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv__a, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[40])));
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[41]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1673))), gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[42]), ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, lv__aff, gd::SYM_size, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), lv__aff_names}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drink_1847, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_triggerPotion_1850, _ca, 1); })();
    gd::GdVal lv_affected = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, lv_affected, gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL)), SYM_GEN_triggerPotion_1850, _ca, 1); })();
        (void)gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL)), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PestilenceFlask::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Potion::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__PestilenceFlask(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__PestilenceFlask>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__PestilenceFlask = {CLS_Gd__gd_core_items__PestilenceFlask, "PestilenceFlask", "res://gd_core_items/PestilenceFlask.gd", &META_Gd__gd_core_items__Potion, true, _alloc_Gd__gd_core_items__PestilenceFlask, &Gd__gd_core_items__PestilenceFlask::get_static_prop_fn, &Gd__gd_core_items__PestilenceFlask::call_static_fn};

void Gd__gd_core__Wolpertinger::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_staminaRegenPerBuff = gd::GdVal::null();
    this->f_numBuffs = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core__Wolpertinger::meta() const { return &META_Gd__gd_core__Wolpertinger; }
gd::GdVal Gd__gd_core__Wolpertinger::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Wolpertinger::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Wolpertinger::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_staminaRegenPerBuff_2004: out = this->f_staminaRegenPerBuff; return true;
        case SYM_GEN_numBuffs_2005: out = this->f_numBuffs; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Wolpertinger::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaRegenPerBuff_2004: this->f_staminaRegenPerBuff = val; return true;
        case SYM_GEN_numBuffs_2005: this->f_numBuffs = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Wolpertinger::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onBuffChanged_2006: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Wolpertinger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onBuffChanged_2006: out = fn_onBuffChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Wolpertinger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Wolpertinger::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(3LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Wolpertinger::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[43])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterBuffs_374, _ca, 1); })();
    gd::GdVal lv_baseStaminaRegen = gd::get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_baseStaminaRegen_1057);
    this->f_staminaRegenPerBuff = gd::gd_div(gd_ctx, gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), lv_baseStaminaRegen), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Wolpertinger::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_numBuffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLeastBuffs_366, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Wolpertinger::fn_onBuffChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, this->f_staminaRegenPerBuff)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_giveStaminaRegeneration_1270, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Wolpertinger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_numBuffs = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Wolpertinger(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Wolpertinger>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Wolpertinger = {CLS_Gd__gd_core__Wolpertinger, "Wolpertinger", "res://gd_core/Wolpertinger.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__Wolpertinger, &Gd__gd_core__Wolpertinger::get_static_prop_fn, &Gd__gd_core__Wolpertinger::call_static_fn};

void Gd__gd_core_items__BloodGoobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Goobert::init_fields(gd_ctx);
    this->f_dam = gd::GdVal::null();
    this->f_vampirism = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__BloodGoobert::meta() const { return &META_Gd__gd_core_items__BloodGoobert; }
gd::GdVal Gd__gd_core_items__BloodGoobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__BloodGoobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__BloodGoobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_dam_939: out = this->f_dam; return true;
        case SYM_GEN_vampirism_940: out = this->f_vampirism; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__BloodGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_dam_939: this->f_dam = val; return true;
        case SYM_GEN_vampirism_940: this->f_vampirism = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__BloodGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__BloodGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__BloodGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__BloodGoobert::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_vampirism}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BloodGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_dam, gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getVampirism_1226, nullptr, 0)), gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealLife_329, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BloodGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_dam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[8])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_vampirism = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[44])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__BloodGoobert(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__BloodGoobert>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__BloodGoobert = {CLS_Gd__gd_core_items__BloodGoobert, "BloodGoobert", "res://gd_core_items/BloodGoobert.gd", &META_Gd__gd_core_items__Goobert, true, _alloc_Gd__gd_core_items__BloodGoobert, &Gd__gd_core_items__BloodGoobert::get_static_prop_fn, &Gd__gd_core_items__BloodGoobert::call_static_fn};

void Gd__gd_core_items__CritwoodStaff::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_buffActive = gd::GdVal::from_bool(false);
    this->f_activationParticles = gd::GdVal::null();
    this->f_critTimer = gd::GdVal::null();
    this->f_manaCost = gd::GdVal::null();
    this->f_tempDamBonus = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__CritwoodStaff::meta() const { return &META_Gd__gd_core_items__CritwoodStaff; }
gd::GdVal Gd__gd_core_items__CritwoodStaff::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__CritwoodStaff::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__CritwoodStaff::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_buffActive_1813: out = this->f_buffActive; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_critTimer_1814: out = this->f_critTimer; return true;
        case SYM_GEN_manaCost_1815: out = this->f_manaCost; return true;
        case SYM_GEN_tempDamBonus_1816: out = this->f_tempDamBonus; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__CritwoodStaff::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffActive_1813: this->f_buffActive = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_critTimer_1814: this->f_critTimer = val; return true;
        case SYM_GEN_manaCost_1815: this->f_manaCost = val; return true;
        case SYM_GEN_tempDamBonus_1816: this->f_tempDamBonus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__CritwoodStaff::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_buffEnded_1817: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__CritwoodStaff::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_buffEnded_1817: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__CritwoodStaff::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__CritwoodStaff::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CritwoodStaff::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_manaCost)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_buffActive)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
            {
                gd::GdVal _t1836 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
                gd::GdArr* _t1837 = (_t1836.kind == gd::GdVal::Kind::Arr) ? _t1836.arr : nullptr;
                uint32_t _len__t1838 = _t1837 ? _t1837->len : 0u;
                for (uint32_t _t1838 = 0; _t1838 < _len__t1838; ++_t1838) {
                    gd::GdVal lv_item = _t1837->data[_t1838];
                    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(100LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addCritChancePercent_179, _ca, 1); })();
                }
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 1); })();
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), this->f_tempDamBonus));
        gd::GdVal lv_critBuffDur = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[0])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_critTimer, lv_critBuffDur}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_changeTimer_1796, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CritwoodStaff::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1839 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t1840 = (_t1839.kind == gd::GdVal::Kind::Arr) ? _t1839.arr : nullptr;
        uint32_t _len__t1841 = _t1840 ? _t1840->len : 0u;
        for (uint32_t _t1841 = 0; _t1841 < _len__t1841; ++_t1841) {
            gd::GdVal lv_item = _t1840->data[_t1841];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(100LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_reduceCritChancePercent_180, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CritwoodStaff::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_critTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CritwoodStaff::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CritwoodStaff::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv_active)) {
    }
    else {
    }
    this->f_buffActive = lv_active;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CritwoodStaff::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_critTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[45]), gd::GdVal::from_str(&battle_string_literals[46]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_manaCost = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0);
    this->f_tempDamBonus = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__CritwoodStaff(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__CritwoodStaff>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__CritwoodStaff = {CLS_Gd__gd_core_items__CritwoodStaff, "CritwoodStaff", "res://gd_core_items/CritwoodStaff.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__CritwoodStaff, &Gd__gd_core_items__CritwoodStaff::get_static_prop_fn, &Gd__gd_core_items__CritwoodStaff::call_static_fn};

void Gd__gd_core_items__Exclusive__AcornAce::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_affectedDescriptors = gd::GdVal::null();
    this->f_boostedCollars = gd::GdVal::from_int(0LL);
    this->f_collarDescriptors = gd::GdVal::null();
    this->f_acornCollarDescriptor = gd::GdVal::null();
    this->f_critwoodStaffDescriptor = gd::GdVal::null();
    this->f_staminaReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__AcornAce::meta() const { return &META_Gd__gd_core_items__Exclusive__AcornAce; }
gd::GdVal Gd__gd_core_items__Exclusive__AcornAce::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__AcornAce::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__AcornAce::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_affectedDescriptors_2008: out = this->f_affectedDescriptors; return true;
        case SYM_GEN_boostedCollars_2009: out = this->f_boostedCollars; return true;
        case SYM_GEN_collarDescriptors_2010: out = this->f_collarDescriptors; return true;
        case SYM_GEN_acornCollarDescriptor_2011: out = this->f_acornCollarDescriptor; return true;
        case SYM_GEN_critwoodStaffDescriptor_2012: out = this->f_critwoodStaffDescriptor; return true;
        case SYM_GEN_staminaReduction_2013: out = this->f_staminaReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__AcornAce::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedDescriptors_2008: this->f_affectedDescriptors = val; return true;
        case SYM_GEN_boostedCollars_2009: this->f_boostedCollars = val; return true;
        case SYM_GEN_collarDescriptors_2010: this->f_collarDescriptors = val; return true;
        case SYM_GEN_acornCollarDescriptor_2011: this->f_acornCollarDescriptor = val; return true;
        case SYM_GEN_critwoodStaffDescriptor_2012: this->f_critwoodStaffDescriptor = val; return true;
        case SYM_GEN_staminaReduction_2013: this->f_staminaReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__AcornAce::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_onBought_455: return true;
        case SYM_GEN_canAffect_global_2014: return true;
        case SYM_GEN_onItemInstantiated_2015: return true;
        case SYM_GEN_onAddToInventory_419: return true;
        case SYM_GEN_onAddToInventory_deferred_2016: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_onRemoveFromInventory_deferred_2017: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onItemRoll_2018: return true;
        case SYM_GEN_onItemRolled_2019: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AcornAce::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_onBought_455: out = fn_onBought(args, argc); return true;
        case SYM_GEN_canAffect_global_2014: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN_onItemInstantiated_2015: out = fn_onItemInstantiated(args, argc); return true;
        case SYM_GEN_onAddToInventory_419: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onAddToInventory_deferred_2016: out = fn_onAddToInventory_deferred(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_deferred_2017: out = fn_onRemoveFromInventory_deferred(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemRoll_2018: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_2019: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__AcornAce::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__AcornAce::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_boostedCollars;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AcornAce::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_data, gd::GdVal::null())))) {
        this->f_boostedCollars = lv_data;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AcornAce::fn_onBought(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_boostedCollars = gd::GdVal::from_int(1LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AcornAce::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::gd_in(gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), this->f_affectedDescriptors);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AcornAce::fn_onItemInstantiated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(this->f_placed) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(lv_item, &META_Gd__gd_core_items__RangerCollar)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isOwnable_250, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_activateExtendedAffectedCells_432, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AcornAce::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[47]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_defer_1482, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AcornAce::fn_onAddToInventory_deferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AcornAce::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[48]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_defer_1482, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AcornAce::fn_onRemoveFromInventory_deferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AcornAce::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1842 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {this->f_critwoodStaffDescriptor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAllInInventoryOfType_803, _ca, 1); })());
        gd::GdArr* _t1843 = (_t1842.kind == gd::GdVal::Kind::Arr) ? _t1842.arr : nullptr;
        uint32_t _len__t1844 = _t1843 ? _t1843->len : 0u;
        for (uint32_t _t1844 = 0; _t1844 < _len__t1844; ++_t1844) {
            gd::GdVal lv_staff = _t1843->data[_t1844];
            (void)([&]() { gd::GdVal _ca[] = {this->f_staminaReduction}; return gd::native_inline_call(gd_ctx, lv_staff, SYM_GEN_changeStaminaFactor_305, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AcornAce::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AcornAce::fn_onItemRolled(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_descr, this->f_acornCollarDescriptor)))) {
        this->f_boostedCollars = gd::gd_sub(this->f_boostedCollars, gd::GdVal::from_int(1LL));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AcornAce::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_collarDescriptors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[49])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[50])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[51])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[52])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })()}));
    this->f_acornCollarDescriptor = gd::native_array_index(gd_ctx, this->f_collarDescriptors, gd::GdVal::from_int(0LL));
    this->f_critwoodStaffDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[53])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_staminaReduction = gd::gd_neg(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[54])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_affectedDescriptors = ([&]() { gd::GdVal _ca[] = {this->f_collarDescriptors}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_arrayAsIndexDict_1799, _ca, 1); })();
    { gd::GdVal _t1845 = this->f_affectedDescriptors; gd::GdVal _t1846 = this->f_critwoodStaffDescriptor; gd::native_array_set_index(gd_ctx, _t1845, _t1846, gd::GdVal::from_int(4LL)); }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__AcornAce(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__AcornAce>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AcornAce = {CLS_Gd__gd_core_items__Exclusive__AcornAce, "AcornAce", "res://gd_core_items/Exclusive/AcornAce.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__AcornAce, &Gd__gd_core_items__Exclusive__AcornAce::get_static_prop_fn, &Gd__gd_core_items__Exclusive__AcornAce::call_static_fn};

void Gd__gd_core_items__Exclusive__ArcaneIntellect::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_magicSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ArcaneIntellect::meta() const { return &META_Gd__gd_core_items__Exclusive__ArcaneIntellect; }
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneIntellect::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ArcaneIntellect::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ArcaneIntellect::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_magicSpeed_2041: out = this->f_magicSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ArcaneIntellect::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_magicSpeed_2041: this->f_magicSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ArcaneIntellect::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_getRandomScroll_2042: return true;
        case SYM_GEN_getRandomBook_2043: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ArcaneIntellect::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_getRandomScroll_2042: out = fn_getRandomScroll(args, argc); return true;
        case SYM_GEN_getRandomBook_2043: out = fn_getRandomBook(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ArcaneIntellect::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneIntellect::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(23LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneIntellect::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1847 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1848 = (_t1847.kind == gd::GdVal::Kind::Arr) ? _t1847.arr : nullptr;
        uint32_t _len__t1849 = _t1848 ? _t1848->len : 0u;
        for (uint32_t _t1849 = 0; _t1849 < _len__t1849; ++_t1849) {
            gd::GdVal lv_item = _t1848->data[_t1849];
            (void)([&]() { gd::GdVal _ca[] = {this->f_magicSpeed}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneIntellect::fn_getRandomScroll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneIntellect::fn_getRandomBook(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneIntellect::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_magicSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[55])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ArcaneIntellect(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ArcaneIntellect>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ArcaneIntellect = {CLS_Gd__gd_core_items__Exclusive__ArcaneIntellect, "ArcaneIntellect", "res://gd_core_items/Exclusive/ArcaneIntellect.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__ArcaneIntellect, &Gd__gd_core_items__Exclusive__ArcaneIntellect::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ArcaneIntellect::call_static_fn};

void Gd__gd_core_items__Exclusive__Bazooka::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_activationsLeft = gd::GdVal::from_int(0);
    this->f_stunResistActive = gd::GdVal::from_bool(false);
    this->f_heatNeeded = gd::GdVal::null();
    this->f_luck = gd::GdVal::null();
    this->f_luckNeeded = gd::GdVal::null();
    this->f_uses = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Bazooka::meta() const { return &META_Gd__gd_core_items__Exclusive__Bazooka; }
gd::GdVal Gd__gd_core_items__Exclusive__Bazooka::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Bazooka::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Bazooka::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activationsLeft_2061: out = this->f_activationsLeft; return true;
        case SYM_GEN_stunResistActive_2062: out = this->f_stunResistActive; return true;
        case SYM_GEN_heatNeeded_1880: out = this->f_heatNeeded; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_luckNeeded_1874: out = this->f_luckNeeded; return true;
        case SYM_GEN_uses_2063: out = this->f_uses; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Bazooka::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activationsLeft_2061: this->f_activationsLeft = gd::gd_coerce_int(val); return true;
        case SYM_GEN_stunResistActive_2062: this->f_stunResistActive = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_heatNeeded_1880: this->f_heatNeeded = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_luckNeeded_1874: this->f_luckNeeded = val; return true;
        case SYM_GEN_uses_2063: this->f_uses = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Bazooka::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN_onLuckChanged_2064: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Bazooka::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onLuckChanged_2064: out = fn_onLuckChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Bazooka::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Bazooka::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_activationsLeft = gd::gd_coerce_int(this->f_uses);
    this->f_stunResistActive = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[56]), gd::GdVal::from_str(&battle_string_literals[57])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Bazooka::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_activationsLeft, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getHeat_1251, nullptr, 0), this->f_heatNeeded)))) : gd::GdVal::from_bool(false)))) {
            this->f_activationsLeft = gd::gd_coerce_int(gd::gd_sub(this->f_activationsLeft, gd::GdVal::from_int(1LL)));
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_LoggingMode_1599), SYM_GEN_Delayed_2686)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_setLoggingMode_1588, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_heatNeeded, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useHeat_354, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_luck, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), gd::GdVal::from_bool(true), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 3); })();
            (void)gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_flushLoggingQueue_1591, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[58])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_330, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[59])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_stun_330, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Bazooka::fn_onLuckChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_stunResistActive)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), this->f_luckNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeStunResistance_1176, _ca, 1); })();
        this->f_stunResistActive = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
    }
    else if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(this->f_stunResistActive)) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), this->f_luckNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeStunResistance_1176, _ca, 1); })();
        this->f_stunResistActive = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Bazooka::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_heatNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[60])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[9])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_uses = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[61])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Bazooka(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Bazooka>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Bazooka = {CLS_Gd__gd_core_items__Exclusive__Bazooka, "Bazooka", "res://gd_core_items/Exclusive/Bazooka.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__Bazooka, &Gd__gd_core_items__Exclusive__Bazooka::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Bazooka::call_static_fn};

void Gd__gd_core_items__Exclusive__BowlofTreats::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
    this->f_speedBonusGiven = gd::GdVal::from_float(0.0);
    this->f_speedBonus = gd::GdVal::null();
    this->f_maxSpeedBonus = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__BowlofTreats::meta() const { return &META_Gd__gd_core_items__Exclusive__BowlofTreats; }
gd::GdVal Gd__gd_core_items__Exclusive__BowlofTreats::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__BowlofTreats::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__BowlofTreats::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_speedBonusGiven_2096: out = this->f_speedBonusGiven; return true;
        case SYM_GEN_speedBonus_1877: out = this->f_speedBonus; return true;
        case SYM_GEN_maxSpeedBonus_2097: out = this->f_maxSpeedBonus; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BowlofTreats::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_speedBonusGiven_2096: this->f_speedBonusGiven = val; return true;
        case SYM_GEN_speedBonus_1877: this->f_speedBonus = val; return true;
        case SYM_GEN_maxSpeedBonus_2097: this->f_maxSpeedBonus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BowlofTreats::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_global_2014: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_getGatedDescriptor_956: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BowlofTreats::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_global_2014: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getGatedDescriptor_956: out = fn_getGatedDescriptor(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BowlofTreats::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BowlofTreats::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(3LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BowlofTreats::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_speedBonusGiven = gd::GdVal::from_float(0.0);
    {
        gd::GdVal _t1850 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t1851 = (_t1850.kind == gd::GdVal::Kind::Arr) ? _t1850.arr : nullptr;
        uint32_t _len__t1852 = _t1851 ? _t1851->len : 0u;
        for (uint32_t _t1852 = 0; _t1852 < _len__t1852; ++_t1852) {
            gd::GdVal lv_item = _t1851->data[_t1852];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_global_2014, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_giveDoubleActivationChance_312, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BowlofTreats::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_speedBonusGiven, this->f_maxSpeedBonus)))) {
        {
            gd::GdVal _t1853 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
            gd::GdArr* _t1854 = (_t1853.kind == gd::GdVal::Kind::Arr) ? _t1853.arr : nullptr;
            uint32_t _len__t1855 = _t1854 ? _t1854->len : 0u;
            for (uint32_t _t1855 = 0; _t1855 < _len__t1855; ++_t1855) {
                gd::GdVal lv_item = _t1854->data[_t1855];
                gd::GdVal lv_curBonus = gd::gd_min(this->f_speedBonus, gd::gd_sub(this->f_maxSpeedBonus, this->f_speedBonusGiven));
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, lv_curBonus, gd::GdVal::from_int(100LL))}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
            }
        }
        this->f_speedBonusGiven = gd::gd_add(gd_ctx, this->f_speedBonusGiven, this->f_speedBonus);
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BowlofTreats::fn_getGatedDescriptor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rarity = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_itemName = gd::GdVal::from_cstr(gd_ctx.arena, "");
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_rarity, gd::GdVal::from_int(3LL))))) {
        lv_rarity = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}))}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_pickRandomElement_1746, _ca, 1); })();
    }
    {
        gd::GdVal _t1856 = lv_rarity;
        if (gd::native_scalar_eq(_t1856, gd::GdVal::from_int(0LL))) {
            lv_itemName = gd::GdVal::from_str(&battle_string_literals[62]);
        }
        else if (gd::native_scalar_eq(_t1856, gd::GdVal::from_int(1LL))) {
            lv_itemName = gd::GdVal::from_str(&battle_string_literals[63]);
        }
        else if (gd::native_scalar_eq(_t1856, gd::GdVal::from_int(2LL))) {
            lv_itemName = gd::GdVal::from_str(&battle_string_literals[64]);
        }
    }
    return ([&]() { gd::GdVal _ca[] = {lv_itemName}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BowlofTreats::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speedBonus = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0);
    this->f_maxSpeedBonus = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BowlofTreats(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__BowlofTreats>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BowlofTreats = {CLS_Gd__gd_core_items__Exclusive__BowlofTreats, "BowlofTreats", "res://gd_core_items/Exclusive/BowlofTreats.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Exclusive__BowlofTreats, &Gd__gd_core_items__Exclusive__BowlofTreats::get_static_prop_fn, &Gd__gd_core_items__Exclusive__BowlofTreats::call_static_fn};

void Gd__gd_core_items__Exclusive__ChainWhip::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_buffsPurged = gd::GdVal::from_int(0LL);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ChainWhip::meta() const { return &META_Gd__gd_core_items__Exclusive__ChainWhip; }
gd::GdVal Gd__gd_core_items__Exclusive__ChainWhip::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ChainWhip::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ChainWhip::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_buffsPurged_2131: out = this->f_buffsPurged; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ChainWhip::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffsPurged_2131: this->f_buffsPurged = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ChainWhip::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onOpponentBuffsChanged_2132: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ChainWhip::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onOpponentBuffsChanged_2132: out = fn_onOpponentBuffsChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ChainWhip::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ChainWhip::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_buffsPurged = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[65])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToOpponentBuffs_377, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ChainWhip::fn_onOpponentBuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL))))) {
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getOrigin_1580, nullptr, 0), &META_Gd__gd_core_items__Item))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getOrigin_1580, nullptr, 0), SYM_GEN_character_74, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
            this->f_buffsPurged = gd::gd_add(gd_ctx, this->f_buffsPurged, gd::gd_neg(lv_amount));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_neg(lv_amount), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ChainWhip::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeRandomBuffs_372, _ca, 1); })();
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_isBattleRaging_1207, nullptr, 0))) {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ChainWhip::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ChainWhip(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ChainWhip>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ChainWhip = {CLS_Gd__gd_core_items__Exclusive__ChainWhip, "ChainWhip", "res://gd_core_items/Exclusive/ChainWhip.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__ChainWhip, &Gd__gd_core_items__Exclusive__ChainWhip::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ChainWhip::call_static_fn};

void Gd__gd_core_items__Exclusive__Chess__WhiteRook::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Chess__ChessPiece::init_fields(gd_ctx);
    this->f_buffTimer = gd::GdVal::null();
    this->f_damReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Chess__WhiteRook::meta() const { return &META_Gd__gd_core_items__Exclusive__Chess__WhiteRook; }
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteRook::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteRook::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteRook::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_buffTimer_1819: out = this->f_buffTimer; return true;
        case SYM_GEN_damReduction_1873: out = this->f_damReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteRook::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffTimer_1819: this->f_buffTimer = val; return true;
        case SYM_GEN_damReduction_1873: this->f_damReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteRook::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2146: return true;
        case SYM_GEN_doEliminatedEffect_2148: return true;
        case SYM_GEN_buffEnded_1817: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteRook::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2146: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_doEliminatedEffect_2148: out = fn_doEliminatedEffect(args, argc); return true;
        case SYM_GEN_buffEnded_1817: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteRook::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteRook::fn_doCapturingEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__eliminatedPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteRook::fn_doEliminatedEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[0])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, this->f_buffTimer, SYM_GEN_start_1779, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteRook::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteRook::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[66]), gd::GdVal::from_str(&battle_string_literals[46]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_damReduction = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[8])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Chess__WhiteRook(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Chess__WhiteRook>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__WhiteRook = {CLS_Gd__gd_core_items__Exclusive__Chess__WhiteRook, "WhiteRook", "res://gd_core_items/Exclusive/Chess/WhiteRook.gd", &META_Gd__gd_core_items__Exclusive__Chess__ChessPiece, true, _alloc_Gd__gd_core_items__Exclusive__Chess__WhiteRook, &Gd__gd_core_items__Exclusive__Chess__WhiteRook::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Chess__WhiteRook::call_static_fn};

void Gd__gd_core_items__Exclusive__CupcakeGoobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Goobert::init_fields(gd_ctx);
    this->f_numBuffs = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__CupcakeGoobert::meta() const { return &META_Gd__gd_core_items__Exclusive__CupcakeGoobert; }
gd::GdVal Gd__gd_core_items__Exclusive__CupcakeGoobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__CupcakeGoobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__CupcakeGoobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_numBuffs_2005: out = this->f_numBuffs; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__CupcakeGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numBuffs_2005: this->f_numBuffs = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__CupcakeGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__CupcakeGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__CupcakeGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__CupcakeGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {this->f_numBuffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMostBuffs_367, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CupcakeGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_numBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[67])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__CupcakeGoobert(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__CupcakeGoobert>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__CupcakeGoobert = {CLS_Gd__gd_core_items__Exclusive__CupcakeGoobert, "CupcakeGoobert", "res://gd_core_items/Exclusive/CupcakeGoobert.gd", &META_Gd__gd_core_items__Goobert, true, _alloc_Gd__gd_core_items__Exclusive__CupcakeGoobert, &Gd__gd_core_items__Exclusive__CupcakeGoobert::get_static_prop_fn, &Gd__gd_core_items__Exclusive__CupcakeGoobert::call_static_fn};

void Gd__gd_core_items__Exclusive__DragonKnight::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__RubyWhelp::init_fields(gd_ctx);
    this->f_cdAdvance = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__DragonKnight::meta() const { return &META_Gd__gd_core_items__Exclusive__DragonKnight; }
gd::GdVal Gd__gd_core_items__Exclusive__DragonKnight::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__RubyWhelp::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__DragonKnight::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__DragonKnight::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_cdAdvance_2080: out = this->f_cdAdvance; return true;
        default: break;
    }
    return Gd__gd_core_items__RubyWhelp::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DragonKnight::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_cdAdvance_2080: this->f_cdAdvance = val; return true;
        default: break;
    }
    return Gd__gd_core_items__RubyWhelp::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DragonKnight::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN_onItemActivated_938: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__RubyWhelp::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DragonKnight::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onItemActivated_938: out = fn_onItemActivated(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__RubyWhelp::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DragonKnight::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__RubyWhelp::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonKnight::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canActivate_91, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonKnight::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1857 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1858 = (_t1857.kind == gd::GdVal::Kind::Arr) ? _t1857.arr : nullptr;
        uint32_t _len__t1859 = _t1858 ? _t1858->len : 0u;
        for (uint32_t _t1859 = 0; _t1859 < _len__t1859; ++_t1859) {
            gd::GdVal lv_item = _t1858->data[_t1859];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[68]), gd::GdVal::from_str(&battle_string_literals[69])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonKnight::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[70])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonKnight::fn_onItemActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_cdAdvance}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_advanceCooldownPercent_146, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonKnight::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__RubyWhelp::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_cdAdvance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[71])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DragonKnight(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__DragonKnight>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DragonKnight = {CLS_Gd__gd_core_items__Exclusive__DragonKnight, "DragonKnight", "res://gd_core_items/Exclusive/DragonKnight.gd", &META_Gd__gd_core_items__RubyWhelp, true, _alloc_Gd__gd_core_items__Exclusive__DragonKnight, &Gd__gd_core_items__Exclusive__DragonKnight::get_static_prop_fn, &Gd__gd_core_items__Exclusive__DragonKnight::call_static_fn};

void Gd__gd_core_items__Exclusive__EngineerBag2::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bag::init_fields(gd_ctx);
    this->f_cogDescriptor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__EngineerBag2::meta() const { return &META_Gd__gd_core_items__Exclusive__EngineerBag2; }
gd::GdVal Gd__gd_core_items__Exclusive__EngineerBag2::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__EngineerBag2::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__EngineerBag2::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_cogDescriptor_2180: out = this->f_cogDescriptor; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__EngineerBag2::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_cogDescriptor_2180: this->f_cogDescriptor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__EngineerBag2::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onItemRoll_2018: return true;
        case SYM_GEN_getRelatedItems_459: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__EngineerBag2::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onItemRoll_2018: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_getRelatedItems_459: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__EngineerBag2::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__EngineerBag2::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EngineerBag2::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EngineerBag2::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {this->f_cogDescriptor}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EngineerBag2::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_cogDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[72])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__EngineerBag2(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__EngineerBag2>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__EngineerBag2 = {CLS_Gd__gd_core_items__Exclusive__EngineerBag2, "EngineerBag2", "res://gd_core_items/Exclusive/EngineerBag2.gd", &META_Gd__gd_core_items__Bag, true, _alloc_Gd__gd_core_items__Exclusive__EngineerBag2, &Gd__gd_core_items__Exclusive__EngineerBag2::get_static_prop_fn, &Gd__gd_core_items__Exclusive__EngineerBag2::call_static_fn};

void Gd__gd_core_items__Exclusive__ForgingHammer::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ForgingHammer::meta() const { return &META_Gd__gd_core_items__Exclusive__ForgingHammer; }
gd::GdVal Gd__gd_core_items__Exclusive__ForgingHammer::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ForgingHammer::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ForgingHammer::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ForgingHammer::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ForgingHammer::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onEmpowerChanged_2113: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ForgingHammer::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onEmpowerChanged_2113: out = fn_onEmpowerChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ForgingHammer::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ForgingHammer::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[73]), gd::GdVal::from_str(&battle_string_literals[74])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ForgingHammer::fn_onEmpowerChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_162, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ForgingHammer::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ForgingHammer(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ForgingHammer>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ForgingHammer = {CLS_Gd__gd_core_items__Exclusive__ForgingHammer, "ForgingHammer", "res://gd_core_items/Exclusive/ForgingHammer.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__ForgingHammer, &Gd__gd_core_items__Exclusive__ForgingHammer::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ForgingHammer::call_static_fn};

void Gd__gd_core_items__Exclusive__GoldCube::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Cube::init_fields(gd_ctx);
    this->f_hasActivated = gd::GdVal::from_bool(false);
    this->f_healthThreshold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__GoldCube::meta() const { return &META_Gd__gd_core_items__Exclusive__GoldCube; }
gd::GdVal Gd__gd_core_items__Exclusive__GoldCube::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Cube::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__GoldCube::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__GoldCube::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_hasActivated_1906: out = this->f_hasActivated; return true;
        case SYM_GEN_healthThreshold_1854: out = this->f_healthThreshold; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__GoldCube::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hasActivated_1906: this->f_hasActivated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_healthThreshold_1854: this->f_healthThreshold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__GoldCube::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onDamaged_1855: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__GoldCube::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1855: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__GoldCube::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Cube::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldCube::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldCube::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    this->f_affectedItem = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_428, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[75]), gd::GdVal::from_str(&battle_string_literals[76])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldCube::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(this->f_hasActivated)) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRelativeHealth_302, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_affectedItem, gd::GdVal::null())))) {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_advanceAffectedItem_2082, nullptr, 0);
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[70])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[77])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRegeneration_1233, nullptr, 0)))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 1); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_381, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldCube::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Cube::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[78])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__GoldCube(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__GoldCube>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__GoldCube = {CLS_Gd__gd_core_items__Exclusive__GoldCube, "GoldCube", "res://gd_core_items/Exclusive/GoldCube.gd", &META_Gd__gd_core_items__Exclusive__Cube, true, _alloc_Gd__gd_core_items__Exclusive__GoldCube, &Gd__gd_core_items__Exclusive__GoldCube::get_static_prop_fn, &Gd__gd_core_items__Exclusive__GoldCube::call_static_fn};

void Gd__gd_core_items__Exclusive__IceDragon::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_gaveBlock = gd::GdVal::from_bool(false);
    this->f_coldOnHit = gd::GdVal::from_int(0);
    this->f_coldThreshold = gd::GdVal::from_int(0);
    this->f_damReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__IceDragon::meta() const { return &META_Gd__gd_core_items__Exclusive__IceDragon; }
gd::GdVal Gd__gd_core_items__Exclusive__IceDragon::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__IceDragon::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__IceDragon::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_gaveBlock_2314: out = this->f_gaveBlock; return true;
        case SYM_GEN_coldOnHit_2315: out = this->f_coldOnHit; return true;
        case SYM_GEN_coldThreshold_2316: out = this->f_coldThreshold; return true;
        case SYM_GEN_damReduction_1873: out = this->f_damReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__IceDragon::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_gaveBlock_2314: this->f_gaveBlock = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_coldOnHit_2315: this->f_coldOnHit = gd::gd_coerce_int(val); return true;
        case SYM_GEN_coldThreshold_2316: this->f_coldThreshold = gd::gd_coerce_int(val); return true;
        case SYM_GEN_damReduction_1873: this->f_damReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__IceDragon::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onOpponentColdChanged_2204: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__IceDragon::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onOpponentColdChanged_2204: out = fn_onOpponentColdChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__IceDragon::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__IceDragon::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_gaveBlock = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[79]), gd::GdVal::from_str(&battle_string_literals[80])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__IceDragon::fn_onOpponentColdChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_gaveBlock))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getCold_1254, nullptr, 0), this->f_coldThreshold)))) : gd::GdVal::from_bool(false)))) {
        this->f_gaveBlock = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), gd::GdVal::from_bool(true), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeEffectDamageFactor_1281, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__IceDragon::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_coldOnHit}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_351, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__IceDragon::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_coldOnHit = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[81])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_coldThreshold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[82])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_damReduction = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[83])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__IceDragon(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__IceDragon>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__IceDragon = {CLS_Gd__gd_core_items__Exclusive__IceDragon, "IceDragon", "res://gd_core_items/Exclusive/IceDragon.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__IceDragon, &Gd__gd_core_items__Exclusive__IceDragon::get_static_prop_fn, &Gd__gd_core_items__Exclusive__IceDragon::call_static_fn};

void Gd__gd_core_items__Exclusive__LightFlower::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
    this->f_manaNeeded = gd::GdVal::null();
    this->f_debuffs = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
    this->f_luck = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__LightFlower::meta() const { return &META_Gd__gd_core_items__Exclusive__LightFlower; }
gd::GdVal Gd__gd_core_items__Exclusive__LightFlower::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__LightFlower::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__LightFlower::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_manaNeeded_1881: out = this->f_manaNeeded; return true;
        case SYM_GEN_debuffs_2151: out = this->f_debuffs; return true;
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__LightFlower::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaNeeded_1881: this->f_manaNeeded = val; return true;
        case SYM_GEN_debuffs_2151: this->f_debuffs = val; return true;
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__LightFlower::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__LightFlower::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__LightFlower::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__LightFlower::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LightFlower::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0), gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, _ca, 1); })()))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeBuffProtectionChance_1286, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LightFlower::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_manaNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_debuffs, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_356, _ca, 2); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getDebuffStacks_1216, nullptr, 0), gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LightFlower::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[84])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_debuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[85])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[86])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[9])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__LightFlower(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__LightFlower>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__LightFlower = {CLS_Gd__gd_core_items__Exclusive__LightFlower, "LightFlower", "res://gd_core_items/Exclusive/LightFlower.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Exclusive__LightFlower, &Gd__gd_core_items__Exclusive__LightFlower::get_static_prop_fn, &Gd__gd_core_items__Exclusive__LightFlower::call_static_fn};

void Gd__gd_core_items__Exclusive__ManaMastery::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_boosted = gd::GdVal::from_int(0LL);
    this->f_mana = gd::GdVal::null();
    this->f_magicSpeed = gd::GdVal::null();
    this->f_bonusBuffs = gd::GdVal::null();
    this->f_manaOrbDescriptor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ManaMastery::meta() const { return &META_Gd__gd_core_items__Exclusive__ManaMastery; }
gd::GdVal Gd__gd_core_items__Exclusive__ManaMastery::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ManaMastery::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ManaMastery::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_boosted_2197: out = this->f_boosted; return true;
        case SYM_GEN_mana_1928: out = this->f_mana; return true;
        case SYM_GEN_magicSpeed_2041: out = this->f_magicSpeed; return true;
        case SYM_GEN_bonusBuffs_1927: out = this->f_bonusBuffs; return true;
        case SYM_GEN_manaOrbDescriptor_2393: out = this->f_manaOrbDescriptor; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ManaMastery::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_boosted_2197: this->f_boosted = val; return true;
        case SYM_GEN_mana_1928: this->f_mana = val; return true;
        case SYM_GEN_magicSpeed_2041: this->f_magicSpeed = val; return true;
        case SYM_GEN_bonusBuffs_1927: this->f_bonusBuffs = val; return true;
        case SYM_GEN_manaOrbDescriptor_2393: this->f_manaOrbDescriptor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ManaMastery::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_onBought_455: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_global_2014: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreCombatStart_125: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onItemRoll_2018: return true;
        case SYM_GEN_onItemRolled_2019: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ManaMastery::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_onBought_455: out = fn_onBought(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_global_2014: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreCombatStart_125: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onItemRoll_2018: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_2019: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ManaMastery::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaMastery::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_boosted;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaMastery::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_data, gd::GdVal::null())))) {
        this->f_boosted = lv_data;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaMastery::fn_onBought(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_boosted = gd::GdVal::from_int(1LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaMastery::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(23LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaMastery::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {this->f_manaOrbDescriptor}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isA_245, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaMastery::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numMagic = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numMagic, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_magicSpeed, lv_numMagic)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaMastery::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1860 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {this->f_manaOrbDescriptor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAllInInventoryOfType_803, _ca, 1); })());
        gd::GdArr* _t1861 = (_t1860.kind == gd::GdVal::Kind::Arr) ? _t1860.arr : nullptr;
        uint32_t _len__t1862 = _t1861 ? _t1861->len : 0u;
        for (uint32_t _t1862 = 0; _t1862 < _len__t1862; ++_t1862) {
            gd::GdVal lv_manaOrb = _t1861->data[_t1862];
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusBuffs}; return gd::native_inline_call(gd_ctx, lv_manaOrb, SYM_GEN_addBonusRandomBuffs_1930, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaMastery::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaMastery::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaMastery::fn_onItemRolled(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_descr, this->f_manaOrbDescriptor)))) {
        this->f_boosted = gd::gd_sub(this->f_boosted, gd::GdVal::from_int(1LL));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaMastery::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[87])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_magicSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[55])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_bonusBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[67])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_manaOrbDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[88])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ManaMastery(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ManaMastery>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ManaMastery = {CLS_Gd__gd_core_items__Exclusive__ManaMastery, "ManaMastery", "res://gd_core_items/Exclusive/ManaMastery.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__ManaMastery, &Gd__gd_core_items__Exclusive__ManaMastery::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ManaMastery::call_static_fn};

void Gd__gd_core_items__Exclusive__NullBlade::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_luckNeeded = gd::GdVal::null();
    this->f_regenNeeded = gd::GdVal::null();
    this->f_dam = gd::GdVal::null();
    this->f_buffs = gd::GdVal::null();
    this->f_speedBonus = gd::GdVal::null();
    this->f_distortion = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__NullBlade::meta() const { return &META_Gd__gd_core_items__Exclusive__NullBlade; }
gd::GdVal Gd__gd_core_items__Exclusive__NullBlade::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__NullBlade::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__NullBlade::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_luckNeeded_1874: out = this->f_luckNeeded; return true;
        case SYM_GEN_regenNeeded_942: out = this->f_regenNeeded; return true;
        case SYM_GEN_dam_939: out = this->f_dam; return true;
        case SYM_GEN_buffs_1048: out = this->f_buffs; return true;
        case SYM_GEN_speedBonus_1877: out = this->f_speedBonus; return true;
        case SYM_GEN_distortion_2203: out = this->f_distortion; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__NullBlade::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_luckNeeded_1874: this->f_luckNeeded = val; return true;
        case SYM_GEN_regenNeeded_942: this->f_regenNeeded = val; return true;
        case SYM_GEN_dam_939: this->f_dam = val; return true;
        case SYM_GEN_buffs_1048: this->f_buffs = val; return true;
        case SYM_GEN_speedBonus_1877: this->f_speedBonus = val; return true;
        case SYM_GEN_distortion_2203: this->f_distortion = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__NullBlade::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_pickup_717: return true;
        case SYM_GEN_drop_723: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__NullBlade::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_pickup_717: out = fn_pickup(args, argc); return true;
        case SYM_GEN_drop_723: out = fn_drop(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__NullBlade::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__NullBlade::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), this->f_luckNeeded)))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_luckNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useLucky_350, _ca, 1); })();
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), this->f_dam));
            (void)([&]() { gd::GdVal _ca[] = {this->f_dam}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRegeneration_1233, nullptr, 0), this->f_regenNeeded)))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_regenNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_346, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_buffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeRandomBuffs_372, _ca, 1); })();
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getBuffStacks_1215, nullptr, 0), gd::GdVal::from_int(0LL))))) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_speedBonus}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__NullBlade::fn_pickup(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_pickupType = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__NullBlade::get_static_const_or_enum(gd_ctx, SYM_GEN_PickupType_866), SYM_GEN_Grabbed_2730));
    (void)([&]() { gd::GdVal _ca[] = {lv_pickupType}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_pickup_717, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__NullBlade::fn_drop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_res = ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_drop_723, nullptr, 0, _out); return _out; })();
    return lv_res;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__NullBlade::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regenNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[89])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_dam = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[8])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_buffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[67])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_speedBonus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[55])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__NullBlade(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__NullBlade>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__NullBlade = {CLS_Gd__gd_core_items__Exclusive__NullBlade, "NullBlade", "res://gd_core_items/Exclusive/NullBlade.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__NullBlade, &Gd__gd_core_items__Exclusive__NullBlade::get_static_prop_fn, &Gd__gd_core_items__Exclusive__NullBlade::call_static_fn};

void Gd__gd_core_items__Exclusive__PoisonShortbow::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_poison = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PoisonShortbow::meta() const { return &META_Gd__gd_core_items__Exclusive__PoisonShortbow; }
gd::GdVal Gd__gd_core_items__Exclusive__PoisonShortbow::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PoisonShortbow::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PoisonShortbow::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_poison_1962: out = this->f_poison; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PoisonShortbow::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_poison_1962: this->f_poison = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PoisonShortbow::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PoisonShortbow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PoisonShortbow::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonShortbow::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv_randomDebuff = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1391, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_pickRandomElement_1746, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_randomDebuff, gd::GdVal::from_int(108LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_poison, gd::GdVal::from_int(1LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {this->f_poison}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), lv_randomDebuff, gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonShortbow::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_poison = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PoisonShortbow(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__PoisonShortbow>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PoisonShortbow = {CLS_Gd__gd_core_items__Exclusive__PoisonShortbow, "PoisonShortbow", "res://gd_core_items/Exclusive/PoisonShortbow.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__PoisonShortbow, &Gd__gd_core_items__Exclusive__PoisonShortbow::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PoisonShortbow::call_static_fn};

void Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Goobert::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer::meta() const { return &META_Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer; }
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_267, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_213, _ca, 1); })();
    {
        gd::GdVal _t1863 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1864 = (_t1863.kind == gd::GdVal::Kind::Arr) ? _t1863.arr : nullptr;
        uint32_t _len__t1865 = _t1864 ? _t1864->len : 0u;
        for (uint32_t _t1865 = 0; _t1865 < _len__t1865; ++_t1865) {
            gd::GdVal lv_item = _t1864->data[_t1865];
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP6_268, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer = {CLS_Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer, "RainbowGoobertAdventurer", "res://gd_core_items/Exclusive/RainbowGoobertAdventurer.gd", &META_Gd__gd_core_items__Goobert, true, _alloc_Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer, &Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer::get_static_prop_fn, &Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer::call_static_fn};

void Gd__gd_core_items__Exclusive__Rope::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_speedUpItem = gd::GdVal::null();
    this->f_speedTimer = gd::GdVal::null();
    this->f_speedPerTrigger = gd::GdVal::null();
    this->f_maxSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Rope::meta() const { return &META_Gd__gd_core_items__Exclusive__Rope; }
gd::GdVal Gd__gd_core_items__Exclusive__Rope::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Rope::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Rope::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_speedUpItem_2471: out = this->f_speedUpItem; return true;
        case SYM_GEN_speedTimer_2039: out = this->f_speedTimer; return true;
        case SYM_GEN_speedPerTrigger_2472: out = this->f_speedPerTrigger; return true;
        case SYM_GEN_maxSpeed_2473: out = this->f_maxSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Rope::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_speedUpItem_2471: this->f_speedUpItem = val; return true;
        case SYM_GEN_speedTimer_2039: this->f_speedTimer = val; return true;
        case SYM_GEN_speedPerTrigger_2472: this->f_speedPerTrigger = val; return true;
        case SYM_GEN_maxSpeed_2473: this->f_maxSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Rope::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onTriggerItemActivated_2474: return true;
        case SYM_GEN_onSpeedTimeout_2475: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Rope::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onTriggerItemActivated_2474: out = fn_onTriggerItemActivated(args, argc); return true;
        case SYM_GEN_onSpeedTimeout_2475: out = fn_onSpeedTimeout(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Rope::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Rope::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canActivate_91, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Rope::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Rope::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1866 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, _ca, 1); })());
        gd::GdArr* _t1867 = (_t1866.kind == gd::GdVal::Kind::Arr) ? _t1866.arr : nullptr;
        uint32_t _len__t1868 = _t1867 ? _t1867->len : 0u;
        for (uint32_t _t1868 = 0; _t1868 < _len__t1868; ++_t1868) {
            gd::GdVal lv_item = _t1867->data[_t1868];
            this->f_speedUpItem = lv_item;
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_speedUpItem, gd::GdVal::null())))) {
        {
            gd::GdVal _t1869 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
            gd::GdArr* _t1870 = (_t1869.kind == gd::GdVal::Kind::Arr) ? _t1869.arr : nullptr;
            uint32_t _len__t1871 = _t1870 ? _t1870->len : 0u;
            for (uint32_t _t1871 = 0; _t1871 < _len__t1871; ++_t1871) {
                gd::GdVal lv_triggerItem = _t1870->data[_t1871];
                (void)([&]() { gd::GdVal _ca[] = {lv_triggerItem, gd::GdVal::from_str(&battle_string_literals[68]), gd::GdVal::from_str(&battle_string_literals[90])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Rope::fn_onTriggerItemActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_curSpeed = ([&]() { gd::GdVal _ca[] = {this->f_speedUpItem, gd::GdVal::from_float(0.0)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rope_speedups_1425), gd::SYM_get, _ca, 2); })();
    gd::GdVal lv_speedLeft = gd::gd_sub(this->f_maxSpeed, lv_curSpeed);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_speedLeft, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_min(lv_speedLeft, this->f_speedPerTrigger)}; return gd::native_inline_call(gd_ctx, this->f_speedUpItem, SYM_GEN_addSpeed_273, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rope_speedups_1425), this->f_speedUpItem, this->f_speedPerTrigger}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_dictAdd_1789, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[0])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, this->f_speedTimer, SYM_GEN_start_1779, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Rope::fn_onSpeedTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rope_speedups_1425), this->f_speedUpItem, this->f_speedPerTrigger}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_dictSub_1790, _ca, 3); })();
    gd::GdVal lv_curSpeed = ([&]() { gd::GdVal _ca[] = {this->f_speedUpItem, gd::GdVal::from_float(0.0)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rope_speedups_1425), gd::SYM_get, _ca, 2); })();
    gd::GdVal lv_speedLeft = gd::gd_sub(this->f_maxSpeed, lv_curSpeed);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_speedLeft, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_min(lv_speedLeft, this->f_speedPerTrigger)}; return gd::native_inline_call(gd_ctx, this->f_speedUpItem, SYM_GEN_reduceSpeed_274, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Rope::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_speedTimer, SYM_GEN_stop_1780, nullptr, 0);
    this->f_speedUpItem = gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Rope::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speedTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[91]), gd::GdVal::from_str(&battle_string_literals[92]), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_speedPerTrigger = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[55])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_maxSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[61])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Rope(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Rope>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Rope = {CLS_Gd__gd_core_items__Exclusive__Rope, "Rope", "res://gd_core_items/Exclusive/Rope.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Rope, &Gd__gd_core_items__Exclusive__Rope::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Rope::call_static_fn};

void Gd__gd_core_items__Exclusive__ShinyShell::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ShinyShell::meta() const { return &META_Gd__gd_core_items__Exclusive__ShinyShell; }
gd::GdVal Gd__gd_core_items__Exclusive__ShinyShell::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ShinyShell::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ShinyShell::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ShinyShell::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ShinyShell::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ShinyShell::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ShinyShell::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyShell::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyShell::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_healAmount = gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[70])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[93])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()));
    (void)([&]() { gd::GdVal _ca[] = {lv_healAmount}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyShell::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ShinyShell(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ShinyShell>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ShinyShell = {CLS_Gd__gd_core_items__Exclusive__ShinyShell, "ShinyShell", "res://gd_core_items/Exclusive/ShinyShell.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__ShinyShell, &Gd__gd_core_items__Exclusive__ShinyShell::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ShinyShell::call_static_fn};

void Gd__gd_core_items__Exclusive__SpellScrollDark::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_numActivations = gd::GdVal::from_int(0);
    this->f_speedBonus = gd::GdVal::null();
    this->f_darkSpeed = gd::GdVal::null();
    this->f_maxActivations = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SpellScrollDark::meta() const { return &META_Gd__gd_core_items__Exclusive__SpellScrollDark; }
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollDark::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SpellScrollDark::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SpellScrollDark::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_numActivations_1904: out = this->f_numActivations; return true;
        case SYM_GEN_speedBonus_1877: out = this->f_speedBonus; return true;
        case SYM_GEN_darkSpeed_2199: out = this->f_darkSpeed; return true;
        case SYM_GEN_maxActivations_1905: out = this->f_maxActivations; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SpellScrollDark::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numActivations_1904: this->f_numActivations = gd::gd_coerce_int(val); return true;
        case SYM_GEN_speedBonus_1877: this->f_speedBonus = val; return true;
        case SYM_GEN_darkSpeed_2199: this->f_darkSpeed = val; return true;
        case SYM_GEN_maxActivations_1905: this->f_maxActivations = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SpellScrollDark::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SpellScrollDark::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SpellScrollDark::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollDark::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollDark::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(25LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollDark::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_numActivations = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, _ca, 1); })(), this->f_darkSpeed)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollDark::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_numActivations = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numActivations, gd::GdVal::from_int(1LL)));
    {
        gd::GdVal _t1872 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1873 = (_t1872.kind == gd::GdVal::Kind::Arr) ? _t1872.arr : nullptr;
        uint32_t _len__t1874 = _t1873 ? _t1873->len : 0u;
        for (uint32_t _t1874 = 0; _t1874 < _len__t1874; ++_t1874) {
            gd::GdVal lv_item = _t1873->data[_t1874];
            (void)([&]() { gd::GdVal _ca[] = {this->f_speedBonus}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_int(109LL), gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 3); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_numActivations, this->f_maxActivations)))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    }
    else {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollDark::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speedBonus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[55])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_darkSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[94])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_maxActivations = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[61])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SpellScrollDark(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SpellScrollDark>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpellScrollDark = {CLS_Gd__gd_core_items__Exclusive__SpellScrollDark, "SpellScrollDark", "res://gd_core_items/Exclusive/SpellScrollDark.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__SpellScrollDark, &Gd__gd_core_items__Exclusive__SpellScrollDark::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SpellScrollDark::call_static_fn};

void Gd__gd_core_items__Exclusive__SteelDragon::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_reflectStacks = gd::GdVal::null();
    this->f_blockFactor = gd::GdVal::null();
    this->f_dam = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SteelDragon::meta() const { return &META_Gd__gd_core_items__Exclusive__SteelDragon; }
gd::GdVal Gd__gd_core_items__Exclusive__SteelDragon::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SteelDragon::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SteelDragon::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_reflectStacks_2547: out = this->f_reflectStacks; return true;
        case SYM_GEN_blockFactor_1977: out = this->f_blockFactor; return true;
        case SYM_GEN_dam_939: out = this->f_dam; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SteelDragon::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_reflectStacks_2547: this->f_reflectStacks = val; return true;
        case SYM_GEN_blockFactor_1977: this->f_blockFactor = val; return true;
        case SYM_GEN_dam_939: this->f_dam = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SteelDragon::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreCombatStart_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SteelDragon::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreCombatStart_125: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SteelDragon::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SteelDragon::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBlock_291, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SteelDragon::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1875 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1876 = (_t1875.kind == gd::GdVal::Kind::Arr) ? _t1875.arr : nullptr;
        uint32_t _len__t1877 = _t1876 ? _t1876->len : 0u;
        for (uint32_t _t1877 = 0; _t1877 < _len__t1877; ++_t1877) {
            gd::GdVal lv_item = _t1876->data[_t1877];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(100LL), this->f_blockFactor}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_giveBuffPower_303, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SteelDragon::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_reflectStacks}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveReflectStacks_200, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SteelDragon::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1878 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1879 = (_t1878.kind == gd::GdVal::Kind::Arr) ? _t1878.arr : nullptr;
        uint32_t _len__t1880 = _t1879 ? _t1879->len : 0u;
        for (uint32_t _t1880 = 0; _t1880 < _len__t1880; ++_t1880) {
            gd::GdVal lv_item = _t1879->data[_t1880];
            (void)([&]() { gd::GdVal _ca[] = {this->f_dam}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SteelDragon::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_reflectStacks = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[95])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_blockFactor = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[96])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_dam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[8])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SteelDragon(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SteelDragon>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SteelDragon = {CLS_Gd__gd_core_items__Exclusive__SteelDragon, "SteelDragon", "res://gd_core_items/Exclusive/SteelDragon.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__SteelDragon, &Gd__gd_core_items__Exclusive__SteelDragon::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SteelDragon::call_static_fn};

void Gd__gd_core_items__Exclusive__ThornShortbow::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ThornShortbow::meta() const { return &META_Gd__gd_core_items__Exclusive__ThornShortbow; }
gd::GdVal Gd__gd_core_items__Exclusive__ThornShortbow::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ThornShortbow::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ThornShortbow::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ThornShortbow::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ThornShortbow::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ThornShortbow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ThornShortbow::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ThornShortbow::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThornShortbow::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ThornShortbow(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ThornShortbow>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ThornShortbow = {CLS_Gd__gd_core_items__Exclusive__ThornShortbow, "ThornShortbow", "res://gd_core_items/Exclusive/ThornShortbow.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__ThornShortbow, &Gd__gd_core_items__Exclusive__ThornShortbow::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ThornShortbow::call_static_fn};

void Gd__gd_core_items__Exclusive__VampiricCollar::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__RangerCollar::init_fields(gd_ctx);
    this->f_affectedItems_dict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_maxLifesteal = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__VampiricCollar::meta() const { return &META_Gd__gd_core_items__Exclusive__VampiricCollar; }
gd::GdVal Gd__gd_core_items__Exclusive__VampiricCollar::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__RangerCollar::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__VampiricCollar::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__VampiricCollar::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_affectedItems_dict_2605: out = this->f_affectedItems_dict; return true;
        case SYM_GEN_maxLifesteal_2606: out = this->f_maxLifesteal; return true;
        default: break;
    }
    return Gd__gd_core_items__RangerCollar::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__VampiricCollar::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedItems_dict_2605: this->f_affectedItems_dict = val; return true;
        case SYM_GEN_maxLifesteal_2606: this->f_maxLifesteal = val; return true;
        default: break;
    }
    return Gd__gd_core_items__RangerCollar::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__VampiricCollar::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onVampirismChanged_943: return true;
        case SYM_GEN_onOpponentAttacked_2404: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__RangerCollar::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__VampiricCollar::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onVampirismChanged_943: out = fn_onVampirismChanged(args, argc); return true;
        case SYM_GEN_onOpponentAttacked_2404: out = fn_onOpponentAttacked(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__RangerCollar::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__VampiricCollar::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__RangerCollar::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__VampiricCollar::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canDamage_89, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__VampiricCollar::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_affectedItems, gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[97]), gd::GdVal::from_str(&battle_string_literals[98])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[99]), gd::GdVal::from_str(&battle_string_literals[100])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    }
    this->f_affectedItems_dict = ([&]() { gd::GdVal _ca[] = {this->f_affectedItems}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_arrayAsIndexDict_1799, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__VampiricCollar::fn_onVampirismChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    {
        gd::GdVal _t1881 = gd::gd_iter_seq(gd_ctx.arena, this->f_affectedItems);
        gd::GdArr* _t1882 = (_t1881.kind == gd::GdVal::Kind::Arr) ? _t1881.arr : nullptr;
        uint32_t _len__t1883 = _t1882 ? _t1882->len : 0u;
        for (uint32_t _t1883 = 0; _t1883 < _len__t1883; ++_t1883) {
            gd::GdVal lv_item = _t1882->data[_t1883];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0))}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeCritChancePercent_181, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__VampiricCollar::fn_onOpponentAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_getDamage_1522, nullptr, 0), gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_canApplyLifesteal_1563, nullptr, 0))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::gd_in(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_origin_1546), this->f_affectedItems_dict))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv_lifestealFactor = gd::gd_mul(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_lifestealFactor, gd::GdVal::from_int(0LL))))) {
            lv_lifestealFactor = gd::gd_min(lv_lifestealFactor, this->f_maxLifesteal);
            gd::GdVal lv_lifesteal = gd::gd_max(gd::GdVal::from_int(1LL), gd::gd_mul(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_lifestealFactor));
            (void)([&]() { gd::GdVal _ca[] = {lv_lifesteal, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__VampiricCollar::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__RangerCollar::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_maxLifesteal = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[61])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__VampiricCollar(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__VampiricCollar>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__VampiricCollar = {CLS_Gd__gd_core_items__Exclusive__VampiricCollar, "VampiricCollar", "res://gd_core_items/Exclusive/VampiricCollar.gd", &META_Gd__gd_core_items__RangerCollar, true, _alloc_Gd__gd_core_items__Exclusive__VampiricCollar, &Gd__gd_core_items__Exclusive__VampiricCollar::get_static_prop_fn, &Gd__gd_core_items__Exclusive__VampiricCollar::call_static_fn};

void Gd__gd_core_items__FannyPack::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bag::init_fields(gd_ctx);
    this->f_speedBonus = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__FannyPack::meta() const { return &META_Gd__gd_core_items__FannyPack; }
gd::GdVal Gd__gd_core_items__FannyPack::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__FannyPack::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__FannyPack::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_speedBonus_1877: out = this->f_speedBonus; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__FannyPack::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_speedBonus_1877: this->f_speedBonus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__FannyPack::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__FannyPack::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__FannyPack::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__FannyPack::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = gd::GdVal::from_bool(false);
    gd::GdVal lv_totalSpeed = this->f_speedBonus;
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[101])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isTypeInInventory_805, _ca, 1); })())) {
        lv_totalSpeed = gd::gd_add(gd_ctx, lv_totalSpeed, gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[55])}; return gd::native_inline_call(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[101])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })(), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0)));
    }
    {
        gd::GdVal _t1884 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0));
        gd::GdArr* _t1885 = (_t1884.kind == gd::GdVal::Kind::Arr) ? _t1884.arr : nullptr;
        uint32_t _len__t1886 = _t1885 ? _t1885->len : 0u;
        for (uint32_t _t1886 = 0; _t1886 < _len__t1886; ++_t1886) {
            gd::GdVal lv_item = _t1885->data[_t1886];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_920, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_totalSpeed}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
                lv_active = gd::GdVal::from_bool(true);
            }
        }
    }
    if (gd::gd_truth(lv_active)) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__FannyPack::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_toItem, SYM_GEN_hasCooldown_95, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, lv_toItem, SYM_GEN_isBag_83, nullptr, 0))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__FannyPack::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speedBonus = gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::GdVal::from_int(100LL));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__FannyPack(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__FannyPack>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__FannyPack = {CLS_Gd__gd_core_items__FannyPack, "FannyPack", "res://gd_core_items/FannyPack.gd", &META_Gd__gd_core_items__Bag, true, _alloc_Gd__gd_core_items__FannyPack, &Gd__gd_core_items__FannyPack::get_static_prop_fn, &Gd__gd_core_items__FannyPack::call_static_fn};

void Gd__gd_core_items__HeartContainer::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_activated = gd::GdVal::from_bool(false);
    this->f_regenNeeded = gd::GdVal::null();
    this->f_fillAnimation = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__HeartContainer::meta() const { return &META_Gd__gd_core_items__HeartContainer; }
gd::GdVal Gd__gd_core_items__HeartContainer::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__HeartContainer::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__HeartContainer::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activated_1314: out = this->f_activated; return true;
        case SYM_GEN_regenNeeded_942: out = this->f_regenNeeded; return true;
        case SYM_GEN_fillAnimation_1890: out = this->f_fillAnimation; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__HeartContainer::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1314: this->f_activated = val; return true;
        case SYM_GEN_regenNeeded_942: this->f_regenNeeded = val; return true;
        case SYM_GEN_fillAnimation_1890: this->f_fillAnimation = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__HeartContainer::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onRegenChanged_1891: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__HeartContainer::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onRegenChanged_1891: out = fn_onRegenChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__HeartContainer::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__HeartContainer::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[102]), gd::GdVal::from_str(&battle_string_literals[103])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeartContainer::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeartContainer::fn_onRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRegeneration_1233, nullptr, 0), this->f_regenNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_regenNeeded, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_346, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[104])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_267, nullptr, 0), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_addHealingEfficiency_1182, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeartContainer::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeartContainer::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_filled = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_activated, lv_filled)))) {
        return gd::GdVal::null();
    }
    this->f_activated = lv_filled;
    if (gd::gd_truth(lv_filled)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeartContainer::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_regenNeeded = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__HeartContainer(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__HeartContainer>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__HeartContainer = {CLS_Gd__gd_core_items__HeartContainer, "HeartContainer", "res://gd_core_items/HeartContainer.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__HeartContainer, &Gd__gd_core_items__HeartContainer::get_static_prop_fn, &Gd__gd_core_items__HeartContainer::call_static_fn};

void Gd__gd_core_items__MagicStaff::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_manaCost = gd::GdVal::null();
    this->f_tempDamBonus = gd::GdVal::null();
    this->f_permDamBonus = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__MagicStaff::meta() const { return &META_Gd__gd_core_items__MagicStaff; }
gd::GdVal Gd__gd_core_items__MagicStaff::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__MagicStaff::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__MagicStaff::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_manaCost_1815: out = this->f_manaCost; return true;
        case SYM_GEN_tempDamBonus_1816: out = this->f_tempDamBonus; return true;
        case SYM_GEN_permDamBonus_997: out = this->f_permDamBonus; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__MagicStaff::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaCost_1815: this->f_manaCost = val; return true;
        case SYM_GEN_tempDamBonus_1816: this->f_tempDamBonus = val; return true;
        case SYM_GEN_permDamBonus_997: this->f_permDamBonus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__MagicStaff::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__MagicStaff::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__MagicStaff::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__MagicStaff::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_333, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_event, gd::GdVal::null())))) {
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), this->f_tempDamBonus));
        (void)([&]() { gd::GdVal _ca[] = {this->f_permDamBonus}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MagicStaff::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_manaCost = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0);
    this->f_tempDamBonus = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0);
    this->f_permDamBonus = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__MagicStaff(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__MagicStaff>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__MagicStaff = {CLS_Gd__gd_core_items__MagicStaff, "MagicStaff", "res://gd_core_items/MagicStaff.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__MagicStaff, &Gd__gd_core_items__MagicStaff::get_static_prop_fn, &Gd__gd_core_items__MagicStaff::call_static_fn};

void Gd__gd_core_items__PotionBelt::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bag::init_fields(gd_ctx);
    this->f_affectedPotions = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_numConsumed = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__PotionBelt::meta() const { return &META_Gd__gd_core_items__PotionBelt; }
gd::GdVal Gd__gd_core_items__PotionBelt::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__PotionBelt::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__PotionBelt::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_affectedPotions_1965: out = this->f_affectedPotions; return true;
        case SYM_GEN_numConsumed_1966: out = this->f_numConsumed; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__PotionBelt::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedPotions_1965: this->f_affectedPotions = val; return true;
        case SYM_GEN_numConsumed_1966: this->f_numConsumed = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__PotionBelt::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPotionEmptied_1967: return true;
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__PotionBelt::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPotionEmptied_1967: out = fn_onPotionEmptied(args, argc); return true;
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__PotionBelt::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__PotionBelt::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_numConsumed = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)gd::native_inline_call(gd_ctx, this->f_affectedPotions, gd::SYM_clear, nullptr, 0);
    gd::GdVal lv_affectedItems = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0);
    {
        gd::GdVal _t1887 = gd::gd_iter_seq(gd_ctx.arena, lv_affectedItems);
        gd::GdArr* _t1888 = (_t1887.kind == gd::GdVal::Kind::Arr) ? _t1887.arr : nullptr;
        uint32_t _len__t1889 = _t1888 ? _t1888->len : 0u;
        for (uint32_t _t1889 = 0; _t1889 < _len__t1889; ++_t1889) {
            gd::GdVal lv_item = _t1888->data[_t1889];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_920, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, this->f_affectedPotions, gd::SYM_push_back, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[105]), gd::GdVal::from_str(&battle_string_literals[106])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PotionBelt::fn_onPotionEmptied(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__potion = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_numBuffs = gd::GdVal::from_int(0LL);
    gd::GdVal lv_active = gd::GdVal::from_bool(false);
    this->f_numConsumed = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numConsumed, gd::GdVal::from_int(1LL)));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_numConsumed, gd::GdVal::from_int(1LL))))) {
        lv_numBuffs = gd::GdVal::from_int(1LL);
        lv_active = gd::GdVal::from_bool(true);
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_numConsumed, gd::GdVal::from_int(4LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_356, _ca, 1); })();
        lv_active = gd::GdVal::from_bool(true);
    }
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[101])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isTypeInInventory_805, _ca, 1); })())) {
        lv_numBuffs = gd::gd_add(gd_ctx, lv_numBuffs, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[67])}; return gd::native_inline_call(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[101])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })(), SYM_GEN_getP_188, _ca, 1); })()));
        lv_active = gd::GdVal::from_bool(true);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numBuffs, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_numBuffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 1); })();
    }
    if (gd::gd_truth(lv_active)) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PotionBelt::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(11LL)}; return gd::native_inline_call(gd_ctx, lv_toItem, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PotionBelt::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__PotionBelt(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__PotionBelt>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__PotionBelt = {CLS_Gd__gd_core_items__PotionBelt, "PotionBelt", "res://gd_core_items/PotionBelt.gd", &META_Gd__gd_core_items__Bag, true, _alloc_Gd__gd_core_items__PotionBelt, &Gd__gd_core_items__PotionBelt::get_static_prop_fn, &Gd__gd_core_items__PotionBelt::call_static_fn};

void Gd__gd_core_items__StoneHelm::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__LeatherHelm::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__StoneHelm::meta() const { return &META_Gd__gd_core_items__StoneHelm; }
gd::GdVal Gd__gd_core_items__StoneHelm::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__LeatherHelm::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__StoneHelm::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__StoneHelm::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__LeatherHelm::get_prop(prop, out);
}
bool Gd__gd_core_items__StoneHelm::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__LeatherHelm::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__StoneHelm::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getStunProtectChance_1907: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::has_own_method(m);
}
bool Gd__gd_core_items__StoneHelm::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getStunProtectChance_1907: out = fn_getStunProtectChance(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__StoneHelm::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__LeatherHelm::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__StoneHelm::fn_getStunProtectChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StoneHelm::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN_onCombatStart_934, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StoneHelm::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__StoneHelm(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__StoneHelm>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__StoneHelm = {CLS_Gd__gd_core_items__StoneHelm, "StoneHelm", "res://gd_core_items/StoneHelm.gd", &META_Gd__gd_core_items__LeatherHelm, true, _alloc_Gd__gd_core_items__StoneHelm, &Gd__gd_core_items__StoneHelm::get_static_prop_fn, &Gd__gd_core_items__StoneHelm::call_static_fn};

void Gd__gd_core_items__White_EyesBlueDragon::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Card::init_fields(gd_ctx);
    this->f_snowflakes = gd::GdVal::null();
    this->f_damReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__White_EyesBlueDragon::meta() const { return &META_Gd__gd_core_items__White_EyesBlueDragon; }
gd::GdVal Gd__gd_core_items__White_EyesBlueDragon::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Card::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__White_EyesBlueDragon::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__White_EyesBlueDragon::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_snowflakes_2003: out = this->f_snowflakes; return true;
        case SYM_GEN_damReduction_1873: out = this->f_damReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::get_prop(prop, out);
}
bool Gd__gd_core_items__White_EyesBlueDragon::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_snowflakes_2003: this->f_snowflakes = val; return true;
        case SYM_GEN_damReduction_1873: this->f_damReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__White_EyesBlueDragon::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Card::has_own_method(m);
}
bool Gd__gd_core_items__White_EyesBlueDragon::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__White_EyesBlueDragon::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__White_EyesBlueDragon::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), this->f_chainPosition))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_351, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeEffectDamageFactor_1281, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__White_EyesBlueDragon::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Card::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_damReduction = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[83])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__White_EyesBlueDragon(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__White_EyesBlueDragon>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__White_EyesBlueDragon = {CLS_Gd__gd_core_items__White_EyesBlueDragon, "White-EyesBlueDragon", "res://gd_core_items/White-EyesBlueDragon.gd", &META_Gd__gd_core_items__Card, true, _alloc_Gd__gd_core_items__White_EyesBlueDragon, &Gd__gd_core_items__White_EyesBlueDragon::get_static_prop_fn, &Gd__gd_core_items__White_EyesBlueDragon::call_static_fn};
