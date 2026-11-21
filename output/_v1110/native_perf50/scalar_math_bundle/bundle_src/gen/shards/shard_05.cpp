#include "../../native_inline_dispatch.hpp"
#include "../../native_scalar_equal.hpp"
#include "../../native_array_index.hpp"
#include "../../native_event_kernel.hpp"
#include "../../gd_rt.hpp"
extern bool gd_native_character_snapshots_are_noop(const gd::GdVal& context);
#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core__AcornCollar.hpp"
#include "../hdrs/Gd__gd_core__Blueberries.hpp"
#include "../hdrs/Gd__gd_core__CoreCombatLog.hpp"
#include "../hdrs/Gd__gd_core__CoreRng__INNER__BalancedRange.hpp"
#include "../hdrs/Gd__gd_core__CoreRng.hpp"
#include "../hdrs/Gd__gd_core__Potion.hpp"
#include "../hdrs/Gd__gd_core__GlovesofHaste.hpp"
#include "../hdrs/Gd__gd_core__LeatherArmor.hpp"
#include "../hdrs/Gd__gd_core__MrStruggles.hpp"
#include "../hdrs/Gd__gd_core__Pumpkin.hpp"
#include "../hdrs/Gd__gd_core__Stone.hpp"
#include "../hdrs/Gd__gd_core__ThornWhip.hpp"
#include "../hdrs/Gd__gd_core_items__AcornCollar.hpp"
#include "../hdrs/Gd__gd_core_items__BoxofRiches.hpp"
#include "../hdrs/Gd__gd_core_items__DarkestLotus.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__AmuletofFortune.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ArtifactStoneDeath.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BismuthCube.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BurningSword.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Chess__BlackKnight.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__CogBadge.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DevouringSphere.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__EchoingBattlecry.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Fedora.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__FrozenBuckler.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Hedgehog.hpp"
#include "../hdrs/Gd__gd_core_items__RibSawBlade.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__LuckyShortbow.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MoltenDagger.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Phoenix.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PrismaticWand.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__RandomLoadoutBag.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Scissorswords.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SmithingForDummies.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SpikedStaff.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__StrongDivinePotion.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ToastGoobert.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Whetstone3.hpp"
#include "../hdrs/Gd__gd_core_items__Gems__LumpofCoal.hpp"
#include "../hdrs/Gd__gd_core_items__HolySpear.hpp"
#include "../hdrs/Gd__gd_core_items__Pandamonium.hpp"
#include "../hdrs/Gd__gd_core_items__RubyChonk.hpp"
#include "../hdrs/Gd__gd_core_items__TheLovers.hpp"

namespace {
constexpr gd::GdStr battle_string_literals[] = {
    {"character_lucky_changed", 23u, 2259242176u},
    {"onLuckyChanged", 14u, 1760969932u},
    {"Mananana", 8u, 62091374u},
    {"damage", 6u, 1508461632u},
    {"amount", 6u, 4152741449u},
    {"used", 4u, 1786277552u},
    {"reflected", 9u, 3405838907u},
    {"duration", 8u, 799079693u},
    {"timeout", 7u, 2549515144u},
    {"resisted", 8u, 1836039126u},
    {"protected", 9u, 508850813u},
    {"stamina", 7u, 3875003702u},
    {"item", 4u, 2671260646u},
    {"health", 6u, 1805184399u},
    {"isPercent", 9u, 918779786u},
    {"type", 4u, 1361572173u},
    {"randi_range", 11u, 488468259u},
    {"potion_triggered", 16u, 729283976u},
    {"potion_emptied", 14u, 70999789u},
    {"Mrs Struggles", 13u, 3720174819u},
    {"Miss Fortune", 12u, 2446127352u},
    {"onDebuffed", 10u, 562402695u},
    {"character_damaged", 17u, 745527748u},
    {"onDamaged", 9u, 2303747743u},
    {"dur_speed", 9u, 1036633528u},
    {"", 0u, 2166136261u},
    {"SpeedbuffTimer", 14u, 437591678u},
    {"onSpeedbuffTimeout", 18u, 4061665073u},
    {"fatigue_start", 13u, 1129723937u},
    {"onFatigueStarted", 16u, 504449962u},
    {"dur_stun", 8u, 1388942617u},
    {"heat", 4u, 577319571u},
    {"character_spikes_changed", 24u, 3463900413u},
    {"onSpikesChanged", 15u, 3715123341u},
    {",", 1u, 688690635u},
    {"chance", 6u, 2459084481u},
    {"buffs", 5u, 2149256365u},
    {"fatigue_damage_changed", 22u, 2103754981u},
    {"onFatigueDamageChanged", 22u, 4187265744u},
    {"onBuffsChanged", 14u, 1288163266u},
    {"max", 3u, 3617776409u},
    {"character_heat_changed", 22u, 2413560104u},
    {"onHeatChanged", 13u, 775078454u},
    {"vampirism", 9u, 773404377u},
    {"charge_emitted", 14u, 395874890u},
    {"dur", 3u, 3509645056u},
    {"speed", 5u, 2072037248u},
    {"speed2", 6u, 498752822u},
    {"Cog", 3u, 1243110080u},
    {"character_cold_changed", 22u, 3066049132u},
    {"onOpponentColdChanged", 21u, 3656074605u},
    {"character_blind_changed", 23u, 2628032727u},
    {"onOpponentBlindChanged", 22u, 4206373648u},
    {"lifesteal", 9u, 1515578962u},
    {"speed_blind", 11u, 1879357596u},
    {"speed_cold", 10u, 115977751u},
    {"dam", 3u, 4031722721u},
    {"@", 1u, 3305896031u},
    {"Exclusive/EchoingBattlecry.gd:14", 32u, 2214288675u},
    {"EBARR", 5u, 2502617925u},
    {"ot", 2u, 1530144350u},
    {"luck", 4u, 4145017712u},
    {"luck2", 5u, 807137510u},
    {"luckt", 5u, 4061892428u},
    {"spikes", 6u, 439106706u},
    {"dam_spikes", 10u, 1180426837u},
    {"healtht", 7u, 1555997217u},
    {"bonusdam", 8u, 3306431450u},
    {"selfdam", 7u, 2790126895u},
    {"reincarnate_health", 18u, 2456985760u},
    {"manat", 5u, 126091098u},
    {"regent", 6u, 4290639402u},
    {"empower", 7u, 2037162760u},
    {"use", 3u, 1469170932u},
    {"Ranger Bag", 10u, 743242342u},
    {"Vineweave Basket", 16u, 2633978233u},
    {"Storage Coffin", 14u, 3989679071u},
    {"Relic Case", 10u, 2514799320u},
    {"Fire Pit", 8u, 2502778388u},
    {"Portable Altar", 14u, 2268932890u},
    {"Berserker Bag", 13u, 2477068292u},
    {"Toolbox", 7u, 597333304u},
    {"Scholar Bag", 11u, 2862919283u},
    {"Puzzlebox", 9u, 3354515146u},
    {"Bag of Giving", 13u, 4233879148u},
    {"Sewing Case", 11u, 2327584018u},
    {"Engineer Box", 12u, 2990726433u},
    {"Engineer Bag 2", 14u, 695622072u},
    {"Acorn Collar", 12u, 982085103u},
    {"Unstable Recombobulator", 23u, 2655714527u},
    {"Draconic Orb", 12u, 2484959023u},
    {"Stone Skin Potion", 17u, 2812583478u},
    {"Divine Potion", 13u, 110771253u},
    {"createRevealParticles", 21u, 2275131827u},
    {"regen", 5u, 16724762u},
    {"Whetstone", 9u, 3932146392u},
    {"mana", 4u, 3650585354u},
    {"staminat", 8u, 3660664550u},
    {"blockfactor", 11u, 4227576901u},
    {"pre_deal_damage_early", 21u, 2143897571u},
    {"preAttack", 9u, 3919347442u},
    {"character_mana_changed", 22u, 798563205u},
    {"checkTrigger", 12u, 3751686889u},
    {"character_invulnerable_end", 26u, 3350240732u},
    {"onInvuEnded", 11u, 2135122486u},
    {"dur_invu", 8u, 277695711u},
    {"BuffTimer", 9u, 194754125u},
    {"buffEnded", 9u, 3457903416u},
    {"activated", 9u, 2866667388u},
    {"onFoodActivated", 15u, 3933616099u},
    {"healamp", 7u, 54482251u},
};
}

void Gd__gd_core__AcornCollar::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__RangerCollar::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__AcornCollar::meta() const { return &META_Gd__gd_core__AcornCollar; }
gd::GdVal Gd__gd_core__AcornCollar::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__RangerCollar::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__AcornCollar::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__AcornCollar::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__RangerCollar::get_prop(prop, out);
}
bool Gd__gd_core__AcornCollar::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__RangerCollar::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__AcornCollar::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onLuckyChanged_901: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__RangerCollar::has_own_method(m);
}
bool Gd__gd_core__AcornCollar::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onLuckyChanged_901: out = fn_onLuckyChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__RangerCollar::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__AcornCollar::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__RangerCollar::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__AcornCollar::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canDamage_89, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__AcornCollar::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_affectedItems, gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[0]), gd::GdVal::from_str(&battle_string_literals[1])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__AcornCollar::fn_onLuckyChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    {
        gd::GdVal _t954 = gd::gd_iter_seq(gd_ctx.arena, this->f_affectedItems);
        gd::GdArr* _t955 = (_t954.kind == gd::GdVal::Kind::Arr) ? _t954.arr : nullptr;
        uint32_t _len__t956 = _t955 ? _t955->len : 0u;
        for (uint32_t _t956 = 0; _t956 < _len__t956; ++_t956) {
            gd::GdVal lv_item = _t955->data[_t956];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_numeric_mul(lv_amount, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0))}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeCritChancePercent_181, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__AcornCollar::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__RangerCollar::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__AcornCollar(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__AcornCollar>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,1u); return object; }
const gd::GdClassMeta META_Gd__gd_core__AcornCollar = {CLS_Gd__gd_core__AcornCollar, "AcornCollar", "res://gd_core/AcornCollar.gd", &META_Gd__gd_core__RangerCollar, false, _alloc_Gd__gd_core__AcornCollar, &Gd__gd_core__AcornCollar::get_static_prop_fn, &Gd__gd_core__AcornCollar::call_static_fn};

void Gd__gd_core__Blueberries::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Food::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__Blueberries::meta() const { return &META_Gd__gd_core__Blueberries; }
gd::GdVal Gd__gd_core__Blueberries::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Blueberries::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Blueberries::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Food::get_prop(prop, out);
}
bool Gd__gd_core__Blueberries::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Blueberries::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Food::has_own_method(m);
}
bool Gd__gd_core__Blueberries::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Blueberries::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Blueberries::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_overflow = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_capped_335, _ca, 2); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_overflow, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Blueberries::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Blueberries(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__Blueberries>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,11u); return object; }
const gd::GdClassMeta META_Gd__gd_core__Blueberries = {CLS_Gd__gd_core__Blueberries, "Blueberries", "res://gd_core/Blueberries.gd", &META_Gd__gd_core__Food, false, _alloc_Gd__gd_core__Blueberries, &Gd__gd_core__Blueberries::get_static_prop_fn, &Gd__gd_core__Blueberries::call_static_fn};

void Gd__gd_core__CoreCombatLog::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_eventNum = gd::GdVal::from_int(0LL);
    this->f__ctx = gd::GdVal::null();
    this->f__mananana_log_rows = gd::GdVal::null();
    this->f__written_log_rows = gd::GdVal::from_int(0LL);
    this->f__previous_written_log_rows = gd::GdVal::from_int(0LL);
    this->f__rendered_log_rows = gd::GdVal::from_int(0LL);
    this->f__next_mananana_log_row = gd::GdVal::from_int(0LL);
}
const gd::GdClassMeta* Gd__gd_core__CoreCombatLog::meta() const { return &META_Gd__gd_core__CoreCombatLog; }
gd::GdVal Gd__gd_core__CoreCombatLog::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreCombatLog::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreCombatLog::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_eventNum_1346: out = this->f_eventNum; return true;
        case SYM_GEN__ctx_1347: out = this->f__ctx; return true;
        case SYM_GEN__mananana_log_rows_1348: out = this->f__mananana_log_rows; return true;
        case SYM_GEN__written_log_rows_1349: out = this->f__written_log_rows; return true;
        case SYM_GEN__previous_written_log_rows_1350: out = this->f__previous_written_log_rows; return true;
        case SYM_GEN__rendered_log_rows_1351: out = this->f__rendered_log_rows; return true;
        case SYM_GEN__next_mananana_log_row_1352: out = this->f__next_mananana_log_row; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreCombatLog::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_eventNum_1346: this->f_eventNum = val; return true;
        case SYM_GEN__ctx_1347: this->f__ctx = val; return true;
        case SYM_GEN__mananana_log_rows_1348: this->f__mananana_log_rows = val; return true;
        case SYM_GEN__written_log_rows_1349: this->f__written_log_rows = val; return true;
        case SYM_GEN__previous_written_log_rows_1350: this->f__previous_written_log_rows = val; return true;
        case SYM_GEN__rendered_log_rows_1351: this->f__rendered_log_rows = val; return true;
        case SYM_GEN__next_mananana_log_row_1352: this->f__next_mananana_log_row = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreCombatLog::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getTimeStamp_1353: return true;
        case SYM_GEN_createEvent_1354: return true;
        case SYM_GEN_prepareHiddenLog_1355: return true;
        case SYM_GEN_replayHiddenLogEvent_1356: return true;
        case SYM_GEN_logEvent_1357: return true;
        case SYM_GEN_createEvent_Attack_1358: return true;
        case SYM_GEN_createEvent_Damage_1359: return true;
        case SYM_GEN_createEvent_Heal_1360: return true;
        case SYM_GEN_createEvent_LoseHealth_1361: return true;
        case SYM_GEN_createEvent_Stack_1362: return true;
        case SYM_GEN_createEvent_StackTemporary_1363: return true;
        case SYM_GEN_createEvent_StackTimeout_1364: return true;
        case SYM_GEN_createEvent_StackResistOrNullify_1365: return true;
        case SYM_GEN_createEvent_StackProtect_1366: return true;
        case SYM_GEN_createEvent_Stun_1367: return true;
        case SYM_GEN_createEvent_StunResist_1368: return true;
        case SYM_GEN_createEvent_InvulnerableStart_1369: return true;
        case SYM_GEN_createEvent_InvulnerableEnd_1370: return true;
        case SYM_GEN_createEvent_Stamina_1371: return true;
        case SYM_GEN_createEvent_DrainStamina_1372: return true;
        case SYM_GEN_createEvent_OutOfStamina_1373: return true;
        case SYM_GEN_createEvent_DamageBuff_1374: return true;
        case SYM_GEN_createEvent_TemporaryMaxHealth_1375: return true;
        case SYM_GEN_createEvent_TemporaryMaxStamina_1376: return true;
        case SYM_GEN_createEvent_BattleRageStart_1377: return true;
        case SYM_GEN_createEvent_BattleRageEnd_1378: return true;
        case SYM_GEN_createEvent_Reincarnate_1379: return true;
        case SYM_GEN_createEvent_Activation_1380: return true;
        case SYM_GEN_createEvent_DamChange_1381: return true;
        case SYM_GEN_snapshotMetric_1382: return true;
        case SYM_GEN_snapshotItemMetric_1383: return true;
        case SYM_GEN_snapshotItemTooltipStat_1384: return true;
        case SYM_GEN_snapshotItemState_1385: return true;
        case SYM_GEN_snapshotGlobalStat_1386: return true;
        case SYM_GEN_snapshotCharacterStat_1387: return true;
        case SYM_GEN_snapshotStack_1388: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreCombatLog::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getTimeStamp_1353: out = fn_getTimeStamp(args, argc); return true;
        case SYM_GEN_createEvent_1354: out = fn_createEvent(args, argc); return true;
        case SYM_GEN_prepareHiddenLog_1355: out = fn_prepareHiddenLog(args, argc); return true;
        case SYM_GEN_replayHiddenLogEvent_1356: out = fn_replayHiddenLogEvent(args, argc); return true;
        case SYM_GEN_logEvent_1357: out = fn_logEvent(args, argc); return true;
        case SYM_GEN_createEvent_Attack_1358: out = fn_createEvent_Attack(args, argc); return true;
        case SYM_GEN_createEvent_Damage_1359: out = fn_createEvent_Damage(args, argc); return true;
        case SYM_GEN_createEvent_Heal_1360: out = fn_createEvent_Heal(args, argc); return true;
        case SYM_GEN_createEvent_LoseHealth_1361: out = fn_createEvent_LoseHealth(args, argc); return true;
        case SYM_GEN_createEvent_Stack_1362: out = fn_createEvent_Stack(args, argc); return true;
        case SYM_GEN_createEvent_StackTemporary_1363: out = fn_createEvent_StackTemporary(args, argc); return true;
        case SYM_GEN_createEvent_StackTimeout_1364: out = fn_createEvent_StackTimeout(args, argc); return true;
        case SYM_GEN_createEvent_StackResistOrNullify_1365: out = fn_createEvent_StackResistOrNullify(args, argc); return true;
        case SYM_GEN_createEvent_StackProtect_1366: out = fn_createEvent_StackProtect(args, argc); return true;
        case SYM_GEN_createEvent_Stun_1367: out = fn_createEvent_Stun(args, argc); return true;
        case SYM_GEN_createEvent_StunResist_1368: out = fn_createEvent_StunResist(args, argc); return true;
        case SYM_GEN_createEvent_InvulnerableStart_1369: out = fn_createEvent_InvulnerableStart(args, argc); return true;
        case SYM_GEN_createEvent_InvulnerableEnd_1370: out = fn_createEvent_InvulnerableEnd(args, argc); return true;
        case SYM_GEN_createEvent_Stamina_1371: out = fn_createEvent_Stamina(args, argc); return true;
        case SYM_GEN_createEvent_DrainStamina_1372: out = fn_createEvent_DrainStamina(args, argc); return true;
        case SYM_GEN_createEvent_OutOfStamina_1373: out = fn_createEvent_OutOfStamina(args, argc); return true;
        case SYM_GEN_createEvent_DamageBuff_1374: out = fn_createEvent_DamageBuff(args, argc); return true;
        case SYM_GEN_createEvent_TemporaryMaxHealth_1375: out = fn_createEvent_TemporaryMaxHealth(args, argc); return true;
        case SYM_GEN_createEvent_TemporaryMaxStamina_1376: out = fn_createEvent_TemporaryMaxStamina(args, argc); return true;
        case SYM_GEN_createEvent_BattleRageStart_1377: out = fn_createEvent_BattleRageStart(args, argc); return true;
        case SYM_GEN_createEvent_BattleRageEnd_1378: out = fn_createEvent_BattleRageEnd(args, argc); return true;
        case SYM_GEN_createEvent_Reincarnate_1379: out = fn_createEvent_Reincarnate(args, argc); return true;
        case SYM_GEN_createEvent_Activation_1380: out = fn_createEvent_Activation(args, argc); return true;
        case SYM_GEN_createEvent_DamChange_1381: out = fn_createEvent_DamChange(args, argc); return true;
        case SYM_GEN_snapshotMetric_1382: out = fn_snapshotMetric(args, argc); return true;
        case SYM_GEN_snapshotItemMetric_1383: out = fn_snapshotItemMetric(args, argc); return true;
        case SYM_GEN_snapshotItemTooltipStat_1384: out = fn_snapshotItemTooltipStat(args, argc); return true;
        case SYM_GEN_snapshotItemState_1385: out = fn_snapshotItemState(args, argc); return true;
        case SYM_GEN_snapshotGlobalStat_1386: out = fn_snapshotGlobalStat(args, argc); return true;
        case SYM_GEN_snapshotCharacterStat_1387: out = fn_snapshotCharacterStat(args, argc); return true;
        case SYM_GEN_snapshotStack_1388: out = fn_snapshotStack(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreCombatLog::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_getTimeStamp(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    return native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_combat_time>(gd_ctx, this->f__ctx, SYM_GEN_combat_time_1306);
    return gd::GdVal::null();
    }
    return gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_combat_time_1306);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
        ++gd_ctx.native_event_counts[3];
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_origin = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_type = (_argc > 2) ? _args[2] : gd::GdVal::null();
    this->f_eventNum = gd::native_numeric_add(gd_ctx, this->f_eventNum, gd::GdVal::from_int(1LL));
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_eventNum, this->fn_getTimeStamp(nullptr, 0), lv_triggerEvent, lv_origin, lv_type}; return native_event_new<Gd__gd_core__CoreEvent>(gd_ctx, _ca, 5); })();
    if (!gd_native_character_snapshots_are_noop(this->f__ctx)) {
        gd::GdVal _t957 = gd::gd_iter_seq(gd_ctx.arena, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_player>(gd_ctx, this->f__ctx, SYM_GEN_player_1302), native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_opponent>(gd_ctx, this->f__ctx, SYM_GEN_opponent_75)})));
        gd::GdArr* _t958 = (_t957.kind == gd::GdVal::Kind::Arr) ? _t957.arr : nullptr;
        uint32_t _len__t959 = _t958 ? _t958->len : 0u;
        for (uint32_t _t959 = 0; _t959 < _len__t959; ++_t959) {
            gd::GdVal lv_character = _t958->data[_t959];
            (void)([&]() { gd::GdVal _ca[] = {lv_character, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_Stat_870), SYM_GEN_Stamina_2673)}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
        }
    }
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_origin = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_type = (_argc > 2) ? _args[2] : gd::GdVal::null();
    this->f_eventNum = gd::native_numeric_add(gd_ctx, this->f_eventNum, gd::GdVal::from_int(1LL));
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_eventNum, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getTimeStamp_1353, nullptr, 0), lv_triggerEvent, lv_origin, lv_type}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEvent), gd::SYM_new, _ca, 5); })();
    if (!gd_native_character_snapshots_are_noop(this->f__ctx)) {
        gd::GdVal _t957 = gd::gd_iter_seq(gd_ctx.arena, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_player_1302), gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_opponent_75)})));
        gd::GdArr* _t958 = (_t957.kind == gd::GdVal::Kind::Arr) ? _t957.arr : nullptr;
        uint32_t _len__t959 = _t958 ? _t958->len : 0u;
        for (uint32_t _t959 = 0; _t959 < _len__t959; ++_t959) {
            gd::GdVal lv_character = _t958->data[_t959];
            (void)([&]() { gd::GdVal _ca[] = {lv_character, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_Stat_870), SYM_GEN_Stamina_2673)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
        }
    }
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_prepareHiddenLog(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_items = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f__mananana_log_rows = gd::GdVal::null();
    this->f__written_log_rows = gd::GdVal::from_int(0LL);
    this->f__previous_written_log_rows = gd::GdVal::from_int(0LL);
    this->f__rendered_log_rows = gd::GdVal::from_int(0LL);
    this->f__next_mananana_log_row = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t960 = gd::gd_iter_seq(gd_ctx.arena, lv_items);
        gd::GdArr* _t961 = (_t960.kind == gd::GdVal::Kind::Arr) ? _t960.arr : nullptr;
        uint32_t _len__t962 = _t961 ? _t961->len : 0u;
        for (uint32_t _t962 = 0; _t962 < _len__t962; ++_t962) {
            gd::GdVal lv_item = _t961->data[_t962];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673), gd::GdVal::from_str(&battle_string_literals[2]))))) {
                this->f__mananana_log_rows = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
                return gd::GdVal::from_bool(true);
            }
        }
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_replayHiddenLogEvent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f__previous_written_log_rows, this->f__written_log_rows))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f__rendered_log_rows, this->f__written_log_rows)))) : gd::GdVal::from_bool(false)))) {
        this->f__rendered_log_rows = gd::native_numeric_add(gd_ctx, this->f__rendered_log_rows, gd::GdVal::from_int(1LL));
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f__next_mananana_log_row, gd::native_inline_call(gd_ctx, this->f__mananana_log_rows, gd::SYM_size, nullptr, 0)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_array_index(gd_ctx, this->f__mananana_log_rows, this->f__next_mananana_log_row), this->f__rendered_log_rows)))) : gd::GdVal::from_bool(false)))) {
            this->f__next_mananana_log_row = gd::native_numeric_add(gd_ctx, this->f__next_mananana_log_row, gd::GdVal::from_int(1LL));
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.001)}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_flip>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN_flip_1735, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), gd::GdVal::from_int(3LL)}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_randi_range>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), gd::SYM_randi_range, _ca, 2); })();
            }
        }
    }
    this->f__previous_written_log_rows = this->f__written_log_rows;
    return gd::GdVal::null();
    }
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f__previous_written_log_rows, this->f__written_log_rows))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f__rendered_log_rows, this->f__written_log_rows)))) : gd::GdVal::from_bool(false)))) {
        this->f__rendered_log_rows = gd::native_numeric_add(gd_ctx, this->f__rendered_log_rows, gd::GdVal::from_int(1LL));
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f__next_mananana_log_row, gd::native_inline_call(gd_ctx, this->f__mananana_log_rows, gd::SYM_size, nullptr, 0)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_array_index(gd_ctx, this->f__mananana_log_rows, this->f__next_mananana_log_row), this->f__rendered_log_rows)))) : gd::GdVal::from_bool(false)))) {
            this->f__next_mananana_log_row = gd::native_numeric_add(gd_ctx, this->f__next_mananana_log_row, gd::GdVal::from_int(1LL));
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.001)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), SYM_GEN_flip_1735, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), gd::GdVal::from_int(3LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1406), gd::SYM_randi_range, _ca, 2); })();
            }
        }
    }
    this->f__previous_written_log_rows = this->f__written_log_rows;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_logEvent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f__mananana_log_rows, gd::GdVal::null())))) {
        this->f__written_log_rows = gd::native_numeric_add(gd_ctx, this->f__written_log_rows, gd::GdVal::from_int(1LL));
        gd::GdVal lv_origin = gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getOrigin_1580, nullptr, 0);
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_inline_is_type(gd_ctx, lv_origin, &META_Gd__gd_core__CoreItem))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_origin, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673), gd::GdVal::from_str(&battle_string_literals[2]))))) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f__written_log_rows}; return gd::native_inline_call(gd_ctx, this->f__mananana_log_rows, gd::SYM_push_back, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_logEvent_1357, _ca, 1); })();
    return gd::GdVal::null();
    }
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f__mananana_log_rows, gd::GdVal::null())))) {
        this->f__written_log_rows = gd::native_numeric_add(gd_ctx, this->f__written_log_rows, gd::GdVal::from_int(1LL));
        gd::GdVal lv_origin = gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getOrigin_1580, nullptr, 0);
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_inline_is_type(gd_ctx, lv_origin, &META_Gd__gd_core__CoreItem))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_origin, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673), gd::GdVal::from_str(&battle_string_literals[2]))))) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f__written_log_rows}; return gd::native_inline_call(gd_ctx, this->f__mananana_log_rows, gd::SYM_push_back, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_logEvent_1357, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_Attack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_event = gd::GdVal::null();
    gd::GdVal lv_origin = native_event_get<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::f_origin>(gd_ctx, native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damageSource>(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_origin_1546);
    gd::GdVal lv_character = gd::native_inline_call(gd_ctx, lv_origin, SYM_GEN_character_74, nullptr, 0);
    if (gd::gd_truth(native_event_call<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::fn_hasHit>(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        if (gd::gd_truth(native_event_call<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::fn_wasCriticalHit>(gd_ctx, lv_damageRes, SYM_GEN_wasCriticalHit_1524, nullptr, 0))) {
            lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_origin, gd::GdVal::from_int(2LL)}; return this->fn_createEvent(_ca, 3); })();
        }
        else {
            lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_origin, gd::GdVal::from_int(1LL)}; return this->fn_createEvent(_ca, 3); })();
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[3]), native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damage>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518)}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
        gd::GdVal lv_attackedCharacter = gd::GdVal::null();
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_SelfDamage_2837)}; return native_event_call<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::fn_hasType>(gd_ctx, native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damageSource>(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_hasType_79, _ca, 1); })())) {
            lv_attackedCharacter = lv_character;
        }
        else {
            lv_attackedCharacter = native_event_get<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::f_opponent>(gd_ctx, lv_character, SYM_GEN_opponent_75);
        }
        (void)([&]() { gd::GdVal _ca[] = {lv_attackedCharacter, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_Stat_870), SYM_GEN_Health_2787)}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_attackedCharacter, gd::GdVal::from_int(100LL)}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotStack_1388, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {native_event_get<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::f_playerId>(gd_ctx, lv_character, SYM_GEN_playerId_1046), gd::native_array_index(gd_ctx, native_event_get<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::f_types>(gd_ctx, native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damageSource>(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_types_1544), gd::GdVal::from_int(0LL)), native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damage>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518)}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotDamageDealt_1645, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {native_event_get<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::f_playerId>(gd_ctx, lv_character, SYM_GEN_playerId_1046), lv_event}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_updateDamageMeter_1646, _ca, 2); })();
    }
    else {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_origin, gd::GdVal::from_int(3LL)}; return this->fn_createEvent(_ca, 3); })();
    }
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_event = gd::GdVal::null();
    gd::GdVal lv_origin = gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_origin_1546);
    gd::GdVal lv_character = gd::native_inline_call(gd_ctx, lv_origin, SYM_GEN_character_74, nullptr, 0);
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_wasCriticalHit_1524, nullptr, 0))) {
            lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_origin, gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
        }
        else {
            lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_origin, gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[3]), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518)}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
        gd::GdVal lv_attackedCharacter = gd::GdVal::null();
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_SelfDamage_2837)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_hasType_79, _ca, 1); })())) {
            lv_attackedCharacter = lv_character;
        }
        else {
            lv_attackedCharacter = gd::native_inline_get_prop(gd_ctx, lv_character, SYM_GEN_opponent_75);
        }
        (void)([&]() { gd::GdVal _ca[] = {lv_attackedCharacter, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_Stat_870), SYM_GEN_Health_2787)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_attackedCharacter, gd::GdVal::from_int(100LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotStack_1388, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, lv_character, SYM_GEN_playerId_1046), gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_types_1544), gd::GdVal::from_int(0LL)), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotDamageDealt_1645, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, lv_character, SYM_GEN_playerId_1046), lv_event}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_updateDamageMeter_1646, _ca, 2); })();
    }
    else {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_origin, gd::GdVal::from_int(3LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    }
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_Damage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_damagingPlayerId = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_event = gd::GdVal::null();
    if (gd::gd_truth(native_event_call<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::fn_wasCriticalHit>(gd_ctx, lv_damageRes, SYM_GEN_wasCriticalHit_1524, nullptr, 0))) {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, gd::native_array_index(gd_ctx, native_event_get<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::f_types>(gd_ctx, native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damageSource>(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_types_1544), gd::GdVal::from_int(0LL)), gd::GdVal::from_int(2LL)}; return this->fn_createEvent(_ca, 3); })();
    }
    else {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, gd::native_array_index(gd_ctx, native_event_get<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::f_types>(gd_ctx, native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damageSource>(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_types_1544), gd::GdVal::from_int(0LL)), gd::GdVal::from_int(1LL)}; return this->fn_createEvent(_ca, 3); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[3]), native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damage>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518)}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_damagingPlayerId}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setTarget>(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    gd::GdVal lv_damagingCharacter = ([&]() { gd::GdVal _ca[] = {lv_damagingPlayerId}; return native_event_call<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::fn_getCharacterFromId>(gd_ctx, this->f__ctx, SYM_GEN_getCharacterFromId_1476, _ca, 1); })();
    gd::GdVal lv_damagedCharacter = native_event_get<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::f_opponent>(gd_ctx, lv_damagingCharacter, SYM_GEN_opponent_75);
    (void)([&]() { gd::GdVal _ca[] = {lv_damagedCharacter, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_Stat_870), SYM_GEN_Health_2787)}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_damagedCharacter, gd::GdVal::from_int(100LL)}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotStack_1388, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_damagingPlayerId, gd::native_array_index(gd_ctx, native_event_get<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::f_types>(gd_ctx, native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damageSource>(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_types_1544), gd::GdVal::from_int(0LL)), native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damage>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518)}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotDamageDealt_1645, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_damagingPlayerId, lv_event}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_updateDamageMeter_1646, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_damagingPlayerId = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_event = gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_wasCriticalHit_1524, nullptr, 0))) {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_types_1544), gd::GdVal::from_int(0LL)), gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    }
    else {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_types_1544), gd::GdVal::from_int(0LL)), gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[3]), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518)}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_damagingPlayerId}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    gd::GdVal lv_damagingCharacter = ([&]() { gd::GdVal _ca[] = {lv_damagingPlayerId}; return gd::native_inline_call(gd_ctx, this->f__ctx, SYM_GEN_getCharacterFromId_1476, _ca, 1); })();
    gd::GdVal lv_damagedCharacter = gd::native_inline_get_prop(gd_ctx, lv_damagingCharacter, SYM_GEN_opponent_75);
    (void)([&]() { gd::GdVal _ca[] = {lv_damagedCharacter, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_Stat_870), SYM_GEN_Health_2787)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_damagedCharacter, gd::GdVal::from_int(100LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotStack_1388, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_damagingPlayerId, gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_types_1544), gd::GdVal::from_int(0LL)), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotDamageDealt_1645, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_damagingPlayerId, lv_event}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_updateDamageMeter_1646, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_Heal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_playerId = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_playerId = gd::gd_coerce_int(lv_playerId);
    gd::GdVal lv_origin = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_origin, gd::GdVal::from_int(12LL)}; return this->fn_createEvent(_ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4]), lv_amount}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setTarget>(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_playerId}; return native_event_call<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::fn_getCharacterFromId>(gd_ctx, this->f__ctx, SYM_GEN_getCharacterFromId_1476, _ca, 1); })(), gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_Stat_870), SYM_GEN_Health_2787)}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_playerId = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_playerId = gd::gd_coerce_int(lv_playerId);
    gd::GdVal lv_origin = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_origin, gd::GdVal::from_int(12LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4]), lv_amount}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_playerId}; return gd::native_inline_call(gd_ctx, this->f__ctx, SYM_GEN_getCharacterFromId_1476, _ca, 1); })(), gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_Stat_870), SYM_GEN_Health_2787)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_LoseHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_playerId = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_playerId = gd::gd_coerce_int(lv_playerId);
    gd::GdVal lv_origin = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_origin, gd::GdVal::from_int(5LL)}; return this->fn_createEvent(_ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4]), lv_amount}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setTarget>(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_playerId}; return native_event_call<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::fn_getCharacterFromId>(gd_ctx, this->f__ctx, SYM_GEN_getCharacterFromId_1476, _ca, 1); })(), gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_Stat_870), SYM_GEN_Health_2787)}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_playerId = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_playerId = gd::gd_coerce_int(lv_playerId);
    gd::GdVal lv_origin = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_origin, gd::GdVal::from_int(5LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4]), lv_amount}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_playerId}; return gd::native_inline_call(gd_ctx, this->f__ctx, SYM_GEN_getCharacterFromId_1476, _ca, 1); })(), gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_Stat_870), SYM_GEN_Health_2787)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_Stack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_playerId = (_argc > 3) ? _args[3] : gd::GdVal::null();
    lv_playerId = gd::gd_coerce_int(lv_playerId);
    gd::GdVal lv_triggerEvent = (_argc > 4) ? _args[4] : (gd::GdVal::null());
    gd::GdVal lv_used = (_argc > 5) ? _args[5] : (gd::GdVal::from_bool(false));
    lv_used = gd::gd_coerce_bool(lv_used);
    gd::GdVal lv_reflected = (_argc > 6) ? _args[6] : (gd::GdVal::from_bool(false));
    lv_reflected = gd::gd_coerce_bool(lv_reflected);
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, lv_type}; return this->fn_createEvent(_ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4]), lv_amount}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[5]), lv_used}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6]), lv_reflected}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setTarget>(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_playerId}; return native_event_call<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::fn_getCharacterFromId>(gd_ctx, this->f__ctx, SYM_GEN_getCharacterFromId_1476, _ca, 1); })(), lv_type}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotStack_1388, _ca, 2); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_type, gd::GdVal::from_int(106LL))))) {
        {
            gd::GdVal _t963 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_playerId}; return native_event_call<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::fn_getCharacterFromId>(gd_ctx, this->f__ctx, SYM_GEN_getCharacterFromId_1476, _ca, 1); })(), SYM_GEN_items_1092));
            gd::GdArr* _t964 = (_t963.kind == gd::GdVal::Kind::Arr) ? _t963.arr : nullptr;
            uint32_t _len__t965 = _t964 ? _t964->len : 0u;
            for (uint32_t _t965 = 0; _t965 < _len__t965; ++_t965) {
                gd::GdVal lv_i = _t964->data[_t965];
                if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, lv_i, SYM_GEN_isWeapon_82, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_i, SYM_GEN_canBeEmpowered_90, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_i, gd::GdVal::from_int(0LL)}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
                    (void)([&]() { gd::GdVal _ca[] = {lv_i, gd::GdVal::from_int(1LL)}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
                }
            }
        }
    }
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_type, gd::GdVal::from_int(107LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_type, gd::GdVal::from_int(110LL)))))))) {
        {
            gd::GdVal _t966 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_playerId}; return native_event_call<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::fn_getCharacterFromId>(gd_ctx, this->f__ctx, SYM_GEN_getCharacterFromId_1476, _ca, 1); })(), SYM_GEN_items_1092));
            gd::GdArr* _t967 = (_t966.kind == gd::GdVal::Kind::Arr) ? _t966.arr : nullptr;
            uint32_t _len__t968 = _t967 ? _t967->len : 0u;
            for (uint32_t _t968 = 0; _t968 < _len__t968; ++_t968) {
                gd::GdVal lv_i = _t967->data[_t968];
                if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_i, SYM_GEN_hasCooldown_95, nullptr, 0))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_i, gd::GdVal::from_int(9LL)}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
                }
            }
        }
    }
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_playerId = (_argc > 3) ? _args[3] : gd::GdVal::null();
    lv_playerId = gd::gd_coerce_int(lv_playerId);
    gd::GdVal lv_triggerEvent = (_argc > 4) ? _args[4] : (gd::GdVal::null());
    gd::GdVal lv_used = (_argc > 5) ? _args[5] : (gd::GdVal::from_bool(false));
    lv_used = gd::gd_coerce_bool(lv_used);
    gd::GdVal lv_reflected = (_argc > 6) ? _args[6] : (gd::GdVal::from_bool(false));
    lv_reflected = gd::gd_coerce_bool(lv_reflected);
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, lv_type}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4]), lv_amount}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[5]), lv_used}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6]), lv_reflected}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_playerId}; return gd::native_inline_call(gd_ctx, this->f__ctx, SYM_GEN_getCharacterFromId_1476, _ca, 1); })(), lv_type}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotStack_1388, _ca, 2); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_type, gd::GdVal::from_int(106LL))))) {
        {
            gd::GdVal _t963 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_playerId}; return gd::native_inline_call(gd_ctx, this->f__ctx, SYM_GEN_getCharacterFromId_1476, _ca, 1); })(), SYM_GEN_items_1092));
            gd::GdArr* _t964 = (_t963.kind == gd::GdVal::Kind::Arr) ? _t963.arr : nullptr;
            uint32_t _len__t965 = _t964 ? _t964->len : 0u;
            for (uint32_t _t965 = 0; _t965 < _len__t965; ++_t965) {
                gd::GdVal lv_i = _t964->data[_t965];
                if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, lv_i, SYM_GEN_isWeapon_82, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_i, SYM_GEN_canBeEmpowered_90, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_i, gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
                    (void)([&]() { gd::GdVal _ca[] = {lv_i, gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
                }
            }
        }
    }
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_type, gd::GdVal::from_int(107LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_type, gd::GdVal::from_int(110LL)))))))) {
        {
            gd::GdVal _t966 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_playerId}; return gd::native_inline_call(gd_ctx, this->f__ctx, SYM_GEN_getCharacterFromId_1476, _ca, 1); })(), SYM_GEN_items_1092));
            gd::GdArr* _t967 = (_t966.kind == gd::GdVal::Kind::Arr) ? _t966.arr : nullptr;
            uint32_t _len__t968 = _t967 ? _t967->len : 0u;
            for (uint32_t _t968 = 0; _t968 < _len__t968; ++_t968) {
                gd::GdVal lv_i = _t967->data[_t968];
                if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_i, SYM_GEN_hasCooldown_95, nullptr, 0))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_i, gd::GdVal::from_int(9LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
                }
            }
        }
    }
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_StackTemporary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 4) ? _args[4] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 5) ? _args[5] : gd::GdVal::null();
    gd::GdVal lv_reflected = (_argc > 6) ? _args[6] : (gd::GdVal::from_bool(false));
    lv_reflected = gd::gd_coerce_bool(lv_reflected);
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_type, lv_item, lv_amount, lv_playerId, lv_triggerEvent}; return this->fn_createEvent_Stack(_ca, 5); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7]), lv_duration}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6]), lv_reflected}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 4) ? _args[4] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 5) ? _args[5] : gd::GdVal::null();
    gd::GdVal lv_reflected = (_argc > 6) ? _args[6] : (gd::GdVal::from_bool(false));
    lv_reflected = gd::gd_coerce_bool(lv_reflected);
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_type, lv_item, lv_amount, lv_playerId, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_Stack_1362, _ca, 5); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7]), lv_duration}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6]), lv_reflected}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_StackTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 4) ? _args[4] : gd::GdVal::null();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_type, lv_item, lv_amount, lv_playerId, lv_triggerEvent}; return this->fn_createEvent_Stack(_ca, 5); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[8]), gd::GdVal::from_bool(true)}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 4) ? _args[4] : gd::GdVal::null();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_type, lv_item, lv_amount, lv_playerId, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_Stack_1362, _ca, 5); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[8]), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_StackResistOrNullify(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 4) ? _args[4] : gd::GdVal::null();
    gd::GdVal lv_reflect = (_argc > 5) ? _args[5] : (gd::GdVal::from_bool(false));
    lv_reflect = gd::gd_coerce_bool(lv_reflect);
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_type, lv_item, lv_amount, lv_playerId, lv_triggerEvent}; return this->fn_createEvent_Stack(_ca, 5); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[9]), gd::GdVal::from_bool(true)}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6]), lv_reflect}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 4) ? _args[4] : gd::GdVal::null();
    gd::GdVal lv_reflect = (_argc > 5) ? _args[5] : (gd::GdVal::from_bool(false));
    lv_reflect = gd::gd_coerce_bool(lv_reflect);
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_type, lv_item, lv_amount, lv_playerId, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_Stack_1362, _ca, 5); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[9]), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6]), lv_reflect}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_StackProtect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 4) ? _args[4] : gd::GdVal::null();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_type, lv_item, lv_amount, lv_playerId, lv_triggerEvent}; return this->fn_createEvent_Stack(_ca, 5); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[10]), gd::GdVal::from_bool(true)}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 4) ? _args[4] : gd::GdVal::null();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_type, lv_item, lv_amount, lv_playerId, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_Stack_1362, _ca, 5); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[10]), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_Stun(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(9LL)}; return this->fn_createEvent(_ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7]), lv_duration}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setTarget>(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(9LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7]), lv_duration}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_StunResist(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(10LL)}; return this->fn_createEvent(_ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setTarget>(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(10LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_InvulnerableStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(7LL)}; return this->fn_createEvent(_ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7]), lv_duration}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setTarget>(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(7LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7]), lv_duration}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_InvulnerableEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(8LL)}; return this->fn_createEvent(_ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setTarget>(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(8LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_Stamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(13LL)}; return this->fn_createEvent(_ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[11]), gd::native_numeric_div(gd_ctx, gd::gd_floor(gd::native_numeric_mul(lv_amount, gd::GdVal::from_int(10LL))), gd::GdVal::from_float(10.0))}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setTarget>(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(13LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[11]), gd::native_numeric_div(gd_ctx, gd::gd_floor(gd::native_numeric_mul(lv_amount, gd::GdVal::from_int(10LL))), gd::GdVal::from_float(10.0))}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_DrainStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(14LL)}; return this->fn_createEvent(_ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setTarget>(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[11]), gd::native_numeric_div(gd_ctx, gd::gd_floor(gd::native_numeric_mul(lv_amount, gd::GdVal::from_int(10LL))), gd::GdVal::from_float(10.0))}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(14LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[11]), gd::native_numeric_div(gd_ctx, gd::gd_floor(gd::native_numeric_mul(lv_amount, gd::GdVal::from_int(10LL))), gd::GdVal::from_float(10.0))}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_OutOfStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(15LL)}; return this->fn_createEvent(_ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setTarget>(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(15LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_DamageBuff(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_buffedItem = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_damage = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 4) ? _args[4] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(16LL)}; return this->fn_createEvent(_ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setTarget>(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[12]), gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_buffedItem, SYM_GEN_descriptor_2), SYM_GEN_getTranslatedName_641, nullptr, 0)}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[3]), lv_damage}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_buffedItem = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_damage = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 4) ? _args[4] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(16LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[12]), gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_buffedItem, SYM_GEN_descriptor_2), SYM_GEN_getTranslatedName_641, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[3]), lv_damage}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_TemporaryMaxHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(19LL)}; return this->fn_createEvent(_ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4]), lv_amount}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0), gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_Stat_870), SYM_GEN_Health_2787)}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0), gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_Stat_870), SYM_GEN_MaxHealth_2684)}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(19LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4]), lv_amount}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0), gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_Stat_870), SYM_GEN_Health_2787)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0), gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_Stat_870), SYM_GEN_MaxHealth_2684)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_TemporaryMaxStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(20LL)}; return this->fn_createEvent(_ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[11]), lv_amount}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0), gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_Stat_870), SYM_GEN_Stamina_2673)}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0), gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_Stat_870), SYM_GEN_MaxStamina_2801)}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(20LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[11]), lv_amount}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0), gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_Stat_870), SYM_GEN_Stamina_2673)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0), gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_Stat_870), SYM_GEN_MaxStamina_2801)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_BattleRageStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(21LL)}; return this->fn_createEvent(_ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7]), lv_duration}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(21LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7]), lv_duration}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_BattleRageEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_playerId = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, gd::GdVal::from_int(22LL), gd::GdVal::from_int(22LL)}; return this->fn_createEvent(_ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setTarget>(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_playerId = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, gd::GdVal::from_int(22LL), gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setTarget_1573, _ca, 1); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_Reincarnate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_health = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_health = gd::gd_coerce_int(lv_health);
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(23LL)}; return this->fn_createEvent(_ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[13]), lv_health}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0), gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_Stat_870), SYM_GEN_Health_2787)}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_health = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_health = gd::gd_coerce_int(lv_health);
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(23LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[13]), lv_health}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0), gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_Stat_870), SYM_GEN_Health_2787)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_Activation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(0LL)}; return this->fn_createEvent(_ca, 3); })();
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_createEvent_DamChange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    gd::GdVal lv_isPercent = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_isPercent = gd::gd_coerce_bool(lv_isPercent);
    gd::GdVal lv_duration = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_type = (_argc > 4) ? _args[4] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 5) ? _args[5] : (gd::GdVal::null());
    gd::GdVal lv_event = gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(18LL)}; return this->fn_createEvent(_ca, 3); })();
    }
    else {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(17LL)}; return this->fn_createEvent(_ca, 3); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4]), lv_amount}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[14]), lv_isPercent}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_duration, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7]), lv_duration}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_type, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[15]), lv_type}; return native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_setParam>(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    }
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    gd::GdVal lv_isPercent = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_isPercent = gd::gd_coerce_bool(lv_isPercent);
    gd::GdVal lv_duration = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_type = (_argc > 4) ? _args[4] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 5) ? _args[5] : (gd::GdVal::null());
    gd::GdVal lv_event = gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(18LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    }
    else {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent, lv_item, gd::GdVal::from_int(17LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createEvent_1354, _ca, 3); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4]), lv_amount}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[14]), lv_isPercent}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_duration, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7]), lv_duration}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_type, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[15]), lv_type}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_setParam_1574, _ca, 2); })();
    }
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_snapshotMetric(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_playerId = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_metric = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_eventType = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 3) ? _args[3] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId, lv_metric, lv_eventType, lv_value}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotMetric_1382, _ca, 4); })();
    return gd::GdVal::null();
    }
    gd::GdVal lv_playerId = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_metric = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_eventType = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 3) ? _args[3] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_playerId, lv_metric, lv_eventType, lv_value}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotMetric_1382, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_snapshotItemMetric(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_metricIndex = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_withNextEvent = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(false));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_playerId, gd::GdVal::null())))) {
        lv_playerId = gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0), SYM_GEN_playerId_1046);
    }
    gd::GdVal lv_connectedEventNum = this->f_eventNum;
    if (gd::gd_truth(lv_withNextEvent)) {
        lv_connectedEventNum = gd::native_numeric_add(gd_ctx, lv_connectedEventNum, gd::GdVal::from_int(1LL));
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_item, lv_metricIndex, lv_playerId, lv_withNextEvent}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotItemMetric_1383, _ca, 4); })();
    return gd::GdVal::null();
    }
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_metricIndex = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_withNextEvent = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(false));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_playerId, gd::GdVal::null())))) {
        lv_playerId = gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0), SYM_GEN_playerId_1046);
    }
    gd::GdVal lv_connectedEventNum = this->f_eventNum;
    if (gd::gd_truth(lv_withNextEvent)) {
        lv_connectedEventNum = gd::native_numeric_add(gd_ctx, lv_connectedEventNum, gd::GdVal::from_int(1LL));
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_item, lv_metricIndex, lv_playerId, lv_withNextEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotItemMetric_1383, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_snapshotItemTooltipStat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_statType = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_withNextEvent = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(false));
    gd::GdVal lv_event = (_argc > 4) ? _args[4] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_playerId, gd::GdVal::null())))) {
        lv_playerId = gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0), SYM_GEN_playerId_1046);
    }
    gd::GdVal lv_connectedEventNum = this->f_eventNum;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_event, gd::GdVal::null())))) {
        lv_connectedEventNum = gd::native_inline_get_prop(gd_ctx, lv_event, SYM_GEN_id_1566);
    }
    else if (gd::gd_truth(lv_withNextEvent)) {
        lv_connectedEventNum = gd::native_numeric_add(gd_ctx, lv_connectedEventNum, gd::GdVal::from_int(1LL));
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_item, lv_statType, lv_playerId, lv_withNextEvent, lv_event}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 5); })();
    return gd::GdVal::null();
    }
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_statType = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_playerId = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_withNextEvent = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(false));
    gd::GdVal lv_event = (_argc > 4) ? _args[4] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_playerId, gd::GdVal::null())))) {
        lv_playerId = gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0), SYM_GEN_playerId_1046);
    }
    gd::GdVal lv_connectedEventNum = this->f_eventNum;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_event, gd::GdVal::null())))) {
        lv_connectedEventNum = gd::native_inline_get_prop(gd_ctx, lv_event, SYM_GEN_id_1566);
    }
    else if (gd::gd_truth(lv_withNextEvent)) {
        lv_connectedEventNum = gd::native_numeric_add(gd_ctx, lv_connectedEventNum, gd::GdVal::from_int(1LL));
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_item, lv_statType, lv_playerId, lv_withNextEvent, lv_event}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_snapshotItemState(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_state = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_withNextEvent = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_withNextEvent = gd::gd_coerce_bool(lv_withNextEvent);
    gd::GdVal lv_event = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_playerId = gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0), SYM_GEN_playerId_1046);
    (void)([&]() { gd::GdVal _ca[] = {lv_item, lv_state, lv_withNextEvent, lv_event}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotItemState_1385, _ca, 4); })();
    return gd::GdVal::null();
    }
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_state = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_withNextEvent = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_withNextEvent = gd::gd_coerce_bool(lv_withNextEvent);
    gd::GdVal lv_event = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_playerId = gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0), SYM_GEN_playerId_1046);
    (void)([&]() { gd::GdVal _ca[] = {lv_item, lv_state, lv_withNextEvent, lv_event}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotItemState_1385, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_snapshotGlobalStat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_stat = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_stat = gd::gd_coerce_int(lv_stat);
    gd::GdVal lv_newValue = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_stat, lv_newValue}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotGlobalStat_1386, _ca, 2); })();
    return gd::GdVal::null();
    }
    gd::GdVal lv_stat = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_stat = gd::gd_coerce_int(lv_stat);
    gd::GdVal lv_newValue = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_stat, lv_newValue}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotGlobalStat_1386, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_snapshotCharacterStat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_statType = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_withNextEvent = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    lv_withNextEvent = gd::gd_coerce_bool(lv_withNextEvent);
    gd::GdVal lv_event = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_character, lv_statType, lv_withNextEvent, lv_event}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 4); })();
    return gd::GdVal::null();
    }
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_statType = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_withNextEvent = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    lv_withNextEvent = gd::gd_coerce_bool(lv_withNextEvent);
    gd::GdVal lv_event = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_character, lv_statType, lv_withNextEvent, lv_event}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotCharacterStat_1387, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombatLog::fn_snapshotStack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_type = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_character, lv_type}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotStack_1388, _ca, 2); })();
    return gd::GdVal::null();
    }
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_type = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_character, lv_type}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotStack_1388, _ca, 2); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreCombatLog(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__CoreCombatLog>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,26u); return object; }
const gd::GdClassMeta META_Gd__gd_core__CoreCombatLog = {CLS_Gd__gd_core__CoreCombatLog, "CoreCombatLog", "res://gd_core/CoreCombatLog.gd", nullptr, false, _alloc_Gd__gd_core__CoreCombatLog, &Gd__gd_core__CoreCombatLog::get_static_prop_fn, &Gd__gd_core__CoreCombatLog::call_static_fn};

void Gd__gd_core__CoreRng__INNER__BalancedRange::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_acc = gd::GdVal::from_float(0.0);
    this->f__rng = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__CoreRng__INNER__BalancedRange::meta() const { return &META_Gd__gd_core__CoreRng__INNER__BalancedRange; }
gd::GdVal Gd__gd_core__CoreRng__INNER__BalancedRange::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreRng__INNER__BalancedRange::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreRng__INNER__BalancedRange::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_acc_1763: out = this->f_acc; return true;
        case SYM_GEN__rng_1548: out = this->f__rng; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreRng__INNER__BalancedRange::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_acc_1763: this->f_acc = val; return true;
        case SYM_GEN__rng_1548: this->f__rng = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreRng__INNER__BalancedRange::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_reset_1025: return true;
        case SYM_GEN_randIntRange_1764: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreRng__INNER__BalancedRange::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_reset_1025: out = fn_reset(args, argc); return true;
        case SYM_GEN_randIntRange_1764: out = fn_randIntRange(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreRng__INNER__BalancedRange::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core__CoreRng__INNER__BalancedRange::fn__init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__rng_ref = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    this->f__rng = lv__rng_ref;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng__INNER__BalancedRange::fn_reset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_acc = gd::GdVal::from_float(0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng__INNER__BalancedRange::fn_randIntRange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_from = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_from = gd::gd_coerce_int(lv_from);
    gd::GdVal lv_to = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_to = gd::gd_coerce_int(lv_to);
    gd::GdVal lv_rng = ([&]() { gd::GdVal _ca[] = {lv_from, lv_to}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f__rng, SYM_GEN_rng_1406), gd::SYM_randi_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[16]), lv_from, lv_to, lv_rng}; return gd::native_inline_call(gd_ctx, this->f__rng, SYM_GEN_bare_draw_seq_1742, _ca, 4); })();
    gd::GdVal lv_expected = gd::gd_coerce_float(gd::native_numeric_mul(gd::GdVal::from_float(0.5), gd::native_numeric_add(gd_ctx, lv_from, lv_to)));
    gd::GdVal lv_dif = gd::gd_coerce_float(gd::native_numeric_sub(lv_rng, lv_expected));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_acc, gd::GdVal::from_int(1LL))))) {
        gd::GdVal lv_malus = gd::gd_min(gd::native_numeric_sub(lv_rng, lv_from), gd::gd_coerce_int(this->f_acc));
        this->f_acc = gd::native_numeric_sub(this->f_acc, lv_malus);
        lv_rng = gd::native_numeric_sub(lv_rng, lv_malus);
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f_acc, gd::gd_neg(gd::GdVal::from_int(1LL)))))) {
        gd::GdVal lv_bonus = gd::gd_min(gd::native_numeric_sub(lv_to, lv_rng), gd::gd_coerce_int(gd::gd_abs(this->f_acc)));
        this->f_acc = gd::native_numeric_add(gd_ctx, this->f_acc, lv_bonus);
        lv_rng = gd::native_numeric_add(gd_ctx, lv_rng, lv_bonus);
    }
    this->f_acc = gd::native_numeric_add(gd_ctx, this->f_acc, lv_dif);
    return lv_rng;
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreRng__INNER__BalancedRange(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__CoreRng__INNER__BalancedRange>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,43u); return object; }
const gd::GdClassMeta META_Gd__gd_core__CoreRng__INNER__BalancedRange = {CLS_Gd__gd_core__CoreRng__INNER__BalancedRange, "BalancedRange", "", nullptr, false, _alloc_Gd__gd_core__CoreRng__INNER__BalancedRange, &Gd__gd_core__CoreRng__INNER__BalancedRange::get_static_prop_fn, &Gd__gd_core__CoreRng__INNER__BalancedRange::call_static_fn};

void Gd__gd_core__Potion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_potionColor = gd::make_color_from_args(nullptr, 0);
    this->f_fluidTween = gd::GdVal::null();
    this->f_isFull = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
    this->f_connector = gd::GdVal::null();
    this->f_fluid = gd::GdVal::null();
    this->f_fluidGradientTex = gd::GdVal::null();
    this->f_fluidGradient = gd::GdVal::null();
    this->f_baseFoaminess = gd::GdVal::null();
    this->f_baseScroll = gd::GdVal::null();
    this->f_baseLevel = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__Potion::meta() const { return &META_Gd__gd_core__Potion; }
gd::GdVal Gd__gd_core__Potion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Potion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Potion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_potionColor_1838: out = this->f_potionColor; return true;
        case SYM_GEN_fluidTween_1839: out = this->f_fluidTween; return true;
        case SYM_GEN_isFull_1840: out = this->f_isFull; return true;
        case SYM_GEN_connector_885: out = this->f_connector; return true;
        case SYM_GEN_fluid_1841: out = this->f_fluid; return true;
        case SYM_GEN_fluidGradientTex_1842: out = this->f_fluidGradientTex; return true;
        case SYM_GEN_fluidGradient_1843: out = this->f_fluidGradient; return true;
        case SYM_GEN_baseFoaminess_1844: out = this->f_baseFoaminess; return true;
        case SYM_GEN_baseScroll_1845: out = this->f_baseScroll; return true;
        case SYM_GEN_baseLevel_1846: out = this->f_baseLevel; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Potion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_potionColor_1838: this->f_potionColor = val; return true;
        case SYM_GEN_fluidTween_1839: this->f_fluidTween = val; return true;
        case SYM_GEN_isFull_1840: this->f_isFull = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_connector_885: this->f_connector = val; return true;
        case SYM_GEN_fluid_1841: this->f_fluid = val; return true;
        case SYM_GEN_fluidGradientTex_1842: this->f_fluidGradientTex = val; return true;
        case SYM_GEN_fluidGradient_1843: this->f_fluidGradient = val; return true;
        case SYM_GEN_baseFoaminess_1844: this->f_baseFoaminess = val; return true;
        case SYM_GEN_baseScroll_1845: this->f_baseScroll = val; return true;
        case SYM_GEN_baseLevel_1846: this->f_baseLevel = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Potion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepare_122: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_isEmpty_923: return true;
        case gd::SYM_fill: return true;
        case gd::SYM_empty: return true;
        case SYM_GEN_drink_1847: return true;
        case SYM_GEN_consumePotion_1848: return true;
        case SYM_GEN_onTriggerPotion_1849: return true;
        case SYM_GEN_triggerPotion_1850: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN_activate_150: return true;
        case SYM_GEN_shopEntered_745: return true;
        case SYM_GEN_getAffectedCellsAfterRotate_primary_410: return true;
        case SYM_GEN_addToInventory_120: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_onFusingAsIngredient_842: return true;
        case SYM_GEN_onAffectedItemAdded_435: return true;
        case SYM_GEN_onAffectedItemRemoved_436: return true;
        case SYM_GEN_updateConnector_1851: return true;
        case SYM_GEN_resetGradient_1852: return true;
        case SYM_GEN_discard_764: return true;
        case SYM_GEN_getStarPosition_1853: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Potion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepare_122: out = fn_prepare(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_isEmpty_923: out = fn_isEmpty(args, argc); return true;
        case gd::SYM_fill: out = fn_fill(args, argc); return true;
        case gd::SYM_empty: out = fn_empty(args, argc); return true;
        case SYM_GEN_drink_1847: out = fn_drink(args, argc); return true;
        case SYM_GEN_consumePotion_1848: out = fn_consumePotion(args, argc); return true;
        case SYM_GEN_onTriggerPotion_1849: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_triggerPotion_1850: out = fn_triggerPotion(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_activate_150: out = fn_activate(args, argc); return true;
        case SYM_GEN_shopEntered_745: out = fn_shopEntered(args, argc); return true;
        case SYM_GEN_getAffectedCellsAfterRotate_primary_410: out = fn_getAffectedCellsAfterRotate_primary(args, argc); return true;
        case SYM_GEN_addToInventory_120: out = fn_addToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_onFusingAsIngredient_842: out = fn_onFusingAsIngredient(args, argc); return true;
        case SYM_GEN_onAffectedItemAdded_435: out = fn_onAffectedItemAdded(args, argc); return true;
        case SYM_GEN_onAffectedItemRemoved_436: out = fn_onAffectedItemRemoved(args, argc); return true;
        case SYM_GEN_updateConnector_1851: out = fn_updateConnector(args, argc); return true;
        case SYM_GEN_resetGradient_1852: out = fn_resetGradient(args, argc); return true;
        case SYM_GEN_discard_764: out = fn_discard(args, argc); return true;
        case SYM_GEN_getStarPosition_1853: out = fn_getStarPosition(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Potion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Potion::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_prepare_122, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(11LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn_isEmpty(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(!gd::gd_truth(this->f_isFull));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn_fill(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_isFull = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn_empty(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_isFull = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn_drink(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn_consumePotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_withActivate = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    lv_withActivate = gd::gd_coerce_bool(lv_withActivate);
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drink_1847, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_triggerPotion_1850, _ca, 1); })();
    gd::GdVal lv_affected = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, lv_affected, gd::SYM_empty, nullptr, 0))))) {
        (void)gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL)), SYM_GEN_triggerPotion_1850, nullptr, 0);
        (void)gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL)), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    if (gd::gd_truth(lv_withActivate)) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn_triggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onTriggerPotion_1849, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_778, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[17]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_obj(this)}))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__isFull = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv__isFull)) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_fill, nullptr, 0);
    }
    else {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_empty, nullptr, 0);
    }
    this->f_isFull = gd::gd_coerce_bool(lv__isFull);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn_activate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_playCombatAni = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_consume = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    gd::GdVal lv_animationOverride = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_emitSignal = (_argc > 4) ? _args[4] : (gd::GdVal::from_bool(true));
    lv_emitSignal = gd::gd_coerce_bool(lv_emitSignal);
    (void)([&]() { gd::GdVal _ca[] = {lv_damageRes, lv_playCombatAni, lv_consume, gd::GdVal::null()}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_activate_150, _ca, 4, _out); return _out; })();
    if (gd::gd_truth(lv_emitSignal)) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[18]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_obj(this)}))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn_shopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craft = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_craft = gd::gd_coerce_bool(lv_craft);
    (void)([&]() { gd::GdVal _ca[] = {lv_craft}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_shopEntered_745, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_isFull)))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_fill, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn_getAffectedCellsAfterRotate_primary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rotatedCells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_faceDirection, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))))) {
        return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_numeric_add(gd_ctx, gd::native_array_index(gd_ctx, lv_rotatedCells, gd::GdVal::from_int(1LL)), gd::GdVal::from_vec2(0.0, -1.0))}));
    }
    else {
        return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_numeric_add(gd_ctx, gd::native_array_index(gd_ctx, lv_rotatedCells, gd::GdVal::from_int(0LL)), gd::GdVal::from_vec2(0.0, -1.0))}));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn_addToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__inventory = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__occupiedCells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__placedByPlayer = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv__placedByPlayer = gd::gd_coerce_bool(lv__placedByPlayer);
    (void)([&]() { gd::GdVal _ca[] = {lv__inventory, lv__occupiedCells, lv__placedByPlayer}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_addToInventory_120, _ca, 3, _out); return _out; })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateConnector_1851, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetGradient_1852, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn_onFusingAsIngredient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetGradient_1852, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn_onAffectedItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_color, gd::GdVal::from_int(0LL))))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateConnector_1851, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn_onAffectedItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_color, gd::GdVal::from_int(0LL))))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateConnector_1851, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn_updateConnector(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn_resetGradient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn_discard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_discardGems = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    if (gd::gd_truth(this->f_pooled)) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetGradient_1852, nullptr, 0);
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_discardGems}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_discard_764, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn_getStarPosition(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Potion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Potion(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__Potion>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,120u); return object; }
const gd::GdClassMeta META_Gd__gd_core__Potion = {CLS_Gd__gd_core__Potion, "Potion", "res://gd_core/Potion.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__Potion, &Gd__gd_core__Potion::get_static_prop_fn, &Gd__gd_core__Potion::call_static_fn};

void Gd__gd_core__GlovesofHaste::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_bonusSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__GlovesofHaste::meta() const { return &META_Gd__gd_core__GlovesofHaste; }
gd::GdVal Gd__gd_core__GlovesofHaste::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__GlovesofHaste::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__GlovesofHaste::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_bonusSpeed_1882: out = this->f_bonusSpeed; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__GlovesofHaste::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusSpeed_1882: this->f_bonusSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__GlovesofHaste::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__GlovesofHaste::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__GlovesofHaste::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__GlovesofHaste::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__GlovesofHaste::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t969 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t970 = (_t969.kind == gd::GdVal::Kind::Arr) ? _t969.arr : nullptr;
        uint32_t _len__t971 = _t970 ? _t970->len : 0u;
        for (uint32_t _t971 = 0; _t971 < _len__t971; ++_t971) {
            gd::GdVal lv_item = _t970->data[_t971];
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__GlovesofHaste::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_bonusSpeed = gd::native_numeric_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::GdVal::from_int(100LL));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__GlovesofHaste(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__GlovesofHaste>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,75u); return object; }
const gd::GdClassMeta META_Gd__gd_core__GlovesofHaste = {CLS_Gd__gd_core__GlovesofHaste, "GlovesofHaste", "res://gd_core/GlovesofHaste.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__GlovesofHaste, &Gd__gd_core__GlovesofHaste::get_static_prop_fn, &Gd__gd_core__GlovesofHaste::call_static_fn};

void Gd__gd_core__LeatherArmor::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__LeatherArmor::meta() const { return &META_Gd__gd_core__LeatherArmor; }
gd::GdVal Gd__gd_core__LeatherArmor::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__LeatherArmor::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__LeatherArmor::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__LeatherArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__LeatherArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreCombatStart_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__LeatherArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreCombatStart_125: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__LeatherArmor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__LeatherArmor::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDebuffResistStacks_1185, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__LeatherArmor(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__LeatherArmor>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,93u); return object; }
const gd::GdClassMeta META_Gd__gd_core__LeatherArmor = {CLS_Gd__gd_core__LeatherArmor, "LeatherArmor", "res://gd_core/LeatherArmor.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__LeatherArmor, &Gd__gd_core__LeatherArmor::get_static_prop_fn, &Gd__gd_core__LeatherArmor::call_static_fn};

void Gd__gd_core__MrStruggles::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_hasActivated = gd::GdVal::from_bool(false);
    this->f_speedbuffTimer = gd::GdVal::null();
    this->f_activationParticles = gd::GdVal::null();
    this->f_healthThreshold = gd::GdVal::null();
    this->f_bonusSpeed = gd::GdVal::null();
    this->f_fatigueDam = gd::GdVal::null();
    this->f_speedBuffParticles1 = gd::GdVal::null();
    this->f_speedBuffParticles2 = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__MrStruggles::meta() const { return &META_Gd__gd_core__MrStruggles; }
gd::GdVal Gd__gd_core__MrStruggles::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_plushies_1949: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_str(&battle_string_literals[19]), gd::GdVal::from_str(&battle_string_literals[20])}));
        default: break;
    }
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__MrStruggles::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__MrStruggles::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_hasActivated_1906: out = this->f_hasActivated; return true;
        case SYM_GEN_speedbuffTimer_1950: out = this->f_speedbuffTimer; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_healthThreshold_1854: out = this->f_healthThreshold; return true;
        case SYM_GEN_bonusSpeed_1882: out = this->f_bonusSpeed; return true;
        case SYM_GEN_fatigueDam_1951: out = this->f_fatigueDam; return true;
        case SYM_GEN_speedBuffParticles1_1952: out = this->f_speedBuffParticles1; return true;
        case SYM_GEN_speedBuffParticles2_1953: out = this->f_speedBuffParticles2; return true;
        case SYM_GEN_plushies_1949: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__MrStruggles::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hasActivated_1906: this->f_hasActivated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_speedbuffTimer_1950: this->f_speedbuffTimer = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_healthThreshold_1854: this->f_healthThreshold = val; return true;
        case SYM_GEN_bonusSpeed_1882: this->f_bonusSpeed = val; return true;
        case SYM_GEN_fatigueDam_1951: this->f_fatigueDam = val; return true;
        case SYM_GEN_speedBuffParticles1_1952: this->f_speedBuffParticles1 = val; return true;
        case SYM_GEN_speedBuffParticles2_1953: this->f_speedBuffParticles2 = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__MrStruggles::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onDamaged_1855: return true;
        case SYM_GEN_onSpeedbuffTimeout_1954: return true;
        case SYM_GEN_onDebuffed_1955: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_rollShopChance_773: return true;
        case SYM_GEN_getGatedDescriptor_956: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__MrStruggles::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1855: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN_onSpeedbuffTimeout_1954: out = fn_onSpeedbuffTimeout(args, argc); return true;
        case SYM_GEN_onDebuffed_1955: out = fn_onDebuffed(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_rollShopChance_773: out = fn_rollShopChance(args, argc); return true;
        case SYM_GEN_getGatedDescriptor_956: out = fn_getGatedDescriptor(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__MrStruggles::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__MrStruggles::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MrStruggles::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t972 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1391, nullptr, 0));
        gd::GdArr* _t973 = (_t972.kind == gd::GdVal::Kind::Arr) ? _t972.arr : nullptr;
        uint32_t _len__t974 = _t973 ? _t973->len : 0u;
        for (uint32_t _t974 = 0; _t974 < _len__t974; ++_t974) {
            gd::GdVal lv_debuff = _t973->data[_t974];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::native_inline_get_prop(gd_ctx, gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_buffs_1048), lv_debuff), SYM_GEN_signalName_1013), gd::GdVal::from_str(&battle_string_literals[21])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[22]), gd::GdVal::from_str(&battle_string_literals[23])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MrStruggles::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(this->f_hasActivated)) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRelativeHealth_302, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
        {
            gd::GdVal _t975 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
            gd::GdArr* _t976 = (_t975.kind == gd::GdVal::Kind::Arr) ? _t975.arr : nullptr;
            uint32_t _len__t977 = _t976 ? _t976->len : 0u;
            for (uint32_t _t977 = 0; _t977 < _len__t977; ++_t977) {
                gd::GdVal lv_item = _t976->data[_t977];
                (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[24])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, this->f_speedbuffTimer, SYM_GEN_start_1779, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MrStruggles::fn_onSpeedbuffTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    {
        gd::GdVal _t978 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t979 = (_t978.kind == gd::GdVal::Kind::Arr) ? _t978.arr : nullptr;
        uint32_t _len__t980 = _t979 ? _t979->len : 0u;
        for (uint32_t _t980 = 0; _t980 < _len__t980; ++_t980) {
            gd::GdVal lv_item = _t979->data[_t980];
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_reduceSpeed_274, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MrStruggles::fn_onDebuffed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(10LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkTriggerCount_142, _ca, 1); })())) {
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
            gd::GdVal lv_debuffType = gd::native_inline_get_prop(gd_ctx, lv_event, SYM_GEN_type_1005);
            gd::GdVal lv_dur = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7]), gd::gd_neg(gd::GdVal::from_int(1LL))}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getParam_1575, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), lv_debuffType, lv_amount, lv_dur, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacksTemporary_202, _ca, 5); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MrStruggles::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_fatigueDam}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictFatigueDamage_319, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MrStruggles::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_speedbuffTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MrStruggles::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_numeric_add(gd_ctx, gd::GdVal::from_int(1000LL), gd::GdVal::from_int(3LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MrStruggles::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    return gd::GdVal::from_str(&battle_string_literals[25]);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MrStruggles::fn_rollShopChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_shopChance = (_argc > 0) ? _args[0] : (gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_shopChance_1683));
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MrStruggles::fn_getGatedDescriptor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rarity = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {Gd__gd_core__MrStruggles::get_static_const_or_enum(gd_ctx, SYM_GEN_plushies_1949)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_pickRandomElement_1746, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MrStruggles::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MrStruggles::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_speedBuffActive = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv_speedBuffActive)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MrStruggles::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speedbuffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[26]), gd::GdVal::from_str(&battle_string_literals[27]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_healthThreshold = gd::native_numeric_sub(gd::native_numeric_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    this->f_bonusSpeed = gd::native_numeric_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), gd::GdVal::from_float(100.0));
    this->f_fatigueDam = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__MrStruggles(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__MrStruggles>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,107u); return object; }
const gd::GdClassMeta META_Gd__gd_core__MrStruggles = {CLS_Gd__gd_core__MrStruggles, "MrStruggles", "res://gd_core/MrStruggles.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__MrStruggles, &Gd__gd_core__MrStruggles::get_static_prop_fn, &Gd__gd_core__MrStruggles::call_static_fn};

void Gd__gd_core__Pumpkin::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Food::init_fields(gd_ctx);
    this->f_heat = gd::GdVal::null();
    this->f_normalTexture = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__Pumpkin::meta() const { return &META_Gd__gd_core__Pumpkin; }
gd::GdVal Gd__gd_core__Pumpkin::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Pumpkin::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Pumpkin::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_heat_1896: out = this->f_heat; return true;
        case SYM_GEN_normalTexture_1968: out = this->f_normalTexture; return true;
        default: break;
    }
    return Gd__gd_core__Food::get_prop(prop, out);
}
bool Gd__gd_core__Pumpkin::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heat_1896: this->f_heat = val; return true;
        case SYM_GEN_normalTexture_1968: this->f_normalTexture = val; return true;
        default: break;
    }
    return Gd__gd_core__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Pumpkin::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN_onFatigueStarted_1969: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Food::has_own_method(m);
}
bool Gd__gd_core__Pumpkin::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onFatigueStarted_1969: out = fn_onFatigueStarted(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Pumpkin::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Pumpkin::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_res = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_220, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Pumpkin::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::set_prop(gd_ctx, this->f_descriptor, SYM_GEN_activationAni_1717, gd::native_inline_get_prop(gd_ctx, Gd__gd_core__Pumpkin::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Throw_2747));
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_1420), gd::GdVal::from_str(&battle_string_literals[28]), gd::GdVal::from_str(&battle_string_literals[29])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Pumpkin::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[30])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_330, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Pumpkin::fn_onFatigueStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Pumpkin::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Pumpkin::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[31])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1550, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Pumpkin(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__Pumpkin>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,124u); return object; }
const gd::GdClassMeta META_Gd__gd_core__Pumpkin = {CLS_Gd__gd_core__Pumpkin, "Pumpkin", "res://gd_core/Pumpkin.gd", &META_Gd__gd_core__Food, false, _alloc_Gd__gd_core__Pumpkin, &Gd__gd_core__Pumpkin::get_static_prop_fn, &Gd__gd_core__Pumpkin::call_static_fn};

void Gd__gd_core__Stone::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_ammunition = gd::GdVal::from_int(0);
    this->f_bonusDamage = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core__Stone::meta() const { return &META_Gd__gd_core__Stone; }
gd::GdVal Gd__gd_core__Stone::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Stone::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Stone::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_ammunition_903: out = this->f_ammunition; return true;
        case SYM_GEN_bonusDamage_904: out = this->f_bonusDamage; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Stone::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_ammunition_903: this->f_ammunition = gd::gd_coerce_int(val); return true;
        case SYM_GEN_bonusDamage_904: this->f_bonusDamage = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Stone::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_combatEnd_131: return true;
        case SYM_GEN_setBagOfStones_905: return true;
        case SYM_GEN_onPreDealDamage_late_906: return true;
        case SYM_GEN_preHit_907: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN_onHit_909: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Stone::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_combatEnd_131: out = fn_combatEnd(args, argc); return true;
        case SYM_GEN_setBagOfStones_905: out = fn_setBagOfStones(args, argc); return true;
        case SYM_GEN_onPreDealDamage_late_906: out = fn_onPreDealDamage_late(args, argc); return true;
        case SYM_GEN_preHit_907: out = fn_preHit(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onHit_909: out = fn_onHit(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Stone::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Stone::fn_combatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_combatEnd_131, nullptr, 0, _out); return _out; })();
    this->f_ammunition = gd::gd_coerce_int(gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Stone::fn_setBagOfStones(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_ammunition = gd::gd_coerce_int(gd::GdVal::from_int(9000LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Stone::fn_onPreDealDamage_late(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_preHit_907, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Stone::fn_preHit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeBlock_205, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Stone::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_ammunition, gd::GdVal::from_int(1LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
        this->f_ammunition = gd::gd_coerce_int(gd::native_numeric_sub(this->f_ammunition, gd::GdVal::from_int(1LL)));
        gd::GdVal lv_res = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_220, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ammunition, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_381, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Stone::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onHit_909, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Stone::fn_onHit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Stone::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1550, _ca, 1); })();
    this->f_ammunition = gd::gd_coerce_int(gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Stone(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__Stone>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,142u); return object; }
const gd::GdClassMeta META_Gd__gd_core__Stone = {CLS_Gd__gd_core__Stone, "Stone", "res://gd_core/Stone.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__Stone, &Gd__gd_core__Stone::get_static_prop_fn, &Gd__gd_core__Stone::call_static_fn};

void Gd__gd_core__ThornWhip::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__ThornWhip::meta() const { return &META_Gd__gd_core__ThornWhip; }
gd::GdVal Gd__gd_core__ThornWhip::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__ThornWhip::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__ThornWhip::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__ThornWhip::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__ThornWhip::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_onSpikesChanged_944: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__ThornWhip::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onSpikesChanged_944: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__ThornWhip::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__ThornWhip::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[32]), gd::GdVal::from_str(&battle_string_literals[33])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ThornWhip::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ThornWhip::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_numeric_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), lv_amount)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_162, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ThornWhip::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__ThornWhip(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__ThornWhip>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,153u); return object; }
const gd::GdClassMeta META_Gd__gd_core__ThornWhip = {CLS_Gd__gd_core__ThornWhip, "ThornWhip", "res://gd_core/ThornWhip.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__ThornWhip, &Gd__gd_core__ThornWhip::get_static_prop_fn, &Gd__gd_core__ThornWhip::call_static_fn};

void Gd__gd_core_items__AcornCollar::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__RangerCollar::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__AcornCollar::meta() const { return &META_Gd__gd_core_items__AcornCollar; }
gd::GdVal Gd__gd_core_items__AcornCollar::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__RangerCollar::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__AcornCollar::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__AcornCollar::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__RangerCollar::get_prop(prop, out);
}
bool Gd__gd_core_items__AcornCollar::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__RangerCollar::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__AcornCollar::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onLuckyChanged_901: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__RangerCollar::has_own_method(m);
}
bool Gd__gd_core_items__AcornCollar::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onLuckyChanged_901: out = fn_onLuckyChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__RangerCollar::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__AcornCollar::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__RangerCollar::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__AcornCollar::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canDamage_89, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__AcornCollar::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_affectedItems, gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[0]), gd::GdVal::from_str(&battle_string_literals[1])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__AcornCollar::fn_onLuckyChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    {
        gd::GdVal _t981 = gd::gd_iter_seq(gd_ctx.arena, this->f_affectedItems);
        gd::GdArr* _t982 = (_t981.kind == gd::GdVal::Kind::Arr) ? _t981.arr : nullptr;
        uint32_t _len__t983 = _t982 ? _t982->len : 0u;
        for (uint32_t _t983 = 0; _t983 < _len__t983; ++_t983) {
            gd::GdVal lv_item = _t982->data[_t983];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_numeric_mul(lv_amount, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0))}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeCritChancePercent_181, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__AcornCollar::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__RangerCollar::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__AcornCollar(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__AcornCollar>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,168u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__AcornCollar = {CLS_Gd__gd_core_items__AcornCollar, "AcornCollar", "res://gd_core_items/AcornCollar.gd", &META_Gd__gd_core_items__RangerCollar, true, _alloc_Gd__gd_core_items__AcornCollar, &Gd__gd_core_items__AcornCollar::get_static_prop_fn, &Gd__gd_core_items__AcornCollar::call_static_fn};

void Gd__gd_core_items__BoxofRiches::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_numGems = gd::GdVal::from_int(1LL);
}
const gd::GdClassMeta* Gd__gd_core_items__BoxofRiches::meta() const { return &META_Gd__gd_core_items__BoxofRiches; }
gd::GdVal Gd__gd_core_items__BoxofRiches::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_gemOdds_955: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(16LL), gd::GdVal::from_int(8LL), gd::GdVal::from_int(2LL), gd::GdVal::from_int(1LL), gd::GdVal::from_float(0.5)}));
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__BoxofRiches::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__BoxofRiches::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_numGems_954: out = this->f_numGems; return true;
        case SYM_GEN_gemOdds_955: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__BoxofRiches::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numGems_954: this->f_numGems = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__BoxofRiches::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_getGatedDescriptor_956: return true;
        case SYM_GEN_getRelatedItemHeight_700: return true;
        case SYM_GEN_onGateItemRoll_451: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__BoxofRiches::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_getGatedDescriptor_956: out = fn_getGatedDescriptor(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_700: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN_onGateItemRoll_451: out = fn_onGateItemRoll(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__BoxofRiches::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__BoxofRiches::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BoxofRiches::fn_getGatedDescriptor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rarityOdds = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_numHighRolls = (_argc > 1) ? _args[1] : (gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BoxofRiches::fn_getRelatedItemHeight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(50LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BoxofRiches::fn_onGateItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BoxofRiches::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__BoxofRiches(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__BoxofRiches>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,181u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__BoxofRiches = {CLS_Gd__gd_core_items__BoxofRiches, "BoxofRiches", "res://gd_core_items/BoxofRiches.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__BoxofRiches, &Gd__gd_core_items__BoxofRiches::get_static_prop_fn, &Gd__gd_core_items__BoxofRiches::call_static_fn};

void Gd__gd_core_items__DarkestLotus::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Card::init_fields(gd_ctx);
    this->f_manaParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__DarkestLotus::meta() const { return &META_Gd__gd_core_items__DarkestLotus; }
gd::GdVal Gd__gd_core_items__DarkestLotus::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Card::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__DarkestLotus::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__DarkestLotus::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_manaParticles_1826: out = this->f_manaParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::get_prop(prop, out);
}
bool Gd__gd_core_items__DarkestLotus::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaParticles_1826: this->f_manaParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__DarkestLotus::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Card::has_own_method(m);
}
bool Gd__gd_core_items__DarkestLotus::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__DarkestLotus::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__DarkestLotus::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_mana = gd::native_numeric_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), this->f_chainPosition);
    (void)([&]() { gd::GdVal _ca[] = {lv_mana}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_numeric_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), this->f_chainPosition)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeRandomBuffs_372, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DarkestLotus::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Card::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__DarkestLotus(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__DarkestLotus>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,199u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__DarkestLotus = {CLS_Gd__gd_core_items__DarkestLotus, "DarkestLotus", "res://gd_core_items/DarkestLotus.gd", &META_Gd__gd_core_items__Card, true, _alloc_Gd__gd_core_items__DarkestLotus, &Gd__gd_core_items__DarkestLotus::get_static_prop_fn, &Gd__gd_core_items__DarkestLotus::call_static_fn};

void Gd__gd_core_items__Exclusive__AmuletofFortune::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_bonusChance = gd::GdVal::null();
    this->f_numBuffs = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__AmuletofFortune::meta() const { return &META_Gd__gd_core_items__Exclusive__AmuletofFortune; }
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofFortune::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_amuletColor_2020: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.266667), gd::GdVal::from_float(0.960784), gd::GdVal::from_float(0.667953)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__AmuletofFortune::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__AmuletofFortune::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_bonusChance_2030: out = this->f_bonusChance; return true;
        case SYM_GEN_numBuffs_2005: out = this->f_numBuffs; return true;
        case SYM_GEN_amuletColor_2020: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofFortune::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusChance_2030: this->f_bonusChance = val; return true;
        case SYM_GEN_numBuffs_2005: this->f_numBuffs = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__AmuletofFortune::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AmuletofFortune::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofFortune::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofFortune::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canModifyChance_293, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofFortune::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__aff = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(&battle_string_literals[25]))))) {
        gd::GdVal lv__names = gd::GdVal::from_str(&battle_string_literals[25]);
        {
            gd::GdVal _t984 = gd::gd_iter_seq(gd_ctx.arena, lv__aff);
            gd::GdArr* _t985 = (_t984.kind == gd::GdVal::Kind::Arr) ? _t984.arr : nullptr;
            uint32_t _len__t986 = _t985 ? _t985->len : 0u;
            for (uint32_t _t986 = 0; _t986 < _len__t986; ++_t986) {
                gd::GdVal lv__a = _t985->data[_t986];
                lv__names = gd::native_numeric_add(gd_ctx, lv__names, gd::native_numeric_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv__a, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[34])));
            }
        }
        (void)gd::GdVal::null();
    }
    {
        gd::GdVal _t987 = gd::gd_iter_seq(gd_ctx.arena, lv__aff);
        gd::GdArr* _t988 = (_t987.kind == gd::GdVal::Kind::Arr) ? _t987.arr : nullptr;
        uint32_t _len__t989 = _t988 ? _t988->len : 0u;
        for (uint32_t _t989 = 0; _t989 < _len__t989; ++_t989) {
            gd::GdVal lv_item = _t988->data[_t989];
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusChance}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusChance_175, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofFortune::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_numBuffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMostBuffs_367, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofFortune::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_numeric_add(gd_ctx, gd::GdVal::from_int(1000LL), gd::GdVal::from_int(5LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofFortune::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_bonusChance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[35])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_numBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[36])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__AmuletofFortune(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__AmuletofFortune>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,216u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletofFortune = {CLS_Gd__gd_core_items__Exclusive__AmuletofFortune, "AmuletofFortune", "res://gd_core_items/Exclusive/AmuletofFortune.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__AmuletofFortune, &Gd__gd_core_items__Exclusive__AmuletofFortune::get_static_prop_fn, &Gd__gd_core_items__Exclusive__AmuletofFortune::call_static_fn};

void Gd__gd_core_items__Exclusive__ArtifactStoneDeath::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Stone::init_fields(gd_ctx);
    this->f_lastFatigueDam = gd::GdVal::from_int(0);
    this->f_activationParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ArtifactStoneDeath::meta() const { return &META_Gd__gd_core_items__Exclusive__ArtifactStoneDeath; }
gd::GdVal Gd__gd_core_items__Exclusive__ArtifactStoneDeath::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Stone::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ArtifactStoneDeath::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ArtifactStoneDeath::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_lastFatigueDam_2046: out = this->f_lastFatigueDam; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Stone::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ArtifactStoneDeath::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_lastFatigueDam_2046: this->f_lastFatigueDam = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Stone::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ArtifactStoneDeath::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onFatigueDamageChanged_2047: return true;
        case SYM_GEN_preHit_907: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Stone::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ArtifactStoneDeath::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onFatigueDamageChanged_2047: out = fn_onFatigueDamageChanged(args, argc); return true;
        case SYM_GEN_preHit_907: out = fn_preHit(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Stone::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ArtifactStoneDeath::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Stone::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ArtifactStoneDeath::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_lastFatigueDam = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[37]), gd::GdVal::from_str(&battle_string_literals[38])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_1420), gd::GdVal::from_str(&battle_string_literals[37]), gd::GdVal::from_str(&battle_string_literals[38])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArtifactStoneDeath::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canDamage_89, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArtifactStoneDeath::fn_onFatigueDamageChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_fatigueDam = gd::native_numeric_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_fatigueDamageSource_1430), SYM_GEN_minDamage_1542), gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getBonusFatigueDamage_1194, nullptr, 0));
    gd::GdVal lv_fatigueDiff = gd::native_numeric_sub(lv_fatigueDam, this->f_lastFatigueDam);
    this->f_lastFatigueDam = gd::gd_coerce_int(lv_fatigueDam);
    {
        gd::GdVal _t990 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t991 = (_t990.kind == gd::GdVal::Kind::Arr) ? _t990.arr : nullptr;
        uint32_t _len__t992 = _t991 ? _t991->len : 0u;
        for (uint32_t _t992 = 0; _t992 < _len__t992; ++_t992) {
            gd::GdVal lv_item = _t991->data[_t992];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_numeric_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0), lv_fatigueDiff)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeCritChancePercent_181, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArtifactStoneDeath::fn_preHit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictFatigueDamage_319, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArtifactStoneDeath::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Stone::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ArtifactStoneDeath(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__ArtifactStoneDeath>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,228u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ArtifactStoneDeath = {CLS_Gd__gd_core_items__Exclusive__ArtifactStoneDeath, "ArtifactStoneDeath", "res://gd_core_items/Exclusive/ArtifactStoneDeath.gd", &META_Gd__gd_core_items__Stone, true, _alloc_Gd__gd_core_items__Exclusive__ArtifactStoneDeath, &Gd__gd_core_items__Exclusive__ArtifactStoneDeath::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ArtifactStoneDeath::call_static_fn};

void Gd__gd_core_items__Exclusive__BismuthCube::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Cube::init_fields(gd_ctx);
    this->f_numActivations = gd::GdVal::from_int(0LL);
    this->f_buffCounter = gd::GdVal::from_int(0LL);
    this->f_nonOxidated = gd::GdVal::null();
    this->f_buffsNeeded = gd::GdVal::null();
    this->f_maxUses = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__BismuthCube::meta() const { return &META_Gd__gd_core_items__Exclusive__BismuthCube; }
gd::GdVal Gd__gd_core_items__Exclusive__BismuthCube::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Cube::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__BismuthCube::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__BismuthCube::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_numActivations_1904: out = this->f_numActivations; return true;
        case SYM_GEN_buffCounter_2083: out = this->f_buffCounter; return true;
        case SYM_GEN_nonOxidated_2084: out = this->f_nonOxidated; return true;
        case SYM_GEN_buffsNeeded_2085: out = this->f_buffsNeeded; return true;
        case SYM_GEN_maxUses_2086: out = this->f_maxUses; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BismuthCube::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numActivations_1904: this->f_numActivations = val; return true;
        case SYM_GEN_buffCounter_2083: this->f_buffCounter = val; return true;
        case SYM_GEN_nonOxidated_2084: this->f_nonOxidated = val; return true;
        case SYM_GEN_buffsNeeded_2085: this->f_buffsNeeded = val; return true;
        case SYM_GEN_maxUses_2086: this->f_maxUses = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BismuthCube::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onBuffsChanged_2087: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BismuthCube::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBuffsChanged_2087: out = fn_onBuffsChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BismuthCube::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Cube::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BismuthCube::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BismuthCube::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    this->f_buffCounter = gd::GdVal::from_int(0LL);
    this->f_affectedItem = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_428, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[39])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterBuffs_374, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BismuthCube::fn_onBuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_remainingUses = gd::native_numeric_sub(this->f_maxUses, this->f_numActivations);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_remainingUses, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_numProccs = gd::GdVal::from_int(0LL);
        this->f_buffCounter = gd::native_numeric_add(gd_ctx, this->f_buffCounter, lv_amount);
        while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_buffCounter, this->f_buffsNeeded)))) {
            lv_numProccs = gd::native_numeric_add(gd_ctx, lv_numProccs, gd::GdVal::from_int(1LL));
            this->f_buffCounter = gd::native_numeric_sub(this->f_buffCounter, this->f_buffsNeeded);
        }
        lv_numProccs = gd::gd_min(lv_remainingUses, lv_numProccs);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numProccs, gd::GdVal::from_int(0LL))))) {
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_affectedItem, gd::GdVal::null())))) {
                if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(([&]() { gd::GdVal _ca[] = {this->f_affectedItem, gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_cube_advanced_1426), gd::SYM_get, _ca, 2); })(), gd::GdVal::from_obj(this))))) {
                    { gd::GdVal _t993 = gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_cube_advanced_1426); gd::GdVal _t994 = this->f_affectedItem; gd::native_array_set_index(gd_ctx, _t993, _t994, gd::GdVal::from_obj(this)); }
                    (void)([&]() { gd::GdVal _ca[] = {gd::native_numeric_mul(this->f_cdAdvance, lv_numProccs)}; return gd::native_inline_call(gd_ctx, this->f_affectedItem, SYM_GEN_advanceCooldownSeconds_147, _ca, 1); })();
                }
                else {
                    (void)([&]() { gd::GdVal _ca[] = {gd::native_numeric_mul(gd::native_numeric_mul(this->f_cdAdvance, lv_numProccs), this->f_penaltyFactor)}; return gd::native_inline_call(gd_ctx, this->f_affectedItem, SYM_GEN_advanceCooldownSeconds_147, _ca, 1); })();
                }
            }
            (void)([&]() { gd::GdVal _ca[] = {lv_numProccs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::native_numeric_add(gd_ctx, this->f_numActivations, lv_numProccs)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BismuthCube::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_maxUses}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BismuthCube::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__numActivations = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_numActivations = lv__numActivations;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BismuthCube::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Cube::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_buffsNeeded = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[36])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_maxUses = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[40])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    (void)([&]() { gd::GdVal _ca[] = {this->f_maxUses}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BismuthCube(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__BismuthCube>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,241u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BismuthCube = {CLS_Gd__gd_core_items__Exclusive__BismuthCube, "BismuthCube", "res://gd_core_items/Exclusive/BismuthCube.gd", &META_Gd__gd_core_items__Exclusive__Cube, true, _alloc_Gd__gd_core_items__Exclusive__BismuthCube, &Gd__gd_core_items__Exclusive__BismuthCube::get_static_prop_fn, &Gd__gd_core_items__Exclusive__BismuthCube::call_static_fn};

void Gd__gd_core_items__Exclusive__BurningSword::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_heatCounter = gd::GdVal::from_int(0LL);
    this->f_particleReadyTime = gd::GdVal::from_float(0.0);
    this->f_heatOnHit = gd::GdVal::from_int(0);
    this->f_heatNeeded = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__BurningSword::meta() const { return &META_Gd__gd_core_items__Exclusive__BurningSword; }
gd::GdVal Gd__gd_core_items__Exclusive__BurningSword::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__BurningSword::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__BurningSword::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_heatCounter_2105: out = this->f_heatCounter; return true;
        case SYM_GEN_particleReadyTime_2106: out = this->f_particleReadyTime; return true;
        case SYM_GEN_heatOnHit_2107: out = this->f_heatOnHit; return true;
        case SYM_GEN_heatNeeded_1880: out = this->f_heatNeeded; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BurningSword::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heatCounter_2105: this->f_heatCounter = val; return true;
        case SYM_GEN_particleReadyTime_2106: this->f_particleReadyTime = val; return true;
        case SYM_GEN_heatOnHit_2107: this->f_heatOnHit = gd::gd_coerce_int(val); return true;
        case SYM_GEN_heatNeeded_1880: this->f_heatNeeded = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BurningSword::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onHeatChanged_913: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BurningSword::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onHeatChanged_913: out = fn_onHeatChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BurningSword::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningSword::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningSword::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_heatCounter = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[41]), gd::GdVal::from_str(&battle_string_literals[42])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningSword::fn_onHeatChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        this->f_heatCounter = gd::native_numeric_add(gd_ctx, this->f_heatCounter, lv_amount);
        gd::GdVal lv_bonus = gd::native_numeric_div(gd_ctx, this->f_heatCounter, this->f_heatNeeded);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_bonus, gd::GdVal::from_int(0LL))))) {
            gd::GdVal lv_bonusDamage = gd::native_numeric_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), lv_bonus);
            {
                gd::GdVal _t995 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
                gd::GdArr* _t996 = (_t995.kind == gd::GdVal::Kind::Arr) ? _t995.arr : nullptr;
                uint32_t _len__t997 = _t996 ? _t996->len : 0u;
                for (uint32_t _t997 = 0; _t997 < _len__t997; ++_t997) {
                    gd::GdVal lv_item = _t996->data[_t997];
                    (void)([&]() { gd::GdVal _ca[] = {lv_bonusDamage}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
                }
            }
            (void)([&]() { gd::GdVal _ca[] = {lv_bonusDamage}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1411), this->f_particleReadyTime)))) {
                this->f_particleReadyTime = gd::native_numeric_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1411), gd::GdVal::from_float(0.1));
            }
        }
        this->f_heatCounter = gd::gd_mod(gd_ctx, this->f_heatCounter, this->f_heatNeeded);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningSword::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_heatOnHit}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningSword::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_heatOnHit = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    this->f_heatNeeded = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BurningSword(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__BurningSword>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,259u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BurningSword = {CLS_Gd__gd_core_items__Exclusive__BurningSword, "BurningSword", "res://gd_core_items/Exclusive/BurningSword.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__BurningSword, &Gd__gd_core_items__Exclusive__BurningSword::get_static_prop_fn, &Gd__gd_core_items__Exclusive__BurningSword::call_static_fn};

void Gd__gd_core_items__Exclusive__Chess__BlackKnight::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Chess__ChessPiece::init_fields(gd_ctx);
    this->f_vampirism = gd::GdVal::null();
    this->f_stamina = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Chess__BlackKnight::meta() const { return &META_Gd__gd_core_items__Exclusive__Chess__BlackKnight; }
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackKnight::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackKnight::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Chess__BlackKnight::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_vampirism_940: out = this->f_vampirism; return true;
        case SYM_GEN_stamina_2156: out = this->f_stamina; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackKnight::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_vampirism_940: this->f_vampirism = val; return true;
        case SYM_GEN_stamina_2156: this->f_stamina = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackKnight::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2146: return true;
        case SYM_GEN_doEliminatedEffect_2148: return true;
        case SYM_GEN_canBeBlocked_1558: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackKnight::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2146: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_doEliminatedEffect_2148: out = fn_doEliminatedEffect(args, argc); return true;
        case SYM_GEN_canBeBlocked_1558: out = fn_canBeBlocked(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackKnight::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackKnight::fn_doCapturingEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__eliminatedPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {this->f_vampirism}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackKnight::fn_doEliminatedEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_stamina}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drainStamina_117, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackKnight::fn_canBeBlocked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackKnight::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_vampirism = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[43])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[11])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Chess__BlackKnight(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Chess__BlackKnight>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,274u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__BlackKnight = {CLS_Gd__gd_core_items__Exclusive__Chess__BlackKnight, "BlackKnight", "res://gd_core_items/Exclusive/Chess/BlackKnight.gd", &META_Gd__gd_core_items__Exclusive__Chess__ChessPiece, true, _alloc_Gd__gd_core_items__Exclusive__Chess__BlackKnight, &Gd__gd_core_items__Exclusive__Chess__BlackKnight::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Chess__BlackKnight::call_static_fn};

void Gd__gd_core_items__Exclusive__CogBadge::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_flatSpeed = gd::GdVal::null();
    this->f_speedPerTile = gd::GdVal::null();
    this->f_cogDescriptor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__CogBadge::meta() const { return &META_Gd__gd_core_items__Exclusive__CogBadge; }
gd::GdVal Gd__gd_core_items__Exclusive__CogBadge::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_chargeCells_2055: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(2LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(3LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(4LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(2LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(3LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(3LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(2LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(4LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(3LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(2LL))).as_float(), (gd::GdVal::from_int(1LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(2LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(1LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(2LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(2LL))).as_float())}));
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__CogBadge::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__CogBadge::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_flatSpeed_2056: out = this->f_flatSpeed; return true;
        case SYM_GEN_speedPerTile_2057: out = this->f_speedPerTile; return true;
        case SYM_GEN_cogDescriptor_2180: out = this->f_cogDescriptor; return true;
        case SYM_GEN_chargeCells_2055: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__CogBadge::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_flatSpeed_2056: this->f_flatSpeed = val; return true;
        case SYM_GEN_speedPerTile_2057: this->f_speedPerTile = val; return true;
        case SYM_GEN_cogDescriptor_2180: this->f_cogDescriptor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__CogBadge::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onAddToInventory_419: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_canAffect_lightning_289: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_emitCharge_2058: return true;
        case SYM_GEN_onChargeEnteredCell_2059: return true;
        case SYM_GEN_chargedItemStatChange_2060: return true;
        case SYM_GEN_getRelatedItems_459: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__CogBadge::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onAddToInventory_419: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_canAffect_lightning_289: out = fn_canAffect_lightning(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_emitCharge_2058: out = fn_emitCharge(args, argc); return true;
        case SYM_GEN_onChargeEnteredCell_2059: out = fn_onChargeEnteredCell(args, argc); return true;
        case SYM_GEN_chargedItemStatChange_2060: out = fn_chargedItemStatChange(args, argc); return true;
        case SYM_GEN_getRelatedItems_459: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__CogBadge::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__CogBadge::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CogBadge::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CogBadge::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CogBadge::fn_canAffect_lightning(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_reactsToCharges_299, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CogBadge::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_emitCharge_2058, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[44]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_obj(this)}))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CogBadge::fn_emitCharge(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_speedFactor = (_argc > 0) ? _args[0] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_event = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[45])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), Gd__gd_core_items__Exclusive__CogBadge::get_static_const_or_enum(gd_ctx, SYM_GEN_chargeCells_2055), lv_speedFactor, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_sendCharge_320, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CogBadge::fn_onChargeEnteredCell(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cellIndex = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_charge, lv_cellIndex, this->f_flatSpeed, this->f_speedPerTile}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeChargedItemStat_326, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CogBadge::fn_chargedItemStatChange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_value}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CogBadge::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CogBadge::fn_getRelatedItemColumns(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(3LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CogBadge::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_flatSpeed = gd::native_numeric_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[46])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_int(100LL));
    this->f_speedPerTile = gd::native_numeric_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[47])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_int(100LL));
    this->f_cogDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[48])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__CogBadge(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__CogBadge>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,289u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__CogBadge = {CLS_Gd__gd_core_items__Exclusive__CogBadge, "CogBadge", "res://gd_core_items/Exclusive/CogBadge.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__CogBadge, &Gd__gd_core_items__Exclusive__CogBadge::get_static_prop_fn, &Gd__gd_core_items__Exclusive__CogBadge::call_static_fn};

void Gd__gd_core_items__Exclusive__DevouringSphere::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_vampirism = gd::GdVal::null();
    this->f_blindSpeed = gd::GdVal::null();
    this->f_coldSpeed = gd::GdVal::null();
    this->f_dam = gd::GdVal::null();
    this->f_distortion = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__DevouringSphere::meta() const { return &META_Gd__gd_core_items__Exclusive__DevouringSphere; }
gd::GdVal Gd__gd_core_items__Exclusive__DevouringSphere::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__DevouringSphere::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__DevouringSphere::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_vampirism_940: out = this->f_vampirism; return true;
        case SYM_GEN_blindSpeed_2201: out = this->f_blindSpeed; return true;
        case SYM_GEN_coldSpeed_2202: out = this->f_coldSpeed; return true;
        case SYM_GEN_dam_939: out = this->f_dam; return true;
        case SYM_GEN_distortion_2203: out = this->f_distortion; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DevouringSphere::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_vampirism_940: this->f_vampirism = val; return true;
        case SYM_GEN_blindSpeed_2201: this->f_blindSpeed = val; return true;
        case SYM_GEN_coldSpeed_2202: this->f_coldSpeed = val; return true;
        case SYM_GEN_dam_939: this->f_dam = val; return true;
        case SYM_GEN_distortion_2203: this->f_distortion = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DevouringSphere::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onOpponentColdChanged_2204: return true;
        case SYM_GEN_onOpponentBlindChanged_1914: return true;
        case SYM_GEN_pickup_717: return true;
        case SYM_GEN_drop_723: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DevouringSphere::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onOpponentColdChanged_2204: out = fn_onOpponentColdChanged(args, argc); return true;
        case SYM_GEN_onOpponentBlindChanged_1914: out = fn_onOpponentBlindChanged(args, argc); return true;
        case SYM_GEN_pickup_717: out = fn_pickup(args, argc); return true;
        case SYM_GEN_drop_723: out = fn_drop(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DevouringSphere::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DevouringSphere::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[49]), gd::GdVal::from_str(&battle_string_literals[50])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[51]), gd::GdVal::from_str(&battle_string_literals[52])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DevouringSphere::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_vampirism}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_dam, gd::native_numeric_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[53])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealLife_329, _ca, 2); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DevouringSphere::fn_onOpponentColdChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_numeric_mul(lv_amount, this->f_coldSpeed)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DevouringSphere::fn_onOpponentBlindChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_numeric_mul(lv_amount, this->f_blindSpeed)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DevouringSphere::fn_pickup(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_pickupType = (_argc > 0) ? _args[0] : (gd::native_inline_get_prop(gd_ctx, Gd__gd_core_items__Exclusive__DevouringSphere::get_static_const_or_enum(gd_ctx, SYM_GEN_PickupType_866), SYM_GEN_Grabbed_2730));
    (void)([&]() { gd::GdVal _ca[] = {lv_pickupType}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_pickup_717, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DevouringSphere::fn_drop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_res = ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_drop_723, nullptr, 0, _out); return _out; })();
    return lv_res;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DevouringSphere::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_vampirism = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[43])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_blindSpeed = gd::native_numeric_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[54])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_coldSpeed = gd::native_numeric_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[55])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_dam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[56])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DevouringSphere(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__DevouringSphere>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,307u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DevouringSphere = {CLS_Gd__gd_core_items__Exclusive__DevouringSphere, "DevouringSphere", "res://gd_core_items/Exclusive/DevouringSphere.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__DevouringSphere, &Gd__gd_core_items__Exclusive__DevouringSphere::get_static_prop_fn, &Gd__gd_core_items__Exclusive__DevouringSphere::call_static_fn};

void Gd__gd_core_items__Exclusive__EchoingBattlecry::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_affectedItems = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_speedPerItem = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__EchoingBattlecry::meta() const { return &META_Gd__gd_core_items__Exclusive__EchoingBattlecry; }
gd::GdVal Gd__gd_core_items__Exclusive__EchoingBattlecry::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__EchoingBattlecry::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__EchoingBattlecry::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_affectedItems_899: out = this->f_affectedItems; return true;
        case SYM_GEN_speedPerItem_2237: out = this->f_speedPerItem; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__EchoingBattlecry::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedItems_899: this->f_affectedItems = val; return true;
        case SYM_GEN_speedPerItem_2237: this->f_speedPerItem = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__EchoingBattlecry::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__EchoingBattlecry::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__EchoingBattlecry::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__EchoingBattlecry::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasStartofBattle_126, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EchoingBattlecry::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_affectedItems = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0);
    gd::GdVal lv__b = gd::GdVal::from_str(&battle_string_literals[25]);
    gd::GdVal lv__aft = gd::GdVal::from_str(&battle_string_literals[25]);
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN__stacktrace_1731))) : gd::GdVal::from_bool(false)))) {
        {
            gd::GdVal _t998 = gd::gd_iter_seq(gd_ctx.arena, this->f_affectedItems);
            gd::GdArr* _t999 = (_t998.kind == gd::GdVal::Kind::Arr) ? _t998.arr : nullptr;
            uint32_t _len__t1000 = _t999 ? _t999->len : 0u;
            for (uint32_t _t1000 = 0; _t1000 < _len__t1000; ++_t1000) {
                gd::GdVal lv__a = _t999->data[_t1000];
                lv__b = gd::native_numeric_add(gd_ctx, lv__b, gd::native_numeric_add(gd_ctx, gd::native_numeric_add(gd_ctx, gd::native_numeric_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv__a, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[57])), ([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv__a, SYM_GEN_occupiedCells_52), gd::GdVal::from_int(0LL))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[34])));
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {this->f_affectedItems, gd::GdVal::from_str(&battle_string_literals[58])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_shuffleEngine_1747, _ca, 2); })();
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN__stacktrace_1731))) : gd::GdVal::from_bool(false)))) {
        {
            gd::GdVal _t1001 = gd::gd_iter_seq(gd_ctx.arena, this->f_affectedItems);
            gd::GdArr* _t1002 = (_t1001.kind == gd::GdVal::Kind::Arr) ? _t1001.arr : nullptr;
            uint32_t _len__t1003 = _t1002 ? _t1002->len : 0u;
            for (uint32_t _t1003 = 0; _t1003 < _len__t1003; ++_t1003) {
                gd::GdVal lv__a = _t1002->data[_t1003];
                lv__aft = gd::native_numeric_add(gd_ctx, lv__aft, gd::native_numeric_add(gd_ctx, gd::native_numeric_add(gd_ctx, gd::native_numeric_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv__a, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[57])), ([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv__a, SYM_GEN_occupiedCells_52), gd::GdVal::from_int(0LL))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[34])));
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[59]), gd::native_numeric_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[60]), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(this->f_ownerType)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), lv__b, lv__aft}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::native_numeric_mul(this->f_speedPerItem, gd::native_inline_call(gd_ctx, this->f_affectedItems, gd::SYM_size, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EchoingBattlecry::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_affectedItems, gd::SYM_empty, nullptr, 0))))) {
        gd::GdVal lv_item = gd::native_inline_call(gd_ctx, this->f_affectedItems, gd::SYM_pop_back, nullptr, 0);
        (void)gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_repeatCombatStart_130, nullptr, 0);
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_affectedItems, gd::SYM_empty, nullptr, 0))) {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
        }
        else {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EchoingBattlecry::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speedPerItem = gd::native_numeric_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[46])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__EchoingBattlecry(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__EchoingBattlecry>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,322u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__EchoingBattlecry = {CLS_Gd__gd_core_items__Exclusive__EchoingBattlecry, "EchoingBattlecry", "res://gd_core_items/Exclusive/EchoingBattlecry.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__EchoingBattlecry, &Gd__gd_core_items__Exclusive__EchoingBattlecry::get_static_prop_fn, &Gd__gd_core_items__Exclusive__EchoingBattlecry::call_static_fn};

void Gd__gd_core_items__Exclusive__Fedora::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_luckPerNature = gd::GdVal::null();
    this->f_luckPerTreasure = gd::GdVal::null();
    this->f_luckNeeded = gd::GdVal::null();
    this->f_numBuffs = gd::GdVal::null();
    this->f_bonusChance = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Fedora::meta() const { return &META_Gd__gd_core_items__Exclusive__Fedora; }
gd::GdVal Gd__gd_core_items__Exclusive__Fedora::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Fedora::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Fedora::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_luckPerNature_2258: out = this->f_luckPerNature; return true;
        case SYM_GEN_luckPerTreasure_2259: out = this->f_luckPerTreasure; return true;
        case SYM_GEN_luckNeeded_1874: out = this->f_luckNeeded; return true;
        case SYM_GEN_numBuffs_2005: out = this->f_numBuffs; return true;
        case SYM_GEN_bonusChance_2030: out = this->f_bonusChance; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Fedora::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_luckPerNature_2258: this->f_luckPerNature = val; return true;
        case SYM_GEN_luckPerTreasure_2259: this->f_luckPerTreasure = val; return true;
        case SYM_GEN_luckNeeded_1874: this->f_luckNeeded = val; return true;
        case SYM_GEN_numBuffs_2005: this->f_numBuffs = val; return true;
        case SYM_GEN_bonusChance_2030: this->f_bonusChance = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Fedora::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Fedora::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Fedora::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Fedora::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isTreasure_247, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(26LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Fedora::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canModifyChance_293, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Fedora::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1004 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, _ca, 1); })());
        gd::GdArr* _t1005 = (_t1004.kind == gd::GdVal::Kind::Arr) ? _t1004.arr : nullptr;
        uint32_t _len__t1006 = _t1005 ? _t1005->len : 0u;
        for (uint32_t _t1006 = 0; _t1006 < _len__t1006; ++_t1006) {
            gd::GdVal lv_item = _t1005->data[_t1006];
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusChance}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusChance_175, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Fedora::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numNature = gd::GdVal::from_int(0LL);
    gd::GdVal lv_numTreasure = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t1007 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1008 = (_t1007.kind == gd::GdVal::Kind::Arr) ? _t1007.arr : nullptr;
        uint32_t _len__t1009 = _t1008 ? _t1008->len : 0u;
        for (uint32_t _t1009 = 0; _t1009 < _len__t1009; ++_t1009) {
            gd::GdVal lv_item = _t1008->data[_t1009];
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isTreasure_247, nullptr, 0))) {
                lv_numTreasure = gd::native_numeric_add(gd_ctx, lv_numTreasure, gd::GdVal::from_int(1LL));
            }
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(26LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
                lv_numNature = gd::native_numeric_add(gd_ctx, lv_numNature, gd::GdVal::from_int(1LL));
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::native_numeric_add(gd_ctx, gd::native_numeric_mul(lv_numNature, this->f_luckPerNature), gd::native_numeric_mul(lv_numTreasure, this->f_luckPerTreasure))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Fedora::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), this->f_luckNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_luckNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useLucky_350, _ca, 1); })();
        gd::GdVal lv_buffs = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(101LL)}; return gd::native_inline_call(gd_ctx, lv_buffs, gd::SYM_erase, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_numBuffs, lv_event, lv_buffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_373, _ca, 3); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Fedora::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_numeric_add(gd_ctx, gd::GdVal::from_int(1000LL), gd::GdVal::from_int(5LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Fedora::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_luckPerNature = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[61])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_luckPerTreasure = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[62])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[63])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_numBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[36])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_bonusChance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[35])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Fedora(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Fedora>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,337u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Fedora = {CLS_Gd__gd_core_items__Exclusive__Fedora, "Fedora", "res://gd_core_items/Exclusive/Fedora.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Fedora, &Gd__gd_core_items__Exclusive__Fedora::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Fedora::call_static_fn};

void Gd__gd_core_items__Exclusive__FrozenBuckler::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Shield::init_fields(gd_ctx);
    this->f_coldInflicted = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__FrozenBuckler::meta() const { return &META_Gd__gd_core_items__Exclusive__FrozenBuckler; }
gd::GdVal Gd__gd_core_items__Exclusive__FrozenBuckler::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Shield::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__FrozenBuckler::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__FrozenBuckler::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_coldInflicted_2281: out = this->f_coldInflicted; return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__FrozenBuckler::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_coldInflicted_2281: this->f_coldInflicted = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__FrozenBuckler::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_afterBlock_1942: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__FrozenBuckler::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_afterBlock_1942: out = fn_afterBlock(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__FrozenBuckler::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Shield::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__FrozenBuckler::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_coldInflicted = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrozenBuckler::fn_afterBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), gd::native_inline_get_prop(gd_ctx, this->f_blockedDamageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drainStamina_117, _ca, 2); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_coldInflicted, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0))))) {
        this->f_coldInflicted = gd::gd_coerce_int(gd::native_numeric_add(gd_ctx, this->f_coldInflicted, gd::GdVal::from_int(1LL)));
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), gd::native_inline_get_prop(gd_ctx, this->f_blockedDamageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_351, _ca, 2); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrozenBuckler::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Shield::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__FrozenBuckler(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__FrozenBuckler>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,350u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FrozenBuckler = {CLS_Gd__gd_core_items__Exclusive__FrozenBuckler, "FrozenBuckler", "res://gd_core_items/Exclusive/FrozenBuckler.gd", &META_Gd__gd_core_items__Shield, true, _alloc_Gd__gd_core_items__Exclusive__FrozenBuckler, &Gd__gd_core_items__Exclusive__FrozenBuckler::get_static_prop_fn, &Gd__gd_core_items__Exclusive__FrozenBuckler::call_static_fn};

void Gd__gd_core_items__Exclusive__Hedgehog::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__ForestFriend::init_fields(gd_ctx);
    this->f_hasActivated = gd::GdVal::from_bool(false);
    this->f_spikes = gd::GdVal::null();
    this->f_damagePerSpike = gd::GdVal::null();
    this->f_healthThreshold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Hedgehog::meta() const { return &META_Gd__gd_core_items__Exclusive__Hedgehog; }
gd::GdVal Gd__gd_core_items__Exclusive__Hedgehog::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__ForestFriend::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Hedgehog::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Hedgehog::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_hasActivated_1906: out = this->f_hasActivated; return true;
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        case SYM_GEN_damagePerSpike_2304: out = this->f_damagePerSpike; return true;
        case SYM_GEN_healthThreshold_1854: out = this->f_healthThreshold; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__ForestFriend::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Hedgehog::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hasActivated_1906: this->f_hasActivated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        case SYM_GEN_damagePerSpike_2304: this->f_damagePerSpike = val; return true;
        case SYM_GEN_healthThreshold_1854: this->f_healthThreshold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__ForestFriend::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Hedgehog::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onDamaged_1855: return true;
        case SYM_GEN_onHPLow_2305: return true;
        case SYM_GEN_spawnSpikeParticles_2306: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__ForestFriend::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Hedgehog::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1855: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN_onHPLow_2305: out = fn_onHPLow(args, argc); return true;
        case SYM_GEN_spawnSpikeParticles_2306: out = fn_spawnSpikeParticles(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__ForestFriend::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Hedgehog::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__ForestFriend::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Hedgehog::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dam = gd::native_numeric_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1675), gd::native_numeric_mul(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getSpikes_1223, nullptr, 0), this->f_damagePerSpike));
    gd::GdVal lv_res = ([&]() { gd::GdVal _ca[] = {lv_dam}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealEffectDamage_221, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hedgehog::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[22]), gd::GdVal::from_str(&battle_string_literals[23])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hedgehog::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(this->f_hasActivated)) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRelativeHealth_302, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onHPLow_2305, _ca, 1); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hedgehog::fn_onHPLow(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_spikes, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), gd::GdVal::from_bool(true), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 3); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_spawnSpikeParticles_2306, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hedgehog::fn_spawnSpikeParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hedgehog::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_numeric_add(gd_ctx, gd::GdVal::from_int(1000LL), gd::GdVal::from_int(3LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hedgehog::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__ForestFriend::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[64])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_damagePerSpike = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[65])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_healthThreshold = gd::native_numeric_sub(gd::native_numeric_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[66])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1550, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Hedgehog(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Hedgehog>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,366u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Hedgehog = {CLS_Gd__gd_core_items__Exclusive__Hedgehog, "Hedgehog", "res://gd_core_items/Exclusive/Hedgehog.gd", &META_Gd__gd_core_items__Exclusive__ForestFriend, true, _alloc_Gd__gd_core_items__Exclusive__Hedgehog, &Gd__gd_core_items__Exclusive__Hedgehog::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Hedgehog::call_static_fn};

void Gd__gd_core_items__RibSawBlade::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_opponentWeapons = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_removeDam = gd::GdVal::null();
    this->f_bonusDam = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__RibSawBlade::meta() const { return &META_Gd__gd_core_items__RibSawBlade; }
gd::GdVal Gd__gd_core_items__RibSawBlade::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__RibSawBlade::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__RibSawBlade::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_opponentWeapons_1971: out = this->f_opponentWeapons; return true;
        case SYM_GEN_removeDam_1972: out = this->f_removeDam; return true;
        case SYM_GEN_bonusDam_1875: out = this->f_bonusDam; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__RibSawBlade::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_opponentWeapons_1971: this->f_opponentWeapons = val; return true;
        case SYM_GEN_removeDam_1972: this->f_removeDam = val; return true;
        case SYM_GEN_bonusDam_1875: this->f_bonusDam = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__RibSawBlade::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__RibSawBlade::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__RibSawBlade::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__RibSawBlade::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_opponentWeapons, gd::SYM_clear, nullptr, 0);
    {
        gd::GdVal _t1010 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_INVENTORY_1093), SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t1011 = (_t1010.kind == gd::GdVal::Kind::Arr) ? _t1010.arr : nullptr;
        uint32_t _len__t1012 = _t1011 ? _t1011->len : 0u;
        for (uint32_t _t1012 = 0; _t1012 < _len__t1012; ++_t1012) {
            gd::GdVal lv_item = _t1011->data[_t1012];
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, this->f_opponentWeapons, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RibSawBlade::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        {
            gd::GdVal _t1013 = gd::gd_iter_seq(gd_ctx.arena, this->f_opponentWeapons);
            gd::GdArr* _t1014 = (_t1013.kind == gd::GdVal::Kind::Arr) ? _t1013.arr : nullptr;
            uint32_t _len__t1015 = _t1014 ? _t1014->len : 0u;
            for (uint32_t _t1015 = 0; _t1015 < _len__t1015; ++_t1015) {
                gd::GdVal lv_weapon = _t1014->data[_t1015];
                (void)([&]() { gd::GdVal _ca[] = {this->f_removeDam}; return gd::native_inline_call(gd_ctx, lv_weapon, SYM_GEN_purgeDamage_311, _ca, 1); })();
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {this->f_bonusDam}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RibSawBlade::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_removeDam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[56])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_bonusDam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[67])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__RibSawBlade(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__RibSawBlade>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,636u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__RibSawBlade = {CLS_Gd__gd_core_items__RibSawBlade, "RibSawBlade", "res://gd_core_items/RibSawBlade.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__RibSawBlade, &Gd__gd_core_items__RibSawBlade::get_static_prop_fn, &Gd__gd_core_items__RibSawBlade::call_static_fn};

void Gd__gd_core_items__Exclusive__LuckyShortbow::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__LuckyShortbow::meta() const { return &META_Gd__gd_core_items__Exclusive__LuckyShortbow; }
gd::GdVal Gd__gd_core_items__Exclusive__LuckyShortbow::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__LuckyShortbow::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__LuckyShortbow::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__LuckyShortbow::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__LuckyShortbow::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__LuckyShortbow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__LuckyShortbow::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyShortbow::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyShortbow::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__LuckyShortbow(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__LuckyShortbow>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,396u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__LuckyShortbow = {CLS_Gd__gd_core_items__Exclusive__LuckyShortbow, "LuckyShortbow", "res://gd_core_items/Exclusive/LuckyShortbow.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__LuckyShortbow, &Gd__gd_core_items__Exclusive__LuckyShortbow::get_static_prop_fn, &Gd__gd_core_items__Exclusive__LuckyShortbow::call_static_fn};

void Gd__gd_core_items__Exclusive__MoltenDagger::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Dagger::init_fields(gd_ctx);
    this->f_heatNeeded = gd::GdVal::null();
    this->f_bonusDam = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__MoltenDagger::meta() const { return &META_Gd__gd_core_items__Exclusive__MoltenDagger; }
gd::GdVal Gd__gd_core_items__Exclusive__MoltenDagger::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Dagger::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__MoltenDagger::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__MoltenDagger::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_heatNeeded_1880: out = this->f_heatNeeded; return true;
        case SYM_GEN_bonusDam_1875: out = this->f_bonusDam; return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MoltenDagger::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heatNeeded_1880: this->f_heatNeeded = val; return true;
        case SYM_GEN_bonusDam_1875: this->f_bonusDam = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MoltenDagger::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MoltenDagger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__MoltenDagger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Dagger::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenDagger::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getHeat_1251, nullptr, 0), this->f_heatNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_bonusDam}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_heatNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useHeat_354, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenDagger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Dagger::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_heatNeeded = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    this->f_bonusDam = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MoltenDagger(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__MoltenDagger>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,412u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MoltenDagger = {CLS_Gd__gd_core_items__Exclusive__MoltenDagger, "MoltenDagger", "res://gd_core_items/Exclusive/MoltenDagger.gd", &META_Gd__gd_core_items__Dagger, true, _alloc_Gd__gd_core_items__Exclusive__MoltenDagger, &Gd__gd_core_items__Exclusive__MoltenDagger::get_static_prop_fn, &Gd__gd_core_items__Exclusive__MoltenDagger::call_static_fn};

void Gd__gd_core_items__Exclusive__Phoenix::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_ashSprite = gd::GdVal::null();
    this->f_deathPrevented = gd::GdVal::from_bool(false);
    this->f_normalSprite = gd::GdVal::null();
    this->f_selfDam = gd::GdVal::from_int(0);
    this->f_reincarnateHealth = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Phoenix::meta() const { return &META_Gd__gd_core_items__Exclusive__Phoenix; }
gd::GdVal Gd__gd_core_items__Exclusive__Phoenix::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Phoenix::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Phoenix::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_ashSprite_2422: out = this->f_ashSprite; return true;
        case SYM_GEN_deathPrevented_2191: out = this->f_deathPrevented; return true;
        case SYM_GEN_normalSprite_2192: out = this->f_normalSprite; return true;
        case SYM_GEN_selfDam_2423: out = this->f_selfDam; return true;
        case SYM_GEN_reincarnateHealth_2424: out = this->f_reincarnateHealth; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Phoenix::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_ashSprite_2422: this->f_ashSprite = val; return true;
        case SYM_GEN_deathPrevented_2191: this->f_deathPrevented = val; return true;
        case SYM_GEN_normalSprite_2192: this->f_normalSprite = val; return true;
        case SYM_GEN_selfDam_2423: this->f_selfDam = gd::gd_coerce_int(val); return true;
        case SYM_GEN_reincarnateHealth_2424: this->f_reincarnateHealth = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Phoenix::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onDamaged_1855: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Phoenix::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1855: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Phoenix::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Phoenix::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[22]), gd::GdVal::from_str(&battle_string_literals[23])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Phoenix::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(this->f_deathPrevented)) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getCurrentHealth_1154, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_heat = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getHeat_1251, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_heat, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
            gd::GdVal lv_event2 = ([&]() { gd::GdVal _ca[] = {gd::native_numeric_mul(this->f_reincarnateHealth, lv_heat), gd::GdVal::from_bool(false), gd::GdVal::from_obj(this), lv_event}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_reincarnate_1153, _ca, 4); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_heat, lv_event2}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useHeat_354, _ca, 2); })();
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Phoenix::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getCurrentHealth_1154, nullptr, 0), this->f_selfDam)))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_selfDam, gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_loseHealth_1157, _ca, 2); })();
            gd::GdVal lv_res = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_220, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Phoenix::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Phoenix::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__deathPrevented = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv__deathPrevented)) {
    }
    else {
    }
    this->f_deathPrevented = lv__deathPrevented;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Phoenix::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_selfDam = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[68])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_reincarnateHealth = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[69])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Phoenix(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Phoenix>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,428u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Phoenix = {CLS_Gd__gd_core_items__Exclusive__Phoenix, "Phoenix", "res://gd_core_items/Exclusive/Phoenix.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__Phoenix, &Gd__gd_core_items__Exclusive__Phoenix::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Phoenix::call_static_fn};

void Gd__gd_core_items__Exclusive__PrismaticWand::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_buffs = gd::GdVal::null();
    this->f_manaNeeded = gd::GdVal::null();
    this->f_luckNeeded = gd::GdVal::null();
    this->f_regenNeeded = gd::GdVal::null();
    this->f_empower = gd::GdVal::null();
    this->f_buffsToUse = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PrismaticWand::meta() const { return &META_Gd__gd_core_items__Exclusive__PrismaticWand; }
gd::GdVal Gd__gd_core_items__Exclusive__PrismaticWand::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PrismaticWand::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PrismaticWand::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_buffs_1048: out = this->f_buffs; return true;
        case SYM_GEN_manaNeeded_1881: out = this->f_manaNeeded; return true;
        case SYM_GEN_luckNeeded_1874: out = this->f_luckNeeded; return true;
        case SYM_GEN_regenNeeded_942: out = this->f_regenNeeded; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        case SYM_GEN_buffsToUse_2446: out = this->f_buffsToUse; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PrismaticWand::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffs_1048: this->f_buffs = val; return true;
        case SYM_GEN_manaNeeded_1881: this->f_manaNeeded = val; return true;
        case SYM_GEN_luckNeeded_1874: this->f_luckNeeded = val; return true;
        case SYM_GEN_regenNeeded_942: this->f_regenNeeded = val; return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        case SYM_GEN_buffsToUse_2446: this->f_buffsToUse = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PrismaticWand::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PrismaticWand::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PrismaticWand::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PrismaticWand::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveAllBuffs_370, nullptr, 0);
    gd::GdVal lv_mana = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0);
    gd::GdVal lv_luck = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0);
    gd::GdVal lv_regen = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRegeneration_1233, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_mana, this->f_manaNeeded))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_luck, this->f_luckNeeded)))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_regen, this->f_regenNeeded))))))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_buffsToUse, gd::GdVal::null(), gd::GdVal::from_bool(true), this->f_buffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeMostBuffs_368, _ca, 4); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_empower, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 2); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PrismaticWand::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_buffs = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(105LL), gd::GdVal::from_int(101LL), gd::GdVal::from_int(102LL)}));
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[70])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[63])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regenNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[71])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[72])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_buffsToUse = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[73])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PrismaticWand(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__PrismaticWand>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,444u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PrismaticWand = {CLS_Gd__gd_core_items__Exclusive__PrismaticWand, "PrismaticWand", "res://gd_core_items/Exclusive/PrismaticWand.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__PrismaticWand, &Gd__gd_core_items__Exclusive__PrismaticWand::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PrismaticWand::call_static_fn};

void Gd__gd_core_items__Exclusive__RandomLoadoutBag::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bag::init_fields(gd_ctx);
    this->f_mainBags = ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 7); d->set(gd_ctx.arena, gd::GdVal::from_int(0LL), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_str(&battle_string_literals[74]), gd::GdVal::from_str(&battle_string_literals[75])}))); d->set(gd_ctx.arena, gd::GdVal::from_int(1LL), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_str(&battle_string_literals[76]), gd::GdVal::from_str(&battle_string_literals[77])}))); d->set(gd_ctx.arena, gd::GdVal::from_int(3LL), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_str(&battle_string_literals[78]), gd::GdVal::from_str(&battle_string_literals[79])}))); d->set(gd_ctx.arena, gd::GdVal::from_int(2LL), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_str(&battle_string_literals[80]), gd::GdVal::from_str(&battle_string_literals[81])}))); d->set(gd_ctx.arena, gd::GdVal::from_int(4LL), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_str(&battle_string_literals[82]), gd::GdVal::from_str(&battle_string_literals[83])}))); d->set(gd_ctx.arena, gd::GdVal::from_int(5LL), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_str(&battle_string_literals[84]), gd::GdVal::from_str(&battle_string_literals[85])}))); d->set(gd_ctx.arena, gd::GdVal::from_int(6LL), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_str(&battle_string_literals[86]), gd::GdVal::from_str(&battle_string_literals[87])}))); return gd::GdVal::from_dict(d); })();
    this->f_compensationValue = ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 7); d->set(gd_ctx.arena, gd::GdVal::from_int(0LL), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(0LL)}))); d->set(gd_ctx.arena, gd::GdVal::from_int(1LL), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(1LL), gd::GdVal::from_int(0LL)}))); d->set(gd_ctx.arena, gd::GdVal::from_int(3LL), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(2LL), gd::GdVal::from_int(1LL)}))); d->set(gd_ctx.arena, gd::GdVal::from_int(2LL), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(1LL), gd::GdVal::from_int(0LL)}))); d->set(gd_ctx.arena, gd::GdVal::from_int(4LL), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(0LL)}))); d->set(gd_ctx.arena, gd::GdVal::from_int(5LL), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(0LL)}))); d->set(gd_ctx.arena, gd::GdVal::from_int(6LL), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(0LL)}))); return gd::GdVal::from_dict(d); })();
    this->f_excludeNames = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_str(&battle_string_literals[88]), gd::GdVal::from_str(&battle_string_literals[89]), gd::GdVal::from_str(&battle_string_literals[90]), gd::GdVal::from_str(&battle_string_literals[91]), gd::GdVal::from_str(&battle_string_literals[92])}));
    this->f_bagCells = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__RandomLoadoutBag::meta() const { return &META_Gd__gd_core_items__Exclusive__RandomLoadoutBag; }
gd::GdVal Gd__gd_core_items__Exclusive__RandomLoadoutBag::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_bagRarityWeights_2459: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 5); d->set(gd_ctx.arena, gd::GdVal::from_int(0LL), gd::GdVal::from_int(2LL)); d->set(gd_ctx.arena, gd::GdVal::from_int(1LL), gd::GdVal::from_float(0.5)); d->set(gd_ctx.arena, gd::GdVal::from_int(2LL), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_int(3LL), gd::GdVal::from_float(0.1)); d->set(gd_ctx.arena, gd::GdVal::from_int(4LL), gd::GdVal::from_float(0.05)); return gd::GdVal::from_dict(d); })();
        default: break;
    }
    return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__RandomLoadoutBag::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__RandomLoadoutBag::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_mainBags_2457: out = this->f_mainBags; return true;
        case SYM_GEN_compensationValue_2458: out = this->f_compensationValue; return true;
        case SYM_GEN_excludeNames_2460: out = this->f_excludeNames; return true;
        case SYM_GEN_bagCells_1601: out = this->f_bagCells; return true;
        case SYM_GEN_bagRarityWeights_2459: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__RandomLoadoutBag::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_mainBags_2457: this->f_mainBags = val; return true;
        case SYM_GEN_compensationValue_2458: this->f_compensationValue = val; return true;
        case SYM_GEN_excludeNames_2460: this->f_excludeNames = val; return true;
        case SYM_GEN_bagCells_1601: this->f_bagCells = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__RandomLoadoutBag::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_addBagWherePossible_2461: return true;
        case SYM_GEN_addItemWherePossible_2462: return true;
        case SYM_GEN_shopOpened_2463: return true;
        case SYM_GEN_prepareParticles_2464: return true;
        case SYM_GEN_createRevealParticles_2465: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__RandomLoadoutBag::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_addBagWherePossible_2461: out = fn_addBagWherePossible(args, argc); return true;
        case SYM_GEN_addItemWherePossible_2462: out = fn_addItemWherePossible(args, argc); return true;
        case SYM_GEN_shopOpened_2463: out = fn_shopOpened(args, argc); return true;
        case SYM_GEN_prepareParticles_2464: out = fn_prepareParticles(args, argc); return true;
        case SYM_GEN_createRevealParticles_2465: out = fn_createRevealParticles(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__RandomLoadoutBag::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__RandomLoadoutBag::fn_addBagWherePossible(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bag = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_startPos = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RandomLoadoutBag::fn_addItemWherePossible(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RandomLoadoutBag::fn_shopOpened(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RandomLoadoutBag::fn_prepareParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[93]), gd::GdVal::from_float(0.4)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_callDelayed_1479, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RandomLoadoutBag::fn_createRevealParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RandomLoadoutBag::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__RandomLoadoutBag(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__RandomLoadoutBag>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,460u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RandomLoadoutBag = {CLS_Gd__gd_core_items__Exclusive__RandomLoadoutBag, "RandomLoadoutBag", "res://gd_core_items/Exclusive/RandomLoadoutBag.gd", &META_Gd__gd_core_items__Bag, true, _alloc_Gd__gd_core_items__Exclusive__RandomLoadoutBag, &Gd__gd_core_items__Exclusive__RandomLoadoutBag::get_static_prop_fn, &Gd__gd_core_items__Exclusive__RandomLoadoutBag::call_static_fn};

void Gd__gd_core_items__Exclusive__Scissorswords::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Lightsaber::init_fields(gd_ctx);
    this->f_luckNeeded = gd::GdVal::null();
    this->f_bonusDam = gd::GdVal::null();
    this->f_luck = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Scissorswords::meta() const { return &META_Gd__gd_core_items__Exclusive__Scissorswords; }
gd::GdVal Gd__gd_core_items__Exclusive__Scissorswords::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Lightsaber::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Scissorswords::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Scissorswords::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_luckNeeded_1874: out = this->f_luckNeeded; return true;
        case SYM_GEN_bonusDam_1875: out = this->f_bonusDam; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core_items__Lightsaber::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Scissorswords::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_luckNeeded_1874: this->f_luckNeeded = val; return true;
        case SYM_GEN_bonusDam_1875: this->f_bonusDam = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Lightsaber::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Scissorswords::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_inflict_1913: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Lightsaber::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Scissorswords::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_inflict_1913: out = fn_inflict(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Lightsaber::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Scissorswords::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Lightsaber::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Scissorswords::fn_inflict(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_duration = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_duration, lv_event}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Lightsaber::call_method(gd_ctx, SYM_GEN_inflict_1913, _ca, 2, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_int(109LL), this->f_blind, lv_duration, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacksTemporary_202, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scissorswords::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), this->f_luckNeeded)))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_luckNeeded, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useLucky_350, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusDam}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_regen, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 2); })();
        }
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scissorswords::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Lightsaber::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[63])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_bonusDam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[56])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[61])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[94])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Scissorswords(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Scissorswords>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,475u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Scissorswords = {CLS_Gd__gd_core_items__Exclusive__Scissorswords, "Scissorswords", "res://gd_core_items/Exclusive/Scissorswords.gd", &META_Gd__gd_core_items__Lightsaber, true, _alloc_Gd__gd_core_items__Exclusive__Scissorswords, &Gd__gd_core_items__Exclusive__Scissorswords::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Scissorswords::call_static_fn};

void Gd__gd_core_items__Exclusive__SmithingForDummies::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_boostedWhetstones = gd::GdVal::from_int(0LL);
    this->f_whetstoneDescriptor = gd::GdVal::null();
    this->f_staminaReduction = gd::GdVal::null();
    this->f_bonusDamage = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SmithingForDummies::meta() const { return &META_Gd__gd_core_items__Exclusive__SmithingForDummies; }
gd::GdVal Gd__gd_core_items__Exclusive__SmithingForDummies::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SmithingForDummies::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SmithingForDummies::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_boostedWhetstones_2510: out = this->f_boostedWhetstones; return true;
        case SYM_GEN_whetstoneDescriptor_2511: out = this->f_whetstoneDescriptor; return true;
        case SYM_GEN_staminaReduction_2013: out = this->f_staminaReduction; return true;
        case SYM_GEN_bonusDamage_904: out = this->f_bonusDamage; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SmithingForDummies::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_boostedWhetstones_2510: this->f_boostedWhetstones = val; return true;
        case SYM_GEN_whetstoneDescriptor_2511: this->f_whetstoneDescriptor = val; return true;
        case SYM_GEN_staminaReduction_2013: this->f_staminaReduction = val; return true;
        case SYM_GEN_bonusDamage_904: this->f_bonusDamage = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SmithingForDummies::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onBought_455: return true;
        case SYM_GEN_onItemRoll_2018: return true;
        case SYM_GEN_onItemRolled_2019: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SmithingForDummies::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onBought_455: out = fn_onBought(args, argc); return true;
        case SYM_GEN_onItemRoll_2018: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_2019: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SmithingForDummies::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SmithingForDummies::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_boostedWhetstones;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SmithingForDummies::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_data, gd::GdVal::null())))) {
        this->f_boostedWhetstones = lv_data;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SmithingForDummies::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isWeapon_82, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isCrafted_800, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SmithingForDummies::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1016 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1017 = (_t1016.kind == gd::GdVal::Kind::Arr) ? _t1016.arr : nullptr;
        uint32_t _len__t1018 = _t1017 ? _t1017->len : 0u;
        for (uint32_t _t1018 = 0; _t1018 < _len__t1018; ++_t1018) {
            gd::GdVal lv_item = _t1017->data[_t1018];
            (void)([&]() { gd::GdVal _ca[] = {this->f_staminaReduction}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeStaminaFactor_305, _ca, 1); })();
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canDamage_89, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_bonusDamage}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
            }
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SmithingForDummies::fn_onBought(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SmithingForDummies::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SmithingForDummies::fn_onItemRolled(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_descr, this->f_whetstoneDescriptor)))) {
        this->f_boostedWhetstones = gd::native_numeric_sub(this->f_boostedWhetstones, gd::GdVal::from_int(1LL));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SmithingForDummies::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_whetstoneDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[95])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_staminaReduction = gd::gd_neg(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[11])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_bonusDamage = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[56])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SmithingForDummies(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__SmithingForDummies>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,492u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SmithingForDummies = {CLS_Gd__gd_core_items__Exclusive__SmithingForDummies, "SmithingForDummies", "res://gd_core_items/Exclusive/SmithingForDummies.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__SmithingForDummies, &Gd__gd_core_items__Exclusive__SmithingForDummies::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SmithingForDummies::call_static_fn};

void Gd__gd_core_items__Exclusive__SpikedStaff::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_manaCost = gd::GdVal::null();
    this->f_empower = gd::GdVal::null();
    this->f_spikes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SpikedStaff::meta() const { return &META_Gd__gd_core_items__Exclusive__SpikedStaff; }
gd::GdVal Gd__gd_core_items__Exclusive__SpikedStaff::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SpikedStaff::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SpikedStaff::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_manaCost_1815: out = this->f_manaCost; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SpikedStaff::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaCost_1815: this->f_manaCost = val; return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SpikedStaff::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SpikedStaff::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SpikedStaff::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SpikedStaff::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_333, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_event, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_empower, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 2); })();
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_isBattleRaging_1207, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_spikes, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpikedStaff::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_manaCost = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[96])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_empower = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[72])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_spikes = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[64])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SpikedStaff(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__SpikedStaff>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,508u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpikedStaff = {CLS_Gd__gd_core_items__Exclusive__SpikedStaff, "SpikedStaff", "res://gd_core_items/Exclusive/SpikedStaff.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__SpikedStaff, &Gd__gd_core_items__Exclusive__SpikedStaff::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SpikedStaff::call_static_fn};

void Gd__gd_core_items__Exclusive__StrongDivinePotion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__DivinePotion::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__StrongDivinePotion::meta() const { return &META_Gd__gd_core_items__Exclusive__StrongDivinePotion; }
gd::GdVal Gd__gd_core_items__Exclusive__StrongDivinePotion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__DivinePotion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__StrongDivinePotion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__StrongDivinePotion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Exclusive__DivinePotion::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__StrongDivinePotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Exclusive__DivinePotion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__StrongDivinePotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__DivinePotion::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__StrongDivinePotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__DivinePotion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__StrongDivinePotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__DivinePotion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__StrongDivinePotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__DivinePotion::call_method(gd_ctx, SYM_GEN_onTriggerPotion_1849, _ca, 1, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StrongDivinePotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__DivinePotion::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__StrongDivinePotion(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__StrongDivinePotion>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,525u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StrongDivinePotion = {CLS_Gd__gd_core_items__Exclusive__StrongDivinePotion, "StrongDivinePotion", "res://gd_core_items/Exclusive/StrongDivinePotion.gd", &META_Gd__gd_core_items__Exclusive__DivinePotion, true, _alloc_Gd__gd_core_items__Exclusive__StrongDivinePotion, &Gd__gd_core_items__Exclusive__StrongDivinePotion::get_static_prop_fn, &Gd__gd_core_items__Exclusive__StrongDivinePotion::call_static_fn};

void Gd__gd_core_items__Exclusive__ToastGoobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Goobert::init_fields(gd_ctx);
    this->f_staminaThreshold = gd::GdVal::null();
    this->f_stamina = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ToastGoobert::meta() const { return &META_Gd__gd_core_items__Exclusive__ToastGoobert; }
gd::GdVal Gd__gd_core_items__Exclusive__ToastGoobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ToastGoobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ToastGoobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_staminaThreshold_2075: out = this->f_staminaThreshold; return true;
        case SYM_GEN_stamina_2156: out = this->f_stamina; return true;
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ToastGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaThreshold_2075: this->f_staminaThreshold = val; return true;
        case SYM_GEN_stamina_2156: this->f_stamina = val; return true;
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ToastGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ToastGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ToastGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ToastGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getCurrentStamina_1262, nullptr, 0), this->f_staminaThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_stamina}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_318, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ToastGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_staminaThreshold = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[97])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[11])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[94])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ToastGoobert(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__ToastGoobert>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,541u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ToastGoobert = {CLS_Gd__gd_core_items__Exclusive__ToastGoobert, "ToastGoobert", "res://gd_core_items/Exclusive/ToastGoobert.gd", &META_Gd__gd_core_items__Goobert, true, _alloc_Gd__gd_core_items__Exclusive__ToastGoobert, &Gd__gd_core_items__Exclusive__ToastGoobert::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ToastGoobert::call_static_fn};

void Gd__gd_core_items__Exclusive__Whetstone3::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Whetstone::init_fields(gd_ctx);
    this->f_blockFactor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Whetstone3::meta() const { return &META_Gd__gd_core_items__Exclusive__Whetstone3; }
gd::GdVal Gd__gd_core_items__Exclusive__Whetstone3::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Whetstone::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Whetstone3::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Whetstone3::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_blockFactor_1977: out = this->f_blockFactor; return true;
        default: break;
    }
    return Gd__gd_core_items__Whetstone::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Whetstone3::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockFactor_1977: this->f_blockFactor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Whetstone::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Whetstone3::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Whetstone::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Whetstone3::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Whetstone::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Whetstone3::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Whetstone::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Whetstone3::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBlock_291, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Whetstone::call_method(gd_ctx, SYM_GEN_canAffect_286, _ca, 1, _out); return _out; })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Whetstone3::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1019 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1020 = (_t1019.kind == gd::GdVal::Kind::Arr) ? _t1019.arr : nullptr;
        uint32_t _len__t1021 = _t1020 ? _t1020->len : 0u;
        for (uint32_t _t1021 = 0; _t1021 < _len__t1021; ++_t1021) {
            gd::GdVal lv_item = _t1020->data[_t1021];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(100LL), this->f_blockFactor}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_giveBuffPower_303, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Whetstone3::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Whetstone::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_blockFactor = gd::native_numeric_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[98])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Whetstone3(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Whetstone3>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,557u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Whetstone3 = {CLS_Gd__gd_core_items__Exclusive__Whetstone3, "Whetstone3", "res://gd_core_items/Exclusive/Whetstone3.gd", &META_Gd__gd_core_items__Whetstone, true, _alloc_Gd__gd_core_items__Exclusive__Whetstone3, &Gd__gd_core_items__Exclusive__Whetstone3::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Whetstone3::call_static_fn};

void Gd__gd_core_items__Gems__LumpofCoal::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Gems__Gem::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Gems__LumpofCoal::meta() const { return &META_Gd__gd_core_items__Gems__LumpofCoal; }
gd::GdVal Gd__gd_core_items__Gems__LumpofCoal::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_gemColor_995: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.132813), gd::GdVal::from_float(0.132813), gd::GdVal::from_float(0.132813)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Gems__LumpofCoal::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Gems__LumpofCoal::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_gemColor_995: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Gems__LumpofCoal::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Gems__LumpofCoal::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canBlock_291: return true;
        case SYM_GEN_prepareWeapon_982: return true;
        case SYM_GEN_preAttack_996: return true;
        case SYM_GEN_prepareArmor_983: return true;
        case SYM_GEN_combatStartArmor_986: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Gems__LumpofCoal::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canBlock_291: out = fn_canBlock(args, argc); return true;
        case SYM_GEN_prepareWeapon_982: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_preAttack_996: out = fn_preAttack(args, argc); return true;
        case SYM_GEN_prepareArmor_983: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_combatStartArmor_986: out = fn_combatStartArmor(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: out = fn_onHotSwapHoverWithGemEnd(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Gems__LumpofCoal::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Gems__LumpofCoal::fn_canBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__LumpofCoal::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, this->f_socket, SYM_GEN_getItem_389, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[99]), gd::GdVal::from_str(&battle_string_literals[100])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__LumpofCoal::fn_preAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::native_numeric_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)));
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__LumpofCoal::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_round(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDebuffResistStacks_1185, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__LumpofCoal::fn_combatStartArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_round(gd::native_numeric_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0)))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__LumpofCoal::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictRandomDebuffs_357, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__LumpofCoal::fn_onHotSwapHoverWithGemEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__LumpofCoal::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Gems__LumpofCoal(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Gems__LumpofCoal>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,576u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Gems__LumpofCoal = {CLS_Gd__gd_core_items__Gems__LumpofCoal, "LumpofCoal", "res://gd_core_items/Gems/LumpofCoal.gd", &META_Gd__gd_core_items__Gems__Gem, true, _alloc_Gd__gd_core_items__Gems__LumpofCoal, &Gd__gd_core_items__Gems__LumpofCoal::get_static_prop_fn, &Gd__gd_core_items__Gems__LumpofCoal::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core_items__HolySpear_SpearState[] = {{"Inactive", 0LL}, {"Active", 1LL}, {"Used", 2LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__HolySpear_SpearState = {"SpearState", _ekv_Gd__gd_core_items__HolySpear_SpearState, 3u};
void Gd__gd_core_items__HolySpear::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_blockRemoval = gd::GdVal::from_int(0);
    this->f_cleanses = gd::GdVal::from_int(0);
    this->f_spearState = gd::GdVal::from_int(0);
    this->f_activationParticles = gd::GdVal::null();
    this->f_buffTimer = gd::GdVal::null();
    this->f_blockRemovalPerSlot = gd::GdVal::from_int(0);
    this->f_buffedSpeed = gd::GdVal::null();
    this->f_manaCost = gd::GdVal::from_int(0);
    this->f_light = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__HolySpear::meta() const { return &META_Gd__gd_core_items__HolySpear; }
gd::GdVal Gd__gd_core_items__HolySpear::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_SpearState_1902: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__HolySpear_SpearState);
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__HolySpear::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__HolySpear::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_blockRemoval_1897: out = this->f_blockRemoval; return true;
        case SYM_GEN_cleanses_1898: out = this->f_cleanses; return true;
        case SYM_GEN_spearState_1899: out = this->f_spearState; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_buffTimer_1819: out = this->f_buffTimer; return true;
        case SYM_GEN_blockRemovalPerSlot_1900: out = this->f_blockRemovalPerSlot; return true;
        case SYM_GEN_buffedSpeed_1901: out = this->f_buffedSpeed; return true;
        case SYM_GEN_manaCost_1815: out = this->f_manaCost; return true;
        case SYM_GEN_light_949: out = this->f_light; return true;
        case SYM_GEN_SpearState_1902: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__HolySpear_SpearState); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__HolySpear::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockRemoval_1897: this->f_blockRemoval = gd::gd_coerce_int(val); return true;
        case SYM_GEN_cleanses_1898: this->f_cleanses = gd::gd_coerce_int(val); return true;
        case SYM_GEN_spearState_1899: this->f_spearState = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_buffTimer_1819: this->f_buffTimer = val; return true;
        case SYM_GEN_blockRemovalPerSlot_1900: this->f_blockRemovalPerSlot = gd::gd_coerce_int(val); return true;
        case SYM_GEN_buffedSpeed_1901: this->f_buffedSpeed = val; return true;
        case SYM_GEN_manaCost_1815: this->f_manaCost = gd::gd_coerce_int(val); return true;
        case SYM_GEN_light_949: this->f_light = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__HolySpear::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_affectsEmpty_255: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreDealDamage_late_906: return true;
        case SYM_GEN_onInvuEnded_1820: return true;
        case SYM_GEN_checkTrigger_1821: return true;
        case SYM_GEN_buffEnded_1817: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__HolySpear::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_affectsEmpty_255: out = fn_affectsEmpty(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_late_906: out = fn_onPreDealDamage_late(args, argc); return true;
        case SYM_GEN_onInvuEnded_1820: out = fn_onInvuEnded(args, argc); return true;
        case SYM_GEN_checkTrigger_1821: out = fn_checkTrigger(args, argc); return true;
        case SYM_GEN_buffEnded_1817: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__HolySpear::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__HolySpear::fn_affectsEmpty(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HolySpear::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HolySpear::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numSlots = gd::native_numeric_add(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumEmptyAffectedCells_426, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0));
    this->f_blockRemoval = gd::gd_coerce_int(gd::native_numeric_mul(this->f_blockRemovalPerSlot, lv_numSlots));
    this->f_cleanses = gd::gd_coerce_int(lv_numSlots);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[101]), gd::GdVal::from_str(&battle_string_literals[102])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[103]), gd::GdVal::from_str(&battle_string_literals[104])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HolySpear::fn_onPreDealDamage_late(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_blockRemoval}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeBlock_205, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_cleanses}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_356, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HolySpear::fn_onInvuEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkTrigger_1821, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HolySpear::fn_checkTrigger(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_spearState, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_isVulnerable_1291, nullptr, 0))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkMana_331, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
        gd::GdVal lv_invuDur = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[105])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_invuDur, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_makeInvulnerable_1211, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_invuDur}; return gd::native_inline_call(gd_ctx, this->f_buffTimer, SYM_GEN_start_1779, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_manaCost, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_numeric_div(gd_ctx, this->f_buffedSpeed, gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HolySpear::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_numeric_div(gd_ctx, this->f_buffedSpeed, gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_reduceSpeed_274, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HolySpear::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HolySpear::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HolySpear::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__spearState = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv__spearState, gd::GdVal::from_int(0LL))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv__spearState, gd::GdVal::from_int(1LL))))) {
    }
    else {
    }
    this->f_spearState = gd::gd_coerce_int(lv__spearState);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HolySpear::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_numeric_add(gd_ctx, gd::GdVal::from_int(0LL), gd::GdVal::from_int(2LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HolySpear::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[106]), gd::GdVal::from_str(&battle_string_literals[107]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_blockRemovalPerSlot = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    this->f_buffedSpeed = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0);
    this->f_manaCost = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__HolySpear(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__HolySpear>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,595u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__HolySpear = {CLS_Gd__gd_core_items__HolySpear, "HolySpear", "res://gd_core_items/HolySpear.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__HolySpear, &Gd__gd_core_items__HolySpear::get_static_prop_fn, &Gd__gd_core_items__HolySpear::call_static_fn};

void Gd__gd_core_items__Pandamonium::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Pandamonium::meta() const { return &META_Gd__gd_core_items__Pandamonium; }
gd::GdVal Gd__gd_core_items__Pandamonium::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Pandamonium::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Pandamonium::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Pandamonium::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Pandamonium::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onFoodActivated_1956: return true;
        case SYM_GEN_getCraftingOffset_850: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Pandamonium::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onFoodActivated_1956: out = fn_onFoodActivated(args, argc); return true;
        case SYM_GEN_getCraftingOffset_850: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Pandamonium::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Pandamonium::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Pandamonium::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1022 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1023 = (_t1022.kind == gd::GdVal::Kind::Arr) ? _t1022.arr : nullptr;
        uint32_t _len__t1024 = _t1023 ? _t1023->len : 0u;
        for (uint32_t _t1024 = 0; _t1024 < _len__t1024; ++_t1024) {
            gd::GdVal lv_item = _t1023->data[_t1024];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[108]), gd::GdVal::from_str(&battle_string_literals[109])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::native_numeric_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changePoisonCritChancePercent_1283, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Pandamonium::fn_onFoodActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Pandamonium::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1025 = lv_forDirection;
        if (gd::native_scalar_eq(_t1025, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(1LL)).as_float());
        }
        else if (gd::native_scalar_eq(_t1025, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
        else if (gd::native_scalar_eq(_t1025, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::native_scalar_eq(_t1025, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Pandamonium::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Pandamonium(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Pandamonium>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,616u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Pandamonium = {CLS_Gd__gd_core_items__Pandamonium, "Pandamonium", "res://gd_core_items/Pandamonium.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Pandamonium, &Gd__gd_core_items__Pandamonium::get_static_prop_fn, &Gd__gd_core_items__Pandamonium::call_static_fn};

void Gd__gd_core_items__RubyChonk::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_heatThresholdReached = gd::GdVal::from_bool(false);
    this->f_hasStunned = gd::GdVal::from_bool(false);
    this->f_activationParticles = gd::GdVal::null();
    this->f_heatThreshold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__RubyChonk::meta() const { return &META_Gd__gd_core_items__RubyChonk; }
gd::GdVal Gd__gd_core_items__RubyChonk::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__RubyChonk::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__RubyChonk::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_heatThresholdReached_1973: out = this->f_heatThresholdReached; return true;
        case SYM_GEN_hasStunned_1974: out = this->f_hasStunned; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_heatThreshold_1975: out = this->f_heatThreshold; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__RubyChonk::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heatThresholdReached_1973: this->f_heatThresholdReached = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_hasStunned_1974: this->f_hasStunned = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_heatThreshold_1975: this->f_heatThreshold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__RubyChonk::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onHeatChanged_913: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN_getCraftingOffset_850: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__RubyChonk::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onHeatChanged_913: out = fn_onHeatChanged(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_getCraftingOffset_850: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__RubyChonk::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__RubyChonk::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[41]), gd::GdVal::from_str(&battle_string_literals[42])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RubyChonk::fn_onHeatChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_heatThresholdReached)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getHeat_1251, nullptr, 0), this->f_heatThreshold)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(false), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 3); })();
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getHeat_1251, nullptr, 0), this->f_heatThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false), gd::GdVal::from_bool(false), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RubyChonk::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        this->f_hasStunned = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
        gd::GdVal lv_res = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_220, nullptr, 0);
        if (gd::gd_truth(this->f_hasStunned)) {
            (void)([&]() { gd::GdVal _ca[] = {lv_res, gd::GdVal::from_bool(false), gd::GdVal::from_bool(false), gd::native_inline_get_prop(gd_ctx, Gd__gd_core_items__RubyChonk::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Tackle_2753)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 4); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {lv_res, gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 2); })();
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(30.0)), gd::GdVal::from_float(30.0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_bare_randf_range_1743, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(100.0)), gd::GdVal::from_float(100.0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_bare_randf_range_1743, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(5.0)), gd::GdVal::from_float(5.0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_bare_randf_range_1743, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RubyChonk::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 2); })();
        if (gd::gd_truth(this->f_heatThresholdReached)) {
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[30])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_330, _ca, 2); })();
                this->f_hasStunned = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RubyChonk::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RubyChonk::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__heatThresholdReached = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv__heatThresholdReached)) {
    }
    else {
    }
    this->f_heatThresholdReached = gd::gd_coerce_bool(lv__heatThresholdReached);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RubyChonk::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1026 = lv_forDirection;
        if (gd::native_scalar_eq(_t1026, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
        else if (gd::native_scalar_eq(_t1026, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
        else if (gd::native_scalar_eq(_t1026, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::native_scalar_eq(_t1026, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RubyChonk::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_heatThreshold = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__RubyChonk(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__RubyChonk>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,637u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__RubyChonk = {CLS_Gd__gd_core_items__RubyChonk, "RubyChonk", "res://gd_core_items/RubyChonk.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__RubyChonk, &Gd__gd_core_items__RubyChonk::get_static_prop_fn, &Gd__gd_core_items__RubyChonk::call_static_fn};

void Gd__gd_core_items__TheLovers::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Card::init_fields(gd_ctx);
    this->f_particle_draw_frame = gd::gd_neg(gd::GdVal::from_int(1LL));
    this->f_particle_start_phase = gd::GdVal::from_int(0LL);
    this->f_particle_hidden_at = gd::GdVal::from_int(0LL);
    this->f_healAmp = gd::GdVal::null();
    this->f_dam = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__TheLovers::meta() const { return &META_Gd__gd_core_items__TheLovers; }
gd::GdVal Gd__gd_core_items__TheLovers::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Card::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__TheLovers::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__TheLovers::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_particle_draw_frame_1465: out = this->f_particle_draw_frame; return true;
        case SYM_GEN_particle_start_phase_2634: out = this->f_particle_start_phase; return true;
        case SYM_GEN_particle_hidden_at_2635: out = this->f_particle_hidden_at; return true;
        case SYM_GEN_healAmp_1998: out = this->f_healAmp; return true;
        case SYM_GEN_dam_939: out = this->f_dam; return true;
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::get_prop(prop, out);
}
bool Gd__gd_core_items__TheLovers::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_particle_draw_frame_1465: this->f_particle_draw_frame = val; return true;
        case SYM_GEN_particle_start_phase_2634: this->f_particle_start_phase = val; return true;
        case SYM_GEN_particle_hidden_at_2635: this->f_particle_hidden_at = val; return true;
        case SYM_GEN_healAmp_1998: this->f_healAmp = val; return true;
        case SYM_GEN_dam_939: this->f_dam = val; return true;
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__TheLovers::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_890: return true;
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN_prepare_122: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Card::has_own_method(m);
}
bool Gd__gd_core_items__TheLovers::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_890: out = fn_cardSecondaryEffectActive(args, argc); return true;
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN_prepare_122: out = fn_prepare(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__TheLovers::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__TheLovers::fn_cardSecondaryEffectActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::native_scalar_eq(gd::gd_mod(gd_ctx, this->f_chainPosition, gd::GdVal::from_int(2LL)), gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__TheLovers::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cardSecondaryEffectActive_890, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_healAmp}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_addHealingEfficiency_1182, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {this->f_dam, gd::native_numeric_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[53])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealLife_329, _ca, 2); })();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cardSecondaryEffectActive_890, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
        if (gd::gd_truth(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_native_frame_rng_1450))) {
            gd::GdVal lv_next_idle = gd::gd_coerce_int(gd::native_numeric_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_frame_counter_1413), (gd::gd_truth(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN__critical_shake_after_idle_1460)) ? (gd::GdVal::from_int(1LL)) : (gd::GdVal::from_int(0LL)))));
            this->f_particle_start_phase = ([&]() { gd::GdVal _ca[] = {this->f_particle_draw_frame, this->f_particle_start_phase, gd::GdVal::from_bool(gd::gd_lt(lv_next_idle, this->f_particle_hidden_at))}; return gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_restartLoversParticleDraws_1493, _ca, 3); })();
            this->f_particle_draw_frame = gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_particle_draw_frame_1465);
            this->f_particle_hidden_at = gd::native_numeric_add(gd_ctx, lv_next_idle, gd::GdVal::from_int(76LL));
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__TheLovers::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Card::call_method(gd_ctx, SYM_GEN_prepare_122, nullptr, 0, _out); return _out; })();
    this->f_particle_draw_frame = gd::gd_neg(gd::GdVal::from_int(1LL));
    this->f_particle_hidden_at = gd::GdVal::from_int(0LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__TheLovers::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Card::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_healAmp = gd::native_numeric_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[110])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_dam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[56])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[94])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__TheLovers(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__TheLovers>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,658u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__TheLovers = {CLS_Gd__gd_core_items__TheLovers, "TheLovers", "res://gd_core_items/TheLovers.gd", &META_Gd__gd_core_items__Card, true, _alloc_Gd__gd_core_items__TheLovers, &Gd__gd_core_items__TheLovers::get_static_prop_fn, &Gd__gd_core_items__TheLovers::call_static_fn};
