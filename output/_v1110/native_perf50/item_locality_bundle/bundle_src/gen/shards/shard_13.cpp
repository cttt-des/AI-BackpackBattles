#include "../../native_inline_dispatch.hpp"
#include "../../native_scalar_equal.hpp"
#include "../../native_array_index.hpp"
#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core__Banana.hpp"
#include "../hdrs/Gd__gd_core__Carrot.hpp"
#include "../hdrs/Gd__gd_core__CoreGrid.hpp"
#include "../hdrs/Gd__gd_core__CursedDagger.hpp"
#include "../hdrs/Gd__gd_core__FalconBlade.hpp"
#include "../hdrs/Gd__gd_core__HeroLongsword.hpp"
#include "../hdrs/Gd__gd_core__LuckyPiggy.hpp"
#include "../hdrs/Gd__gd_core__PocketSand.hpp"
#include "../hdrs/Gd__gd_core__ShieldofValor.hpp"
#include "../hdrs/Gd__gd_core__StrongHealthPotion.hpp"
#include "../hdrs/Gd__gd_core__White_EyesBlueDragon.hpp"
#include "../hdrs/Gd__gd_core_items__Goobert.hpp"
#include "../hdrs/Gd__gd_core_items__CorruptedArmor.hpp"
#include "../hdrs/Gd__gd_core_items__EvilCap.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ArcaneBoots.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Battery.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Boomerang.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Chainsaw.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Chess__WhiteQueen.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__CupcakeDragon.hpp"
#include "../hdrs/Gd__gd_core_items__RubyWhelp.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__EnergyConversion.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ForestFriend.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__GoldArmor.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__IceArmor.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__LevelUp.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ManaCrystal.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__NoRushPlease.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PoisonGrenade.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__RainbowBadge.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Robodog.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ShinyMantle.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SpeakwithAnimals.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__StarofCourage.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ThornElemental.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__UniquelyUnique.hpp"
#include "../hdrs/Gd__gd_core_items__Fanfare.hpp"
#include "../hdrs/Gd__gd_core_items__HealingHerbs.hpp"
#include "../hdrs/Gd__gd_core_items__LuckyPiggy.hpp"
#include "../hdrs/Gd__gd_core_items__PoisonIvy.hpp"
#include "../hdrs/Gd__gd_core_items__SteelGoobert.hpp"
#include "../hdrs/Gd__gd_core_items__WalrusTusk.hpp"

namespace {
constexpr gd::GdStr battle_string_literals[] = {
    {"onOpponentDebuffsChanged", 24u, 915890936u},
    {"damfactor", 9u, 2846421882u},
    {"activated", 9u, 2866667388u},
    {"onItemActivated", 15u, 1109670618u},
    {"dur", 3u, 3509645056u},
    {"BuffTimer", 9u, 194754125u},
    {"buffEnded", 9u, 3457903416u},
    {"character_damaged", 17u, 745527748u},
    {"onDamaged", 9u, 2303747743u},
    {"dur_speed", 9u, 1036633528u},
    {"SpeedTimer", 10u, 767231377u},
    {"onSpeedTimerTimeout", 19u, 2432812723u},
    {"healtht", 7u, 1555997217u},
    {"manat", 5u, 126091098u},
    {"luck", 4u, 4145017712u},
    {"empower", 7u, 2037162760u},
    {"speed", 5u, 2072037248u},
    {"charge_emitted", 14u, 395874890u},
    {"speed2", 6u, 498752822u},
    {"stamina", 7u, 3875003702u},
    {"buffs", 5u, 2149256365u},
    {"slow", 4u, 1838498488u},
    {"heat2", 5u, 3432690547u},
    {"heat1", 5u, 3449468166u},
    {"Exclusive/CupcakeDragon.gd:11", 29u, 808790628u},
    {"remove", 6u, 3683784189u},
    {"gain", 4u, 458499838u},
    {"heat", 4u, 577319571u},
    {"heatt", 5u, 312156581u},
    {"gold", 4u, 3966162835u},
    {"regen", 5u, 16724762u},
    {"cleanse", 7u, 4032992022u},
    {"block", 5u, 3943480674u},
    {"maxhealth", 9u, 429334299u},
    {"mana", 4u, 3650585354u},
    {"skillround", 10u, 536382606u},
    {"mana1", 5u, 3296957921u},
    {"mana2", 5u, 3246625064u},
    {"cold", 4u, 3930381583u},
    {"character_lucky_changed", 23u, 2259242176u},
    {"onLuckChanged", 13u, 1398589215u},
    {"poison", 6u, 3470992305u},
    {"poison2", 7u, 848357177u},
    {"cdadvance", 9u, 1429998028u},
    {"luckt", 5u, 4061892428u},
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
    {"cdincrease", 10u, 3408620914u},
    {"character_invulnerable_start", 28u, 2327172069u},
    {"onInvuStarted", 13u, 3032367235u},
    {"dur_base", 8u, 1192387968u},
    {"dur_bonus", 9u, 1817849404u},
    {"blind", 5u, 274826164u},
    {"max", 3u, 3617776409u},
    {"Rat", 3u, 2743707096u},
    {"Squirrel", 8u, 1290664062u},
    {"Rat Chef", 8u, 572479476u},
    {"Hedgehog", 8u, 2199372732u},
    {"Squirrel Archer", 15u, 4127129685u},
    {"Hyper Hedgehog", 14u, 1195488790u},
    {"Carrot Goobert", 14u, 543467458u},
    {"Snowmaster", 10u, 2951696720u},
    {"Forest Dragon", 13u, 3303480971u},
    {"Toad", 4u, 3717358401u},
    {"Poison Goobert", 14u, 223924985u},
    {"Poison Frog", 11u, 651599933u},
    {"Ruby Chonk", 10u, 3919210698u},
    {"Frog Prince", 11u, 2193683624u},
    {"Crow", 4u, 369737854u},
    {"Ice Dragon", 10u, 146363883u},
    {"Courage Puppy", 13u, 4267069725u},
    {"Wisdom Puppy", 12u, 1992099224u},
    {"Power Puppy", 11u, 3978561720u},
    {"Armored Courage Puppy", 21u, 4189224435u},
    {"Armored Wisdom Puppy", 20u, 1090629742u},
    {"Armored Power Puppy", 19u, 4024806426u},
    {"Cheese Goobert", 14u, 805969492u},
    {"Steel Dragon", 12u, 2257125335u},
    {"Chili Goobert", 13u, 3143028190u},
    {"Fire Shelly", 11u, 1161690050u},
    {"Phoenix", 7u, 3793837196u},
    {"Phoenix2", 8u, 3095723802u},
    {"Emerald Whelp", 13u, 1388363089u},
    {"Sapphire Whelp", 14u, 3815824741u},
    {"Amethyst Whelp", 14u, 2213887872u},
    {"Obsidian Dragon", 15u, 392111003u},
    {"Cat Spirit", 10u, 1210696136u},
    {"Owl Spirit", 10u, 101434458u},
    {"Badger Spirit", 13u, 2798271123u},
    {"Cupcake Goobert", 15u, 3729492599u},
    {"Cupcake Dragon", 14u, 850212218u},
    {"Broccoli Goobert", 16u, 1024677650u},
    {"Dragon Knight", 13u, 3590476875u},
    {"Jynx Staff", 10u, 1073820372u},
    {"Robodog", 7u, 3571492197u},
    {"Toast Goobert", 13u, 2489044924u},
    {"Mecha Bat", 9u, 1506856216u},
    {"Thunder Drake", 13u, 3806765776u},
    {"Goobling", 8u, 1161906606u},
    {"Shelly", 6u, 3456212744u},
    {"Steel Goobert", 13u, 2603286472u},
    {"Blood Goobert", 13u, 2250286763u},
    {"Ruby Whelp", 10u, 2760839315u},
    {"sale", 4u, 2970508478u},
    {"spikedam", 8u, 1746925713u},
    {"spikes", 6u, 439106706u},
    {"Platin Customer Card", 20u, 1703252961u},
    {"character_spikes_changed", 24u, 3463900413u},
    {"onSpikesChanged", 15u, 3715123341u},
    {"character_poison_changed", 24u, 65736246u},
    {"onOpponentPoisonChanged", 23u, 839266911u},
};
}

void Gd__gd_core__Banana::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Food::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__Banana::meta() const { return &META_Gd__gd_core__Banana; }
gd::GdVal Gd__gd_core__Banana::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Banana::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Banana::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Food::get_prop(prop, out);
}
bool Gd__gd_core__Banana::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Banana::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Food::has_own_method(m);
}
bool Gd__gd_core__Banana::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Banana::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Banana::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_318, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Banana::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Banana(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__Banana>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,6u); return object; }
const gd::GdClassMeta META_Gd__gd_core__Banana = {CLS_Gd__gd_core__Banana, "Banana", "res://gd_core/Banana.gd", &META_Gd__gd_core__Food, false, _alloc_Gd__gd_core__Banana, &Gd__gd_core__Banana::get_static_prop_fn, &Gd__gd_core__Banana::call_static_fn};

void Gd__gd_core__Carrot::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Food::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__Carrot::meta() const { return &META_Gd__gd_core__Carrot; }
gd::GdVal Gd__gd_core__Carrot::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Carrot::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Carrot::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Food::get_prop(prop, out);
}
bool Gd__gd_core__Carrot::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Carrot::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Food::has_own_method(m);
}
bool Gd__gd_core__Carrot::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Carrot::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Carrot::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_356, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0))))) {
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Carrot::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Carrot(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__Carrot>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,19u); return object; }
const gd::GdClassMeta META_Gd__gd_core__Carrot = {CLS_Gd__gd_core__Carrot, "Carrot", "res://gd_core/Carrot.gd", &META_Gd__gd_core__Food, false, _alloc_Gd__gd_core__Carrot, &Gd__gd_core__Carrot::get_static_prop_fn, &Gd__gd_core__Carrot::call_static_fn};

void Gd__gd_core__CoreGrid::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_filledCells = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_bagCells = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_items = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_character = gd::GdVal::null();
    this->f_curHovered = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
}
const gd::GdClassMeta* Gd__gd_core__CoreGrid::meta() const { return &META_Gd__gd_core__CoreGrid; }
gd::GdVal Gd__gd_core__CoreGrid::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreGrid::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreGrid::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_filledCells_1600: out = this->f_filledCells; return true;
        case SYM_GEN_bagCells_1601: out = this->f_bagCells; return true;
        case SYM_GEN_items_1092: out = this->f_items; return true;
        case SYM_GEN_character_74: out = this->f_character; return true;
        case SYM_GEN_curHovered_1602: out = this->f_curHovered; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreGrid::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_filledCells_1600: this->f_filledCells = val; return true;
        case SYM_GEN_bagCells_1601: this->f_bagCells = val; return true;
        case SYM_GEN_items_1092: this->f_items = val; return true;
        case SYM_GEN_character_74: this->f_character = val; return true;
        case SYM_GEN_curHovered_1602: this->f_curHovered = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreGrid::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_getCellsForGlobalPositions_401: return true;
        case SYM_GEN_getItems_1603: return true;
        case SYM_GEN_getItemsAndGems_1604: return true;
        case SYM_GEN_isHovered_714: return true;
        case SYM_GEN_isCellEmpty_1605: return true;
        case SYM_GEN_getEmptyCellsInCells_1606: return true;
        case SYM_GEN_getItemInCell_1607: return true;
        case SYM_GEN_getItemsInCells_1608: return true;
        case SYM_GEN_countItemsInCells_1609: return true;
        case SYM_GEN_getBagsInCells_1610: return true;
        case SYM_GEN_getAdjacentItems_1613: return true;
        case SYM_GEN_countSocketedGems_1614: return true;
        case SYM_GEN_changeBuffPower_allItems_1615: return true;
        case SYM_GEN_changeBuffAmplification_allItems_1616: return true;
        case SYM_GEN_addItemCells_1617: return true;
        case SYM_GEN_addItem_1618: return true;
        case SYM_GEN_removeItem_1619: return true;
        case SYM_GEN_clearItemCells_1620: return true;
        case SYM_GEN_moveItem_1621: return true;
        case SYM_GEN_onItemTypeChanged_458: return true;
        case SYM_GEN_cleanUp_1622: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreGrid::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_getCellsForGlobalPositions_401: out = fn_getCellsForGlobalPositions(args, argc); return true;
        case SYM_GEN_getItems_1603: out = fn_getItems(args, argc); return true;
        case SYM_GEN_getItemsAndGems_1604: out = fn_getItemsAndGems(args, argc); return true;
        case SYM_GEN_isHovered_714: out = fn_isHovered(args, argc); return true;
        case SYM_GEN_isCellEmpty_1605: out = fn_isCellEmpty(args, argc); return true;
        case SYM_GEN_getEmptyCellsInCells_1606: out = fn_getEmptyCellsInCells(args, argc); return true;
        case SYM_GEN_getItemInCell_1607: out = fn_getItemInCell(args, argc); return true;
        case SYM_GEN_getItemsInCells_1608: out = fn_getItemsInCells(args, argc); return true;
        case SYM_GEN_countItemsInCells_1609: out = fn_countItemsInCells(args, argc); return true;
        case SYM_GEN_getBagsInCells_1610: out = fn_getBagsInCells(args, argc); return true;
        case SYM_GEN_getCellsInLine_1611: out = sf_getCellsInLine(gd_ctx, args, argc); return true;
        case SYM_GEN_getAdjacentCells_1612: out = sf_getAdjacentCells(gd_ctx, args, argc); return true;
        case SYM_GEN_getAdjacentItems_1613: out = fn_getAdjacentItems(args, argc); return true;
        case SYM_GEN_countSocketedGems_1614: out = fn_countSocketedGems(args, argc); return true;
        case SYM_GEN_changeBuffPower_allItems_1615: out = fn_changeBuffPower_allItems(args, argc); return true;
        case SYM_GEN_changeBuffAmplification_allItems_1616: out = fn_changeBuffAmplification_allItems(args, argc); return true;
        case SYM_GEN_addItemCells_1617: out = fn_addItemCells(args, argc); return true;
        case SYM_GEN_addItem_1618: out = fn_addItem(args, argc); return true;
        case SYM_GEN_removeItem_1619: out = fn_removeItem(args, argc); return true;
        case SYM_GEN_clearItemCells_1620: out = fn_clearItemCells(args, argc); return true;
        case SYM_GEN_moveItem_1621: out = fn_moveItem(args, argc); return true;
        case SYM_GEN_onItemTypeChanged_458: out = fn_onItemTypeChanged(args, argc); return true;
        case SYM_GEN_cleanUp_1622: out = fn_cleanUp(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreGrid::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getCellsInLine_1611: out = sf_getCellsInLine(gd_ctx, args, argc); return true;
        case SYM_GEN_getAdjacentCells_1612: out = sf_getAdjacentCells(gd_ctx, args, argc); return true;
        default: break;
    }
    return false;
}
gd::GdVal Gd__gd_core__CoreGrid::fn__init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__character = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    this->f_character = lv__character;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_getCellsForGlobalPositions(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_points = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return lv_points;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_getItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_items;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_getItemsAndGems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_itemsAndGems = gd::native_inline_call(gd_ctx, this->f_items, gd::SYM_duplicate, nullptr, 0);
    {
        gd::GdVal _t1701 = gd::gd_iter_seq(gd_ctx.arena, this->f_items);
        gd::GdArr* _t1702 = (_t1701.kind == gd::GdVal::Kind::Arr) ? _t1701.arr : nullptr;
        uint32_t _len__t1703 = _t1702 ? _t1702->len : 0u;
        for (uint32_t _t1703 = 0; _t1703 < _len__t1703; ++_t1703) {
            gd::GdVal lv_item = _t1702->data[_t1703];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getGemsNoNull_497, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_itemsAndGems, gd::SYM_append_array, _ca, 1); })();
        }
    }
    return lv_itemsAndGems;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_isHovered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_cell = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::gd_in(lv_cell, this->f_curHovered);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_isCellEmpty(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_cell = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::gd_in(lv_cell, this->f_bagCells)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_cell, this->f_filledCells))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_getEmptyCellsInCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_cells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_num = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t1704 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t1705 = (_t1704.kind == gd::GdVal::Kind::Arr) ? _t1704.arr : nullptr;
        uint32_t _len__t1706 = _t1705 ? _t1705->len : 0u;
        for (uint32_t _t1706 = 0; _t1706 < _len__t1706; ++_t1706) {
            gd::GdVal lv_cell = _t1705->data[_t1706];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCellEmpty_1605, _ca, 1); })())) {
                lv_num = gd::gd_add(gd_ctx, lv_num, gd::GdVal::from_int(1LL));
            }
        }
    }
    return lv_num;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_getItemInCell(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_cell = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_cell, gd::GdVal::null()}; return gd::native_inline_call(gd_ctx, this->f_filledCells, gd::SYM_get, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_getItemsInCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_cells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_itemsInCells = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1707 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t1708 = (_t1707.kind == gd::GdVal::Kind::Arr) ? _t1707.arr : nullptr;
        uint32_t _len__t1709 = _t1708 ? _t1708->len : 0u;
        for (uint32_t _t1709 = 0; _t1709 < _len__t1709; ++_t1709) {
            gd::GdVal lv_cell = _t1708->data[_t1709];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::native_inline_call(gd_ctx, this->f_filledCells, gd::SYM_has, _ca, 1); })())) {
                gd::GdVal lv_item = gd::native_array_index(gd_ctx, this->f_filledCells, lv_cell);
                if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_item, lv_itemsInCells)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_placed_6))) : gd::GdVal::from_bool(false)))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, lv_itemsInCells, gd::SYM_push_back, _ca, 1); })();
                }
            }
        }
    }
    return lv_itemsInCells;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_countItemsInCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_cells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_itemCounter = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t1710 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t1711 = (_t1710.kind == gd::GdVal::Kind::Arr) ? _t1710.arr : nullptr;
        uint32_t _len__t1712 = _t1711 ? _t1711->len : 0u;
        for (uint32_t _t1712 = 0; _t1712 < _len__t1712; ++_t1712) {
            gd::GdVal lv_cell = _t1711->data[_t1712];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::native_inline_call(gd_ctx, this->f_filledCells, gd::SYM_has, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_itemCounter, gd::native_array_index(gd_ctx, this->f_filledCells, lv_cell)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictAdd_1789, _ca, 2); })();
            }
        }
    }
    return lv_itemCounter;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_getBagsInCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_cells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_bags = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1713 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t1714 = (_t1713.kind == gd::GdVal::Kind::Arr) ? _t1713.arr : nullptr;
        uint32_t _len__t1715 = _t1714 ? _t1714->len : 0u;
        for (uint32_t _t1715 = 0; _t1715 < _len__t1715; ++_t1715) {
            gd::GdVal lv_cell = _t1714->data[_t1715];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::native_inline_call(gd_ctx, this->f_bagCells, gd::SYM_has, _ca, 1); })())) {
                gd::GdVal lv_bag = gd::native_array_index(gd_ctx, this->f_bagCells, lv_cell);
                if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_bag, lv_bags))))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_bag}; return gd::native_inline_call(gd_ctx, lv_bags, gd::SYM_push_back, _ca, 1); })();
                }
            }
        }
    }
    return lv_bags;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::sf_getCellsInLine(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_cells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_direction = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_distance = (_argc > 2) ? _args[2] : (gd::GdVal::from_int(7LL));
    gd::GdVal lv_lineCells = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1716 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t1717 = (_t1716.kind == gd::GdVal::Kind::Arr) ? _t1716.arr : nullptr;
        uint32_t _len__t1718 = _t1717 ? _t1717->len : 0u;
        for (uint32_t _t1718 = 0; _t1718 < _len__t1718; ++_t1718) {
            gd::GdVal lv_cell = _t1717->data[_t1718];
            {
                gd::GdVal _t1719 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::gd_add(gd_ctx, lv_distance, gd::GdVal::from_int(1LL))}; return gd::gd_range(gd_ctx.arena, _ca, 2); })());
                gd::GdArr* _t1720 = (_t1719.kind == gd::GdVal::Kind::Arr) ? _t1719.arr : nullptr;
                uint32_t _len__t1721 = _t1720 ? _t1720->len : 0u;
                for (uint32_t _t1721 = 0; _t1721 < _len__t1721; ++_t1721) {
                    gd::GdVal lv_offset = _t1720->data[_t1721];
                    gd::GdVal lv_neighbor = gd::gd_add(gd_ctx, lv_cell, gd::gd_mul(lv_direction, lv_offset));
                    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_neighbor, lv_cells)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_neighbor, lv_lineCells))))) : gd::GdVal::from_bool(false)))) {
                        (void)([&]() { gd::GdVal _ca[] = {lv_neighbor}; return gd::native_inline_call(gd_ctx, lv_lineCells, gd::SYM_push_back, _ca, 1); })();
                    }
                }
            }
        }
    }
    return lv_lineCells;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::sf_getAdjacentCells(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_cells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_adjacentCells = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1722 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t1723 = (_t1722.kind == gd::GdVal::Kind::Arr) ? _t1722.arr : nullptr;
        uint32_t _len__t1724 = _t1723 ? _t1723->len : 0u;
        for (uint32_t _t1724 = 0; _t1724 < _len__t1724; ++_t1724) {
            gd::GdVal lv_cell = _t1723->data[_t1724];
            {
                gd::GdVal _t1725 = gd::gd_iter_seq(gd_ctx.arena, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2(1.0, 0.0), gd::GdVal::from_vec2(-1.0, 0.0), gd::GdVal::from_vec2(0.0, -1.0), gd::GdVal::from_vec2(0.0, 1.0)})));
                gd::GdArr* _t1726 = (_t1725.kind == gd::GdVal::Kind::Arr) ? _t1725.arr : nullptr;
                uint32_t _len__t1727 = _t1726 ? _t1726->len : 0u;
                for (uint32_t _t1727 = 0; _t1727 < _len__t1727; ++_t1727) {
                    gd::GdVal lv_offset = _t1726->data[_t1727];
                    gd::GdVal lv_neighbor = gd::gd_add(gd_ctx, lv_cell, lv_offset);
                    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_neighbor, lv_cells)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_neighbor, lv_adjacentCells))))) : gd::GdVal::from_bool(false)))) {
                        (void)([&]() { gd::GdVal _ca[] = {lv_neighbor}; return gd::native_inline_call(gd_ctx, lv_adjacentCells, gd::SYM_push_back, _ca, 1); })();
                    }
                }
            }
        }
    }
    return lv_adjacentCells;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_getAdjacentItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, lv_item, SYM_GEN_occupiedCells_52)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreGrid::call_static_fn(gd_ctx, SYM_GEN_getAdjacentCells_1612, _ca, 1, _out); return _out; })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInCells_1608, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_countSocketedGems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numGems = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t1728 = gd::gd_iter_seq(gd_ctx.arena, this->f_items);
        gd::GdArr* _t1729 = (_t1728.kind == gd::GdVal::Kind::Arr) ? _t1728.arr : nullptr;
        uint32_t _len__t1730 = _t1729 ? _t1729->len : 0u;
        for (uint32_t _t1730 = 0; _t1730 < _len__t1730; ++_t1730) {
            gd::GdVal lv_item = _t1729->data[_t1730];
            lv_numGems = gd::gd_add(gd_ctx, lv_numGems, gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getGemsNoNull_497, nullptr, 0), gd::SYM_size, nullptr, 0));
        }
    }
    return lv_numGems;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_changeBuffPower_allItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    {
        gd::GdVal _t1731 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsAndGems_1604, nullptr, 0));
        gd::GdArr* _t1732 = (_t1731.kind == gd::GdVal::Kind::Arr) ? _t1731.arr : nullptr;
        uint32_t _len__t1733 = _t1732 ? _t1732->len : 0u;
        for (uint32_t _t1733 = 0; _t1733 < _len__t1733; ++_t1733) {
            gd::GdVal lv_item = _t1732->data[_t1733];
            (void)([&]() { gd::GdVal _ca[] = {lv_buffType, lv_amount}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_giveBuffPower_303, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_changeBuffAmplification_allItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    {
        gd::GdVal _t1734 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsAndGems_1604, nullptr, 0));
        gd::GdArr* _t1735 = (_t1734.kind == gd::GdVal::Kind::Arr) ? _t1734.arr : nullptr;
        uint32_t _len__t1736 = _t1735 ? _t1735->len : 0u;
        for (uint32_t _t1736 = 0; _t1736 < _len__t1736; ++_t1736) {
            gd::GdVal lv_item = _t1735->data[_t1736];
            (void)([&]() { gd::GdVal _ca[] = {lv_buffType, lv_amount}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_196, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_addItemCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isBag_83, nullptr, 0))) {
        {
            gd::GdVal _t1737 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
            gd::GdArr* _t1738 = (_t1737.kind == gd::GdVal::Kind::Arr) ? _t1737.arr : nullptr;
            uint32_t _len__t1739 = _t1738 ? _t1738->len : 0u;
            for (uint32_t _t1739 = 0; _t1739 < _len__t1739; ++_t1739) {
                gd::GdVal lv_cell = _t1738->data[_t1739];
                { gd::GdVal _t1740 = this->f_bagCells; gd::GdVal _t1741 = lv_cell; gd::native_array_set_index(gd_ctx, _t1740, _t1741, lv_item); }
            }
        }
    }
    else {
        {
            gd::GdVal _t1742 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
            gd::GdArr* _t1743 = (_t1742.kind == gd::GdVal::Kind::Arr) ? _t1742.arr : nullptr;
            uint32_t _len__t1744 = _t1743 ? _t1743->len : 0u;
            for (uint32_t _t1744 = 0; _t1744 < _len__t1744; ++_t1744) {
                gd::GdVal lv_cell = _t1743->data[_t1744];
                { gd::GdVal _t1745 = this->f_filledCells; gd::GdVal _t1746 = lv_cell; gd::native_array_set_index(gd_ctx, _t1745, _t1746, lv_item); }
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_addItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_placedByPlayer = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    lv_placedByPlayer = gd::gd_coerce_bool(lv_placedByPlayer);
    (void)([&]() { gd::GdVal _ca[] = {lv_item, lv_cells}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addItemCells_1617, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, this->f_items, gd::SYM_push_back, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_cells, lv_placedByPlayer}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addToInventory_120, _ca, 3); })();
    {
        gd::GdVal _t1747 = gd::gd_iter_seq(gd_ctx.arena, this->f_items);
        gd::GdArr* _t1748 = (_t1747.kind == gd::GdVal::Kind::Arr) ? _t1747.arr : nullptr;
        uint32_t _len__t1749 = _t1748 ? _t1748->len : 0u;
        for (uint32_t _t1749 = 0; _t1749 < _len__t1749; ++_t1749) {
            gd::GdVal lv_other = _t1748->data[_t1749];
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, lv_other, SYM_GEN_onItemAdded_437, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_removeItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_isBag = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    lv_isBag = gd::gd_coerce_bool(lv_isBag);
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearItemCells_1620, _ca, 1); })();
    gd::GdVal lv_idx = ([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, this->f_items, gd::SYM_find, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_idx, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_idx}; return gd::native_inline_call(gd_ctx, this->f_items, gd::SYM_remove, _ca, 1); })();
    }
    {
        gd::GdVal _t1750 = gd::gd_iter_seq(gd_ctx.arena, this->f_items);
        gd::GdArr* _t1751 = (_t1750.kind == gd::GdVal::Kind::Arr) ? _t1750.arr : nullptr;
        uint32_t _len__t1752 = _t1751 ? _t1751->len : 0u;
        for (uint32_t _t1752 = 0; _t1752 < _len__t1752; ++_t1752) {
            gd::GdVal lv_other = _t1751->data[_t1752];
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, lv_other, SYM_GEN_onItemRemoved_438, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_clearItemCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1753 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, lv_item, SYM_GEN_occupiedCells_52));
        gd::GdArr* _t1754 = (_t1753.kind == gd::GdVal::Kind::Arr) ? _t1753.arr : nullptr;
        uint32_t _len__t1755 = _t1754 ? _t1754->len : 0u;
        for (uint32_t _t1755 = 0; _t1755 < _len__t1755; ++_t1755) {
            gd::GdVal lv_cell = _t1754->data[_t1755];
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isBag_83, nullptr, 0))) {
                if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(([&]() { gd::GdVal _ca[] = {lv_cell, gd::GdVal::null()}; return gd::native_inline_call(gd_ctx, this->f_bagCells, gd::SYM_get, _ca, 2); })(), lv_item)))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::native_inline_call(gd_ctx, this->f_bagCells, gd::SYM_erase, _ca, 1); })();
                }
            }
            else {
                if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(([&]() { gd::GdVal _ca[] = {lv_cell, gd::GdVal::null()}; return gd::native_inline_call(gd_ctx, this->f_filledCells, gd::SYM_get, _ca, 2); })(), lv_item)))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::native_inline_call(gd_ctx, this->f_filledCells, gd::SYM_erase, _ca, 1); })();
                }
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_moveItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_newCells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearItemCells_1620, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_item, lv_newCells}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addItemCells_1617, _ca, 2); })();
    gd::set_prop(gd_ctx, lv_item, SYM_GEN_occupiedCells_52, lv_newCells);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_onItemTypeChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1756 = gd::gd_iter_seq(gd_ctx.arena, this->f_items);
        gd::GdArr* _t1757 = (_t1756.kind == gd::GdVal::Kind::Arr) ? _t1756.arr : nullptr;
        uint32_t _len__t1758 = _t1757 ? _t1757->len : 0u;
        for (uint32_t _t1758 = 0; _t1758 < _len__t1758; ++_t1758) {
            gd::GdVal lv_other = _t1757->data[_t1758];
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, lv_other, SYM_GEN_onItemTypeChanged_458, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_cleanUp(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_filledCells, gd::SYM_clear, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, this->f_bagCells, gd::SYM_clear, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, this->f_items, gd::SYM_clear, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, this->f_curHovered, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreGrid(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__CoreGrid>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,33u); return object; }
const gd::GdClassMeta META_Gd__gd_core__CoreGrid = {CLS_Gd__gd_core__CoreGrid, "CoreGrid", "res://gd_core/CoreGrid.gd", nullptr, false, _alloc_Gd__gd_core__CoreGrid, &Gd__gd_core__CoreGrid::get_static_prop_fn, &Gd__gd_core__CoreGrid::call_static_fn};

void Gd__gd_core__CursedDagger::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Dagger::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__CursedDagger::meta() const { return &META_Gd__gd_core__CursedDagger; }
gd::GdVal Gd__gd_core__CursedDagger::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Dagger::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__CursedDagger::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CursedDagger::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Dagger::get_prop(prop, out);
}
bool Gd__gd_core__CursedDagger::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Dagger::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__CursedDagger::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_onOpponentDebuffsChanged_1823: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Dagger::has_own_method(m);
}
bool Gd__gd_core__CursedDagger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onOpponentDebuffsChanged_1823: out = fn_onOpponentDebuffsChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Dagger::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__CursedDagger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Dagger::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__CursedDagger::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canDamage_89, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CursedDagger::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[0])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToOpponentDebuffs_376, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CursedDagger::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictRandomDebuffs_357, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CursedDagger::fn_onOpponentDebuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_extraCritChance = gd::gd_mul(lv_amount, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0));
    gd::GdVal lv_extraAccuracy = gd::gd_mul(lv_amount, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    (void)([&]() { gd::GdVal _ca[] = {lv_extraCritChance}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addCritChancePercent_179, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_extraAccuracy}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addAccuracy_177, _ca, 1); })();
    {
        gd::GdVal _t1759 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1760 = (_t1759.kind == gd::GdVal::Kind::Arr) ? _t1759.arr : nullptr;
        uint32_t _len__t1761 = _t1760 ? _t1760->len : 0u;
        for (uint32_t _t1761 = 0; _t1761 < _len__t1761; ++_t1761) {
            gd::GdVal lv_item = _t1760->data[_t1761];
            (void)([&]() { gd::GdVal _ca[] = {lv_extraCritChance}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addCritChancePercent_179, _ca, 1); })();
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isWeapon_82, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_extraAccuracy}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addAccuracy_177, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CursedDagger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Dagger::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CursedDagger(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__CursedDagger>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,47u); return object; }
const gd::GdClassMeta META_Gd__gd_core__CursedDagger = {CLS_Gd__gd_core__CursedDagger, "CursedDagger", "res://gd_core/CursedDagger.gd", &META_Gd__gd_core__Dagger, false, _alloc_Gd__gd_core__CursedDagger, &Gd__gd_core__CursedDagger::get_static_prop_fn, &Gd__gd_core__CursedDagger::call_static_fn};

void Gd__gd_core__FalconBlade::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__FalconBlade::meta() const { return &META_Gd__gd_core__FalconBlade; }
gd::GdVal Gd__gd_core__FalconBlade::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__FalconBlade::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__FalconBlade::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__FalconBlade::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__FalconBlade::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_getCraftingOffset_850: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__FalconBlade::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getCraftingOffset_850: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__FalconBlade::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__FalconBlade::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__FalconBlade::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1762 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1763 = (_t1762.kind == gd::GdVal::Kind::Arr) ? _t1762.arr : nullptr;
        uint32_t _len__t1764 = _t1763 ? _t1763->len : 0u;
        for (uint32_t _t1764 = 0; _t1764 < _len__t1764; ++_t1764) {
            gd::GdVal lv_item = _t1763->data[_t1764];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::GdVal::from_int(100LL))}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__FalconBlade::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_res = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_220, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res, gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 2); })();
        gd::GdVal lv_res2 = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_220, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res2, gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 2); })();
        gd::GdVal lv_hits = gd::GdVal::from_int(0LL);
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_res, SYM_GEN_hasHit_1523, nullptr, 0))) {
            lv_hits = gd::gd_add(gd_ctx, lv_hits, gd::GdVal::from_int(1LL));
        }
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_res2, SYM_GEN_hasHit_1523, nullptr, 0))) {
            lv_hits = gd::gd_add(gd_ctx, lv_hits, gd::GdVal::from_int(1LL));
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(30.0)), gd::GdVal::from_float(30.0)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_bare_randf_range_1743, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(100.0)), gd::GdVal::from_float(100.0)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_bare_randf_range_1743, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(5.0)), gd::GdVal::from_float(5.0)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_bare_randf_range_1743, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__FalconBlade::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1765 = lv_forDirection;
        if (gd::native_scalar_eq(_t1765, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
        else if (gd::native_scalar_eq(_t1765, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
        else if (gd::native_scalar_eq(_t1765, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::native_scalar_eq(_t1765, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__FalconBlade::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__FalconBlade(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__FalconBlade>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,61u); return object; }
const gd::GdClassMeta META_Gd__gd_core__FalconBlade = {CLS_Gd__gd_core__FalconBlade, "FalconBlade", "res://gd_core/FalconBlade.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__FalconBlade, &Gd__gd_core__FalconBlade::get_static_prop_fn, &Gd__gd_core__FalconBlade::call_static_fn};

void Gd__gd_core__HeroLongsword::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__HeroLongsword::meta() const { return &META_Gd__gd_core__HeroLongsword; }
gd::GdVal Gd__gd_core__HeroLongsword::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__HeroLongsword::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__HeroLongsword::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__HeroLongsword::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__HeroLongsword::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_getCraftingOffset_850: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__HeroLongsword::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_getCraftingOffset_850: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__HeroLongsword::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__HeroLongsword::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeroLongsword::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1766 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1767 = (_t1766.kind == gd::GdVal::Kind::Arr) ? _t1766.arr : nullptr;
        uint32_t _len__t1768 = _t1767 ? _t1767->len : 0u;
        for (uint32_t _t1768 = 0; _t1768 < _len__t1768; ++_t1768) {
            gd::GdVal lv_item = _t1767->data[_t1768];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeroLongsword::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1769 = lv_forDirection;
        if (gd::native_scalar_eq(_t1769, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
        else if (gd::native_scalar_eq(_t1769, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
        else if (gd::native_scalar_eq(_t1769, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::native_scalar_eq(_t1769, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeroLongsword::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__HeroLongsword(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__HeroLongsword>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,79u); return object; }
const gd::GdClassMeta META_Gd__gd_core__HeroLongsword = {CLS_Gd__gd_core__HeroLongsword, "HeroLongsword", "res://gd_core/HeroLongsword.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__HeroLongsword, &Gd__gd_core__HeroLongsword::get_static_prop_fn, &Gd__gd_core__HeroLongsword::call_static_fn};

void Gd__gd_core__LuckyPiggy::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Piggybank::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__LuckyPiggy::meta() const { return &META_Gd__gd_core__LuckyPiggy; }
gd::GdVal Gd__gd_core__LuckyPiggy::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Piggybank::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__LuckyPiggy::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__LuckyPiggy::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Piggybank::get_prop(prop, out);
}
bool Gd__gd_core__LuckyPiggy::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Piggybank::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__LuckyPiggy::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_explodeRandomly_1921: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Piggybank::has_own_method(m);
}
bool Gd__gd_core__LuckyPiggy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_explodeRandomly_1921: out = fn_explodeRandomly(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Piggybank::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__LuckyPiggy::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Piggybank::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__LuckyPiggy::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canModifyChance_293, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyPiggy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1770 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1771 = (_t1770.kind == gd::GdVal::Kind::Arr) ? _t1770.arr : nullptr;
        uint32_t _len__t1772 = _t1771 ? _t1771->len : 0u;
        for (uint32_t _t1772 = 0; _t1772 < _len__t1772; ++_t1772) {
            gd::GdVal lv_item = _t1771->data[_t1772];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusChance_175, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyPiggy::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyPiggy::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::GdVal::from_int(1000LL), gd::GdVal::from_int(5LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyPiggy::fn_explodeRandomly(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyPiggy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Piggybank::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__LuckyPiggy(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__LuckyPiggy>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,94u); return object; }
const gd::GdClassMeta META_Gd__gd_core__LuckyPiggy = {CLS_Gd__gd_core__LuckyPiggy, "LuckyPiggy", "res://gd_core/LuckyPiggy.gd", &META_Gd__gd_core_items__Piggybank, false, _alloc_Gd__gd_core__LuckyPiggy, &Gd__gd_core__LuckyPiggy::get_static_prop_fn, &Gd__gd_core__LuckyPiggy::call_static_fn};

void Gd__gd_core__PocketSand::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__PocketSand::meta() const { return &META_Gd__gd_core__PocketSand; }
gd::GdVal Gd__gd_core__PocketSand::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__PocketSand::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__PocketSand::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__PocketSand::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__PocketSand::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__PocketSand::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__PocketSand::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__PocketSand::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_213, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_381, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PocketSand::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__PocketSand(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__PocketSand>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,109u); return object; }
const gd::GdClassMeta META_Gd__gd_core__PocketSand = {CLS_Gd__gd_core__PocketSand, "PocketSand", "res://gd_core/PocketSand.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__PocketSand, &Gd__gd_core__PocketSand::get_static_prop_fn, &Gd__gd_core__PocketSand::call_static_fn};

void Gd__gd_core__ShieldofValor::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Shield::init_fields(gd_ctx);
    this->f_blockFactor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__ShieldofValor::meta() const { return &META_Gd__gd_core__ShieldofValor; }
gd::GdVal Gd__gd_core__ShieldofValor::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Shield::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__ShieldofValor::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__ShieldofValor::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_blockFactor_1977: out = this->f_blockFactor; return true;
        default: break;
    }
    return Gd__gd_core__Shield::get_prop(prop, out);
}
bool Gd__gd_core__ShieldofValor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockFactor_1977: this->f_blockFactor = val; return true;
        default: break;
    }
    return Gd__gd_core__Shield::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__ShieldofValor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_afterBlock_1942: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Shield::has_own_method(m);
}
bool Gd__gd_core__ShieldofValor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_afterBlock_1942: out = fn_afterBlock(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Shield::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__ShieldofValor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Shield::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__ShieldofValor::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBlock_291, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ShieldofValor::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1773 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1774 = (_t1773.kind == gd::GdVal::Kind::Arr) ? _t1773.arr : nullptr;
        uint32_t _len__t1775 = _t1774 ? _t1774->len : 0u;
        for (uint32_t _t1775 = 0; _t1775 < _len__t1775; ++_t1775) {
            gd::GdVal lv_item = _t1774->data[_t1775];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(100LL), this->f_blockFactor}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_giveBuffPower_303, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ShieldofValor::fn_afterBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), gd::get_prop(gd_ctx, this->f_blockedDamageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drainStamina_117, _ca, 2); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ShieldofValor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Shield::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_blockFactor = gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__ShieldofValor(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__ShieldofValor>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,128u); return object; }
const gd::GdClassMeta META_Gd__gd_core__ShieldofValor = {CLS_Gd__gd_core__ShieldofValor, "ShieldofValor", "res://gd_core/ShieldofValor.gd", &META_Gd__gd_core__Shield, false, _alloc_Gd__gd_core__ShieldofValor, &Gd__gd_core__ShieldofValor::get_static_prop_fn, &Gd__gd_core__ShieldofValor::call_static_fn};

void Gd__gd_core__StrongHealthPotion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__HealthPotion::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__StrongHealthPotion::meta() const { return &META_Gd__gd_core__StrongHealthPotion; }
gd::GdVal Gd__gd_core__StrongHealthPotion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__HealthPotion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__StrongHealthPotion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__StrongHealthPotion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__HealthPotion::get_prop(prop, out);
}
bool Gd__gd_core__StrongHealthPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__HealthPotion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__StrongHealthPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__HealthPotion::has_own_method(m);
}
bool Gd__gd_core__StrongHealthPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: out = fn_onTriggerPotion(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__HealthPotion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__StrongHealthPotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__HealthPotion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__StrongHealthPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__HealthPotion::call_method(gd_ctx, SYM_GEN_onTriggerPotion_1849, _ca, 1, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StrongHealthPotion::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::GdVal::from_int(1000LL), gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StrongHealthPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__HealthPotion::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__StrongHealthPotion(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__StrongHealthPotion>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,141u); return object; }
const gd::GdClassMeta META_Gd__gd_core__StrongHealthPotion = {CLS_Gd__gd_core__StrongHealthPotion, "StrongHealthPotion", "res://gd_core/StrongHealthPotion.gd", &META_Gd__gd_core_items__HealthPotion, false, _alloc_Gd__gd_core__StrongHealthPotion, &Gd__gd_core__StrongHealthPotion::get_static_prop_fn, &Gd__gd_core__StrongHealthPotion::call_static_fn};

void Gd__gd_core__White_EyesBlueDragon::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Card::init_fields(gd_ctx);
    this->f_snowflakes = gd::GdVal::null();
    this->f_damReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__White_EyesBlueDragon::meta() const { return &META_Gd__gd_core__White_EyesBlueDragon; }
gd::GdVal Gd__gd_core__White_EyesBlueDragon::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Card::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__White_EyesBlueDragon::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__White_EyesBlueDragon::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_snowflakes_2003: out = this->f_snowflakes; return true;
        case SYM_GEN_damReduction_1873: out = this->f_damReduction; return true;
        default: break;
    }
    return Gd__gd_core__Card::get_prop(prop, out);
}
bool Gd__gd_core__White_EyesBlueDragon::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_snowflakes_2003: this->f_snowflakes = val; return true;
        case SYM_GEN_damReduction_1873: this->f_damReduction = val; return true;
        default: break;
    }
    return Gd__gd_core__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__White_EyesBlueDragon::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Card::has_own_method(m);
}
bool Gd__gd_core__White_EyesBlueDragon::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__White_EyesBlueDragon::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__White_EyesBlueDragon::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), this->f_chainPosition))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_351, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeEffectDamageFactor_1281, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__White_EyesBlueDragon::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Card::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_damReduction = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[1])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__White_EyesBlueDragon(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__White_EyesBlueDragon>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,156u); return object; }
const gd::GdClassMeta META_Gd__gd_core__White_EyesBlueDragon = {CLS_Gd__gd_core__White_EyesBlueDragon, "White-EyesBlueDragon", "res://gd_core/White-EyesBlueDragon.gd", &META_Gd__gd_core__Card, false, _alloc_Gd__gd_core__White_EyesBlueDragon, &Gd__gd_core__White_EyesBlueDragon::get_static_prop_fn, &Gd__gd_core__White_EyesBlueDragon::call_static_fn};

void Gd__gd_core_items__Goobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_activations = gd::GdVal::from_int(0);
    this->f_goobertAnimation = gd::GdVal::null();
    this->f_activationsToTrigger = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Goobert::meta() const { return &META_Gd__gd_core_items__Goobert; }
gd::GdVal Gd__gd_core_items__Goobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Goobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Goobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activations_935: out = this->f_activations; return true;
        case SYM_GEN_goobertAnimation_936: out = this->f_goobertAnimation; return true;
        case SYM_GEN_activationsToTrigger_937: out = this->f_activationsToTrigger; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Goobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activations_935: this->f_activations = gd::gd_coerce_int(val); return true;
        case SYM_GEN_goobertAnimation_936: this->f_goobertAnimation = val; return true;
        case SYM_GEN_activationsToTrigger_937: this->f_activationsToTrigger = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Goobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_logCooldown_759: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_prepare_122: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onItemActivated_938: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Goobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_logCooldown_759: out = fn_logCooldown(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_prepare_122: out = fn_prepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onItemActivated_938: out = fn_onItemActivated(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Goobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Goobert::fn_logCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Goobert::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canActivate_91, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Goobert::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_activations = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_iterationCooldown = gd::gd_coerce_float(this->f_activationsToTrigger);
    this->f_triggerTime = gd::gd_coerce_float(this->f_iterationCooldown);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(9LL)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    {
        gd::GdVal _t1776 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1777 = (_t1776.kind == gd::GdVal::Kind::Arr) ? _t1776.arr : nullptr;
        uint32_t _len__t1778 = _t1777 ? _t1777->len : 0u;
        for (uint32_t _t1778 = 0; _t1778 < _len__t1778; ++_t1778) {
            gd::GdVal lv_item = _t1777->data[_t1778];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[2]), gd::GdVal::from_str(&battle_string_literals[3])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_prepare_122, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Goobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Goobert::fn_onItemActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_activations = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_activations, gd::GdVal::from_int(1LL)));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_activations, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0))))) {
        this->f_activations = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCooldownEffect_144, nullptr, 0);
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_doubleActivationChance, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_doubleActivationChance}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_flip_1735, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCooldownEffect_144, nullptr, 0);
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, this->f_activations, this->f_activationsToTrigger), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 2); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, this->f_activations, this->f_activationsToTrigger), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 2); })();
    }
    this->f_triggerTime = gd::gd_coerce_float(gd::gd_sub(this->f_activationsToTrigger, this->f_activations));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(9LL), gd::GdVal::null(), gd::GdVal::from_bool(false), lv_event}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Goobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_activationsToTrigger = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Goobert(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Goobert>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,576u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Goobert = {CLS_Gd__gd_core_items__Goobert, "Goobert", "res://gd_core_items/Goobert.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Goobert, &Gd__gd_core_items__Goobert::get_static_prop_fn, &Gd__gd_core_items__Goobert::call_static_fn};

void Gd__gd_core_items__CorruptedArmor::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_movedDebuffs = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__CorruptedArmor::meta() const { return &META_Gd__gd_core_items__CorruptedArmor; }
gd::GdVal Gd__gd_core_items__CorruptedArmor::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__CorruptedArmor::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__CorruptedArmor::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_movedDebuffs_1812: out = this->f_movedDebuffs; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__CorruptedArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_movedDebuffs_1812: this->f_movedDebuffs = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__CorruptedArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_reactToItemTypeChange_457: return true;
        case SYM_GEN_onAffectedItemAdded_435: return true;
        case SYM_GEN_onAffectedItemRemoved_436: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__CorruptedArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_reactToItemTypeChange_457: out = fn_reactToItemTypeChange(args, argc); return true;
        case SYM_GEN_onAffectedItemAdded_435: out = fn_onAffectedItemAdded(args, argc); return true;
        case SYM_GEN_onAffectedItemRemoved_436: out = fn_onAffectedItemRemoved(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__CorruptedArmor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__CorruptedArmor::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(25LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CorruptedArmor::fn_reactToItemTypeChange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::gd_in(lv_item, gd::native_array_index(gd_ctx, this->f_currentAffectedItems, gd::GdVal::from_int(0LL))))) {
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(25LL), gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasDynamicType_241, _ca, 2); })())) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, this->f_currentAffectedItems, gd::GdVal::from_int(0LL)), gd::SYM_erase, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemRemoved_436, _ca, 2); })();
            return gd::GdVal::from_bool(false);
        }
    }
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CorruptedArmor::fn_onAffectedItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    if (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(25LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(25LL), gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addDynamicType_242, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CorruptedArmor::fn_onAffectedItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(25LL), gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_removeDynamicType_243, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CorruptedArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    gd::GdVal lv_debuffProtectionChance = gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0));
    (void)([&]() { gd::GdVal _ca[] = {lv_debuffProtectionChance}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeDebuffProtectionChance_1287, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CorruptedArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_cleansedDebuffs = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1391, nullptr, 0), this->f_movedDebuffs, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_pickRandomStacks_358, _ca, 3); })();
    {
        gd::GdVal _t1779 = gd::gd_iter_seq(gd_ctx.arena, lv_cleansedDebuffs);
        gd::GdArr* _t1780 = (_t1779.kind == gd::GdVal::Kind::Arr) ? _t1779.arr : nullptr;
        uint32_t _len__t1781 = _t1780 ? _t1780->len : 0u;
        for (uint32_t _t1781 = 0; _t1781 < _len__t1781; ++_t1781) {
            gd::GdVal lv_debuff = _t1780->data[_t1781];
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_debuff, gd::native_array_index(gd_ctx, lv_cleansedDebuffs, lv_debuff), gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_loseStacks_1032, _ca, 3); })();
            if (gd::gd_truth(lv_event)) {
                gd::GdVal lv_actuallyCleansed = gd::gd_neg(gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getAmount_1576, nullptr, 0));
                (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), lv_debuff, lv_actuallyCleansed, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
            }
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CorruptedArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_movedDebuffs = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__CorruptedArmor(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__CorruptedArmor>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,184u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__CorruptedArmor = {CLS_Gd__gd_core_items__CorruptedArmor, "CorruptedArmor", "res://gd_core_items/CorruptedArmor.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__CorruptedArmor, &Gd__gd_core_items__CorruptedArmor::get_static_prop_fn, &Gd__gd_core_items__CorruptedArmor::call_static_fn};

void Gd__gd_core_items__EvilCap::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_nullifyApplied = gd::GdVal::from_bool(false);
    this->f_buffsActive = gd::GdVal::from_int(0LL);
    this->f_buffTimer = gd::GdVal::null();
    this->f_activationParticles = gd::GdVal::null();
    this->f_damReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__EvilCap::meta() const { return &META_Gd__gd_core_items__EvilCap; }
gd::GdVal Gd__gd_core_items__EvilCap::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__EvilCap::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__EvilCap::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_nullifyApplied_1871: out = this->f_nullifyApplied; return true;
        case SYM_GEN_buffsActive_1872: out = this->f_buffsActive; return true;
        case SYM_GEN_buffTimer_1819: out = this->f_buffTimer; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_damReduction_1873: out = this->f_damReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__EvilCap::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_nullifyApplied_1871: this->f_nullifyApplied = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_buffsActive_1872: this->f_buffsActive = val; return true;
        case SYM_GEN_buffTimer_1819: this->f_buffTimer = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_damReduction_1873: this->f_damReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__EvilCap::has_own_method(gd::SymId m) const {
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
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__EvilCap::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
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
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__EvilCap::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__EvilCap::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_reduceHealingEfficiency_1183, _ca, 1); })();
    this->f_nullifyApplied = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__EvilCap::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__EvilCap::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_nullifyApplied)))) {
        this->f_nullifyApplied = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeBuffNullifyChances_1288, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, this->f_buffTimer, SYM_GEN_start_1779, _ca, 1); })();
    this->f_buffsActive = gd::gd_add(gd_ctx, this->f_buffsActive, gd::GdVal::from_int(1LL));
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__EvilCap::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
    this->f_buffsActive = gd::gd_sub(this->f_buffsActive, gd::GdVal::from_int(1LL));
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__EvilCap::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__EvilCap::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_buffsActive = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__EvilCap::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__buffsActive = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv__buffsActive, gd::GdVal::from_int(0LL))))) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__EvilCap::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[5]), gd::GdVal::from_str(&battle_string_literals[6]), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_damReduction = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__EvilCap(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__EvilCap>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,201u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__EvilCap = {CLS_Gd__gd_core_items__EvilCap, "EvilCap", "res://gd_core_items/EvilCap.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__EvilCap, &Gd__gd_core_items__EvilCap::get_static_prop_fn, &Gd__gd_core_items__EvilCap::call_static_fn};

void Gd__gd_core_items__Exclusive__ArcaneBoots::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_hasActivated = gd::GdVal::from_bool(false);
    this->f_speedTimer = gd::GdVal::null();
    this->f_healthThreshold = gd::GdVal::null();
    this->f_manaNeeded = gd::GdVal::null();
    this->f_luck = gd::GdVal::null();
    this->f_empower = gd::GdVal::null();
    this->f_bonusSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ArcaneBoots::meta() const { return &META_Gd__gd_core_items__Exclusive__ArcaneBoots; }
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneBoots::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ArcaneBoots::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ArcaneBoots::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_hasActivated_1906: out = this->f_hasActivated; return true;
        case SYM_GEN_speedTimer_2039: out = this->f_speedTimer; return true;
        case SYM_GEN_healthThreshold_1854: out = this->f_healthThreshold; return true;
        case SYM_GEN_manaNeeded_1881: out = this->f_manaNeeded; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        case SYM_GEN_bonusSpeed_1882: out = this->f_bonusSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ArcaneBoots::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hasActivated_1906: this->f_hasActivated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_speedTimer_2039: this->f_speedTimer = val; return true;
        case SYM_GEN_healthThreshold_1854: this->f_healthThreshold = val; return true;
        case SYM_GEN_manaNeeded_1881: this->f_manaNeeded = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        case SYM_GEN_bonusSpeed_1882: this->f_bonusSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ArcaneBoots::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onDamaged_1855: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_onSpeedTimerTimeout_2040: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ArcaneBoots::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1855: out = fn_onDamaged(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_onSpeedTimerTimeout_2040: out = fn_onSpeedTimerTimeout(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ArcaneBoots::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneBoots::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneBoots::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[7]), gd::GdVal::from_str(&battle_string_literals[8])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneBoots::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(this->f_hasActivated)) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRelativeHealth_302, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_manaNeeded)))) {
            this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
            gd::GdVal lv_event2 = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_luck, lv_event2}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_empower, lv_event2}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), gd::GdVal::from_bool(true), lv_event2}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 3); })();
            {
                gd::GdVal _t1782 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
                gd::GdArr* _t1783 = (_t1782.kind == gd::GdVal::Kind::Arr) ? _t1782.arr : nullptr;
                uint32_t _len__t1784 = _t1783 ? _t1783->len : 0u;
                for (uint32_t _t1784 = 0; _t1784 < _len__t1784; ++_t1784) {
                    gd::GdVal lv_item = _t1783->data[_t1784];
                    (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
                }
            }
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[9])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, this->f_speedTimer, SYM_GEN_start_1779, _ca, 1); })();
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_381, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneBoots::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::GdVal::from_int(1000LL), gd::GdVal::from_int(2LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneBoots::fn_onSpeedTimerTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1785 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1786 = (_t1785.kind == gd::GdVal::Kind::Arr) ? _t1785.arr : nullptr;
        uint32_t _len__t1787 = _t1786 ? _t1786->len : 0u;
        for (uint32_t _t1787 = 0; _t1787 < _len__t1787; ++_t1787) {
            gd::GdVal lv_item = _t1786->data[_t1787];
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_reduceSpeed_274, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneBoots::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_speedTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneBoots::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speedTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[10]), gd::GdVal::from_str(&battle_string_literals[11]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[12])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[13])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[14])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[15])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_bonusSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[16])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ArcaneBoots(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__ArcaneBoots>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,217u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ArcaneBoots = {CLS_Gd__gd_core_items__Exclusive__ArcaneBoots, "ArcaneBoots", "res://gd_core_items/Exclusive/ArcaneBoots.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__ArcaneBoots, &Gd__gd_core_items__Exclusive__ArcaneBoots::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ArcaneBoots::call_static_fn};

void Gd__gd_core_items__Exclusive__Battery::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_flatSpeed = gd::GdVal::null();
    this->f_speedPerTile = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Battery::meta() const { return &META_Gd__gd_core_items__Exclusive__Battery; }
gd::GdVal Gd__gd_core_items__Exclusive__Battery::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_chargeCells_2055: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(2LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(3LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(4LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(5LL))).as_float())}));
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Battery::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Battery::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_flatSpeed_2056: out = this->f_flatSpeed; return true;
        case SYM_GEN_speedPerTile_2057: out = this->f_speedPerTile; return true;
        case SYM_GEN_chargeCells_2055: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Battery::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_flatSpeed_2056: this->f_flatSpeed = val; return true;
        case SYM_GEN_speedPerTile_2057: this->f_speedPerTile = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Battery::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_lightning_289: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_emitCharge_2058: return true;
        case SYM_GEN_onChargeEnteredCell_2059: return true;
        case SYM_GEN_chargedItemStatChange_2060: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Battery::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_lightning_289: out = fn_canAffect_lightning(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_emitCharge_2058: out = fn_emitCharge(args, argc); return true;
        case SYM_GEN_onChargeEnteredCell_2059: out = fn_onChargeEnteredCell(args, argc); return true;
        case SYM_GEN_chargedItemStatChange_2060: out = fn_chargedItemStatChange(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Battery::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Battery::fn_canAffect_lightning(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_reactsToCharges_299, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Battery::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_emitCharge_2058, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[17]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_obj(this)}))}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Battery::fn_emitCharge(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_speedFactor = (_argc > 0) ? _args[0] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_event = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), Gd__gd_core_items__Exclusive__Battery::get_static_const_or_enum(gd_ctx, SYM_GEN_chargeCells_2055), lv_speedFactor, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_sendCharge_320, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Battery::fn_onChargeEnteredCell(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cellIndex = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_charge, lv_cellIndex, this->f_flatSpeed, this->f_speedPerTile}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeChargedItemStat_326, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Battery::fn_chargedItemStatChange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_value}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Battery::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::GdVal::from_int(1000LL), gd::GdVal::from_int(5LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Battery::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_flatSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[16])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_int(100LL));
    this->f_speedPerTile = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[18])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_int(100LL));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Battery(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Battery>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,229u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Battery = {CLS_Gd__gd_core_items__Exclusive__Battery, "Battery", "res://gd_core_items/Exclusive/Battery.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Battery, &Gd__gd_core_items__Exclusive__Battery::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Battery::call_static_fn};

void Gd__gd_core_items__Exclusive__Boomerang::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_staminaReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Boomerang::meta() const { return &META_Gd__gd_core_items__Exclusive__Boomerang; }
gd::GdVal Gd__gd_core_items__Exclusive__Boomerang::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Boomerang::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Boomerang::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_staminaReduction_2013: out = this->f_staminaReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Boomerang::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaReduction_2013: this->f_staminaReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Boomerang::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Boomerang::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Boomerang::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Boomerang::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_staminaReduction)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeStaminaFactor_305, _ca, 1); })();
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_373, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Boomerang::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_staminaReduction = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[19])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Boomerang(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Boomerang>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,243u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Boomerang = {CLS_Gd__gd_core_items__Exclusive__Boomerang, "Boomerang", "res://gd_core_items/Exclusive/Boomerang.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__Boomerang, &Gd__gd_core_items__Exclusive__Boomerang::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Boomerang::call_static_fn};

void Gd__gd_core_items__Exclusive__Chainsaw::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_sawFrame = gd::GdVal::from_int(0LL);
    this->f_sawTween = gd::GdVal::null();
    this->f_removeBuffs = gd::GdVal::null();
    this->f_slowdown = gd::GdVal::null();
    this->f_sawAnimation = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Chainsaw::meta() const { return &META_Gd__gd_core_items__Exclusive__Chainsaw; }
gd::GdVal Gd__gd_core_items__Exclusive__Chainsaw::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_sawSpeed_2122: return gd::GdVal::from_float(8.0);
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Chainsaw::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Chainsaw::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_sawFrame_2123: out = this->f_sawFrame; return true;
        case SYM_GEN_sawTween_2124: out = this->f_sawTween; return true;
        case SYM_GEN_removeBuffs_2125: out = this->f_removeBuffs; return true;
        case SYM_GEN_slowdown_2126: out = this->f_slowdown; return true;
        case SYM_GEN_sawAnimation_2127: out = this->f_sawAnimation; return true;
        case SYM_GEN_sawSpeed_2122: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chainsaw::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_sawFrame_2123: this->f_sawFrame = val; return true;
        case SYM_GEN_sawTween_2124: this->f_sawTween = val; return true;
        case SYM_GEN_removeBuffs_2125: this->f_removeBuffs = val; return true;
        case SYM_GEN_slowdown_2126: this->f_slowdown = val; return true;
        case SYM_GEN_sawAnimation_2127: this->f_sawAnimation = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chainsaw::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_pickup_717: return true;
        case SYM_GEN_drop_723: return true;
        case SYM_GEN_setSawTexture_2128: return true;
        case SYM_GEN_onChargeReceived_2129: return true;
        case SYM_GEN_onChargeLeft_2130: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chainsaw::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_pickup_717: out = fn_pickup(args, argc); return true;
        case SYM_GEN_drop_723: out = fn_drop(args, argc); return true;
        case SYM_GEN_setSawTexture_2128: out = fn_setSawTexture(args, argc); return true;
        case SYM_GEN_onChargeReceived_2129: out = fn_onChargeReceived(args, argc); return true;
        case SYM_GEN_onChargeLeft_2130: out = fn_onChargeLeft(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Chainsaw::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Chainsaw::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chainsaw::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_numCharges, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_removeBuffs, gd::GdVal::from_int(1000LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealBuffsFraction_365, _ca, 2); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {this->f_removeBuffs, gd::GdVal::from_int(1000LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeBuffsFraction_364, _ca, 2); })();
        }
        (void)([&]() { gd::GdVal _ca[] = {this->f_slowdown}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_reduceSpeed_274, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chainsaw::fn_pickup(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_pickupType = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Chainsaw::get_static_const_or_enum(gd_ctx, SYM_GEN_PickupType_866), SYM_GEN_Grabbed_2730));
    (void)([&]() { gd::GdVal _ca[] = {lv_pickupType}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_pickup_717, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chainsaw::fn_drop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_res = ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_drop_723, nullptr, 0, _out); return _out; })();
    return lv_res;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chainsaw::fn_setSawTexture(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_sawFrame = gd::gd_add(gd_ctx, this->f_sawFrame, gd::GdVal::from_int(1LL));
    this->f_sawFrame = gd::gd_mod(gd_ctx, this->f_sawFrame, gd::GdVal::from_int(4LL));
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadowTexture_789, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chainsaw::fn_onChargeReceived(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_numCharges, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playPickupSound_736, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chainsaw::fn_onChargeLeft(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_numCharges, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chainsaw::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chainsaw::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charged = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv_charged)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chainsaw::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chainsaw::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_removeBuffs = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[20])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_slowdown = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[21])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Chainsaw(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Chainsaw>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,259u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chainsaw = {CLS_Gd__gd_core_items__Exclusive__Chainsaw, "Chainsaw", "res://gd_core_items/Exclusive/Chainsaw.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__Chainsaw, &Gd__gd_core_items__Exclusive__Chainsaw::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Chainsaw::call_static_fn};

void Gd__gd_core_items__Exclusive__Chess__WhiteQueen::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Chess__ChessPiece::init_fields(gd_ctx);
    this->f_heat = gd::GdVal::null();
    this->f_heatFirstCapture = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Chess__WhiteQueen::meta() const { return &META_Gd__gd_core_items__Exclusive__Chess__WhiteQueen; }
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteQueen::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteQueen::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteQueen::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_heat_1896: out = this->f_heat; return true;
        case SYM_GEN_heatFirstCapture_2160: out = this->f_heatFirstCapture; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteQueen::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heat_1896: this->f_heat = val; return true;
        case SYM_GEN_heatFirstCapture_2160: this->f_heatFirstCapture = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteQueen::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2146: return true;
        case SYM_GEN_doEliminatedEffect_2148: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteQueen::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2146: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_doEliminatedEffect_2148: out = fn_doEliminatedEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteQueen::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteQueen::fn_doCapturingEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__eliminatedPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_numCaptures, gd::GdVal::from_int(1LL))))) {
        return ([&]() { gd::GdVal _ca[] = {this->f_heatFirstCapture}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteQueen::fn_doEliminatedEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_makeInvulnerable_1211, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteQueen::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[22])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_heatFirstCapture = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[23])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Chess__WhiteQueen(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Chess__WhiteQueen>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,275u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__WhiteQueen = {CLS_Gd__gd_core_items__Exclusive__Chess__WhiteQueen, "WhiteQueen", "res://gd_core_items/Exclusive/Chess/WhiteQueen.gd", &META_Gd__gd_core_items__Exclusive__Chess__ChessPiece, true, _alloc_Gd__gd_core_items__Exclusive__Chess__WhiteQueen, &Gd__gd_core_items__Exclusive__Chess__WhiteQueen::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Chess__WhiteQueen::call_static_fn};

void Gd__gd_core_items__Exclusive__CupcakeDragon::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_buffRemoval = gd::GdVal::null();
    this->f_buffGain = gd::GdVal::null();
    this->f_speedPerFood = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__CupcakeDragon::meta() const { return &META_Gd__gd_core_items__Exclusive__CupcakeDragon; }
gd::GdVal Gd__gd_core_items__Exclusive__CupcakeDragon::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__CupcakeDragon::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__CupcakeDragon::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_buffRemoval_2187: out = this->f_buffRemoval; return true;
        case SYM_GEN_buffGain_2188: out = this->f_buffGain; return true;
        case SYM_GEN_speedPerFood_2189: out = this->f_speedPerFood; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__CupcakeDragon::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffRemoval_2187: this->f_buffRemoval = val; return true;
        case SYM_GEN_buffGain_2188: this->f_buffGain = val; return true;
        case SYM_GEN_speedPerFood_2189: this->f_speedPerFood = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__CupcakeDragon::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__CupcakeDragon::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__CupcakeDragon::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__CupcakeDragon::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        gd::GdVal lv_buffsLeft = this->f_buffRemoval;
        gd::GdVal lv_ownMostBuffs = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMostStacks_361, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_ownMostBuffs, gd::GdVal::from_str(&battle_string_literals[24])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_shuffleEngine_1747, _ca, 2); })();
        {
            gd::GdVal _t1788 = gd::gd_iter_seq(gd_ctx.arena, lv_ownMostBuffs);
            gd::GdArr* _t1789 = (_t1788.kind == gd::GdVal::Kind::Arr) ? _t1788.arr : nullptr;
            uint32_t _len__t1790 = _t1789 ? _t1789->len : 0u;
            for (uint32_t _t1790 = 0; _t1790 < _len__t1790; ++_t1790) {
                gd::GdVal lv_buffType = _t1789->data[_t1790];
                gd::GdVal lv_cur = ([&]() { gd::GdVal _ca[] = {lv_buffType}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getStacks_1023, _ca, 1); })();
                gd::GdVal lv_buffsRemoved = gd::gd_min(lv_cur, lv_buffsLeft);
                (void)([&]() { gd::GdVal _ca[] = {lv_buffType, lv_buffsRemoved, gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_loseStacks_1032, _ca, 3); })();
                lv_buffsLeft = gd::gd_sub(lv_buffsLeft, lv_buffsRemoved);
                if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_buffsLeft, gd::GdVal::from_int(0LL))))) {
                    break;
                }
            }
        }
        gd::GdVal lv_oppoMostBuffs = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMostStacks_361, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), ([&]() { gd::GdVal _ca[] = {lv_oppoMostBuffs}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_pickRandomElement_1746, _ca, 1); })(), this->f_buffGain}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CupcakeDragon::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CupcakeDragon::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_speedPerFood, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CupcakeDragon::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_buffRemoval = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[25])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_buffGain = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[26])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_speedPerFood = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[16])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__CupcakeDragon(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__CupcakeDragon>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,293u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__CupcakeDragon = {CLS_Gd__gd_core_items__Exclusive__CupcakeDragon, "CupcakeDragon", "res://gd_core_items/Exclusive/CupcakeDragon.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__CupcakeDragon, &Gd__gd_core_items__Exclusive__CupcakeDragon::get_static_prop_fn, &Gd__gd_core_items__Exclusive__CupcakeDragon::call_static_fn};

void Gd__gd_core_items__RubyWhelp::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__RubyWhelp::meta() const { return &META_Gd__gd_core_items__RubyWhelp; }
gd::GdVal Gd__gd_core_items__RubyWhelp::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__RubyWhelp::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__RubyWhelp::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__RubyWhelp::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__RubyWhelp::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreCombatStart_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__RubyWhelp::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreCombatStart_125: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__RubyWhelp::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__RubyWhelp::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveReflectStacks_200, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RubyWhelp::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RubyWhelp::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__RubyWhelp(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__RubyWhelp>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,630u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__RubyWhelp = {CLS_Gd__gd_core_items__RubyWhelp, "RubyWhelp", "res://gd_core_items/RubyWhelp.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__RubyWhelp, &Gd__gd_core_items__RubyWhelp::get_static_prop_fn, &Gd__gd_core_items__RubyWhelp::call_static_fn};

void Gd__gd_core_items__Exclusive__EnergyConversion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_stackTypes = gd::GdVal::null();
    this->f_heat = gd::GdVal::null();
    this->f_heatThreshold = gd::GdVal::null();
    this->f_numBuffs = gd::GdVal::null();
    this->f_speedPerFood = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__EnergyConversion::meta() const { return &META_Gd__gd_core_items__Exclusive__EnergyConversion; }
gd::GdVal Gd__gd_core_items__Exclusive__EnergyConversion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__EnergyConversion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__EnergyConversion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_stackTypes_1926: out = this->f_stackTypes; return true;
        case SYM_GEN_heat_1896: out = this->f_heat; return true;
        case SYM_GEN_heatThreshold_1975: out = this->f_heatThreshold; return true;
        case SYM_GEN_numBuffs_2005: out = this->f_numBuffs; return true;
        case SYM_GEN_speedPerFood_2189: out = this->f_speedPerFood; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__EnergyConversion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stackTypes_1926: this->f_stackTypes = val; return true;
        case SYM_GEN_heat_1896: this->f_heat = val; return true;
        case SYM_GEN_heatThreshold_1975: this->f_heatThreshold = val; return true;
        case SYM_GEN_numBuffs_2005: this->f_numBuffs = val; return true;
        case SYM_GEN_speedPerFood_2189: this->f_speedPerFood = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__EnergyConversion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__EnergyConversion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__EnergyConversion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__EnergyConversion::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EnergyConversion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0), this->f_speedPerFood)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EnergyConversion::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getHeat_1251, nullptr, 0), this->f_heatThreshold)))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_numBuffs, gd::GdVal::null(), this->f_stackTypes}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 3); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
        }
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EnergyConversion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[27])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_heatThreshold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[28])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_numBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[20])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_speedPerFood = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[16])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_stackTypes = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(107LL)}; return gd::native_inline_call(gd_ctx, this->f_stackTypes, gd::SYM_erase, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__EnergyConversion(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__EnergyConversion>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,323u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__EnergyConversion = {CLS_Gd__gd_core_items__Exclusive__EnergyConversion, "EnergyConversion", "res://gd_core_items/Exclusive/EnergyConversion.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__EnergyConversion, &Gd__gd_core_items__Exclusive__EnergyConversion::get_static_prop_fn, &Gd__gd_core_items__Exclusive__EnergyConversion::call_static_fn};

void Gd__gd_core_items__Exclusive__ForestFriend::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ForestFriend::meta() const { return &META_Gd__gd_core_items__Exclusive__ForestFriend; }
gd::GdVal Gd__gd_core_items__Exclusive__ForestFriend::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ForestFriend::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ForestFriend::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ForestFriend::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ForestFriend::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_combatStart_127: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ForestFriend::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_combatStart_127: out = fn_combatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ForestFriend::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ForestFriend::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(3LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ForestFriend::fn_combatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_combatStart_127, nullptr, 0, _out); return _out; })();
    gd::GdVal lv_numAffected = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numAffected, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(lv_numAffected, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ForestFriend::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ForestFriend(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__ForestFriend>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,338u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ForestFriend = {CLS_Gd__gd_core_items__Exclusive__ForestFriend, "ForestFriend", "res://gd_core_items/Exclusive/ForestFriend.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__ForestFriend, &Gd__gd_core_items__Exclusive__ForestFriend::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ForestFriend::call_static_fn};

void Gd__gd_core_items__Exclusive__GoldArmor::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_gold = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
    this->f_cleanse = gd::GdVal::null();
    this->f_block = gd::GdVal::null();
    this->f_speedMalus = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__GoldArmor::meta() const { return &META_Gd__gd_core_items__Exclusive__GoldArmor; }
gd::GdVal Gd__gd_core_items__Exclusive__GoldArmor::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__GoldArmor::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__GoldArmor::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_gold_2293: out = this->f_gold; return true;
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        case SYM_GEN_cleanse_1133: out = this->f_cleanse; return true;
        case SYM_GEN_block_1678: out = this->f_block; return true;
        case SYM_GEN_speedMalus_2181: out = this->f_speedMalus; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__GoldArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_gold_2293: this->f_gold = val; return true;
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        case SYM_GEN_cleanse_1133: this->f_cleanse = val; return true;
        case SYM_GEN_block_1678: this->f_block = val; return true;
        case SYM_GEN_speedMalus_2181: this->f_speedMalus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__GoldArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__GoldArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__GoldArmor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldArmor::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_gold}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveGold_754, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldArmor::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldArmor::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1791 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t1792 = (_t1791.kind == gd::GdVal::Kind::Arr) ? _t1791.arr : nullptr;
        uint32_t _len__t1793 = _t1792 ? _t1792->len : 0u;
        for (uint32_t _t1793 = 0; _t1793 < _len__t1793; ++_t1793) {
            gd::GdVal lv_item = _t1792->data[_t1793];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(4LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_speedMalus}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_reduceSpeed_274, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0), this->f_regen)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_cleanse}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_356, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getDebuffStacks_1216, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_block}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_gold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[29])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[30])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_cleanse = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[31])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_block = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[32])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_speedMalus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[16])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__GoldArmor(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__GoldArmor>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,352u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__GoldArmor = {CLS_Gd__gd_core_items__Exclusive__GoldArmor, "GoldArmor", "res://gd_core_items/Exclusive/GoldArmor.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__GoldArmor, &Gd__gd_core_items__Exclusive__GoldArmor::get_static_prop_fn, &Gd__gd_core_items__Exclusive__GoldArmor::call_static_fn};

void Gd__gd_core_items__Exclusive__IceArmor::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__IceArmor::meta() const { return &META_Gd__gd_core_items__Exclusive__IceArmor; }
gd::GdVal Gd__gd_core_items__Exclusive__IceArmor::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__IceArmor::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__IceArmor::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__IceArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__IceArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__IceArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__IceArmor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__IceArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_351, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__IceArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getHeat_1251, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useHeat_354, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_351, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__IceArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__IceArmor(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__IceArmor>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,367u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__IceArmor = {CLS_Gd__gd_core_items__Exclusive__IceArmor, "IceArmor", "res://gd_core_items/Exclusive/IceArmor.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__IceArmor, &Gd__gd_core_items__Exclusive__IceArmor::get_static_prop_fn, &Gd__gd_core_items__Exclusive__IceArmor::call_static_fn};

void Gd__gd_core_items__Exclusive__LevelUp::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_stamina = gd::GdVal::null();
    this->f_mana = gd::GdVal::null();
    this->f_luck = gd::GdVal::null();
    this->f_speedPerRound = gd::GdVal::null();
    this->f_buyRound = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__LevelUp::meta() const { return &META_Gd__gd_core_items__Exclusive__LevelUp; }
gd::GdVal Gd__gd_core_items__Exclusive__LevelUp::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__LevelUp::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__LevelUp::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_stamina_2156: out = this->f_stamina; return true;
        case SYM_GEN_mana_1928: out = this->f_mana; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_speedPerRound_2344: out = this->f_speedPerRound; return true;
        case SYM_GEN_buyRound_2345: out = this->f_buyRound; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__LevelUp::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stamina_2156: this->f_stamina = val; return true;
        case SYM_GEN_mana_1928: this->f_mana = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_speedPerRound_2344: this->f_speedPerRound = val; return true;
        case SYM_GEN_buyRound_2345: this->f_buyRound = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__LevelUp::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__LevelUp::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__LevelUp::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__LevelUp::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_roundsPassed = gd::gd_sub(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_cur_round_1424), this->f_buyRound);
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_roundsPassed, this->f_speedPerRound)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LevelUp::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[33])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_stamina}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_318, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LevelUp::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[19])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[34])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[14])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_speedPerRound = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[16])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_buyRound = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[35])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__LevelUp(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__LevelUp>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,382u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__LevelUp = {CLS_Gd__gd_core_items__Exclusive__LevelUp, "LevelUp", "res://gd_core_items/Exclusive/LevelUp.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__LevelUp, &Gd__gd_core_items__Exclusive__LevelUp::get_static_prop_fn, &Gd__gd_core_items__Exclusive__LevelUp::call_static_fn};

void Gd__gd_core_items__Exclusive__ManaCrystal::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_mana1 = gd::GdVal::null();
    this->f_mana2 = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ManaCrystal::meta() const { return &META_Gd__gd_core_items__Exclusive__ManaCrystal; }
gd::GdVal Gd__gd_core_items__Exclusive__ManaCrystal::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_chargeCells_2055: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(2LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(3LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float())})), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(2LL))).as_float())})), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(2LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(3LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float())})), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(1LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(2LL)).as_float())}))}));
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ManaCrystal::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ManaCrystal::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_mana1_2392: out = this->f_mana1; return true;
        case SYM_GEN_mana2_2273: out = this->f_mana2; return true;
        case SYM_GEN_chargeCells_2055: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ManaCrystal::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_mana1_2392: this->f_mana1 = val; return true;
        case SYM_GEN_mana2_2273: this->f_mana2 = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ManaCrystal::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_lightning_289: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_emitCharge_2058: return true;
        case SYM_GEN_onChargeEnteredCell_2059: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ManaCrystal::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_lightning_289: out = fn_canAffect_lightning(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_emitCharge_2058: out = fn_emitCharge(args, argc); return true;
        case SYM_GEN_onChargeEnteredCell_2059: out = fn_onChargeEnteredCell(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ManaCrystal::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaCrystal::fn_canAffect_lightning(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaCrystal::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_emitCharge_2058, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[17]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_obj(this)}))}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaCrystal::fn_emitCharge(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_speedFactor = (_argc > 0) ? _args[0] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_event = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    {
        gd::GdVal _t1794 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, Gd__gd_core_items__Exclusive__ManaCrystal::get_static_const_or_enum(gd_ctx, SYM_GEN_chargeCells_2055), gd::SYM_size, nullptr, 0));
        gd::GdArr* _t1795 = (_t1794.kind == gd::GdVal::Kind::Arr) ? _t1794.arr : nullptr;
        uint32_t _len__t1796 = _t1795 ? _t1795->len : 0u;
        for (uint32_t _t1796 = 0; _t1796 < _len__t1796; ++_t1796) {
            gd::GdVal lv_i = _t1795->data[_t1796];
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__ManaCrystal::get_static_const_or_enum(gd_ctx, SYM_GEN_chargeCells_2055), lv_i), lv_speedFactor, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_sendCharge_320, _ca, 4); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaCrystal::fn_onChargeEnteredCell(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cellIndex = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1648), gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1648), gd::get_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1647))))) : gd::GdVal::from_bool(false)))) {
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(23LL)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1648), SYM_GEN_hasType_79, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_mana2}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {this->f_mana1}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaCrystal::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_mana1 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[36])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_mana2 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[37])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ManaCrystal(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__ManaCrystal>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,397u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ManaCrystal = {CLS_Gd__gd_core_items__Exclusive__ManaCrystal, "ManaCrystal", "res://gd_core_items/Exclusive/ManaCrystal.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__ManaCrystal, &Gd__gd_core_items__Exclusive__ManaCrystal::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ManaCrystal::call_static_fn};

void Gd__gd_core_items__Exclusive__NoRushPlease::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__LeatherHelm::init_fields(gd_ctx);
    this->f_cold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__NoRushPlease::meta() const { return &META_Gd__gd_core_items__Exclusive__NoRushPlease; }
gd::GdVal Gd__gd_core_items__Exclusive__NoRushPlease::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__LeatherHelm::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__NoRushPlease::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__NoRushPlease::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_cold_2045: out = this->f_cold; return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__NoRushPlease::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_cold_2045: this->f_cold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__NoRushPlease::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreCombatStart_125: return true;
        case SYM_GEN_buffEnded_1817: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__NoRushPlease::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreCombatStart_125: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_buffEnded_1817: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__NoRushPlease::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__LeatherHelm::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__NoRushPlease::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__NoRushPlease::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN_onPreCombatStart_125, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__NoRushPlease::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN_buffEnded_1817, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__NoRushPlease::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_cold}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_351, _ca, 1); })();
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN_onCombatStart_934, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__NoRushPlease::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_cold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[38])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__NoRushPlease(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__NoRushPlease>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,413u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__NoRushPlease = {CLS_Gd__gd_core_items__Exclusive__NoRushPlease, "NoRushPlease", "res://gd_core_items/Exclusive/NoRushPlease.gd", &META_Gd__gd_core_items__LeatherHelm, true, _alloc_Gd__gd_core_items__Exclusive__NoRushPlease, &Gd__gd_core_items__Exclusive__NoRushPlease::get_static_prop_fn, &Gd__gd_core_items__Exclusive__NoRushPlease::call_static_fn};

void Gd__gd_core_items__Exclusive__PoisonGrenade::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_poisonCritActive = gd::GdVal::from_bool(false);
    this->f_tween = gd::GdVal::null();
    this->f_poison = gd::GdVal::null();
    this->f_selfPoison = gd::GdVal::null();
    this->f_cdAdvance = gd::GdVal::null();
    this->f_luckNeeded = gd::GdVal::null();
    this->f_light = gd::GdVal::null();
    this->f_lightAni = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PoisonGrenade::meta() const { return &META_Gd__gd_core_items__Exclusive__PoisonGrenade; }
gd::GdVal Gd__gd_core_items__Exclusive__PoisonGrenade::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PoisonGrenade::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PoisonGrenade::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_poisonCritActive_2429: out = this->f_poisonCritActive; return true;
        case SYM_GEN_tween_2430: out = this->f_tween; return true;
        case SYM_GEN_poison_1962: out = this->f_poison; return true;
        case SYM_GEN_selfPoison_2403: out = this->f_selfPoison; return true;
        case SYM_GEN_cdAdvance_2080: out = this->f_cdAdvance; return true;
        case SYM_GEN_luckNeeded_1874: out = this->f_luckNeeded; return true;
        case SYM_GEN_light_949: out = this->f_light; return true;
        case SYM_GEN_lightAni_2431: out = this->f_lightAni; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PoisonGrenade::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_poisonCritActive_2429: this->f_poisonCritActive = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_tween_2430: this->f_tween = val; return true;
        case SYM_GEN_poison_1962: this->f_poison = val; return true;
        case SYM_GEN_selfPoison_2403: this->f_selfPoison = val; return true;
        case SYM_GEN_cdAdvance_2080: this->f_cdAdvance = val; return true;
        case SYM_GEN_luckNeeded_1874: this->f_luckNeeded = val; return true;
        case SYM_GEN_light_949: this->f_light = val; return true;
        case SYM_GEN_lightAni_2431: this->f_lightAni = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PoisonGrenade::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onChargeReceived_2129: return true;
        case SYM_GEN_onLuckChanged_2064: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PoisonGrenade::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onChargeReceived_2129: out = fn_onChargeReceived(args, argc); return true;
        case SYM_GEN_onLuckChanged_2064: out = fn_onLuckChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PoisonGrenade::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonGrenade::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[39]), gd::GdVal::from_str(&battle_string_literals[40])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonGrenade::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_poison}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_selfPoison}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_selfInflictPoison_212, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonGrenade::fn_onChargeReceived(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_cdAdvance}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_advanceCooldownSeconds_147, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonGrenade::fn_onLuckChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_poisonCritActive)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), this->f_luckNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changePoisonCritChancePercent_1283, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    }
    else if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(this->f_poisonCritActive)) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), this->f_luckNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changePoisonCritChancePercent_1283, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonGrenade::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonGrenade::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__poisonCritActive = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_poisonCritActive = gd::gd_coerce_bool(lv__poisonCritActive);
    if (gd::gd_truth(this->f_poisonCritActive)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonGrenade::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_poison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[41])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_selfPoison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[42])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_cdAdvance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[43])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[44])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PoisonGrenade(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__PoisonGrenade>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,428u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PoisonGrenade = {CLS_Gd__gd_core_items__Exclusive__PoisonGrenade, "PoisonGrenade", "res://gd_core_items/Exclusive/PoisonGrenade.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__PoisonGrenade, &Gd__gd_core_items__Exclusive__PoisonGrenade::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PoisonGrenade::call_static_fn};

void Gd__gd_core_items__Exclusive__RainbowBadge::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__RainbowBadge::meta() const { return &META_Gd__gd_core_items__Exclusive__RainbowBadge; }
gd::GdVal Gd__gd_core_items__Exclusive__RainbowBadge::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__RainbowBadge::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__RainbowBadge::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__RainbowBadge::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__RainbowBadge::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onAddToInventory_419: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_getRelatedItems_459: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN_getRelatedItemHeight_700: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__RainbowBadge::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onAddToInventory_419: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getRelatedItems_459: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_700: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__RainbowBadge::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowBadge::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowBadge::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowBadge::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1797 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0));
        gd::GdArr* _t1798 = (_t1797.kind == gd::GdVal::Kind::Arr) ? _t1797.arr : nullptr;
        uint32_t _len__t1799 = _t1798 ? _t1798->len : 0u;
        for (uint32_t _t1799 = 0; _t1799 < _len__t1799; ++_t1799) {
            gd::GdVal lv_buff = _t1798->data[_t1799];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), lv_buff, gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 3); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowBadge::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowBadge::fn_getRelatedItemColumns(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(6LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowBadge::fn_getRelatedItemHeight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(100LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowBadge::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__RainbowBadge(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__RainbowBadge>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,445u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RainbowBadge = {CLS_Gd__gd_core_items__Exclusive__RainbowBadge, "RainbowBadge", "res://gd_core_items/Exclusive/RainbowBadge.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__RainbowBadge, &Gd__gd_core_items__Exclusive__RainbowBadge::get_static_prop_fn, &Gd__gd_core_items__Exclusive__RainbowBadge::call_static_fn};

void Gd__gd_core_items__Exclusive__Robodog::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_digUpItems = ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 25); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[45]), gd::GdVal::from_int(4LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[46]), gd::GdVal::from_int(3LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[47]), gd::GdVal::from_int(2LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[48]), gd::GdVal::from_int(3LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[49]), gd::GdVal::from_int(3LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[50]), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[51]), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[52]), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[53]), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[54]), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[55]), gd::GdVal::from_float(0.5)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[56]), gd::GdVal::from_float(0.5)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[57]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[58]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[59]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[60]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[61]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[62]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[63]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[64]), gd::GdVal::from_float(0.1)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[65]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[66]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[67]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[68]), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[69]), gd::GdVal::from_float(0.2)); return gd::GdVal::from_dict(d); })();
    this->f_spawnPos = gd::GdVal::null();
    this->f_luck = gd::GdVal::null();
    this->f_heat = gd::GdVal::null();
    this->f_cdIncrease = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Robodog::meta() const { return &META_Gd__gd_core_items__Exclusive__Robodog; }
gd::GdVal Gd__gd_core_items__Exclusive__Robodog::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Robodog::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Robodog::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_digUpItems_1978: out = this->f_digUpItems; return true;
        case SYM_GEN_spawnPos_1980: out = this->f_spawnPos; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_heat_1896: out = this->f_heat; return true;
        case SYM_GEN_cdIncrease_2470: out = this->f_cdIncrease; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Robodog::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_digUpItems_1978: this->f_digUpItems = val; return true;
        case SYM_GEN_spawnPos_1980: this->f_spawnPos = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_heat_1896: this->f_heat = val; return true;
        case SYM_GEN_cdIncrease_2470: this->f_cdIncrease = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Robodog::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onChargeReceived_2129: return true;
        case SYM_GEN_onChargeLeft_2130: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Robodog::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onChargeReceived_2129: out = fn_onChargeReceived(args, argc); return true;
        case SYM_GEN_onChargeLeft_2130: out = fn_onChargeLeft(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Robodog::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Robodog::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Robodog::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Robodog::fn_onChargeReceived(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetBaseCooldown_109, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_numCharges, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Robodog::fn_onChargeLeft(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_numCharges, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Robodog::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_numCharges, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_baseCooldownOverride, this->f_cdIncrease)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBaseCooldown_108, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Robodog::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charged = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_charged = gd::gd_coerce_bool(lv_charged);
    if (gd::gd_truth(lv_charged)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Robodog::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[14])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[27])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_cdIncrease = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[70])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Robodog(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Robodog>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,461u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Robodog = {CLS_Gd__gd_core_items__Exclusive__Robodog, "Robodog", "res://gd_core_items/Exclusive/Robodog.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Robodog, &Gd__gd_core_items__Exclusive__Robodog::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Robodog::call_static_fn};

void Gd__gd_core_items__Exclusive__ShinyMantle::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_invuProcced = gd::GdVal::from_int(0);
    this->f_gemDurFactor = gd::GdVal::from_float(0.0);
    this->f_manaNeeded = gd::GdVal::null();
    this->f_activationParticles = gd::GdVal::null();
    this->f_buffTimer = gd::GdVal::null();
    this->f_blind = gd::GdVal::null();
    this->f_manaNeeded_base = gd::GdVal::null();
    this->f_manaCostIncrease = gd::GdVal::null();
    this->f_maxUses = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ShinyMantle::meta() const { return &META_Gd__gd_core_items__Exclusive__ShinyMantle; }
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ShinyMantle::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ShinyMantle::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_invuProcced_2493: out = this->f_invuProcced; return true;
        case SYM_GEN_gemDurFactor_2494: out = this->f_gemDurFactor; return true;
        case SYM_GEN_manaNeeded_1881: out = this->f_manaNeeded; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_buffTimer_1819: out = this->f_buffTimer; return true;
        case SYM_GEN_blind_1911: out = this->f_blind; return true;
        case SYM_GEN_manaNeeded_base_2495: out = this->f_manaNeeded_base; return true;
        case SYM_GEN_manaCostIncrease_2496: out = this->f_manaCostIncrease; return true;
        case SYM_GEN_maxUses_2086: out = this->f_maxUses; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ShinyMantle::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_invuProcced_2493: this->f_invuProcced = gd::gd_coerce_int(val); return true;
        case SYM_GEN_gemDurFactor_2494: this->f_gemDurFactor = gd::gd_coerce_float(val); return true;
        case SYM_GEN_manaNeeded_1881: this->f_manaNeeded = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_buffTimer_1819: this->f_buffTimer = val; return true;
        case SYM_GEN_blind_1911: this->f_blind = val; return true;
        case SYM_GEN_manaNeeded_base_2495: this->f_manaNeeded_base = val; return true;
        case SYM_GEN_manaCostIncrease_2496: this->f_manaCostIncrease = val; return true;
        case SYM_GEN_maxUses_2086: this->f_maxUses = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ShinyMantle::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_readyToFuse_751: return true;
        case SYM_GEN_onFusingFinished_848: return true;
        case SYM_GEN_getCounterValue_2351: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onInvuStarted_2497: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN_buffEnded_1817: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ShinyMantle::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_readyToFuse_751: out = fn_readyToFuse(args, argc); return true;
        case SYM_GEN_onFusingFinished_848: out = fn_onFusingFinished(args, argc); return true;
        case SYM_GEN_getCounterValue_2351: out = fn_getCounterValue(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onInvuStarted_2497: out = fn_onInvuStarted(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_buffEnded_1817: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ShinyMantle::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isBag_83, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_readyToFuse(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_bondedIngredients, gd::SYM_empty, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_onFusingFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_validBonds = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_validBonds}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onFusingFinished_848, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_getCounterValue(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_gold = gd::GdVal::from_int(0LL);
    gd::GdVal lv_inv = (gd::gd_truth(this->f_placed) ? (this->f_inventory) : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1302), SYM_GEN_INVENTORY_1093)));
    {
        gd::GdVal _t1800 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, lv_inv, SYM_GEN_getItemsAndGems_1604, nullptr, 0));
        gd::GdArr* _t1801 = (_t1800.kind == gd::GdVal::Kind::Arr) ? _t1800.arr : nullptr;
        uint32_t _len__t1802 = _t1801 ? _t1801->len : 0u;
        for (uint32_t _t1802 = 0; _t1802 < _len__t1802; ++_t1802) {
            gd::GdVal lv_item = _t1801->data[_t1802];
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isGem_84, nullptr, 0))) {
                lv_gold = gd::gd_add(gd_ctx, lv_gold, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getPrice_392, nullptr, 0));
            }
        }
    }
    if (gd::gd_truth(this->f_dragged)) {
        {
            gd::GdVal _t1803 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_497, nullptr, 0));
            gd::GdArr* _t1804 = (_t1803.kind == gd::GdVal::Kind::Arr) ? _t1803.arr : nullptr;
            uint32_t _len__t1805 = _t1804 ? _t1804->len : 0u;
            for (uint32_t _t1805 = 0; _t1805 < _len__t1805; ++_t1805) {
                gd::GdVal lv_gem = _t1804->data[_t1805];
                lv_gold = gd::gd_add(gd_ctx, lv_gold, gd::native_inline_call(gd_ctx, lv_gem, SYM_GEN_getPrice_392, nullptr, 0));
            }
        }
    }
    return lv_gold;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[71]), gd::GdVal::from_str(&battle_string_literals[72])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    this->f_manaNeeded = this->f_manaNeeded_base;
    this->f_invuProcced = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_gemDurFactor = gd::gd_coerce_float(gd::gd_floor(gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue_2351, nullptr, 0), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[29])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })())));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_isVulnerable_1291, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_manaNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
        this->f_invuProcced = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_invuProcced, gd::GdVal::from_int(1LL)));
        gd::GdVal lv_invuDur = gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[73])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[74])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), this->f_gemDurFactor));
        (void)([&]() { gd::GdVal _ca[] = {lv_invuDur}; return gd::native_inline_call(gd_ctx, this->f_buffTimer, SYM_GEN_start_1779, _ca, 1); })();
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_invuDur, gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_makeInvulnerable_1211, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_manaNeeded, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 2); })();
        this->f_manaNeeded = gd::gd_add(gd_ctx, this->f_manaNeeded, this->f_manaCostIncrease);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_invuProcced, this->f_maxUses)))) {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
            return gd::GdVal::null();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_onInvuStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_blind, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_213, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_invuActive = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv_invuActive)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[5]), gd::GdVal::from_str(&battle_string_literals[6]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_blind = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[75])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_manaNeeded_base = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[13])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_manaCostIncrease = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[34])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_maxUses = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[76])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ShinyMantle(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__ShinyMantle>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,477u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ShinyMantle = {CLS_Gd__gd_core_items__Exclusive__ShinyMantle, "ShinyMantle", "res://gd_core_items/Exclusive/ShinyMantle.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__ShinyMantle, &Gd__gd_core_items__Exclusive__ShinyMantle::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ShinyMantle::call_static_fn};

void Gd__gd_core_items__Exclusive__SpeakwithAnimals::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_petDescriptors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}));
    this->f_salesChance = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SpeakwithAnimals::meta() const { return &META_Gd__gd_core_items__Exclusive__SpeakwithAnimals; }
gd::GdVal Gd__gd_core_items__Exclusive__SpeakwithAnimals::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_pets_2524: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_str(&battle_string_literals[77]), gd::GdVal::from_str(&battle_string_literals[78]), gd::GdVal::from_str(&battle_string_literals[79]), gd::GdVal::from_str(&battle_string_literals[80]), gd::GdVal::from_str(&battle_string_literals[81]), gd::GdVal::from_str(&battle_string_literals[82]), gd::GdVal::from_str(&battle_string_literals[83]), gd::GdVal::from_str(&battle_string_literals[84]), gd::GdVal::from_str(&battle_string_literals[85]), gd::GdVal::from_str(&battle_string_literals[86]), gd::GdVal::from_str(&battle_string_literals[87]), gd::GdVal::from_str(&battle_string_literals[88]), gd::GdVal::from_str(&battle_string_literals[89]), gd::GdVal::from_str(&battle_string_literals[90]), gd::GdVal::from_str(&battle_string_literals[91]), gd::GdVal::from_str(&battle_string_literals[92]), gd::GdVal::from_str(&battle_string_literals[93]), gd::GdVal::from_str(&battle_string_literals[94]), gd::GdVal::from_str(&battle_string_literals[95]), gd::GdVal::from_str(&battle_string_literals[96]), gd::GdVal::from_str(&battle_string_literals[97]), gd::GdVal::from_str(&battle_string_literals[98]), gd::GdVal::from_str(&battle_string_literals[99]), gd::GdVal::from_str(&battle_string_literals[100]), gd::GdVal::from_str(&battle_string_literals[101]), gd::GdVal::from_str(&battle_string_literals[102]), gd::GdVal::from_str(&battle_string_literals[103]), gd::GdVal::from_str(&battle_string_literals[104]), gd::GdVal::from_str(&battle_string_literals[105]), gd::GdVal::from_str(&battle_string_literals[106]), gd::GdVal::from_str(&battle_string_literals[107]), gd::GdVal::from_str(&battle_string_literals[108]), gd::GdVal::from_str(&battle_string_literals[109]), gd::GdVal::from_str(&battle_string_literals[110]), gd::GdVal::from_str(&battle_string_literals[111]), gd::GdVal::from_str(&battle_string_literals[112]), gd::GdVal::from_str(&battle_string_literals[113]), gd::GdVal::from_str(&battle_string_literals[114]), gd::GdVal::from_str(&battle_string_literals[115]), gd::GdVal::from_str(&battle_string_literals[116]), gd::GdVal::from_str(&battle_string_literals[117]), gd::GdVal::from_str(&battle_string_literals[118]), gd::GdVal::from_str(&battle_string_literals[119]), gd::GdVal::from_str(&battle_string_literals[120]), gd::GdVal::from_str(&battle_string_literals[121]), gd::GdVal::from_str(&battle_string_literals[122]), gd::GdVal::from_str(&battle_string_literals[123]), gd::GdVal::from_str(&battle_string_literals[124]), gd::GdVal::from_str(&battle_string_literals[125])}));
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SpeakwithAnimals::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SpeakwithAnimals::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_petDescriptors_2525: out = this->f_petDescriptors; return true;
        case SYM_GEN_salesChance_2092: out = this->f_salesChance; return true;
        case SYM_GEN_pets_2524: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SpeakwithAnimals::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_petDescriptors_2525: this->f_petDescriptors = val; return true;
        case SYM_GEN_salesChance_2092: this->f_salesChance = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SpeakwithAnimals::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onSaleRoll_2093: return true;
        case SYM_GEN_getGatedDescriptor_956: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_getRelatedItems_459: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN_getRelatedItemHeight_700: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SpeakwithAnimals::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onSaleRoll_2093: out = fn_onSaleRoll(args, argc); return true;
        case SYM_GEN_getGatedDescriptor_956: out = fn_getGatedDescriptor(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getRelatedItems_459: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_700: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SpeakwithAnimals::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SpeakwithAnimals::fn_onSaleRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpeakwithAnimals::fn_getGatedDescriptor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rarity = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpeakwithAnimals::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(3LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpeakwithAnimals::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1806 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1807 = (_t1806.kind == gd::GdVal::Kind::Arr) ? _t1806.arr : nullptr;
        uint32_t _len__t1808 = _t1807 ? _t1807->len : 0u;
        for (uint32_t _t1808 = 0; _t1808 < _len__t1808; ++_t1808) {
            gd::GdVal lv_item = _t1807->data[_t1808];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_giveDoubleActivationChance_312, _ca, 1); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpeakwithAnimals::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {this->f_petDescriptors}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_flatten_1803, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpeakwithAnimals::fn_getRelatedItemColumns(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(6LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpeakwithAnimals::fn_getRelatedItemHeight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(100LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpeakwithAnimals::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_salesChance = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[126])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    {
        gd::GdVal _t1809 = gd::gd_iter_seq(gd_ctx.arena, Gd__gd_core_items__Exclusive__SpeakwithAnimals::get_static_const_or_enum(gd_ctx, SYM_GEN_pets_2524));
        gd::GdArr* _t1810 = (_t1809.kind == gd::GdVal::Kind::Arr) ? _t1809.arr : nullptr;
        uint32_t _len__t1811 = _t1810 ? _t1810->len : 0u;
        for (uint32_t _t1811 = 0; _t1811 < _len__t1811; ++_t1811) {
            gd::GdVal lv_pet = _t1810->data[_t1811];
            gd::GdVal lv_desc = ([&]() { gd::GdVal _ca[] = {lv_pet}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_desc, SYM_GEN_isReleased_1725, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_desc}; return gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, this->f_petDescriptors, gd::native_inline_call(gd_ctx, lv_desc, SYM_GEN_getRarity_236, nullptr, 0)), gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SpeakwithAnimals(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__SpeakwithAnimals>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,493u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpeakwithAnimals = {CLS_Gd__gd_core_items__Exclusive__SpeakwithAnimals, "SpeakwithAnimals", "res://gd_core_items/Exclusive/SpeakwithAnimals.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__SpeakwithAnimals, &Gd__gd_core_items__Exclusive__SpeakwithAnimals::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SpeakwithAnimals::call_static_fn};

void Gd__gd_core_items__Exclusive__StarofCourage::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_staminaReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__StarofCourage::meta() const { return &META_Gd__gd_core_items__Exclusive__StarofCourage; }
gd::GdVal Gd__gd_core_items__Exclusive__StarofCourage::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__StarofCourage::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__StarofCourage::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_staminaReduction_2013: out = this->f_staminaReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__StarofCourage::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaReduction_2013: this->f_staminaReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__StarofCourage::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__StarofCourage::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__StarofCourage::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__StarofCourage::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1812 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t1813 = (_t1812.kind == gd::GdVal::Kind::Arr) ? _t1812.arr : nullptr;
        uint32_t _len__t1814 = _t1813 ? _t1813->len : 0u;
        for (uint32_t _t1814 = 0; _t1814 < _len__t1814; ++_t1814) {
            gd::GdVal lv_item = _t1813->data[_t1814];
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isWeapon_82, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_staminaReduction}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeStaminaFactor_305, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StarofCourage::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_staminaReduction = gd::gd_neg(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[19])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__StarofCourage(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__StarofCourage>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,510u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StarofCourage = {CLS_Gd__gd_core_items__Exclusive__StarofCourage, "StarofCourage", "res://gd_core_items/Exclusive/StarofCourage.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__StarofCourage, &Gd__gd_core_items__Exclusive__StarofCourage::get_static_prop_fn, &Gd__gd_core_items__Exclusive__StarofCourage::call_static_fn};

void Gd__gd_core_items__Exclusive__ThornElemental::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_spikesLimit = gd::GdVal::null();
    this->f_spikes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ThornElemental::meta() const { return &META_Gd__gd_core_items__Exclusive__ThornElemental; }
gd::GdVal Gd__gd_core_items__Exclusive__ThornElemental::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ThornElemental::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ThornElemental::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_spikesLimit_2537: out = this->f_spikesLimit; return true;
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ThornElemental::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikesLimit_2537: this->f_spikesLimit = val; return true;
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ThornElemental::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ThornElemental::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ThornElemental::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ThornElemental::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(26LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThornElemental::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_spikesLimit}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeEffectSpikesLimit_1191, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_spikesLimit}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeRangedSpikesLimit_1190, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeSpikesCritChancePercent_1284, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThornElemental::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThornElemental::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_spikesLimit = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[127])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[128])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ThornElemental(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__ThornElemental>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,525u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ThornElemental = {CLS_Gd__gd_core_items__Exclusive__ThornElemental, "ThornElemental", "res://gd_core_items/Exclusive/ThornElemental.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__ThornElemental, &Gd__gd_core_items__Exclusive__ThornElemental::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ThornElemental::call_static_fn};

void Gd__gd_core_items__Exclusive__UniquelyUnique::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_boosted = gd::GdVal::from_int(0LL);
    this->f_baseSpeed = gd::GdVal::null();
    this->f_bonusSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__UniquelyUnique::meta() const { return &META_Gd__gd_core_items__Exclusive__UniquelyUnique; }
gd::GdVal Gd__gd_core_items__Exclusive__UniquelyUnique::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__UniquelyUnique::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__UniquelyUnique::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_boosted_2197: out = this->f_boosted; return true;
        case SYM_GEN_baseSpeed_2604: out = this->f_baseSpeed; return true;
        case SYM_GEN_bonusSpeed_1882: out = this->f_bonusSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__UniquelyUnique::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_boosted_2197: this->f_boosted = val; return true;
        case SYM_GEN_baseSpeed_2604: this->f_baseSpeed = val; return true;
        case SYM_GEN_bonusSpeed_1882: this->f_bonusSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__UniquelyUnique::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onBought_455: return true;
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onItemRoll_2018: return true;
        case SYM_GEN_onItemRolled_2019: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__UniquelyUnique::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onBought_455: out = fn_onBought(args, argc); return true;
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemRoll_2018: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_2019: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__UniquelyUnique::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__UniquelyUnique::fn_onBought(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_boosted = gd::GdVal::from_int(2LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UniquelyUnique::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_boosted;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UniquelyUnique::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_data, gd::GdVal::null())))) {
        this->f_boosted = lv_data;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UniquelyUnique::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UniquelyUnique::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getRarity_236, nullptr, 0), gd::GdVal::from_int(5LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[129])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isA_245, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[61])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isA_245, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UniquelyUnique::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_affectedItems = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, lv_affectedItems, gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_baseSpeed, gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, _ca, 1); })(), this->f_bonusSpeed))}; return gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, lv_affectedItems, gd::GdVal::from_int(0LL)), SYM_GEN_addSpeed_273, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UniquelyUnique::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UniquelyUnique::fn_onItemRolled(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_descr, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[61])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })())))) {
        this->f_boosted = gd::gd_sub(this->f_boosted, gd::GdVal::from_int(1LL));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UniquelyUnique::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_baseSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[16])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_bonusSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[18])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__UniquelyUnique(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__UniquelyUnique>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,542u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__UniquelyUnique = {CLS_Gd__gd_core_items__Exclusive__UniquelyUnique, "UniquelyUnique", "res://gd_core_items/Exclusive/UniquelyUnique.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__UniquelyUnique, &Gd__gd_core_items__Exclusive__UniquelyUnique::get_static_prop_fn, &Gd__gd_core_items__Exclusive__UniquelyUnique::call_static_fn};

void Gd__gd_core_items__Fanfare::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_options = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
}
const gd::GdClassMeta* Gd__gd_core_items__Fanfare::meta() const { return &META_Gd__gd_core_items__Fanfare; }
gd::GdVal Gd__gd_core_items__Fanfare::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Fanfare::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Fanfare::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_options_1876: out = this->f_options; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Fanfare::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_options_1876: this->f_options = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Fanfare::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Fanfare::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Fanfare::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Fanfare::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Fanfare::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_267, nullptr, 0), gd::GdVal::from_float(100.0)), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Fanfare::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rng = ([&]() { gd::GdVal _ca[] = {this->f_options}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_pickRandomElement_1746, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_rng, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_rng, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeMana_334, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drainStamina_117, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    (void)([&]() { gd::GdVal _ca[] = {lv_rng}; return gd::native_inline_call(gd_ctx, this->f_options, gd::SYM_erase, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Fanfare::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Fanfare(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Fanfare>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,559u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Fanfare = {CLS_Gd__gd_core_items__Fanfare, "Fanfare", "res://gd_core_items/Fanfare.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Fanfare, &Gd__gd_core_items__Fanfare::get_static_prop_fn, &Gd__gd_core_items__Fanfare::call_static_fn};

void Gd__gd_core_items__HealingHerbs::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__HealingHerbs::meta() const { return &META_Gd__gd_core_items__HealingHerbs; }
gd::GdVal Gd__gd_core_items__HealingHerbs::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__HealingHerbs::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__HealingHerbs::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__HealingHerbs::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__HealingHerbs::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__HealingHerbs::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__HealingHerbs::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__HealingHerbs::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_381, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HealingHerbs::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__HealingHerbs(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__HealingHerbs>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,579u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__HealingHerbs = {CLS_Gd__gd_core_items__HealingHerbs, "HealingHerbs", "res://gd_core_items/HealingHerbs.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__HealingHerbs, &Gd__gd_core_items__HealingHerbs::get_static_prop_fn, &Gd__gd_core_items__HealingHerbs::call_static_fn};

void Gd__gd_core_items__LuckyPiggy::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Piggybank::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__LuckyPiggy::meta() const { return &META_Gd__gd_core_items__LuckyPiggy; }
gd::GdVal Gd__gd_core_items__LuckyPiggy::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Piggybank::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__LuckyPiggy::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__LuckyPiggy::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Piggybank::get_prop(prop, out);
}
bool Gd__gd_core_items__LuckyPiggy::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Piggybank::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__LuckyPiggy::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_explodeRandomly_1921: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Piggybank::has_own_method(m);
}
bool Gd__gd_core_items__LuckyPiggy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_explodeRandomly_1921: out = fn_explodeRandomly(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Piggybank::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__LuckyPiggy::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Piggybank::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__LuckyPiggy::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canModifyChance_293, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyPiggy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1815 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1816 = (_t1815.kind == gd::GdVal::Kind::Arr) ? _t1815.arr : nullptr;
        uint32_t _len__t1817 = _t1816 ? _t1816->len : 0u;
        for (uint32_t _t1817 = 0; _t1817 < _len__t1817; ++_t1817) {
            gd::GdVal lv_item = _t1816->data[_t1817];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusChance_175, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyPiggy::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyPiggy::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::GdVal::from_int(1000LL), gd::GdVal::from_int(5LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyPiggy::fn_explodeRandomly(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyPiggy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Piggybank::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__LuckyPiggy(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__LuckyPiggy>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,598u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__LuckyPiggy = {CLS_Gd__gd_core_items__LuckyPiggy, "LuckyPiggy", "res://gd_core_items/LuckyPiggy.gd", &META_Gd__gd_core_items__Piggybank, true, _alloc_Gd__gd_core_items__LuckyPiggy, &Gd__gd_core_items__LuckyPiggy::get_static_prop_fn, &Gd__gd_core_items__LuckyPiggy::call_static_fn};

void Gd__gd_core_items__PoisonIvy::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_damageIncreaseActive = gd::GdVal::from_bool(false);
    this->f_activationParticles = gd::GdVal::null();
    this->f_poisonPerSpike = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__PoisonIvy::meta() const { return &META_Gd__gd_core_items__PoisonIvy; }
gd::GdVal Gd__gd_core_items__PoisonIvy::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__PoisonIvy::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__PoisonIvy::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_damageIncreaseActive_1963: out = this->f_damageIncreaseActive; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_poisonPerSpike_1964: out = this->f_poisonPerSpike; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__PoisonIvy::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damageIncreaseActive_1963: this->f_damageIncreaseActive = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_poisonPerSpike_1964: this->f_poisonPerSpike = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__PoisonIvy::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onSpikesChanged_944: return true;
        case SYM_GEN_onOpponentPoisonChanged_1831: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__PoisonIvy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onSpikesChanged_944: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN_onOpponentPoisonChanged_1831: out = fn_onOpponentPoisonChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__PoisonIvy::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__PoisonIvy::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(26LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonIvy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[130]), gd::GdVal::from_str(&battle_string_literals[131])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[132]), gd::GdVal::from_str(&battle_string_literals[133])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDebuffResistChances_1220, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonIvy::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, this->f_poisonPerSpike), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 2); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonIvy::fn_onOpponentPoisonChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_curPoison = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getPoison_1229, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_damageIncreaseActive))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_curPoison, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(false), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonIvy::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonIvy::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv_active)) {
    }
    else {
    }
    this->f_damageIncreaseActive = lv_active;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonIvy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_poisonPerSpike = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__PoisonIvy(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__PoisonIvy>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,617u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__PoisonIvy = {CLS_Gd__gd_core_items__PoisonIvy, "PoisonIvy", "res://gd_core_items/PoisonIvy.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__PoisonIvy, &Gd__gd_core_items__PoisonIvy::get_static_prop_fn, &Gd__gd_core_items__PoisonIvy::call_static_fn};

void Gd__gd_core_items__SteelGoobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Goobert::init_fields(gd_ctx);
    this->f_affectedWeapons = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
}
const gd::GdClassMeta* Gd__gd_core_items__SteelGoobert::meta() const { return &META_Gd__gd_core_items__SteelGoobert; }
gd::GdVal Gd__gd_core_items__SteelGoobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__SteelGoobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__SteelGoobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_affectedWeapons_1985: out = this->f_affectedWeapons; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__SteelGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedWeapons_1985: this->f_affectedWeapons = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__SteelGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__SteelGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__SteelGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__SteelGoobert::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__SteelGoobert::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1818 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, _ca, 1); })());
        gd::GdArr* _t1819 = (_t1818.kind == gd::GdVal::Kind::Arr) ? _t1818.arr : nullptr;
        uint32_t _len__t1820 = _t1819 ? _t1819->len : 0u;
        for (uint32_t _t1820 = 0; _t1820 < _len__t1820; ++_t1820) {
            gd::GdVal lv_item = _t1819->data[_t1820];
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, this->f_affectedWeapons, gd::SYM_push_back, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__SteelGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1821 = gd::gd_iter_seq(gd_ctx.arena, this->f_affectedWeapons);
        gd::GdArr* _t1822 = (_t1821.kind == gd::GdVal::Kind::Arr) ? _t1821.arr : nullptr;
        uint32_t _len__t1823 = _t1822 ? _t1822->len : 0u;
        for (uint32_t _t1823 = 0; _t1823 < _len__t1823; ++_t1823) {
            gd::GdVal lv_item = _t1822->data[_t1823];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__SteelGoobert::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_affectedWeapons, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__SteelGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__SteelGoobert(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__SteelGoobert>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,639u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__SteelGoobert = {CLS_Gd__gd_core_items__SteelGoobert, "SteelGoobert", "res://gd_core_items/SteelGoobert.gd", &META_Gd__gd_core_items__Goobert, true, _alloc_Gd__gd_core_items__SteelGoobert, &Gd__gd_core_items__SteelGoobert::get_static_prop_fn, &Gd__gd_core_items__SteelGoobert::call_static_fn};

void Gd__gd_core_items__WalrusTusk::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__WalrusTusk::meta() const { return &META_Gd__gd_core_items__WalrusTusk; }
gd::GdVal Gd__gd_core_items__WalrusTusk::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__WalrusTusk::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__WalrusTusk::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__WalrusTusk::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__WalrusTusk::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__WalrusTusk::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__WalrusTusk::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__WalrusTusk::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_381, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__WalrusTusk::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__WalrusTusk(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__WalrusTusk>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,657u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__WalrusTusk = {CLS_Gd__gd_core_items__WalrusTusk, "WalrusTusk", "res://gd_core_items/WalrusTusk.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__WalrusTusk, &Gd__gd_core_items__WalrusTusk::get_static_prop_fn, &Gd__gd_core_items__WalrusTusk::call_static_fn};
