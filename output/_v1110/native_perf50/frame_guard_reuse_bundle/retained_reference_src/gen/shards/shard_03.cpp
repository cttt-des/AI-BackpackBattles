#include "../../native_inline_dispatch.hpp"
#include "../../native_scalar_equal.hpp"
#include "../../native_array_index.hpp"
#pragma STDC FP_CONTRACT OFF
#include "../../native_targeted_timers.hpp"
#include "../../native_active_cooldowns.hpp"

#include "../hdrs/Gd__gd_core__CoreContext.hpp"
#include "../hdrs/Gd__gd_core__CoreGrid.hpp"
#include "../hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "../hdrs/Gd__gd_core__CoreItem.hpp"
#include "../hdrs/Gd__gd_core__AceofSpades.hpp"
#include "../hdrs/Gd__gd_core__Dagger.hpp"
#include "../hdrs/Gd__gd_core__CoreCombat.hpp"
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
#include "../hdrs/Gd__gd_core_items__Exclusive__AmuletofDarkness.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__WisdomPuppy.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BionicArmor.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Broccotree.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Chess__BlackBishop.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ChromeCube.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DeathLotus.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DualWielding.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ExtraBags.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Frostbite.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__HeartShield.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__JustStats.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Lootbox.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MercuryElemental.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ParadiseBirb.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PoweroftheMoon.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__RainbowOrb.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ScholarBag.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Sloth.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SpicyBanana.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__StoneGolem.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__TimeMelting.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__WaterElemental.hpp"
#include "../hdrs/Gd__gd_core_items__Gems__CorruptedCrystal.hpp"
#include "../hdrs/Gd__gd_core_items__HoloFireLizard.hpp"
#include "../hdrs/Gd__gd_core_items__MoonShield.hpp"
#include "../hdrs/Gd__gd_core_items__RainbowGoobertRanger.hpp"
#include "../hdrs/Gd__gd_core_items__StrongStoneSkinPotion.hpp"

namespace {
constexpr gd::GdStr battle_string_literals[] = {
    {"luck", 4u, 4145017712u},
    {"spikes", 6u, 439106706u},
    {"character_stunned", 17u, 4164697708u},
    {"onStun", 6u, 2496468248u},
    {"endCombat", 9u, 1451178710u},
    {"sort_TriggerPriority", 20u, 1247176926u},
    {"clashTrainingSwords", 19u, 1548656078u},
    {"activateTraining", 16u, 4123765630u},
    {"combat_start", 12u, 3632592994u},
    {"replayHiddenLogEvent", 20u, 29295192u},
    {"Start", 5u, 182978943u},
    {"fatigue_start", 13u, 1129723937u},
    {"fatigue_damage_changed", 22u, 2103754981u},
    {"Tick", 4u, 3724338628u},
    {"combat_end", 10u, 2262066087u},
    {"round_result", 12u, 1391377173u},
    {"Hide", 4u, 3775691725u},
    {"", 0u, 2166136261u},
    {"randf", 5u, 400455952u},
    {"flipWeighted", 12u, 101400015u},
    {"%s:%d:%s", 8u, 2520059110u},
    {"source", 6u, 466561496u},
    {"line", 4u, 400234023u},
    {"function", 8u, 2664841801u},
    {"<-", 2u, 2767665890u},
    {"EVENT", 5u, 236776447u},
    {"randf_range", 11u, 1285829098u},
    {"randi_range", 11u, 488468259u},
    {"pickRandomElement", 17u, 3446313617u},
    {"randi", 5u, 652120237u},
    {"Gshuffle", 8u, 3464886495u},
    {"Gpick", 5u, 3370211175u},
    {"character_poison_changed", 24u, 65736246u},
    {"onOpponentPoisonChanged", 23u, 839266911u},
    {"pre_take_damage", 15u, 2330033632u},
    {"preTakeDamage", 13u, 311913432u},
    {"character_attacked", 18u, 2439462988u},
    {"onCharacterAttacked", 19u, 1493935206u},
    {"damblock", 8u, 2582642454u},
    {"blocked", 7u, 1516072627u},
    {"Bagtacular", 10u, 2131747329u},
    {"stamina", 7u, 3875003702u},
    {"lifesteal", 9u, 1515578962u},
    {"healamp", 7u, 54482251u},
    {"dam", 3u, 4031722721u},
    {"regen", 5u, 16724762u},
    {"attacked", 8u, 3381721668u},
    {"onWeaponAttacked", 16u, 3445043441u},
    {"onOpponentDamaged", 17u, 568571164u},
    {"activated", 9u, 2866667388u},
    {"onItemActivated", 15u, 1109670618u},
    {"AOD t=", 6u, 871672730u},
    {"damt", 4u, 3786393231u},
    {"character_healed", 16u, 2989261042u},
    {"onHealOrBlockChanged", 20u, 999114700u},
    {"character_block_changed", 23u, 4278945901u},
    {"staminaregen", 12u, 2522043943u},
    {"healtht", 7u, 1555997217u},
    {"maxstamina", 10u, 2834798586u},
    {"staminat1", 9u, 1386159221u},
    {"staminat2", 9u, 1335826364u},
    {"empower", 7u, 2037162760u},
    {"block", 5u, 3943480674u},
    {"character_regeneration_changed", 30u, 2797934681u},
    {"onRegenChanged", 14u, 661197895u},
    {"luckt", 5u, 4061892428u},
    {"debuffs", 7u, 504032524u},
    {"healreduction", 13u, 2587190196u},
    {"healthreduction", 15u, 4039077536u},
    {"character_damaged", 17u, 745527748u},
    {"onDamaged", 9u, 2303747743u},
    {"mana", 4u, 3650585354u},
    {"buffs", 5u, 2149256365u},
    {"speed", 5u, 2072037248u},
    {"sales", 5u, 2258376375u},
    {"bagweight", 9u, 1204315077u},
    {"character_vampirism_changed", 27u, 75150398u},
    {"onVampirismChanged", 18u, 3624660862u},
    {"character_cold_changed", 22u, 3066049132u},
    {"onOpponentColdChanged", 21u, 3656074605u},
    {"maxhealth", 9u, 429334299u},
    {"regent", 6u, 4290639402u},
    {"max_regen", 9u, 854804219u},
    {"round", 5u, 1326178875u},
    {"TOOLTIP_Always Offered", 22u, 1323998851u},
    {"\n\n", 2u, 2274317941u},
    {"generateItems", 13u, 3717244974u},
    {"gold", 4u, 3966162835u},
    {"dropped", 7u, 3229108261u},
    {"onDropped", 9u, 1334518102u},
    {"onOpponentAttacked", 18u, 21269012u},
    {"character_used_stamina", 22u, 4094391974u},
    {"onStaminaUsed", 13u, 3121214912u},
    {"poison", 6u, 3470992305u},
    {"poison2", 7u, 848357177u},
    {"staminat", 8u, 3660664550u},
    {"max", 3u, 3617776409u},
    {"onFatigueStarted", 16u, 504449962u},
    {"onMoonArmorActivated", 20u, 2016617511u},
    {"onMoonShiedActivated", 20u, 838698207u},
    {"Moon Armor", 10u, 3232704711u},
    {"Moon Shield", 11u, 1630382969u},
    {"Mana Orb", 8u, 293290099u},
    {"time", 4u, 1564253156u},
    {"blind", 5u, 274826164u},
    {"vampirism", 9u, 773404377u},
    {"$n_magic", 8u, 536624491u},
    {"$n_vampiric", 11u, 1179443659u},
    {"$n_holy", 7u, 2980935886u},
    {"$n_dark", 7u, 3365736372u},
    {"n_magic", 7u, 1294501073u},
    {"n_vampiric", 10u, 665009097u},
    {"n_holy", 6u, 2117373556u},
    {"n_dark", 6u, 2718798678u},
    {"maxhealth_base", 14u, 362443289u},
    {"maxhealth_item", 14u, 1253390883u},
    {"dur_stun", 8u, 1388942617u},
    {"dur_stun_amulet", 15u, 2268929100u},
    {"$s[", 3u, 4111241473u},
    {"[shake]", 7u, 3662855435u},
    {"$s]", 3u, 4144796711u},
    {"[/shake]", 8u, 1700033762u},
    {"buffs_amulet", 12u, 3453122904u},
    {"onBananaActivated", 17u, 4013418872u},
    {"heal", 4u, 979982427u},
    {"Banana", 6u, 3336821872u},
    {"Mananana", 8u, 62091374u},
    {"heat", 4u, 577319571u},
    {"bonusdam", 8u, 3306431450u},
    {"Bag of Stones", 13u, 3970243028u},
    {"dur", 3u, 3509645056u},
    {"bonusdur", 8u, 3225794759u},
    {"character_mana_changed", 22u, 798563205u},
    {"onManaChanged", 13u, 3105672029u},
    {"used", 4u, 1786277552u},
    {"mana2", 5u, 3246625064u},
    {"cold", 4u, 3930381583u},
    {"manat1", 6u, 1070273905u},
    {"manat2", 6u, 1019941048u},
    {"manat3", 6u, 1036718667u},
    {"onOpponentDebuffsChanged", 24u, 915890936u},
    {"damfactor", 9u, 2846421882u},
    {"gave_block", 10u, 905150934u},
    {"onItemGaveBlock", 15u, 3788065731u},
};
}

void replay_host_before_idle(int64_t control, gd::GdObj* context, double combat_time);

void Gd__gd_core__AceofSpades::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Card::init_fields(gd_ctx);
    this->f_spadesParticles = gd::GdVal::null();
    this->f_luck = gd::GdVal::null();
    this->f_spikes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__AceofSpades::meta() const { return &META_Gd__gd_core__AceofSpades; }
gd::GdVal Gd__gd_core__AceofSpades::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Card::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__AceofSpades::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__AceofSpades::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_spadesParticles_896: out = this->f_spadesParticles; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        default: break;
    }
    return Gd__gd_core__Card::get_prop(prop, out);
}
bool Gd__gd_core__AceofSpades::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spadesParticles_896: this->f_spadesParticles = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__AceofSpades::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_890: return true;
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Card::has_own_method(m);
}
bool Gd__gd_core__AceofSpades::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_890: out = fn_cardSecondaryEffectActive(args, argc); return true;
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__AceofSpades::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__AceofSpades::fn_cardSecondaryEffectActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::native_scalar_eq(gd::gd_mod(gd_ctx, this->f_chainPosition, gd::GdVal::from_int(2LL)), gd::GdVal::from_int(1LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__AceofSpades::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveCritTokens_314, _ca, 1); })();
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cardSecondaryEffectActive_890, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__AceofSpades::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Card::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[0])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[1])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__AceofSpades(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__AceofSpades>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,0u); return object; }
const gd::GdClassMeta META_Gd__gd_core__AceofSpades = {CLS_Gd__gd_core__AceofSpades, "AceofSpades", "res://gd_core/AceofSpades.gd", &META_Gd__gd_core__Card, false, _alloc_Gd__gd_core__AceofSpades, &Gd__gd_core__AceofSpades::get_static_prop_fn, &Gd__gd_core__AceofSpades::call_static_fn};

void Gd__gd_core__Dagger::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__Dagger::meta() const { return &META_Gd__gd_core__Dagger; }
gd::GdVal Gd__gd_core__Dagger::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Dagger::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Dagger::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__Dagger::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Dagger::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepare_122: return true;
        case SYM_GEN_onStun_946: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Dagger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepare_122: out = fn_prepare(args, argc); return true;
        case SYM_GEN_onStun_946: out = fn_onStun(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Dagger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Dagger::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN_prepare_122, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[2]), gd::GdVal::from_str(&battle_string_literals[3])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Dagger::fn_onStun(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_attack_941, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Dagger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Dagger(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__Dagger>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,55u); return object; }
const gd::GdClassMeta META_Gd__gd_core__Dagger = {CLS_Gd__gd_core__Dagger, "Dagger", "res://gd_core/Dagger.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__Dagger, &Gd__gd_core__Dagger::get_static_prop_fn, &Gd__gd_core__Dagger::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreCombat_RoundResult[] = {{"Win", 0LL}, {"Loss", 1LL}, {"Draw", 2LL}, {"RunOver", 3LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreCombat_RoundResult = {"RoundResult", _ekv_Gd__gd_core__CoreCombat_RoundResult, 4u};
void Gd__gd_core__CoreCombat::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_ctx = gd::GdVal::null();
    this->f_player = gd::GdVal::null();
    this->f_opponent = gd::GdVal::null();
    this->f_ordered_items = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_result = gd::gd_coerce_int(gd::gd_neg(gd::GdVal::from_int(1LL)));
    this->f_fight_ended = gd::GdVal::from_bool(false);
    this->f_combat_time = gd::GdVal::from_float(0.0);
    this->f_fatigue_counter = gd::GdVal::from_int(0LL);
    this->f_fatigue_started = gd::GdVal::from_bool(false);
    this->f_fatigue_next_tick = gd::GdVal::from_float(0.0);
    this->f_fatigue_interval = gd::GdVal::from_float(0.0);
    this->f_time_advance = gd::GdVal::from_float(0.0);
    this->f_speed_scale = gd::GdVal::from_float(1.0);
    this->f__activate_countdown = gd::GdVal::from_float(0.0);
    this->f_activated = gd::GdVal::from_bool(false);
    this->f__track_hidden_log = gd::GdVal::from_bool(false);
    this->f__tick_timer_left = gd::GdVal::from_float(0.0);
    this->f__tick_timer_active = gd::GdVal::from_bool(false);
    this->f_max_time = gd::GdVal::from_float(180.0);
    this->f_timed_out = gd::GdVal::from_bool(false);
    this->f__pending_deferred = gd::GdVal::from_bool(false);
}
const gd::GdClassMeta* Gd__gd_core__CoreCombat::meta() const { return &META_Gd__gd_core__CoreCombat; }
gd::GdVal Gd__gd_core__CoreCombat::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_RoundResult_1340: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreCombat_RoundResult);
        case SYM_GEN_FATIGUE_TIME_1299: return gd::GdVal::from_float(17.0);
        case SYM_GEN_FATIGUE_START_DELAY_1300: return gd::GdVal::from_float(3.0);
        case SYM_GEN_FATIGUE_SLOW_TIME_1301: return gd::GdVal::from_float(60.0);
        case SYM_GEN_CoreItemSort_1344: return gd::GdVal::from_cls(&META_Gd__gd_core__CoreCombat__INNER__CoreItemSort);
        default: break;
    }
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreCombat::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    switch (prop) {
        case SYM_GEN_RoundResult_1340: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreCombat_RoundResult); return true;
        case SYM_GEN_FATIGUE_TIME_1299: out = gd::GdVal::from_float(17.0); return true;
        case SYM_GEN_FATIGUE_START_DELAY_1300: out = gd::GdVal::from_float(3.0); return true;
        case SYM_GEN_FATIGUE_SLOW_TIME_1301: out = gd::GdVal::from_float(60.0); return true;
        case SYM_GEN_CoreItemSort_1344: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreCombat__INNER__CoreItemSort); return true;
        default: break;
    }
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreCombat::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_ctx_3: out = this->f_ctx; return true;
        case SYM_GEN_player_1302: out = this->f_player; return true;
        case SYM_GEN_opponent_75: out = this->f_opponent; return true;
        case SYM_GEN_ordered_items_1303: out = this->f_ordered_items; return true;
        case SYM_GEN_result_1304: out = this->f_result; return true;
        case SYM_GEN_fight_ended_1305: out = this->f_fight_ended; return true;
        case SYM_GEN_combat_time_1306: out = this->f_combat_time; return true;
        case SYM_GEN_fatigue_counter_1307: out = this->f_fatigue_counter; return true;
        case SYM_GEN_fatigue_started_1308: out = this->f_fatigue_started; return true;
        case SYM_GEN_fatigue_next_tick_1309: out = this->f_fatigue_next_tick; return true;
        case SYM_GEN_fatigue_interval_1310: out = this->f_fatigue_interval; return true;
        case SYM_GEN_time_advance_1311: out = this->f_time_advance; return true;
        case SYM_GEN_speed_scale_1312: out = this->f_speed_scale; return true;
        case SYM_GEN__activate_countdown_1313: out = this->f__activate_countdown; return true;
        case SYM_GEN_activated_1314: out = this->f_activated; return true;
        case SYM_GEN__track_hidden_log_1315: out = this->f__track_hidden_log; return true;
        case SYM_GEN__tick_timer_left_1111: out = this->f__tick_timer_left; return true;
        case SYM_GEN__tick_timer_active_1112: out = this->f__tick_timer_active; return true;
        case SYM_GEN_max_time_1316: out = this->f_max_time; return true;
        case SYM_GEN_timed_out_1317: out = this->f_timed_out; return true;
        case SYM_GEN__pending_deferred_1318: out = this->f__pending_deferred; return true;
        case SYM_GEN_RoundResult_1340: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreCombat_RoundResult); return true;
        case SYM_GEN_CoreItemSort_1344: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreCombat__INNER__CoreItemSort); return true;
        case SYM_GEN_FATIGUE_TIME_1299: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_FATIGUE_START_DELAY_1300: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_FATIGUE_SLOW_TIME_1301: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreCombat::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_ctx_3: this->f_ctx = val; return true;
        case SYM_GEN_player_1302: this->f_player = val; return true;
        case SYM_GEN_opponent_75: this->f_opponent = val; return true;
        case SYM_GEN_ordered_items_1303: this->f_ordered_items = val; return true;
        case SYM_GEN_result_1304: this->f_result = gd::gd_coerce_int(val); return true;
        case SYM_GEN_fight_ended_1305: this->f_fight_ended = val; return true;
        case SYM_GEN_combat_time_1306: this->f_combat_time = val; return true;
        case SYM_GEN_fatigue_counter_1307: this->f_fatigue_counter = val; return true;
        case SYM_GEN_fatigue_started_1308: this->f_fatigue_started = val; return true;
        case SYM_GEN_fatigue_next_tick_1309: this->f_fatigue_next_tick = val; return true;
        case SYM_GEN_fatigue_interval_1310: this->f_fatigue_interval = val; return true;
        case SYM_GEN_time_advance_1311: this->f_time_advance = val; return true;
        case SYM_GEN_speed_scale_1312: this->f_speed_scale = val; return true;
        case SYM_GEN__activate_countdown_1313: this->f__activate_countdown = val; return true;
        case SYM_GEN_activated_1314: this->f_activated = val; return true;
        case SYM_GEN__track_hidden_log_1315: this->f__track_hidden_log = val; return true;
        case SYM_GEN__tick_timer_left_1111: this->f__tick_timer_left = val; return true;
        case SYM_GEN__tick_timer_active_1112: this->f__tick_timer_active = val; return true;
        case SYM_GEN_max_time_1316: this->f_max_time = val; return true;
        case SYM_GEN_timed_out_1317: this->f_timed_out = val; return true;
        case SYM_GEN__pending_deferred_1318: this->f__pending_deferred = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreCombat::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_setup_72: return true;
        case SYM_GEN_startBattle_1319: return true;
        case SYM_GEN_prepareItems_1320: return true;
        case SYM_GEN_resetInventories_1321: return true;
        case SYM_GEN_activateItems_1322: return true;
        case SYM_GEN_clashTrainingSwords_1323: return true;
        case SYM_GEN_activateTraining_1324: return true;
        case SYM_GEN_physicsTick_134: return true;
        case SYM_GEN_run_1325: return true;
        case SYM_GEN__fatigueTick_1326: return true;
        case SYM_GEN_startFatigue_1327: return true;
        case SYM_GEN_dealFatigueDamage_1328: return true;
        case SYM_GEN_hasFatigueStarted_1329: return true;
        case SYM_GEN_advanceTime_1330: return true;
        case SYM_GEN_getEffectiveTime_1331: return true;
        case SYM_GEN_endCombat_1332: return true;
        case SYM_GEN_forceLoseCombat_1333: return true;
        case SYM_GEN__flushDeferred_1334: return true;
        case SYM_GEN_combatEndDeferred_1335: return true;
        case SYM_GEN_playerWins_1336: return true;
        case SYM_GEN_winner_1337: return true;
        case SYM_GEN__tickCharacterTimers_1338: return true;
        case SYM_GEN_stepCharacterIdle_1339: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreCombat::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_setup_72: out = fn_setup(args, argc); return true;
        case SYM_GEN_startBattle_1319: out = fn_startBattle(args, argc); return true;
        case SYM_GEN_prepareItems_1320: out = fn_prepareItems(args, argc); return true;
        case SYM_GEN_resetInventories_1321: out = fn_resetInventories(args, argc); return true;
        case SYM_GEN_activateItems_1322: out = fn_activateItems(args, argc); return true;
        case SYM_GEN_clashTrainingSwords_1323: out = fn_clashTrainingSwords(args, argc); return true;
        case SYM_GEN_activateTraining_1324: out = fn_activateTraining(args, argc); return true;
        case SYM_GEN_physicsTick_134: out = fn_physicsTick(args, argc); return true;
        case SYM_GEN_run_1325: out = fn_run(args, argc); return true;
        case SYM_GEN__fatigueTick_1326: out = fn__fatigueTick(args, argc); return true;
        case SYM_GEN_startFatigue_1327: out = fn_startFatigue(args, argc); return true;
        case SYM_GEN_dealFatigueDamage_1328: out = fn_dealFatigueDamage(args, argc); return true;
        case SYM_GEN_hasFatigueStarted_1329: out = fn_hasFatigueStarted(args, argc); return true;
        case SYM_GEN_advanceTime_1330: out = fn_advanceTime(args, argc); return true;
        case SYM_GEN_getEffectiveTime_1331: out = fn_getEffectiveTime(args, argc); return true;
        case SYM_GEN_endCombat_1332: out = fn_endCombat(args, argc); return true;
        case SYM_GEN_forceLoseCombat_1333: out = fn_forceLoseCombat(args, argc); return true;
        case SYM_GEN__flushDeferred_1334: out = fn__flushDeferred(args, argc); return true;
        case SYM_GEN_combatEndDeferred_1335: out = fn_combatEndDeferred(args, argc); return true;
        case SYM_GEN_playerWins_1336: out = fn_playerWins(args, argc); return true;
        case SYM_GEN_winner_1337: out = fn_winner(args, argc); return true;
        case SYM_GEN__tickCharacterTimers_1338: out = fn__tickCharacterTimers(args, argc); return true;
        case SYM_GEN_stepCharacterIdle_1339: out = fn_stepCharacterIdle(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreCombat::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core__CoreCombat::fn__init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__ctx = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    this->f_ctx = lv__ctx;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_setup(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__player = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__opponent = (_argc > 1) ? _args[1] : gd::GdVal::null();
    this->f_player = lv__player;
    this->f_opponent = lv__opponent;
    gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1302, lv__player);
    gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_opponent_75, lv__opponent);
    gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_1420, gd::GdVal::from_obj(this));
    (void)([&]() { gd::GdVal _ca[] = {this->f_opponent}; return gd::native_inline_call(gd_ctx, this->f_player, SYM_GEN_setOpponent_1129, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_player}; return gd::native_inline_call(gd_ctx, this->f_opponent, SYM_GEN_setOpponent_1129, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, this->f_player, SYM_GEN_clearCharacterDiedHandlers_1131, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, this->f_opponent, SYM_GEN_clearCharacterDiedHandlers_1131, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {([&]() { auto* fr = gd_ctx.arena.make<gd::GdFuncRef>(); gd::GdVal inst = gd::GdVal::from_obj(this); gd::GdVal mname = gd::GdVal::from_str(&battle_string_literals[4]); fr->instance = (inst.kind == gd::GdVal::Kind::Obj) ? inst.obj : nullptr; fr->method = (mname.kind == gd::GdVal::Kind::Str && mname.str) ? gd::intern_sym(std::string_view(mname.str->data, mname.str->len)) : gd::SYM_NONE; return gd::GdVal::from_funcref(fr); })()}; return gd::native_inline_call(gd_ctx, this->f_player, SYM_GEN_registerCharacterDied_1130, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { auto* fr = gd_ctx.arena.make<gd::GdFuncRef>(); gd::GdVal inst = gd::GdVal::from_obj(this); gd::GdVal mname = gd::GdVal::from_str(&battle_string_literals[4]); fr->instance = (inst.kind == gd::GdVal::Kind::Obj) ? inst.obj : nullptr; fr->method = (mname.kind == gd::GdVal::Kind::Str && mname.str) ? gd::intern_sym(std::string_view(mname.str->data, mname.str->len)) : gd::SYM_NONE; return gd::GdVal::from_funcref(fr); })()}; return gd::native_inline_call(gd_ctx, this->f_opponent, SYM_GEN_registerCharacterDied_1130, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_startBattle(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_player_items = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_opponent_items = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_preordered = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    lv_preordered = gd::gd_coerce_bool(lv_preordered);
    gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_fight_ended_1305, gd::GdVal::from_bool(false));
    this->f_fight_ended = gd::GdVal::from_bool(false);
    this->f_result = gd::gd_coerce_int(gd::gd_neg(gd::GdVal::from_int(1LL)));
    this->f_timed_out = gd::GdVal::from_bool(false);
    this->f_activated = gd::GdVal::from_bool(false);
    this->f__pending_deferred = gd::GdVal::from_bool(false);
    gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_out_of_stamina_count_1432, gd::GdVal::from_int(0LL));
    this->f_combat_time = gd::GdVal::from_float(0.0);
    gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_time_1306, gd::GdVal::from_float(0.0));
    this->f_fatigue_counter = gd::GdVal::from_int(0LL);
    this->f_fatigue_started = gd::GdVal::from_bool(false);
    this->f_fatigue_interval = gd::GdVal::from_float(0.0);
    this->f_fatigue_next_tick = gd::GdVal::from_float(0.0);
    this->f_speed_scale = gd::GdVal::from_float(1.0);
    if (gd::native_scalar_truth(lv_preordered)) {
        this->f_ordered_items = gd::gd_add(gd_ctx, lv_player_items, lv_opponent_items);
        { gd::GdVal _t728 = gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406); gd::set_prop(gd_ctx, _t728, SYM_GEN_globalChainOpen_1733, gd::GdVal::from_bool(true)); }
    }
    else {
        gd::GdVal lv_p_items = gd::native_inline_call(gd_ctx, lv_player_items, gd::SYM_duplicate, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_p_items}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_shuffle, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCombat__INNER__CoreItemSort), gd::SYM_new, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[5])}; return gd::native_inline_call(gd_ctx, lv_p_items, gd::SYM_sort_custom, _ca, 2); })();
        gd::GdVal lv_o_items = gd::native_inline_call(gd_ctx, lv_opponent_items, gd::SYM_duplicate, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_o_items}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_shuffle, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCombat__INNER__CoreItemSort), gd::SYM_new, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[5])}; return gd::native_inline_call(gd_ctx, lv_o_items, gd::SYM_sort_custom, _ca, 2); })();
        this->f_ordered_items = gd::gd_add(gd_ctx, lv_p_items, lv_o_items);
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_restoreEngineRng_1489, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_resetCriticalShake_1495, nullptr, 0);
    this->f__track_hidden_log = ([&]() { gd::GdVal _ca[] = {this->f_ordered_items}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_prepareHiddenLog_1355, _ca, 1); })();
    if (gd::native_scalar_truth(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_training_start_1452))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[6]), gd::GdVal::from_float(1.0)}; return gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_callDelayed_1479, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[7]), gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreContext), SYM_GEN_COMBAT_DELAY_1405)}; return gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_callDelayed_1479, _ca, 3); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {this->f_ordered_items}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_prepareItems_1320, _ca, 1); })();
    this->f__activate_countdown = gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreContext), SYM_GEN_COMBAT_DELAY_1405);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_prepareItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_items = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t729 = gd::gd_iter_seq(gd_ctx.arena, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {this->f_player, this->f_opponent})));
        gd::GdArr* _t730 = (_t729.kind == gd::GdVal::Kind::Arr) ? _t729.arr : nullptr;
        uint32_t _len__t731 = _t730 ? _t730->len : 0u;
        for (uint32_t _t731 = 0; _t731 < _len__t731; ++_t731) {
            gd::GdVal lv_character = _t730->data[_t731];
            if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, lv_character, SYM_GEN_inventory_5), gd::GdVal::null())))) {
                gd::set_prop(gd_ctx, lv_character, SYM_GEN_inventory_5, ([&]() { gd::GdVal _ca[] = {lv_character}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreGrid), gd::SYM_new, _ca, 1); })());
            }
        }
    }
    {
        gd::GdVal _t732 = gd::gd_iter_seq(gd_ctx.arena, lv_items);
        gd::GdArr* _t733 = (_t732.kind == gd::GdVal::Kind::Arr) ? _t732.arr : nullptr;
        uint32_t _len__t734 = _t733 ? _t733->len : 0u;
        for (uint32_t _t734 = 0; _t734 < _len__t734; ++_t734) {
            gd::GdVal lv_item = _t733->data[_t734];
            if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_ctx_3), gd::GdVal::null())))) {
                gd::set_prop(gd_ctx, lv_item, SYM_GEN_ctx_3, this->f_ctx);
            }
            if (gd::native_scalar_truth(gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_placed_6))) {
                continue;
            }
            gd::GdVal lv_ch = gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0);
            if (gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_ch, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, lv_ch, SYM_GEN_inventory_5), gd::GdVal::null())))) : gd::GdVal::from_bool(false)))) {
                gd::set_prop(gd_ctx, lv_ch, SYM_GEN_inventory_5, ([&]() { gd::GdVal _ca[] = {lv_ch}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreGrid), gd::SYM_new, _ca, 1); })());
            }
            gd::GdVal lv_grid = (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_ch, gd::GdVal::null()))) ? (gd::native_inline_get_prop(gd_ctx, lv_ch, SYM_GEN_inventory_5)) : (gd::native_inline_get_prop(gd_ctx, this->f_player, SYM_GEN_inventory_5)));
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_occupiedCells_52)}; return gd::native_inline_call(gd_ctx, lv_grid, SYM_GEN_addItem_1618, _ca, 2); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, this->f_player, SYM_GEN_prepare_122, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, this->f_opponent, SYM_GEN_prepare_122, nullptr, 0);
    {
        gd::GdVal _t735 = gd::gd_iter_seq(gd_ctx.arena, lv_items);
        gd::GdArr* _t736 = (_t735.kind == gd::GdVal::Kind::Arr) ? _t735.arr : nullptr;
        uint32_t _len__t737 = _t736 ? _t736->len : 0u;
        for (uint32_t _t737 = 0; _t737 < _len__t737; ++_t737) {
            gd::GdVal lv_item = _t736->data[_t737];
            (void)gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_prepare_122, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_resetInventories(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t738 = gd::gd_iter_seq(gd_ctx.arena, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {this->f_player, this->f_opponent})));
        gd::GdArr* _t739 = (_t738.kind == gd::GdVal::Kind::Arr) ? _t738.arr : nullptr;
        uint32_t _len__t740 = _t739 ? _t739->len : 0u;
        for (uint32_t _t740 = 0; _t740 < _len__t740; ++_t740) {
            gd::GdVal lv_character = _t739->data[_t740];
            if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, lv_character, SYM_GEN_inventory_5), gd::GdVal::null())))) {
                (void)gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_character, SYM_GEN_inventory_5), SYM_GEN_cleanUp_1622, nullptr, 0);
            }
            {
                gd::GdVal _t741 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, lv_character, SYM_GEN_items_1092));
                gd::GdArr* _t742 = (_t741.kind == gd::GdVal::Kind::Arr) ? _t741.arr : nullptr;
                uint32_t _len__t743 = _t742 ? _t742->len : 0u;
                for (uint32_t _t743 = 0; _t743 < _len__t743; ++_t743) {
                    gd::GdVal lv_item = _t742->data[_t743];
                    gd::set_prop(gd_ctx, lv_item, SYM_GEN_placed_6, gd::GdVal::from_bool(false));
                    gd::set_prop(gd_ctx, lv_item, SYM_GEN_consumed_60, gd::GdVal::from_bool(false));
                }
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_activateItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_items = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_restoreEngineRng_1489, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_restoreReplayBuffs_1499, nullptr, 0);
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_activation_rng_state_1443), gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_activation_rng_state_1443))}; return gd::native_inline_call(gd_ctx, this->f_ctx, gd::SYM_set_state, _ca, 1); })();
    }
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_idle_timer_initial_1444), gd::SYM_size, nullptr, 0), gd::GdVal::from_int(2LL))))) {
        gd::set_prop(gd_ctx, this->f_player, SYM_GEN__idle_animation_left_1126, gd::gd_coerce_float(gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_idle_timer_initial_1444), gd::GdVal::from_int(0LL))));
        gd::set_prop(gd_ctx, this->f_opponent, SYM_GEN__idle_animation_left_1126, gd::gd_coerce_float(gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_idle_timer_initial_1444), gd::GdVal::from_int(1LL))));
    }
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_flicker_initial_1469), gd::GdVal::null())))) {
        (void)gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_restoreFlickers_1504, nullptr, 0);
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[8])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_emit_signal, _ca, 1); })();
    this->f_combat_time = gd::GdVal::from_float(0.0);
    gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_time_1306, gd::GdVal::from_float(0.0));
    this->f_fatigue_next_tick = gd::gd_sub(gd::gd_sub(Gd__gd_core__CoreCombat::get_static_const_or_enum(gd_ctx, SYM_GEN_FATIGUE_TIME_1299), Gd__gd_core__CoreCombat::get_static_const_or_enum(gd_ctx, SYM_GEN_FATIGUE_START_DELAY_1300)), this->f_time_advance);
    this->f_fatigue_interval = gd::GdVal::from_float(0.0);
    this->f_fatigue_started = gd::GdVal::from_bool(false);
    (void)gd::native_inline_call(gd_ctx, this->f_player, SYM_GEN_combatStart_127, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, this->f_opponent, SYM_GEN_combatStart_127, nullptr, 0);
    {
        gd::GdVal _t744 = gd::gd_iter_seq(gd_ctx.arena, lv_items);
        gd::GdArr* _t745 = (_t744.kind == gd::GdVal::Kind::Arr) ? _t744.arr : nullptr;
        uint32_t _len__t746 = _t745 ? _t745->len : 0u;
        for (uint32_t _t746 = 0; _t746 < _len__t746; ++_t746) {
            gd::GdVal lv_item = _t745->data[_t746];
            (void)gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_preCombatStart_124, nullptr, 0);
        }
    }
    {
        gd::GdVal _t747 = gd::gd_iter_seq(gd_ctx.arena, lv_items);
        gd::GdArr* _t748 = (_t747.kind == gd::GdVal::Kind::Arr) ? _t747.arr : nullptr;
        uint32_t _len__t749 = _t748 ? _t748->len : 0u;
        for (uint32_t _t749 = 0; _t749 < _len__t749; ++_t749) {
            gd::GdVal lv_item = _t748->data[_t749];
            (void)gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_combatStart_127, nullptr, 0);
        }
    }
    {
        gd::GdVal _t750 = gd::gd_iter_seq(gd_ctx.arena, lv_items);
        gd::GdArr* _t751 = (_t750.kind == gd::GdVal::Kind::Arr) ? _t750.arr : nullptr;
        uint32_t _len__t752 = _t751 ? _t751->len : 0u;
        for (uint32_t _t752 = 0; _t752 < _len__t752; ++_t752) {
            gd::GdVal lv_item = _t751->data[_t752];
            (void)gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_postCombatStart_128, nullptr, 0);
        }
    }
    this->f_activated = gd::GdVal::from_bool(true);
    (void)gd::native_inline_call(gd_ctx, this->f_player, SYM_GEN_rebuildTimerSeen_139, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, this->f_opponent, SYM_GEN_rebuildTimerSeen_139, nullptr, 0);
    {
        gd::GdVal _t753 = gd::gd_iter_seq(gd_ctx.arena, lv_items);
        gd::GdArr* _t754 = (_t753.kind == gd::GdVal::Kind::Arr) ? _t753.arr : nullptr;
        uint32_t _len__t755 = _t754 ? _t754->len : 0u;
        for (uint32_t _t755 = 0; _t755 < _len__t755; ++_t755) {
            gd::GdVal lv_item = _t754->data[_t755];
            (void)gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_rebuildTimerSeen_139, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_clashTrainingSwords(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_activateTraining(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_ordered_items}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activateItems_1322, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_physicsTick(const gd::GdVal* _args, int _argc) {
    gd::NativeFrameSegmentSnapshot native_segment_snapshot;
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    // The native battle constructs exact CoreContext and CoreCharacter objects.
    const auto context = [this] { return static_cast<Gd__gd_core__CoreContext*>(this->f_ctx.obj); };
    const auto opponent = [this] { return static_cast<Gd__gd_core__CoreCharacter*>(this->f_opponent.obj); };
    const auto player = [this] { return static_cast<Gd__gd_core__CoreCharacter*>(this->f_player.obj); };
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (gd::native_scalar_truth(this->f__pending_deferred)) {
        (void)this->fn__flushDeferred(nullptr, 0);
        return gd::GdVal::null();
    }
    if (gd::native_scalar_truth(this->f_fight_ended)) {
        return gd::GdVal::null();
    }
    if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(this->f_activated)))) {
        if (gd::native_scalar_truth(this->f__track_hidden_log)) {
            (void)([&]() { gd::GdVal _ca[] = {context()->f_combat_log, gd::GdVal::from_str(&battle_string_literals[9])}; return context()->fn_defer(_ca, 2); })();
        }
        (void)context()->fn_flushDeferred(nullptr, 0);
        (void)context()->fn_flushIdleFrameCalls(nullptr, 0);
        (void)context()->fn_flushDeferred(nullptr, 0);
        if (gd::native_scalar_truth(context()->f_training_start)) {
            (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return context()->fn_advancePhysicsFrame(_ca, 1); })();
            (void)context()->fn_beginCriticalShakeFrame(nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return this->fn_stepCharacterIdle(_ca, 1); })();
            (void)context()->fn_flushDeferred(nullptr, 0);
            (void)context()->fn__flushTimed(nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return context()->fn_tickMotion(_ca, 1); })();
            (void)context()->fn_flushDeferred(nullptr, 0);
            return gd::GdVal::null();
        }
        this->f__activate_countdown = gd::gd_sub(this->f__activate_countdown, lv_delta);
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_le(this->f__activate_countdown, gd::GdVal::from_float(0.0))))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_ordered_items}; return this->fn_activateItems(_ca, 1); })();
            if (_argc > 1) replay_host_before_idle(
                _args[1].as_int(), this->f_ctx.obj, this->f_combat_time.as_float());
            (void)context()->fn_runOpeningSceneDelays(nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return context()->fn_tickMotion(_ca, 1); })();
        }
        (void)context()->fn_flushDeferred(nullptr, 0);
        return gd::GdVal::null();
    }
    if (gd::native_scalar_truth(context()->f_native_frame_rng)) {
        (void)context()->fn_beginCriticalShakeFrame(nullptr, 0);
    }
    context()->f_timer_pass_epoch = gd::gd_add(gd_ctx, context()->f_timer_pass_epoch, gd::GdVal::from_int(1LL));
    context()->f_in_physics_timer_pass = gd::GdVal::from_bool(true);
    (void)opponent()->fn_snapshotPhysicsTimers(nullptr, 0);
    (void)player()->fn_snapshotPhysicsTimers(nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {this->f_opponent, lv_delta}; return this->fn__tickCharacterTimers(_ca, 2); })();
    (void)this->fn__fatigueTick(nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {this->f_player, lv_delta}; return this->fn__tickCharacterTimers(_ca, 2); })();
    context()->f_in_physics_timer_pass = gd::GdVal::from_bool(false);
    (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return context()->fn_advancePhysicsFrame(_ca, 1); })();
    context()->f_in_item_physics_pass = gd::GdVal::from_bool(true);
    native_segment_snapshot.clear();
    (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return opponent()->fn_physicsTickCharacter(_ca, 1); })();
    if(!gd::active_cooldown_phase(gd_ctx,opponent(),native_segment_snapshot,lv_delta))
    {
        gd::GdVal _t756 = gd::gd_iter_seq(gd_ctx.arena, static_cast<Gd__gd_core__CoreGrid*>(opponent()->f_inventory.obj)->f_items);
        gd::GdArr* _t757 = (_t756.kind == gd::GdVal::Kind::Arr) ? _t756.arr : nullptr;
        uint32_t _len__t758 = _t757 ? _t757->len : 0u;
        for (uint32_t _t758 = 0; _t758 < _len__t758; ++_t758) {
            gd::GdVal lv_item = _t757->data[_t758];
            auto* cooldown_item = static_cast<Gd__gd_core__CoreItem*>(lv_item.obj);
            if (([&] { const auto& active = cooldown_item->f__cooldown_active; if (active.kind == gd::GdVal::Kind::Bool) [[likely]] return active.b; return gd::native_scalar_truth(active); }())) gd::native_frame_segment_tick(cooldown_item,native_segment_snapshot,lv_delta);
            {
                gd::GdVal _t759 = cooldown_item->f_gems;
                gd::GdArr* _t760 = (_t759.kind == gd::GdVal::Kind::Arr) ? _t759.arr : nullptr;
                uint32_t _len__t761 = _t760 ? _t760->len : 0u;
                for (uint32_t _t761 = 0; _t761 < _len__t761; ++_t761) {
                    gd::GdVal lv_gem = _t760->data[_t761];
                    if (!lv_gem.is_null()) {
                        auto* cooldown_gem = static_cast<Gd__gd_core__CoreItem*>(lv_gem.obj);
                        if (([&] { const auto& active = cooldown_gem->f__cooldown_active; if (active.kind == gd::GdVal::Kind::Bool) [[likely]] return active.b; return gd::native_scalar_truth(active); }())) {native_segment_snapshot.clear();cooldown_gem->fn_physicsTick(&lv_delta, 1);}
                    }
                }
            }
        }
    }
    this->f_combat_time = gd::gd_add(gd_ctx, this->f_combat_time, lv_delta);
    context()->f_combat_time = this->f_combat_time;
    native_segment_snapshot.clear();
    (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return player()->fn_physicsTickCharacter(_ca, 1); })();
    if(!gd::active_cooldown_phase(gd_ctx,player(),native_segment_snapshot,lv_delta))
    {
        gd::GdVal _t762 = gd::gd_iter_seq(gd_ctx.arena, static_cast<Gd__gd_core__CoreGrid*>(player()->f_inventory.obj)->f_items);
        gd::GdArr* _t763 = (_t762.kind == gd::GdVal::Kind::Arr) ? _t762.arr : nullptr;
        uint32_t _len__t764 = _t763 ? _t763->len : 0u;
        for (uint32_t _t764 = 0; _t764 < _len__t764; ++_t764) {
            gd::GdVal lv_item = _t763->data[_t764];
            auto* cooldown_item = static_cast<Gd__gd_core__CoreItem*>(lv_item.obj);
            if (([&] { const auto& active = cooldown_item->f__cooldown_active; if (active.kind == gd::GdVal::Kind::Bool) [[likely]] return active.b; return gd::native_scalar_truth(active); }())) gd::native_frame_segment_tick(cooldown_item,native_segment_snapshot,lv_delta);
            {
                gd::GdVal _t765 = cooldown_item->f_gems;
                gd::GdArr* _t766 = (_t765.kind == gd::GdVal::Kind::Arr) ? _t765.arr : nullptr;
                uint32_t _len__t767 = _t766 ? _t766->len : 0u;
                for (uint32_t _t767 = 0; _t767 < _len__t767; ++_t767) {
                    gd::GdVal lv_gem = _t766->data[_t767];
                    if (!lv_gem.is_null()) {
                        auto* cooldown_gem = static_cast<Gd__gd_core__CoreItem*>(lv_gem.obj);
                        if (([&] { const auto& active = cooldown_gem->f__cooldown_active; if (active.kind == gd::GdVal::Kind::Bool) [[likely]] return active.b; return gd::native_scalar_truth(active); }())) {native_segment_snapshot.clear();cooldown_gem->fn_physicsTick(&lv_delta, 1);}
                    }
                }
            }
        }
    }
    context()->f_in_item_physics_pass = gd::GdVal::from_bool(false);
    if (gd::native_scalar_truth(this->f__track_hidden_log)) {
        (void)([&]() { gd::GdVal _ca[] = {context()->f_combat_log, gd::GdVal::from_str(&battle_string_literals[9])}; return context()->fn_defer(_ca, 2); })();
    }
    (void)context()->fn_flushDeferred(nullptr, 0);
    (void)context()->fn_flushIdleFrameCalls(nullptr, 0);
    if (_argc > 1) replay_host_before_idle(
        _args[1].as_int(), this->f_ctx.obj, this->f_combat_time.as_float());
    (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return this->fn_stepCharacterIdle(_ca, 1); })();
    (void)context()->fn_flushDeferred(nullptr, 0);
    if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(context()->f_fight_ended)))) {
        (void)([&]() { gd::GdVal _ca[] = {Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_PHYSICS_DELTA_1404)}; return context()->fn_lib_fires_tick(_ca, 1); })();
        (void)context()->fn__flushTimed(nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return context()->fn_tickMotion(_ca, 1); })();
    }
    if (gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(this->f_fight_ended))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_combat_time, this->f_max_time)))) : gd::GdVal::from_bool(false)))) {
        this->f_timed_out = gd::GdVal::from_bool(true);
        (void)this->fn_forceLoseCombat(nullptr, 0);
    }
    if (gd::native_scalar_truth(this->f__pending_deferred)) {
        (void)this->fn__flushDeferred(nullptr, 0);
    }
    (void)context()->fn_flushDeferred(nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_run(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    while (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(this->f_fight_ended)))) {
        (void)([&]() { gd::GdVal _ca[] = {Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_PHYSICS_DELTA_1404)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_physicsTick_134, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn__fatigueTick(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_fatigue_next_tick = gd::gd_sub(this->f_fatigue_next_tick, Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_PHYSICS_DELTA_1404));
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_fatigue_next_tick, gd::GdVal::from_float(0.0))))) {
        return gd::GdVal::null();
    }
    if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(this->f_fatigue_started)))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_startFatigue_1327, nullptr, 0);
    }
    else {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealFatigueDamage_1328, nullptr, 0);
    }
    this->f_fatigue_next_tick = this->f_fatigue_interval;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_startFatigue(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[10])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_playFatigueAnimation_1625, _ca, 1); })();
    this->f_fatigue_started = gd::GdVal::from_bool(true);
    this->f_fatigue_counter = gd::GdVal::from_int(0LL);
    this->f_fatigue_interval = Gd__gd_core__CoreCombat::get_static_const_or_enum(gd_ctx, SYM_GEN_FATIGUE_START_DELAY_1300);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_dealFatigueDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_fatigue_counter, gd::GdVal::from_int(0LL))))) {
        (void)gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_playFatigueSound_1626, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[11])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 2); })();
    }
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_combat_time, Gd__gd_core__CoreCombat::get_static_const_or_enum(gd_ctx, SYM_GEN_FATIGUE_SLOW_TIME_1301))))) {
        this->f_fatigue_counter = gd::gd_add(gd_ctx, this->f_fatigue_counter, gd::gd_add(gd_ctx, gd::GdVal::from_int(1LL), gd::gd_coerce_int(gd::gd_floor(gd::gd_mul(gd::GdVal::from_float(0.1), this->f_fatigue_counter)))));
    }
    else {
        this->f_fatigue_counter = gd::gd_add(gd_ctx, this->f_fatigue_counter, gd::gd_add(gd_ctx, gd::GdVal::from_int(1LL), gd::gd_coerce_int(gd::gd_floor(gd::gd_mul(gd::GdVal::from_float(0.2), this->f_fatigue_counter)))));
    }
    (void)([&]() { gd::GdVal _ca[] = {this->f_fatigue_counter}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_fatigueDamageSource_1430), SYM_GEN_setDamage_1551, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[12])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 2); })();
    (void)gd::native_inline_call(gd_ctx, this->f_opponent, SYM_GEN_takeFatigueDamage_1196, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, this->f_player, SYM_GEN_takeFatigueDamage_1196, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[13])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_playFatigueAnimation_1625, _ca, 1); })();
    this->f_fatigue_interval = gd::GdVal::from_float(1.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_hasFatigueStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_gt(this->f_fatigue_counter, gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_advanceTime(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__time = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__time = gd::gd_coerce_float(lv__time);
    this->f_time_advance = gd::gd_add(gd_ctx, this->f_time_advance, lv__time);
    gd::GdVal lv_time_left = (gd::native_scalar_truth(this->f_fatigue_started) ? (gd::GdVal::from_float(0.0)) : (([&]() { gd::GdVal _ca[] = {gd::gd_max(gd::GdVal::from_float(0.0), this->f_fatigue_next_tick)}; return gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN__nativeF32_1502, _ca, 1); })()));
    gd::GdVal lv_new_time = gd::gd_sub(lv_time_left, lv__time);
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(lv_new_time, gd::GdVal::from_int(0LL))))) {
        this->f_fatigue_next_tick = ([&]() { gd::GdVal _ca[] = {lv_new_time}; return gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN__nativeF32_1502, _ca, 1); })();
    }
    else {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_startFatigue_1327, nullptr, 0);
        this->f_fatigue_next_tick = this->f_fatigue_interval;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_getEffectiveTime(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreContext), SYM_GEN_COMBAT_DELAY_1405), this->f_combat_time), this->f_time_advance);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_endCombat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(this->f_fight_ended)) {
        return gd::GdVal::null();
    }
    this->f_fight_ended = gd::GdVal::from_bool(true);
    gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_fight_ended_1305, gd::GdVal::from_bool(true));
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_le(gd::native_inline_get_prop(gd_ctx, this->f_opponent, SYM_GEN_curHealth_1050), gd::GdVal::from_int(0LL))))) {
        this->f_result = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), gd::gd_sub(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, this->f_player, SYM_GEN_classRoundSoundCount_1141, _ca, 1); })(), gd::GdVal::from_int(1LL))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randi_range, _ca, 2); })();
    }
    else {
        this->f_result = gd::gd_coerce_int(gd::GdVal::from_int(1LL));
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), gd::gd_sub(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, this->f_player, SYM_GEN_classRoundSoundCount_1141, _ca, 1); })(), gd::GdVal::from_int(1LL))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randi_range, _ca, 2); })();
    }
    this->f__pending_deferred = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_forceLoseCombat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(this->f_fight_ended)) {
        return gd::GdVal::null();
    }
    this->f_fight_ended = gd::GdVal::from_bool(true);
    gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_fight_ended_1305, gd::GdVal::from_bool(true));
    this->f_result = gd::gd_coerce_int(gd::GdVal::from_int(1LL));
    this->f__pending_deferred = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn__flushDeferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f__pending_deferred = gd::GdVal::from_bool(false);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_combatEndDeferred_1335, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_combatEndDeferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[14]), this->f_result}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_emit_signal, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[15])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_emit_signal, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_disconnectAll_1597, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, this->f_player, SYM_GEN_combatEnd_131, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, this->f_opponent, SYM_GEN_combatEnd_131, nullptr, 0);
    this->f__tick_timer_active = gd::GdVal::from_bool(false);
    this->f__tick_timer_left = gd::GdVal::from_float(0.0);
    this->f__tick_timer_active = gd::GdVal::from_bool(false);
    this->f__tick_timer_left = gd::GdVal::from_float(0.0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[16])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_playFatigueAnimation_1625, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_fatigueDamageSource_1430), SYM_GEN_setDamage_1551, _ca, 1); })();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_result, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, this->f_opponent, SYM_GEN_setCurrentHealth_1156, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_max(gd::GdVal::from_int(1LL), gd::native_inline_call(gd_ctx, this->f_player, SYM_GEN_getCurrentHealth_1154, nullptr, 0))}; return gd::native_inline_call(gd_ctx, this->f_player, SYM_GEN_setCurrentHealth_1156, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, this->f_player, SYM_GEN_setCurrentHealth_1156, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_max(gd::GdVal::from_int(1LL), gd::native_inline_call(gd_ctx, this->f_opponent, SYM_GEN_getCurrentHealth_1154, nullptr, 0))}; return gd::native_inline_call(gd_ctx, this->f_opponent, SYM_GEN_setCurrentHealth_1156, _ca, 1); })();
    }
    {
        gd::GdVal _t768 = gd::gd_iter_seq(gd_ctx.arena, this->f_ordered_items);
        gd::GdArr* _t769 = (_t768.kind == gd::GdVal::Kind::Arr) ? _t768.arr : nullptr;
        uint32_t _len__t770 = _t769 ? _t769->len : 0u;
        for (uint32_t _t770 = 0; _t770 < _len__t770; ++_t770) {
            gd::GdVal lv_item = _t769->data[_t770];
            (void)gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_combatEnd_131, nullptr, 0);
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rope_speedups_1425), gd::SYM_clear, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_cube_advanced_1426), gd::SYM_clear, nullptr, 0);
    gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_sandbag_active_1422, gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_playerWins(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::native_scalar_eq(this->f_result, gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_winner(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_result, gd::GdVal::from_int(0LL))))) {
        return this->f_player;
    }
    else if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_result, gd::GdVal::from_int(1LL))))) {
        return this->f_opponent;
    }
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn__tickCharacterTimers(const gd::GdVal* args, int argc) {
    auto* character = static_cast<Gd__gd_core__CoreCharacter*>(args[0].obj);
    const auto delta = gd::gd_coerce_float(argc > 1 ? args[1] : gd::GdVal::null());
    character->fn_tickPhysicsTimers(&delta, 1);
    character->fn_tickBuffs(&delta, 1);
    gd::targeted_timer_tick(*this->rt_ctx_,character,delta);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_stepCharacterIdle(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    // The native battle constructs exact CoreContext and CoreCharacter objects.
    const auto context = [this] { return static_cast<Gd__gd_core__CoreContext*>(this->f_ctx.obj); };
    const auto opponent = [this] { return static_cast<Gd__gd_core__CoreCharacter*>(this->f_opponent.obj); };
    const auto player = [this] { return static_cast<Gd__gd_core__CoreCharacter*>(this->f_player.obj); };
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return opponent()->fn_tickIdleAnimation(_ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return context()->fn_tickOpponentFlickers(_ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return player()->fn_tickIdleAnimation(_ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return context()->fn_tickFlickers(_ca, 1); })();
    if (gd::native_scalar_truth(context()->f_native_frame_rng)) {
        (void)context()->fn_stepCriticalShake(nullptr, 0);
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreCombat(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__CoreCombat>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,25u); return object; }
const gd::GdClassMeta META_Gd__gd_core__CoreCombat = {CLS_Gd__gd_core__CoreCombat, "CoreCombat", "res://gd_core/CoreCombat.gd", nullptr, false, _alloc_Gd__gd_core__CoreCombat, &Gd__gd_core__CoreCombat::get_static_prop_fn, &Gd__gd_core__CoreCombat::call_static_fn};

void Gd__gd_core__CoreRng::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_rng = gd::GdVal::null();
    this->f_debug_flip_tag = gd::GdVal::from_str(&battle_string_literals[17]);
    this->f_oracle_trace = gd::GdVal::from_bool(false);
    this->f_oracle_trace_log = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f__stacktrace = gd::GdVal::from_bool(false);
    this->f_draw_seq = gd::gd_neg(gd::GdVal::from_int(1LL));
    this->f_globalChainOpen = gd::GdVal::from_bool(false);
}
const gd::GdClassMeta* Gd__gd_core__CoreRng::meta() const { return &META_Gd__gd_core__CoreRng; }
gd::GdVal Gd__gd_core__CoreRng::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_BalancedRng_1749: return gd::GdVal::from_cls(&META_Gd__gd_core__CoreRng__INNER__BalancedRng);
        case SYM_GEN_BalancedRange_1750: return gd::GdVal::from_cls(&META_Gd__gd_core__CoreRng__INNER__BalancedRange);
        default: break;
    }
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreRng::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    switch (prop) {
        case SYM_GEN_BalancedRng_1749: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreRng__INNER__BalancedRng); return true;
        case SYM_GEN_BalancedRange_1750: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreRng__INNER__BalancedRange); return true;
        default: break;
    }
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
        case SYM_GEN_rng_1406: out = this->f_rng; return true;
        case SYM_GEN_debug_flip_tag_1728: out = this->f_debug_flip_tag; return true;
        case SYM_GEN_oracle_trace_1729: out = this->f_oracle_trace; return true;
        case SYM_GEN_oracle_trace_log_1730: out = this->f_oracle_trace_log; return true;
        case SYM_GEN__stacktrace_1731: out = this->f__stacktrace; return true;
        case SYM_GEN_draw_seq_1732: out = this->f_draw_seq; return true;
        case SYM_GEN_globalChainOpen_1733: out = this->f_globalChainOpen; return true;
        case SYM_GEN_BalancedRng_1749: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreRng__INNER__BalancedRng); return true;
        case SYM_GEN_BalancedRange_1750: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreRng__INNER__BalancedRange); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreRng::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_rng_1406: this->f_rng = val; return true;
        case SYM_GEN_debug_flip_tag_1728: this->f_debug_flip_tag = val; return true;
        case SYM_GEN_oracle_trace_1729: this->f_oracle_trace = val; return true;
        case SYM_GEN_oracle_trace_log_1730: this->f_oracle_trace_log = val; return true;
        case SYM_GEN__stacktrace_1731: this->f__stacktrace = val; return true;
        case SYM_GEN_draw_seq_1732: this->f_draw_seq = val; return true;
        case SYM_GEN_globalChainOpen_1733: this->f_globalChainOpen = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreRng::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case gd::SYM_set_state: return true;
        case SYM_GEN_roll_1734: return true;
        case SYM_GEN_flip_1735: return true;
        case SYM_GEN_flipPercent_1736: return true;
        case SYM_GEN_flipRound_1737: return true;
        case SYM_GEN_flipWeighted_1738: return true;
        case SYM_GEN__trace_1739: return true;
        case SYM_GEN_trace_event_1740: return true;
        case SYM_GEN_trace_diag_1741: return true;
        case SYM_GEN_bare_draw_seq_1742: return true;
        case SYM_GEN_bare_randf_range_1743: return true;
        case SYM_GEN_bare_randf_1744: return true;
        case SYM_GEN_bare_randi_range_1745: return true;
        case gd::SYM_randf_range: return true;
        case gd::SYM_randi_range: return true;
        case SYM_GEN_pickRandomElement_1746: return true;
        case gd::SYM_shuffle: return true;
        case SYM_GEN_shuffleEngine_1747: return true;
        case SYM_GEN_pickRandomEngine_1748: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreRng::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case gd::SYM_set_state: out = fn_set_state(args, argc); return true;
        case SYM_GEN_roll_1734: out = fn_roll(args, argc); return true;
        case SYM_GEN_flip_1735: out = fn_flip(args, argc); return true;
        case SYM_GEN_flipPercent_1736: out = fn_flipPercent(args, argc); return true;
        case SYM_GEN_flipRound_1737: out = fn_flipRound(args, argc); return true;
        case SYM_GEN_flipWeighted_1738: out = fn_flipWeighted(args, argc); return true;
        case SYM_GEN__trace_1739: out = fn__trace(args, argc); return true;
        case SYM_GEN_trace_event_1740: out = fn_trace_event(args, argc); return true;
        case SYM_GEN_trace_diag_1741: out = fn_trace_diag(args, argc); return true;
        case SYM_GEN_bare_draw_seq_1742: out = fn_bare_draw_seq(args, argc); return true;
        case SYM_GEN_bare_randf_range_1743: out = fn_bare_randf_range(args, argc); return true;
        case SYM_GEN_bare_randf_1744: out = fn_bare_randf(args, argc); return true;
        case SYM_GEN_bare_randi_range_1745: out = fn_bare_randi_range(args, argc); return true;
        case gd::SYM_randf_range: out = fn_randf_range(args, argc); return true;
        case gd::SYM_randi_range: out = fn_randi_range(args, argc); return true;
        case SYM_GEN_pickRandomElement_1746: out = fn_pickRandomElement(args, argc); return true;
        case gd::SYM_shuffle: out = fn_shuffle(args, argc); return true;
        case SYM_GEN_shuffleEngine_1747: out = fn_shuffleEngine(args, argc); return true;
        case SYM_GEN_pickRandomEngine_1748: out = fn_pickRandomEngine(args, argc); return true;
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
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv__seed, gd::GdVal::from_int(0LL))))) {
        (void)gd::native_inline_call(gd_ctx, this->f_rng, gd::SYM_randomize, nullptr, 0);
    }
    else {
        gd::set_prop(gd_ctx, this->f_rng, gd::SYM_seed, lv__seed);
    }
    this->f__stacktrace = gd::GdVal::from_bool(gd::native_scalar_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(&battle_string_literals[17])));
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
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), lv_maximum}; return this->fn_randf_range(_ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_flip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : (gd::GdVal::from_float(0.5));
    lv_chance = gd::gd_coerce_float(lv_chance);
    gd::GdVal lv_r = gd::native_inline_call(gd_ctx, this->f_rng, gd::SYM_randf, nullptr, 0);
    if (gd::native_scalar_truth(this->f_oracle_trace)) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[18]), gd::GdVal::from_int(0LL), gd::GdVal::from_int(0LL), lv_r}; return this->fn__trace(_ca, 4); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[18]), gd::GdVal::from_int(0LL), gd::GdVal::from_int(0LL), lv_r}; return this->fn_bare_draw_seq(_ca, 4); })();
    if (gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(&battle_string_literals[17])))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_debug_flip_tag, gd::GdVal::from_str(&battle_string_literals[17]))))) : gd::GdVal::from_bool(false)))) {
        (void)gd::GdVal::null();
        this->f_debug_flip_tag = gd::GdVal::from_str(&battle_string_literals[17]);
    }
    return gd::GdVal::from_bool(gd::gd_le(lv_r, lv_chance));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_flipPercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_chance = gd::gd_coerce_float(lv_chance);
    return gd::GdVal::from_bool(gd::gd_le(this->fn_roll(nullptr, 0), lv_chance));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_flipRound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_chance = gd::gd_coerce_float(lv_chance);
    return gd::gd_coerce_int(gd::gd_add(gd_ctx, gd::gd_floor(lv_chance), gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::gd_fmod(lv_chance, gd::GdVal::from_float(1.0))}; return this->fn_flip(_ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_flipWeighted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_weights = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_sum = gd::GdVal::from_float(0.0);
    {
        gd::GdVal _t774 = gd::gd_iter_seq(gd_ctx.arena, lv_weights);
        gd::GdArr* _t775 = (_t774.kind == gd::GdVal::Kind::Arr) ? _t774.arr : nullptr;
        uint32_t _len__t776 = _t775 ? _t775->len : 0u;
        for (uint32_t _t776 = 0; _t776 < _len__t776; ++_t776) {
            gd::GdVal lv_weight = _t775->data[_t776];
            lv_sum = gd::gd_add(gd_ctx, lv_sum, lv_weight);
        }
    }
    gd::GdVal lv_val = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), lv_sum, gd::GdVal::from_str(&battle_string_literals[19])}; return this->fn_randf_range(_ca, 3); })();
    gd::GdVal lv_subsum = gd::GdVal::from_float(0.0);
    {
        gd::GdVal _t777 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, lv_weights, gd::SYM_size, nullptr, 0));
        gd::GdArr* _t778 = (_t777.kind == gd::GdVal::Kind::Arr) ? _t777.arr : nullptr;
        uint32_t _len__t779 = _t778 ? _t778->len : 0u;
        for (uint32_t _t779 = 0; _t779 < _len__t779; ++_t779) {
            gd::GdVal lv_i = _t778->data[_t779];
            lv_subsum = gd::gd_add(gd_ctx, lv_subsum, gd::native_array_index(gd_ctx, lv_weights, lv_i));
            if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(lv_subsum, lv_val)))) {
                return lv_i;
            }
        }
    }
    return gd::native_inline_call(gd_ctx, lv_weights, gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn__trace(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_kind = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_from = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_to = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_r = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_row = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_inline_call(gd_ctx, this->f_oracle_trace_log, gd::SYM_size, nullptr, 0), lv_kind, lv_from, lv_to, lv_r, gd::GdVal::from_float(0.0), gd::GdVal::from_str(&battle_string_literals[17]), ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, this->f_rng, gd::SYM_get_state, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}));
    if (gd::native_scalar_truth(this->f__stacktrace)) {
        gd::GdVal lv_frames = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
        gd::GdVal lv_st = gd::GdVal::null();
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_st, gd::GdVal::null())))) {
            {
                gd::GdVal _t780 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL), gd::gd_min(gd::GdVal::from_int(5LL), gd::native_inline_call(gd_ctx, lv_st, gd::SYM_size, nullptr, 0))}; return gd::gd_range(gd_ctx.arena, _ca, 2); })());
                gd::GdArr* _t781 = (_t780.kind == gd::GdVal::Kind::Arr) ? _t780.arr : nullptr;
                uint32_t _len__t782 = _t781 ? _t781->len : 0u;
                for (uint32_t _t782 = 0; _t782 < _len__t782; ++_t782) {
                    gd::GdVal lv_i = _t781->data[_t782];
                    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mod(gd_ctx, gd::GdVal::from_str(&battle_string_literals[20]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_inline_call(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_array_index(gd_ctx, gd::native_array_index(gd_ctx, lv_st, lv_i), gd::GdVal::from_str(&battle_string_literals[21])))), SYM_GEN_get_file_2824, nullptr, 0), gd::gd_coerce_int(gd::native_array_index(gd_ctx, gd::native_array_index(gd_ctx, lv_st, lv_i), gd::GdVal::from_str(&battle_string_literals[22]))), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_array_index(gd_ctx, gd::native_array_index(gd_ctx, lv_st, lv_i), gd::GdVal::from_str(&battle_string_literals[23]))))})))}; return gd::native_inline_call(gd_ctx, lv_frames, gd::SYM_append, _ca, 1); })();
                }
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[24])}; return gd::native_inline_call(gd_ctx, (lv_frames), gd::SYM_join, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, lv_row, gd::SYM_append, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_row}; return gd::native_inline_call(gd_ctx, this->f_oracle_trace_log, gd::SYM_push_back, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_trace_event(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_inline_call(gd_ctx, this->f_oracle_trace_log, gd::SYM_size, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[25]), ([&]() { gd::GdVal _ca[] = {lv_type}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::GdVal::from_str(&battle_string_literals[17]), gd::GdVal::from_str(&battle_string_literals[17]), gd::GdVal::from_float(0.0), gd::GdVal::from_str(&battle_string_literals[17]), ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, this->f_rng, gd::SYM_get_state, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}))}; return gd::native_inline_call(gd_ctx, this->f_oracle_trace_log, gd::SYM_push_back, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_trace_diag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_kind = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_a = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_b = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_c = (_argc > 3) ? _args[3] : (gd::GdVal::from_str(&battle_string_literals[17]));
    if (gd::native_scalar_truth((gd::native_scalar_truth(this->f_oracle_trace) ? gd::GdVal::from_bool(gd::native_scalar_truth(this->f__stacktrace)) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_inline_call(gd_ctx, this->f_oracle_trace_log, gd::SYM_size, nullptr, 0), lv_kind, ([&]() { gd::GdVal _ca[] = {lv_a}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {lv_b}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {lv_c}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}))}; return gd::native_inline_call(gd_ctx, this->f_oracle_trace_log, gd::SYM_push_back, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_bare_draw_seq(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_kind = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_from = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_to = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_r = (_argc > 3) ? _args[3] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_draw_seq, gd::GdVal::from_int(0LL))))) {
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
    gd::GdVal lv_r = ([&]() { gd::GdVal _ca[] = {lv_from, lv_to}; return (this->f_rng.kind == gd::GdVal::Kind::Rng && this->f_rng.rng ? gd::GdVal::from_float(this->f_rng.rng->randf_range(_ca[0].as_float(), _ca[1].as_float())) : gd::native_inline_call(gd_ctx, this->f_rng, gd::SYM_randf_range, _ca, 2)); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[26]), lv_from, lv_to, lv_r}; return this->fn_bare_draw_seq(_ca, 4); })();
    return lv_r;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_bare_randf(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_r = gd::native_inline_call(gd_ctx, this->f_rng, gd::SYM_randf, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[18]), gd::GdVal::from_int(0LL), gd::GdVal::from_int(0LL), lv_r}; return this->fn_bare_draw_seq(_ca, 4); })();
    return lv_r;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_bare_randi_range(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_from = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_from = gd::gd_coerce_int(lv_from);
    gd::GdVal lv_to = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_to = gd::gd_coerce_int(lv_to);
    gd::GdVal lv_r = ([&]() { gd::GdVal _ca[] = {lv_from, lv_to}; return gd::native_inline_call(gd_ctx, this->f_rng, gd::SYM_randi_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[27]), lv_from, lv_to, lv_r}; return this->fn_bare_draw_seq(_ca, 4); })();
    return lv_r;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_randf_range(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_from = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_from = gd::gd_coerce_float(lv_from);
    gd::GdVal lv_to = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_to = gd::gd_coerce_float(lv_to);
    gd::GdVal lv_tag = (_argc > 2) ? _args[2] : (gd::GdVal::from_str(&battle_string_literals[26]));
    gd::GdVal lv_r = ([&]() { gd::GdVal _ca[] = {lv_from, lv_to}; return (this->f_rng.kind == gd::GdVal::Kind::Rng && this->f_rng.rng ? gd::GdVal::from_float(this->f_rng.rng->randf_range(_ca[0].as_float(), _ca[1].as_float())) : gd::native_inline_call(gd_ctx, this->f_rng, gd::SYM_randf_range, _ca, 2)); })();
    if (gd::native_scalar_truth(this->f_oracle_trace)) {
        (void)([&]() { gd::GdVal _ca[] = {lv_tag, lv_from, lv_to, lv_r}; return this->fn__trace(_ca, 4); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_tag, lv_from, lv_to, lv_r}; return this->fn_bare_draw_seq(_ca, 4); })();
    return lv_r;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_randi_range(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_from = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_from = gd::gd_coerce_int(lv_from);
    gd::GdVal lv_to = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_to = gd::gd_coerce_int(lv_to);
    gd::GdVal lv_tag = (_argc > 2) ? _args[2] : (gd::GdVal::from_str(&battle_string_literals[27]));
    gd::GdVal lv_r = ([&]() { gd::GdVal _ca[] = {lv_from, lv_to}; return gd::native_inline_call(gd_ctx, this->f_rng, gd::SYM_randi_range, _ca, 2); })();
    if (gd::native_scalar_truth(this->f_oracle_trace)) {
        (void)([&]() { gd::GdVal _ca[] = {lv_tag, lv_from, lv_to, lv_r}; return this->fn__trace(_ca, 4); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_tag, lv_from, lv_to, lv_r}; return this->fn_bare_draw_seq(_ca, 4); })();
    return lv_r;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_pickRandomElement(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_array = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_array_index(gd_ctx, lv_array, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), gd::gd_sub(gd::native_inline_call(gd_ctx, lv_array, gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL)), gd::GdVal::from_str(&battle_string_literals[28])}; return this->fn_randi_range(_ca, 3); })());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_shuffle(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_array = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_n = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, lv_array, gd::SYM_size, nullptr, 0));
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(lv_n, gd::GdVal::from_int(2LL))))) {
        return lv_array;
    }
    {
        gd::GdVal _t783 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::gd_sub(lv_n, gd::GdVal::from_int(1LL))}; return gd::gd_range(gd_ctx.arena, _ca, 1); })());
        gd::GdArr* _t784 = (_t783.kind == gd::GdVal::Kind::Arr) ? _t783.arr : nullptr;
        uint32_t _len__t785 = _t784 ? _t784->len : 0u;
        for (uint32_t _t785 = 0; _t785 < _len__t785; ++_t785) {
            gd::GdVal lv_i = _t784->data[_t785];
            gd::GdVal lv_r = gd::native_inline_call(gd_ctx, this->f_rng, gd::SYM_randi, nullptr, 0);
            if (gd::native_scalar_truth(this->f_oracle_trace)) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[29]), gd::GdVal::from_int(0LL), gd::GdVal::from_int(0LL), lv_r}; return this->fn__trace(_ca, 4); })();
            }
            gd::GdVal lv_j = gd::gd_coerce_int(gd::gd_mod(gd_ctx, gd::gd_coerce_int(gd::gd_abs(lv_r)), gd::gd_sub(lv_n, lv_i)));
            gd::GdVal lv_tmp = gd::native_array_index(gd_ctx, lv_array, lv_i);
            { gd::GdVal _t786 = lv_array; gd::GdVal _t787 = lv_i; gd::native_array_set_index(gd_ctx, _t786, _t787, gd::native_array_index(gd_ctx, lv_array, gd::gd_add(gd_ctx, lv_i, lv_j))); }
            { gd::GdVal _t788 = lv_array; gd::GdVal _t789 = gd::gd_add(gd_ctx, lv_i, lv_j); gd::native_array_set_index(gd_ctx, _t788, _t789, lv_tmp); }
        }
    }
    return lv_array;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_shuffleEngine(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_array = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_tag = (_argc > 1) ? _args[1] : (gd::GdVal::from_str(&battle_string_literals[30]));
    (void)gd::native_inline_call(gd_ctx, lv_array, gd::SYM_shuffle, nullptr, 0);
    if (gd::native_scalar_truth((gd::native_scalar_truth(this->f_globalChainOpen) ? gd::GdVal::from_bool(gd::native_scalar_truth(this->f_oracle_trace)) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_inline_call(gd_ctx, this->f_oracle_trace_log, gd::SYM_size, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[30]), lv_tag, gd::native_inline_call(gd_ctx, lv_array, gd::SYM_size, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[17])}))}; return gd::native_inline_call(gd_ctx, this->f_oracle_trace_log, gd::SYM_push_back, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_pickRandomEngine(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_array = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_tag = (_argc > 1) ? _args[1] : (gd::GdVal::from_str(&battle_string_literals[31]));
    gd::GdVal lv_v = gd::native_inline_call(gd_ctx, lv_array, gd::SYM_pick_random, nullptr, 0);
    if (gd::native_scalar_truth((gd::native_scalar_truth(this->f_globalChainOpen) ? gd::GdVal::from_bool(gd::native_scalar_truth(this->f_oracle_trace)) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_inline_call(gd_ctx, this->f_oracle_trace_log, gd::SYM_size, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[31]), lv_tag, gd::native_inline_call(gd_ctx, lv_array, gd::SYM_size, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[17])}))}; return gd::native_inline_call(gd_ctx, this->f_oracle_trace_log, gd::SYM_push_back, _ca, 1); })();
    }
    return lv_v;
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreRng(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__CoreRng>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,42u); return object; }
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
        case SYM_GEN_critBonusActive_1829: out = this->f_critBonusActive; return true;
        case SYM_GEN_poisonThreshold_1830: out = this->f_poisonThreshold; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__DeathScythe::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_critBonusActive_1829: this->f_critBonusActive = val; return true;
        case SYM_GEN_poisonThreshold_1830: this->f_poisonThreshold = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__DeathScythe::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onOpponentPoisonChanged_1831: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__DeathScythe::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onOpponentPoisonChanged_1831: out = fn_onOpponentPoisonChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(256LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_gainsStack_86, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeathScythe::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[32]), gd::GdVal::from_str(&battle_string_literals[33])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    {
        gd::GdVal _t790 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t791 = (_t790.kind == gd::GdVal::Kind::Arr) ? _t790.arr : nullptr;
        uint32_t _len__t792 = _t791 ? _t791->len : 0u;
        for (uint32_t _t792 = 0; _t792 < _len__t792; ++_t792) {
            gd::GdVal lv_item = _t791->data[_t792];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(108LL), gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_giveBuffPower_303, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeathScythe::fn_onOpponentPoisonChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_curPoison = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getPoison_1229, nullptr, 0);
    if (gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(this->f_critBonusActive))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(lv_curPoison, this->f_poisonThreshold)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeCritChancePercent_181, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeathScythe::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeathScythe::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__critBonusActive = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(lv__critBonusActive)) {
    }
    else {
    }
    this->f_critBonusActive = lv__critBonusActive;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeathScythe::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_poisonThreshold = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__DeathScythe(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__DeathScythe>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,59u); return object; }
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
        case SYM_GEN_extraBlock_1878: out = this->f_extraBlock; return true;
        default: break;
    }
    return Gd__gd_core__Food::get_prop(prop, out);
}
bool Gd__gd_core__Garlic::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_extraBlock_1878: this->f_extraBlock = val; return true;
        default: break;
    }
    return Gd__gd_core__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Garlic::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_addBonusBlock_1879: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Food::has_own_method(m);
}
bool Gd__gd_core__Garlic::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_addBonusBlock_1879: out = fn_addBonusBlock(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Garlic::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Garlic::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), this->f_extraBlock)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 1); })();
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeVampirism_339, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Garlic(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__Garlic>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,73u); return object; }
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
        case SYM_GEN_emitter_1654: out = this->f_emitter; return true;
        case SYM_GEN_signalName_1013: out = this->f_signalName; return true;
        case SYM_GEN_receiver_1655: out = this->f_receiver; return true;
        case SYM_GEN_methodName_1656: out = this->f_methodName; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__Item__INNER__SignalConnection::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_emitter_1654: this->f_emitter = val; return true;
        case SYM_GEN_signalName_1013: this->f_signalName = val; return true;
        case SYM_GEN_receiver_1655: this->f_receiver = val; return true;
        case SYM_GEN_methodName_1656: this->f_methodName = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__Item__INNER__SignalConnection::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_destroy_1657: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__Item__INNER__SignalConnection::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_destroy_1657: out = fn_destroy(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {this->f_signalName, this->f_receiver, this->f_methodName, lv_binds}; return gd::native_inline_call(gd_ctx, this->f_emitter, gd::SYM_connect, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item__INNER__SignalConnection::fn_destroy(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Item__INNER__SignalConnection(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__Item__INNER__SignalConnection>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,91u); return object; }
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
        case SYM_GEN_blockedDamageRes_1939: out = this->f_blockedDamageRes; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Shield::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockedDamageRes_1939: this->f_blockedDamageRes = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Shield::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepare_122: return true;
        case SYM_GEN_getDamageBlock_1940: return true;
        case SYM_GEN_beforeBlock_1941: return true;
        case SYM_GEN_afterBlock_1942: return true;
        case SYM_GEN_canBlockDamageRes_1943: return true;
        case SYM_GEN_preTakeDamage_1944: return true;
        case SYM_GEN_onCharacterAttacked_1945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Shield::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepare_122: out = fn_prepare(args, argc); return true;
        case SYM_GEN_getDamageBlock_1940: out = fn_getDamageBlock(args, argc); return true;
        case SYM_GEN_beforeBlock_1941: out = fn_beforeBlock(args, argc); return true;
        case SYM_GEN_afterBlock_1942: out = fn_afterBlock(args, argc); return true;
        case SYM_GEN_canBlockDamageRes_1943: out = fn_canBlockDamageRes(args, argc); return true;
        case SYM_GEN_preTakeDamage_1944: out = fn_preTakeDamage(args, argc); return true;
        case SYM_GEN_onCharacterAttacked_1945: out = fn_onCharacterAttacked(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[34]), gd::GdVal::from_str(&battle_string_literals[35])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[36]), gd::GdVal::from_str(&battle_string_literals[37])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_prepare_122, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Shield::fn_getDamageBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[38])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Shield::fn_beforeBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getDamageBlock_1940, nullptr, 0), gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, this->f_blockedDamageRes, SYM_GEN_applyDamageReduction_1526, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Shield::fn_afterBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Shield::fn_canBlockDamageRes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_triggerOnMeleeAttacked_1529, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Shield::fn_preTakeDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth((gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {lv_damageRes}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canBlockDamageRes_1943, _ca, 1); })()) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        this->f_blockedDamageRes = lv_damageRes;
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_beforeBlock_1941, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Shield::fn_onCharacterAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_blockedDamageRes, lv_damageRes)))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_afterBlock_1942, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[39]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {this->f_blockedDamageRes}))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
        this->f_blockedDamageRes = gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Shield::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Shield(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__Shield>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,133u); return object; }
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
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Present::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_getShopPriority_853: out = fn_getShopPriority(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Present::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Present::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Present::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Present::fn_getShopPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::GdVal::from_int(-1000LL), gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Present::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Present(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__Present>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,122u); return object; }
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
        case SYM_GEN_addToInventory_120: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Bag::has_own_method(m);
}
bool Gd__gd_core__StaminaSack::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_addToInventory_120: out = fn_addToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {lv__inventory, lv__occupiedCells, lv__placedByPlayer}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bag::call_method(gd_ctx, SYM_GEN_addToInventory_120, _ca, 3, _out); return _out; })();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(1LL))))) {
        (void)gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeBaseMaxStamina_1272, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StaminaSack::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bag::call_method(gd_ctx, SYM_GEN_onRemoveFromInventory_418, nullptr, 0, _out); return _out; })();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_ownerType, gd::GdVal::from_int(10LL))))) {
        (void)gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeBaseMaxStamina_1272, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StaminaSack::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[40])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isTypeInInventory_805, _ca, 1); })())) {
        gd::GdVal lv_stamina = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[41])}; return gd::native_inline_call(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[40])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })(), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
        (void)([&]() { gd::GdVal _ca[] = {lv_stamina}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_giveStaminaRegeneration_1270, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StaminaSack::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bag::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__StaminaSack(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__StaminaSack>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,140u); return object; }
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
        case SYM_GEN_heartParticles_1997: out = this->f_heartParticles; return true;
        case SYM_GEN_healAmp_1998: out = this->f_healAmp; return true;
        case SYM_GEN_dam_939: out = this->f_dam; return true;
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core__Card::get_prop(prop, out);
}
bool Gd__gd_core__TheLovers::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heartParticles_1997: this->f_heartParticles = val; return true;
        case SYM_GEN_healAmp_1998: this->f_healAmp = val; return true;
        case SYM_GEN_dam_939: this->f_dam = val; return true;
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__TheLovers::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_890: return true;
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Card::has_own_method(m);
}
bool Gd__gd_core__TheLovers::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_890: out = fn_cardSecondaryEffectActive(args, argc); return true;
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__TheLovers::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__TheLovers::fn_cardSecondaryEffectActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::native_scalar_eq(gd::gd_mod(gd_ctx, this->f_chainPosition, gd::GdVal::from_int(2LL)), gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__TheLovers::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cardSecondaryEffectActive_890, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_healAmp}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_addHealingEfficiency_1182, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {this->f_dam, gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[42])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealLife_329, _ca, 2); })();
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cardSecondaryEffectActive_890, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__TheLovers::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Card::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_healAmp = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[43])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_dam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[44])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[45])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__TheLovers(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__TheLovers>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,151u); return object; }
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
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Card::has_own_method(m);
}
bool Gd__gd_core_items__AceofSpades::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_890: out = fn_cardSecondaryEffectActive(args, argc); return true;
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__AceofSpades::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__AceofSpades::fn_cardSecondaryEffectActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::native_scalar_eq(gd::gd_mod(gd_ctx, this->f_chainPosition, gd::GdVal::from_int(2LL)), gd::GdVal::from_int(1LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__AceofSpades::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveCritTokens_314, _ca, 1); })();
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cardSecondaryEffectActive_890, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__AceofSpades::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Card::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[0])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[1])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__AceofSpades(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__AceofSpades>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,167u); return object; }
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
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_prepare_122: return true;
        case SYM_GEN_onWeaponAttacked_950: return true;
        case SYM_GEN_combatEnd_131: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Bow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_prepare_122: out = fn_prepare(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_950: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN_combatEnd_131: out = fn_combatEnd(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isWeapon_82, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bow::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_affectedWeapon = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_428, nullptr, 0);
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_affectedWeapon, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_affectedWeapon, gd::GdVal::from_str(&battle_string_literals[46]), gd::GdVal::from_str(&battle_string_literals[47])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_prepare_122, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bow::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bow::fn_combatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_combatEnd_131, nullptr, 0, _out); return _out; })();
    this->f_affectedWeapon = gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bow::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Bow(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Bow>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,179u); return object; }
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
        case SYM_GEN_onCalcTradeChance_1825: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__CustomerCard::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCalcTradeChance_1825: out = fn_onCalcTradeChance(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__CustomerCard(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__CustomerCard>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,196u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__CustomerCard = {CLS_Gd__gd_core_items__CustomerCard, "CustomerCard", "res://gd_core_items/CustomerCard.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__CustomerCard, &Gd__gd_core_items__CustomerCard::get_static_prop_fn, &Gd__gd_core_items__CustomerCard::call_static_fn};

void Gd__gd_core_items__Exclusive__AmuletofDarkness::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_damageAcc = gd::GdVal::from_int(0);
    this->f_damageThreshold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__AmuletofDarkness::meta() const { return &META_Gd__gd_core_items__Exclusive__AmuletofDarkness; }
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofDarkness::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_amuletColor_2020: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.580392), gd::GdVal::from_float(0.266667), gd::GdVal::from_float(0.960784)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__AmuletofDarkness::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__AmuletofDarkness::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_damageAcc_1960: out = this->f_damageAcc; return true;
        case SYM_GEN_damageThreshold_2027: out = this->f_damageThreshold; return true;
        case SYM_GEN_amuletColor_2020: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofDarkness::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damageAcc_1960: this->f_damageAcc = gd::gd_coerce_int(val); return true;
        case SYM_GEN_damageThreshold_2027: this->f_damageThreshold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__AmuletofDarkness::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onItemActivated_938: return true;
        case SYM_GEN_onOpponentDamaged_1992: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AmuletofDarkness::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemActivated_938: out = fn_onItemActivated(args, argc); return true;
        case SYM_GEN_onOpponentDamaged_1992: out = fn_onOpponentDamaged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofDarkness::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofDarkness::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canActivate_91, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofDarkness::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_damageAcc = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[36]), gd::GdVal::from_str(&battle_string_literals[48])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    {
        gd::GdVal _t793 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t794 = (_t793.kind == gd::GdVal::Kind::Arr) ? _t793.arr : nullptr;
        uint32_t _len__t795 = _t794 ? _t794->len : 0u;
        for (uint32_t _t795 = 0; _t795 < _len__t795; ++_t795) {
            gd::GdVal lv_item = _t794->data[_t795];
            if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(&battle_string_literals[17]))))) {
                (void)gd::GdVal::null();
            }
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[49]), gd::GdVal::from_str(&battle_string_literals[50])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofDarkness::fn_onItemActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(&battle_string_literals[17]))))) {
        (void)gd::GdVal::null();
    }
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(&battle_string_literals[17]))))) {
        { gd::GdVal _t796 = gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406); gd::set_prop(gd_ctx, _t796, SYM_GEN_debug_flip_tag_1728, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[51]), ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1411)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())); }
    }
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
        gd::GdVal lv_dam = gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1675);
        gd::GdVal lv_res = ([&]() { gd::GdVal _ca[] = {lv_dam}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealEffectDamage_221, _ca, 1); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofDarkness::fn_onOpponentDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth((gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_isEffectDamage_1561, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        this->f_damageAcc = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_damageAcc, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518)));
        gd::GdVal lv_proccs = gd::gd_div(gd_ctx, this->f_damageAcc, this->f_damageThreshold);
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(lv_proccs, gd::GdVal::from_int(0LL))))) {
            this->f_damageAcc = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_damageAcc, this->f_damageThreshold));
            (void)([&]() { gd::GdVal _ca[] = {lv_proccs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictRandomDebuffs_357, _ca, 1); })();
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofDarkness::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_damageThreshold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[52])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1550, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__AmuletofDarkness(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__AmuletofDarkness>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,214u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletofDarkness = {CLS_Gd__gd_core_items__Exclusive__AmuletofDarkness, "AmuletofDarkness", "res://gd_core_items/Exclusive/AmuletofDarkness.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__AmuletofDarkness, &Gd__gd_core_items__Exclusive__AmuletofDarkness::get_static_prop_fn, &Gd__gd_core_items__Exclusive__AmuletofDarkness::call_static_fn};

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
        case SYM_GEN_playDropSound_149: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__WisdomPuppy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_149: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(3LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WisdomPuppy::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseCold_352, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WisdomPuppy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WisdomPuppy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__WisdomPuppy(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__WisdomPuppy>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,559u); return object; }
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
        case SYM_GEN_blockHealthAcc_2073: out = this->f_blockHealthAcc; return true;
        case SYM_GEN_staminaRegenMalus_2074: out = this->f_staminaRegenMalus; return true;
        case SYM_GEN_healthThreshold_1854: out = this->f_healthThreshold; return true;
        case SYM_GEN_maxStamina_1054: out = this->f_maxStamina; return true;
        case SYM_GEN_staminaThreshold_2075: out = this->f_staminaThreshold; return true;
        case SYM_GEN_staminaUsed_2076: out = this->f_staminaUsed; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        case SYM_GEN_block2_2077: out = this->f_block2; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BionicArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockHealthAcc_2073: this->f_blockHealthAcc = gd::gd_coerce_int(val); return true;
        case SYM_GEN_staminaRegenMalus_2074: this->f_staminaRegenMalus = val; return true;
        case SYM_GEN_healthThreshold_1854: this->f_healthThreshold = val; return true;
        case SYM_GEN_maxStamina_1054: this->f_maxStamina = val; return true;
        case SYM_GEN_staminaThreshold_2075: this->f_staminaThreshold = val; return true;
        case SYM_GEN_staminaUsed_2076: this->f_staminaUsed = val; return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        case SYM_GEN_block2_2077: this->f_block2 = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BionicArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onHealOrBlockChanged_2078: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BionicArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onHealOrBlockChanged_2078: out = fn_onHealOrBlockChanged(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    gd::GdVal lv_baseStaminaRegen = gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_baseStaminaRegen_1057);
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_staminaRegenMalus, lv_baseStaminaRegen)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_giveStaminaRegeneration_1270, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[53]), gd::GdVal::from_str(&battle_string_literals[54])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[55]), gd::GdVal::from_str(&battle_string_literals[54])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BionicArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BionicArmor::fn_onHealOrBlockChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        this->f_blockHealthAcc = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_blockHealthAcc, lv_amount));
        gd::GdVal lv_numProccs = gd::gd_coerce_int(gd::gd_div(gd_ctx, this->f_blockHealthAcc, this->f_healthThreshold));
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numProccs, gd::GdVal::from_int(0LL))))) {
            this->f_blockHealthAcc = gd::gd_coerce_int(gd::gd_sub(this->f_blockHealthAcc, gd::gd_mul(lv_numProccs, this->f_healthThreshold)));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_maxStamina, lv_numProccs)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxStaminaTemporary_316, _ca, 1); })();
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BionicArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getCurrentStamina_1262, nullptr, 0), this->f_staminaThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_block2}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {this->f_staminaUsed}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_empower}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BionicArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_staminaRegenMalus = gd::gd_div(gd_ctx, gd::gd_neg(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[56])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()), gd::GdVal::from_float(100.0));
    this->f_healthThreshold = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[57])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_maxStamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[58])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_staminaThreshold = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[59])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_staminaUsed = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[60])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[61])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_block2 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[62])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BionicArmor(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__BionicArmor>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,240u); return object; }
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
        case SYM_GEN_staminaPerRegen_2102: out = this->f_staminaPerRegen; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_luckNeeded_1874: out = this->f_luckNeeded; return true;
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Broccotree::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaPerRegen_2102: this->f_staminaPerRegen = gd::gd_coerce_float(val); return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_luckNeeded_1874: this->f_luckNeeded = val; return true;
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Broccotree::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onRegenChanged_1891: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Broccotree::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onRegenChanged_1891: out = fn_onRegenChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Broccotree::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Broccotree::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), this->f_luckNeeded)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Broccotree::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_baseStaminaRegen = gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_baseStaminaRegen_1057);
    this->f_staminaPerRegen = gd::gd_coerce_float(gd::gd_div(gd_ctx, gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[41])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), lv_baseStaminaRegen), gd::GdVal::from_float(100.0)));
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[63]), gd::GdVal::from_str(&battle_string_literals[64])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Broccotree::fn_onRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, this->f_staminaPerRegen)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_giveStaminaRegeneration_1270, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Broccotree::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[0])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[65])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[45])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Broccotree(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Broccotree>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,255u); return object; }
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
        case SYM_GEN_debuffs_2151: out = this->f_debuffs; return true;
        case SYM_GEN_healReduction_2152: out = this->f_healReduction; return true;
        case SYM_GEN_maxHealthReduction_2153: out = this->f_maxHealthReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackBishop::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_debuffs_2151: this->f_debuffs = val; return true;
        case SYM_GEN_healReduction_2152: this->f_healReduction = val; return true;
        case SYM_GEN_maxHealthReduction_2153: this->f_maxHealthReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackBishop::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2146: return true;
        case SYM_GEN_doEliminatedEffect_2148: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackBishop::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2146: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_doEliminatedEffect_2148: out = fn_doEliminatedEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {this->f_debuffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictRandomDebuffs_357, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackBishop::fn_doEliminatedEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_healReduction}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_reduceHealingEfficiency_1183, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_maxHealthReduction}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeMaxHealthGain_1277, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackBishop::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_debuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[66])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_healReduction = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[67])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_maxHealthReduction = gd::gd_div(gd_ctx, gd::gd_neg(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[68])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Chess__BlackBishop(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Chess__BlackBishop>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,272u); return object; }
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
        case SYM_GEN_hasActivated_1906: out = this->f_hasActivated; return true;
        case SYM_GEN_healthThreshold_1854: out = this->f_healthThreshold; return true;
        case SYM_GEN_healReduction_2152: out = this->f_healReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ChromeCube::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hasActivated_1906: this->f_hasActivated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_healthThreshold_1854: this->f_healthThreshold = val; return true;
        case SYM_GEN_healReduction_2152: this->f_healReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ChromeCube::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onDamaged_1855: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ChromeCube::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1855: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ChromeCube::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    this->f_affectedItem = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_428, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[69]), gd::GdVal::from_str(&battle_string_literals[70])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ChromeCube::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::native_scalar_truth(this->f_hasActivated)) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getRelativeHealth_302, nullptr, 0);
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_affectedItem, gd::GdVal::null())))) {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_advanceAffectedItem_2082, nullptr, 0);
        }
        (void)([&]() { gd::GdVal _ca[] = {this->f_healReduction}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_reduceHealingEfficiency_1183, _ca, 1); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_381, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ChromeCube::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Cube::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[57])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    this->f_healReduction = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[67])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ChromeCube(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__ChromeCube>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,287u); return object; }
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
        case SYM_GEN_mana_1928: out = this->f_mana; return true;
        case SYM_GEN_buffs_1048: out = this->f_buffs; return true;
        case SYM_GEN_darkSpeed_2199: out = this->f_darkSpeed; return true;
        case SYM_GEN_luckNeeded_1874: out = this->f_luckNeeded; return true;
        case SYM_GEN_stamina_2156: out = this->f_stamina; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DeathLotus::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_mana_1928: this->f_mana = val; return true;
        case SYM_GEN_buffs_1048: this->f_buffs = val; return true;
        case SYM_GEN_darkSpeed_2199: this->f_darkSpeed = val; return true;
        case SYM_GEN_luckNeeded_1874: this->f_luckNeeded = val; return true;
        case SYM_GEN_stamina_2156: this->f_stamina = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DeathLotus::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DeathLotus::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(25LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeathLotus::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0), this->f_darkSpeed)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeathLotus::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeRandomBuffs_372, _ca, 1); })();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), this->f_luckNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_luckNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useLucky_350, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_stamina, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_318, _ca, 2); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeathLotus::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[71])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_buffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[72])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_darkSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[73])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[65])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[41])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DeathLotus(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__DeathLotus>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,305u); return object; }
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
        case SYM_GEN_active_1653: out = this->f_active; return true;
        case SYM_GEN_weaponSpeed_2154: out = this->f_weaponSpeed; return true;
        case SYM_GEN_weaponStamina_2225: out = this->f_weaponStamina; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DualWielding::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_active_1653: this->f_active = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_weaponSpeed_2154: this->f_weaponSpeed = val; return true;
        case SYM_GEN_weaponStamina_2225: this->f_weaponStamina = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DualWielding::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onItemAdded_437: return true;
        case SYM_GEN_onItemRemoved_438: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_canAffect_global_2014: return true;
        case SYM_GEN_checkItems_2224: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DualWielding::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onItemAdded_437: out = fn_onItemAdded(args, argc); return true;
        case SYM_GEN_onItemRemoved_438: out = fn_onItemRemoved(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_canAffect_global_2014: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN_checkItems_2224: out = fn_checkItems(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemAdded_437, _ca, 1, _out); return _out; })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkItems_2224, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DualWielding::fn_onItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemRemoved_438, _ca, 1, _out); return _out; })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkItems_2224, nullptr, 0);
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
    return (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isWeapon_82, nullptr, 0)) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getBaseStaminaCost_111, nullptr, 0), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DualWielding::fn_checkItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numWeapons = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t797 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t798 = (_t797.kind == gd::GdVal::Kind::Arr) ? _t797.arr : nullptr;
        uint32_t _len__t799 = _t798 ? _t798->len : 0u;
        for (uint32_t _t799 = 0; _t799 < _len__t799; ++_t799) {
            gd::GdVal lv_item = _t798->data[_t799];
            if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_global_2014, _ca, 1); })())) {
                lv_numWeapons = gd::gd_add(gd_ctx, lv_numWeapons, gd::GdVal::from_int(1LL));
            }
        }
    }
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_numWeapons, gd::GdVal::from_int(2LL))))) {
        this->f_active = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
    }
    else {
        this->f_active = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DualWielding::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(this->f_active)) {
        {
            gd::GdVal _t800 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
            gd::GdArr* _t801 = (_t800.kind == gd::GdVal::Kind::Arr) ? _t800.arr : nullptr;
            uint32_t _len__t802 = _t801 ? _t801->len : 0u;
            for (uint32_t _t802 = 0; _t802 < _len__t802; ++_t802) {
                gd::GdVal lv_item = _t801->data[_t802];
                if (gd::native_scalar_truth((gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(4LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getBaseStaminaCost_111, nullptr, 0), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
                    (void)([&]() { gd::GdVal _ca[] = {this->f_weaponSpeed}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
                    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_weaponStamina)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeStaminaFactor_305, _ca, 1); })();
                }
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DualWielding::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_weaponSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[73])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_weaponStamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[41])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DualWielding(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__DualWielding>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,320u); return object; }
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
        case SYM_GEN_freeSlotSpeed_2254: out = this->f_freeSlotSpeed; return true;
        case SYM_GEN_salesChance_2092: out = this->f_salesChance; return true;
        case SYM_GEN_bagWeight_2255: out = this->f_bagWeight; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ExtraBags::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_freeSlotSpeed_2254: this->f_freeSlotSpeed = val; return true;
        case SYM_GEN_salesChance_2092: this->f_salesChance = val; return true;
        case SYM_GEN_bagWeight_2255: this->f_bagWeight = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ExtraBags::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_affectsEmpty_255: return true;
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onSaleRoll_2093: return true;
        case SYM_GEN_onItemRoll_2018: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ExtraBags::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_affectsEmpty_255: out = fn_affectsEmpty(args, argc); return true;
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onSaleRoll_2093: out = fn_onSaleRoll(args, argc); return true;
        case SYM_GEN_onItemRoll_2018: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraBags::fn_affectsEmpty(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(gd::native_scalar_eq(lv_color, gd::GdVal::from_int(1LL)));
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
    gd::GdVal lv_freeSlotSpeed_total = gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumEmptyAffectedCells_426, _ca, 1); })(), this->f_freeSlotSpeed);
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(lv_freeSlotSpeed_total, gd::GdVal::from_int(0LL))))) {
        {
            gd::GdVal _t803 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
            gd::GdArr* _t804 = (_t803.kind == gd::GdVal::Kind::Arr) ? _t803.arr : nullptr;
            uint32_t _len__t805 = _t804 ? _t804->len : 0u;
            for (uint32_t _t805 = 0; _t805 < _len__t805; ++_t805) {
                gd::GdVal lv_item = _t804->data[_t805];
                (void)([&]() { gd::GdVal _ca[] = {lv_freeSlotSpeed_total}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_freeSlotSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[73])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_salesChance = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[74])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_bagWeight = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[75])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ExtraBags(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__ExtraBags>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,335u); return object; }
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
        case SYM_GEN_gaveVampirism_2278: out = this->f_gaveVampirism; return true;
        case SYM_GEN_damagePerCold_2279: out = this->f_damagePerCold; return true;
        case SYM_GEN_coldNeeded_2280: out = this->f_coldNeeded; return true;
        case SYM_GEN_vampirism_940: out = this->f_vampirism; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Frostbite::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_gaveVampirism_2278: this->f_gaveVampirism = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_damagePerCold_2279: this->f_damagePerCold = val; return true;
        case SYM_GEN_coldNeeded_2280: this->f_coldNeeded = val; return true;
        case SYM_GEN_vampirism_940: this->f_vampirism = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Frostbite::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onVampirismChanged_943: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_onOpponentColdChanged_2204: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Frostbite::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onVampirismChanged_943: out = fn_onVampirismChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onOpponentColdChanged_2204: out = fn_onOpponentColdChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[76]), gd::GdVal::from_str(&battle_string_literals[77])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[78]), gd::GdVal::from_str(&battle_string_literals[79])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Frostbite::fn_onVampirismChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_162, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Frostbite::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth((gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_351, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Frostbite::fn_onOpponentColdChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_damagePerCold, lv_amount)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_162, _ca, 1); })();
    if (gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(this->f_gaveVampirism))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getCold_1254, nullptr, 0), this->f_coldNeeded)))) : gd::GdVal::from_bool(false)))) {
        this->f_gaveVampirism = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)([&]() { gd::GdVal _ca[] = {this->f_vampirism, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Frostbite::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_damagePerCold = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0);
    this->f_coldNeeded = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0));
    this->f_vampirism = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Frostbite(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Frostbite>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,349u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Frostbite = {CLS_Gd__gd_core_items__Exclusive__Frostbite, "Frostbite", "res://gd_core_items/Exclusive/Frostbite.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__Frostbite, &Gd__gd_core_items__Exclusive__Frostbite::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Frostbite::call_static_fn};

void Gd__gd_core_items__Exclusive__HeartShield::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Shield::init_fields(gd_ctx);
    this->f_activated = gd::GdVal::from_bool(false);
    this->f_regenGiven = gd::GdVal::from_int(0);
    this->f_fillAnimation = gd::GdVal::null();
    this->f_healamp = gd::GdVal::null();
    this->f_blockFactor = gd::GdVal::null();
    this->f_regenNeeded = gd::GdVal::null();
    this->f_regenOnBlock = gd::GdVal::null();
    this->f_regenMax = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__HeartShield::meta() const { return &META_Gd__gd_core_items__Exclusive__HeartShield; }
gd::GdVal Gd__gd_core_items__Exclusive__HeartShield::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Shield::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__HeartShield::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__HeartShield::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activated_1314: out = this->f_activated; return true;
        case SYM_GEN_regenGiven_2299: out = this->f_regenGiven; return true;
        case SYM_GEN_fillAnimation_1890: out = this->f_fillAnimation; return true;
        case SYM_GEN_healamp_2158: out = this->f_healamp; return true;
        case SYM_GEN_blockFactor_1977: out = this->f_blockFactor; return true;
        case SYM_GEN_regenNeeded_942: out = this->f_regenNeeded; return true;
        case SYM_GEN_regenOnBlock_2300: out = this->f_regenOnBlock; return true;
        case SYM_GEN_regenMax_2301: out = this->f_regenMax; return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__HeartShield::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1314: this->f_activated = val; return true;
        case SYM_GEN_regenGiven_2299: this->f_regenGiven = gd::gd_coerce_int(val); return true;
        case SYM_GEN_fillAnimation_1890: this->f_fillAnimation = val; return true;
        case SYM_GEN_healamp_2158: this->f_healamp = val; return true;
        case SYM_GEN_blockFactor_1977: this->f_blockFactor = val; return true;
        case SYM_GEN_regenNeeded_942: this->f_regenNeeded = val; return true;
        case SYM_GEN_regenOnBlock_2300: this->f_regenOnBlock = val; return true;
        case SYM_GEN_regenMax_2301: this->f_regenMax = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__HeartShield::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_afterBlock_1942: return true;
        case SYM_GEN_onRegenChanged_1891: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN_preTakeDamage_1944: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__HeartShield::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_afterBlock_1942: out = fn_afterBlock(args, argc); return true;
        case SYM_GEN_onRegenChanged_1891: out = fn_onRegenChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_preTakeDamage_1944: out = fn_preTakeDamage(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__HeartShield::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Shield::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartShield::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::native_scalar_truth((gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBlock_291, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canHealOrLifesteal_292, nullptr, 0))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(4LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_gainsStack_86, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartShield::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t806 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t807 = (_t806.kind == gd::GdVal::Kind::Arr) ? _t806.arr : nullptr;
        uint32_t _len__t808 = _t807 ? _t807->len : 0u;
        for (uint32_t _t808 = 0; _t808 < _len__t808; ++_t808) {
            gd::GdVal lv_item = _t807->data[_t808];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(100LL), this->f_blockFactor}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_giveBuffPower_303, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_healamp}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeHealAmp_304, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(102LL), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_196, _ca, 2); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[63]), gd::GdVal::from_str(&battle_string_literals[64])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    this->f_regenGiven = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartShield::fn_afterBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), gd::native_inline_get_prop(gd_ctx, this->f_blockedDamageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drainStamina_117, _ca, 2); })();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_regenGiven, this->f_regenMax)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regenOnBlock, gd::native_inline_get_prop(gd_ctx, this->f_blockedDamageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 2); })();
        this->f_regenGiven = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_regenGiven, this->f_regenOnBlock));
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartShield::fn_onRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::native_scalar_truth((gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(this->f_activated)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRegeneration_1233, nullptr, 0), this->f_regenNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
        gd::GdVal lv_event2 = ([&]() { gd::GdVal _ca[] = {this->f_regenNeeded, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_346, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[80])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), lv_event2}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartShield::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartShield::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_filled = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_activated, lv_filled)))) {
        return gd::GdVal::null();
    }
    this->f_activated = lv_filled;
    if (gd::native_scalar_truth(lv_filled)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartShield::fn_preTakeDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(this->f_activated)) {
        if (gd::native_scalar_truth((gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_isAttackOrEffect_1562, nullptr, 0)) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
            this->f_blockedDamageRes = lv_damageRes;
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_beforeBlock_1941, nullptr, 0);
        }
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {lv_damageRes}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Shield::call_method(gd_ctx, SYM_GEN_preTakeDamage_1944, _ca, 1, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartShield::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Shield::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_healamp = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[43])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_blockFactor = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[62])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_regenNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[81])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regenOnBlock = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[45])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regenMax = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[82])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__HeartShield(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__HeartShield>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,363u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__HeartShield = {CLS_Gd__gd_core_items__Exclusive__HeartShield, "HeartShield", "res://gd_core_items/Exclusive/HeartShield.gd", &META_Gd__gd_core_items__Shield, true, _alloc_Gd__gd_core_items__Exclusive__HeartShield, &Gd__gd_core_items__Exclusive__HeartShield::get_static_prop_fn, &Gd__gd_core_items__Exclusive__HeartShield::call_static_fn};

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
        case SYM_GEN__readyInit_140: return true;
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
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__JustStats::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__JustStats::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_round(gd::gd_mul(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[80])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMaxHealth_1160, nullptr, 0)))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_staminaRegen}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_giveStaminaRegeneration_1270, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__JustStats::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(-1000LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__JustStats::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_642, _ca, 1, _out); return _out; })();
    gd::GdVal lv_string = gd::GdVal::null();
    if (gd::native_scalar_truth(lv_wrapInColor)) {
        lv_string = ([&]() { gd::GdVal _ca[] = {([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 1); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[83]), gd::GdVal::null()); return gd::GdVal::from_dict(d); })()}; return gd::native_inline_call(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[84])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_tr_2826, _ca, 1); })(), SYM_GEN_format_2716, _ca, 1); })();
    }
    else {
        lv_string = ([&]() { gd::GdVal _ca[] = {([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 1); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[83]), gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_appearRounds_2827), gd::GdVal::from_int(0LL))); return gd::GdVal::from_dict(d); })()}; return gd::native_inline_call(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[84])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_tr_2826, _ca, 1); })(), SYM_GEN_format_2716, _ca, 1); })();
    }
    lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[85]), lv_string));
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_staminaRegen = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[41])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__JustStats(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__JustStats>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,379u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__JustStats = {CLS_Gd__gd_core_items__Exclusive__JustStats, "JustStats", "res://gd_core_items/Exclusive/JustStats.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__JustStats, &Gd__gd_core_items__Exclusive__JustStats::get_static_prop_fn, &Gd__gd_core_items__Exclusive__JustStats::call_static_fn};

void Gd__gd_core_items__Exclusive__Lootbox::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_itemValue = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Lootbox::meta() const { return &META_Gd__gd_core_items__Exclusive__Lootbox; }
gd::GdVal Gd__gd_core_items__Exclusive__Lootbox::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_OFFSET_2353: return gd::GdVal::from_float(50.0);
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Lootbox::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    switch (prop) {
        case SYM_GEN_OFFSET_2353: out = gd::GdVal::from_float(50.0); return true;
        default: break;
    }
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
        case SYM_GEN_itemValue_2354: out = this->f_itemValue; return true;
        case SYM_GEN_OFFSET_2353: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Lootbox::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_itemValue_2354: this->f_itemValue = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Lootbox::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onDropped_2034: return true;
        case SYM_GEN_generateItems_2355: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Lootbox::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDropped_2034: out = fn_onDropped(args, argc); return true;
        case SYM_GEN_generateItems_2355: out = fn_generateItems(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    if (gd::native_scalar_truth((gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {lv_dropRes}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core_items__Exclusive__Lootbox::call_static_fn(gd_ctx, SYM_GEN_wasAddedToInventory_659, _ca, 1, _out); return _out; })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_dropRes, gd::native_inline_get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Lootbox::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_AddedToStorageBox_2723)))))))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_prepareReplacement_446, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[86]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_dropRes}))}; return gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_defer_1482, _ca, 3); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_itemValue = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[87])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[88]), gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[89])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_connect, _ca, 3); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Lootbox(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Lootbox>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,394u); return object; }
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
        case SYM_GEN_staminaUsed_2076: out = this->f_staminaUsed; return true;
        case SYM_GEN_poison_1962: out = this->f_poison; return true;
        case SYM_GEN_selfPoison_2403: out = this->f_selfPoison; return true;
        case SYM_GEN_staminaThreshold_2075: out = this->f_staminaThreshold; return true;
        case SYM_GEN_distortion_2203: out = this->f_distortion; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MercuryElemental::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaRegen_1058: this->f_staminaRegen = gd::gd_coerce_float(val); return true;
        case SYM_GEN_staminaUsed_2076: this->f_staminaUsed = gd::gd_coerce_float(val); return true;
        case SYM_GEN_poison_1962: this->f_poison = val; return true;
        case SYM_GEN_selfPoison_2403: this->f_selfPoison = val; return true;
        case SYM_GEN_staminaThreshold_2075: this->f_staminaThreshold = val; return true;
        case SYM_GEN_distortion_2203: this->f_distortion = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MercuryElemental::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_isAffectingDistinct_254: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onOpponentAttacked_2404: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onStaminaUsed_2405: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MercuryElemental::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_isAffectingDistinct_254: out = fn_isAffectingDistinct(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onOpponentAttacked_2404: out = fn_onOpponentAttacked(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onStaminaUsed_2405: out = fn_onStaminaUsed(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__MercuryElemental::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__MercuryElemental::fn_isAffectingDistinct(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    return gd::GdVal::from_bool(gd::native_scalar_eq(lv_color, gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MercuryElemental::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), SYM_GEN_isMeleeWeapon_1722, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MercuryElemental::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[36]), gd::GdVal::from_str(&battle_string_literals[90])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[91]), gd::GdVal::from_str(&battle_string_literals[92])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    this->f_staminaRegen = gd::gd_coerce_float(gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[41])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumDistinctAffectedItems_430, nullptr, 0)));
    this->f_staminaUsed = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MercuryElemental::fn_onOpponentAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_triggerOnAttacked_1530, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), gd::GdVal::from_float(100.0)), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MercuryElemental::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_staminaRegen}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_318, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MercuryElemental::fn_onStaminaUsed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_staminaUsed = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_staminaUsed, lv_amount));
    gd::GdVal lv_ticks = gd::gd_floor(gd::gd_div(gd_ctx, this->f_staminaUsed, this->f_staminaThreshold));
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(lv_ticks, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_ticks, this->f_poison)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_ticks, this->f_selfPoison)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_selfInflictPoison_212, _ca, 1); })();
        this->f_staminaUsed = gd::gd_coerce_float(gd::gd_sub(this->f_staminaUsed, gd::gd_mul(lv_ticks, this->f_staminaThreshold)));
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MercuryElemental::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_poison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[93])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_selfPoison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[94])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_staminaThreshold = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[95])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(12LL))))) {
    }
    else {
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MercuryElemental(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__MercuryElemental>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,410u); return object; }
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
        case SYM_GEN_numActivations_1904: out = this->f_numActivations; return true;
        case SYM_GEN_speedBonus_1877: out = this->f_speedBonus; return true;
        case SYM_GEN_maxActivations_1905: out = this->f_maxActivations; return true;
        case SYM_GEN_bonusHeal_2419: out = this->f_bonusHeal; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ParadiseBirb::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numActivations_1904: this->f_numActivations = gd::gd_coerce_int(val); return true;
        case SYM_GEN_speedBonus_1877: this->f_speedBonus = val; return true;
        case SYM_GEN_maxActivations_1905: this->f_maxActivations = val; return true;
        case SYM_GEN_bonusHeal_2419: this->f_bonusHeal = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ParadiseBirb::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_149: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ParadiseBirb::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_149: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    return (gd::native_scalar_truth((gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_gainsBuffs_296, nullptr, 0))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canHealOrLifesteal_292, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ParadiseBirb::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_numActivations = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ParadiseBirb::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_numActivations, this->f_maxActivations)))) {
        {
            gd::GdVal _t809 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
            gd::GdArr* _t810 = (_t809.kind == gd::GdVal::Kind::Arr) ? _t809.arr : nullptr;
            uint32_t _len__t811 = _t810 ? _t810->len : 0u;
            for (uint32_t _t811 = 0; _t811 < _len__t811; ++_t811) {
                gd::GdVal lv_item = _t810->data[_t811];
                (void)([&]() { gd::GdVal _ca[] = {this->f_speedBonus}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_allBuffs_197, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {this->f_bonusHeal}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeHealAmp_304, _ca, 1); })();
            }
        }
        this->f_numActivations = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numActivations, gd::GdVal::from_int(1LL)));
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_numActivations, this->f_maxActivations)))) {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
        }
        else {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ParadiseBirb::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_pitch = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.8), gd::GdVal::from_float(1.0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ParadiseBirb::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    gd::GdVal lv_pitch = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.8), gd::GdVal::from_float(1.0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ParadiseBirb::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speedBonus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[73])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_maxActivations = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[96])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_bonusHeal = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[43])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ParadiseBirb(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__ParadiseBirb>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,426u); return object; }
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
        case SYM_GEN_boosted_2197: out = this->f_boosted; return true;
        case SYM_GEN_moonArmorDescriptor_2439: out = this->f_moonArmorDescriptor; return true;
        case SYM_GEN_moonShieldDescriptor_2440: out = this->f_moonShieldDescriptor; return true;
        case SYM_GEN_manaOrbDescriptor_2393: out = this->f_manaOrbDescriptor; return true;
        case SYM_GEN_timeAdvance_2441: out = this->f_timeAdvance; return true;
        case SYM_GEN_blind_1911: out = this->f_blind; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PoweroftheMoon::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_boosted_2197: this->f_boosted = val; return true;
        case SYM_GEN_moonArmorDescriptor_2439: this->f_moonArmorDescriptor = val; return true;
        case SYM_GEN_moonShieldDescriptor_2440: this->f_moonShieldDescriptor = val; return true;
        case SYM_GEN_manaOrbDescriptor_2393: this->f_manaOrbDescriptor = val; return true;
        case SYM_GEN_timeAdvance_2441: this->f_timeAdvance = val; return true;
        case SYM_GEN_blind_1911: this->f_blind = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PoweroftheMoon::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_onBought_455: return true;
        case SYM_GEN_onPostCombatStart_129: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onFatigueStarted_1969: return true;
        case SYM_GEN_onMoonArmorActivated_2442: return true;
        case SYM_GEN_onMoonShiedActivated_2443: return true;
        case SYM_GEN_onItemRoll_2018: return true;
        case SYM_GEN_onItemRolled_2019: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PoweroftheMoon::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_onBought_455: out = fn_onBought(args, argc); return true;
        case SYM_GEN_onPostCombatStart_129: out = fn_onPostCombatStart(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onFatigueStarted_1969: out = fn_onFatigueStarted(args, argc); return true;
        case SYM_GEN_onMoonArmorActivated_2442: out = fn_onMoonArmorActivated(args, argc); return true;
        case SYM_GEN_onMoonShiedActivated_2443: out = fn_onMoonShiedActivated(args, argc); return true;
        case SYM_GEN_onItemRoll_2018: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_2019: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    return (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {this->f_moonArmorDescriptor}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isA_245, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {this->f_moonShieldDescriptor}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isA_245, _ca, 1); })())));
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
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_data, gd::GdVal::null())))) {
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
    (void)([&]() { gd::GdVal _ca[] = {this->f_timeAdvance}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_1420), SYM_GEN_advanceTime_1330, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoweroftheMoon::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_1420), gd::GdVal::from_str(&battle_string_literals[11]), gd::GdVal::from_str(&battle_string_literals[97])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    {
        gd::GdVal _t812 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t813 = (_t812.kind == gd::GdVal::Kind::Arr) ? _t812.arr : nullptr;
        uint32_t _len__t814 = _t813 ? _t813->len : 0u;
        for (uint32_t _t814 = 0; _t814 < _len__t814; ++_t814) {
            gd::GdVal lv_item = _t813->data[_t814];
            if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {this->f_moonArmorDescriptor}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isA_245, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[49]), gd::GdVal::from_str(&battle_string_literals[98])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
            }
            else {
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[49]), gd::GdVal::from_str(&battle_string_literals[99])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoweroftheMoon::fn_onFatigueStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bonusHealth = gd::gd_mul(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[80])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMaxHealth_1160, nullptr, 0));
    (void)([&]() { gd::GdVal _ca[] = {lv_bonusHealth}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoweroftheMoon::fn_onMoonArmorActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_blind, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_213, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoweroftheMoon::fn_onMoonShiedActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveReflectStacks_200, _ca, 1); })();
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
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_descr, this->f_manaOrbDescriptor)))) {
        this->f_boosted = gd::gd_sub(this->f_boosted, gd::GdVal::from_int(1LL));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoweroftheMoon::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_moonArmorDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[100])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_moonShieldDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[101])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_manaOrbDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[102])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_timeAdvance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[103])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_blind = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[104])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PoweroftheMoon(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__PoweroftheMoon>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,442u); return object; }
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
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__RainbowOrb::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    return (gd::native_scalar_truth((gd::native_scalar_truth((gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(24LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(23LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(25LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowOrb::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_typesDict = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countTypes_495, _ca, 1); })();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_array_index(gd_ctx, lv_typesDict, gd::GdVal::from_int(24LL)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_array_index(gd_ctx, lv_typesDict, gd::GdVal::from_int(24LL)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[105])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
    }
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_array_index(gd_ctx, lv_typesDict, gd::GdVal::from_int(23LL)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_array_index(gd_ctx, lv_typesDict, gd::GdVal::from_int(23LL)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[71])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
    }
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_array_index(gd_ctx, lv_typesDict, gd::GdVal::from_int(22LL)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(gd::native_array_index(gd_ctx, lv_typesDict, gd::GdVal::from_int(22LL)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[43])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_addHealingEfficiency_1182, _ca, 1); })();
    }
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_array_index(gd_ctx, lv_typesDict, gd::GdVal::from_int(25LL)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_array_index(gd_ctx, lv_typesDict, gd::GdVal::from_int(25LL)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[66])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictRandomDebuffs_357, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowOrb::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveAllBuffs_370, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowOrb::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_642, _ca, 1, _out); return _out; })();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(this->f_placed)))) {
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[106]), gd::GdVal::from_str(&battle_string_literals[17])}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[107]), gd::GdVal::from_str(&battle_string_literals[17])}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[108]), gd::GdVal::from_str(&battle_string_literals[17])}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[109]), gd::GdVal::from_str(&battle_string_literals[17])}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        return lv_descr;
    }
    gd::GdVal lv_typesDict = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countTypes_495, _ca, 1); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[110]), gd::native_array_index(gd_ctx, lv_typesDict, gd::GdVal::from_int(23LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_452, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[111]), gd::native_array_index(gd_ctx, lv_typesDict, gd::GdVal::from_int(24LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_452, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[112]), gd::native_array_index(gd_ctx, lv_typesDict, gd::GdVal::from_int(22LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_452, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[113]), gd::native_array_index(gd_ctx, lv_typesDict, gd::GdVal::from_int(25LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_452, _ca, 3); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowOrb::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_buffs = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[72])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__RainbowOrb(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__RainbowOrb>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,458u); return object; }
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
        case SYM_GEN_mana_1928: out = this->f_mana; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ScholarBag::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_mana_1928: this->f_mana = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ScholarBag::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ScholarBag::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(32LL)}; return gd::native_inline_call(gd_ctx, lv_toItem, SYM_GEN_gainsStack_86, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ScholarBag::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t815 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_927, nullptr, 0));
        gd::GdArr* _t816 = (_t815.kind == gd::GdVal::Kind::Arr) ? _t815.arr : nullptr;
        uint32_t _len__t817 = _t816 ? _t816->len : 0u;
        for (uint32_t _t817 = 0; _t817 < _len__t817; ++_t817) {
            gd::GdVal lv_item = _t816->data[_t817];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(105LL), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_196, _ca, 2); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(105LL), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeProtectionChance_1285, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ScholarBag::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ScholarBag::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[71])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ScholarBag(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__ScholarBag>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,474u); return object; }
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
        case SYM_GEN_awakenNow_2499: out = this->f_awakenNow; return true;
        case SYM_GEN_speed_v_2179: out = this->f_speed_v; return true;
        case SYM_GEN_buffs_1048: out = this->f_buffs; return true;
        case SYM_GEN_buffsAmulet_2500: out = this->f_buffsAmulet; return true;
        case SYM_GEN_light1_2501: out = this->f_light1; return true;
        case SYM_GEN_light2_2502: out = this->f_light2; return true;
        case SYM_GEN_particles1_2503: out = this->f_particles1; return true;
        case SYM_GEN_particles2_2504: out = this->f_particles2; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Sloth::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_awakenNow_2499: this->f_awakenNow = val; return true;
        case SYM_GEN_speed_v_2179: this->f_speed_v = val; return true;
        case SYM_GEN_buffs_1048: this->f_buffs = val; return true;
        case SYM_GEN_buffsAmulet_2500: this->f_buffsAmulet = val; return true;
        case SYM_GEN_light1_2501: this->f_light1 = val; return true;
        case SYM_GEN_light2_2502: this->f_light2 = val; return true;
        case SYM_GEN_particles1_2503: this->f_particles1 = val; return true;
        case SYM_GEN_particles2_2504: this->f_particles2 = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Sloth::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_trigger_143: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Sloth::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_trigger_143: out = fn_trigger(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Sloth::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    {
        gd::GdVal _t818 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t819 = (_t818.kind == gd::GdVal::Kind::Arr) ? _t818.arr : nullptr;
        uint32_t _len__t820 = _t819 ? _t819->len : 0u;
        for (uint32_t _t820 = 0; _t820 < _len__t820; ++_t820) {
            gd::GdVal lv_item = _t819->data[_t820];
            (void)([&]() { gd::GdVal _ca[] = {this->f_speed_v}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_reduceSpeed_274, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Sloth::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_m = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[114])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })();
    lv_m = gd::gd_add(gd_ctx, lv_m, gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[115])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()));
    lv_m = gd::gd_round(gd::gd_mul(gd::gd_div(gd_ctx, lv_m, gd::GdVal::from_float(100.0)), gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMaxHealth_1160, nullptr, 0)));
    (void)([&]() { gd::GdVal _ca[] = {lv_m}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Sloth::fn_trigger(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_awakenNow = gd::GdVal::from_bool(true);
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_trigger_143, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Sloth::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(this->f_awakenNow)) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_buffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveAllBuffs_370, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[116])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_330, _ca, 1); })();
        this->f_awakenNow = gd::GdVal::from_bool(false);
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {this->f_buffsAmulet}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveAllBuffs_370, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[117])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_330, _ca, 1); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Sloth::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Sloth::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_awakened = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_awakened = gd::gd_coerce_bool(lv_awakened);
    if (gd::native_scalar_truth(lv_awakened)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Sloth::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_642, _ca, 1, _out); return _out; })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[118]), gd::GdVal::from_str(&battle_string_literals[119])}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[120]), gd::GdVal::from_str(&battle_string_literals[121])}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Sloth::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speed_v = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[73])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_buffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[72])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_buffsAmulet = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[122])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Sloth(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Sloth>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,490u); return object; }
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
        case SYM_GEN_staminaUsed_2076: out = this->f_staminaUsed; return true;
        case SYM_GEN_boostedBananas_2531: out = this->f_boostedBananas; return true;
        case SYM_GEN_bananaDescriptor_2532: out = this->f_bananaDescriptor; return true;
        case SYM_GEN_manananaDescriptor_2533: out = this->f_manananaDescriptor; return true;
        case SYM_GEN_heatPerActivation_2534: out = this->f_heatPerActivation; return true;
        case SYM_GEN_staminaForHeal_2535: out = this->f_staminaForHeal; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SpicyBanana::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaUsed_2076: this->f_staminaUsed = gd::gd_coerce_float(val); return true;
        case SYM_GEN_boostedBananas_2531: this->f_boostedBananas = val; return true;
        case SYM_GEN_bananaDescriptor_2532: this->f_bananaDescriptor = val; return true;
        case SYM_GEN_manananaDescriptor_2533: this->f_manananaDescriptor = val; return true;
        case SYM_GEN_heatPerActivation_2534: this->f_heatPerActivation = val; return true;
        case SYM_GEN_staminaForHeal_2535: this->f_staminaForHeal = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SpicyBanana::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onBought_455: return true;
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onBananaActivated_2536: return true;
        case SYM_GEN_onStaminaUsed_2405: return true;
        case SYM_GEN_onItemRoll_2018: return true;
        case SYM_GEN_onItemRolled_2019: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SpicyBanana::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onBought_455: out = fn_onBought(args, argc); return true;
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBananaActivated_2536: out = fn_onBananaActivated(args, argc); return true;
        case SYM_GEN_onStaminaUsed_2405: out = fn_onStaminaUsed(args, argc); return true;
        case SYM_GEN_onItemRoll_2018: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_2019: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    return (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {this->f_bananaDescriptor}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isA_245, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {this->f_manananaDescriptor}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isA_245, _ca, 1); })())));
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
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_data, gd::GdVal::null())))) {
        this->f_boostedBananas = lv_data;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpicyBanana::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t821 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t822 = (_t821.kind == gd::GdVal::Kind::Arr) ? _t821.arr : nullptr;
        uint32_t _len__t823 = _t822 ? _t822->len : 0u;
        for (uint32_t _t823 = 0; _t823 < _len__t823; ++_t823) {
            gd::GdVal lv_banana = _t822->data[_t823];
            (void)([&]() { gd::GdVal _ca[] = {lv_banana, gd::GdVal::from_str(&battle_string_literals[49]), gd::GdVal::from_str(&battle_string_literals[123])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    this->f_staminaUsed = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[91]), gd::GdVal::from_str(&battle_string_literals[92])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpicyBanana::fn_onBananaActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_heatPerActivation, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 2); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpicyBanana::fn_onStaminaUsed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_staminaUsed = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_staminaUsed, lv_amount));
    gd::GdVal lv_healTicks = gd::gd_floor(gd::gd_div(gd_ctx, this->f_staminaUsed, this->f_staminaForHeal));
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(lv_healTicks, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_healTicks, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[124])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 1); })();
        this->f_staminaUsed = gd::gd_coerce_float(gd::gd_sub(this->f_staminaUsed, gd::gd_mul(lv_healTicks, this->f_staminaForHeal)));
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
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
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_descr, this->f_bananaDescriptor)))) {
        this->f_boostedBananas = gd::gd_sub(this->f_boostedBananas, gd::GdVal::from_int(1LL));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpicyBanana::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_bananaDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[125])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_manananaDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[126])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_heatPerActivation = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[127])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_staminaForHeal = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[41])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SpicyBanana(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__SpicyBanana>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,506u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpicyBanana = {CLS_Gd__gd_core_items__Exclusive__SpicyBanana, "SpicyBanana", "res://gd_core_items/Exclusive/SpicyBanana.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__SpicyBanana, &Gd__gd_core_items__Exclusive__SpicyBanana::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SpicyBanana::call_static_fn};

void Gd__gd_core_items__Exclusive__StoneGolem::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_activated = gd::GdVal::from_bool(false);
    this->f_hasStunned = gd::GdVal::from_bool(false);
    this->f_empower = gd::GdVal::null();
    this->f_regenThreshold = gd::GdVal::null();
    this->f_bagOfStonesDescriptor = gd::GdVal::null();
    this->f_activationParticles1 = gd::GdVal::null();
    this->f_activationParticles2 = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__StoneGolem::meta() const { return &META_Gd__gd_core_items__Exclusive__StoneGolem; }
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__StoneGolem::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__StoneGolem::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activated_1314: out = this->f_activated; return true;
        case SYM_GEN_hasStunned_1974: out = this->f_hasStunned; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        case SYM_GEN_regenThreshold_2561: out = this->f_regenThreshold; return true;
        case SYM_GEN_bagOfStonesDescriptor_2562: out = this->f_bagOfStonesDescriptor; return true;
        case SYM_GEN_activationParticles1_2563: out = this->f_activationParticles1; return true;
        case SYM_GEN_activationParticles2_2564: out = this->f_activationParticles2; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__StoneGolem::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1314: this->f_activated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_hasStunned_1974: this->f_hasStunned = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        case SYM_GEN_regenThreshold_2561: this->f_regenThreshold = val; return true;
        case SYM_GEN_bagOfStonesDescriptor_2562: this->f_bagOfStonesDescriptor = val; return true;
        case SYM_GEN_activationParticles1_2563: this->f_activationParticles1 = val; return true;
        case SYM_GEN_activationParticles2_2564: this->f_activationParticles2 = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__StoneGolem::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreCombatStart_125: return true;
        case SYM_GEN_onRegenChanged_1891: return true;
        case SYM_GEN_attack_941: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__StoneGolem::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreCombatStart_125: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_onRegenChanged_1891: out = fn_onRegenChanged(args, argc); return true;
        case SYM_GEN_attack_941: out = fn_attack(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__StoneGolem::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {this->f_bagOfStonesDescriptor}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isA_245, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[63]), gd::GdVal::from_str(&battle_string_literals[64])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[128])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn_onRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(this->f_activated))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRegeneration_1233, nullptr, 0), this->f_regenThreshold)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
            gd::GdVal lv_event2 = ([&]() { gd::GdVal _ca[] = {this->f_regenThreshold, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_346, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), gd::GdVal::from_bool(true), lv_event2}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 3); })();
            this->f_baseCooldownOverride = gd::gd_coerce_float(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0));
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateBaseCooldown_110, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn_attack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    this->f_hasStunned = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    gd::GdVal lv_res = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_220, _ca, 1); })();
    if (gd::native_scalar_truth(this->f_hasStunned)) {
        (void)([&]() { gd::GdVal _ca[] = {lv_res, gd::GdVal::from_bool(true), gd::GdVal::from_bool(false), gd::native_inline_get_prop(gd_ctx, Gd__gd_core_items__Exclusive__StoneGolem::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Tackle_2753)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 4); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_empower}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
            this->f_hasStunned = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[116])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_330, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(lv_active)) {
    }
    else {
    }
    this->f_activated = gd::gd_coerce_bool(lv_active);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::GdVal::from_int(1000LL), gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_empower = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[61])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_regenThreshold = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[45])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_bagOfStonesDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[129])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__StoneGolem(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__StoneGolem>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,522u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StoneGolem = {CLS_Gd__gd_core_items__Exclusive__StoneGolem, "StoneGolem", "res://gd_core_items/Exclusive/StoneGolem.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__StoneGolem, &Gd__gd_core_items__Exclusive__StoneGolem::get_static_prop_fn, &Gd__gd_core_items__Exclusive__StoneGolem::call_static_fn};

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
        case SYM_GEN_heat_1896: out = this->f_heat; return true;
        case SYM_GEN_bonusdur_2450: out = this->f_bonusdur; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__TimeMelting::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heat_1896: this->f_heat = val; return true;
        case SYM_GEN_bonusdur_2450: this->f_bonusdur = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__TimeMelting::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__TimeMelting::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasInventoryDuration_797, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TimeMelting::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t824 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t825 = (_t824.kind == gd::GdVal::Kind::Arr) ? _t824.arr : nullptr;
        uint32_t _len__t826 = _t825 ? _t825->len : 0u;
        for (uint32_t _t826 = 0; _t826 < _len__t826; ++_t826) {
            gd::GdVal lv_item = _t825->data[_t826];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[130]), this->f_bonusdur}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_modifyParam_191, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TimeMelting::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TimeMelting::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::GdVal::from_int(1000LL), gd::GdVal::from_int(100LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TimeMelting::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[127])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_bonusdur = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[131])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__TimeMelting(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__TimeMelting>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,538u); return object; }
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
        case SYM_GEN_manaUsed_2007: out = this->f_manaUsed; return true;
        case SYM_GEN_activeEffects_2615: out = this->f_activeEffects; return true;
        case SYM_GEN_coldParticles_2616: out = this->f_coldParticles; return true;
        case SYM_GEN_distortion_2203: out = this->f_distortion; return true;
        case SYM_GEN_manaOnHit_2617: out = this->f_manaOnHit; return true;
        case SYM_GEN_bonusManaOnHit_2618: out = this->f_bonusManaOnHit; return true;
        case SYM_GEN_iceSpeed_2516: out = this->f_iceSpeed; return true;
        case SYM_GEN_bonusDam_1875: out = this->f_bonusDam; return true;
        case SYM_GEN_coldOnHit_2315: out = this->f_coldOnHit; return true;
        case SYM_GEN_manaNeeded1_2619: out = this->f_manaNeeded1; return true;
        case SYM_GEN_manaNeeded2_2620: out = this->f_manaNeeded2; return true;
        case SYM_GEN_manaNeeded3_2621: out = this->f_manaNeeded3; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__WaterElemental::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaUsed_2007: this->f_manaUsed = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activeEffects_2615: this->f_activeEffects = val; return true;
        case SYM_GEN_coldParticles_2616: this->f_coldParticles = val; return true;
        case SYM_GEN_distortion_2203: this->f_distortion = val; return true;
        case SYM_GEN_manaOnHit_2617: this->f_manaOnHit = val; return true;
        case SYM_GEN_bonusManaOnHit_2618: this->f_bonusManaOnHit = val; return true;
        case SYM_GEN_iceSpeed_2516: this->f_iceSpeed = val; return true;
        case SYM_GEN_bonusDam_1875: this->f_bonusDam = val; return true;
        case SYM_GEN_coldOnHit_2315: this->f_coldOnHit = val; return true;
        case SYM_GEN_manaNeeded1_2619: this->f_manaNeeded1 = val; return true;
        case SYM_GEN_manaNeeded2_2620: this->f_manaNeeded2 = val; return true;
        case SYM_GEN_manaNeeded3_2621: this->f_manaNeeded3 = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__WaterElemental::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onManaChanged_1929: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_149: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__WaterElemental::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onManaChanged_1929: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_149: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(26LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(28LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[132]), gd::GdVal::from_str(&battle_string_literals[133])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    this->f_manaUsed = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_iceSpeed, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    this->f_activeEffects = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {this->f_activeEffects}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::fn_onManaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::native_scalar_truth((gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, lv_event, SYM_GEN_type_1005), gd::GdVal::from_int(105LL))))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[134]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getParam_1575, _ca, 2); })())) : gd::GdVal::from_bool(false)))) {
        this->f_manaUsed = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_manaUsed, gd::gd_abs(lv_amount)));
        gd::GdVal lv_before = this->f_activeEffects;
        if (gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_activeEffects, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_manaUsed, this->f_manaNeeded1)))) : gd::GdVal::from_bool(false)))) {
            this->f_activeEffects = gd::GdVal::from_int(1LL);
        }
        if (gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_activeEffects, gd::GdVal::from_int(1LL)))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_manaUsed, this->f_manaNeeded2)))) : gd::GdVal::from_bool(false)))) {
            this->f_activeEffects = gd::GdVal::from_int(2LL);
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusDam}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
        }
        if (gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_activeEffects, gd::GdVal::from_int(2LL)))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_manaUsed, this->f_manaNeeded3)))) : gd::GdVal::from_bool(false)))) {
            this->f_activeEffects = gd::GdVal::from_int(3LL);
        }
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_before, this->f_activeEffects)))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_activeEffects}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        gd::GdVal lv_mana = this->f_manaOnHit;
        gd::GdVal lv_chance = gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0));
        if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, _ca, 1); })())) {
            lv_mana = gd::gd_add(gd_ctx, lv_mana, this->f_bonusManaOnHit);
        }
        (void)([&]() { gd::GdVal _ca[] = {lv_mana, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 2); })();
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_activeEffects, gd::GdVal::from_int(1LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[124])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 2); })();
        }
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_activeEffects, gd::GdVal::from_int(3LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_coldOnHit, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_351, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__activeEffects = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__activeEffects = gd::gd_coerce_int(lv__activeEffects);
    this->f_activeEffects = lv__activeEffects;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_activeEffects, gd::GdVal::from_int(3LL))))) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_getDescription_642, _ca, 1, _out); return _out; })();
    gd::GdVal lv_colors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_triggerColor_2828), gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_triggerColor_2828), gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_triggerColor_2828)}));
    if (gd::native_scalar_truth(this->f_placed)) {
        {
            gd::GdVal _t827 = gd::gd_iter_seq(gd_ctx.arena, this->f_activeEffects);
            gd::GdArr* _t828 = (_t827.kind == gd::GdVal::Kind::Arr) ? _t827.arr : nullptr;
            uint32_t _len__t829 = _t828 ? _t828->len : 0u;
            for (uint32_t _t829 = 0; _t829 < _len__t829; ++_t829) {
                gd::GdVal lv_i = _t828->data[_t829];
                { gd::GdVal _t830 = lv_colors; gd::GdVal _t831 = lv_i; gd::native_array_set_index(gd_ctx, _t830, _t831, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_modifiedColor_2829)); }
            }
        }
    }
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, lv_colors, gd::GdVal::from_bool(false), lv_wrapInColor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModeDescription_645, _ca, 4); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_manaOnHit = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[71])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_bonusManaOnHit = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[135])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_iceSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[73])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_bonusDam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[44])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_coldOnHit = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[136])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_manaNeeded1 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[137])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_manaNeeded2 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[138])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_manaNeeded3 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[139])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(12LL))))) {
    }
    else {
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__WaterElemental(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__WaterElemental>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,556u); return object; }
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
        case SYM_GEN_damageBonusApplied_2628: out = this->f_damageBonusApplied; return true;
        case SYM_GEN_debuffsInflicted_2629: out = this->f_debuffsInflicted; return true;
        case SYM_GEN_weaponParticles_2630: out = this->f_weaponParticles; return true;
        case SYM_GEN_healthThreshold_1854: out = this->f_healthThreshold; return true;
        case SYM_GEN_damageFactor_2410: out = this->f_damageFactor; return true;
        case SYM_GEN_debuffsNeeded_2207: out = this->f_debuffsNeeded; return true;
        case SYM_GEN_blockGain_2631: out = this->f_blockGain; return true;
        case SYM_GEN_gemColor_995: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Gems__CorruptedCrystal::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damageBonusApplied_2628: this->f_damageBonusApplied = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_debuffsInflicted_2629: this->f_debuffsInflicted = gd::gd_coerce_int(val); return true;
        case SYM_GEN_weaponParticles_2630: this->f_weaponParticles = val; return true;
        case SYM_GEN_healthThreshold_1854: this->f_healthThreshold = val; return true;
        case SYM_GEN_damageFactor_2410: this->f_damageFactor = val; return true;
        case SYM_GEN_debuffsNeeded_2207: this->f_debuffsNeeded = val; return true;
        case SYM_GEN_blockGain_2631: this->f_blockGain = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Gems__CorruptedCrystal::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepareWeapon_982: return true;
        case SYM_GEN_onOpponentDamaged_1992: return true;
        case SYM_GEN_combatEndWeapon_988: return true;
        case SYM_GEN_prepareArmor_983: return true;
        case SYM_GEN_onOpponentDebuffsChanged_1823: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Gems__CorruptedCrystal::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepareWeapon_982: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_onOpponentDamaged_1992: out = fn_onOpponentDamaged(args, argc); return true;
        case SYM_GEN_combatEndWeapon_988: out = fn_combatEndWeapon(args, argc); return true;
        case SYM_GEN_prepareArmor_983: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_onOpponentDebuffsChanged_1823: out = fn_onOpponentDebuffsChanged(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: out = fn_onHotSwapHoverWithGemEnd(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[69]), gd::GdVal::from_str(&battle_string_literals[48])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__CorruptedCrystal::fn_onOpponentDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__healthChange = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getRelativeHealth_302, nullptr, 0), this->f_healthThreshold)))) {
        if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(this->f_damageBonusApplied)))) {
            this->f_damageBonusApplied = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
            (void)([&]() { gd::GdVal _ca[] = {this->f_damageFactor}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_389, nullptr, 0), SYM_GEN_addBonusDamageFactor_306, _ca, 1); })();
        }
    }
    else if (gd::native_scalar_truth(this->f_damageBonusApplied)) {
        this->f_damageBonusApplied = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
        (void)([&]() { gd::GdVal _ca[] = {this->f_damageFactor}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_389, nullptr, 0), SYM_GEN_reduceBonusDamageFactor_307, _ca, 1); })();
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
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[140])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToOpponentDebuffs_376, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__CorruptedCrystal::fn_onOpponentDebuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        if (gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_inline_is_type(gd_ctx, gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getOrigin_1580, nullptr, 0), &META_Gd__gd_core_items__Item))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getOrigin_1580, nullptr, 0), SYM_GEN_character_74, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
            this->f_debuffsInflicted = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_debuffsInflicted, lv_amount));
            gd::GdVal lv_activations = gd::gd_coerce_int(gd::gd_div(gd_ctx, this->f_debuffsInflicted, this->f_debuffsNeeded));
            this->f_debuffsInflicted = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_debuffsInflicted, gd::gd_coerce_int(this->f_debuffsNeeded)));
            if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(lv_activations, gd::GdVal::from_int(0LL))))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0), this->f_blockGain), lv_activations), gd::GdVal::from_bool(true), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 3); })();
                (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__CorruptedCrystal::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_addFatigueDamage_1195, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_takeFatigueDamage_1196, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__CorruptedCrystal::fn_onHotSwapHoverWithGemEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__CorruptedCrystal::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    this->f_damageFactor = gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), gd::GdVal::from_float(100.0));
    this->f_debuffsNeeded = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0);
    this->f_blockGain = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Gems__CorruptedCrystal(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Gems__CorruptedCrystal>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,573u); return object; }
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
        case SYM_GEN_fireParticles_1894: out = this->f_fireParticles; return true;
        case SYM_GEN_damFactor_1895: out = this->f_damFactor; return true;
        case SYM_GEN_heat_1896: out = this->f_heat; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::get_prop(prop, out);
}
bool Gd__gd_core_items__HoloFireLizard::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_fireParticles_1894: this->f_fireParticles = val; return true;
        case SYM_GEN_damFactor_1895: this->f_damFactor = val; return true;
        case SYM_GEN_heat_1896: this->f_heat = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__HoloFireLizard::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Card::has_own_method(m);
}
bool Gd__gd_core_items__HoloFireLizard::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__HoloFireLizard::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__HoloFireLizard::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_damFactor}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeEffectDamageFactor_1281, _ca, 1); })();
    gd::GdVal lv_dam = gd::gd_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1675), gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), this->f_chainPosition));
    gd::GdVal lv_res = ([&]() { gd::GdVal _ca[] = {lv_dam}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealEffectDamage_221, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HoloFireLizard::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Card::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_damFactor = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[141])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_heat = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1550, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__HoloFireLizard(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__HoloFireLizard>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,593u); return object; }
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
        case SYM_GEN_blockAcc_1946: out = this->f_blockAcc; return true;
        case SYM_GEN_blockForMana_1947: out = this->f_blockForMana; return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::get_prop(prop, out);
}
bool Gd__gd_core_items__MoonShield::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockAcc_1946: this->f_blockAcc = gd::gd_coerce_int(val); return true;
        case SYM_GEN_blockForMana_1947: this->f_blockForMana = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__MoonShield::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_afterBlock_1942: return true;
        case SYM_GEN_onItemGaveBlock_1948: return true;
        case SYM_GEN_canBlockDamageRes_1943: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::has_own_method(m);
}
bool Gd__gd_core_items__MoonShield::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_afterBlock_1942: out = fn_afterBlock(args, argc); return true;
        case SYM_GEN_onItemGaveBlock_1948: out = fn_onItemGaveBlock(args, argc); return true;
        case SYM_GEN_canBlockDamageRes_1943: out = fn_canBlockDamageRes(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBlock_291, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MoonShield::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t832 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t833 = (_t832.kind == gd::GdVal::Kind::Arr) ? _t832.arr : nullptr;
        uint32_t _len__t834 = _t833 ? _t833->len : 0u;
        for (uint32_t _t834 = 0; _t834 < _len__t834; ++_t834) {
            gd::GdVal lv_item = _t833->data[_t834];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(100LL), gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_giveBuffPower_303, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[142]), gd::GdVal::from_str(&battle_string_literals[143])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    this->f_blockAcc = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MoonShield::fn_afterBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), gd::native_inline_get_prop(gd_ctx, this->f_blockedDamageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drainStamina_117, _ca, 2); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MoonShield::fn_onItemGaveBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    this->f_blockAcc = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_blockAcc, lv_amount));
    gd::GdVal lv_mana = gd::gd_div(gd_ctx, this->f_blockAcc, this->f_blockForMana);
    this->f_blockAcc = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_blockAcc, this->f_blockForMana));
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(lv_mana, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_mana, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 2); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MoonShield::fn_canBlockDamageRes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_triggerOnAttacked_1530, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MoonShield::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Shield::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_blockForMana = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__MoonShield(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__MoonShield>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,613u); return object; }
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
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__RainbowGoobertRanger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__RainbowGoobertRanger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__RainbowGoobertRanger::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_267, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_213, _ca, 1); })();
    {
        gd::GdVal _t835 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t836 = (_t835.kind == gd::GdVal::Kind::Arr) ? _t835.arr : nullptr;
        uint32_t _len__t837 = _t836 ? _t836->len : 0u;
        for (uint32_t _t837 = 0; _t837 < _len__t837; ++_t837) {
            gd::GdVal lv_item = _t836->data[_t837];
            if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP6_268, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RainbowGoobertRanger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__RainbowGoobertRanger(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__RainbowGoobertRanger>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,633u); return object; }
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
        case SYM_GEN_onTriggerPotion_1849: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__StoneSkinPotion::has_own_method(m);
}
bool Gd__gd_core_items__StrongStoneSkinPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__StoneSkinPotion::call_method(gd_ctx, SYM_GEN_onTriggerPotion_1849, _ca, 1, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_int(104LL), this->f_spikes, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[130])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacksTemporary_202, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongStoneSkinPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__StoneSkinPotion::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[1])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__StrongStoneSkinPotion(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__StrongStoneSkinPotion>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,656u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__StrongStoneSkinPotion = {CLS_Gd__gd_core_items__StrongStoneSkinPotion, "StrongStoneSkinPotion", "res://gd_core_items/StrongStoneSkinPotion.gd", &META_Gd__gd_core_items__StoneSkinPotion, true, _alloc_Gd__gd_core_items__StrongStoneSkinPotion, &Gd__gd_core_items__StrongStoneSkinPotion::get_static_prop_fn, &Gd__gd_core_items__StrongStoneSkinPotion::call_static_fn};


extern "C" uint32_t gd_test_native_timer_control(const gd::NativeTimerWatch* watch) {
    return (gd::native_timer_active_ready(*watch)?1u:0u) |
        (gd::native_timer_index_ready(*watch)?2u:0u) |
        (gd::native_timer_suffix_ready(*watch)?4u:0u) |
        (gd::native_timer_control_word_compatible?8u:0u);
}
