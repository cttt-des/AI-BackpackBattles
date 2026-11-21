#include "../../native_inline_dispatch.hpp"
#include "../../native_scalar_equal.hpp"
#include "../../native_array_index.hpp"
#include "../../native_event_kernel.hpp"
#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core__RangerCollar.hpp"
#include "../hdrs/Gd__gd_core__BloodyDagger.hpp"
#include "../hdrs/Gd__gd_core__CoreCombat__INNER__CoreItemSort.hpp"
#include "../hdrs/Gd__gd_core__CoreCombat.hpp"
#include "../hdrs/Gd__gd_core__CoreRng__INNER__BalancedRng.hpp"
#include "../hdrs/Gd__gd_core__CoreRng.hpp"
#include "../hdrs/Gd__gd_core__DeckofCards.hpp"
#include "../hdrs/Gd__gd_core__GingerbreadMan.hpp"
#include "../hdrs/Gd__gd_core__Jynxtorquilla.hpp"
#include "../hdrs/Gd__gd_core__MoonShield.hpp"
#include "../hdrs/Gd__gd_core__ProtectivePurse.hpp"
#include "../hdrs/Gd__gd_core__SteelGoobert.hpp"
#include "../hdrs/Gd__gd_core__ThornBow.hpp"
#include "../hdrs/Gd__gd_core_items__RangerCollar.hpp"
#include "../hdrs/Gd__gd_core_items__BowandArrow.hpp"
#include "../hdrs/Gd__gd_core_items__DancingDragon.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__AmuletofFeasting.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Cube.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BurningBanner.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Chess__BlackKing.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Cog.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DeerTotem.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Eat_o_matic.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__FalseLife.hpp"
#include "../hdrs/Gd__gd_core_items__Shield.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__HeavyDrinking.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__JynxStaff.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__LuckyCat.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MissFortune.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PerpetuumMobile.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PrismaticSword.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__RainbowPotion.hpp"
#include "../hdrs/Gd__gd_core_items__Lightsaber.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SmellyBarrier.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SpikedCollar.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__StoneShoes.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__TimePendant.hpp"
#include "../hdrs/Gd__gd_core_items__Whetstone.hpp"
#include "../hdrs/Gd__gd_core_items__Gems__Emerald.hpp"
#include "../hdrs/Gd__gd_core_items__HolyArmor.hpp"
#include "../hdrs/Gd__gd_core_items__MrStruggles.hpp"
#include "../hdrs/Gd__gd_core_items__RangerBag.hpp"
#include "../hdrs/Gd__gd_core_items__TheFool.hpp"

namespace {
constexpr gd::GdStr battle_string_literals[] = {
    {"stamina", 7u, 3875003702u},
    {"Acorn Ace", 9u, 3796396897u},
    {"heal", 4u, 979982427u},
    {"BALROLL", 7u, 3540806267u},
    {"ch=", 3u, 1099301385u},
    {"ew=", 3u, 799268632u},
    {" w=", 3u, 2304806591u},
    {"lr=", 3u, 2307236146u},
    {"startActivation", 15u, 1963752975u},
    {"maxhealth_use", 13u, 2642987079u},
    {"speed", 5u, 2072037248u},
    {"max", 3u, 3617776409u},
    {"gave_block", 10u, 905150934u},
    {"onItemGaveBlock", 15u, 3788065731u},
    {"Bagtacular", 10u, 2131747329u},
    {"block", 5u, 3943480674u},
    {"character_heat_changed", 22u, 2413560104u},
    {"onHeatChanged", 13u, 775078454u},
    {"character_lucky_changed", 23u, 2259242176u},
    {"onLuckyChanged", 14u, 1760969932u},
    {"foodspeed", 9u, 2449332788u},
    {"\n\n", 2u, 2274317941u},
    {"Cube_HINT", 9u, 3874930544u},
    {"cdadvance", 9u, 1429998028u},
    {"penalty", 7u, 2921086870u},
    {"activated", 9u, 2866667388u},
    {"onItemActivated", 15u, 1109670618u},
    {"dur_blind", 9u, 3690439708u},
    {"regen", 5u, 16724762u},
    {"buffs", 5u, 2149256365u},
    {"piece_captured", 14u, 1502329272u},
    {"onAnyPieceCaptured", 18u, 2156068214u},
    {"dur_rage", 8u, 2784799188u},
    {"battle_rage_started", 19u, 3997014835u},
    {"onBattleRageStarted", 19u, 3330696088u},
    {"battle_rage_ended", 17u, 4230921894u},
    {"onBattleRageEnded", 17u, 1252110145u},
    {"speed2", 6u, 498752822u},
    {"speed3", 6u, 515530441u},
    {"maxhealth", 9u, 429334299u},
    {"character_overhealed", 20u, 177632284u},
    {"onOverheal", 10u, 2924617628u},
    {"heal_dark", 9u, 2196921632u},
    {"healthamp", 9u, 440853359u},
    {"pre_take_damage", 15u, 2330033632u},
    {"preTakeDamage", 13u, 311913432u},
    {"character_attacked", 18u, 2439462988u},
    {"onCharacterAttacked", 19u, 1493935206u},
    {"damblock", 8u, 2582642454u},
    {"blocked", 7u, 1516072627u},
    {"manat", 5u, 126091098u},
    {"dam", 3u, 4031722721u},
    {"luck", 4u, 4145017712u},
    {"sales", 5u, 2258376375u},
    {"gold1", 5u, 3353703430u},
    {"gold2", 5u, 3336925811u},
    {"onBuffChanged", 13u, 3423803215u},
    {"character_used_stamina", 22u, 4094391974u},
    {"onStaminaUsed", 13u, 3121214912u},
    {"used", 4u, 1786277552u},
    {"refund_buffs", 12u, 886263414u},
    {"refund_stamina", 14u, 1640677733u},
    {"lifesteal", 9u, 1515578962u},
    {"$n_magic", 8u, 536624491u},
    {"", 0u, 2166136261u},
    {"$n_vampiric", 11u, 1179443659u},
    {"$n_holy", 7u, 2980935886u},
    {"$n_dark", 7u, 3365736372u},
    {"n_magic", 7u, 1294501073u},
    {"n_vampiric", 10u, 665009097u},
    {"n_holy", 6u, 2117373556u},
    {"n_dark", 6u, 2718798678u},
    {"debuffs", 7u, 504032524u},
    {"Exclusive/RainbowPotion.gd:37", 29u, 250868686u},
    {"onBuffsChanged", 14u, 1288163266u},
    {"buffst", 6u, 2207594907u},
    {"potions", 7u, 2866898395u},
    {"mana", 4u, 3650585354u},
    {"blinding_light_ended", 20u, 2616732264u},
    {"onBlindingLightEnded", 20u, 1777857537u},
    {"character_blind_changed", 23u, 2628032727u},
    {"onOpponentBlindChanged", 22u, 4206373648u},
    {"character_regeneration_changed", 30u, 2797934681u},
    {"onRegenChanged", 14u, 661197895u},
    {"endBlindingLight", 16u, 2663387189u},
    {"BlindingLightTimer", 18u, 3459613801u},
    {"onBlindingLightTimeout", 22u, 1728096158u},
    {"regent", 6u, 4290639402u},
    {"blind", 5u, 274826164u},
    {"dam_blind", 9u, 3475979813u},
    {"Garlic", 6u, 137760495u},
    {"blockbonus", 10u, 1855968229u},
    {"blockt", 6u, 453880226u},
    {"poison", 6u, 3470992305u},
    {"spikes", 6u, 439106706u},
    {"character_damaged", 17u, 745527748u},
    {"onDamaged", 9u, 2303747743u},
    {"dur", 3u, 3509645056u},
    {"empower", 7u, 2037162760u},
    {"damreduction", 12u, 2823666870u},
    {"BuffTimer", 9u, 194754125u},
    {"onBuffTimeout", 13u, 3028159308u},
    {"attacked", 8u, 3381721668u},
    {"onAttack", 8u, 3086142220u},
    {"Mrs Struggles", 13u, 3720174819u},
    {"Miss Fortune", 12u, 2446127352u},
    {"onDebuffed", 10u, 562402695u},
    {"dur_speed", 9u, 1036633528u},
    {"MSROLL", 6u, 2840464882u},
    {"type=", 5u, 836834128u},
    {" amt=", 5u, 2285430122u},
    {" ew=", 4u, 3964045074u},
    {" lr=", 4u, 1846101108u},
    {"duration", 8u, 799079693u},
    {"SpeedbuffTimer", 14u, 437591678u},
    {"onSpeedbuffTimeout", 18u, 4061665073u},
    {"revealspeed", 11u, 3267256187u},
};
}

void Gd__gd_core__RangerCollar::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_affectedItems = gd::GdVal::null();
    this->f_acornAceDescriptor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__RangerCollar::meta() const { return &META_Gd__gd_core__RangerCollar; }
gd::GdVal Gd__gd_core__RangerCollar::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__RangerCollar::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__RangerCollar::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_affectedItems_899: out = this->f_affectedItems; return true;
        case SYM_GEN_acornAceDescriptor_900: out = this->f_acornAceDescriptor; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__RangerCollar::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedItems_899: this->f_affectedItems = val; return true;
        case SYM_GEN_acornAceDescriptor_900: this->f_acornAceDescriptor = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__RangerCollar::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepare_122: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__RangerCollar::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepare_122: out = fn_prepare(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__RangerCollar::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__RangerCollar::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_affectedItems = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0);
    gd::GdVal lv_numAces = ([&]() { gd::GdVal _ca[] = {this->f_acornAceDescriptor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countAllInInventoryOfType_804, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numAces, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_staminaReduction = gd::gd_mul(lv_numAces, gd::gd_neg(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[0])}; return gd::native_inline_call(gd_ctx, this->f_acornAceDescriptor, SYM_GEN_getP_188, _ca, 1); })()));
        {
            gd::GdVal _t838 = gd::gd_iter_seq(gd_ctx.arena, this->f_affectedItems);
            gd::GdArr* _t839 = (_t838.kind == gd::GdVal::Kind::Arr) ? _t838.arr : nullptr;
            uint32_t _len__t840 = _t839 ? _t839->len : 0u;
            for (uint32_t _t840 = 0; _t840 < _len__t840; ++_t840) {
                gd::GdVal lv_item = _t839->data[_t840];
                (void)([&]() { gd::GdVal _ca[] = {lv_staminaReduction}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeStaminaFactor_305, _ca, 1); })();
            }
        }
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_prepare_122, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RangerCollar::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_acornAceDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[1])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__RangerCollar(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__RangerCollar>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,124u); return object; }
const gd::GdClassMeta META_Gd__gd_core__RangerCollar = {CLS_Gd__gd_core__RangerCollar, "RangerCollar", "res://gd_core/RangerCollar.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__RangerCollar, &Gd__gd_core__RangerCollar::get_static_prop_fn, &Gd__gd_core__RangerCollar::call_static_fn};

void Gd__gd_core__BloodyDagger::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Dagger::init_fields(gd_ctx);
    this->f_vampirismStacks = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core__BloodyDagger::meta() const { return &META_Gd__gd_core__BloodyDagger; }
gd::GdVal Gd__gd_core__BloodyDagger::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Dagger::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__BloodyDagger::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__BloodyDagger::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_vampirismStacks_947: out = this->f_vampirismStacks; return true;
        default: break;
    }
    return Gd__gd_core__Dagger::get_prop(prop, out);
}
bool Gd__gd_core__BloodyDagger::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_vampirismStacks_947: this->f_vampirismStacks = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core__Dagger::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__BloodyDagger::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Dagger::has_own_method(m);
}
bool Gd__gd_core__BloodyDagger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Dagger::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__BloodyDagger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Dagger::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__BloodyDagger::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(24LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BloodyDagger::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_vampirismStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BloodyDagger::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_vampirismStacks, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
            this->f_vampirismStacks = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_vampirismStacks, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)));
        }
        gd::GdVal lv_numAffected = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numAffected, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_numAffected, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[2])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BloodyDagger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Dagger::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__BloodyDagger(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__BloodyDagger>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,10u); return object; }
const gd::GdClassMeta META_Gd__gd_core__BloodyDagger = {CLS_Gd__gd_core__BloodyDagger, "BloodyDagger", "res://gd_core/BloodyDagger.gd", &META_Gd__gd_core__Dagger, false, _alloc_Gd__gd_core__BloodyDagger, &Gd__gd_core__BloodyDagger::get_static_prop_fn, &Gd__gd_core__BloodyDagger::call_static_fn};

void Gd__gd_core__CoreCombat__INNER__CoreItemSort::init_fields(gd::BattleCtx& gd_ctx) {
}
const gd::GdClassMeta* Gd__gd_core__CoreCombat__INNER__CoreItemSort::meta() const { return &META_Gd__gd_core__CoreCombat__INNER__CoreItemSort; }
gd::GdVal Gd__gd_core__CoreCombat__INNER__CoreItemSort::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreCombat__INNER__CoreItemSort::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreCombat__INNER__CoreItemSort::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return false;
}
bool Gd__gd_core__CoreCombat__INNER__CoreItemSort::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return false;
}
bool Gd__gd_core__CoreCombat__INNER__CoreItemSort::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_sort_TriggerPriority_1345: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreCombat__INNER__CoreItemSort::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_sort_TriggerPriority_1345: out = fn_sort_TriggerPriority(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreCombat__INNER__CoreItemSort::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core__CoreCombat__INNER__CoreItemSort::fn_sort_TriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item1 = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item2 = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, lv_item1, gd::SYM_getTriggerPriority, nullptr, 0), gd::native_inline_call(gd_ctx, lv_item2, gd::SYM_getTriggerPriority, nullptr, 0)));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreCombat__INNER__CoreItemSort(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__CoreCombat__INNER__CoreItemSort>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,27u); return object; }
const gd::GdClassMeta META_Gd__gd_core__CoreCombat__INNER__CoreItemSort = {CLS_Gd__gd_core__CoreCombat__INNER__CoreItemSort, "CoreItemSort", "", nullptr, false, _alloc_Gd__gd_core__CoreCombat__INNER__CoreItemSort, &Gd__gd_core__CoreCombat__INNER__CoreItemSort::get_static_prop_fn, &Gd__gd_core__CoreCombat__INNER__CoreItemSort::call_static_fn};

void Gd__gd_core__CoreRng__INNER__BalancedRng::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_expectedWins = gd::GdVal::from_float(0.0);
    this->f_wins = gd::GdVal::from_int(0LL);
    this->f_balancedness = gd::GdVal::from_float(3.0);
    this->f_lastResult = gd::GdVal::from_bool(false);
    this->f_extraLuck = gd::GdVal::from_float(0.0);
    this->f_lastTarget = gd::GdVal::from_float(0.0);
    this->f_accChance = gd::GdVal::from_float(0.0);
    this->f__rng = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__CoreRng__INNER__BalancedRng::meta() const { return &META_Gd__gd_core__CoreRng__INNER__BalancedRng; }
gd::GdVal Gd__gd_core__CoreRng__INNER__BalancedRng::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_luckBalance_1758: return gd::GdVal::from_float(0.2);
        default: break;
    }
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreRng__INNER__BalancedRng::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreRng__INNER__BalancedRng::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_expectedWins_1751: out = this->f_expectedWins; return true;
        case SYM_GEN_wins_1752: out = this->f_wins; return true;
        case SYM_GEN_balancedness_1753: out = this->f_balancedness; return true;
        case SYM_GEN_lastResult_1754: out = this->f_lastResult; return true;
        case SYM_GEN_extraLuck_1755: out = this->f_extraLuck; return true;
        case SYM_GEN_lastTarget_1756: out = this->f_lastTarget; return true;
        case SYM_GEN_accChance_1757: out = this->f_accChance; return true;
        case SYM_GEN__rng_1548: out = this->f__rng; return true;
        case SYM_GEN_luckBalance_1758: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreRng__INNER__BalancedRng::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_expectedWins_1751: this->f_expectedWins = gd::gd_coerce_float(val); return true;
        case SYM_GEN_wins_1752: this->f_wins = val; return true;
        case SYM_GEN_balancedness_1753: this->f_balancedness = val; return true;
        case SYM_GEN_lastResult_1754: this->f_lastResult = val; return true;
        case SYM_GEN_extraLuck_1755: this->f_extraLuck = val; return true;
        case SYM_GEN_lastTarget_1756: this->f_lastTarget = val; return true;
        case SYM_GEN_accChance_1757: this->f_accChance = val; return true;
        case SYM_GEN__rng_1548: this->f__rng = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreRng__INNER__BalancedRng::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_setBias_1759: return true;
        case SYM_GEN_rollPercent_1760: return true;
        case SYM_GEN_roll_1734: return true;
        case SYM_GEN_roll2_1761: return true;
        case SYM_GEN_roll1_1762: return true;
        case SYM_GEN_reset_1025: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreRng__INNER__BalancedRng::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_setBias_1759: out = fn_setBias(args, argc); return true;
        case SYM_GEN_rollPercent_1760: out = fn_rollPercent(args, argc); return true;
        case SYM_GEN_roll_1734: out = fn_roll(args, argc); return true;
        case SYM_GEN_roll2_1761: out = fn_roll2(args, argc); return true;
        case SYM_GEN_roll1_1762: out = fn_roll1(args, argc); return true;
        case SYM_GEN_reset_1025: out = fn_reset(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreRng__INNER__BalancedRng::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core__CoreRng__INNER__BalancedRng::fn__init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__rng_ref = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_startBias = (_argc > 1) ? _args[1] : (gd::GdVal::from_float(0.0));
    lv_startBias = gd::gd_coerce_float(lv_startBias);
    this->f__rng = lv__rng_ref;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f__rng, gd::GdVal::null())))) {
        this->f_expectedWins = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.2), gd::gd_neg(gd::GdVal::from_float(0.2))}; return gd::native_inline_call(gd_ctx, this->f__rng, gd::SYM_randf_range, _ca, 2); })());
    }
    else {
        this->f_expectedWins = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    }
    this->f_expectedWins = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_expectedWins, lv_startBias));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng__INNER__BalancedRng::fn_setBias(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bias = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_bias = gd::gd_coerce_float(lv_bias);
    this->f_expectedWins = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_expectedWins, lv_bias));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng__INNER__BalancedRng::fn_rollPercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_target = gd::gd_coerce_float(lv_target);
    return ([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, lv_target, gd::GdVal::from_float(100.0))}; return this->fn_roll(_ca, 1); })();
    return gd::GdVal::null();
    }
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_target = gd::gd_coerce_float(lv_target);
    return ([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, lv_target, gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_roll_1734, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng__INNER__BalancedRng::fn_roll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_target = gd::gd_coerce_float(lv_target);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(lv_target, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_bool(false);
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_target, gd::GdVal::from_int(1LL))))) {
        return gd::GdVal::from_bool(true);
    }
    gd::GdVal lv_chance = lv_target;
    gd::GdVal lv_dif = gd::gd_sub(this->f_expectedWins, this->f_wins);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_dif, gd::GdVal::from_float(0.3))))) {
        lv_chance = gd::gd_mul(lv_chance, gd::gd_mul(this->f_balancedness, gd::gd_min(gd::GdVal::from_float(1.0), lv_dif)));
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_dif, gd::gd_neg(gd::GdVal::from_float(0.3)))))) {
        lv_chance = gd::gd_div(gd_ctx, lv_chance, gd::gd_mul(this->f_balancedness, gd::gd_min(gd::GdVal::from_float(1.0), gd::gd_neg(lv_dif))));
    }
    this->f_expectedWins = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_expectedWins, lv_target));
    if (gd::gd_truth((gd::gd_truth(this->f_lastResult) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_target, gd::GdVal::from_float(0.4))))) : gd::GdVal::from_bool(false)))) {
        lv_chance = gd::gd_mul(lv_chance, gd::GdVal::from_float(0.5));
    }
    else if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_lastResult))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_target, gd::GdVal::from_float(0.6))))) : gd::GdVal::from_bool(false)))) {
        lv_chance = gd::gd_mul(lv_chance, gd::GdVal::from_float(2.0));
    }
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_get_prop(gd_ctx, this->f__rng, SYM_GEN_oracle_trace_1729)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_get_prop(gd_ctx, this->f__rng, SYM_GEN__stacktrace_1731))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[3]), gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[4]), ([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[5]), ([&]() { gd::GdVal _ca[] = {this->f_expectedWins}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[6])), ([&]() { gd::GdVal _ca[] = {this->f_wins}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[7]), ([&]() { gd::GdVal _ca[] = {this->f_lastResult}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, this->f__rng, SYM_GEN_trace_diag_1741, _ca, 4); })();
    }
    gd::GdVal lv_result = ([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::native_inline_call(gd_ctx, this->f__rng, SYM_GEN_flip_1735, _ca, 1); })();
    this->f_lastResult = lv_result;
    if (gd::gd_truth(lv_result)) {
        this->f_wins = gd::gd_add(gd_ctx, this->f_wins, gd::GdVal::from_int(1LL));
        return gd::GdVal::from_bool(true);
    }
    else {
        return gd::GdVal::from_bool(false);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng__INNER__BalancedRng::fn_roll2(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_target = gd::gd_coerce_float(lv_target);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(lv_target, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_bool(false);
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_target, gd::GdVal::from_int(1LL))))) {
        return gd::GdVal::from_bool(true);
    }
    gd::GdVal lv_chance = gd::gd_add(gd_ctx, lv_target, gd::gd_mul(this->f_extraLuck, gd::GdVal::from_float(0.3)));
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::native_inline_call(gd_ctx, this->f__rng, SYM_GEN_flip_1735, _ca, 1); })())) {
        this->f_extraLuck = gd::gd_sub(this->f_extraLuck, gd::gd_sub(gd::GdVal::from_float(1.0), lv_target));
        return gd::GdVal::from_bool(true);
    }
    else {
        this->f_extraLuck = gd::gd_add(gd_ctx, this->f_extraLuck, lv_target);
        return gd::GdVal::from_bool(false);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng__INNER__BalancedRng::fn_roll1(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_target = gd::gd_coerce_float(lv_target);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(lv_target, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_bool(false);
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_target, gd::GdVal::from_int(1LL))))) {
        return gd::GdVal::from_bool(true);
    }
    this->f_accChance = gd::gd_add(gd_ctx, this->f_accChance, gd::gd_sub(lv_target, this->f_lastTarget));
    this->f_extraLuck = gd::gd_add(gd_ctx, this->f_extraLuck, gd::gd_sub(gd::gd_clamp(this->f_accChance, gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL)), lv_target));
    this->f_lastTarget = lv_target;
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_accChance}; return gd::native_inline_call(gd_ctx, this->f__rng, SYM_GEN_flip_1735, _ca, 1); })())) {
        this->f_accChance = gd::gd_sub(lv_target, this->f_extraLuck);
        return gd::GdVal::from_bool(true);
    }
    else {
        this->f_accChance = gd::gd_add(gd_ctx, this->f_accChance, Gd__gd_core__CoreRng__INNER__BalancedRng::get_static_const_or_enum(gd_ctx, SYM_GEN_luckBalance_1758));
        return gd::GdVal::from_bool(false);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng__INNER__BalancedRng::fn_reset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_expectedWins = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_wins = gd::GdVal::from_int(0LL);
    this->f_lastResult = gd::GdVal::from_bool(false);
    this->f_extraLuck = gd::GdVal::from_float(0.0);
    this->f_accChance = gd::GdVal::from_float(0.0);
    this->f_lastTarget = gd::GdVal::from_float(0.0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreRng__INNER__BalancedRng(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__CoreRng__INNER__BalancedRng>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,42u); return object; }
const gd::GdClassMeta META_Gd__gd_core__CoreRng__INNER__BalancedRng = {CLS_Gd__gd_core__CoreRng__INNER__BalancedRng, "BalancedRng", "", nullptr, false, _alloc_Gd__gd_core__CoreRng__INNER__BalancedRng, &Gd__gd_core__CoreRng__INNER__BalancedRng::get_static_prop_fn, &Gd__gd_core__CoreRng__INNER__BalancedRng::call_static_fn};

void Gd__gd_core__DeckofCards::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_cards = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_cardActivations = gd::GdVal::from_int(0LL);
    this->f_chainStarted = gd::GdVal::from_bool(false);
    this->f_connector = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__DeckofCards::meta() const { return &META_Gd__gd_core__DeckofCards; }
gd::GdVal Gd__gd_core__DeckofCards::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__DeckofCards::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__DeckofCards::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_cards_1832: out = this->f_cards; return true;
        case SYM_GEN_cardActivations_1833: out = this->f_cardActivations; return true;
        case SYM_GEN_chainStarted_1834: out = this->f_chainStarted; return true;
        case SYM_GEN_connector_885: out = this->f_connector; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__DeckofCards::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_cards_1832: this->f_cards = val; return true;
        case SYM_GEN_cardActivations_1833: this->f_cardActivations = val; return true;
        case SYM_GEN_chainStarted_1834: this->f_chainStarted = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_connector_885: this->f_connector = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__DeckofCards::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onAddToInventory_419: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_resetChain_1835: return true;
        case SYM_GEN_countDuplicates_1802: return true;
        case SYM_GEN_updateCards_1836: return true;
        case SYM_GEN_onItemAdded_437: return true;
        case SYM_GEN_onItemRemoved_438: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_notifyActivation_1837: return true;
        case SYM_GEN_getGatedDescriptor_956: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN_getRelatedItemHeight_700: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__DeckofCards::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onAddToInventory_419: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_resetChain_1835: out = fn_resetChain(args, argc); return true;
        case SYM_GEN_countDuplicates_1802: out = fn_countDuplicates(args, argc); return true;
        case SYM_GEN_updateCards_1836: out = fn_updateCards(args, argc); return true;
        case SYM_GEN_onItemAdded_437: out = fn_onItemAdded(args, argc); return true;
        case SYM_GEN_onItemRemoved_438: out = fn_onItemRemoved(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_notifyActivation_1837: out = fn_notifyActivation(args, argc); return true;
        case SYM_GEN_getGatedDescriptor_956: out = fn_getGatedDescriptor(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_700: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__DeckofCards::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__DeckofCards::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(12LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeckofCards::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateCards_1836, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeckofCards::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetChain_1835, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeckofCards::fn_resetChain(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t841 = gd::gd_iter_seq(gd_ctx.arena, this->f_cards);
        gd::GdArr* _t842 = (_t841.kind == gd::GdVal::Kind::Arr) ? _t841.arr : nullptr;
        uint32_t _len__t843 = _t842 ? _t842->len : 0u;
        for (uint32_t _t843 = 0; _t843 < _len__t843; ++_t843) {
            gd::GdVal lv_card = _t842->data[_t843];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::gd_neg(gd::GdVal::from_int(1LL)), gd::native_inline_call(gd_ctx, this->f_cards, gd::SYM_size, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_card, SYM_GEN_notifyChainPosition_894, _ca, 3); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, this->f_cards, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeckofCards::fn_countDuplicates(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_untilCardIndex = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_descriptors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t844 = gd::gd_iter_seq(gd_ctx.arena, lv_untilCardIndex);
        gd::GdArr* _t845 = (_t844.kind == gd::GdVal::Kind::Arr) ? _t844.arr : nullptr;
        uint32_t _len__t846 = _t845 ? _t845->len : 0u;
        for (uint32_t _t846 = 0; _t846 < _len__t846; ++_t846) {
            gd::GdVal lv_i = _t845->data[_t846];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_array_index(gd_ctx, this->f_cards, lv_i), SYM_GEN_descriptor_2)}; return gd::native_inline_call(gd_ctx, lv_descriptors, gd::SYM_push_back, _ca, 1); })();
        }
    }
    return ([&]() { gd::GdVal _ca[] = {lv_descriptors}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_countDuplicates_1802, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeckofCards::fn_updateCards(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetChain_1835, nullptr, 0);
    gd::GdVal lv_affected = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, lv_affected, gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL))}; return gd::native_inline_call(gd_ctx, this->f_cards, gd::SYM_push_back, _ca, 1); })();
        gd::GdVal lv_nextCard = gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, this->f_cards, gd::GdVal::from_int(0LL)), SYM_GEN_getNextCard_891, nullptr, 0);
        while (gd::gd_truth((gd::gd_truth(lv_nextCard) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_nextCard, this->f_cards))))) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_nextCard}; return gd::native_inline_call(gd_ctx, this->f_cards, gd::SYM_push_back, _ca, 1); })();
            lv_nextCard = gd::native_inline_call(gd_ctx, lv_nextCard, SYM_GEN_getNextCard_891, nullptr, 0);
        }
    }
    else {
    }
    gd::GdVal lv_chainLength = gd::native_inline_call(gd_ctx, this->f_cards, gd::SYM_size, nullptr, 0);
    {
        gd::GdVal _t847 = gd::gd_iter_seq(gd_ctx.arena, lv_chainLength);
        gd::GdArr* _t848 = (_t847.kind == gd::GdVal::Kind::Arr) ? _t847.arr : nullptr;
        uint32_t _len__t849 = _t848 ? _t848->len : 0u;
        for (uint32_t _t849 = 0; _t849 < _len__t849; ++_t849) {
            gd::GdVal lv_i = _t848->data[_t849];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_i, lv_chainLength}; return gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, this->f_cards, lv_i), SYM_GEN_notifyChainPosition_894, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeckofCards::fn_onItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_onItemAdded_437, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(lv_item, &META_Gd__gd_core_items__Card)))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateCards_1836, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeckofCards::fn_onItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_onItemRemoved_438, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(lv_item, &META_Gd__gd_core_items__Card)))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateCards_1836, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeckofCards::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_chainStarted = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeckofCards::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_chainStarted)))) {
        this->f_chainStarted = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        this->f_cardActivations = gd::GdVal::from_int(0LL);
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_cards, gd::SYM_empty, nullptr, 0))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, this->f_cards, gd::GdVal::from_int(0LL)), gd::GdVal::from_str(&battle_string_literals[8]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_defer_1482, _ca, 3); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeckofCards::fn_notifyActivation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_cardActivations = gd::gd_add(gd_ctx, this->f_cardActivations, gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeckofCards::fn_getGatedDescriptor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rarity = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeckofCards::fn_getRelatedItemColumns(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(4LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeckofCards::fn_getRelatedItemHeight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(120LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeckofCards::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__DeckofCards(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__DeckofCards>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,57u); return object; }
const gd::GdClassMeta META_Gd__gd_core__DeckofCards = {CLS_Gd__gd_core__DeckofCards, "DeckofCards", "res://gd_core/DeckofCards.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__DeckofCards, &Gd__gd_core__DeckofCards::get_static_prop_fn, &Gd__gd_core__DeckofCards::call_static_fn};

void Gd__gd_core__GingerbreadMan::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Food::init_fields(gd_ctx);
    this->f_luckNeeded = gd::GdVal::from_int(0);
    this->f_heatNeeded = gd::GdVal::from_int(0);
    this->f_manaNeeded = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core__GingerbreadMan::meta() const { return &META_Gd__gd_core__GingerbreadMan; }
gd::GdVal Gd__gd_core__GingerbreadMan::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__GingerbreadMan::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__GingerbreadMan::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_luckNeeded_1874: out = this->f_luckNeeded; return true;
        case SYM_GEN_heatNeeded_1880: out = this->f_heatNeeded; return true;
        case SYM_GEN_manaNeeded_1881: out = this->f_manaNeeded; return true;
        default: break;
    }
    return Gd__gd_core__Food::get_prop(prop, out);
}
bool Gd__gd_core__GingerbreadMan::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_luckNeeded_1874: this->f_luckNeeded = gd::gd_coerce_int(val); return true;
        case SYM_GEN_heatNeeded_1880: this->f_heatNeeded = gd::gd_coerce_int(val); return true;
        case SYM_GEN_manaNeeded_1881: this->f_manaNeeded = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__GingerbreadMan::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Food::has_own_method(m);
}
bool Gd__gd_core__GingerbreadMan::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__GingerbreadMan::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__GingerbreadMan::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__GingerbreadMan::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), this->f_luckNeeded)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getHeat_1251, nullptr, 0), this->f_heatNeeded)))) {
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_manaNeeded)))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_LoggingMode_1599), SYM_GEN_Delayed_2686)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_setLoggingMode_1588, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {this->f_luckNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useLucky_350, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {this->f_heatNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useHeat_354, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_267, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP6_268, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
                (void)gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_flushLoggingQueue_1591, nullptr, 0);
                (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[9])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, _ca, 1); })();
            }
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__GingerbreadMan::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_luckNeeded = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    this->f_heatNeeded = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0));
    this->f_manaNeeded = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__GingerbreadMan(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__GingerbreadMan>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,71u); return object; }
const gd::GdClassMeta META_Gd__gd_core__GingerbreadMan = {CLS_Gd__gd_core__GingerbreadMan, "GingerbreadMan", "res://gd_core/GingerbreadMan.gd", &META_Gd__gd_core__Food, false, _alloc_Gd__gd_core__GingerbreadMan, &Gd__gd_core__GingerbreadMan::get_static_prop_fn, &Gd__gd_core__GingerbreadMan::call_static_fn};

void Gd__gd_core__Jynxtorquilla::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_numActivations = gd::GdVal::from_int(0);
    this->f_speedBonus = gd::GdVal::null();
    this->f_maxActivations = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__Jynxtorquilla::meta() const { return &META_Gd__gd_core__Jynxtorquilla; }
gd::GdVal Gd__gd_core__Jynxtorquilla::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Jynxtorquilla::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Jynxtorquilla::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_numActivations_1904: out = this->f_numActivations; return true;
        case SYM_GEN_speedBonus_1877: out = this->f_speedBonus; return true;
        case SYM_GEN_maxActivations_1905: out = this->f_maxActivations; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Jynxtorquilla::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numActivations_1904: this->f_numActivations = gd::gd_coerce_int(val); return true;
        case SYM_GEN_speedBonus_1877: this->f_speedBonus = val; return true;
        case SYM_GEN_maxActivations_1905: this->f_maxActivations = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Jynxtorquilla::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Jynxtorquilla::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Jynxtorquilla::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Jynxtorquilla::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Jynxtorquilla::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_numActivations = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Jynxtorquilla::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_numActivations, this->f_maxActivations)))) {
        {
            gd::GdVal _t850 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
            gd::GdArr* _t851 = (_t850.kind == gd::GdVal::Kind::Arr) ? _t850.arr : nullptr;
            uint32_t _len__t852 = _t851 ? _t851->len : 0u;
            for (uint32_t _t852 = 0; _t852 < _len__t852; ++_t852) {
                gd::GdVal lv_item = _t851->data[_t852];
                (void)([&]() { gd::GdVal _ca[] = {this->f_speedBonus}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
            }
        }
        this->f_numActivations = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numActivations, gd::GdVal::from_int(1LL)));
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeLucky_349, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Jynxtorquilla::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speedBonus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[10])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_maxActivations = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[11])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Jynxtorquilla(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__Jynxtorquilla>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,88u); return object; }
const gd::GdClassMeta META_Gd__gd_core__Jynxtorquilla = {CLS_Gd__gd_core__Jynxtorquilla, "Jynxtorquilla", "res://gd_core/Jynxtorquilla.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__Jynxtorquilla, &Gd__gd_core__Jynxtorquilla::get_static_prop_fn, &Gd__gd_core__Jynxtorquilla::call_static_fn};

void Gd__gd_core__MoonShield::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Shield::init_fields(gd_ctx);
    this->f_blockAcc = gd::GdVal::from_int(0);
    this->f_blockForMana = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core__MoonShield::meta() const { return &META_Gd__gd_core__MoonShield; }
gd::GdVal Gd__gd_core__MoonShield::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Shield::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__MoonShield::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__MoonShield::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_blockAcc_1946: out = this->f_blockAcc; return true;
        case SYM_GEN_blockForMana_1947: out = this->f_blockForMana; return true;
        default: break;
    }
    return Gd__gd_core__Shield::get_prop(prop, out);
}
bool Gd__gd_core__MoonShield::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockAcc_1946: this->f_blockAcc = gd::gd_coerce_int(val); return true;
        case SYM_GEN_blockForMana_1947: this->f_blockForMana = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core__Shield::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__MoonShield::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_afterBlock_1942: return true;
        case SYM_GEN_onItemGaveBlock_1948: return true;
        case SYM_GEN_canBlockDamageRes_1943: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Shield::has_own_method(m);
}
bool Gd__gd_core__MoonShield::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_afterBlock_1942: out = fn_afterBlock(args, argc); return true;
        case SYM_GEN_onItemGaveBlock_1948: out = fn_onItemGaveBlock(args, argc); return true;
        case SYM_GEN_canBlockDamageRes_1943: out = fn_canBlockDamageRes(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Shield::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__MoonShield::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Shield::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__MoonShield::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBlock_291, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MoonShield::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t853 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t854 = (_t853.kind == gd::GdVal::Kind::Arr) ? _t853.arr : nullptr;
        uint32_t _len__t855 = _t854 ? _t854->len : 0u;
        for (uint32_t _t855 = 0; _t855 < _len__t855; ++_t855) {
            gd::GdVal lv_item = _t854->data[_t855];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(100LL), gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_giveBuffPower_303, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[12]), gd::GdVal::from_str(&battle_string_literals[13])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    this->f_blockAcc = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MoonShield::fn_afterBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), gd::native_inline_get_prop(gd_ctx, this->f_blockedDamageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drainStamina_117, _ca, 2); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MoonShield::fn_onItemGaveBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    this->f_blockAcc = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_blockAcc, lv_amount));
    gd::GdVal lv_mana = gd::gd_div(gd_ctx, this->f_blockAcc, this->f_blockForMana);
    this->f_blockAcc = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_blockAcc, this->f_blockForMana));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_mana, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_mana, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 2); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MoonShield::fn_canBlockDamageRes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_triggerOnAttacked_1530, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MoonShield::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Shield::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_blockForMana = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__MoonShield(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__MoonShield>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,102u); return object; }
const gd::GdClassMeta META_Gd__gd_core__MoonShield = {CLS_Gd__gd_core__MoonShield, "MoonShield", "res://gd_core/MoonShield.gd", &META_Gd__gd_core__Shield, false, _alloc_Gd__gd_core__MoonShield, &Gd__gd_core__MoonShield::get_static_prop_fn, &Gd__gd_core__MoonShield::call_static_fn};

void Gd__gd_core__ProtectivePurse::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Bag::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__ProtectivePurse::meta() const { return &META_Gd__gd_core__ProtectivePurse; }
gd::GdVal Gd__gd_core__ProtectivePurse::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__ProtectivePurse::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__ProtectivePurse::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Bag::get_prop(prop, out);
}
bool Gd__gd_core__ProtectivePurse::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__ProtectivePurse::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Bag::has_own_method(m);
}
bool Gd__gd_core__ProtectivePurse::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__ProtectivePurse::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__ProtectivePurse::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_totalBlock = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0);
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[14])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isTypeInInventory_805, _ca, 1); })())) {
        lv_totalBlock = gd::gd_add(gd_ctx, lv_totalBlock, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[15])}; return gd::native_inline_call(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[14])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })(), SYM_GEN_getP_188, _ca, 1); })());
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_totalBlock}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ProtectivePurse::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bag::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__ProtectivePurse(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__ProtectivePurse>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,119u); return object; }
const gd::GdClassMeta META_Gd__gd_core__ProtectivePurse = {CLS_Gd__gd_core__ProtectivePurse, "ProtectivePurse", "res://gd_core/ProtectivePurse.gd", &META_Gd__gd_core__Bag, false, _alloc_Gd__gd_core__ProtectivePurse, &Gd__gd_core__ProtectivePurse::get_static_prop_fn, &Gd__gd_core__ProtectivePurse::call_static_fn};

void Gd__gd_core__SteelGoobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Goobert::init_fields(gd_ctx);
    this->f_affectedWeapons = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
}
const gd::GdClassMeta* Gd__gd_core__SteelGoobert::meta() const { return &META_Gd__gd_core__SteelGoobert; }
gd::GdVal Gd__gd_core__SteelGoobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__SteelGoobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__SteelGoobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_affectedWeapons_1985: out = this->f_affectedWeapons; return true;
        default: break;
    }
    return Gd__gd_core__Goobert::get_prop(prop, out);
}
bool Gd__gd_core__SteelGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedWeapons_1985: this->f_affectedWeapons = val; return true;
        default: break;
    }
    return Gd__gd_core__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__SteelGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Goobert::has_own_method(m);
}
bool Gd__gd_core__SteelGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__SteelGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__SteelGoobert::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__SteelGoobert::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t856 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, _ca, 1); })());
        gd::GdArr* _t857 = (_t856.kind == gd::GdVal::Kind::Arr) ? _t856.arr : nullptr;
        uint32_t _len__t858 = _t857 ? _t857->len : 0u;
        for (uint32_t _t858 = 0; _t858 < _len__t858; ++_t858) {
            gd::GdVal lv_item = _t857->data[_t858];
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, this->f_affectedWeapons, gd::SYM_push_back, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__SteelGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t859 = gd::gd_iter_seq(gd_ctx.arena, this->f_affectedWeapons);
        gd::GdArr* _t860 = (_t859.kind == gd::GdVal::Kind::Arr) ? _t859.arr : nullptr;
        uint32_t _len__t861 = _t860 ? _t860->len : 0u;
        for (uint32_t _t861 = 0; _t861 < _len__t861; ++_t861) {
            gd::GdVal lv_item = _t860->data[_t861];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__SteelGoobert::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_affectedWeapons, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__SteelGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__SteelGoobert(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__SteelGoobert>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,137u); return object; }
const gd::GdClassMeta META_Gd__gd_core__SteelGoobert = {CLS_Gd__gd_core__SteelGoobert, "SteelGoobert", "res://gd_core/SteelGoobert.gd", &META_Gd__gd_core__Goobert, false, _alloc_Gd__gd_core__SteelGoobert, &Gd__gd_core__SteelGoobert::get_static_prop_fn, &Gd__gd_core__SteelGoobert::call_static_fn};

void Gd__gd_core__ThornBow::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Bow::init_fields(gd_ctx);
    this->f_bonusCounter = gd::GdVal::from_int(0LL);
    this->f_tempBonusDam = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core__ThornBow::meta() const { return &META_Gd__gd_core__ThornBow; }
gd::GdVal Gd__gd_core__ThornBow::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Bow::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__ThornBow::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__ThornBow::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_bonusCounter_2000: out = this->f_bonusCounter; return true;
        case SYM_GEN_tempBonusDam_2001: out = this->f_tempBonusDam; return true;
        default: break;
    }
    return Gd__gd_core__Bow::get_prop(prop, out);
}
bool Gd__gd_core__ThornBow::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusCounter_2000: this->f_bonusCounter = val; return true;
        case SYM_GEN_tempBonusDam_2001: this->f_tempBonusDam = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core__Bow::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__ThornBow::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_hasAttackEffect_295: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onWeaponAttacked_950: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Bow::has_own_method(m);
}
bool Gd__gd_core__ThornBow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_hasAttackEffect_295: out = fn_hasAttackEffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_950: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Bow::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__ThornBow::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Bow::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__ThornBow::fn_hasAttackEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ThornBow::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_bonusCounter = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {this->f_bonusCounter}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ThornBow::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ThornBow::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_res = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_220, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_bonusCounter, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_tempBonusDam, this->f_bonusCounter), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_reduceBonusDamage_310, _ca, 2); })();
            this->f_bonusCounter = gd::GdVal::from_int(0LL);
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusCounter, gd::GdVal::from_bool(false), gd::native_inline_get_prop(gd_ctx, lv_res, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ThornBow::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        gd::GdVal lv_attackEffectCount = gd::gd_add(gd_ctx, gd::GdVal::from_int(1LL), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollDoubleAttackEffect_187, nullptr, 0));
        {
            gd::GdVal _t862 = gd::gd_iter_seq(gd_ctx.arena, lv_attackEffectCount);
            gd::GdArr* _t863 = (_t862.kind == gd::GdVal::Kind::Arr) ? _t862.arr : nullptr;
            uint32_t _len__t864 = _t863 ? _t863->len : 0u;
            for (uint32_t _t864 = 0; _t864 < _len__t864; ++_t864) {
                gd::GdVal lv_i = _t863->data[_t864];
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getSpikes_1223, nullptr, 0), gd::GdVal::from_int(0LL))))) {
                    this->f_bonusCounter = gd::gd_add(gd_ctx, this->f_bonusCounter, gd::GdVal::from_int(1LL));
                    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useSpikes_337, _ca, 2); })();
                    (void)([&]() { gd::GdVal _ca[] = {this->f_tempBonusDam}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
                }
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {this->f_bonusCounter, gd::GdVal::from_bool(false), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ThornBow::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ThornBow::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__bonusCounter = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv__bonusCounter, gd::GdVal::from_int(0LL))))) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ThornBow::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bow::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_tempBonusDam = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__ThornBow(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__ThornBow>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,148u); return object; }
const gd::GdClassMeta META_Gd__gd_core__ThornBow = {CLS_Gd__gd_core__ThornBow, "ThornBow", "res://gd_core/ThornBow.gd", &META_Gd__gd_core__Bow, false, _alloc_Gd__gd_core__ThornBow, &Gd__gd_core__ThornBow::get_static_prop_fn, &Gd__gd_core__ThornBow::call_static_fn};

void Gd__gd_core_items__RangerCollar::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_affectedItems = gd::GdVal::null();
    this->f_acornAceDescriptor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__RangerCollar::meta() const { return &META_Gd__gd_core_items__RangerCollar; }
gd::GdVal Gd__gd_core_items__RangerCollar::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__RangerCollar::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__RangerCollar::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_affectedItems_899: out = this->f_affectedItems; return true;
        case SYM_GEN_acornAceDescriptor_900: out = this->f_acornAceDescriptor; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__RangerCollar::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedItems_899: this->f_affectedItems = val; return true;
        case SYM_GEN_acornAceDescriptor_900: this->f_acornAceDescriptor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__RangerCollar::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepare_122: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__RangerCollar::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepare_122: out = fn_prepare(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__RangerCollar::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__RangerCollar::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numAces = ([&]() { gd::GdVal _ca[] = {this->f_acornAceDescriptor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countAllInInventoryOfType_804, _ca, 1); })();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numAces, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(8LL)}; return gd::native_inline_call(gd_ctx, this->f_affectedTileCells, gd::SYM_has, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        { gd::GdVal _t865 = this->f_affectedTileCells; gd::GdVal _t866 = gd::GdVal::from_int(0LL); gd::native_array_set_index(gd_ctx, _t865, _t866, gd::native_array_index(gd_ctx, this->f_affectedTileCells, gd::GdVal::from_int(8LL))); }
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cacheAffectedCells_416, nullptr, 0);
    }
    this->f_affectedItems = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numAces, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_staminaReduction = gd::gd_mul(lv_numAces, gd::gd_neg(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[0])}; return gd::native_inline_call(gd_ctx, this->f_acornAceDescriptor, SYM_GEN_getP_188, _ca, 1); })()));
        {
            gd::GdVal _t867 = gd::gd_iter_seq(gd_ctx.arena, this->f_affectedItems);
            gd::GdArr* _t868 = (_t867.kind == gd::GdVal::Kind::Arr) ? _t867.arr : nullptr;
            uint32_t _len__t869 = _t868 ? _t868->len : 0u;
            for (uint32_t _t869 = 0; _t869 < _len__t869; ++_t869) {
                gd::GdVal lv_item = _t868->data[_t869];
                (void)([&]() { gd::GdVal _ca[] = {lv_staminaReduction}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeStaminaFactor_305, _ca, 1); })();
            }
        }
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_prepare_122, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RangerCollar::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_acornAceDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[1])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__RangerCollar(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__RangerCollar>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,628u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__RangerCollar = {CLS_Gd__gd_core_items__RangerCollar, "RangerCollar", "res://gd_core_items/RangerCollar.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__RangerCollar, &Gd__gd_core_items__RangerCollar::get_static_prop_fn, &Gd__gd_core_items__RangerCollar::call_static_fn};

void Gd__gd_core_items__BowandArrow::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bow::init_fields(gd_ctx);
    this->f_bonusDmg = gd::GdVal::from_int(0);
    this->f_bonusDmgPerHit = gd::GdVal::from_int(0);
    this->f_maxDmg = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__BowandArrow::meta() const { return &META_Gd__gd_core_items__BowandArrow; }
gd::GdVal Gd__gd_core_items__BowandArrow::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Bow::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__BowandArrow::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__BowandArrow::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_bonusDmg_951: out = this->f_bonusDmg; return true;
        case SYM_GEN_bonusDmgPerHit_952: out = this->f_bonusDmgPerHit; return true;
        case SYM_GEN_maxDmg_953: out = this->f_maxDmg; return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::get_prop(prop, out);
}
bool Gd__gd_core_items__BowandArrow::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusDmg_951: this->f_bonusDmg = gd::gd_coerce_int(val); return true;
        case SYM_GEN_bonusDmgPerHit_952: this->f_bonusDmgPerHit = gd::gd_coerce_int(val); return true;
        case SYM_GEN_maxDmg_953: this->f_maxDmg = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__BowandArrow::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_hasAttackEffect_295: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onWeaponAttacked_950: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::has_own_method(m);
}
bool Gd__gd_core_items__BowandArrow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_hasAttackEffect_295: out = fn_hasAttackEffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_950: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__BowandArrow::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bow::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__BowandArrow::fn_hasAttackEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BowandArrow::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_bonusDmg = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BowandArrow::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        gd::GdVal lv_dmgAdded = gd::GdVal::from_bool(false);
        gd::GdVal lv_attackEffectCount = gd::gd_add(gd_ctx, gd::GdVal::from_int(1LL), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollDoubleAttackEffect_187, nullptr, 0));
        {
            gd::GdVal _t870 = gd::gd_iter_seq(gd_ctx.arena, lv_attackEffectCount);
            gd::GdArr* _t871 = (_t870.kind == gd::GdVal::Kind::Arr) ? _t870.arr : nullptr;
            uint32_t _len__t872 = _t871 ? _t871->len : 0u;
            for (uint32_t _t872 = 0; _t872 < _len__t872; ++_t872) {
                gd::GdVal lv_i = _t871->data[_t872];
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_bonusDmg, this->f_maxDmg)))) {
                    this->f_bonusDmg = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_bonusDmg, this->f_bonusDmgPerHit));
                    (void)([&]() { gd::GdVal _ca[] = {this->f_bonusDmgPerHit}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
                    lv_dmgAdded = gd::GdVal::from_bool(true);
                }
            }
        }
        if (gd::gd_truth(lv_dmgAdded)) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusDmg, gd::GdVal::from_bool(false), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BowandArrow::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BowandArrow::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__bonusDmg = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv__bonusDmg, gd::GdVal::from_int(0LL))))) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BowandArrow::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bow::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_bonusDmgPerHit = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    this->f_maxDmg = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__BowandArrow(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__BowandArrow>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,176u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__BowandArrow = {CLS_Gd__gd_core_items__BowandArrow, "BowandArrow", "res://gd_core_items/BowandArrow.gd", &META_Gd__gd_core_items__Bow, true, _alloc_Gd__gd_core_items__BowandArrow, &Gd__gd_core_items__BowandArrow::get_static_prop_fn, &Gd__gd_core_items__BowandArrow::call_static_fn};

void Gd__gd_core_items__DancingDragon::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__DancingDragon::meta() const { return &META_Gd__gd_core_items__DancingDragon; }
gd::GdVal Gd__gd_core_items__DancingDragon::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__DancingDragon::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__DancingDragon::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__DancingDragon::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__DancingDragon::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onHeatChanged_913: return true;
        case SYM_GEN_onLuckyChanged_901: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__DancingDragon::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onHeatChanged_913: out = fn_onHeatChanged(args, argc); return true;
        case SYM_GEN_onLuckyChanged_901: out = fn_onLuckyChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__DancingDragon::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__DancingDragon::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(23LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DancingDragon::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[16]), gd::GdVal::from_str(&battle_string_literals[17])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[18]), gd::GdVal::from_str(&battle_string_literals[19])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DancingDragon::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numAffected = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numAffected, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), lv_numAffected)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), lv_numAffected)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DancingDragon::fn_onHeatChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), lv_amount)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_162, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DancingDragon::fn_onLuckyChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0), lv_amount)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDebuffResistChances_1220, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DancingDragon::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__DancingDragon(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__DancingDragon>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,194u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__DancingDragon = {CLS_Gd__gd_core_items__DancingDragon, "DancingDragon", "res://gd_core_items/DancingDragon.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__DancingDragon, &Gd__gd_core_items__DancingDragon::get_static_prop_fn, &Gd__gd_core_items__DancingDragon::call_static_fn};

void Gd__gd_core_items__Exclusive__AmuletofFeasting::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_foodSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__AmuletofFeasting::meta() const { return &META_Gd__gd_core_items__Exclusive__AmuletofFeasting; }
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofFeasting::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_amuletColor_2020: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.929412), gd::GdVal::from_float(0.498039), gd::GdVal::from_float(0.180392)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__AmuletofFeasting::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__AmuletofFeasting::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_foodSpeed_2028: out = this->f_foodSpeed; return true;
        case SYM_GEN_amuletColor_2020: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofFeasting::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_foodSpeed_2028: this->f_foodSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__AmuletofFeasting::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_getReplaceDescriptor_2029: return true;
        case SYM_GEN_getRelatedItems_459: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AmuletofFeasting::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_getReplaceDescriptor_2029: out = fn_getReplaceDescriptor(args, argc); return true;
        case SYM_GEN_getRelatedItems_459: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofFeasting::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofFeasting::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofFeasting::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t873 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t874 = (_t873.kind == gd::GdVal::Kind::Arr) ? _t873.arr : nullptr;
        uint32_t _len__t875 = _t874 ? _t874->len : 0u;
        for (uint32_t _t875 = 0; _t875 < _len__t875; ++_t875) {
            gd::GdVal lv_item = _t874->data[_t875];
            (void)([&]() { gd::GdVal _ca[] = {this->f_foodSpeed}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofFeasting::fn_getReplaceDescriptor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rarity = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofFeasting::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofFeasting::fn_getRelatedItemColumns(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(4LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofFeasting::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_foodSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[20])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__AmuletofFeasting(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__AmuletofFeasting>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,211u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletofFeasting = {CLS_Gd__gd_core_items__Exclusive__AmuletofFeasting, "AmuletofFeasting", "res://gd_core_items/Exclusive/AmuletofFeasting.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__AmuletofFeasting, &Gd__gd_core_items__Exclusive__AmuletofFeasting::get_static_prop_fn, &Gd__gd_core_items__Exclusive__AmuletofFeasting::call_static_fn};

void Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__WisdomPuppy::init_fields(gd_ctx);
    this->f_bonusBlock = gd::GdVal::from_int(0LL);
    this->f_cold = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy::meta() const { return &META_Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy; }
gd::GdVal Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__WisdomPuppy::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_bonusBlock_2044: out = this->f_bonusBlock; return true;
        case SYM_GEN_cold_2045: out = this->f_cold; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__WisdomPuppy::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusBlock_2044: this->f_bonusBlock = val; return true;
        case SYM_GEN_cold_2045: this->f_cold = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__WisdomPuppy::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__WisdomPuppy::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__WisdomPuppy::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__WisdomPuppy::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__WisdomPuppy::call_method(gd_ctx, SYM_GEN_onPrepare_123, nullptr, 0, _out); return _out; })();
    this->f_bonusBlock = gd::GdVal::from_int(0LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), this->f_bonusBlock)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_cold}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseCold_352, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    this->f_bonusBlock = gd::gd_add(gd_ctx, this->f_bonusBlock, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__WisdomPuppy::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_cold = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,223u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy = {CLS_Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy, "ArmoredWisdomPuppy", "res://gd_core_items/Exclusive/ArmoredWisdomPuppy.gd", &META_Gd__gd_core_items__Exclusive__WisdomPuppy, true, _alloc_Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy, &Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy::call_static_fn};

void Gd__gd_core_items__Exclusive__Cube::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_affectedItem = gd::GdVal::null();
    this->f_cdAdvance = gd::GdVal::null();
    this->f_penaltyFactor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Cube::meta() const { return &META_Gd__gd_core_items__Exclusive__Cube; }
gd::GdVal Gd__gd_core_items__Exclusive__Cube::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Cube::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Cube::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_affectedItem_2079: out = this->f_affectedItem; return true;
        case SYM_GEN_cdAdvance_2080: out = this->f_cdAdvance; return true;
        case SYM_GEN_penaltyFactor_2081: out = this->f_penaltyFactor; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Cube::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedItem_2079: this->f_affectedItem = val; return true;
        case SYM_GEN_cdAdvance_2080: this->f_cdAdvance = val; return true;
        case SYM_GEN_penaltyFactor_2081: this->f_penaltyFactor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Cube::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_advanceAffectedItem_2082: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Cube::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_advanceAffectedItem_2082: out = fn_advanceAffectedItem(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Cube::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Cube::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_getDescription_642, nullptr, 0);
    lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[21]), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[22])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_tra_2715, _ca, 1); })()));
    return ([&]() { gd::GdVal _ca[] = {lv_descr, lv_wrapInColor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameters_643, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cube::fn_advanceAffectedItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(this->f_affectedItem, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_cube_advanced_1426)))))) {
        { gd::GdVal _t876 = gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_cube_advanced_1426); gd::GdVal _t877 = this->f_affectedItem; gd::native_array_set_index(gd_ctx, _t876, _t877, gd::GdVal::from_obj(this)); }
        (void)([&]() { gd::GdVal _ca[] = {this->f_cdAdvance}; return gd::native_inline_call(gd_ctx, this->f_affectedItem, SYM_GEN_advanceCooldownSeconds_147, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_cdAdvance, this->f_penaltyFactor)}; return gd::native_inline_call(gd_ctx, this->f_affectedItem, SYM_GEN_advanceCooldownSeconds_147, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cube::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_cdAdvance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[23])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_penaltyFactor = gd::gd_sub(gd::GdVal::from_float(1.0), gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[24])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0)));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Cube(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Cube>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,292u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Cube = {CLS_Gd__gd_core_items__Exclusive__Cube, "Cube", "res://gd_core_items/Exclusive/Cube.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Cube, &Gd__gd_core_items__Exclusive__Cube::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Cube::call_static_fn};

void Gd__gd_core_items__Exclusive__BurningBanner::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_regeneration = gd::GdVal::null();
    this->f_buffsToRemove = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__BurningBanner::meta() const { return &META_Gd__gd_core_items__Exclusive__BurningBanner; }
gd::GdVal Gd__gd_core_items__Exclusive__BurningBanner::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__BurningBanner::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__BurningBanner::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_regeneration_2103: out = this->f_regeneration; return true;
        case SYM_GEN_buffsToRemove_2104: out = this->f_buffsToRemove; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BurningBanner::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_regeneration_2103: this->f_regeneration = val; return true;
        case SYM_GEN_buffsToRemove_2104: this->f_buffsToRemove = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BurningBanner::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onItemActivated_938: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BurningBanner::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemActivated_938: out = fn_onItemActivated(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BurningBanner::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningBanner::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canActivate_91, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningBanner::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t878 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t879 = (_t878.kind == gd::GdVal::Kind::Arr) ? _t878.arr : nullptr;
        uint32_t _len__t880 = _t879 ? _t879->len : 0u;
        for (uint32_t _t880 = 0; _t880 < _len__t880; ++_t880) {
            gd::GdVal lv_item = _t879->data[_t880];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[25]), gd::GdVal::from_str(&battle_string_literals[26])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeDebuffProtectionChance_1287, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeBuffProtectionChance_1286, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningBanner::fn_onItemActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_int(109LL), gd::GdVal::from_int(1LL), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[27])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacksTemporary_202, _ca, 4); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningBanner::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsToRemove}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeRandomBuffs_372, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_regeneration}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningBanner::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_regeneration = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[28])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_buffsToRemove = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[29])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BurningBanner(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__BurningBanner>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,252u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BurningBanner = {CLS_Gd__gd_core_items__Exclusive__BurningBanner, "BurningBanner", "res://gd_core_items/Exclusive/BurningBanner.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__BurningBanner, &Gd__gd_core_items__Exclusive__BurningBanner::get_static_prop_fn, &Gd__gd_core_items__Exclusive__BurningBanner::call_static_fn};

void Gd__gd_core_items__Exclusive__Chess__BlackKing::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Chess__ChessPiece::init_fields(gd_ctx);
    this->f_weaponSpeed = gd::GdVal::null();
    this->f_buffs = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Chess__BlackKing::meta() const { return &META_Gd__gd_core_items__Exclusive__Chess__BlackKing; }
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackKing::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackKing::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Chess__BlackKing::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_weaponSpeed_2154: out = this->f_weaponSpeed; return true;
        case SYM_GEN_buffs_1048: out = this->f_buffs; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackKing::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_weaponSpeed_2154: this->f_weaponSpeed = val; return true;
        case SYM_GEN_buffs_1048: this->f_buffs = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackKing::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCapturingEffect_2146: return true;
        case SYM_GEN_onAnyPieceCaptured_2155: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackKing::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCapturingEffect_2146: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_onAnyPieceCaptured_2155: out = fn_onAnyPieceCaptured(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackKing::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackKing::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_board, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_board, gd::GdVal::from_str(&battle_string_literals[30]), gd::GdVal::from_str(&battle_string_literals[31])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackKing::fn_doCapturingEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__eliminatedPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t881 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t882 = (_t881.kind == gd::GdVal::Kind::Arr) ? _t881.arr : nullptr;
        uint32_t _len__t883 = _t882 ? _t882->len : 0u;
        for (uint32_t _t883 = 0; _t883 < _len__t883; ++_t883) {
            gd::GdVal lv_item = _t882->data[_t883];
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isWeapon_82, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_weaponSpeed}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackKing::fn_onAnyPieceCaptured(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__eliminatedPiece = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, lv_capturingPiece, SYM_GEN_pieceColor_2135), gd::native_inline_get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Chess__BlackKing::get_static_const_or_enum(gd_ctx, SYM_GEN_PieceColor_2150), SYM_GEN_Black_2820))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, lv_capturingPiece, SYM_GEN_numCaptures_2138), gd::GdVal::from_int(1LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_buffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeRandomBuffs_372, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeRandomBuffs_372, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackKing::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_weaponSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[10])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_buffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[29])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Chess__BlackKing(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Chess__BlackKing>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,269u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__BlackKing = {CLS_Gd__gd_core_items__Exclusive__Chess__BlackKing, "BlackKing", "res://gd_core_items/Exclusive/Chess/BlackKing.gd", &META_Gd__gd_core_items__Exclusive__Chess__ChessPiece, true, _alloc_Gd__gd_core_items__Exclusive__Chess__BlackKing, &Gd__gd_core_items__Exclusive__Chess__BlackKing::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Chess__BlackKing::call_static_fn};

void Gd__gd_core_items__Exclusive__Cog::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Cog::meta() const { return &META_Gd__gd_core_items__Exclusive__Cog; }
gd::GdVal Gd__gd_core_items__Exclusive__Cog::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Cog::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Cog::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Cog::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Cog::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onSold_456: return true;
        case SYM_GEN_getSellPrice_394: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Cog::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onSold_456: out = fn_onSold(args, argc); return true;
        case SYM_GEN_getSellPrice_394: out = fn_getSellPrice(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Cog::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Cog::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isCrafted_800, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cog::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numAffected = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numAffected, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), lv_numAffected)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 1); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cog::fn_onSold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cog::fn_getSellPrice(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(0LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cog::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Cog(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Cog>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,284u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Cog = {CLS_Gd__gd_core_items__Exclusive__Cog, "Cog", "res://gd_core_items/Exclusive/Cog.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Cog, &Gd__gd_core_items__Exclusive__Cog::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Cog::call_static_fn};

void Gd__gd_core_items__Exclusive__DeerTotem::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_normalTex = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__DeerTotem::meta() const { return &META_Gd__gd_core_items__Exclusive__DeerTotem; }
gd::GdVal Gd__gd_core_items__Exclusive__DeerTotem::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__DeerTotem::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__DeerTotem::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_normalTex_2200: out = this->f_normalTex; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DeerTotem::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_normalTex_2200: this->f_normalTex = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DeerTotem::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_preCombatStart_124: return true;
        case SYM_GEN_onBattleRageStarted_2066: return true;
        case SYM_GEN_onBattleRageEnded_2067: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DeerTotem::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_preCombatStart_124: out = fn_preCombatStart(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_2066: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN_onBattleRageEnded_2067: out = fn_onBattleRageEnded(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DeerTotem::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DeerTotem::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(26LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeerTotem::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
    gd::GdVal lv_numNatureItems = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[32])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), lv_numNatureItems)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_addBattleRageDuration_1290, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[33]), gd::GdVal::from_str(&battle_string_literals[34])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[35]), gd::GdVal::from_str(&battle_string_literals[36])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeerTotem::fn_preCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_preCombatStart_124, nullptr, 0, _out); return _out; })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_99, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeerTotem::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activateCooldown_98, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeerTotem::fn_onBattleRageEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_99, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeerTotem::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeerTotem::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeerTotem::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv_active)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeerTotem::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(10000LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeerTotem::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DeerTotem(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__DeerTotem>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,302u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DeerTotem = {CLS_Gd__gd_core_items__Exclusive__DeerTotem, "DeerTotem", "res://gd_core_items/Exclusive/DeerTotem.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__DeerTotem, &Gd__gd_core_items__Exclusive__DeerTotem::get_static_prop_fn, &Gd__gd_core_items__Exclusive__DeerTotem::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Exclusive__Eat_o_matic_ArmState[] = {{"Off", 0LL}, {"Slow", 1LL}, {"Fast", 2LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Exclusive__Eat_o_matic_ArmState = {"ArmState", _ekv_Gd__gd_core_items__Exclusive__Eat_o_matic_ArmState, 3u};
void Gd__gd_core_items__Exclusive__Eat_o_matic::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_affectedFood = gd::GdVal::null();
    this->f_otherFood = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_armTween = gd::GdVal::null();
    this->f_armState = gd::GdVal::from_int(0);
    this->f_foodSpeed = gd::GdVal::null();
    this->f_chargedSpeed = gd::GdVal::null();
    this->f_otherSpeed = gd::GdVal::null();
    this->f_arm = gd::GdVal::null();
    this->f_armAnimation = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Eat_o_matic::meta() const { return &META_Gd__gd_core_items__Exclusive__Eat_o_matic; }
gd::GdVal Gd__gd_core_items__Exclusive__Eat_o_matic::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_ArmState_2236: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__Eat_o_matic_ArmState);
        case SYM_GEN_SLOW_SPEED_2228: return gd::GdVal::from_float(0.2);
        case SYM_GEN_FAST_SPEED_2229: return gd::GdVal::from_float(1.0);
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Eat_o_matic::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Eat_o_matic::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_affectedFood_2184: out = this->f_affectedFood; return true;
        case SYM_GEN_otherFood_2226: out = this->f_otherFood; return true;
        case SYM_GEN_armTween_2227: out = this->f_armTween; return true;
        case SYM_GEN_armState_2230: out = this->f_armState; return true;
        case SYM_GEN_foodSpeed_2028: out = this->f_foodSpeed; return true;
        case SYM_GEN_chargedSpeed_2231: out = this->f_chargedSpeed; return true;
        case SYM_GEN_otherSpeed_2232: out = this->f_otherSpeed; return true;
        case SYM_GEN_arm_2233: out = this->f_arm; return true;
        case SYM_GEN_armAnimation_2234: out = this->f_armAnimation; return true;
        case SYM_GEN_ArmState_2236: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__Eat_o_matic_ArmState); return true;
        case SYM_GEN_SLOW_SPEED_2228: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_FAST_SPEED_2229: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Eat_o_matic::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedFood_2184: this->f_affectedFood = val; return true;
        case SYM_GEN_otherFood_2226: this->f_otherFood = val; return true;
        case SYM_GEN_armTween_2227: this->f_armTween = val; return true;
        case SYM_GEN_armState_2230: this->f_armState = gd::gd_coerce_int(val); return true;
        case SYM_GEN_foodSpeed_2028: this->f_foodSpeed = val; return true;
        case SYM_GEN_chargedSpeed_2231: this->f_chargedSpeed = val; return true;
        case SYM_GEN_otherSpeed_2232: this->f_otherSpeed = val; return true;
        case SYM_GEN_arm_2233: this->f_arm = val; return true;
        case SYM_GEN_armAnimation_2234: this->f_armAnimation = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Eat_o_matic::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_global_2014: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_combatStart_127: return true;
        case SYM_GEN_onChargeReceived_2129: return true;
        case SYM_GEN_onChargeLeft_2130: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_stopArmAni_2235: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Eat_o_matic::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_global_2014: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_combatStart_127: out = fn_combatStart(args, argc); return true;
        case SYM_GEN_onChargeReceived_2129: out = fn_onChargeReceived(args, argc); return true;
        case SYM_GEN_onChargeLeft_2130: out = fn_onChargeLeft(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_stopArmAni_2235: out = fn_stopArmAni(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Eat_o_matic::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Eat_o_matic::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Eat_o_matic::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())))) {
        return gd::GdVal::from_bool(false);
    }
    if (gd::gd_truth(gd::gd_in(lv_item, gd::native_array_index(gd_ctx, this->f_currentAffectedItems, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_bool(false);
    }
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Eat_o_matic::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    this->f_affectedFood = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_428, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_affectedFood, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_foodSpeed}; return gd::native_inline_call(gd_ctx, this->f_affectedFood, SYM_GEN_addSpeed_273, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, this->f_otherFood, gd::SYM_clear, nullptr, 0);
    {
        gd::GdVal _t884 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t885 = (_t884.kind == gd::GdVal::Kind::Arr) ? _t884.arr : nullptr;
        uint32_t _len__t886 = _t885 ? _t885->len : 0u;
        for (uint32_t _t886 = 0; _t886 < _len__t886; ++_t886) {
            gd::GdVal lv_item = _t885->data[_t886];
            if (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_global_2014, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, this->f_affectedFood)))) : gd::GdVal::from_bool(false)))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, this->f_otherFood, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Eat_o_matic::fn_combatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_combatStart_127, nullptr, 0, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_armState, gd::GdVal::from_int(2LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Eat_o_matic::fn_onChargeReceived(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_numCharges, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_affectedFood, gd::GdVal::null())))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(this->f_chargedSpeed, this->f_foodSpeed)}; return gd::native_inline_call(gd_ctx, this->f_affectedFood, SYM_GEN_addSpeed_273, _ca, 1); })();
        }
        {
            gd::GdVal _t887 = gd::gd_iter_seq(gd_ctx.arena, this->f_otherFood);
            gd::GdArr* _t888 = (_t887.kind == gd::GdVal::Kind::Arr) ? _t887.arr : nullptr;
            uint32_t _len__t889 = _t888 ? _t888->len : 0u;
            for (uint32_t _t889 = 0; _t889 < _len__t889; ++_t889) {
                gd::GdVal lv_food = _t888->data[_t889];
                (void)([&]() { gd::GdVal _ca[] = {this->f_otherSpeed}; return gd::native_inline_call(gd_ctx, lv_food, SYM_GEN_addSpeed_273, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Eat_o_matic::fn_onChargeLeft(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_numCharges, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_affectedFood, gd::GdVal::null())))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(this->f_chargedSpeed, this->f_foodSpeed)}; return gd::native_inline_call(gd_ctx, this->f_affectedFood, SYM_GEN_reduceSpeed_274, _ca, 1); })();
        }
        {
            gd::GdVal _t890 = gd::gd_iter_seq(gd_ctx.arena, this->f_otherFood);
            gd::GdArr* _t891 = (_t890.kind == gd::GdVal::Kind::Arr) ? _t890.arr : nullptr;
            uint32_t _len__t892 = _t891 ? _t891->len : 0u;
            for (uint32_t _t892 = 0; _t892 < _len__t892; ++_t892) {
                gd::GdVal lv_food = _t891->data[_t892];
                (void)([&]() { gd::GdVal _ca[] = {this->f_otherSpeed}; return gd::native_inline_call(gd_ctx, lv_food, SYM_GEN_reduceSpeed_274, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Eat_o_matic::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Eat_o_matic::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Eat_o_matic::fn_stopArmAni(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Eat_o_matic::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__armState = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__armState = gd::gd_coerce_int(lv__armState);
    this->f_armState = gd::gd_coerce_int(lv__armState);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_armState, gd::GdVal::from_int(0LL))))) {
    }
    else {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_armState, gd::GdVal::from_int(1LL))))) {
        }
        else {
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Eat_o_matic::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_foodSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[10])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_chargedSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[37])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_otherSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[38])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Eat_o_matic(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Eat_o_matic>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,317u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Eat_o_matic = {CLS_Gd__gd_core_items__Exclusive__Eat_o_matic, "Eat-o-matic", "res://gd_core_items/Exclusive/Eat-o-matic.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Eat_o_matic, &Gd__gd_core_items__Exclusive__Eat_o_matic::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Eat_o_matic::call_static_fn};

void Gd__gd_core_items__Exclusive__FalseLife::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_maxHealthAmp = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__FalseLife::meta() const { return &META_Gd__gd_core_items__Exclusive__FalseLife; }
gd::GdVal Gd__gd_core_items__Exclusive__FalseLife::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__FalseLife::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__FalseLife::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_maxHealthAmp_2256: out = this->f_maxHealthAmp; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__FalseLife::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_maxHealthAmp_2256: this->f_maxHealthAmp = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__FalseLife::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_global_2014: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onOverheal_2257: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__FalseLife::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_global_2014: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onOverheal_2257: out = fn_onOverheal(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__FalseLife::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__FalseLife::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(25LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FalseLife::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[39])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), SYM_GEN_hasParam_1578, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FalseLife::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_maxHealthAmp}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeMaxHealthGain_1277, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[40]), gd::GdVal::from_str(&battle_string_literals[41])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FalseLife::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_healAmount = gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[2])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[42])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0)));
    (void)([&]() { gd::GdVal _ca[] = {lv_healAmount}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FalseLife::fn_onOverheal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_overheal = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_healEvent = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_overheal, lv_healEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FalseLife::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_maxHealthAmp = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[43])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__FalseLife(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__FalseLife>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,332u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FalseLife = {CLS_Gd__gd_core_items__Exclusive__FalseLife, "FalseLife", "res://gd_core_items/Exclusive/FalseLife.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__FalseLife, &Gd__gd_core_items__Exclusive__FalseLife::get_static_prop_fn, &Gd__gd_core_items__Exclusive__FalseLife::call_static_fn};

void Gd__gd_core_items__Shield::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_blockedDamageRes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Shield::meta() const { return &META_Gd__gd_core_items__Shield; }
gd::GdVal Gd__gd_core_items__Shield::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Shield::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Shield::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_blockedDamageRes_1939: out = this->f_blockedDamageRes; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Shield::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockedDamageRes_1939: this->f_blockedDamageRes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Shield::has_own_method(gd::SymId m) const {
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
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Shield::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
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
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Shield::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Shield::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_blockedDamageRes = gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[44]), gd::GdVal::from_str(&battle_string_literals[45])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[46]), gd::GdVal::from_str(&battle_string_literals[47])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_prepare_122, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Shield::fn_getDamageBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[48])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Shield::fn_beforeBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getDamageBlock_1940, nullptr, 0), gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, this->f_blockedDamageRes, SYM_GEN_applyDamageReduction_1526, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Shield::fn_afterBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Shield::fn_canBlockDamageRes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_triggerOnMeleeAttacked_1529, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Shield::fn_preTakeDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_damageRes}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canBlockDamageRes_1943, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        this->f_blockedDamageRes = lv_damageRes;
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_beforeBlock_1941, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Shield::fn_onCharacterAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_blockedDamageRes, lv_damageRes)))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_afterBlock_1942, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[49]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {this->f_blockedDamageRes}))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
        this->f_blockedDamageRes = gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Shield::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Shield(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Shield>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,633u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Shield = {CLS_Gd__gd_core_items__Shield, "Shield", "res://gd_core_items/Shield.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Shield, &Gd__gd_core_items__Shield::get_static_prop_fn, &Gd__gd_core_items__Shield::call_static_fn};

void Gd__gd_core_items__Exclusive__HeavyDrinking::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_allPotions = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_boostedPotions = gd::GdVal::from_int(0LL);
    this->f_potionSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__HeavyDrinking::meta() const { return &META_Gd__gd_core_items__Exclusive__HeavyDrinking; }
gd::GdVal Gd__gd_core_items__Exclusive__HeavyDrinking::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__HeavyDrinking::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__HeavyDrinking::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_allPotions_2302: out = this->f_allPotions; return true;
        case SYM_GEN_boostedPotions_2303: out = this->f_boostedPotions; return true;
        case SYM_GEN_potionSpeed_2260: out = this->f_potionSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__HeavyDrinking::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_allPotions_2302: this->f_allPotions = val; return true;
        case SYM_GEN_boostedPotions_2303: this->f_boostedPotions = val; return true;
        case SYM_GEN_potionSpeed_2260: this->f_potionSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__HeavyDrinking::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_onBought_455: return true;
        case SYM_GEN_isAffectingDistinct_254: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_global_2014: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onItemRoll_2018: return true;
        case SYM_GEN_onItemRolled_2019: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__HeavyDrinking::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_onBought_455: out = fn_onBought(args, argc); return true;
        case SYM_GEN_isAffectingDistinct_254: out = fn_isAffectingDistinct(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_global_2014: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onItemRoll_2018: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_2019: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__HeavyDrinking::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__HeavyDrinking::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_boostedPotions;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeavyDrinking::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_data, gd::GdVal::null())))) {
        this->f_boostedPotions = lv_data;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeavyDrinking::fn_onBought(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_boostedPotions = gd::GdVal::from_int(3LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeavyDrinking::fn_isAffectingDistinct(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    return gd::GdVal::from_bool(gd::native_scalar_eq(lv_color, gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeavyDrinking::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(11LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeavyDrinking::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(11LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeavyDrinking::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumDistinctAffectedItems_430, nullptr, 0), this->f_potionSpeed)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, this->f_allPotions, gd::SYM_clear, nullptr, 0);
    {
        gd::GdVal _t893 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t894 = (_t893.kind == gd::GdVal::Kind::Arr) ? _t893.arr : nullptr;
        uint32_t _len__t895 = _t894 ? _t894->len : 0u;
        for (uint32_t _t895 = 0; _t895 < _len__t895; ++_t895) {
            gd::GdVal lv_item = _t894->data[_t895];
            if (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(11LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::from_obj(this))))) : gd::GdVal::from_bool(false)))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, this->f_allPotions, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeavyDrinking::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_allPotions, gd::SYM_empty, nullptr, 0))))) {
        gd::GdVal lv_potionToTrigger = ([&]() { gd::GdVal _ca[] = {this->f_allPotions}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_pickRandomElement_1746, _ca, 1); })();
        (void)gd::native_inline_call(gd_ctx, lv_potionToTrigger, SYM_GEN_triggerPotion_1850, nullptr, 0);
        (void)gd::native_inline_call(gd_ctx, lv_potionToTrigger, SYM_GEN_miniActivate_470, nullptr, 0);
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeavyDrinking::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeavyDrinking::fn_onItemRolled(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(11LL)}; return gd::native_inline_call(gd_ctx, lv_descr, SYM_GEN_hasType_79, _ca, 1); })())) {
        this->f_boostedPotions = gd::gd_sub(this->f_boostedPotions, gd::GdVal::from_int(1LL));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeavyDrinking::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_potionSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[10])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__HeavyDrinking(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__HeavyDrinking>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,361u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__HeavyDrinking = {CLS_Gd__gd_core_items__Exclusive__HeavyDrinking, "HeavyDrinking", "res://gd_core_items/Exclusive/HeavyDrinking.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__HeavyDrinking, &Gd__gd_core_items__Exclusive__HeavyDrinking::get_static_prop_fn, &Gd__gd_core_items__Exclusive__HeavyDrinking::call_static_fn};

void Gd__gd_core_items__Exclusive__JynxStaff::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_numActivations = gd::GdVal::from_int(0);
    this->f_manaCost = gd::GdVal::null();
    this->f_permDamBonus = gd::GdVal::null();
    this->f_speedBonus = gd::GdVal::null();
    this->f_maxActivations = gd::GdVal::null();
    this->f_luckRemoval = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__JynxStaff::meta() const { return &META_Gd__gd_core_items__Exclusive__JynxStaff; }
gd::GdVal Gd__gd_core_items__Exclusive__JynxStaff::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__JynxStaff::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__JynxStaff::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_numActivations_1904: out = this->f_numActivations; return true;
        case SYM_GEN_manaCost_1815: out = this->f_manaCost; return true;
        case SYM_GEN_permDamBonus_997: out = this->f_permDamBonus; return true;
        case SYM_GEN_speedBonus_1877: out = this->f_speedBonus; return true;
        case SYM_GEN_maxActivations_1905: out = this->f_maxActivations; return true;
        case SYM_GEN_luckRemoval_2330: out = this->f_luckRemoval; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__JynxStaff::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numActivations_1904: this->f_numActivations = gd::gd_coerce_int(val); return true;
        case SYM_GEN_manaCost_1815: this->f_manaCost = val; return true;
        case SYM_GEN_permDamBonus_997: this->f_permDamBonus = val; return true;
        case SYM_GEN_speedBonus_1877: this->f_speedBonus = val; return true;
        case SYM_GEN_maxActivations_1905: this->f_maxActivations = val; return true;
        case SYM_GEN_luckRemoval_2330: this->f_luckRemoval = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__JynxStaff::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__JynxStaff::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__JynxStaff::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__JynxStaff::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__JynxStaff::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_numActivations = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__JynxStaff::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_333, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_event, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_permDamBonus}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_numActivations, this->f_maxActivations)))) {
            {
                gd::GdVal _t896 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
                gd::GdArr* _t897 = (_t896.kind == gd::GdVal::Kind::Arr) ? _t896.arr : nullptr;
                uint32_t _len__t898 = _t897 ? _t897->len : 0u;
                for (uint32_t _t898 = 0; _t898 < _len__t898; ++_t898) {
                    gd::GdVal lv_item = _t897->data[_t898];
                    (void)([&]() { gd::GdVal _ca[] = {this->f_speedBonus}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
                }
            }
            this->f_numActivations = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numActivations, gd::GdVal::from_int(1LL)));
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_luckRemoval}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeLucky_349, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__JynxStaff::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_manaCost = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[50])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_permDamBonus = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[51])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_speedBonus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[10])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_maxActivations = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[11])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_luckRemoval = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[52])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__JynxStaff(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__JynxStaff>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,376u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__JynxStaff = {CLS_Gd__gd_core_items__Exclusive__JynxStaff, "JynxStaff", "res://gd_core_items/Exclusive/JynxStaff.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__JynxStaff, &Gd__gd_core_items__Exclusive__JynxStaff::get_static_prop_fn, &Gd__gd_core_items__Exclusive__JynxStaff::call_static_fn};

void Gd__gd_core_items__Exclusive__LuckyCat::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_sales = gd::GdVal::null();
    this->f_goldThreshold1 = gd::GdVal::null();
    this->f_goldThreshold2 = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__LuckyCat::meta() const { return &META_Gd__gd_core_items__Exclusive__LuckyCat; }
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__LuckyCat::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__LuckyCat::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_sales_2356: out = this->f_sales; return true;
        case SYM_GEN_goldThreshold1_2357: out = this->f_goldThreshold1; return true;
        case SYM_GEN_goldThreshold2_2358: out = this->f_goldThreshold2; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__LuckyCat::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_sales_2356: this->f_sales = val; return true;
        case SYM_GEN_goldThreshold1_2357: this->f_goldThreshold1 = val; return true;
        case SYM_GEN_goldThreshold2_2358: this->f_goldThreshold2 = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__LuckyCat::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_getCounterValue_2351: return true;
        case SYM_GEN_condition1Fulfilled_2359: return true;
        case SYM_GEN_condition2Fulfilled_2360: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_updatePaws_2361: return true;
        case SYM_GEN_onAffectedItemAdded_435: return true;
        case SYM_GEN_onAffectedItemRemoved_436: return true;
        case SYM_GEN_onAddToInventory_419: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_canAffect_global_2014: return true;
        case SYM_GEN_onSaleRoll_2093: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__LuckyCat::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_getCounterValue_2351: out = fn_getCounterValue(args, argc); return true;
        case SYM_GEN_condition1Fulfilled_2359: out = fn_condition1Fulfilled(args, argc); return true;
        case SYM_GEN_condition2Fulfilled_2360: out = fn_condition2Fulfilled(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_updatePaws_2361: out = fn_updatePaws(args, argc); return true;
        case SYM_GEN_onAffectedItemAdded_435: out = fn_onAffectedItemAdded(args, argc); return true;
        case SYM_GEN_onAffectedItemRemoved_436: out = fn_onAffectedItemRemoved(args, argc); return true;
        case SYM_GEN_onAddToInventory_419: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_canAffect_global_2014: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN_onSaleRoll_2093: out = fn_onSaleRoll(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__LuckyCat::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn_getCounterValue(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedGoldValue_494, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn_condition1Fulfilled(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_gold = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_gold = gd::gd_coerce_int(lv_gold);
    return gd::GdVal::from_bool(gd::gd_gt(lv_gold, this->f_goldThreshold1));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn_condition2Fulfilled(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_gold = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(gd::gd_gt(lv_gold, this->f_goldThreshold2));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_gold = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue_2351, nullptr, 0);
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_gold}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_condition1Fulfilled_2359, _ca, 1); })())) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeCritResistance_1173, _ca, 1); })();
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_gold}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_condition2Fulfilled_2360, _ca, 1); })())) {
            gd::GdVal lv_bonusSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[10])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
            {
                gd::GdVal _t899 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
                gd::GdArr* _t900 = (_t899.kind == gd::GdVal::Kind::Arr) ? _t899.arr : nullptr;
                uint32_t _len__t901 = _t900 ? _t900->len : 0u;
                for (uint32_t _t901 = 0; _t901 < _len__t901; ++_t901) {
                    gd::GdVal lv_item = _t900->data[_t901];
                    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_global_2014, _ca, 1); })())) {
                        (void)([&]() { gd::GdVal _ca[] = {lv_bonusSpeed}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
                    }
                }
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_642, _ca, 1, _out); return _out; })();
    gd::GdVal lv_colors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_inactiveColor_2834), gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_inactiveColor_2834)}));
    gd::GdVal lv_gold = gd::GdVal::from_int(0);
    if (gd::gd_truth(this->f_placed)) {
        lv_gold = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue_2351, nullptr, 0));
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_gold}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_condition1Fulfilled_2359, _ca, 1); })())) {
            { gd::GdVal _t902 = lv_colors; gd::GdVal _t903 = gd::GdVal::from_int(0LL); gd::native_array_set_index(gd_ctx, _t902, _t903, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_modifiedColor_2829)); }
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_gold}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_condition2Fulfilled_2360, _ca, 1); })())) {
                { gd::GdVal _t904 = lv_colors; gd::GdVal _t905 = gd::GdVal::from_int(1LL); gd::native_array_set_index(gd_ctx, _t904, _t905, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_modifiedColor_2829)); }
            }
        }
    }
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, lv_colors, gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModeDescription_645, _ca, 4); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn_updatePaws(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_gold = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue_2351, nullptr, 0);
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_gold}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_condition1Fulfilled_2359, _ca, 1); })())) {
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_gold}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_condition2Fulfilled_2360, _ca, 1); })())) {
        }
        else {
        }
    }
    else {
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadowTexture_789, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn_onAffectedItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updatePaws_2361, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn_onAffectedItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updatePaws_2361, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updatePaws_2361, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadowTexture_789, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getRarity_236, nullptr, 0), gd::GdVal::from_int(4LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn_onSaleRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_sales = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[53])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_goldThreshold1 = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[54])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_goldThreshold2 = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[55])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__LuckyCat(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__LuckyCat>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,391u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__LuckyCat = {CLS_Gd__gd_core_items__Exclusive__LuckyCat, "LuckyCat", "res://gd_core_items/Exclusive/LuckyCat.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__LuckyCat, &Gd__gd_core_items__Exclusive__LuckyCat::get_static_prop_fn, &Gd__gd_core_items__Exclusive__LuckyCat::call_static_fn};

void Gd__gd_core_items__Exclusive__MissFortune::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_luckNeeded = gd::GdVal::null();
    this->f_numBuffs = gd::GdVal::null();
    this->f_activationParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__MissFortune::meta() const { return &META_Gd__gd_core_items__Exclusive__MissFortune; }
gd::GdVal Gd__gd_core_items__Exclusive__MissFortune::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__MissFortune::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__MissFortune::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_luckNeeded_1874: out = this->f_luckNeeded; return true;
        case SYM_GEN_numBuffs_2005: out = this->f_numBuffs; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MissFortune::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_luckNeeded_1874: this->f_luckNeeded = val; return true;
        case SYM_GEN_numBuffs_2005: this->f_numBuffs = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MissFortune::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MissFortune::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__MissFortune::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__MissFortune::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), this->f_luckNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_luckNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useLucky_350, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_numBuffs, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMostBuffs_367, _ca, 2); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MissFortune::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_luckNeeded = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[52])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_numBuffs = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[29])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MissFortune(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__MissFortune>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,406u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MissFortune = {CLS_Gd__gd_core_items__Exclusive__MissFortune, "MissFortune", "res://gd_core_items/Exclusive/MissFortune.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__MissFortune, &Gd__gd_core_items__Exclusive__MissFortune::get_static_prop_fn, &Gd__gd_core_items__Exclusive__MissFortune::call_static_fn};

void Gd__gd_core_items__Exclusive__PerpetuumMobile::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_usedStacks = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_staminaUsed = gd::GdVal::from_float(0.0);
    this->f_stamina = gd::GdVal::null();
    this->f_buffRefund = gd::GdVal::null();
    this->f_staminaRefund = gd::GdVal::null();
    this->f_speed_v = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PerpetuumMobile::meta() const { return &META_Gd__gd_core_items__Exclusive__PerpetuumMobile; }
gd::GdVal Gd__gd_core_items__Exclusive__PerpetuumMobile::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PerpetuumMobile::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PerpetuumMobile::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_usedStacks_1716: out = this->f_usedStacks; return true;
        case SYM_GEN_staminaUsed_2076: out = this->f_staminaUsed; return true;
        case SYM_GEN_stamina_2156: out = this->f_stamina; return true;
        case SYM_GEN_buffRefund_2420: out = this->f_buffRefund; return true;
        case SYM_GEN_staminaRefund_2421: out = this->f_staminaRefund; return true;
        case SYM_GEN_speed_v_2179: out = this->f_speed_v; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PerpetuumMobile::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_usedStacks_1716: this->f_usedStacks = val; return true;
        case SYM_GEN_staminaUsed_2076: this->f_staminaUsed = val; return true;
        case SYM_GEN_stamina_2156: this->f_stamina = val; return true;
        case SYM_GEN_buffRefund_2420: this->f_buffRefund = val; return true;
        case SYM_GEN_staminaRefund_2421: this->f_staminaRefund = val; return true;
        case SYM_GEN_speed_v_2179: this->f_speed_v = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PerpetuumMobile::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onBuffChanged_2006: return true;
        case SYM_GEN_onStaminaUsed_2405: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PerpetuumMobile::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onBuffChanged_2006: out = fn_onBuffChanged(args, argc); return true;
        case SYM_GEN_onStaminaUsed_2405: out = fn_onStaminaUsed(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PerpetuumMobile::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PerpetuumMobile::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(6LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isClassItem_248, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PerpetuumMobile::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[56])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterBuffs_374, _ca, 1); })();
    {
        gd::GdVal _t906 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0));
        gd::GdArr* _t907 = (_t906.kind == gd::GdVal::Kind::Arr) ? _t906.arr : nullptr;
        uint32_t _len__t908 = _t907 ? _t907->len : 0u;
        for (uint32_t _t908 = 0; _t908 < _len__t908; ++_t908) {
            gd::GdVal lv_buff = _t907->data[_t908];
            { gd::GdVal _t909 = this->f_usedStacks; gd::GdVal _t910 = lv_buff; gd::native_array_set_index(gd_ctx, _t909, _t910, gd::GdVal::from_float(0.0)); }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[57]), gd::GdVal::from_str(&battle_string_literals[58])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    this->f_staminaUsed = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_speed_v, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PerpetuumMobile::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_stamina, gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxStaminaTemporary_316, _ca, 3); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PerpetuumMobile::fn_onBuffChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[59]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getParam_1575, _ca, 2); })())) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv_used = gd::gd_neg(lv_amount);
        gd::GdVal lv_buffType = gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getType_1572, nullptr, 0);
        { gd::GdVal _t911 = this->f_usedStacks; gd::GdVal _t912 = lv_buffType; gd::native_array_set_index(gd_ctx, _t911, _t912, gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, _t911, _t912), lv_used)); }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PerpetuumMobile::fn_onStaminaUsed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_staminaUsed = gd::gd_add(gd_ctx, this->f_staminaUsed, lv_amount);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PerpetuumMobile::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t913 = gd::gd_iter_seq(gd_ctx.arena, this->f_usedStacks);
        gd::GdArr* _t914 = (_t913.kind == gd::GdVal::Kind::Arr) ? _t913.arr : nullptr;
        uint32_t _len__t915 = _t914 ? _t914->len : 0u;
        for (uint32_t _t915 = 0; _t915 < _len__t915; ++_t915) {
            gd::GdVal lv_buffType = _t914->data[_t915];
            gd::GdVal lv_toRefund = gd::gd_coerce_int(gd::gd_round(gd::gd_mul(gd::native_array_index(gd_ctx, this->f_usedStacks, lv_buffType), this->f_buffRefund)));
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_toRefund, gd::GdVal::from_int(0LL))))) {
                { gd::GdVal _t916 = this->f_usedStacks; gd::GdVal _t917 = lv_buffType; gd::native_array_set_index(gd_ctx, _t916, _t917, gd::gd_sub(gd::native_array_index(gd_ctx, _t916, _t917), lv_toRefund)); }
                (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), lv_buffType, lv_toRefund}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 3); })();
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_staminaUsed, this->f_staminaRefund)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_318, _ca, 1); })();
    this->f_staminaUsed = gd::GdVal::from_int(0LL);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PerpetuumMobile::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[0])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_buffRefund = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[60])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_staminaRefund = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[61])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_speed_v = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[10])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PerpetuumMobile(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__PerpetuumMobile>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,422u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PerpetuumMobile = {CLS_Gd__gd_core_items__Exclusive__PerpetuumMobile, "PerpetuumMobile", "res://gd_core_items/Exclusive/PerpetuumMobile.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__PerpetuumMobile, &Gd__gd_core_items__Exclusive__PerpetuumMobile::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PerpetuumMobile::call_static_fn};

void Gd__gd_core_items__Exclusive__PrismaticSword::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_affectedTypes = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_holyDam = gd::GdVal::null();
    this->f_debuffs = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PrismaticSword::meta() const { return &META_Gd__gd_core_items__Exclusive__PrismaticSword; }
gd::GdVal Gd__gd_core_items__Exclusive__PrismaticSword::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PrismaticSword::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PrismaticSword::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_affectedTypes_2444: out = this->f_affectedTypes; return true;
        case SYM_GEN_holyDam_2445: out = this->f_holyDam; return true;
        case SYM_GEN_debuffs_2151: out = this->f_debuffs; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PrismaticSword::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedTypes_2444: this->f_affectedTypes = val; return true;
        case SYM_GEN_holyDam_2445: this->f_holyDam = val; return true;
        case SYM_GEN_debuffs_2151: this->f_debuffs = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PrismaticSword::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_onPreDealDamage_late_906: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PrismaticSword::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onPreDealDamage_late_906: out = fn_onPreDealDamage_late(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PrismaticSword::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PrismaticSword::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_affectedTypes = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countTypes_495, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_array_index(gd_ctx, this->f_affectedTypes, gd::GdVal::from_int(23LL)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(gd::native_array_index(gd_ctx, this->f_affectedTypes, gd::GdVal::from_int(23LL)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[10])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PrismaticSword::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_holyDam, gd::native_array_index(gd_ctx, this->f_affectedTypes, gd::GdVal::from_int(22LL)))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseChance2_169, nullptr, 0), gd::native_array_index(gd_ctx, this->f_affectedTypes, gd::GdVal::from_int(25LL)))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_debuffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictRandomDebuffs_357, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PrismaticSword::fn_onPreDealDamage_late(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_ceil(gd::gd_mul(gd::gd_div(gd_ctx, gd::gd_mul(gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[62])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()), gd::GdVal::from_float(100.0)), gd::native_array_index(gd_ctx, this->f_affectedTypes, gd::GdVal::from_int(24LL))))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PrismaticSword::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(24LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(23LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(25LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PrismaticSword::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_getDescription_642, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_placed)))) {
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[63]), gd::GdVal::from_str(&battle_string_literals[64])}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[65]), gd::GdVal::from_str(&battle_string_literals[64])}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[66]), gd::GdVal::from_str(&battle_string_literals[64])}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[67]), gd::GdVal::from_str(&battle_string_literals[64])}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        return lv_descr;
    }
    gd::GdVal lv_typesDict = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countTypes_495, _ca, 1); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[68]), gd::native_array_index(gd_ctx, lv_typesDict, gd::GdVal::from_int(23LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_452, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[69]), gd::native_array_index(gd_ctx, lv_typesDict, gd::GdVal::from_int(24LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_452, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[70]), gd::native_array_index(gd_ctx, lv_typesDict, gd::GdVal::from_int(22LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_452, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[71]), gd::native_array_index(gd_ctx, lv_typesDict, gd::GdVal::from_int(25LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_452, _ca, 3); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PrismaticSword::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_holyDam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[51])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_debuffs = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[72])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PrismaticSword(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__PrismaticSword>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,438u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PrismaticSword = {CLS_Gd__gd_core_items__Exclusive__PrismaticSword, "PrismaticSword", "res://gd_core_items/Exclusive/PrismaticSword.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__PrismaticSword, &Gd__gd_core_items__Exclusive__PrismaticSword::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PrismaticSword::call_static_fn};

void Gd__gd_core_items__Exclusive__RainbowPotion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Potion::init_fields(gd_ctx);
    this->f_usedBuffs = gd::GdVal::from_int(0);
    this->f_buffsNeeded = gd::GdVal::null();
    this->f_numPotions = gd::GdVal::null();
    this->f_buffsPerStaff = gd::GdVal::null();
    this->f_manaPerBook = gd::GdVal::null();
    this->f_staminaPerBook = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__RainbowPotion::meta() const { return &META_Gd__gd_core_items__Exclusive__RainbowPotion; }
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Potion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__RainbowPotion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__RainbowPotion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_usedBuffs_2269: out = this->f_usedBuffs; return true;
        case SYM_GEN_buffsNeeded_2085: out = this->f_buffsNeeded; return true;
        case SYM_GEN_numPotions_2453: out = this->f_numPotions; return true;
        case SYM_GEN_buffsPerStaff_2454: out = this->f_buffsPerStaff; return true;
        case SYM_GEN_manaPerBook_2455: out = this->f_manaPerBook; return true;
        case SYM_GEN_staminaPerBook_2456: out = this->f_staminaPerBook; return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__RainbowPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_usedBuffs_2269: this->f_usedBuffs = gd::gd_coerce_int(val); return true;
        case SYM_GEN_buffsNeeded_2085: this->f_buffsNeeded = val; return true;
        case SYM_GEN_numPotions_2453: this->f_numPotions = val; return true;
        case SYM_GEN_buffsPerStaff_2454: this->f_buffsPerStaff = val; return true;
        case SYM_GEN_manaPerBook_2455: this->f_manaPerBook = val; return true;
        case SYM_GEN_staminaPerBook_2456: this->f_staminaPerBook = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__RainbowPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_global_2014: return true;
        case SYM_GEN_getAffectedCellsAfterRotate_primary_410: return true;
        case SYM_GEN_isAffectingDistinct_254: return true;
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_canAffect_tertiary_288: return true;
        case SYM_GEN_onTriggerPotion_1849: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onBuffsChanged_2087: return true;
        case SYM_GEN_getGatedDescriptor_956: return true;
        case SYM_GEN_getStarPosition_1853: return true;
        case SYM_GEN_getRelatedItems_459: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN_getRelatedItemHeight_700: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__RainbowPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_global_2014: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN_getAffectedCellsAfterRotate_primary_410: out = fn_getAffectedCellsAfterRotate_primary(args, argc); return true;
        case SYM_GEN_isAffectingDistinct_254: out = fn_isAffectingDistinct(args, argc); return true;
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_canAffect_tertiary_288: out = fn_canAffect_tertiary(args, argc); return true;
        case SYM_GEN_onTriggerPotion_1849: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onBuffsChanged_2087: out = fn_onBuffsChanged(args, argc); return true;
        case SYM_GEN_getGatedDescriptor_956: out = fn_getGatedDescriptor(args, argc); return true;
        case SYM_GEN_getStarPosition_1853: out = fn_getStarPosition(args, argc); return true;
        case SYM_GEN_getRelatedItems_459: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_700: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__RainbowPotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Potion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(11LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::from_obj(this))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_getAffectedCellsAfterRotate_primary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rotatedCells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_faceDirection, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))))) {
        return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, lv_rotatedCells, gd::GdVal::from_int(1LL)), gd::GdVal::from_vec2(0.0, -1.0))}));
    }
    else {
        return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, lv_rotatedCells, gd::GdVal::from_int(0LL)), gd::GdVal::from_vec2(0.0, -1.0))}));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_isAffectingDistinct(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    return (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_color, gd::GdVal::from_int(1LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_color, gd::GdVal::from_int(2LL))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(15LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_canAffect_tertiary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(32LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasTag_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_allPotions = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t918 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t919 = (_t918.kind == gd::GdVal::Kind::Arr) ? _t918.arr : nullptr;
        uint32_t _len__t920 = _t919 ? _t919->len : 0u;
        for (uint32_t _t920 = 0; _t920 < _len__t920; ++_t920) {
            gd::GdVal lv_item = _t919->data[_t920];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_global_2014, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, lv_allPotions, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_allPotions, gd::GdVal::from_str(&battle_string_literals[73])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_shuffleEngine_1747, _ca, 2); })();
    gd::GdVal lv_potionsToTrigger = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t921 = gd::gd_iter_seq(gd_ctx.arena, lv_allPotions);
        gd::GdArr* _t922 = (_t921.kind == gd::GdVal::Kind::Arr) ? _t921.arr : nullptr;
        uint32_t _len__t923 = _t922 ? _t922->len : 0u;
        for (uint32_t _t923 = 0; _t923 < _len__t923; ++_t923) {
            gd::GdVal lv_potion = _t922->data[_t923];
            gd::GdVal lv_typeExists = gd::GdVal::from_bool(false);
            {
                gd::GdVal _t924 = gd::gd_iter_seq(gd_ctx.arena, lv_potionsToTrigger);
                gd::GdArr* _t925 = (_t924.kind == gd::GdVal::Kind::Arr) ? _t924.arr : nullptr;
                uint32_t _len__t926 = _t925 ? _t925->len : 0u;
                for (uint32_t _t926 = 0; _t926 < _len__t926; ++_t926) {
                    gd::GdVal lv_triggeredPotion = _t925->data[_t926];
                    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, lv_triggeredPotion, SYM_GEN_descriptor_2)}; return gd::native_inline_call(gd_ctx, lv_potion, SYM_GEN_isA_245, _ca, 1); })())) {
                        lv_typeExists = gd::GdVal::from_bool(true);
                        break;
                    }
                }
            }
            if (gd::gd_truth(lv_typeExists)) {
                continue;
            }
            (void)([&]() { gd::GdVal _ca[] = {lv_potion}; return gd::native_inline_call(gd_ctx, lv_potionsToTrigger, gd::SYM_push_back, _ca, 1); })();
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, lv_potionsToTrigger, gd::SYM_size, nullptr, 0), this->f_numPotions)))) {
                break;
            }
        }
    }
    {
        gd::GdVal _t927 = gd::gd_iter_seq(gd_ctx.arena, lv_potionsToTrigger);
        gd::GdArr* _t928 = (_t927.kind == gd::GdVal::Kind::Arr) ? _t927.arr : nullptr;
        uint32_t _len__t929 = _t928 ? _t928->len : 0u;
        for (uint32_t _t929 = 0; _t929 < _len__t929; ++_t929) {
            gd::GdVal lv_potion = _t928->data[_t929];
            (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, lv_potion, SYM_GEN_triggerPotion_1850, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[74])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterBuffs_374, _ca, 1); })();
    this->f_usedBuffs = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_books = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumDistinctAffectedItems_430, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_books, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_books, this->f_manaPerBook)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_books, this->f_staminaPerBook)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxStaminaTemporary_316, _ca, 1); })();
    }
    gd::GdVal lv_staffs = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumDistinctAffectedItems_430, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_staffs, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_buffsPerStaff, lv_staffs)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false), gd::GdVal::from_bool(false), gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_onBuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[59]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getParam_1575, _ca, 2); })())) : gd::GdVal::from_bool(false)))) {
        this->f_usedBuffs = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_usedBuffs, gd::gd_coerce_int(gd::gd_abs(lv_amount))));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_usedBuffs, this->f_buffsNeeded)))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1848, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_getGatedDescriptor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__rarity = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_getStarPosition(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_getRelatedItemColumns(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(3LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_getRelatedItemHeight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(250LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Potion::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_buffsNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[75])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_numPotions = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[76])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_buffsPerStaff = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[29])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_manaPerBook = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[77])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_staminaPerBook = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[0])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__RainbowPotion(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__RainbowPotion>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,454u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RainbowPotion = {CLS_Gd__gd_core_items__Exclusive__RainbowPotion, "RainbowPotion", "res://gd_core_items/Exclusive/RainbowPotion.gd", &META_Gd__gd_core_items__Potion, true, _alloc_Gd__gd_core_items__Exclusive__RainbowPotion, &Gd__gd_core_items__Exclusive__RainbowPotion::get_static_prop_fn, &Gd__gd_core_items__Exclusive__RainbowPotion::call_static_fn};

void Gd__gd_core_items__Lightsaber::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_blindingLightTimer = gd::GdVal::null();
    this->f_activationParticles = gd::GdVal::null();
    this->f_regenNeeded = gd::GdVal::null();
    this->f_blind = gd::GdVal::null();
    this->f_damPerBlind = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Lightsaber::meta() const { return &META_Gd__gd_core_items__Lightsaber; }
gd::GdVal Gd__gd_core_items__Lightsaber::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Lightsaber::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Lightsaber::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_blindingLightTimer_1910: out = this->f_blindingLightTimer; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_regenNeeded_942: out = this->f_regenNeeded; return true;
        case SYM_GEN_blind_1911: out = this->f_blind; return true;
        case SYM_GEN_damPerBlind_1912: out = this->f_damPerBlind; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Lightsaber::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blindingLightTimer_1910: this->f_blindingLightTimer = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_regenNeeded_942: this->f_regenNeeded = val; return true;
        case SYM_GEN_blind_1911: this->f_blind = val; return true;
        case SYM_GEN_damPerBlind_1912: this->f_damPerBlind = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Lightsaber::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_inflict_1913: return true;
        case SYM_GEN_onRegenChanged_1891: return true;
        case SYM_GEN_onOpponentBlindChanged_1914: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN_onBlindingLightTimeout_1915: return true;
        case SYM_GEN_onBlindingLightEnded_1916: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Lightsaber::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_inflict_1913: out = fn_inflict(args, argc); return true;
        case SYM_GEN_onRegenChanged_1891: out = fn_onRegenChanged(args, argc); return true;
        case SYM_GEN_onOpponentBlindChanged_1914: out = fn_onOpponentBlindChanged(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onBlindingLightTimeout_1915: out = fn_onBlindingLightTimeout(args, argc); return true;
        case SYM_GEN_onBlindingLightEnded_1916: out = fn_onBlindingLightEnded(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Lightsaber::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Lightsaber::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[78]), gd::GdVal::from_str(&battle_string_literals[79])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[80]), gd::GdVal::from_str(&battle_string_literals[81])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[82]), gd::GdVal::from_str(&battle_string_literals[83])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Lightsaber::fn_inflict(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_duration = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_int(109LL), this->f_blind, lv_duration, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacksTemporary_202, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Lightsaber::fn_onRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_blindingLightActive_1077)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRegeneration_1233, nullptr, 0), this->f_regenNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
        (void)gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_startBlindingLight_1197, nullptr, 0);
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_regenNeeded, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_346, _ca, 2); })();
        gd::GdVal lv_duration = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[27])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_duration, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflict_1913, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_duration}; return gd::native_inline_call(gd_ctx, this->f_blindingLightTimer, SYM_GEN_start_1779, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Lightsaber::fn_onOpponentBlindChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_damPerBlind, lv_amount)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_162, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Lightsaber::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_blindingLightTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Lightsaber::fn_onBlindingLightTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[84])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_callNextFrame_1797, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Lightsaber::fn_onBlindingLightEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onRegenChanged_1891, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Lightsaber::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Lightsaber::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv_active)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Lightsaber::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_blindingLightTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[85]), gd::GdVal::from_str(&battle_string_literals[86]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_regenNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[87])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_blind = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[88])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_damPerBlind = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[89])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Lightsaber(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Lightsaber>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,597u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Lightsaber = {CLS_Gd__gd_core_items__Lightsaber, "Lightsaber", "res://gd_core_items/Lightsaber.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Lightsaber, &Gd__gd_core_items__Lightsaber::get_static_prop_fn, &Gd__gd_core_items__Lightsaber::call_static_fn};

void Gd__gd_core_items__Exclusive__SmellyBarrier::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_blockAcc = gd::GdVal::from_int(0);
    this->f_boostedGarlic = gd::GdVal::from_int(0LL);
    this->f_garlicDescriptor = gd::GdVal::null();
    this->f_garlicBlockBonus = gd::GdVal::null();
    this->f_blockForPoison = gd::GdVal::null();
    this->f_poisonForBlock = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SmellyBarrier::meta() const { return &META_Gd__gd_core_items__Exclusive__SmellyBarrier; }
gd::GdVal Gd__gd_core_items__Exclusive__SmellyBarrier::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SmellyBarrier::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SmellyBarrier::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_blockAcc_1946: out = this->f_blockAcc; return true;
        case SYM_GEN_boostedGarlic_2505: out = this->f_boostedGarlic; return true;
        case SYM_GEN_garlicDescriptor_2506: out = this->f_garlicDescriptor; return true;
        case SYM_GEN_garlicBlockBonus_2507: out = this->f_garlicBlockBonus; return true;
        case SYM_GEN_blockForPoison_2508: out = this->f_blockForPoison; return true;
        case SYM_GEN_poisonForBlock_2509: out = this->f_poisonForBlock; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SmellyBarrier::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockAcc_1946: this->f_blockAcc = gd::gd_coerce_int(val); return true;
        case SYM_GEN_boostedGarlic_2505: this->f_boostedGarlic = val; return true;
        case SYM_GEN_garlicDescriptor_2506: this->f_garlicDescriptor = val; return true;
        case SYM_GEN_garlicBlockBonus_2507: this->f_garlicBlockBonus = val; return true;
        case SYM_GEN_blockForPoison_2508: this->f_blockForPoison = val; return true;
        case SYM_GEN_poisonForBlock_2509: this->f_poisonForBlock = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SmellyBarrier::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onBought_455: return true;
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onItemGaveBlock_1948: return true;
        case SYM_GEN_onItemRoll_2018: return true;
        case SYM_GEN_onItemRolled_2019: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SmellyBarrier::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onBought_455: out = fn_onBought(args, argc); return true;
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemGaveBlock_1948: out = fn_onItemGaveBlock(args, argc); return true;
        case SYM_GEN_onItemRoll_2018: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_2019: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SmellyBarrier::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SmellyBarrier::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_garlicDescriptor}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isA_245, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBlock_291, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SmellyBarrier::fn_onBought(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_boostedGarlic = gd::GdVal::from_int(3LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SmellyBarrier::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_boostedGarlic;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SmellyBarrier::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_data, gd::GdVal::null())))) {
        this->f_boostedGarlic = lv_data;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SmellyBarrier::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_blockAcc = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    {
        gd::GdVal _t930 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t931 = (_t930.kind == gd::GdVal::Kind::Arr) ? _t930.arr : nullptr;
        uint32_t _len__t932 = _t931 ? _t931->len : 0u;
        for (uint32_t _t932 = 0; _t932 < _len__t932; ++_t932) {
            gd::GdVal lv_item = _t931->data[_t932];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_garlicDescriptor}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isA_245, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_garlicBlockBonus}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusBlock_1879, _ca, 1); })();
            }
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBlock_291, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[12]), gd::GdVal::from_str(&battle_string_literals[13])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SmellyBarrier::fn_onItemGaveBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    this->f_blockAcc = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_blockAcc, lv_amount));
    gd::GdVal lv_poison = gd::gd_div(gd_ctx, this->f_blockAcc, this->f_blockForPoison);
    this->f_blockAcc = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_blockAcc, this->f_blockForPoison));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_poison, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_poison, this->f_poisonForBlock), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 2); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SmellyBarrier::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SmellyBarrier::fn_onItemRolled(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_descr, this->f_garlicDescriptor)))) {
        this->f_boostedGarlic = gd::gd_sub(this->f_boostedGarlic, gd::GdVal::from_int(1LL));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SmellyBarrier::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_garlicDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[90])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_garlicBlockBonus = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[91])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_blockForPoison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[92])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_poisonForBlock = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[93])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SmellyBarrier(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__SmellyBarrier>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,486u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SmellyBarrier = {CLS_Gd__gd_core_items__Exclusive__SmellyBarrier, "SmellyBarrier", "res://gd_core_items/Exclusive/SmellyBarrier.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__SmellyBarrier, &Gd__gd_core_items__Exclusive__SmellyBarrier::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SmellyBarrier::call_static_fn};

void Gd__gd_core_items__Exclusive__SpikedCollar::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_spikes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SpikedCollar::meta() const { return &META_Gd__gd_core_items__Exclusive__SpikedCollar; }
gd::GdVal Gd__gd_core_items__Exclusive__SpikedCollar::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SpikedCollar::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SpikedCollar::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SpikedCollar::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SpikedCollar::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onBattleRageStarted_2066: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SpikedCollar::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_2066: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SpikedCollar::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SpikedCollar::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[33]), gd::GdVal::from_str(&battle_string_literals[34])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[32])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_addBattleRageDuration_1290, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpikedCollar::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_spikes, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 2); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpikedCollar::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[94])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SpikedCollar(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__SpikedCollar>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,502u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpikedCollar = {CLS_Gd__gd_core_items__Exclusive__SpikedCollar, "SpikedCollar", "res://gd_core_items/Exclusive/SpikedCollar.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__SpikedCollar, &Gd__gd_core_items__Exclusive__SpikedCollar::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SpikedCollar::call_static_fn};

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
        case SYM_GEN_hasActivated_1906: out = this->f_hasActivated; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        case SYM_GEN_damReduction_1873: out = this->f_damReduction; return true;
        case SYM_GEN_healthThreshold_1854: out = this->f_healthThreshold; return true;
        case SYM_GEN_buffTimer_1819: out = this->f_buffTimer; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__StoneShoes::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hasActivated_1906: this->f_hasActivated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        case SYM_GEN_damReduction_1873: this->f_damReduction = val; return true;
        case SYM_GEN_healthThreshold_1854: this->f_healthThreshold = val; return true;
        case SYM_GEN_buffTimer_1819: this->f_buffTimer = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__StoneShoes::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onDamaged_1855: return true;
        case SYM_GEN_onBuffTimeout_2022: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__StoneShoes::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1855: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN_onBuffTimeout_2022: out = fn_onBuffTimeout(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__StoneShoes::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneShoes::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[95]), gd::GdVal::from_str(&battle_string_literals[96])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneShoes::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(this->f_hasActivated)) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRelativeHealth_302, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), gd::GdVal::from_bool(true), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[97])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, this->f_buffTimer, SYM_GEN_start_1779, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Ranged_2786), gd::gd_neg(this->f_damReduction)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeTypedDamageFactor_1280, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeEffectDamageFactor_1281, _ca, 1); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_381, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneShoes::fn_onBuffTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Ranged_2786), this->f_damReduction}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeTypedDamageFactor_1280, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeEffectDamageFactor_1281, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneShoes::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneShoes::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
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
    return gd::gd_add(gd_ctx, gd::GdVal::from_int(1000LL), gd::GdVal::from_int(3LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneShoes::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_luck = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[52])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_empower = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[98])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_damReduction = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[99])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[100]), gd::GdVal::from_str(&battle_string_literals[101]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__StoneShoes(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__StoneShoes>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,518u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StoneShoes = {CLS_Gd__gd_core_items__Exclusive__StoneShoes, "StoneShoes", "res://gd_core_items/Exclusive/StoneShoes.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__StoneShoes, &Gd__gd_core_items__Exclusive__StoneShoes::get_static_prop_fn, &Gd__gd_core_items__Exclusive__StoneShoes::call_static_fn};

void Gd__gd_core_items__Exclusive__TimePendant::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_cdAdvance = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__TimePendant::meta() const { return &META_Gd__gd_core_items__Exclusive__TimePendant; }
gd::GdVal Gd__gd_core_items__Exclusive__TimePendant::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__TimePendant::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__TimePendant::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_cdAdvance_2080: out = this->f_cdAdvance; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__TimePendant::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_cdAdvance_2080: this->f_cdAdvance = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__TimePendant::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__TimePendant::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__TimePendant::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__TimePendant::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TimePendant::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_428, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isCooldownActive_96, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_cdAdvance}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_advanceCooldownSeconds_147, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TimePendant::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_cdAdvance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[23])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__TimePendant(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__TimePendant>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,534u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__TimePendant = {CLS_Gd__gd_core_items__Exclusive__TimePendant, "TimePendant", "res://gd_core_items/Exclusive/TimePendant.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__TimePendant, &Gd__gd_core_items__Exclusive__TimePendant::get_static_prop_fn, &Gd__gd_core_items__Exclusive__TimePendant::call_static_fn};

void Gd__gd_core_items__Whetstone::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_dam = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Whetstone::meta() const { return &META_Gd__gd_core_items__Whetstone; }
gd::GdVal Gd__gd_core_items__Whetstone::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Whetstone::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Whetstone::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_dam_939: out = this->f_dam; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Whetstone::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_dam_939: this->f_dam = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Whetstone::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Whetstone::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Whetstone::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Whetstone::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Whetstone::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t933 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t934 = (_t933.kind == gd::GdVal::Kind::Arr) ? _t933.arr : nullptr;
        uint32_t _len__t935 = _t934 ? _t934->len : 0u;
        for (uint32_t _t935 = 0; _t935 < _len__t935; ++_t935) {
            gd::GdVal lv_item = _t934->data[_t935];
            (void)([&]() { gd::GdVal _ca[] = {this->f_dam}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Whetstone::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_dam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[51])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Whetstone(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Whetstone>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,661u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Whetstone = {CLS_Gd__gd_core_items__Whetstone, "Whetstone", "res://gd_core_items/Whetstone.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Whetstone, &Gd__gd_core_items__Whetstone::get_static_prop_fn, &Gd__gd_core_items__Whetstone::call_static_fn};

void Gd__gd_core_items__Gems__Emerald::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Gems__Gem::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Gems__Emerald::meta() const { return &META_Gd__gd_core_items__Gems__Emerald; }
gd::GdVal Gd__gd_core_items__Gems__Emerald::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_gemColor_995: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.8), gd::GdVal::from_int(3LL), gd::GdVal::from_float(0.8)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Gems__Emerald::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Gems__Emerald::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_gemColor_995: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Gems__Emerald::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Gems__Emerald::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_prepareWeapon_982: return true;
        case SYM_GEN_onAttack_2052: return true;
        case SYM_GEN_prepareArmor_983: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Gems__Emerald::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_prepareWeapon_982: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_onAttack_2052: out = fn_onAttack(args, argc); return true;
        case SYM_GEN_prepareArmor_983: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Gems__Emerald::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Gems__Emerald::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Emerald::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, this->f_socket, SYM_GEN_getItem_389, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[102]), gd::GdVal::from_str(&battle_string_literals[103])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Emerald::fn_onAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 2); })();
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Emerald::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(108LL), gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeResistChance_1026, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Emerald::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Gems__Emerald(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Gems__Emerald>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,569u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Gems__Emerald = {CLS_Gd__gd_core_items__Gems__Emerald, "Emerald", "res://gd_core_items/Gems/Emerald.gd", &META_Gd__gd_core_items__Gems__Gem, true, _alloc_Gd__gd_core_items__Gems__Emerald, &Gd__gd_core_items__Gems__Emerald::get_static_prop_fn, &Gd__gd_core_items__Gems__Emerald::call_static_fn};

void Gd__gd_core_items__HolyArmor::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__HolyArmor::meta() const { return &META_Gd__gd_core_items__HolyArmor; }
gd::GdVal Gd__gd_core_items__HolyArmor::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__HolyArmor::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__HolyArmor::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__HolyArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__HolyArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__HolyArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__HolyArmor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__HolyArmor::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HolyArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    gd::GdVal lv_numAffected = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numAffected, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_numAffected, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HolyArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleansePoison_342, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HolyArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__HolyArmor(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__HolyArmor>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,589u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__HolyArmor = {CLS_Gd__gd_core_items__HolyArmor, "HolyArmor", "res://gd_core_items/HolyArmor.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__HolyArmor, &Gd__gd_core_items__HolyArmor::get_static_prop_fn, &Gd__gd_core_items__HolyArmor::call_static_fn};

void Gd__gd_core_items__MrStruggles::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_hasActivated = gd::GdVal::from_bool(false);
    this->f_speedbuffTimer = gd::GdVal::null();
    this->f_activationParticles = gd::GdVal::null();
    this->f_healthThreshold = gd::GdVal::null();
    this->f_bonusSpeed = gd::GdVal::null();
    this->f_fatigueDam = gd::GdVal::null();
    this->f_speedBuffParticles1 = gd::GdVal::null();
    this->f_speedBuffParticles2 = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__MrStruggles::meta() const { return &META_Gd__gd_core_items__MrStruggles; }
gd::GdVal Gd__gd_core_items__MrStruggles::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_plushies_1949: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_str(&battle_string_literals[104]), gd::GdVal::from_str(&battle_string_literals[105])}));
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__MrStruggles::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__MrStruggles::get_prop(gd::SymId prop, gd::GdVal& out) const {
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
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__MrStruggles::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
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
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__MrStruggles::has_own_method(gd::SymId m) const {
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
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__MrStruggles::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
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
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__MrStruggles::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t936 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1391, nullptr, 0));
        gd::GdArr* _t937 = (_t936.kind == gd::GdVal::Kind::Arr) ? _t936.arr : nullptr;
        uint32_t _len__t938 = _t937 ? _t937->len : 0u;
        for (uint32_t _t938 = 0; _t938 < _len__t938; ++_t938) {
            gd::GdVal lv_debuff = _t937->data[_t938];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::native_inline_get_prop(gd_ctx, gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_buffs_1048), lv_debuff), SYM_GEN_signalName_1013), gd::GdVal::from_str(&battle_string_literals[106])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[95]), gd::GdVal::from_str(&battle_string_literals[96])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_onDamaged(const gd::GdVal* _args, int _argc) {
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
            gd::GdVal _t939 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
            gd::GdArr* _t940 = (_t939.kind == gd::GdVal::Kind::Arr) ? _t939.arr : nullptr;
            uint32_t _len__t941 = _t940 ? _t940->len : 0u;
            for (uint32_t _t941 = 0; _t941 < _len__t941; ++_t941) {
                gd::GdVal lv_item = _t940->data[_t941];
                (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[107])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, this->f_speedbuffTimer, SYM_GEN_start_1779, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_onSpeedbuffTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    {
        gd::GdVal _t942 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t943 = (_t942.kind == gd::GdVal::Kind::Arr) ? _t942.arr : nullptr;
        uint32_t _len__t944 = _t943 ? _t943->len : 0u;
        for (uint32_t _t944 = 0; _t944 < _len__t944; ++_t944) {
            gd::GdVal lv_item = _t943->data[_t944];
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_reduceSpeed_274, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_onDebuffed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[108]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1673))), gd::gd_coerce_int(this->f_ownerType), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[109]), ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, lv_event, SYM_GEN_type_1005)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[110])), ([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[111])), ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_chanceRng, SYM_GEN_expectedWins_1751)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[6])), ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_chanceRng, SYM_GEN_wins_1752)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[112])), ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_chanceRng, SYM_GEN_lastResult_1754)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(10LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkTriggerCount_142, _ca, 1); })())) {
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
            gd::GdVal lv_debuffType = gd::native_inline_get_prop(gd_ctx, lv_event, SYM_GEN_type_1005);
            gd::GdVal lv_dur = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[113]), gd::gd_neg(gd::GdVal::from_int(1LL))}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getParam_1575, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), lv_debuffType, lv_amount, lv_dur, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacksTemporary_202, _ca, 5); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_fatigueDam}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictFatigueDamage_319, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_speedbuffTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::GdVal::from_int(1000LL), gd::GdVal::from_int(3LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    return gd::GdVal::from_str(&battle_string_literals[64]);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_rollShopChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_shopChance = (_argc > 0) ? _args[0] : (gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_shopChance_1683));
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_getGatedDescriptor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rarity = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {Gd__gd_core_items__MrStruggles::get_static_const_or_enum(gd_ctx, SYM_GEN_plushies_1949)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_pickRandomElement_1746, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_speedBuffActive = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv_speedBuffActive)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speedbuffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[114]), gd::GdVal::from_str(&battle_string_literals[115]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    this->f_bonusSpeed = gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), gd::GdVal::from_float(100.0));
    this->f_fatigueDam = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__MrStruggles(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__MrStruggles>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,607u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__MrStruggles = {CLS_Gd__gd_core_items__MrStruggles, "MrStruggles", "res://gd_core_items/MrStruggles.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__MrStruggles, &Gd__gd_core_items__MrStruggles::get_static_prop_fn, &Gd__gd_core_items__MrStruggles::call_static_fn};

void Gd__gd_core_items__RangerBag::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bag::init_fields(gd_ctx);
    this->f_itemsInside = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__RangerBag::meta() const { return &META_Gd__gd_core_items__RangerBag; }
gd::GdVal Gd__gd_core_items__RangerBag::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__RangerBag::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__RangerBag::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_itemsInside_1970: out = this->f_itemsInside; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__RangerBag::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_itemsInside_1970: this->f_itemsInside = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__RangerBag::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onLuckyChanged_901: return true;
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__RangerBag::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onLuckyChanged_901: out = fn_onLuckyChanged(args, argc); return true;
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__RangerBag::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__RangerBag::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_itemsInside = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0), gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[18]), gd::GdVal::from_str(&battle_string_literals[19])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    }
    {
        gd::GdVal _t945 = gd::gd_iter_seq(gd_ctx.arena, this->f_itemsInside);
        gd::GdArr* _t946 = (_t945.kind == gd::GdVal::Kind::Arr) ? _t945.arr : nullptr;
        uint32_t _len__t947 = _t946 ? _t946->len : 0u;
        for (uint32_t _t947 = 0; _t947 < _len__t947; ++_t947) {
            gd::GdVal lv_item = _t946->data[_t947];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeCritChancePercent_181, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RangerBag::fn_onLuckyChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_change = gd::gd_mul(lv_amount, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0));
    {
        gd::GdVal _t948 = gd::gd_iter_seq(gd_ctx.arena, this->f_itemsInside);
        gd::GdArr* _t949 = (_t948.kind == gd::GdVal::Kind::Arr) ? _t948.arr : nullptr;
        uint32_t _len__t950 = _t949 ? _t949->len : 0u;
        for (uint32_t _t950 = 0; _t950 < _len__t950; ++_t950) {
            gd::GdVal lv_item = _t949->data[_t950];
            (void)([&]() { gd::GdVal _ca[] = {lv_change}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeCritChancePercent_181, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RangerBag::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_toItem, SYM_GEN_canDamage_89, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RangerBag::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__RangerBag(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__RangerBag>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,627u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__RangerBag = {CLS_Gd__gd_core_items__RangerBag, "RangerBag", "res://gd_core_items/RangerBag.gd", &META_Gd__gd_core_items__Bag, true, _alloc_Gd__gd_core_items__RangerBag, &Gd__gd_core_items__RangerBag::get_static_prop_fn, &Gd__gd_core_items__RangerBag::call_static_fn};

void Gd__gd_core_items__TheFool::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Card::init_fields(gd_ctx);
    this->f_activationParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__TheFool::meta() const { return &META_Gd__gd_core_items__TheFool; }
gd::GdVal Gd__gd_core_items__TheFool::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Card::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__TheFool::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__TheFool::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::get_prop(prop, out);
}
bool Gd__gd_core_items__TheFool::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__TheFool::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_890: return true;
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Card::has_own_method(m);
}
bool Gd__gd_core_items__TheFool::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_890: out = fn_cardSecondaryEffectActive(args, argc); return true;
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__TheFool::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__TheFool::fn_cardSecondaryEffectActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::native_scalar_eq(this->f_chainPosition, gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__TheFool::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bonusSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[116])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    {
        gd::GdVal _t951 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, this->f_deck, SYM_GEN_cards_1832));
        gd::GdArr* _t952 = (_t951.kind == gd::GdVal::Kind::Arr) ? _t951.arr : nullptr;
        uint32_t _len__t953 = _t952 ? _t952->len : 0u;
        for (uint32_t _t953 = 0; _t953 < _len__t953; ++_t953) {
            gd::GdVal lv_card = _t952->data[_t953];
            (void)([&]() { gd::GdVal _ca[] = {lv_bonusSpeed}; return gd::native_inline_call(gd_ctx, lv_card, SYM_GEN_addSpeed_273, _ca, 1); })();
        }
    }
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cardSecondaryEffectActive_890, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[98])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__TheFool::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Card::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__TheFool(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__TheFool>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,650u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__TheFool = {CLS_Gd__gd_core_items__TheFool, "TheFool", "res://gd_core_items/TheFool.gd", &META_Gd__gd_core_items__Card, true, _alloc_Gd__gd_core_items__TheFool, &Gd__gd_core_items__TheFool::get_static_prop_fn, &Gd__gd_core_items__TheFool::call_static_fn};
