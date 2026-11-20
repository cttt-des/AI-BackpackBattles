#include "../../native_array_index.hpp"
#include "../../native_event_kernel.hpp"
#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core__Food.hpp"
#include "../hdrs/Gd__gd_core__BurningTorch.hpp"
#include "../hdrs/Gd__gd_core__CoreEventBus.hpp"
#include "../hdrs/Gd__gd_core__Crown.hpp"
#include "../hdrs/Gd__gd_core__EvilCap.hpp"
#include "../hdrs/Gd__gd_core__HeroicPotion.hpp"
#include "../hdrs/Gd__gd_core_items__Piggybank.hpp"
#include "../hdrs/Gd__gd_core__PlatinCustomerCard.hpp"
#include "../hdrs/Gd__gd_core__RubyWhelp.hpp"
#include "../hdrs/Gd__gd_core_items__HealthPotion.hpp"
#include "../hdrs/Gd__gd_core__Whetstone.hpp"
#include "../hdrs/Gd__gd_core_items__BloodAmulet.hpp"
#include "../hdrs/Gd__gd_core_items__Coins.hpp"
#include "../hdrs/Gd__gd_core_items__Eggscalibur.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Anvil.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Bagtacular.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BookofNature.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Cauldron.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Chess__WhitePawn.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Cupcake.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DragonClaws.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__EnchantedWeapons.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ForestDragon.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__GirlPower.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__HyperHedgehog.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__LeafBadge.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MagiteccArmor.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MushroomFarm.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PoisonFrog.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Puzzlebox.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Reverse.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Shielded.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Solaris.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__StaffofFire.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Thornburst.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__UnidentifiedSkill.hpp"
#include "../hdrs/Gd__gd_core_items__FancyFencingRapier.hpp"
#include "../hdrs/Gd__gd_core_items__Hammer.hpp"
#include "../hdrs/Gd__gd_core_items__LuckyClover.hpp"
#include "../hdrs/Gd__gd_core_items__PoisonGoobert.hpp"
#include "../hdrs/Gd__gd_core_items__StaminaSack.hpp"
#include "../hdrs/Gd__gd_core_items__VillainSword.hpp"

namespace {
constexpr gd::GdStr battle_string_literals[] = {
    {"", 0u, 2166136261u},
    {"?", 1u, 973910158u},
    {"isCoreItem", 10u, 3597329357u},
    {"/ot", 3u, 3885608693u},
    {"BUS", 3u, 3834310425u},
    {"emitter=", 8u, 2374018256u},
    {"BUSL", 4u, 464962255u},
    {"BUSD", 4u, 599183207u},
    {"character_mana_changed", 22u, 798563205u},
    {"checkTrigger", 12u, 3751686889u},
    {"character_invulnerable_end", 26u, 3350240732u},
    {"onInvuEnded", 11u, 2135122486u},
    {"dur_invu", 8u, 277695711u},
    {"BuffTimer", 9u, 194754125u},
    {"buffEnded", 9u, 3457903416u},
    {"mana", 4u, 3650585354u},
    {"dur", 3u, 3509645056u},
    {"character_pre_use_stamina", 25u, 4061960724u},
    {"checkStamina", 12u, 3432866148u},
    {"maxhealth", 9u, 429334299u},
    {"Piggy Pinata_CRAFT", 18u, 23902885u},
    {"Piggy Pinata", 12u, 2904436292u},
    {"Hammer", 6u, 3178970599u},
    {"Thors Hammer", 12u, 3528755945u},
    {"heal", 4u, 979982427u},
    {"character_damaged", 17u, 745527748u},
    {"onDamaged", 9u, 2303747743u},
    {"dam", 3u, 4031722721u},
    {"Eggscalibur.gd:9", 16u, 394458383u},
    {"|", 1u, 4178332219u},
    {"ESHUF", 5u, 2622025276u},
    {"t=", 2u, 340066234u},
    {"Flame", 5u, 739594656u},
    {"Fanny Pack", 10u, 1541458896u},
    {"Stamina Sack", 12u, 3135812348u},
    {"Potion Belt", 11u, 3530571787u},
    {"Protective Purse", 16u, 3560043597u},
    {"regen", 5u, 16724762u},
    {"luck", 4u, 4145017712u},
    {"spikes", 6u, 439106706u},
    {"speed", 5u, 2072037248u},
    {"buffs", 5u, 2149256365u},
    {"battle_rage_started", 19u, 3997014835u},
    {"onBattleRageStarted", 19u, 3330696088u},
    {"battle_rage_ended", 17u, 4230921894u},
    {"onBattleRageEnded", 17u, 1252110145u},
    {"character_regeneration_changed", 30u, 2797934681u},
    {"onRegenChanged", 14u, 661197895u},
    {"empower", 7u, 2037162760u},
    {"dam_empower", 11u, 3673063641u},
    {"character_lucky_changed", 23u, 2259242176u},
    {"onLuckyChanged", 14u, 1760969932u},
    {"manat", 5u, 126091098u},
    {"cleanse", 7u, 4032992022u},
    {"block", 5u, 3943480674u},
    {"Fly Agaric", 10u, 3159823061u},
    {"Doom Cap", 8u, 3691411692u},
    {"num", 3u, 242376115u},
    {"onBuffsChanged", 14u, 1288163266u},
    {"poison2", 7u, 848357177u},
    {"mana2", 5u, 3246625064u},
    {"gained", 6u, 52449535u},
    {"used", 4u, 1786277552u},
    {"poison", 6u, 3470992305u},
    {"L", 1u, 3373006507u},
    {"S", 1u, 3591115554u},
    {"Z", 1u, 3742114125u},
    {"T", 1u, 3507227459u},
    {"J", 1u, 3473672221u},
    {"speed2", 6u, 498752822u},
    {"reflect", 7u, 2462546090u},
    {"steal", 5u, 218799968u},
    {"\n", 1u, 252472541u},
    {"CARD_DUPLICATES", 15u, 4183871766u},
    {"CARD_HINT", 9u, 4169059801u},
    {"Shield of Valor", 15u, 644584623u},
    {"chance", 6u, 2459084481u},
    {"blocked", 7u, 1516072627u},
    {"onShieldBlocked", 15u, 2340875007u},
    {"used_heat", 9u, 3089606235u},
    {"onArmorUsedHeat", 15u, 2991089272u},
    {"Sun Shield", 10u, 826446202u},
    {"Sun Armor", 9u, 1667246802u},
    {"Holy Armor", 10u, 4110091228u},
    {"heat", 4u, 577319571u},
    {"character_spikes_changed", 24u, 3463900413u},
    {"onSpikesChanged", 15u, 3715123341u},
    {"dur_stun", 8u, 1388942617u},
    {"max", 3u, 3617776409u},
    {"Exclusive/UnidentifiedSkill.gd:23", 33u, 3479551509u},
    {"identifySkill", 13u, 3093266174u},
    {"round1", 6u, 2041894334u},
    {"round2", 6u, 2025116715u},
    {"TOOLTIP_Always Offered2", 23u, 3965178019u},
    {"\n\n", 2u, 2274317941u},
    {"dropped", 7u, 3229108261u},
    {"onDropped", 9u, 1334518102u},
    {"getSkillPool", 12u, 1868377090u},
    {"luckt", 5u, 4061892428u},
    {"Bagtacular", 10u, 2131747329u},
    {"stamina", 7u, 3875003702u},
};
}

void Gd__gd_core__Food::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__Food::meta() const { return &META_Gd__gd_core__Food; }
gd::GdVal Gd__gd_core__Food::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Food::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Food::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Food::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Food::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_prepare_122: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Food::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_prepare_122: out = fn_prepare(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Food::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Food::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), this->f_descriptor)))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Food::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_prepare_122, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0), gd::GdVal::from_float(0.1))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Food::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Food(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Food>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Food = {CLS_Gd__gd_core__Food, "Food", "res://gd_core/Food.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__Food, &Gd__gd_core__Food::get_static_prop_fn, &Gd__gd_core__Food::call_static_fn};

void Gd__gd_core__BurningTorch::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
    this->f_permDamBonus = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__BurningTorch::meta() const { return &META_Gd__gd_core__BurningTorch; }
gd::GdVal Gd__gd_core__BurningTorch::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__BurningTorch::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__BurningTorch::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_permDamBonus_997: out = this->f_permDamBonus; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__BurningTorch::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_permDamBonus_997: this->f_permDamBonus = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__BurningTorch::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__BurningTorch::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__BurningTorch::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__BurningTorch::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BurningTorch::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_permDamBonus}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BurningTorch::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_permDamBonus = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__BurningTorch(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__BurningTorch>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__BurningTorch = {CLS_Gd__gd_core__BurningTorch, "BurningTorch", "res://gd_core/BurningTorch.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__BurningTorch, &Gd__gd_core__BurningTorch::get_static_prop_fn, &Gd__gd_core__BurningTorch::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreEventBus_LoggingMode[] = {{"None", 0LL}, {"Instant", 1LL}, {"Delayed", 2LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreEventBus_LoggingMode = {"LoggingMode", _ekv_Gd__gd_core__CoreEventBus_LoggingMode, 3u};
void Gd__gd_core__CoreEventBus::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_loggingMode = gd::GdVal::from_int(1LL);
    this->f_signalQueue = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_connections = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_signalIDs = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f__ctx = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__CoreEventBus::meta() const { return &META_Gd__gd_core__CoreEventBus; }
gd::GdVal Gd__gd_core__CoreEventBus::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_LoggingMode_1599: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreEventBus_LoggingMode);
        default: break;
    }
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreEventBus::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreEventBus::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_loggingMode_1584: out = this->f_loggingMode; return true;
        case SYM_GEN_signalQueue_1585: out = this->f_signalQueue; return true;
        case SYM_GEN_connections_1586: out = this->f_connections; return true;
        case SYM_GEN_signalIDs_1587: out = this->f_signalIDs; return true;
        case SYM_GEN__ctx_1347: out = this->f__ctx; return true;
        case SYM_GEN_LoggingMode_1599: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreEventBus_LoggingMode); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreEventBus::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_loggingMode_1584: this->f_loggingMode = val; return true;
        case SYM_GEN_signalQueue_1585: this->f_signalQueue = val; return true;
        case SYM_GEN_connections_1586: this->f_connections = val; return true;
        case SYM_GEN_signalIDs_1587: this->f_signalIDs = val; return true;
        case SYM_GEN__ctx_1347: this->f__ctx = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreEventBus::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_setLoggingMode_1588: return true;
        case SYM_GEN_getLoggingMode_1589: return true;
        case SYM_GEN_queueSignal_1590: return true;
        case SYM_GEN_flushLoggingQueue_1591: return true;
        case SYM_GEN_emitSignal_1592: return true;
        case SYM_GEN_emitEvent_1593: return true;
        case SYM_GEN_logEvent_1357: return true;
        case SYM_GEN_emitAndLog_1594: return true;
        case SYM_GEN_connectEvent_1595: return true;
        case SYM_GEN_getEmissionID_1596: return true;
        case SYM_GEN_disconnectAll_1597: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreEventBus::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_setLoggingMode_1588: out = fn_setLoggingMode(args, argc); return true;
        case SYM_GEN_getLoggingMode_1589: out = fn_getLoggingMode(args, argc); return true;
        case SYM_GEN_queueSignal_1590: out = fn_queueSignal(args, argc); return true;
        case SYM_GEN_flushLoggingQueue_1591: out = fn_flushLoggingQueue(args, argc); return true;
        case SYM_GEN_emitSignal_1592: out = fn_emitSignal(args, argc); return true;
        case SYM_GEN_emitEvent_1593: out = fn_emitEvent(args, argc); return true;
        case SYM_GEN_logEvent_1357: out = fn_logEvent(args, argc); return true;
        case SYM_GEN_emitAndLog_1594: out = fn_emitAndLog(args, argc); return true;
        case SYM_GEN_connectEvent_1595: out = fn_connectEvent(args, argc); return true;
        case SYM_GEN_getEmissionID_1596: out = fn_getEmissionID(args, argc); return true;
        case SYM_GEN_disconnectAll_1597: out = fn_disconnectAll(args, argc); return true;
        case SYM_GEN_Util_dictAppend_1598: out = sf_Util_dictAppend(gd_ctx, args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreEventBus::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_Util_dictAppend_1598: out = sf_Util_dictAppend(gd_ctx, args, argc); return true;
        default: break;
    }
    return false;
}
gd::GdVal Gd__gd_core__CoreEventBus::fn_setLoggingMode(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_mode = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_mode = gd::gd_coerce_int(lv_mode);
    this->f_loggingMode = lv_mode;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEventBus::fn_getLoggingMode(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_loggingMode;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEventBus::fn_queueSignal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_emitter = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_signalName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_arguments = (_argc > 3) ? _args[3] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_emitter, lv_signalName, lv_event, lv_arguments}))}; return gd::call_method(gd_ctx, this->f_signalQueue, gd::SYM_push_back, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEventBus::fn_flushLoggingQueue(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return this->fn_setLoggingMode(_ca, 1); })();
    gd::GdVal lv_queueDuplicate = gd::call_method(gd_ctx, this->f_signalQueue, gd::SYM_duplicate, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_signalQueue, gd::SYM_clear, nullptr, 0);
    {
        gd::GdVal _t1641 = gd::gd_iter_seq(gd_ctx.arena, lv_queueDuplicate);
        gd::GdArr* _t1642 = (_t1641.kind == gd::GdVal::Kind::Arr) ? _t1641.arr : nullptr;
        uint32_t _len__t1643 = _t1642 ? _t1642->len : 0u;
        for (uint32_t _t1643 = 0; _t1643 < _len__t1643; ++_t1643) {
            gd::GdVal lv_tuple = _t1642->data[_t1643];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, lv_tuple, gd::GdVal::from_int(0LL)), gd::native_array_index(gd_ctx, lv_tuple, gd::GdVal::from_int(1LL)), gd::native_array_index(gd_ctx, lv_tuple, gd::GdVal::from_int(2LL)), gd::native_array_index(gd_ctx, lv_tuple, gd::GdVal::from_int(3LL))}; return this->fn_emitAndLog(_ca, 4); })();
        }
    }
    return gd::GdVal::null();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setLoggingMode_1588, _ca, 1); })();
    gd::GdVal lv_queueDuplicate = gd::call_method(gd_ctx, this->f_signalQueue, gd::SYM_duplicate, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_signalQueue, gd::SYM_clear, nullptr, 0);
    {
        gd::GdVal _t1641 = gd::gd_iter_seq(gd_ctx.arena, lv_queueDuplicate);
        gd::GdArr* _t1642 = (_t1641.kind == gd::GdVal::Kind::Arr) ? _t1641.arr : nullptr;
        uint32_t _len__t1643 = _t1642 ? _t1642->len : 0u;
        for (uint32_t _t1643 = 0; _t1643 < _len__t1643; ++_t1643) {
            gd::GdVal lv_tuple = _t1642->data[_t1643];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, lv_tuple, gd::GdVal::from_int(0LL)), gd::native_array_index(gd_ctx, lv_tuple, gd::GdVal::from_int(1LL)), gd::native_array_index(gd_ctx, lv_tuple, gd::GdVal::from_int(2LL)), gd::native_array_index(gd_ctx, lv_tuple, gd::GdVal::from_int(3LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_emitAndLog_1594, _ca, 4); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEventBus::fn_emitSignal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_emitter = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_signalName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_arguments = (_argc > 2) ? _args[2] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    (void)([&]() { gd::GdVal _ca[] = {lv_emitter, lv_signalName, gd::GdVal::null(), lv_arguments}; return this->fn_emitEvent(_ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEventBus::fn_emitEvent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_emitter = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_signalName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_arguments = (_argc > 3) ? _args[3] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_loggingMode, gd::GdVal::from_int(2))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_emitter, lv_signalName, lv_event, lv_arguments}; return this->fn_queueSignal(_ca, 4); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {lv_emitter, lv_signalName, lv_event, lv_arguments}; return this->fn_emitAndLog(_ca, 4); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEventBus::fn_logEvent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_loggingMode, gd::GdVal::from_int(2))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_str(&battle_string_literals[0]), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return this->fn_queueSignal(_ca, 4); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_str(&battle_string_literals[0]), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return this->fn_emitAndLog(_ca, 4); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEventBus::fn_emitAndLog(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
        ++gd_ctx.native_event_counts[0];
    gd::GdVal lv_emitter = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_signalName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_arguments = (_argc > 3) ? _args[3] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_event, gd::GdVal::null())))) {
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_fight_ended>(gd_ctx, this->f__ctx, SYM_GEN_fight_ended_1305))))) {
            if (gd::gd_truth(native_event_get<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::f_oracle_trace>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, lv_event, SYM_GEN_type_1005)}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_trace_event>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN_trace_event_1740, _ca, 1); })();
            }
            (void)([&]() { gd::GdVal _ca[] = {lv_event}; return native_event_call<Gd__gd_core__CoreCombatLog, &Gd__gd_core__CoreCombatLog::fn_logEvent>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_combat_log>(gd_ctx, this->f__ctx, SYM_GEN_combat_log_1410), SYM_GEN_logEvent_1357, _ca, 1); })();
        }
    }
    if (lv_emitter.is_null()) return gd::GdVal::null();
    gd::GdVal lv_signalID;
    if (this->f_signalIDs.kind == gd::GdVal::Kind::Dict && this->f_signalIDs.dict) {
        const auto* signals = this->f_signalIDs.dict;
        const auto index = signals->find_index(lv_signalName);
        if (index < 0) return gd::GdVal::null();
        lv_signalID = signals->entries[index].val;
    } else {
        if (!gd::gd_truth(gd::gd_in(lv_signalName, this->f_signalIDs))) return gd::GdVal::null();
        lv_signalID = gd::native_array_index(gd_ctx, this->f_signalIDs, lv_signalName);
    }
    gd::GdVal lv_emissionID = ([&]() { gd::GdVal _ca[] = {lv_emitter, lv_signalID}; return this->fn_getEmissionID(_ca, 2); })();
    const auto bus_trace_enabled = [&] {
        const auto rng = native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f__ctx, SYM_GEN_rng_1406);
        return gd::gd_truth(gd::get_prop(gd_ctx, rng, SYM_GEN_oracle_trace_1729))
            && gd::gd_truth(gd::get_prop(gd_ctx, rng, SYM_GEN__stacktrace_1731));
    };
    gd::GdVal lv__bus_list;
    if (this->f_connections.kind == gd::GdVal::Kind::Dict && this->f_connections.dict) {
        const auto* connections = this->f_connections.dict;
        const auto index = connections->find_index(lv_emissionID);
        if (index < 0) {
            if (!bus_trace_enabled()) return gd::GdVal::null();
            lv__bus_list = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
        } else {
            lv__bus_list = connections->entries[index].val;
            if (lv__bus_list.kind == gd::GdVal::Kind::Arr && lv__bus_list.arr
                    && lv__bus_list.arr->len == 0 && !bus_trace_enabled()) return gd::GdVal::null();
        }
    } else {
        lv__bus_list = ([&]() { gd::GdVal _ca[] = {lv_emissionID, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, this->f_connections, gd::SYM_get, _ca, 2); })();
    }
    if (gd::gd_truth((gd::gd_truth(native_event_get<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::f_oracle_trace>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729)) ? gd::GdVal::from_bool(gd::gd_truth(native_event_get<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::f__stacktrace>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN__stacktrace_1731))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv__eid = gd::GdVal::from_str(&battle_string_literals[1]);
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_emitter, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[2])}; return gd::call_method(gd_ctx, lv_emitter, gd::SYM_has_method, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
            lv__eid = gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv_emitter, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[3])), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(gd::get_prop(gd_ctx, lv_emitter, SYM_GEN_ownerType_49))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, lv_signalName)), ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, lv__bus_list, gd::SYM_size, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[5]), lv__eid)}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_trace_diag>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    }
    gd::GdVal lv__bus_i = gd::GdVal::from_int(0LL);
    gd::GdVal lv__eid2 = gd::GdVal::from_str(&battle_string_literals[1]);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_emitter, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[2])}; return gd::call_method(gd_ctx, lv_emitter, gd::SYM_has_method, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        lv__eid2 = gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv_emitter, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[3])), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(gd::get_prop(gd_ctx, lv_emitter, SYM_GEN_ownerType_49))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
    }
    {
        gd::GdVal _t1644 = gd::gd_iter_seq(gd_ctx.arena, lv__bus_list);
        gd::GdArr* _t1645 = (_t1644.kind == gd::GdVal::Kind::Arr) ? _t1644.arr : nullptr;
        uint32_t _len__t1646 = _t1645 ? _t1645->len : 0u;
        for (uint32_t _t1646 = 0; _t1646 < _len__t1646; ++_t1646) {
            gd::GdVal lv__bus_pair = _t1645->data[_t1646];
            if (gd::gd_truth(native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_fight_ended>(gd_ctx, this->f__ctx, SYM_GEN_fight_ended_1305))) {
                return gd::GdVal::null();
            }
            if (gd::gd_truth((gd::gd_truth(native_event_get<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::f_oracle_trace>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729)) ? gd::GdVal::from_bool(gd::gd_truth(native_event_get<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::f__stacktrace>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN__stacktrace_1731))) : gd::GdVal::from_bool(false)))) {
                gd::GdVal lv__rid = gd::GdVal::from_str(&battle_string_literals[1]);
                gd::GdVal lv__recv = gd::native_array_index(gd_ctx, lv__bus_pair, gd::GdVal::from_int(1LL));
                if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv__recv, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[2])}; return gd::call_method(gd_ctx, lv__recv, gd::SYM_has_method, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
                    lv__rid = gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv__recv, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[3])), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(gd::get_prop(gd_ctx, lv__recv, SYM_GEN_ownerType_49))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
                }
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, lv_signalName)), ([&]() { gd::GdVal _ca[] = {lv__bus_i}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), lv__rid}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_trace_diag>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
            }
            lv__bus_i = gd::gd_add(gd_ctx, lv__bus_i, gd::GdVal::from_int(1LL));
            (void)([&]() { gd::GdVal _ca[] = {lv_arguments}; return native_event_funcv(gd_ctx, gd::native_array_index(gd_ctx, lv__bus_pair, gd::GdVal::from_int(0LL)), _ca, 1); })();
        }
    }
    if (gd::gd_truth((gd::gd_truth(native_event_get<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::f_oracle_trace>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729)) ? gd::GdVal::from_bool(gd::gd_truth(native_event_get<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::f__stacktrace>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN__stacktrace_1731))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, lv_signalName)), ([&]() { gd::GdVal _ca[] = {lv__bus_i}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[5]), lv__eid2)}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_trace_diag>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    }
    return gd::GdVal::null();
    }
    gd::GdVal lv_emitter = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_signalName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_arguments = (_argc > 3) ? _args[3] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_event, gd::GdVal::null())))) {
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_fight_ended_1305))))) {
            if (gd::gd_truth(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, lv_event, SYM_GEN_type_1005)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN_trace_event_1740, _ca, 1); })();
            }
            (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_combat_log_1410), SYM_GEN_logEvent_1357, _ca, 1); })();
        }
    }
    if (lv_emitter.is_null()) return gd::GdVal::null();
    gd::GdVal lv_signalID;
    if (this->f_signalIDs.kind == gd::GdVal::Kind::Dict && this->f_signalIDs.dict) {
        const auto* signals = this->f_signalIDs.dict;
        const auto index = signals->find_index(lv_signalName);
        if (index < 0) return gd::GdVal::null();
        lv_signalID = signals->entries[index].val;
    } else {
        if (!gd::gd_truth(gd::gd_in(lv_signalName, this->f_signalIDs))) return gd::GdVal::null();
        lv_signalID = gd::native_array_index(gd_ctx, this->f_signalIDs, lv_signalName);
    }
    gd::GdVal lv_emissionID = ([&]() { gd::GdVal _ca[] = {lv_emitter, lv_signalID}; return this->fn_getEmissionID(_ca, 2); })();
    const auto bus_trace_enabled = [&] {
        const auto rng = gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1406);
        return gd::gd_truth(gd::get_prop(gd_ctx, rng, SYM_GEN_oracle_trace_1729))
            && gd::gd_truth(gd::get_prop(gd_ctx, rng, SYM_GEN__stacktrace_1731));
    };
    gd::GdVal lv__bus_list;
    if (this->f_connections.kind == gd::GdVal::Kind::Dict && this->f_connections.dict) {
        const auto* connections = this->f_connections.dict;
        const auto index = connections->find_index(lv_emissionID);
        if (index < 0) {
            if (!bus_trace_enabled()) return gd::GdVal::null();
            lv__bus_list = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
        } else {
            lv__bus_list = connections->entries[index].val;
            if (lv__bus_list.kind == gd::GdVal::Kind::Arr && lv__bus_list.arr
                    && lv__bus_list.arr->len == 0 && !bus_trace_enabled()) return gd::GdVal::null();
        }
    } else {
        lv__bus_list = ([&]() { gd::GdVal _ca[] = {lv_emissionID, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, this->f_connections, gd::SYM_get, _ca, 2); })();
    }
    if (gd::gd_truth((gd::gd_truth(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729)) ? gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN__stacktrace_1731))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv__eid = gd::GdVal::from_str(&battle_string_literals[1]);
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_emitter, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[2])}; return gd::call_method(gd_ctx, lv_emitter, gd::SYM_has_method, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
            lv__eid = gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv_emitter, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[3])), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(gd::get_prop(gd_ctx, lv_emitter, SYM_GEN_ownerType_49))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, lv_signalName)), ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, lv__bus_list, gd::SYM_size, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[5]), lv__eid)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    }
    gd::GdVal lv__bus_i = gd::GdVal::from_int(0LL);
    gd::GdVal lv__eid2 = gd::GdVal::from_str(&battle_string_literals[1]);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_emitter, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[2])}; return gd::call_method(gd_ctx, lv_emitter, gd::SYM_has_method, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        lv__eid2 = gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv_emitter, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[3])), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(gd::get_prop(gd_ctx, lv_emitter, SYM_GEN_ownerType_49))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
    }
    {
        gd::GdVal _t1644 = gd::gd_iter_seq(gd_ctx.arena, lv__bus_list);
        gd::GdArr* _t1645 = (_t1644.kind == gd::GdVal::Kind::Arr) ? _t1644.arr : nullptr;
        uint32_t _len__t1646 = _t1645 ? _t1645->len : 0u;
        for (uint32_t _t1646 = 0; _t1646 < _len__t1646; ++_t1646) {
            gd::GdVal lv__bus_pair = _t1645->data[_t1646];
            if (gd::gd_truth(gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_fight_ended_1305))) {
                return gd::GdVal::null();
            }
            if (gd::gd_truth((gd::gd_truth(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729)) ? gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN__stacktrace_1731))) : gd::GdVal::from_bool(false)))) {
                gd::GdVal lv__rid = gd::GdVal::from_str(&battle_string_literals[1]);
                gd::GdVal lv__recv = gd::native_array_index(gd_ctx, lv__bus_pair, gd::GdVal::from_int(1LL));
                if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv__recv, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[2])}; return gd::call_method(gd_ctx, lv__recv, gd::SYM_has_method, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
                    lv__rid = gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv__recv, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[3])), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(gd::get_prop(gd_ctx, lv__recv, SYM_GEN_ownerType_49))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
                }
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, lv_signalName)), ([&]() { gd::GdVal _ca[] = {lv__bus_i}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), lv__rid}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
            }
            lv__bus_i = gd::gd_add(gd_ctx, lv__bus_i, gd::GdVal::from_int(1LL));
            (void)([&]() { gd::GdVal _ca[] = {lv_arguments}; return gd::call_method(gd_ctx, gd::native_array_index(gd_ctx, lv__bus_pair, gd::GdVal::from_int(0LL)), gd::SYM_call_funcv, _ca, 1); })();
        }
    }
    if (gd::gd_truth((gd::gd_truth(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729)) ? gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN__stacktrace_1731))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, lv_signalName)), ([&]() { gd::GdVal _ca[] = {lv__bus_i}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[5]), lv__eid2)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEventBus::fn_connectEvent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_emitter = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_signalName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_receiver = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_method = (_argc > 3) ? _args[3] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_signalName, this->f_signalIDs))))) {
        { gd::GdVal _t1647 = this->f_signalIDs; gd::GdVal _t1648 = lv_signalName; gd::set_index(gd_ctx, _t1647, _t1648, gd::call_method(gd_ctx, this->f_signalIDs, gd::SYM_size, nullptr, 0)); }
    }
    gd::GdVal lv_signalID = gd::native_array_index(gd_ctx, this->f_signalIDs, lv_signalName);
    gd::GdVal lv_emissionID = ([&]() { gd::GdVal _ca[] = {lv_emitter, lv_signalID}; return this->fn_getEmissionID(_ca, 2); })();
    gd::GdVal lv_funcRef = gd::GdVal::from_funcref(gd_ctx.arena.make<gd::GdFuncRef>());
    (void)([&]() { gd::GdVal _ca[] = {lv_method}; return gd::call_method(gd_ctx, lv_funcRef, gd::SYM_set_function, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_receiver}; return gd::call_method(gd_ctx, lv_funcRef, gd::SYM_set_instance, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_connections, lv_emissionID, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_funcRef, lv_receiver}))}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreEventBus::call_static_fn(gd_ctx, SYM_GEN_Util_dictAppend_1598, _ca, 3, _out); return _out; })();
    return gd::GdVal::null();
    }
    gd::GdVal lv_emitter = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_signalName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_receiver = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_method = (_argc > 3) ? _args[3] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_signalName, this->f_signalIDs))))) {
        { gd::GdVal _t1647 = this->f_signalIDs; gd::GdVal _t1648 = lv_signalName; gd::set_index(gd_ctx, _t1647, _t1648, gd::call_method(gd_ctx, this->f_signalIDs, gd::SYM_size, nullptr, 0)); }
    }
    gd::GdVal lv_signalID = gd::native_array_index(gd_ctx, this->f_signalIDs, lv_signalName);
    gd::GdVal lv_emissionID = ([&]() { gd::GdVal _ca[] = {lv_emitter, lv_signalID}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getEmissionID_1596, _ca, 2); })();
    gd::GdVal lv_funcRef = gd::GdVal::from_funcref(gd_ctx.arena.make<gd::GdFuncRef>());
    (void)([&]() { gd::GdVal _ca[] = {lv_method}; return gd::call_method(gd_ctx, lv_funcRef, gd::SYM_set_function, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_receiver}; return gd::call_method(gd_ctx, lv_funcRef, gd::SYM_set_instance, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_connections, lv_emissionID, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_funcRef, lv_receiver}))}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreEventBus::call_static_fn(gd_ctx, SYM_GEN_Util_dictAppend_1598, _ca, 3, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEventBus::fn_getEmissionID(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_emitter = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_signalID = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_signalID = gd::gd_coerce_int(lv_signalID);
    gd::GdVal lv_ID = gd::call_method(gd_ctx, lv_emitter, gd::SYM_get_instance_id, nullptr, 0);
    lv_ID = gd::gd_add(gd_ctx, lv_ID, gd::gd_shl(lv_signalID, gd::GdVal::from_int(32LL)));
    return lv_ID;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEventBus::fn_disconnectAll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_connections, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEventBus::sf_Util_dictAppend(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dict = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_key = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 2) ? _args[2] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_key, lv_dict))))) {
        { gd::GdVal _t1649 = lv_dict; gd::GdVal _t1650 = lv_key; gd::set_index(gd_ctx, _t1649, _t1650, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))); }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_value}; return gd::call_method(gd_ctx, gd::native_array_index(gd_ctx, lv_dict, lv_key), gd::SYM_push_back, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreEventBus(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreEventBus>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__CoreEventBus = {CLS_Gd__gd_core__CoreEventBus, "CoreEventBus", "res://gd_core/CoreEventBus.gd", nullptr, false, _alloc_Gd__gd_core__CoreEventBus, &Gd__gd_core__CoreEventBus::get_static_prop_fn, &Gd__gd_core__CoreEventBus::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core__Crown_CrownState[] = {{"Inactive", 0LL}, {"Active", 1LL}, {"Used", 2LL}};
static const gd::GdEnum _enum_Gd__gd_core__Crown_CrownState = {"CrownState", _ekv_Gd__gd_core__Crown_CrownState, 3u};
void Gd__gd_core__Crown::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_crownState = gd::GdVal::from_int(0);
    this->f_activationParticles = gd::GdVal::null();
    this->f_buffTimer = gd::GdVal::null();
    this->f_manaCost = gd::GdVal::null();
    this->f_light = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__Crown::meta() const { return &META_Gd__gd_core__Crown; }
gd::GdVal Gd__gd_core__Crown::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_CrownState_1822: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Crown_CrownState);
        default: break;
    }
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Crown::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Crown::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_crownState_1818: out = this->f_crownState; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_buffTimer_1819: out = this->f_buffTimer; return true;
        case SYM_GEN_manaCost_1815: out = this->f_manaCost; return true;
        case SYM_GEN_light_949: out = this->f_light; return true;
        case SYM_GEN_CrownState_1822: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Crown_CrownState); return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Crown::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_crownState_1818: this->f_crownState = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_buffTimer_1819: this->f_buffTimer = val; return true;
        case SYM_GEN_manaCost_1815: this->f_manaCost = val; return true;
        case SYM_GEN_light_949: this->f_light = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Crown::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onInvuEnded_1820: return true;
        case SYM_GEN_checkTrigger_1821: return true;
        case SYM_GEN_buffEnded_1817: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Crown::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onInvuEnded_1820: out = fn_onInvuEnded(args, argc); return true;
        case SYM_GEN_checkTrigger_1821: out = fn_checkTrigger(args, argc); return true;
        case SYM_GEN_buffEnded_1817: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Crown::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Crown::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[8]), gd::GdVal::from_str(&battle_string_literals[9])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[10]), gd::GdVal::from_str(&battle_string_literals[11])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crown::fn_onInvuEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkTrigger_1821, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crown::fn_checkTrigger(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_crownState, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_isVulnerable_1291, nullptr, 0))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkMana_331, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
        gd::GdVal lv_invuDur = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[12])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })();
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_invuDur, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_makeInvulnerable_1211, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_invuDur}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1779, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_manaCost, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crown::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crown::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseBlind_344, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crown::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crown::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crown::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__crownState = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__crownState, gd::GdVal::from_int(0LL))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__crownState, gd::GdVal::from_int(1LL))))) {
    }
    else {
    }
    this->f_crownState = gd::gd_coerce_int(lv__crownState);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crown::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[13]), gd::GdVal::from_str(&battle_string_literals[14]), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_manaCost = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[15])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Crown(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Crown>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Crown = {CLS_Gd__gd_core__Crown, "Crown", "res://gd_core/Crown.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__Crown, &Gd__gd_core__Crown::get_static_prop_fn, &Gd__gd_core__Crown::call_static_fn};

void Gd__gd_core__EvilCap::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_nullifyApplied = gd::GdVal::from_bool(false);
    this->f_buffsActive = gd::GdVal::from_int(0LL);
    this->f_buffTimer = gd::GdVal::null();
    this->f_activationParticles = gd::GdVal::null();
    this->f_damReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__EvilCap::meta() const { return &META_Gd__gd_core__EvilCap; }
gd::GdVal Gd__gd_core__EvilCap::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__EvilCap::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__EvilCap::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_nullifyApplied_1871: out = this->f_nullifyApplied; return true;
        case SYM_GEN_buffsActive_1872: out = this->f_buffsActive; return true;
        case SYM_GEN_buffTimer_1819: out = this->f_buffTimer; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_damReduction_1873: out = this->f_damReduction; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__EvilCap::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_nullifyApplied_1871: this->f_nullifyApplied = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_buffsActive_1872: this->f_buffsActive = val; return true;
        case SYM_GEN_buffTimer_1819: this->f_buffTimer = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_damReduction_1873: this->f_damReduction = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__EvilCap::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreCombatStart_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_buffEnded_1817: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__EvilCap::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreCombatStart_125: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_buffEnded_1817: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__EvilCap::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__EvilCap::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_reduceHealingEfficiency_1183, _ca, 1); })();
    this->f_nullifyApplied = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__EvilCap::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__EvilCap::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_nullifyApplied)))) {
        this->f_nullifyApplied = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeBuffNullifyChances_1288, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[16])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1779, _ca, 1); })();
    this->f_buffsActive = gd::gd_add(gd_ctx, this->f_buffsActive, gd::GdVal::from_int(1LL));
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__EvilCap::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
    this->f_buffsActive = gd::gd_sub(this->f_buffsActive, gd::GdVal::from_int(1LL));
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__EvilCap::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__EvilCap::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_buffsActive = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__EvilCap::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__buffsActive = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv__buffsActive, gd::GdVal::from_int(0LL))))) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__EvilCap::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[13]), gd::GdVal::from_str(&battle_string_literals[14]), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_damReduction = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__EvilCap(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__EvilCap>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__EvilCap = {CLS_Gd__gd_core__EvilCap, "EvilCap", "res://gd_core/EvilCap.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__EvilCap, &Gd__gd_core__EvilCap::get_static_prop_fn, &Gd__gd_core__EvilCap::call_static_fn};

void Gd__gd_core__HeroicPotion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Potion::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__HeroicPotion::meta() const { return &META_Gd__gd_core__HeroicPotion; }
gd::GdVal Gd__gd_core__HeroicPotion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Potion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__HeroicPotion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__HeroicPotion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Potion::get_prop(prop, out);
}
bool Gd__gd_core__HeroicPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__HeroicPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_checkStamina_1893: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Potion::has_own_method(m);
}
bool Gd__gd_core__HeroicPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_checkStamina_1893: out = fn_checkStamina(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Potion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__HeroicPotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Potion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__HeroicPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_318, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeroicPotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[17]), gd::GdVal::from_str(&battle_string_literals[18])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeroicPotion::fn_checkStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getCurrentStamina_1262, nullptr, 0), lv_amount)))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1848, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeroicPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Potion::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__HeroicPotion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__HeroicPotion>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__HeroicPotion = {CLS_Gd__gd_core__HeroicPotion, "HeroicPotion", "res://gd_core/HeroicPotion.gd", &META_Gd__gd_core__Potion, false, _alloc_Gd__gd_core__HeroicPotion, &Gd__gd_core__HeroicPotion::get_static_prop_fn, &Gd__gd_core__HeroicPotion::call_static_fn};

void Gd__gd_core_items__Piggybank::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_piggyPinataDescriptor = gd::GdVal::null();
    this->f_hammerDescriptor = gd::GdVal::null();
    this->f_thorsHammerDescriptor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Piggybank::meta() const { return &META_Gd__gd_core_items__Piggybank; }
gd::GdVal Gd__gd_core_items__Piggybank::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Piggybank::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Piggybank::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_piggyPinataDescriptor_1918: out = this->f_piggyPinataDescriptor; return true;
        case SYM_GEN_hammerDescriptor_1919: out = this->f_hammerDescriptor; return true;
        case SYM_GEN_thorsHammerDescriptor_1920: out = this->f_thorsHammerDescriptor; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Piggybank::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_piggyPinataDescriptor_1918: this->f_piggyPinataDescriptor = val; return true;
        case SYM_GEN_hammerDescriptor_1919: this->f_hammerDescriptor = val; return true;
        case SYM_GEN_thorsHammerDescriptor_1920: this->f_thorsHammerDescriptor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Piggybank::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_explodeRandomly_1921: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_hasPinata_1922: return true;
        case SYM_GEN_isSmashRecipe_1923: return true;
        case SYM_GEN_getFusionItemName_836: return true;
        case SYM_GEN_allowGeneratingFusionItem_846: return true;
        case SYM_GEN_explode_1924: return true;
        case SYM_GEN_finishFusing_845: return true;
        case SYM_GEN_getShopPriority_853: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Piggybank::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_explodeRandomly_1921: out = fn_explodeRandomly(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_hasPinata_1922: out = fn_hasPinata(args, argc); return true;
        case SYM_GEN_isSmashRecipe_1923: out = fn_isSmashRecipe(args, argc); return true;
        case SYM_GEN_getFusionItemName_836: out = fn_getFusionItemName(args, argc); return true;
        case SYM_GEN_allowGeneratingFusionItem_846: out = fn_allowGeneratingFusionItem(args, argc); return true;
        case SYM_GEN_explode_1924: out = fn_explode(args, argc); return true;
        case SYM_GEN_finishFusing_845: out = fn_finishFusing(args, argc); return true;
        case SYM_GEN_getShopPriority_853: out = fn_getShopPriority(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Piggybank::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Piggybank::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveGold_754, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_explodeRandomly_1921, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Piggybank::fn_explodeRandomly(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBaseItem_258, nullptr, 0)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBoundAsIngredient_260, nullptr, 0))))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasPinata_1922, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_piggyPinataDescriptor, SYM_GEN_shopChance_1683)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_flipPercent_1736, _ca, 1); })())) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_explode_1924, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_removeItem_1619, _ca, 1); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_discard_764, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Piggybank::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasStartofBattle_126, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Piggybank::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[19])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_381, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Piggybank::fn_hasPinata(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {this->f_piggyPinataDescriptor}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_isItemInInventory_1671, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Piggybank::fn_isSmashRecipe(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::native_array_index(gd_ctx, gd::get_prop(gd_ctx, this->f_curRecipe, SYM_GEN_ingredients_2867), gd::GdVal::from_int(0LL)), this->f_hammerDescriptor))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::native_array_index(gd_ctx, gd::get_prop(gd_ctx, this->f_curRecipe, SYM_GEN_ingredients_2867), gd::GdVal::from_int(0LL)), this->f_thorsHammerDescriptor)))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Piggybank::fn_getFusionItemName(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isSmashRecipe_1923, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasPinata_1922, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[20])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_tr_2826, _ca, 1); })();
    }
    return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getFusionItemName_836, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Piggybank::fn_allowGeneratingFusionItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isSmashRecipe_1923, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasPinata_1922, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        return gd::GdVal::from_bool(false);
    }
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Piggybank::fn_explode(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Piggybank::fn_finishFusing(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isSmashRecipe_1923, nullptr, 0))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_explode_1924, nullptr, 0);
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_finishFusing_845, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Piggybank::fn_getShopPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(-10000LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Piggybank::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_piggyPinataDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[21])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_hammerDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[22])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_thorsHammerDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[23])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Piggybank(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Piggybank>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Piggybank = {CLS_Gd__gd_core_items__Piggybank, "Piggybank", "res://gd_core_items/Piggybank.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Piggybank, &Gd__gd_core_items__Piggybank::get_static_prop_fn, &Gd__gd_core_items__Piggybank::call_static_fn};

void Gd__gd_core__PlatinCustomerCard::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__PlatinCustomerCard::meta() const { return &META_Gd__gd_core__PlatinCustomerCard; }
gd::GdVal Gd__gd_core__PlatinCustomerCard::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__PlatinCustomerCard::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__PlatinCustomerCard::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__PlatinCustomerCard::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__PlatinCustomerCard::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPreCombatStart_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onCalcTradeChance_1825: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__PlatinCustomerCard::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPreCombatStart_125: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onCalcTradeChance_1825: out = fn_onCalcTradeChance(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__PlatinCustomerCard::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__PlatinCustomerCard::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, lv_item, SYM_GEN_getRarity_236, nullptr, 0), gd::GdVal::from_int(3LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PlatinCustomerCard::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveReflectStacks_200, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PlatinCustomerCard::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PlatinCustomerCard::fn_onCalcTradeChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PlatinCustomerCard::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__PlatinCustomerCard(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__PlatinCustomerCard>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__PlatinCustomerCard = {CLS_Gd__gd_core__PlatinCustomerCard, "PlatinCustomerCard", "res://gd_core/PlatinCustomerCard.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__PlatinCustomerCard, &Gd__gd_core__PlatinCustomerCard::get_static_prop_fn, &Gd__gd_core__PlatinCustomerCard::call_static_fn};

void Gd__gd_core__RubyWhelp::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__RubyWhelp::meta() const { return &META_Gd__gd_core__RubyWhelp; }
gd::GdVal Gd__gd_core__RubyWhelp::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__RubyWhelp::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__RubyWhelp::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__RubyWhelp::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__RubyWhelp::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreCombatStart_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__RubyWhelp::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreCombatStart_125: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__RubyWhelp::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__RubyWhelp::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveReflectStacks_200, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RubyWhelp::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RubyWhelp::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__RubyWhelp(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__RubyWhelp>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__RubyWhelp = {CLS_Gd__gd_core__RubyWhelp, "RubyWhelp", "res://gd_core/RubyWhelp.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__RubyWhelp, &Gd__gd_core__RubyWhelp::get_static_prop_fn, &Gd__gd_core__RubyWhelp::call_static_fn};

void Gd__gd_core_items__HealthPotion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Potion::init_fields(gd_ctx);
    this->f_healthThreshold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__HealthPotion::meta() const { return &META_Gd__gd_core_items__HealthPotion; }
gd::GdVal Gd__gd_core_items__HealthPotion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Potion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__HealthPotion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__HealthPotion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_healthThreshold_1854: out = this->f_healthThreshold; return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::get_prop(prop, out);
}
bool Gd__gd_core_items__HealthPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_healthThreshold_1854: this->f_healthThreshold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__HealthPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onDamaged_1855: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::has_own_method(m);
}
bool Gd__gd_core_items__HealthPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1855: out = fn_onDamaged(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__HealthPotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Potion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__HealthPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[24])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleansePoison_342, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HealthPotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[25]), gd::GdVal::from_str(&battle_string_literals[26])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HealthPotion::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__healthChange = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRelativeHealth_302, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1848, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HealthPotion::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(1000LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HealthPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Potion::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_healthThreshold = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__HealthPotion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__HealthPotion>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__HealthPotion = {CLS_Gd__gd_core_items__HealthPotion, "HealthPotion", "res://gd_core_items/HealthPotion.gd", &META_Gd__gd_core_items__Potion, true, _alloc_Gd__gd_core_items__HealthPotion, &Gd__gd_core_items__HealthPotion::get_static_prop_fn, &Gd__gd_core_items__HealthPotion::call_static_fn};

void Gd__gd_core__Whetstone::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_dam = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__Whetstone::meta() const { return &META_Gd__gd_core__Whetstone; }
gd::GdVal Gd__gd_core__Whetstone::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Whetstone::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Whetstone::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_dam_939: out = this->f_dam; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Whetstone::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_dam_939: this->f_dam = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Whetstone::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Whetstone::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Whetstone::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Whetstone::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Whetstone::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1651 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1652 = (_t1651.kind == gd::GdVal::Kind::Arr) ? _t1651.arr : nullptr;
        uint32_t _len__t1653 = _t1652 ? _t1652->len : 0u;
        for (uint32_t _t1653 = 0; _t1653 < _len__t1653; ++_t1653) {
            gd::GdVal lv_item = _t1652->data[_t1653];
            (void)([&]() { gd::GdVal _ca[] = {this->f_dam}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Whetstone::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_dam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[27])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Whetstone(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Whetstone>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Whetstone = {CLS_Gd__gd_core__Whetstone, "Whetstone", "res://gd_core/Whetstone.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__Whetstone, &Gd__gd_core__Whetstone::get_static_prop_fn, &Gd__gd_core__Whetstone::call_static_fn};

void Gd__gd_core_items__BloodAmulet::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__BloodAmulet::meta() const { return &META_Gd__gd_core_items__BloodAmulet; }
gd::GdVal Gd__gd_core_items__BloodAmulet::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__BloodAmulet::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__BloodAmulet::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__BloodAmulet::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__BloodAmulet::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__BloodAmulet::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__BloodAmulet::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__BloodAmulet::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BloodAmulet::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__BloodAmulet(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__BloodAmulet>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__BloodAmulet = {CLS_Gd__gd_core_items__BloodAmulet, "BloodAmulet", "res://gd_core_items/BloodAmulet.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__BloodAmulet, &Gd__gd_core_items__BloodAmulet::get_static_prop_fn, &Gd__gd_core_items__BloodAmulet::call_static_fn};

void Gd__gd_core_items__Coins::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Coins::meta() const { return &META_Gd__gd_core_items__Coins; }
gd::GdVal Gd__gd_core_items__Coins::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Coins::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Coins::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Coins::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Coins::has_own_method(gd::SymId m) const {
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Coins::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Coins::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
static gd::GdObj* _alloc_Gd__gd_core_items__Coins(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Coins>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Coins = {CLS_Gd__gd_core_items__Coins, "Coins", "res://gd_core_items/Coins.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Coins, &Gd__gd_core_items__Coins::get_static_prop_fn, &Gd__gd_core_items__Coins::call_static_fn};

void Gd__gd_core_items__Eggscalibur::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Pan::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Eggscalibur::meta() const { return &META_Gd__gd_core_items__Eggscalibur; }
gd::GdVal Gd__gd_core_items__Eggscalibur::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Pan::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Eggscalibur::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Eggscalibur::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Pan::get_prop(prop, out);
}
bool Gd__gd_core_items__Eggscalibur::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Pan::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Eggscalibur::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Pan::has_own_method(m);
}
bool Gd__gd_core_items__Eggscalibur::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Pan::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Eggscalibur::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Pan::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Eggscalibur::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_333, _ca, 2); })();
    if (gd::gd_truth(lv_event)) {
        gd::GdVal lv_affected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_affected, gd::GdVal::from_str(&battle_string_literals[28])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_shuffleEngine_1747, _ca, 2); })();
        gd::GdVal lv__ids = gd::GdVal::from_str(&battle_string_literals[0]);
        {
            gd::GdVal _t1654 = gd::gd_iter_seq(gd_ctx.arena, lv_affected);
            gd::GdArr* _t1655 = (_t1654.kind == gd::GdVal::Kind::Arr) ? _t1654.arr : nullptr;
            uint32_t _len__t1656 = _t1655 ? _t1655->len : 0u;
            for (uint32_t _t1656 = 0; _t1656 < _len__t1656; ++_t1656) {
                gd::GdVal lv_food = _t1655->data[_t1656];
                lv__ids = gd::gd_add(gd_ctx, lv__ids, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv_food, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[29])));
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[30]), ([&]() { gd::GdVal _ca[] = {lv__ids}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[31]), ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1411)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[0])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
        {
            gd::GdVal _t1657 = gd::gd_iter_seq(gd_ctx.arena, lv_affected);
            gd::GdArr* _t1658 = (_t1657.kind == gd::GdVal::Kind::Arr) ? _t1657.arr : nullptr;
            uint32_t _len__t1659 = _t1658 ? _t1658->len : 0u;
            for (uint32_t _t1659 = 0; _t1659 < _len__t1659; ++_t1659) {
                gd::GdVal lv_food = _t1658->data[_t1659];
                (void)gd::call_method(gd_ctx, lv_food, SYM_GEN_doCooldownEffect_144, nullptr, 0);
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Eggscalibur::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Pan::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Eggscalibur(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Eggscalibur>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Eggscalibur = {CLS_Gd__gd_core_items__Eggscalibur, "Eggscalibur", "res://gd_core_items/Eggscalibur.gd", &META_Gd__gd_core_items__Pan, true, _alloc_Gd__gd_core_items__Eggscalibur, &Gd__gd_core_items__Eggscalibur::get_static_prop_fn, &Gd__gd_core_items__Eggscalibur::call_static_fn};

void Gd__gd_core_items__Exclusive__Anvil::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Anvil::meta() const { return &META_Gd__gd_core_items__Exclusive__Anvil; }
gd::GdVal Gd__gd_core_items__Exclusive__Anvil::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Anvil::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Anvil::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Anvil::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Anvil::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_addToInventory_120: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_onCraft_2038: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_onPreCombatStart_125: return true;
        case SYM_GEN_getRelatedItems_459: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Anvil::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_addToInventory_120: out = fn_addToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_onCraft_2038: out = fn_onCraft(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPreCombatStart_125: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_getRelatedItems_459: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Anvil::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Anvil::fn_addToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__inventory = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__occupiedCells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__placedByPlayer = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv__placedByPlayer = gd::gd_coerce_bool(lv__placedByPlayer);
    (void)([&]() { gd::GdVal _ca[] = {lv__inventory, lv__occupiedCells, lv__placedByPlayer}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_addToInventory_120, _ca, 3, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Anvil::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Anvil::fn_onCraft(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__itemDescriptor = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Anvil::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_isCrafted_800, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Anvil::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_isWeapon_82, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Anvil::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numCrafted = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0), gd::SYM_size, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numCrafted, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_bonusDamage = gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), lv_numCrafted);
        gd::GdVal lv_staminaReduction = gd::gd_mul(gd::gd_neg(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)), lv_numCrafted);
        {
            gd::GdVal _t1660 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, _ca, 1); })());
            gd::GdArr* _t1661 = (_t1660.kind == gd::GdVal::Kind::Arr) ? _t1660.arr : nullptr;
            uint32_t _len__t1662 = _t1661 ? _t1661->len : 0u;
            for (uint32_t _t1662 = 0; _t1662 < _len__t1662; ++_t1662) {
                gd::GdVal lv_affectedWeapon = _t1661->data[_t1662];
                if (gd::gd_truth(gd::call_method(gd_ctx, lv_affectedWeapon, SYM_GEN_canBeEmpowered_90, nullptr, 0))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_bonusDamage}; return gd::call_method(gd_ctx, lv_affectedWeapon, SYM_GEN_addBonusDamage_161, _ca, 1); })();
                    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_affectedWeapon, lv_bonusDamage, gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_playerId_1046)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_DamageBuff_1374, _ca, 4); })();
                    (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_logEvent_1357, _ca, 1); })();
                }
                (void)([&]() { gd::GdVal _ca[] = {lv_staminaReduction}; return gd::call_method(gd_ctx, lv_affectedWeapon, SYM_GEN_changeStaminaFactor_305, _ca, 1); })();
            }
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Anvil::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[32])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })()}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Anvil::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Anvil(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Anvil>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Anvil = {CLS_Gd__gd_core_items__Exclusive__Anvil, "Anvil", "res://gd_core_items/Exclusive/Anvil.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Anvil, &Gd__gd_core_items__Exclusive__Anvil::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Anvil::call_static_fn};

void Gd__gd_core_items__Exclusive__Bagtacular::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_affectedBagDescriptors = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Bagtacular::meta() const { return &META_Gd__gd_core_items__Exclusive__Bagtacular; }
gd::GdVal Gd__gd_core_items__Exclusive__Bagtacular::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Bagtacular::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Bagtacular::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_affectedBagDescriptors_2054: out = this->f_affectedBagDescriptors; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Bagtacular::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedBagDescriptors_2054: this->f_affectedBagDescriptors = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Bagtacular::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_global_2014: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Bagtacular::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_global_2014: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Bagtacular::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Bagtacular::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::gd_in(gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), this->f_affectedBagDescriptors);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Bagtacular::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_affectedBagDescriptors = ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 4); d->set(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[33])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })(), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[34])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })(), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[35])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })(), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[36])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })(), gd::GdVal::from_bool(true)); return gd::GdVal::from_dict(d); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Bagtacular(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Bagtacular>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Bagtacular = {CLS_Gd__gd_core_items__Exclusive__Bagtacular, "Bagtacular", "res://gd_core_items/Exclusive/Bagtacular.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Bagtacular, &Gd__gd_core_items__Exclusive__Bagtacular::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Bagtacular::call_static_fn};

void Gd__gd_core_items__Exclusive__BookofNature::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_regenNeeded = gd::GdVal::null();
    this->f_lucky = gd::GdVal::null();
    this->f_spikes = gd::GdVal::null();
    this->f_spellSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__BookofNature::meta() const { return &META_Gd__gd_core_items__Exclusive__BookofNature; }
gd::GdVal Gd__gd_core_items__Exclusive__BookofNature::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__BookofNature::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__BookofNature::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_regenNeeded_942: out = this->f_regenNeeded; return true;
        case SYM_GEN_lucky_2095: out = this->f_lucky; return true;
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        case SYM_GEN_spellSpeed_2094: out = this->f_spellSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BookofNature::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_regenNeeded_942: this->f_regenNeeded = val; return true;
        case SYM_GEN_lucky_2095: this->f_lucky = val; return true;
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        case SYM_GEN_spellSpeed_2094: this->f_spellSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BookofNature::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BookofNature::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BookofNature::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofNature::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(18LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofNature::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_speed = gd::GdVal::from_float(0.0);
    {
        gd::GdVal _t1663 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1664 = (_t1663.kind == gd::GdVal::Kind::Arr) ? _t1663.arr : nullptr;
        uint32_t _len__t1665 = _t1664 ? _t1664->len : 0u;
        for (uint32_t _t1665 = 0; _t1665 < _len__t1665; ++_t1665) {
            gd::GdVal lv_item = _t1664->data[_t1665];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(26LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
                lv_speed = gd::gd_add(gd_ctx, lv_speed, gd::gd_mul(this->f_spellSpeed, gd::GdVal::from_int(2LL)));
            }
            else {
                lv_speed = gd::gd_add(gd_ctx, lv_speed, this->f_spellSpeed);
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_speed}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofNature::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRegeneration_1233, nullptr, 0), this->f_regenNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_regenNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_346, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_lucky, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_spikes, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofNature::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_regenNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[37])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_lucky = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[38])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[39])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_spellSpeed = gd::gd_div(gd_ctx, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[40])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BookofNature(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__BookofNature>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BookofNature = {CLS_Gd__gd_core_items__Exclusive__BookofNature, "BookofNature", "res://gd_core_items/Exclusive/BookofNature.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__BookofNature, &Gd__gd_core_items__Exclusive__BookofNature::get_static_prop_fn, &Gd__gd_core_items__Exclusive__BookofNature::call_static_fn};

void Gd__gd_core_items__Exclusive__Cauldron::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_options = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Cauldron::meta() const { return &META_Gd__gd_core_items__Exclusive__Cauldron; }
gd::GdVal Gd__gd_core_items__Exclusive__Cauldron::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_healColor_2119: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.384314), gd::GdVal::from_float(0.913725), gd::GdVal::from_float(0.423529)}; return gd::make_color_from_args(_ca, 3); })();
        case SYM_GEN_manaColor_2120: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.329412), gd::GdVal::from_float(0.392157), gd::GdVal::from_float(0.992157)}; return gd::make_color_from_args(_ca, 3); })();
        case SYM_GEN_heatColor_2121: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.996078), gd::GdVal::from_float(0.458824), gd::GdVal::from_float(0.290196)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Cauldron::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Cauldron::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_options_1876: out = this->f_options; return true;
        case SYM_GEN_healColor_2119: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_manaColor_2120: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_heatColor_2121: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Cauldron::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_options_1876: this->f_options = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Cauldron::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Cauldron::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Cauldron::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Cauldron::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(11LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cauldron::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0), gd::GdVal::from_float(100.0)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cauldron::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rng = ([&]() { gd::GdVal _ca[] = {this->f_options}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_pickRandomElement_1746, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_rng, gd::GdVal::from_int(0LL))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_rng, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    (void)([&]() { gd::GdVal _ca[] = {lv_rng}; return gd::call_method(gd_ctx, this->f_options, gd::SYM_erase, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cauldron::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Cauldron(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Cauldron>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Cauldron = {CLS_Gd__gd_core_items__Exclusive__Cauldron, "Cauldron", "res://gd_core_items/Exclusive/Cauldron.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Cauldron, &Gd__gd_core_items__Exclusive__Cauldron::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Cauldron::call_static_fn};

void Gd__gd_core_items__Exclusive__Chess__WhitePawn::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Chess__ChessPiece::init_fields(gd_ctx);
    this->f_luck = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Chess__WhitePawn::meta() const { return &META_Gd__gd_core_items__Exclusive__Chess__WhitePawn; }
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhitePawn::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Chess__WhitePawn::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Chess__WhitePawn::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__WhitePawn::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__WhitePawn::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2146: return true;
        case SYM_GEN_doEliminatedEffect_2148: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__WhitePawn::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2146: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_doEliminatedEffect_2148: out = fn_doEliminatedEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Chess__WhitePawn::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhitePawn::fn_doCapturingEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__eliminatedPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhitePawn::fn_doEliminatedEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhitePawn::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[38])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[37])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Chess__WhitePawn(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Chess__WhitePawn>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__WhitePawn = {CLS_Gd__gd_core_items__Exclusive__Chess__WhitePawn, "WhitePawn", "res://gd_core_items/Exclusive/Chess/WhitePawn.gd", &META_Gd__gd_core_items__Exclusive__Chess__ChessPiece, true, _alloc_Gd__gd_core_items__Exclusive__Chess__WhitePawn, &Gd__gd_core_items__Exclusive__Chess__WhitePawn::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Chess__WhitePawn::call_static_fn};

void Gd__gd_core_items__Exclusive__Cupcake::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
    this->f_numBuffs = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Cupcake::meta() const { return &META_Gd__gd_core_items__Exclusive__Cupcake; }
gd::GdVal Gd__gd_core_items__Exclusive__Cupcake::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Cupcake::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Cupcake::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_numBuffs_2005: out = this->f_numBuffs; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Cupcake::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numBuffs_2005: this->f_numBuffs = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Cupcake::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Cupcake::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Cupcake::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Cupcake::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {this->f_numBuffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMostBuffs_367, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cupcake::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_numBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[41])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Cupcake(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Cupcake>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Cupcake = {CLS_Gd__gd_core_items__Exclusive__Cupcake, "Cupcake", "res://gd_core_items/Exclusive/Cupcake.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Exclusive__Cupcake, &Gd__gd_core_items__Exclusive__Cupcake::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Cupcake::call_static_fn};

void Gd__gd_core_items__Exclusive__DragonClaws::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__DragonClaws::meta() const { return &META_Gd__gd_core_items__Exclusive__DragonClaws; }
gd::GdVal Gd__gd_core_items__Exclusive__DragonClaws::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__DragonClaws::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__DragonClaws::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DragonClaws::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DragonClaws::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onBattleRageStarted_2066: return true;
        case SYM_GEN_onBattleRageEnded_2067: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DragonClaws::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_2066: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN_onBattleRageEnded_2067: out = fn_onBattleRageEnded(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DragonClaws::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonClaws::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonClaws::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[42]), gd::GdVal::from_str(&battle_string_literals[43])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[44]), gd::GdVal::from_str(&battle_string_literals[45])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(108LL), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeResistChance_1026, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonClaws::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1666 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1667 = (_t1666.kind == gd::GdVal::Kind::Arr) ? _t1666.arr : nullptr;
        uint32_t _len__t1668 = _t1667 ? _t1667->len : 0u;
        for (uint32_t _t1668 = 0; _t1668 < _len__t1668; ++_t1668) {
            gd::GdVal lv_item = _t1667->data[_t1668];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::GdVal::from_int(100LL))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonClaws::fn_onBattleRageEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1669 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1670 = (_t1669.kind == gd::GdVal::Kind::Arr) ? _t1669.arr : nullptr;
        uint32_t _len__t1671 = _t1670 ? _t1670->len : 0u;
        for (uint32_t _t1671 = 0; _t1671 < _len__t1671; ++_t1671) {
            gd::GdVal lv_item = _t1670->data[_t1671];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::GdVal::from_int(100LL))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_274, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonClaws::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DragonClaws(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__DragonClaws>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DragonClaws = {CLS_Gd__gd_core_items__Exclusive__DragonClaws, "DragonClaws", "res://gd_core_items/Exclusive/DragonClaws.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__DragonClaws, &Gd__gd_core_items__Exclusive__DragonClaws::get_static_prop_fn, &Gd__gd_core_items__Exclusive__DragonClaws::call_static_fn};

void Gd__gd_core_items__Exclusive__EnchantedWeapons::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_buffs = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__EnchantedWeapons::meta() const { return &META_Gd__gd_core_items__Exclusive__EnchantedWeapons; }
gd::GdVal Gd__gd_core_items__Exclusive__EnchantedWeapons::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__EnchantedWeapons::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__EnchantedWeapons::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_buffs_1048: out = this->f_buffs; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__EnchantedWeapons::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffs_1048: this->f_buffs = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__EnchantedWeapons::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__EnchantedWeapons::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__EnchantedWeapons::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__EnchantedWeapons::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasAttackEffect_295, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EnchantedWeapons::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1672 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1673 = (_t1672.kind == gd::GdVal::Kind::Arr) ? _t1672.arr : nullptr;
        uint32_t _len__t1674 = _t1673 ? _t1673->len : 0u;
        for (uint32_t _t1674 = 0; _t1674 < _len__t1674; ++_t1674) {
            gd::GdVal lv_item = _t1673->data[_t1674];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveDoubleAttackEffectChance_313, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EnchantedWeapons::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLeastBuffs_366, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EnchantedWeapons::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_buffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[41])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__EnchantedWeapons(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__EnchantedWeapons>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__EnchantedWeapons = {CLS_Gd__gd_core_items__Exclusive__EnchantedWeapons, "EnchantedWeapons", "res://gd_core_items/Exclusive/EnchantedWeapons.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__EnchantedWeapons, &Gd__gd_core_items__Exclusive__EnchantedWeapons::get_static_prop_fn, &Gd__gd_core_items__Exclusive__EnchantedWeapons::call_static_fn};

void Gd__gd_core_items__Exclusive__ForestDragon::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_regen = gd::GdVal::null();
    this->f_luck = gd::GdVal::null();
    this->f_damPerRegen = gd::GdVal::null();
    this->f_speedPerNature = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ForestDragon::meta() const { return &META_Gd__gd_core_items__Exclusive__ForestDragon; }
gd::GdVal Gd__gd_core_items__Exclusive__ForestDragon::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ForestDragon::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ForestDragon::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_damPerRegen_2262: out = this->f_damPerRegen; return true;
        case SYM_GEN_speedPerNature_2263: out = this->f_speedPerNature; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ForestDragon::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_damPerRegen_2262: this->f_damPerRegen = val; return true;
        case SYM_GEN_speedPerNature_2263: this->f_speedPerNature = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ForestDragon::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onRegenChanged_1891: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ForestDragon::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onRegenChanged_1891: out = fn_onRegenChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ForestDragon::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ForestDragon::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(26LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ForestDragon::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[46]), gd::GdVal::from_str(&battle_string_literals[47])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_speedPerNature, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ForestDragon::fn_onRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, this->f_damPerRegen)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_162, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ForestDragon::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ForestDragon::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[37])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[38])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_damPerRegen = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[27])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_speedPerNature = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[40])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ForestDragon(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ForestDragon>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ForestDragon = {CLS_Gd__gd_core_items__Exclusive__ForestDragon, "ForestDragon", "res://gd_core_items/Exclusive/ForestDragon.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__ForestDragon, &Gd__gd_core_items__Exclusive__ForestDragon::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ForestDragon::call_static_fn};

void Gd__gd_core_items__Exclusive__GirlPower::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_empower = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
    this->f_speed_v = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__GirlPower::meta() const { return &META_Gd__gd_core_items__Exclusive__GirlPower; }
gd::GdVal Gd__gd_core_items__Exclusive__GirlPower::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__GirlPower::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__GirlPower::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        case SYM_GEN_speed_v_2179: out = this->f_speed_v; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__GirlPower::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        case SYM_GEN_speed_v_2179: this->f_speed_v = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__GirlPower::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_isAffectingDistinct_254: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onItemRoll_2018: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__GirlPower::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_isAffectingDistinct_254: out = fn_isAffectingDistinct(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onItemRoll_2018: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__GirlPower::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__GirlPower::fn_isAffectingDistinct(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    return gd::GdVal::from_bool(gd::gd_eq(lv_color, gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GirlPower::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_isClassItem_248, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GirlPower::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_speed_v, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumDistinctAffectedItems_430, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GirlPower::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_curEmpower = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getEmpower_1248, nullptr, 0);
    gd::GdVal lv_curRegen = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRegeneration_1233, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_curRegen, lv_curEmpower)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_curRegen, lv_curEmpower)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_empower}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
    }
    else {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_flip_1735, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {this->f_empower}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GirlPower::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GirlPower::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[48])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[37])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_speed_v = gd::gd_div(gd_ctx, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[40])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__GirlPower(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__GirlPower>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__GirlPower = {CLS_Gd__gd_core_items__Exclusive__GirlPower, "GirlPower", "res://gd_core_items/Exclusive/GirlPower.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__GirlPower, &Gd__gd_core_items__Exclusive__GirlPower::get_static_prop_fn, &Gd__gd_core_items__Exclusive__GirlPower::call_static_fn};

void Gd__gd_core_items__Exclusive__HyperHedgehog::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Hedgehog::init_fields(gd_ctx);
    this->f_damagePerEmpower = gd::GdVal::null();
    this->f_empower = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__HyperHedgehog::meta() const { return &META_Gd__gd_core_items__Exclusive__HyperHedgehog; }
gd::GdVal Gd__gd_core_items__Exclusive__HyperHedgehog::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Hedgehog::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__HyperHedgehog::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__HyperHedgehog::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_damagePerEmpower_2313: out = this->f_damagePerEmpower; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Hedgehog::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__HyperHedgehog::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damagePerEmpower_2313: this->f_damagePerEmpower = val; return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Hedgehog::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__HyperHedgehog::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onHPLow_2305: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_149: return true;
        case SYM_GEN_spawnSpikeParticles_2306: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Hedgehog::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__HyperHedgehog::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onHPLow_2305: out = fn_onHPLow(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_149: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN_spawnSpikeParticles_2306: out = fn_spawnSpikeParticles(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Hedgehog::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__HyperHedgehog::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Hedgehog::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__HyperHedgehog::fn_onHPLow(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_event}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Hedgehog::call_method(gd_ctx, SYM_GEN_onHPLow_2305, _ca, 1, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_empower, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HyperHedgehog::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dam = gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1675);
    lv_dam = gd::gd_add(gd_ctx, lv_dam, gd::gd_mul(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getSpikes_1223, nullptr, 0), this->f_damagePerSpike));
    lv_dam = gd::gd_add(gd_ctx, lv_dam, gd::gd_mul(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getEmpower_1248, nullptr, 0), this->f_damagePerEmpower));
    gd::GdVal lv_res = ([&]() { gd::GdVal _ca[] = {lv_dam}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealEffectDamage_221, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HyperHedgehog::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HyperHedgehog::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HyperHedgehog::fn_spawnSpikeParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HyperHedgehog::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Hedgehog::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_damagePerEmpower = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[49])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[48])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__HyperHedgehog(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__HyperHedgehog>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__HyperHedgehog = {CLS_Gd__gd_core_items__Exclusive__HyperHedgehog, "HyperHedgehog", "res://gd_core_items/Exclusive/HyperHedgehog.gd", &META_Gd__gd_core_items__Exclusive__Hedgehog, true, _alloc_Gd__gd_core_items__Exclusive__HyperHedgehog, &Gd__gd_core_items__Exclusive__HyperHedgehog::get_static_prop_fn, &Gd__gd_core_items__Exclusive__HyperHedgehog::call_static_fn};

void Gd__gd_core_items__Exclusive__LeafBadge::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__LeafBadge::meta() const { return &META_Gd__gd_core_items__Exclusive__LeafBadge; }
gd::GdVal Gd__gd_core_items__Exclusive__LeafBadge::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__LeafBadge::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__LeafBadge::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__LeafBadge::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__LeafBadge::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onAddToInventory_419: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onLuckyChanged_901: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_getRelatedItems_459: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__LeafBadge::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onAddToInventory_419: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onLuckyChanged_901: out = fn_onLuckyChanged(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getRelatedItems_459: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__LeafBadge::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__LeafBadge::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LeafBadge::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LeafBadge::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canDamage_89, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LeafBadge::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0), gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[50]), gd::GdVal::from_str(&battle_string_literals[51])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LeafBadge::fn_onLuckyChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    {
        gd::GdVal _t1675 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1676 = (_t1675.kind == gd::GdVal::Kind::Arr) ? _t1675.arr : nullptr;
        uint32_t _len__t1677 = _t1676 ? _t1676->len : 0u;
        for (uint32_t _t1677 = 0; _t1677 < _len__t1677; ++_t1677) {
            gd::GdVal lv_item = _t1676->data[_t1677];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeCritChancePercent_181, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LeafBadge::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LeafBadge::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LeafBadge::fn_getRelatedItemColumns(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(3LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LeafBadge::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__LeafBadge(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__LeafBadge>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__LeafBadge = {CLS_Gd__gd_core_items__Exclusive__LeafBadge, "LeafBadge", "res://gd_core_items/Exclusive/LeafBadge.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__LeafBadge, &Gd__gd_core_items__Exclusive__LeafBadge::get_static_prop_fn, &Gd__gd_core_items__Exclusive__LeafBadge::call_static_fn};

void Gd__gd_core_items__Exclusive__MagiteccArmor::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_speedPerAffected = gd::GdVal::null();
    this->f_manaNeeded = gd::GdVal::null();
    this->f_numDebuffs = gd::GdVal::null();
    this->f_block2 = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__MagiteccArmor::meta() const { return &META_Gd__gd_core_items__Exclusive__MagiteccArmor; }
gd::GdVal Gd__gd_core_items__Exclusive__MagiteccArmor::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__MagiteccArmor::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__MagiteccArmor::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_speedPerAffected_2391: out = this->f_speedPerAffected; return true;
        case SYM_GEN_manaNeeded_1881: out = this->f_manaNeeded; return true;
        case SYM_GEN_numDebuffs_2048: out = this->f_numDebuffs; return true;
        case SYM_GEN_block2_2077: out = this->f_block2; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MagiteccArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_speedPerAffected_2391: this->f_speedPerAffected = val; return true;
        case SYM_GEN_manaNeeded_1881: this->f_manaNeeded = val; return true;
        case SYM_GEN_numDebuffs_2048: this->f_numDebuffs = val; return true;
        case SYM_GEN_block2_2077: this->f_block2 = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MagiteccArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MagiteccArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__MagiteccArmor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__MagiteccArmor::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(23LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagiteccArmor::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0), this->f_speedPerAffected)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagiteccArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagiteccArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_manaNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_numDebuffs, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_356, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_block2, gd::GdVal::from_bool(true), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 3); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagiteccArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speedPerAffected = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[40])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[52])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_numDebuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[53])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_block2 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[54])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MagiteccArmor(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__MagiteccArmor>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MagiteccArmor = {CLS_Gd__gd_core_items__Exclusive__MagiteccArmor, "MagiteccArmor", "res://gd_core_items/Exclusive/MagiteccArmor.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__MagiteccArmor, &Gd__gd_core_items__Exclusive__MagiteccArmor::get_static_prop_fn, &Gd__gd_core_items__Exclusive__MagiteccArmor::call_static_fn};

void Gd__gd_core_items__Exclusive__MushroomFarm::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_flyAgaricDescriptor = gd::GdVal::null();
    this->f_doomCapDescriptor = gd::GdVal::null();
    this->f_mushroomSpeed = gd::GdVal::null();
    this->f_mushroomsNeeded = gd::GdVal::null();
    this->f_activeLight = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__MushroomFarm::meta() const { return &META_Gd__gd_core_items__Exclusive__MushroomFarm; }
gd::GdVal Gd__gd_core_items__Exclusive__MushroomFarm::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__MushroomFarm::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__MushroomFarm::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_flyAgaricDescriptor_2411: out = this->f_flyAgaricDescriptor; return true;
        case SYM_GEN_doomCapDescriptor_2412: out = this->f_doomCapDescriptor; return true;
        case SYM_GEN_mushroomSpeed_2413: out = this->f_mushroomSpeed; return true;
        case SYM_GEN_mushroomsNeeded_2414: out = this->f_mushroomsNeeded; return true;
        case SYM_GEN_activeLight_2415: out = this->f_activeLight; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MushroomFarm::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_flyAgaricDescriptor_2411: this->f_flyAgaricDescriptor = val; return true;
        case SYM_GEN_doomCapDescriptor_2412: this->f_doomCapDescriptor = val; return true;
        case SYM_GEN_mushroomSpeed_2413: this->f_mushroomSpeed = val; return true;
        case SYM_GEN_mushroomsNeeded_2414: this->f_mushroomsNeeded = val; return true;
        case SYM_GEN_activeLight_2415: this->f_activeLight = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MushroomFarm::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onItemAdded_437: return true;
        case SYM_GEN_onItemRemoved_438: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_isActive_2416: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onItemRoll_2018: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MushroomFarm::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onItemAdded_437: out = fn_onItemAdded(args, argc); return true;
        case SYM_GEN_onItemRemoved_438: out = fn_onItemRemoved(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_isActive_2416: out = fn_isActive(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onItemRoll_2018: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__MushroomFarm::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__MushroomFarm::fn_onItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemAdded_437, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isActive_2416, nullptr, 0))) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MushroomFarm::fn_onItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemRemoved_438, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isActive_2416, nullptr, 0))))) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MushroomFarm::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MushroomFarm::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_flyAgaricDescriptor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_245, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_doomCapDescriptor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_245, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MushroomFarm::fn_isActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numMushrooms = ([&]() { gd::GdVal _ca[] = {this->f_flyAgaricDescriptor}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_countPlacedItemsInInventoryOfType_1670, _ca, 1); })();
    lv_numMushrooms = gd::gd_add(gd_ctx, lv_numMushrooms, ([&]() { gd::GdVal _ca[] = {this->f_doomCapDescriptor}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_countPlacedItemsInInventoryOfType_1670, _ca, 1); })());
    return gd::GdVal::from_bool(gd::gd_ge(lv_numMushrooms, this->f_mushroomsNeeded));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MushroomFarm::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MushroomFarm::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1678 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1679 = (_t1678.kind == gd::GdVal::Kind::Arr) ? _t1678.arr : nullptr;
        uint32_t _len__t1680 = _t1679 ? _t1679->len : 0u;
        for (uint32_t _t1680 = 0; _t1680 < _len__t1680; ++_t1680) {
            gd::GdVal lv_mushroom = _t1679->data[_t1680];
            (void)([&]() { gd::GdVal _ca[] = {this->f_mushroomSpeed}; return gd::call_method(gd_ctx, lv_mushroom, SYM_GEN_addSpeed_273, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MushroomFarm::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MushroomFarm::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_flyAgaricDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[55])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_doomCapDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[56])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_mushroomSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[40])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_mushroomsNeeded = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[57])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MushroomFarm(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__MushroomFarm>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MushroomFarm = {CLS_Gd__gd_core_items__Exclusive__MushroomFarm, "MushroomFarm", "res://gd_core_items/Exclusive/MushroomFarm.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__MushroomFarm, &Gd__gd_core_items__Exclusive__MushroomFarm::get_static_prop_fn, &Gd__gd_core_items__Exclusive__MushroomFarm::call_static_fn};

void Gd__gd_core_items__Exclusive__PoisonFrog::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_affectedItemsDict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_gainedBuffs = gd::GdVal::from_int(0);
    this->f_usedBuffs = gd::GdVal::from_int(0);
    this->f_gainedThreshold = gd::GdVal::from_int(0);
    this->f_usedThreshold = gd::GdVal::from_int(0);
    this->f_poison = gd::GdVal::null();
    this->f_mana = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PoisonFrog::meta() const { return &META_Gd__gd_core_items__Exclusive__PoisonFrog; }
gd::GdVal Gd__gd_core_items__Exclusive__PoisonFrog::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PoisonFrog::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PoisonFrog::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_affectedItemsDict_2109: out = this->f_affectedItemsDict; return true;
        case SYM_GEN_gainedBuffs_2268: out = this->f_gainedBuffs; return true;
        case SYM_GEN_usedBuffs_2269: out = this->f_usedBuffs; return true;
        case SYM_GEN_gainedThreshold_2270: out = this->f_gainedThreshold; return true;
        case SYM_GEN_usedThreshold_2271: out = this->f_usedThreshold; return true;
        case SYM_GEN_poison_1962: out = this->f_poison; return true;
        case SYM_GEN_mana_1928: out = this->f_mana; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PoisonFrog::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedItemsDict_2109: this->f_affectedItemsDict = val; return true;
        case SYM_GEN_gainedBuffs_2268: this->f_gainedBuffs = gd::gd_coerce_int(val); return true;
        case SYM_GEN_usedBuffs_2269: this->f_usedBuffs = gd::gd_coerce_int(val); return true;
        case SYM_GEN_gainedThreshold_2270: this->f_gainedThreshold = gd::gd_coerce_int(val); return true;
        case SYM_GEN_usedThreshold_2271: this->f_usedThreshold = gd::gd_coerce_int(val); return true;
        case SYM_GEN_poison_1962: this->f_poison = val; return true;
        case SYM_GEN_mana_1928: this->f_mana = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PoisonFrog::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onBuffsChanged_2087: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_149: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PoisonFrog::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBuffsChanged_2087: out = fn_onBuffsChanged(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_149: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PoisonFrog::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonFrog::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsBuffs_296, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_usesBuffs_297, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonFrog::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_affectedItemsDict, gd::SYM_clear, nullptr, 0);
    {
        gd::GdVal _t1681 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1682 = (_t1681.kind == gd::GdVal::Kind::Arr) ? _t1681.arr : nullptr;
        uint32_t _len__t1683 = _t1682 ? _t1682->len : 0u;
        for (uint32_t _t1683 = 0; _t1683 < _len__t1683; ++_t1683) {
            gd::GdVal lv_item = _t1682->data[_t1683];
            { gd::GdVal _t1684 = this->f_affectedItemsDict; gd::GdVal _t1685 = lv_item; gd::set_index(gd_ctx, _t1684, _t1685, gd::GdVal::from_bool(true)); }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[58])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterBuffs_374, _ca, 1); })();
    this->f_gainedBuffs = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_usedBuffs = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonFrog::fn_onBuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::gd_in(gd::call_method(gd_ctx, lv_event, SYM_GEN_getOrigin_1580, nullptr, 0), this->f_affectedItemsDict))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
            this->f_gainedBuffs = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_gainedBuffs, lv_amount));
            gd::GdVal lv_ticks = gd::gd_div(gd_ctx, this->f_gainedBuffs, this->f_gainedThreshold);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_ticks, gd::GdVal::from_int(0LL))))) {
                (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
                this->f_gainedBuffs = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_gainedBuffs, this->f_gainedThreshold));
                (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
            }
        }
        else {
            this->f_usedBuffs = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_usedBuffs, gd::gd_coerce_int(gd::gd_abs(lv_amount))));
            gd::GdVal lv_ticks = gd::gd_div(gd_ctx, this->f_usedBuffs, this->f_usedThreshold);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_ticks, gd::GdVal::from_int(0LL))))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_ticks, this->f_poison), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 2); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_ticks, this->f_mana), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 2); })();
                this->f_usedBuffs = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_usedBuffs, this->f_usedThreshold));
                (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonFrog::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[59])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[60])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonFrog::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_pitch = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonFrog::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    gd::GdVal lv_pitch = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonFrog::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_gainedThreshold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[61])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_usedThreshold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[62])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_poison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[63])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[15])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PoisonFrog(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__PoisonFrog>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PoisonFrog = {CLS_Gd__gd_core_items__Exclusive__PoisonFrog, "PoisonFrog", "res://gd_core_items/Exclusive/PoisonFrog.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__PoisonFrog, &Gd__gd_core_items__Exclusive__PoisonFrog::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PoisonFrog::call_static_fn};

void Gd__gd_core_items__Exclusive__Puzzlebox::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bag::init_fields(gd_ctx);
    this->f_slowSpeed = gd::GdVal::null();
    this->f_fastSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Puzzlebox::meta() const { return &META_Gd__gd_core_items__Exclusive__Puzzlebox; }
gd::GdVal Gd__gd_core_items__Exclusive__Puzzlebox::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_puzzlebags_2447: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_str(&battle_string_literals[64]), gd::GdVal::from_str(&battle_string_literals[65]), gd::GdVal::from_str(&battle_string_literals[66]), gd::GdVal::from_str(&battle_string_literals[67]), gd::GdVal::from_str(&battle_string_literals[68])}));
        default: break;
    }
    return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Puzzlebox::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Puzzlebox::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_slowSpeed_2448: out = this->f_slowSpeed; return true;
        case SYM_GEN_fastSpeed_2449: out = this->f_fastSpeed; return true;
        case SYM_GEN_puzzlebags_2447: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Puzzlebox::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_slowSpeed_2448: this->f_slowSpeed = val; return true;
        case SYM_GEN_fastSpeed_2449: this->f_fastSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Puzzlebox::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_getReplaceDescriptor_2029: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Puzzlebox::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getReplaceDescriptor_2029: out = fn_getReplaceDescriptor(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Puzzlebox::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Puzzlebox::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_toItem, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Puzzlebox::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1686 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_927, nullptr, 0));
        gd::GdArr* _t1687 = (_t1686.kind == gd::GdVal::Kind::Arr) ? _t1686.arr : nullptr;
        uint32_t _len__t1688 = _t1687 ? _t1687->len : 0u;
        for (uint32_t _t1688 = 0; _t1688 < _len__t1688; ++_t1688) {
            gd::GdVal lv_item = _t1687->data[_t1688];
            (void)([&]() { gd::GdVal _ca[] = {this->f_slowSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_274, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Puzzlebox::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1689 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_927, nullptr, 0));
        gd::GdArr* _t1690 = (_t1689.kind == gd::GdVal::Kind::Arr) ? _t1689.arr : nullptr;
        uint32_t _len__t1691 = _t1690 ? _t1690->len : 0u;
        for (uint32_t _t1691 = 0; _t1691 < _len__t1691; ++_t1691) {
            gd::GdVal lv_item = _t1690->data[_t1691];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_slowSpeed, this->f_fastSpeed)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Puzzlebox::fn_getReplaceDescriptor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rarity = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Puzzlebox::fn_getRelatedItemColumns(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(2LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Puzzlebox::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_slowSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[40])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_fastSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[69])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Puzzlebox(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Puzzlebox>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Puzzlebox = {CLS_Gd__gd_core_items__Exclusive__Puzzlebox, "Puzzlebox", "res://gd_core_items/Exclusive/Puzzlebox.gd", &META_Gd__gd_core_items__Bag, true, _alloc_Gd__gd_core_items__Exclusive__Puzzlebox, &Gd__gd_core_items__Exclusive__Puzzlebox::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Puzzlebox::call_static_fn};

void Gd__gd_core_items__Exclusive__Reverse::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Card::init_fields(gd_ctx);
    this->f_activationParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Reverse::meta() const { return &META_Gd__gd_core_items__Exclusive__Reverse; }
gd::GdVal Gd__gd_core_items__Exclusive__Reverse::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Card::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Reverse::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Reverse::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Reverse::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Reverse::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_890: return true;
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN_getCardDescription_895: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Card::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Reverse::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_890: out = fn_cardSecondaryEffectActive(args, argc); return true;
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN_getCardDescription_895: out = fn_getCardDescription(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Reverse::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Reverse::fn_cardSecondaryEffectActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(this->f_deck) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(([&]() { gd::GdVal _ca[] = {this->f_chainPosition}; return gd::call_method(gd_ctx, this->f_deck, SYM_GEN_countDuplicates_1802, _ca, 1); })(), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Reverse::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[70])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveReflectStacks_200, _ca, 1); })();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cardSecondaryEffectActive_890, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[71])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_373, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Reverse::fn_getCardDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(this->f_deck)) {
        gd::GdVal lv_duplicates = ([&]() { gd::GdVal _ca[] = {this->f_chainPosition}; return gd::call_method(gd_ctx, this->f_deck, SYM_GEN_countDuplicates_1802, _ca, 1); })();
        gd::GdVal lv_state = gd::GdVal::from_int(0LL);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_duplicates, gd::GdVal::from_int(0LL))))) {
            lv_state = gd::GdVal::from_int(1LL);
        }
        else {
            lv_state = gd::GdVal::from_int(2LL);
        }
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[72]), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[73]), gd::GdVal::from_str(&battle_string_literals[57]), lv_duplicates, lv_state, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 5); })()));
    }
    else if (gd::gd_truth(this->f_placed)) {
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[72]), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[74]), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_paramColor_2717)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_wrapInColor_2771, _ca, 2); })()));
    }
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Reverse::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Card::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Reverse(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Reverse>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Reverse = {CLS_Gd__gd_core_items__Exclusive__Reverse, "Reverse", "res://gd_core_items/Exclusive/Reverse.gd", &META_Gd__gd_core_items__Card, true, _alloc_Gd__gd_core_items__Exclusive__Reverse, &Gd__gd_core_items__Exclusive__Reverse::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Reverse::call_static_fn};

void Gd__gd_core_items__Exclusive__Shielded::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_boostedShields = gd::GdVal::from_int(0LL);
    this->f_shieldOfValorDescriptor = gd::GdVal::null();
    this->f_shieldChance = gd::GdVal::null();
    this->f_armorSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Shielded::meta() const { return &META_Gd__gd_core_items__Exclusive__Shielded; }
gd::GdVal Gd__gd_core_items__Exclusive__Shielded::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Shielded::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Shielded::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_boostedShields_2489: out = this->f_boostedShields; return true;
        case SYM_GEN_shieldOfValorDescriptor_2490: out = this->f_shieldOfValorDescriptor; return true;
        case SYM_GEN_shieldChance_2491: out = this->f_shieldChance; return true;
        case SYM_GEN_armorSpeed_2492: out = this->f_armorSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Shielded::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_boostedShields_2489: this->f_boostedShields = val; return true;
        case SYM_GEN_shieldOfValorDescriptor_2490: this->f_shieldOfValorDescriptor = val; return true;
        case SYM_GEN_shieldChance_2491: this->f_shieldChance = val; return true;
        case SYM_GEN_armorSpeed_2492: this->f_armorSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Shielded::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_onBought_455: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onItemRoll_2018: return true;
        case SYM_GEN_onItemRolled_2019: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Shielded::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_onBought_455: out = fn_onBought(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemRoll_2018: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_2019: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Shielded::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Shielded::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_boostedShields;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Shielded::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_data, gd::GdVal::null())))) {
        this->f_boostedShields = lv_data;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Shielded::fn_onBought(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_boostedShields = gd::GdVal::from_int(1LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Shielded::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(5LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(6LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0))) : gd::GdVal::from_bool(false)))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Shielded::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1692 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1693 = (_t1692.kind == gd::GdVal::Kind::Arr) ? _t1692.arr : nullptr;
        uint32_t _len__t1694 = _t1693 ? _t1693->len : 0u;
        for (uint32_t _t1694 = 0; _t1694 < _len__t1694; ++_t1694) {
            gd::GdVal lv_item = _t1693->data[_t1694];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(5LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_shieldChance, gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusChance_additive_176, _ca, 2); })();
            }
            else {
                (void)([&]() { gd::GdVal _ca[] = {this->f_armorSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Shielded::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Shielded::fn_onItemRolled(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_descr, this->f_shieldOfValorDescriptor)))) {
        this->f_boostedShields = gd::gd_sub(this->f_boostedShields, gd::GdVal::from_int(1LL));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Shielded::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_shieldOfValorDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[75])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_shieldChance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[76])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_armorSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[40])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Shielded(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Shielded>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Shielded = {CLS_Gd__gd_core_items__Exclusive__Shielded, "Shielded", "res://gd_core_items/Exclusive/Shielded.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Shielded, &Gd__gd_core_items__Exclusive__Shielded::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Shielded::call_static_fn};

void Gd__gd_core_items__Exclusive__Solaris::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_boosted = gd::GdVal::from_int(0LL);
    this->f_sunShieldDescriptor = gd::GdVal::null();
    this->f_sunArmorDescriptor = gd::GdVal::null();
    this->f_holyArmorDescriptor = gd::GdVal::null();
    this->f_shieldOfValorDescriptor = gd::GdVal::null();
    this->f_heatPerShieldBlock = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Solaris::meta() const { return &META_Gd__gd_core_items__Exclusive__Solaris; }
gd::GdVal Gd__gd_core_items__Exclusive__Solaris::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Solaris::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Solaris::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_boosted_2197: out = this->f_boosted; return true;
        case SYM_GEN_sunShieldDescriptor_2518: out = this->f_sunShieldDescriptor; return true;
        case SYM_GEN_sunArmorDescriptor_2519: out = this->f_sunArmorDescriptor; return true;
        case SYM_GEN_holyArmorDescriptor_2520: out = this->f_holyArmorDescriptor; return true;
        case SYM_GEN_shieldOfValorDescriptor_2490: out = this->f_shieldOfValorDescriptor; return true;
        case SYM_GEN_heatPerShieldBlock_2521: out = this->f_heatPerShieldBlock; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Solaris::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_boosted_2197: this->f_boosted = val; return true;
        case SYM_GEN_sunShieldDescriptor_2518: this->f_sunShieldDescriptor = val; return true;
        case SYM_GEN_sunArmorDescriptor_2519: this->f_sunArmorDescriptor = val; return true;
        case SYM_GEN_holyArmorDescriptor_2520: this->f_holyArmorDescriptor = val; return true;
        case SYM_GEN_shieldOfValorDescriptor_2490: this->f_shieldOfValorDescriptor = val; return true;
        case SYM_GEN_heatPerShieldBlock_2521: this->f_heatPerShieldBlock = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Solaris::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onBought_455: return true;
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onArmorUsedHeat_2522: return true;
        case SYM_GEN_onShieldBlocked_2523: return true;
        case SYM_GEN_onItemRoll_2018: return true;
        case SYM_GEN_onItemRolled_2019: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Solaris::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onBought_455: out = fn_onBought(args, argc); return true;
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onArmorUsedHeat_2522: out = fn_onArmorUsedHeat(args, argc); return true;
        case SYM_GEN_onShieldBlocked_2523: out = fn_onShieldBlocked(args, argc); return true;
        case SYM_GEN_onItemRoll_2018: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_2019: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Solaris::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Solaris::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_sunShieldDescriptor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_245, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_sunArmorDescriptor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_245, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Solaris::fn_onBought(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_boosted = gd::GdVal::from_int(1LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Solaris::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_boosted;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Solaris::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_data, gd::GdVal::null())))) {
        this->f_boosted = lv_data;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Solaris::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(107LL), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0)}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_changeBuffAmplification_allItems_1616, _ca, 2); })();
    {
        gd::GdVal _t1695 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1696 = (_t1695.kind == gd::GdVal::Kind::Arr) ? _t1695.arr : nullptr;
        uint32_t _len__t1697 = _t1696 ? _t1696->len : 0u;
        for (uint32_t _t1697 = 0; _t1697 < _len__t1697; ++_t1697) {
            gd::GdVal lv_item = _t1696->data[_t1697];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_sunShieldDescriptor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_245, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[77]), gd::GdVal::from_str(&battle_string_literals[78])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
            }
            else {
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[79]), gd::GdVal::from_str(&battle_string_literals[80])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Solaris::fn_onArmorUsedHeat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), gd::GdVal::from_bool(true), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 3); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Solaris::fn_onShieldBlocked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_blockedDamageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_heatPerShieldBlock}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Solaris::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Solaris::fn_onItemRolled(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_descr, this->f_shieldOfValorDescriptor))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_descr, this->f_holyArmorDescriptor))))))) {
        this->f_boosted = gd::gd_sub(this->f_boosted, gd::GdVal::from_int(1LL));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Solaris::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_sunShieldDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[81])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_sunArmorDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[82])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_holyArmorDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[83])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_shieldOfValorDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[75])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_heatPerShieldBlock = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[84])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Solaris(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Solaris>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Solaris = {CLS_Gd__gd_core_items__Exclusive__Solaris, "Solaris", "res://gd_core_items/Exclusive/Solaris.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Solaris, &Gd__gd_core_items__Exclusive__Solaris::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Solaris::call_static_fn};

void Gd__gd_core_items__Exclusive__StaffofFire::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_numActivations = gd::GdVal::from_int(0);
    this->f_activationParticles = gd::GdVal::null();
    this->f_manaCost = gd::GdVal::from_int(0);
    this->f_heatCost = gd::GdVal::from_int(0);
    this->f_damBonus = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__StaffofFire::meta() const { return &META_Gd__gd_core_items__Exclusive__StaffofFire; }
gd::GdVal Gd__gd_core_items__Exclusive__StaffofFire::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__StaffofFire::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__StaffofFire::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_numActivations_1904: out = this->f_numActivations; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_manaCost_1815: out = this->f_manaCost; return true;
        case SYM_GEN_heatCost_2546: out = this->f_heatCost; return true;
        case SYM_GEN_damBonus_1925: out = this->f_damBonus; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__StaffofFire::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numActivations_1904: this->f_numActivations = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_manaCost_1815: this->f_manaCost = gd::gd_coerce_int(val); return true;
        case SYM_GEN_heatCost_2546: this->f_heatCost = gd::gd_coerce_int(val); return true;
        case SYM_GEN_damBonus_1925: this->f_damBonus = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__StaffofFire::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__StaffofFire::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__StaffofFire::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__StaffofFire::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_numActivations = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StaffofFire::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getHeat_1251, nullptr, 0), this->f_heatCost)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_333, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_event, gd::GdVal::null())))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_heatCost, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useHeat_354, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_damBonus}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
            this->f_numActivations = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numActivations, gd::GdVal::from_int(1LL)));
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StaffofFire::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StaffofFire::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_manaCost = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    this->f_heatCost = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    this->f_damBonus = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__StaffofFire(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__StaffofFire>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StaffofFire = {CLS_Gd__gd_core_items__Exclusive__StaffofFire, "StaffofFire", "res://gd_core_items/Exclusive/StaffofFire.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__StaffofFire, &Gd__gd_core_items__Exclusive__StaffofFire::get_static_prop_fn, &Gd__gd_core_items__Exclusive__StaffofFire::call_static_fn};

void Gd__gd_core_items__Exclusive__Thornburst::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_activationsLeft = gd::GdVal::from_int(0);
    this->f_spikes = gd::GdVal::null();
    this->f_uses = gd::GdVal::null();
    this->f_spikeSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Thornburst::meta() const { return &META_Gd__gd_core_items__Exclusive__Thornburst; }
gd::GdVal Gd__gd_core_items__Exclusive__Thornburst::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Thornburst::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Thornburst::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activationsLeft_2061: out = this->f_activationsLeft; return true;
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        case SYM_GEN_uses_2063: out = this->f_uses; return true;
        case SYM_GEN_spikeSpeed_2583: out = this->f_spikeSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Thornburst::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activationsLeft_2061: this->f_activationsLeft = gd::gd_coerce_int(val); return true;
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        case SYM_GEN_uses_2063: this->f_uses = val; return true;
        case SYM_GEN_spikeSpeed_2583: this->f_spikeSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Thornburst::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onSpikesChanged_944: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Thornburst::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onSpikesChanged_944: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Thornburst::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Thornburst::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_activationsLeft = gd::gd_coerce_int(this->f_uses);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[85]), gd::GdVal::from_str(&battle_string_literals[86])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Thornburst::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[87])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_330, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 1); })();
    this->f_activationsLeft = gd::gd_coerce_int(gd::gd_sub(this->f_activationsLeft, gd::GdVal::from_int(1LL)));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_activationsLeft, gd::GdVal::from_int(0LL))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Thornburst::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_spikeSpeed, lv_amount)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Thornburst::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[39])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_uses = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[88])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_spikeSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[40])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Thornburst(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Thornburst>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Thornburst = {CLS_Gd__gd_core_items__Exclusive__Thornburst, "Thornburst", "res://gd_core_items/Exclusive/Thornburst.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Thornburst, &Gd__gd_core_items__Exclusive__Thornburst::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Thornburst::call_static_fn};

void Gd__gd_core_items__Exclusive__UnidentifiedSkill::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_skillPool = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__UnidentifiedSkill::meta() const { return &META_Gd__gd_core_items__Exclusive__UnidentifiedSkill; }
gd::GdVal Gd__gd_core_items__Exclusive__UnidentifiedSkill::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__UnidentifiedSkill::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__UnidentifiedSkill::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_skillPool_2601: out = this->f_skillPool; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__UnidentifiedSkill::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_skillPool_2601: this->f_skillPool = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__UnidentifiedSkill::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getSkillPool_2602: return true;
        case SYM_GEN_onDropped_2034: return true;
        case SYM_GEN_identifySkill_2603: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_getRelatedItems_459: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN_getRelatedItemHeight_700: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__UnidentifiedSkill::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getSkillPool_2602: out = fn_getSkillPool(args, argc); return true;
        case SYM_GEN_onDropped_2034: out = fn_onDropped(args, argc); return true;
        case SYM_GEN_identifySkill_2603: out = fn_identifySkill(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_getRelatedItems_459: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_700: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__UnidentifiedSkill::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__UnidentifiedSkill::fn_getSkillPool(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UnidentifiedSkill::fn_onDropped(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dropRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_dropRes}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core_items__Exclusive__UnidentifiedSkill::call_static_fn(gd_ctx, SYM_GEN_wasAddedToInventory_659, _ca, 1, _out); return _out; })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__UnidentifiedSkill::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_AddedToStorageBox_2723)))))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_prepareReplacement_446, nullptr, 0);
        gd::GdVal lv_skill = ([&]() { gd::GdVal _ca[] = {this->f_skillPool, gd::GdVal::from_str(&battle_string_literals[89])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_pickRandomEngine_1748, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[90]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_dropRes, lv_skill}))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1482, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UnidentifiedSkill::fn_identifySkill(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dropResult = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_skillDescriptor = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UnidentifiedSkill::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_642, _ca, 1, _out); return _out; })();
    gd::GdVal lv_string = gd::GdVal::null();
    if (gd::gd_truth(lv_wrapInColor)) {
        lv_string = ([&]() { gd::GdVal _ca[] = {([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 2); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[91]), gd::GdVal::null()); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[92]), gd::GdVal::null()); return gd::GdVal::from_dict(d); })()}; return gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[93])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_tr_2826, _ca, 1); })(), SYM_GEN_format_2716, _ca, 1); })();
    }
    else {
        lv_string = ([&]() { gd::GdVal _ca[] = {([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 2); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[91]), gd::native_array_index(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_appearRounds_2827), gd::GdVal::from_int(0LL))); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[92]), gd::native_array_index(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_appearRounds_2827), gd::GdVal::from_int(1LL))); return gd::GdVal::from_dict(d); })()}; return gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[93])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_tr_2826, _ca, 1); })(), SYM_GEN_format_2716, _ca, 1); })();
    }
    lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[94]), lv_string));
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UnidentifiedSkill::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UnidentifiedSkill::fn_getRelatedItemColumns(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(6LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UnidentifiedSkill::fn_getRelatedItemHeight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(80LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UnidentifiedSkill::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[95]), gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[96])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_connect, _ca, 3); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[97]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1482, _ca, 3); })();
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__UnidentifiedSkill(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__UnidentifiedSkill>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__UnidentifiedSkill = {CLS_Gd__gd_core_items__Exclusive__UnidentifiedSkill, "UnidentifiedSkill", "res://gd_core_items/Exclusive/UnidentifiedSkill.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__UnidentifiedSkill, &Gd__gd_core_items__Exclusive__UnidentifiedSkill::get_static_prop_fn, &Gd__gd_core_items__Exclusive__UnidentifiedSkill::call_static_fn};

void Gd__gd_core_items__FancyFencingRapier::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_luckNeeded = gd::GdVal::null();
    this->f_bonusDam = gd::GdVal::null();
    this->f_luck = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__FancyFencingRapier::meta() const { return &META_Gd__gd_core_items__FancyFencingRapier; }
gd::GdVal Gd__gd_core_items__FancyFencingRapier::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__FancyFencingRapier::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__FancyFencingRapier::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_luckNeeded_1874: out = this->f_luckNeeded; return true;
        case SYM_GEN_bonusDam_1875: out = this->f_bonusDam; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__FancyFencingRapier::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_luckNeeded_1874: this->f_luckNeeded = val; return true;
        case SYM_GEN_bonusDam_1875: this->f_bonusDam = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__FancyFencingRapier::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__FancyFencingRapier::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__FancyFencingRapier::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__FancyFencingRapier::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_luckNeeded, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseLucky_347, _ca, 2); })())) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusDam}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
        }
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__FancyFencingRapier::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[98])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_bonusDam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[27])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[38])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__FancyFencingRapier(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__FancyFencingRapier>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__FancyFencingRapier = {CLS_Gd__gd_core_items__FancyFencingRapier, "FancyFencingRapier", "res://gd_core_items/FancyFencingRapier.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__FancyFencingRapier, &Gd__gd_core_items__FancyFencingRapier::get_static_prop_fn, &Gd__gd_core_items__FancyFencingRapier::call_static_fn};

void Gd__gd_core_items__Hammer::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Hammer::meta() const { return &META_Gd__gd_core_items__Hammer; }
gd::GdVal Gd__gd_core_items__Hammer::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Hammer::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Hammer::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Hammer::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Hammer::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN_onFusingAsCatalystFinished_843: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Hammer::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onFusingAsCatalystFinished_843: out = fn_onFusingAsCatalystFinished(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Hammer::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Hammer::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[87])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_330, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Hammer::fn_onFusingAsCatalystFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_onFusingAsCatalystFinished_843, nullptr, 0, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_778, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Hammer::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Hammer(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Hammer>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Hammer = {CLS_Gd__gd_core_items__Hammer, "Hammer", "res://gd_core_items/Hammer.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Hammer, &Gd__gd_core_items__Hammer::get_static_prop_fn, &Gd__gd_core_items__Hammer::call_static_fn};

void Gd__gd_core_items__LuckyClover::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__LuckyClover::meta() const { return &META_Gd__gd_core_items__LuckyClover; }
gd::GdVal Gd__gd_core_items__LuckyClover::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__LuckyClover::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__LuckyClover::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__LuckyClover::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__LuckyClover::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__LuckyClover::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__LuckyClover::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__LuckyClover::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_381, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyClover::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__LuckyClover(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__LuckyClover>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__LuckyClover = {CLS_Gd__gd_core_items__LuckyClover, "LuckyClover", "res://gd_core_items/LuckyClover.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__LuckyClover, &Gd__gd_core_items__LuckyClover::get_static_prop_fn, &Gd__gd_core_items__LuckyClover::call_static_fn};

void Gd__gd_core_items__PoisonGoobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Goobert::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__PoisonGoobert::meta() const { return &META_Gd__gd_core_items__PoisonGoobert; }
gd::GdVal Gd__gd_core_items__PoisonGoobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__PoisonGoobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__PoisonGoobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__PoisonGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__PoisonGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__PoisonGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__PoisonGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__PoisonGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__PoisonGoobert(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__PoisonGoobert>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__PoisonGoobert = {CLS_Gd__gd_core_items__PoisonGoobert, "PoisonGoobert", "res://gd_core_items/PoisonGoobert.gd", &META_Gd__gd_core_items__Goobert, true, _alloc_Gd__gd_core_items__PoisonGoobert, &Gd__gd_core_items__PoisonGoobert::get_static_prop_fn, &Gd__gd_core_items__PoisonGoobert::call_static_fn};

void Gd__gd_core_items__StaminaSack::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bag::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__StaminaSack::meta() const { return &META_Gd__gd_core_items__StaminaSack; }
gd::GdVal Gd__gd_core_items__StaminaSack::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__StaminaSack::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__StaminaSack::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__StaminaSack::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__StaminaSack::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_addToInventory_120: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__StaminaSack::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_addToInventory_120: out = fn_addToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__StaminaSack::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__StaminaSack::fn_addToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__inventory = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__occupiedCells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__placedByPlayer = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv__placedByPlayer = gd::gd_coerce_bool(lv__placedByPlayer);
    (void)([&]() { gd::GdVal _ca[] = {lv__inventory, lv__occupiedCells, lv__placedByPlayer}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN_addToInventory_120, _ca, 3, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::GdVal::from_int(1LL))))) {
        (void)gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeBaseMaxStamina_1272, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaminaSack::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN_onRemoveFromInventory_418, nullptr, 0, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_ownerType, gd::GdVal::from_int(10LL))))) {
        (void)gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeBaseMaxStamina_1272, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaminaSack::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[99])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isTypeInInventory_805, _ca, 1); })())) {
        gd::GdVal lv_stamina = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[100])}; return gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[99])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })(), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
        (void)([&]() { gd::GdVal _ca[] = {lv_stamina}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_giveStaminaRegeneration_1270, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaminaSack::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__StaminaSack(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__StaminaSack>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__StaminaSack = {CLS_Gd__gd_core_items__StaminaSack, "StaminaSack", "res://gd_core_items/StaminaSack.gd", &META_Gd__gd_core_items__Bag, true, _alloc_Gd__gd_core_items__StaminaSack, &Gd__gd_core_items__StaminaSack::get_static_prop_fn, &Gd__gd_core_items__StaminaSack::call_static_fn};

void Gd__gd_core_items__VillainSword::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__VillainSword::meta() const { return &META_Gd__gd_core_items__VillainSword; }
gd::GdVal Gd__gd_core_items__VillainSword::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__VillainSword::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__VillainSword::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__VillainSword::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__VillainSword::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPreCombatStart_125: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__VillainSword::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPreCombatStart_125: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__VillainSword::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__VillainSword::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), SYM_GEN_isMeleeWeapon_1722, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__VillainSword::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1698 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1699 = (_t1698.kind == gd::GdVal::Kind::Arr) ? _t1698.arr : nullptr;
        uint32_t _len__t1700 = _t1699 ? _t1699->len : 0u;
        for (uint32_t _t1700 = 0; _t1700 < _len__t1700; ++_t1700) {
            gd::GdVal lv_item = _t1699->data[_t1700];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceBonusDamage_310, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__VillainSword::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__VillainSword(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__VillainSword>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__VillainSword = {CLS_Gd__gd_core_items__VillainSword, "VillainSword", "res://gd_core_items/VillainSword.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__VillainSword, &Gd__gd_core_items__VillainSword::get_static_prop_fn, &Gd__gd_core_items__VillainSword::call_static_fn};
