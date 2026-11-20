#include "../../native_inline_dispatch.hpp"
#include "../../native_scalar_equal.hpp"
#include "../../native_array_index.hpp"
#include "../../native_event_kernel.hpp"
#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core__BagofStones.hpp"
#include "../hdrs/Gd__gd_core__BurningCoal.hpp"
#include "../hdrs/Gd__gd_core__CoreEvent.hpp"
#include "../hdrs/Gd__gd_core__Crossblades.hpp"
#include "../hdrs/Gd__gd_core__Eggscalibur.hpp"
#include "../hdrs/Gd__gd_core__HeartofDarkness.hpp"
#include "../hdrs/Gd__gd_core__LuckyClover.hpp"
#include "../hdrs/Gd__gd_core__Pineapple.hpp"
#include "../hdrs/Gd__gd_core__RubyEgg.hpp"
#include "../hdrs/Gd__gd_core_items__Potion.hpp"
#include "../hdrs/Gd__gd_core__WalrusTusk.hpp"
#include "../hdrs/Gd__gd_core_items__Banana.hpp"
#include "../hdrs/Gd__gd_core_items__ClawsofAttack.hpp"
#include "../hdrs/Gd__gd_core_items__DragonEgg.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__AngelCrystal.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BagofGiving.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BookofLight.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__CatSpirit.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Chess__WhiteKnight.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Cubert.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DraconicOrb.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__EmployeeUniform.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__FlameWhip.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Gigawatz.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Hypercube.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Laboratory.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MagicRing.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MrsStruggles.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PlasticCube.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PuzzlebagZ.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Resistor.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ShepherdsCrook.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SnowStick.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SquirrelArcher.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Thornbloom.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Ultima.hpp"
#include "../hdrs/Gd__gd_core_items__FalconBlade.hpp"
#include "../hdrs/Gd__gd_core_items__GlovesofHaste.hpp"
#include "../hdrs/Gd__gd_core_items__LuckyBow.hpp"
#include "../hdrs/Gd__gd_core_items__PoisonDagger.hpp"
#include "../hdrs/Gd__gd_core_items__StaffofUnhealing.hpp"
#include "../hdrs/Gd__gd_core_items__VampiricScythe.hpp"

namespace {
constexpr gd::GdStr battle_string_literals[] = {
    {"pre_deal_damage_early", 21u, 2143897571u},
    {"preAttack", 9u, 3919347442u},
    {"amount", 6u, 4152741449u},
    {"character_regeneration_changed", 30u, 2797934681u},
    {"onRegenChanged", 14u, 661197895u},
    {"darkspeed", 9u, 2258258432u},
    {"maxhealth", 9u, 429334299u},
    {"empower", 7u, 2037162760u},
    {"healreduction", 13u, 2587190196u},
    {"regent", 6u, 4290639402u},
    {"buffsteal", 9u, 2485862519u},
    {"potion_triggered", 16u, 729283976u},
    {"potion_emptied", 14u, 70999789u},
    {"character_spikes_changed", 24u, 3463900413u},
    {"onSpikesChanged", 15u, 3715123341u},
    {"Dragon Nest", 11u, 2154829316u},
    {"hatch", 5u, 1592057985u},
    {"hatch_deferred", 14u, 1136131817u},
    {"regen", 5u, 16724762u},
    {"regen_holy", 10u, 3071519213u},
    {"empower_holy", 12u, 4093406655u},
    {"activated", 9u, 2866667388u},
    {"onItemInsideActivated", 21u, 2248618218u},
    {"stamina", 7u, 3875003702u},
    {"heal", 4u, 979982427u},
    {"mana", 4u, 3650585354u},
    {"speed", 5u, 2072037248u},
    {"manat", 5u, 126091098u},
    {"luck", 4u, 4145017712u},
    {"onItemActivated1", 16u, 168345585u},
    {"onItemActivated2", 16u, 118012728u},
    {"character_heat_changed", 22u, 2413560104u},
    {"onHeatChanged", 13u, 775078454u},
    {"spikes", 6u, 439106706u},
    {"heat", 4u, 577319571u},
    {"bonusdam", 8u, 3306431450u},
    {"max", 3u, 3617776409u},
    {"damincrease", 11u, 787916641u},
    {"blind", 5u, 274826164u},
    {"replaceWithCubes", 16u, 4131650135u},
    {"dropped", 7u, 3229108261u},
    {"onDropped", 9u, 1334518102u},
    {"luckt", 5u, 4061892428u},
    {"heatt", 5u, 312156581u},
    {"heat_bonus", 10u, 2290038699u},
    {"spikest", 7u, 430169618u},
    {"spikes_bonus", 12u, 2574830266u},
    {"regen_bonus", 11u, 3151769074u},
    {"vampirism", 9u, 773404377u},
    {"vamp_bonus", 10u, 1823058777u},
    {"vampt", 5u, 3195492059u},
    {"empower_bonus", 13u, 3896273556u},
    {"p_", 2u, 1917750800u},
    {"cold", 4u, 3930381583u},
    {"cold2", 5u, 124274439u},
    {"character_empower_changed", 25u, 2356601027u},
    {"onEmpowerChanged", 16u, 1778241301u},
    {"damperspike", 11u, 3296437158u},
    {"$n_nature", 9u, 3887268331u},
    {"", 0u, 2166136261u},
    {"$n_ice", 6u, 1331838383u},
    {"$n_holy", 7u, 2980935886u},
    {"$n_dark", 7u, 3365736372u},
    {"n_nature", 8u, 233140773u},
    {"n_ice", 5u, 2788820689u},
    {"n_holy", 6u, 2117373556u},
    {"n_dark", 6u, 2718798678u},
    {"dur_unhealing", 13u, 3047247524u},
    {"UnhealingTimer", 14u, 2986033917u},
    {"buffEnded", 9u, 3457903416u},
    {"character_vampirism_changed", 27u, 75150398u},
    {"onVampirismChanged", 18u, 3624660862u},
};
}

void Gd__gd_core__BagofStones::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__BagofStones::meta() const { return &META_Gd__gd_core__BagofStones; }
gd::GdVal Gd__gd_core__BagofStones::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__BagofStones::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__BagofStones::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__BagofStones::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__BagofStones::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_getAffectedCellsAfterRotate_primary_410: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__BagofStones::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_getAffectedCellsAfterRotate_primary_410: out = fn_getAffectedCellsAfterRotate_primary(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__BagofStones::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__BagofStones::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasTag_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BagofStones::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1578 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1579 = (_t1578.kind == gd::GdVal::Kind::Arr) ? _t1578.arr : nullptr;
        uint32_t _len__t1580 = _t1579 ? _t1579->len : 0u;
        for (uint32_t _t1580 = 0; _t1580 < _len__t1580; ++_t1580) {
            gd::GdVal lv_item = _t1579->data[_t1580];
            (void)gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_setBagOfStones_905, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BagofStones::fn_getAffectedCellsAfterRotate_primary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rotatedCells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_rotatedCells, gd::GdVal::from_vec2(0.0, -1.0), gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1302), SYM_GEN_INVENTORY_1093), SYM_GEN_getCellsInLine_1611, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BagofStones::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__BagofStones(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__BagofStones>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__BagofStones = {CLS_Gd__gd_core__BagofStones, "BagofStones", "res://gd_core/BagofStones.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__BagofStones, &Gd__gd_core__BagofStones::get_static_prop_fn, &Gd__gd_core__BagofStones::call_static_fn};

void Gd__gd_core__BurningCoal::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Gems__Gem::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__BurningCoal::meta() const { return &META_Gd__gd_core__BurningCoal; }
gd::GdVal Gd__gd_core__BurningCoal::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_gemColor_995: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.5), gd::GdVal::from_int(1LL), gd::GdVal::from_float(0.7)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__BurningCoal::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__BurningCoal::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_gemColor_995: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core__BurningCoal::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__BurningCoal::has_own_method(gd::SymId m) const {
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
bool Gd__gd_core__BurningCoal::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
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
bool Gd__gd_core__BurningCoal::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__BurningCoal::fn_canBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BurningCoal::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, this->f_socket, SYM_GEN_getItem_389, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[0]), gd::GdVal::from_str(&battle_string_literals[1])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BurningCoal::fn_preAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)));
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BurningCoal::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(110LL), gd::gd_round(gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0)))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeResistStacks_1027, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BurningCoal::fn_combatStartArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BurningCoal::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_267, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_356, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BurningCoal::fn_onHotSwapHoverWithGemEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BurningCoal::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__BurningCoal(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__BurningCoal>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__BurningCoal = {CLS_Gd__gd_core__BurningCoal, "BurningCoal", "res://gd_core/BurningCoal.gd", &META_Gd__gd_core_items__Gems__Gem, false, _alloc_Gd__gd_core__BurningCoal, &Gd__gd_core__BurningCoal::get_static_prop_fn, &Gd__gd_core__BurningCoal::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreEvent_Target[] = {{"Player", 0LL}, {"Opponent", 1LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreEvent_Target = {"Target", _ekv_Gd__gd_core__CoreEvent_Target, 2u};
void Gd__gd_core__CoreEvent::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_id = gd::GdVal::from_int(0);
    this->f_timestamp = gd::GdVal::null();
    this->f_parentEvent = gd::GdVal::null();
    this->f_origin = gd::GdVal::null();
    this->f_type = gd::GdVal::null();
    this->f_target = gd::GdVal::null();
    this->f_params = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_formatParams = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
}
const gd::GdClassMeta* Gd__gd_core__CoreEvent::meta() const { return &META_Gd__gd_core__CoreEvent; }
gd::GdVal Gd__gd_core__CoreEvent::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_Target_1583: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreEvent_Target);
        default: break;
    }
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreEvent::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreEvent::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_id_1566: out = this->f_id; return true;
        case SYM_GEN_timestamp_1567: out = this->f_timestamp; return true;
        case SYM_GEN_parentEvent_1568: out = this->f_parentEvent; return true;
        case SYM_GEN_origin_1546: out = this->f_origin; return true;
        case SYM_GEN_type_1005: out = this->f_type; return true;
        case SYM_GEN_target_1569: out = this->f_target; return true;
        case SYM_GEN_params_1570: out = this->f_params; return true;
        case SYM_GEN_formatParams_1571: out = this->f_formatParams; return true;
        case SYM_GEN_Target_1583: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreEvent_Target); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreEvent::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_id_1566: this->f_id = gd::gd_coerce_int(val); return true;
        case SYM_GEN_timestamp_1567: this->f_timestamp = val; return true;
        case SYM_GEN_parentEvent_1568: this->f_parentEvent = val; return true;
        case SYM_GEN_origin_1546: this->f_origin = val; return true;
        case SYM_GEN_type_1005: this->f_type = val; return true;
        case SYM_GEN_target_1569: this->f_target = val; return true;
        case SYM_GEN_params_1570: this->f_params = val; return true;
        case SYM_GEN_formatParams_1571: this->f_formatParams = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreEvent::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_getType_1572: return true;
        case SYM_GEN_setTarget_1573: return true;
        case SYM_GEN_setParam_1574: return true;
        case SYM_GEN_getParam_1575: return true;
        case SYM_GEN_getAmount_1576: return true;
        case SYM_GEN_getAmountWithDefault_1577: return true;
        case SYM_GEN_hasParam_1578: return true;
        case SYM_GEN_getMainActor_1579: return true;
        case SYM_GEN_getOrigin_1580: return true;
        case SYM_GEN_fromCharacter_1581: return true;
        case SYM_GEN_getDepth_1582: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreEvent::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_getType_1572: out = fn_getType(args, argc); return true;
        case SYM_GEN_setTarget_1573: out = fn_setTarget(args, argc); return true;
        case SYM_GEN_setParam_1574: out = fn_setParam(args, argc); return true;
        case SYM_GEN_getParam_1575: out = fn_getParam(args, argc); return true;
        case SYM_GEN_getAmount_1576: out = fn_getAmount(args, argc); return true;
        case SYM_GEN_getAmountWithDefault_1577: out = fn_getAmountWithDefault(args, argc); return true;
        case SYM_GEN_hasParam_1578: out = fn_hasParam(args, argc); return true;
        case SYM_GEN_getMainActor_1579: out = fn_getMainActor(args, argc); return true;
        case SYM_GEN_getOrigin_1580: out = fn_getOrigin(args, argc); return true;
        case SYM_GEN_fromCharacter_1581: out = fn_fromCharacter(args, argc); return true;
        case SYM_GEN_getDepth_1582: out = fn_getDepth(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreEvent::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core__CoreEvent::fn__init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__id = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__timestamp = (_argc > 1) ? _args[1] : (gd::GdVal::from_float(0.0));
    gd::GdVal lv__parentEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv__origin = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv__type = (_argc > 4) ? _args[4] : (gd::GdVal::null());
    this->f_id = gd::gd_coerce_int(lv__id);
    this->f_timestamp = lv__timestamp;
    this->f_parentEvent = lv__parentEvent;
    this->f_origin = lv__origin;
    this->f_type = lv__type;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_getType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_type;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_setTarget(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_target = lv__target;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_setParam(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_paramName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_paramVal = (_argc > 1) ? _args[1] : gd::GdVal::null();
    { gd::GdVal _t1581 = this->f_params; gd::GdVal _t1582 = lv_paramName; gd::native_array_set_index(gd_ctx, _t1581, _t1582, lv_paramVal); }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_getParam(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_paramName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_default = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_paramName, lv_default}; return gd::native_inline_call(gd_ctx, this->f_params, gd::SYM_get, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_getAmount(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_array_index(gd_ctx, this->f_params, gd::GdVal::from_str(&battle_string_literals[2]));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_getAmountWithDefault(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_default = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[2]), lv_default}; return gd::native_inline_call(gd_ctx, this->f_params, gd::SYM_get, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_hasParam(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_param = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::gd_in(lv_param, this->f_params);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_getMainActor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(this->f_origin, &META_Gd__gd_core__CoreItem)))) {
        return gd::get_prop(gd_ctx, gd::native_inline_call(gd_ctx, this->f_origin, SYM_GEN_character_74, nullptr, 0), SYM_GEN_playerId_1046);
    }
    else if (gd::gd_truth(this->f_target)) {
        return this->f_target;
    }
    else {
        return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_ID_1297), SYM_GEN_PLAYER_2637);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_getOrigin(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_origin;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_fromCharacter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(this->f_origin, &META_Gd__gd_core__CoreItem))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, this->f_origin, SYM_GEN_character_74, nullptr, 0), lv_character)))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_getDepth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    if (gd::gd_truth(this->f_parentEvent)) {
        return gd::gd_add(gd_ctx, native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_getDepth>(gd_ctx, this->f_parentEvent, SYM_GEN_getDepth_1582, nullptr, 0), gd::GdVal::from_int(1LL));
    }
    else {
        return gd::GdVal::from_int(0LL);
    }
    return gd::GdVal::null();
    }
    if (gd::gd_truth(this->f_parentEvent)) {
        return gd::gd_add(gd_ctx, gd::native_inline_call(gd_ctx, this->f_parentEvent, SYM_GEN_getDepth_1582, nullptr, 0), gd::GdVal::from_int(1LL));
    }
    else {
        return gd::GdVal::from_int(0LL);
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreEvent(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreEvent>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__CoreEvent = {CLS_Gd__gd_core__CoreEvent, "CoreEvent", "res://gd_core/CoreEvent.gd", nullptr, false, _alloc_Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::get_static_prop_fn, &Gd__gd_core__CoreEvent::call_static_fn};

void Gd__gd_core__Crossblades::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__Crossblades::meta() const { return &META_Gd__gd_core__Crossblades; }
gd::GdVal Gd__gd_core__Crossblades::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Crossblades::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Crossblades::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__Crossblades::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Crossblades::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_getCraftingOffset_850: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Crossblades::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_getCraftingOffset_850: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Crossblades::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Crossblades::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crossblades::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crossblades::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1583 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, _ca, 1); })());
        gd::GdArr* _t1584 = (_t1583.kind == gd::GdVal::Kind::Arr) ? _t1583.arr : nullptr;
        uint32_t _len__t1585 = _t1584 ? _t1584->len : 0u;
        for (uint32_t _t1585 = 0; _t1585 < _len__t1585; ++_t1585) {
            gd::GdVal lv_item = _t1584->data[_t1585];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
        }
    }
    {
        gd::GdVal _t1586 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, _ca, 1); })());
        gd::GdArr* _t1587 = (_t1586.kind == gd::GdVal::Kind::Arr) ? _t1586.arr : nullptr;
        uint32_t _len__t1588 = _t1587 ? _t1587->len : 0u;
        for (uint32_t _t1588 = 0; _t1588 < _len__t1588; ++_t1588) {
            gd::GdVal lv_item = _t1587->data[_t1588];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crossblades::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crossblades::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1589 = lv_forDirection;
        if (gd::native_scalar_eq(_t1589, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::native_scalar_eq(_t1589, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::native_scalar_eq(_t1589, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
        else if (gd::native_scalar_eq(_t1589, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crossblades::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Crossblades(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Crossblades>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Crossblades = {CLS_Gd__gd_core__Crossblades, "Crossblades", "res://gd_core/Crossblades.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__Crossblades, &Gd__gd_core__Crossblades::get_static_prop_fn, &Gd__gd_core__Crossblades::call_static_fn};

void Gd__gd_core__Eggscalibur::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Pan::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__Eggscalibur::meta() const { return &META_Gd__gd_core__Eggscalibur; }
gd::GdVal Gd__gd_core__Eggscalibur::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Pan::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Eggscalibur::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Eggscalibur::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Pan::get_prop(prop, out);
}
bool Gd__gd_core__Eggscalibur::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Pan::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Eggscalibur::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Pan::has_own_method(m);
}
bool Gd__gd_core__Eggscalibur::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Pan::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Eggscalibur::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Pan::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Eggscalibur::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_333, _ca, 2); })();
    if (gd::gd_truth(lv_event)) {
        gd::GdVal lv_affected = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0);
        (void)gd::native_inline_call(gd_ctx, lv_affected, gd::SYM_shuffle, nullptr, 0);
        {
            gd::GdVal _t1590 = gd::gd_iter_seq(gd_ctx.arena, lv_affected);
            gd::GdArr* _t1591 = (_t1590.kind == gd::GdVal::Kind::Arr) ? _t1590.arr : nullptr;
            uint32_t _len__t1592 = _t1591 ? _t1591->len : 0u;
            for (uint32_t _t1592 = 0; _t1592 < _len__t1592; ++_t1592) {
                gd::GdVal lv_food = _t1591->data[_t1592];
                (void)gd::native_inline_call(gd_ctx, lv_food, SYM_GEN_doCooldownEffect_144, nullptr, 0);
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Eggscalibur::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Pan::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Eggscalibur(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Eggscalibur>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Eggscalibur = {CLS_Gd__gd_core__Eggscalibur, "Eggscalibur", "res://gd_core/Eggscalibur.gd", &META_Gd__gd_core_items__Pan, false, _alloc_Gd__gd_core__Eggscalibur, &Gd__gd_core__Eggscalibur::get_static_prop_fn, &Gd__gd_core__Eggscalibur::call_static_fn};

void Gd__gd_core__HeartofDarkness::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_activated = gd::GdVal::from_bool(false);
    this->f_regenNeeded = gd::GdVal::null();
    this->f_numStealedBuffs = gd::GdVal::null();
    this->f_fillAnimation = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__HeartofDarkness::meta() const { return &META_Gd__gd_core__HeartofDarkness; }
gd::GdVal Gd__gd_core__HeartofDarkness::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__HeartofDarkness::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__HeartofDarkness::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activated_1314: out = this->f_activated; return true;
        case SYM_GEN_regenNeeded_942: out = this->f_regenNeeded; return true;
        case SYM_GEN_numStealedBuffs_1892: out = this->f_numStealedBuffs; return true;
        case SYM_GEN_fillAnimation_1890: out = this->f_fillAnimation; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__HeartofDarkness::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1314: this->f_activated = val; return true;
        case SYM_GEN_regenNeeded_942: this->f_regenNeeded = val; return true;
        case SYM_GEN_numStealedBuffs_1892: this->f_numStealedBuffs = val; return true;
        case SYM_GEN_fillAnimation_1890: this->f_fillAnimation = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__HeartofDarkness::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onRegenChanged_1891: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__HeartofDarkness::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onRegenChanged_1891: out = fn_onRegenChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__HeartofDarkness::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__HeartofDarkness::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(25LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartofDarkness::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[3]), gd::GdVal::from_str(&battle_string_literals[4])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[5])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartofDarkness::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_numStealedBuffs, gd::GdVal::null(), gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0), gd::GdVal::from_int(102LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_373, _ca, 4); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartofDarkness::fn_onRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRegeneration_1233, nullptr, 0), this->f_regenNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_regenNeeded, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_346, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[8])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_reduceHealingEfficiency_1183, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartofDarkness::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartofDarkness::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(1000LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartofDarkness::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core__HeartofDarkness::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_regenNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[9])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_numStealedBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[10])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__HeartofDarkness(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__HeartofDarkness>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__HeartofDarkness = {CLS_Gd__gd_core__HeartofDarkness, "HeartofDarkness", "res://gd_core/HeartofDarkness.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__HeartofDarkness, &Gd__gd_core__HeartofDarkness::get_static_prop_fn, &Gd__gd_core__HeartofDarkness::call_static_fn};

void Gd__gd_core__LuckyClover::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__LuckyClover::meta() const { return &META_Gd__gd_core__LuckyClover; }
gd::GdVal Gd__gd_core__LuckyClover::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__LuckyClover::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__LuckyClover::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__LuckyClover::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__LuckyClover::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__LuckyClover::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__LuckyClover::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__LuckyClover::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_381, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyClover::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__LuckyClover(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__LuckyClover>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__LuckyClover = {CLS_Gd__gd_core__LuckyClover, "LuckyClover", "res://gd_core/LuckyClover.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__LuckyClover, &Gd__gd_core__LuckyClover::get_static_prop_fn, &Gd__gd_core__LuckyClover::call_static_fn};

void Gd__gd_core__Pineapple::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Food::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__Pineapple::meta() const { return &META_Gd__gd_core__Pineapple; }
gd::GdVal Gd__gd_core__Pineapple::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Pineapple::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Pineapple::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Food::get_prop(prop, out);
}
bool Gd__gd_core__Pineapple::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Pineapple::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Food::has_own_method(m);
}
bool Gd__gd_core__Pineapple::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Pineapple::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Pineapple::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Pineapple::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Pineapple(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Pineapple>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Pineapple = {CLS_Gd__gd_core__Pineapple, "Pineapple", "res://gd_core/Pineapple.gd", &META_Gd__gd_core__Food, false, _alloc_Gd__gd_core__Pineapple, &Gd__gd_core__Pineapple::get_static_prop_fn, &Gd__gd_core__Pineapple::call_static_fn};

void Gd__gd_core__RubyEgg::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__DragonEgg::init_fields(gd_ctx);
    this->f_reflects = gd::GdVal::null();
    this->f_heat = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__RubyEgg::meta() const { return &META_Gd__gd_core__RubyEgg; }
gd::GdVal Gd__gd_core__RubyEgg::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__DragonEgg::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__RubyEgg::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__RubyEgg::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_reflects_1976: out = this->f_reflects; return true;
        case SYM_GEN_heat_1896: out = this->f_heat; return true;
        default: break;
    }
    return Gd__gd_core__DragonEgg::get_prop(prop, out);
}
bool Gd__gd_core__RubyEgg::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_reflects_1976: this->f_reflects = val; return true;
        case SYM_GEN_heat_1896: this->f_heat = val; return true;
        default: break;
    }
    return Gd__gd_core__DragonEgg::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__RubyEgg::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreCombatStart_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__DragonEgg::has_own_method(m);
}
bool Gd__gd_core__RubyEgg::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreCombatStart_125: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__DragonEgg::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__RubyEgg::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__DragonEgg::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__RubyEgg::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_reflects}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveReflectStacks_200, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RubyEgg::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCooldownEffect_144, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RubyEgg::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_withReflectStacks = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    lv_withReflectStacks = gd::gd_coerce_bool(lv_withReflectStacks);
    if (gd::gd_truth(lv_withReflectStacks)) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_reflects}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveReflectStacks_200, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RubyEgg::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__DragonEgg::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_reflects = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    this->f_heat = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__RubyEgg(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__RubyEgg>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__RubyEgg = {CLS_Gd__gd_core__RubyEgg, "RubyEgg", "res://gd_core/RubyEgg.gd", &META_Gd__gd_core__DragonEgg, false, _alloc_Gd__gd_core__RubyEgg, &Gd__gd_core__RubyEgg::get_static_prop_fn, &Gd__gd_core__RubyEgg::call_static_fn};

void Gd__gd_core_items__Potion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
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
const gd::GdClassMeta* Gd__gd_core_items__Potion::meta() const { return &META_Gd__gd_core_items__Potion; }
gd::GdVal Gd__gd_core_items__Potion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Potion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Potion::get_prop(gd::SymId prop, gd::GdVal& out) const {
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
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Potion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
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
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Potion::has_own_method(gd::SymId m) const {
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
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Potion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
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
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Potion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Potion::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_prepare_122, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(11LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_isEmpty(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(!gd::gd_truth(this->f_isFull));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_fill(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_isFull = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_empty(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_isFull = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_drink(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_consumePotion(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Potion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_triggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onTriggerPotion_1849, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_778, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[11]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_obj(this)}))}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Potion::fn_activate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_playCombatAni = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_consume = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    gd::GdVal lv_animationOverride = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_emitSignal = (_argc > 4) ? _args[4] : (gd::GdVal::from_bool(true));
    lv_emitSignal = gd::gd_coerce_bool(lv_emitSignal);
    (void)([&]() { gd::GdVal _ca[] = {lv_damageRes, lv_playCombatAni, lv_consume, gd::GdVal::null()}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_activate_150, _ca, 4, _out); return _out; })();
    if (gd::gd_truth(lv_emitSignal)) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[12]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_obj(this)}))}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_shopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craft = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_craft = gd::gd_coerce_bool(lv_craft);
    (void)([&]() { gd::GdVal _ca[] = {lv_craft}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_shopEntered_745, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_isFull)))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_fill, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_getAffectedCellsAfterRotate_primary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rotatedCells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_faceDirection, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))))) {
        return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, lv_rotatedCells, gd::GdVal::from_int(1LL)), gd::GdVal::from_vec2(0.0, -1.0))}));
    }
    else {
        return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, lv_rotatedCells, gd::GdVal::from_int(0LL)), gd::GdVal::from_vec2(0.0, -1.0))}));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_addToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__inventory = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__occupiedCells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__placedByPlayer = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv__placedByPlayer = gd::gd_coerce_bool(lv__placedByPlayer);
    (void)([&]() { gd::GdVal _ca[] = {lv__inventory, lv__occupiedCells, lv__placedByPlayer}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_addToInventory_120, _ca, 3, _out); return _out; })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateConnector_1851, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetGradient_1852, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_onFusingAsIngredient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetGradient_1852, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_onAffectedItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_color, gd::GdVal::from_int(0LL))))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateConnector_1851, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_onAffectedItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_color, gd::GdVal::from_int(0LL))))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateConnector_1851, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_updateConnector(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_resetGradient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_discard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_discardGems = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    if (gd::gd_truth(this->f_pooled)) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetGradient_1852, nullptr, 0);
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_discardGems}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_discard_764, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_getStarPosition(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Potion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Potion>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Potion = {CLS_Gd__gd_core_items__Potion, "Potion", "res://gd_core_items/Potion.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Potion, &Gd__gd_core_items__Potion::get_static_prop_fn, &Gd__gd_core_items__Potion::call_static_fn};

void Gd__gd_core__WalrusTusk::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__WalrusTusk::meta() const { return &META_Gd__gd_core__WalrusTusk; }
gd::GdVal Gd__gd_core__WalrusTusk::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__WalrusTusk::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__WalrusTusk::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__WalrusTusk::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__WalrusTusk::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__WalrusTusk::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__WalrusTusk::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__WalrusTusk::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_381, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__WalrusTusk::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__WalrusTusk(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__WalrusTusk>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__WalrusTusk = {CLS_Gd__gd_core__WalrusTusk, "WalrusTusk", "res://gd_core/WalrusTusk.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__WalrusTusk, &Gd__gd_core__WalrusTusk::get_static_prop_fn, &Gd__gd_core__WalrusTusk::call_static_fn};

void Gd__gd_core_items__Banana::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Banana::meta() const { return &META_Gd__gd_core_items__Banana; }
gd::GdVal Gd__gd_core_items__Banana::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Banana::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Banana::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Banana::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Banana::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Banana::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Banana::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Banana::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_318, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Banana::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Banana(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Banana>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Banana = {CLS_Gd__gd_core_items__Banana, "Banana", "res://gd_core_items/Banana.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Banana, &Gd__gd_core_items__Banana::get_static_prop_fn, &Gd__gd_core_items__Banana::call_static_fn};

void Gd__gd_core_items__ClawsofAttack::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_attackCounter = gd::GdVal::from_int(0LL);
    this->f_lastSpeedBonus = gd::GdVal::from_float(0.0);
    this->f_speedPerSpike = gd::GdVal::null();
    this->f_numHits = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__ClawsofAttack::meta() const { return &META_Gd__gd_core_items__ClawsofAttack; }
gd::GdVal Gd__gd_core_items__ClawsofAttack::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__ClawsofAttack::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__ClawsofAttack::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_attackCounter_1001: out = this->f_attackCounter; return true;
        case SYM_GEN_lastSpeedBonus_1002: out = this->f_lastSpeedBonus; return true;
        case SYM_GEN_speedPerSpike_1003: out = this->f_speedPerSpike; return true;
        case SYM_GEN_numHits_1004: out = this->f_numHits; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__ClawsofAttack::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_attackCounter_1001: this->f_attackCounter = val; return true;
        case SYM_GEN_lastSpeedBonus_1002: this->f_lastSpeedBonus = val; return true;
        case SYM_GEN_speedPerSpike_1003: this->f_speedPerSpike = val; return true;
        case SYM_GEN_numHits_1004: this->f_numHits = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__ClawsofAttack::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onSpikesChanged_944: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__ClawsofAttack::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onSpikesChanged_944: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__ClawsofAttack::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__ClawsofAttack::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[13]), gd::GdVal::from_str(&battle_string_literals[14])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ClawsofAttack::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_clawsBonus = gd::gd_min(gd::gd_mul(this->f_speedPerSpike, gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getSpikes_1223, nullptr, 0)), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    lv_clawsBonus = gd::gd_div(gd_ctx, lv_clawsBonus, gd::GdVal::from_float(100.0));
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(lv_clawsBonus, this->f_lastSpeedBonus)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    this->f_lastSpeedBonus = lv_clawsBonus;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ClawsofAttack::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        this->f_attackCounter = gd::gd_add(gd_ctx, this->f_attackCounter, gd::GdVal::from_int(1LL));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_attackCounter, this->f_numHits)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
            this->f_attackCounter = gd::GdVal::from_int(0LL);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ClawsofAttack::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_lastSpeedBonus = gd::GdVal::from_float(0.0);
    this->f_attackCounter = gd::GdVal::from_int(0LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ClawsofAttack::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speedPerSpike = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0);
    this->f_numHits = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__ClawsofAttack(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__ClawsofAttack>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__ClawsofAttack = {CLS_Gd__gd_core_items__ClawsofAttack, "ClawsofAttack", "res://gd_core_items/ClawsofAttack.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__ClawsofAttack, &Gd__gd_core_items__ClawsofAttack::get_static_prop_fn, &Gd__gd_core_items__ClawsofAttack::call_static_fn};

void Gd__gd_core_items__DragonEgg::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_hatchParticles = gd::GdVal::null();
    this->f_firePulse = gd::GdVal::null();
    this->f_whelpName = gd::GdVal::null();
    this->f_roundsToHatch = gd::GdVal::null();
    this->f_reflectionStacks = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__DragonEgg::meta() const { return &META_Gd__gd_core_items__DragonEgg; }
gd::GdVal Gd__gd_core_items__DragonEgg::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__DragonEgg::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__DragonEgg::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_hatchParticles_1860: out = this->f_hatchParticles; return true;
        case SYM_GEN_firePulse_1861: out = this->f_firePulse; return true;
        case SYM_GEN_whelpName_1862: out = this->f_whelpName; return true;
        case SYM_GEN_roundsToHatch_1863: out = this->f_roundsToHatch; return true;
        case SYM_GEN_reflectionStacks_1864: out = this->f_reflectionStacks; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__DragonEgg::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hatchParticles_1860: this->f_hatchParticles = val; return true;
        case SYM_GEN_firePulse_1861: this->f_firePulse = val; return true;
        case SYM_GEN_whelpName_1862: this->f_whelpName = val; return true;
        case SYM_GEN_roundsToHatch_1863: this->f_roundsToHatch = val; return true;
        case SYM_GEN_reflectionStacks_1864: this->f_reflectionStacks = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__DragonEgg::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_updateEgg_1865: return true;
        case SYM_GEN_isNextToNest_1866: return true;
        case SYM_GEN_readyToTransform_753: return true;
        case SYM_GEN_canHatch_1867: return true;
        case SYM_GEN_shopEntered_745: return true;
        case SYM_GEN_startHatching_1868: return true;
        case SYM_GEN_hatch_1869: return true;
        case SYM_GEN_hatch_deferred_1870: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__DragonEgg::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_updateEgg_1865: out = fn_updateEgg(args, argc); return true;
        case SYM_GEN_isNextToNest_1866: out = fn_isNextToNest(args, argc); return true;
        case SYM_GEN_readyToTransform_753: out = fn_readyToTransform(args, argc); return true;
        case SYM_GEN_canHatch_1867: out = fn_canHatch(args, argc); return true;
        case SYM_GEN_shopEntered_745: out = fn_shopEntered(args, argc); return true;
        case SYM_GEN_startHatching_1868: out = fn_startHatching(args, argc); return true;
        case SYM_GEN_hatch_1869: out = fn_hatch(args, argc); return true;
        case SYM_GEN_hatch_deferred_1870: out = fn_hatch_deferred(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__DragonEgg::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_roundsToHatch;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_roundsToHatch = lv_data;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateEgg_1865, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_updateEgg(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canHatch_1867, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.0), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 2); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(gd::GdVal::from_float(1.0), gd::gd_div(gd_ctx, this->f_roundsToHatch, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0))), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_isNextToNest(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_placed)) {
        {
            gd::GdVal _t1593 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
            gd::GdArr* _t1594 = (_t1593.kind == gd::GdVal::Kind::Arr) ? _t1593.arr : nullptr;
            uint32_t _len__t1595 = _t1594 ? _t1594->len : 0u;
            for (uint32_t _t1595 = 0; _t1595 < _len__t1595; ++_t1595) {
                gd::GdVal lv_item = _t1594->data[_t1595];
                if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getName_234, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[15]))))) {
                    return gd::gd_in(gd::GdVal::from_obj(this), gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getAffectedItems_420, nullptr, 0));
                }
            }
        }
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_readyToTransform(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canHatch_1867, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_canHatch(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_roundsToHatch, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_roundsToHatch, gd::GdVal::from_int(1LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isNextToNest_1866, nullptr, 0))) : gd::GdVal::from_bool(false)))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_shopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craft = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_craft = gd::gd_coerce_bool(lv_craft);
    (void)([&]() { gd::GdVal _ca[] = {lv_craft}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_shopEntered_745, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_startHatching(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[16]), gd::gd_sub(Gd__gd_core_items__DragonEgg::get_static_const_or_enum(gd_ctx, SYM_GEN_TRANSFORMATION_DUR_606), gd::GdVal::from_float(0.1))}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_callDelayed_1479, _ca, 3); })();
    {
        gd::GdVal _t1596 = gd::gd_iter_seq(gd_ctx.arena, this->f_shadows);
        gd::GdArr* _t1597 = (_t1596.kind == gd::GdVal::Kind::Arr) ? _t1596.arr : nullptr;
        uint32_t _len__t1598 = _t1597 ? _t1597->len : 0u;
        for (uint32_t _t1598 = 0; _t1598 < _len__t1598; ++_t1598) {
            gd::GdVal lv_shadow = _t1597->data[_t1598];
            gd::set_prop(gd_ctx, lv_shadow, SYM_GEN_offset_516, gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(138LL))).as_float()));
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_hatch(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[17]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_defer_1482, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_hatch_deferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_roundsToHatch = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateEgg_1865, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__DragonEgg(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__DragonEgg>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__DragonEgg = {CLS_Gd__gd_core_items__DragonEgg, "DragonEgg", "res://gd_core_items/DragonEgg.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__DragonEgg, &Gd__gd_core_items__DragonEgg::get_static_prop_fn, &Gd__gd_core_items__DragonEgg::call_static_fn};

void Gd__gd_core_items__Exclusive__AngelCrystal::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_regen = gd::GdVal::null();
    this->f_regenPerHoly = gd::GdVal::null();
    this->f_empower = gd::GdVal::null();
    this->f_empowerPerHoly = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__AngelCrystal::meta() const { return &META_Gd__gd_core_items__Exclusive__AngelCrystal; }
gd::GdVal Gd__gd_core_items__Exclusive__AngelCrystal::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__AngelCrystal::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__AngelCrystal::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        case SYM_GEN_regenPerHoly_2036: out = this->f_regenPerHoly; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        case SYM_GEN_empowerPerHoly_2037: out = this->f_empowerPerHoly; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__AngelCrystal::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        case SYM_GEN_regenPerHoly_2036: this->f_regenPerHoly = val; return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        case SYM_GEN_empowerPerHoly_2037: this->f_empowerPerHoly = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__AngelCrystal::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onRegenChanged_1891: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AngelCrystal::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onRegenChanged_1891: out = fn_onRegenChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__AngelCrystal::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__AngelCrystal::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AngelCrystal::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[3]), gd::GdVal::from_str(&battle_string_literals[4])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AngelCrystal::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_regen, gd::gd_mul(this->f_regenPerHoly, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0)))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AngelCrystal::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_empower, gd::gd_mul(this->f_empowerPerHoly, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0)))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AngelCrystal::fn_onRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), lv_amount), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, _ca, 2); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AngelCrystal::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[18])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regenPerHoly = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[19])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_empowerPerHoly = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[20])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__AngelCrystal(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__AngelCrystal>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AngelCrystal = {CLS_Gd__gd_core_items__Exclusive__AngelCrystal, "AngelCrystal", "res://gd_core_items/Exclusive/AngelCrystal.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__AngelCrystal, &Gd__gd_core_items__Exclusive__AngelCrystal::get_static_prop_fn, &Gd__gd_core_items__Exclusive__AngelCrystal::call_static_fn};

void Gd__gd_core_items__Exclusive__BagofGiving::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bag::init_fields(gd_ctx);
    this->f_activationParticles = gd::GdVal::null();
    this->f_maxStamina = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__BagofGiving::meta() const { return &META_Gd__gd_core_items__Exclusive__BagofGiving; }
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__BagofGiving::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__BagofGiving::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_maxStamina_1054: out = this->f_maxStamina; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BagofGiving::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_maxStamina_1054: this->f_maxStamina = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BagofGiving::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onItemInsideActivated_2053: return true;
        case SYM_GEN_onAddToInventory_419: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_getShopPriority_853: return true;
        case SYM_GEN_getRelatedItems_459: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN_getRelatedItemHeight_700: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BagofGiving::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemInsideActivated_2053: out = fn_onItemInsideActivated(args, argc); return true;
        case SYM_GEN_onAddToInventory_419: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_getShopPriority_853: out = fn_getShopPriority(args, argc); return true;
        case SYM_GEN_getRelatedItems_459: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_700: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BagofGiving::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_toItem, SYM_GEN_isClassItem_248, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1599 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_927, nullptr, 0));
        gd::GdArr* _t1600 = (_t1599.kind == gd::GdVal::Kind::Arr) ? _t1599.arr : nullptr;
        uint32_t _len__t1601 = _t1600 ? _t1600->len : 0u;
        for (uint32_t _t1601 = 0; _t1601 < _len__t1601; ++_t1601) {
            gd::GdVal lv_item = _t1600->data[_t1601];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[21]), gd::GdVal::from_str(&battle_string_literals[22])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_onItemInsideActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_maxStamina, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxStaminaTemporary_316, _ca, 2); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN_onRemoveFromInventory_418, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_getShopPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(-1000LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_getRelatedItemColumns(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(6LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_getRelatedItemHeight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(110LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_maxStamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[23])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BagofGiving(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__BagofGiving>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BagofGiving = {CLS_Gd__gd_core_items__Exclusive__BagofGiving, "BagofGiving", "res://gd_core_items/Exclusive/BagofGiving.gd", &META_Gd__gd_core_items__Bag, true, _alloc_Gd__gd_core_items__Exclusive__BagofGiving, &Gd__gd_core_items__Exclusive__BagofGiving::get_static_prop_fn, &Gd__gd_core_items__Exclusive__BagofGiving::call_static_fn};

void Gd__gd_core_items__Exclusive__BookofLight::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_manaNeeded = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
    this->f_spellSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__BookofLight::meta() const { return &META_Gd__gd_core_items__Exclusive__BookofLight; }
gd::GdVal Gd__gd_core_items__Exclusive__BookofLight::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__BookofLight::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__BookofLight::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_manaNeeded_1881: out = this->f_manaNeeded; return true;
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        case SYM_GEN_spellSpeed_2094: out = this->f_spellSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BookofLight::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaNeeded_1881: this->f_manaNeeded = val; return true;
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        case SYM_GEN_spellSpeed_2094: this->f_spellSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BookofLight::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BookofLight::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BookofLight::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofLight::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(18LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofLight::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_speed = gd::GdVal::from_float(0.0);
    {
        gd::GdVal _t1602 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1603 = (_t1602.kind == gd::GdVal::Kind::Arr) ? _t1602.arr : nullptr;
        uint32_t _len__t1604 = _t1603 ? _t1603->len : 0u;
        for (uint32_t _t1604 = 0; _t1604 < _len__t1604; ++_t1604) {
            gd::GdVal lv_item = _t1603->data[_t1604];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
                lv_speed = gd::gd_add(gd_ctx, lv_speed, gd::gd_mul(this->f_spellSpeed, gd::GdVal::from_int(2LL)));
            }
            else {
                lv_speed = gd::gd_add(gd_ctx, lv_speed, this->f_spellSpeed);
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_speed}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofLight::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_manaNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[24])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 2); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofLight::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[25])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[18])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_spellSpeed = gd::gd_div(gd_ctx, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[26])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BookofLight(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__BookofLight>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BookofLight = {CLS_Gd__gd_core_items__Exclusive__BookofLight, "BookofLight", "res://gd_core_items/Exclusive/BookofLight.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__BookofLight, &Gd__gd_core_items__Exclusive__BookofLight::get_static_prop_fn, &Gd__gd_core_items__Exclusive__BookofLight::call_static_fn};

void Gd__gd_core_items__Exclusive__CatSpirit::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__SpiritCompanion::init_fields(gd_ctx);
    this->f_manaNeeded = gd::GdVal::null();
    this->f_luck = gd::GdVal::null();
    this->f_empower = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__CatSpirit::meta() const { return &META_Gd__gd_core_items__Exclusive__CatSpirit; }
gd::GdVal Gd__gd_core_items__Exclusive__CatSpirit::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__SpiritCompanion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__CatSpirit::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__CatSpirit::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_manaNeeded_1881: out = this->f_manaNeeded; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__CatSpirit::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaNeeded_1881: this->f_manaNeeded = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__CatSpirit::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_149: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__CatSpirit::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_149: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__CatSpirit::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__SpiritCompanion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__CatSpirit::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canDamage_89, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CatSpirit::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1605 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1606 = (_t1605.kind == gd::GdVal::Kind::Arr) ? _t1605.arr : nullptr;
        uint32_t _len__t1607 = _t1606 ? _t1606->len : 0u;
        for (uint32_t _t1607 = 0; _t1607 < _len__t1607; ++_t1607) {
            gd::GdVal lv_item = _t1606->data[_t1607];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addCritChancePercent_179, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CatSpirit::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_manaNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_empower, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 2); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CatSpirit::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CatSpirit::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CatSpirit::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__SpiritCompanion::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[27])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[28])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__CatSpirit(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__CatSpirit>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__CatSpirit = {CLS_Gd__gd_core_items__Exclusive__CatSpirit, "CatSpirit", "res://gd_core_items/Exclusive/CatSpirit.gd", &META_Gd__gd_core_items__Exclusive__SpiritCompanion, true, _alloc_Gd__gd_core_items__Exclusive__CatSpirit, &Gd__gd_core_items__Exclusive__CatSpirit::get_static_prop_fn, &Gd__gd_core_items__Exclusive__CatSpirit::call_static_fn};

void Gd__gd_core_items__Exclusive__Chess__WhiteKnight::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Chess__ChessPiece::init_fields(gd_ctx);
    this->f_boardSpeed = gd::GdVal::null();
    this->f_stamina = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Chess__WhiteKnight::meta() const { return &META_Gd__gd_core_items__Exclusive__Chess__WhiteKnight; }
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteKnight::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteKnight::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteKnight::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_boardSpeed_2159: out = this->f_boardSpeed; return true;
        case SYM_GEN_stamina_2156: out = this->f_stamina; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteKnight::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_boardSpeed_2159: this->f_boardSpeed = val; return true;
        case SYM_GEN_stamina_2156: this->f_stamina = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteKnight::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2146: return true;
        case SYM_GEN_doEliminatedEffect_2148: return true;
        case SYM_GEN_canBeBlocked_1558: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteKnight::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2146: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_doEliminatedEffect_2148: out = fn_doEliminatedEffect(args, argc); return true;
        case SYM_GEN_canBeBlocked_1558: out = fn_canBeBlocked(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteKnight::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteKnight::fn_doCapturingEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__eliminatedPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_boardSpeed}; return gd::native_inline_call(gd_ctx, this->f_board, SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteKnight::fn_doEliminatedEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_stamina}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxStaminaTemporary_316, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteKnight::fn_canBeBlocked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteKnight::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_boardSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[26])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[23])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Chess__WhiteKnight(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Chess__WhiteKnight>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__WhiteKnight = {CLS_Gd__gd_core_items__Exclusive__Chess__WhiteKnight, "WhiteKnight", "res://gd_core_items/Exclusive/Chess/WhiteKnight.gd", &META_Gd__gd_core_items__Exclusive__Chess__ChessPiece, true, _alloc_Gd__gd_core_items__Exclusive__Chess__WhiteKnight, &Gd__gd_core_items__Exclusive__Chess__WhiteKnight::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Chess__WhiteKnight::call_static_fn};

void Gd__gd_core_items__Exclusive__Cubert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_goobertAnimation = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
    this->f_regenNeeded = gd::GdVal::null();
    this->f_empower = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Cubert::meta() const { return &META_Gd__gd_core_items__Exclusive__Cubert; }
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Cubert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Cubert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_goobertAnimation_936: out = this->f_goobertAnimation; return true;
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        case SYM_GEN_regenNeeded_942: out = this->f_regenNeeded; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Cubert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_goobertAnimation_936: this->f_goobertAnimation = val; return true;
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        case SYM_GEN_regenNeeded_942: this->f_regenNeeded = val; return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Cubert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onItemActivated1_2185: return true;
        case SYM_GEN_onItemActivated2_2186: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Cubert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemActivated1_2185: out = fn_onItemActivated1(args, argc); return true;
        case SYM_GEN_onItemActivated2_2186: out = fn_onItemActivated2(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Cubert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canActivate_91, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canActivate_91, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1608 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1609 = (_t1608.kind == gd::GdVal::Kind::Arr) ? _t1608.arr : nullptr;
        uint32_t _len__t1610 = _t1609 ? _t1609->len : 0u;
        for (uint32_t _t1610 = 0; _t1610 < _len__t1610; ++_t1610) {
            gd::GdVal lv_item = _t1609->data[_t1610];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[21]), gd::GdVal::from_str(&battle_string_literals[29])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    {
        gd::GdVal _t1611 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, _ca, 1); })());
        gd::GdArr* _t1612 = (_t1611.kind == gd::GdVal::Kind::Arr) ? _t1611.arr : nullptr;
        uint32_t _len__t1613 = _t1612 ? _t1612->len : 0u;
        for (uint32_t _t1613 = 0; _t1613 < _len__t1613; ++_t1613) {
            gd::GdVal lv_item = _t1612->data[_t1613];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[21]), gd::GdVal::from_str(&battle_string_literals[30])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::fn_onItemActivated1(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 2); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::fn_onItemActivated2(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRegeneration_1233, nullptr, 0), this->f_regenNeeded)))) {
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance2_174, nullptr, 0))) {
            gd::GdVal lv_event2 = ([&]() { gd::GdVal _ca[] = {this->f_regenNeeded, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_346, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_empower, lv_event2}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 2); })();
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRegeneration_1233, nullptr, 0), this->f_regenNeeded)))) {
        gd::GdVal lv_event2 = ([&]() { gd::GdVal _ca[] = {this->f_regenNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_346, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_empower, lv_event2}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 2); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[18])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regenNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[9])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Cubert(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Cubert>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Cubert = {CLS_Gd__gd_core_items__Exclusive__Cubert, "Cubert", "res://gd_core_items/Exclusive/Cubert.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Cubert, &Gd__gd_core_items__Exclusive__Cubert::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Cubert::call_static_fn};

void Gd__gd_core_items__Exclusive__DraconicOrb::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_counter = gd::GdVal::from_int(0LL);
    this->f_activationParticles = gd::GdVal::null();
    this->f_heatThreshold = gd::GdVal::from_int(0);
    this->f_spikeRemoval = gd::GdVal::from_int(0);
    this->f_heatPerSpike = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__DraconicOrb::meta() const { return &META_Gd__gd_core_items__Exclusive__DraconicOrb; }
gd::GdVal Gd__gd_core_items__Exclusive__DraconicOrb::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__DraconicOrb::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__DraconicOrb::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_counter_2211: out = this->f_counter; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_heatThreshold_1975: out = this->f_heatThreshold; return true;
        case SYM_GEN_spikeRemoval_2212: out = this->f_spikeRemoval; return true;
        case SYM_GEN_heatPerSpike_2213: out = this->f_heatPerSpike; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DraconicOrb::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_counter_2211: this->f_counter = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_heatThreshold_1975: this->f_heatThreshold = gd::gd_coerce_int(val); return true;
        case SYM_GEN_spikeRemoval_2212: this->f_spikeRemoval = gd::gd_coerce_int(val); return true;
        case SYM_GEN_heatPerSpike_2213: this->f_heatPerSpike = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DraconicOrb::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onHeatChanged_913: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DraconicOrb::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onHeatChanged_913: out = fn_onHeatChanged(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DraconicOrb::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DraconicOrb::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_counter = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[31]), gd::GdVal::from_str(&battle_string_literals[32])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DraconicOrb::fn_onHeatChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_counter, this->f_heatThreshold)))) {
        this->f_counter = gd::gd_add(gd_ctx, this->f_counter, lv_amount);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_counter, this->f_heatThreshold)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveCritTokens_314, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DraconicOrb::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_oppoSpikes = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getSpikes_1223, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_oppoSpikes, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_spikeRemoval, gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_loseSpikes_338, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_min(lv_oppoSpikes, this->f_spikeRemoval), this->f_heatPerSpike), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 2); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DraconicOrb::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_heatThreshold = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    this->f_spikeRemoval = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0));
    this->f_heatPerSpike = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DraconicOrb(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__DraconicOrb>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DraconicOrb = {CLS_Gd__gd_core_items__Exclusive__DraconicOrb, "DraconicOrb", "res://gd_core_items/Exclusive/DraconicOrb.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__DraconicOrb, &Gd__gd_core_items__Exclusive__DraconicOrb::get_static_prop_fn, &Gd__gd_core_items__Exclusive__DraconicOrb::call_static_fn};

void Gd__gd_core_items__Exclusive__EmployeeUniform::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__LeatherArmor::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__EmployeeUniform::meta() const { return &META_Gd__gd_core_items__Exclusive__EmployeeUniform; }
gd::GdVal Gd__gd_core_items__Exclusive__EmployeeUniform::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__LeatherArmor::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__EmployeeUniform::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__EmployeeUniform::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__LeatherArmor::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__EmployeeUniform::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__LeatherArmor::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__EmployeeUniform::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCalcTradeChance_1825: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherArmor::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__EmployeeUniform::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCalcTradeChance_1825: out = fn_onCalcTradeChance(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherArmor::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__EmployeeUniform::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__LeatherArmor::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__EmployeeUniform::fn_onCalcTradeChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EmployeeUniform::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherArmor::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__EmployeeUniform(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__EmployeeUniform>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__EmployeeUniform = {CLS_Gd__gd_core_items__Exclusive__EmployeeUniform, "EmployeeUniform", "res://gd_core_items/Exclusive/EmployeeUniform.gd", &META_Gd__gd_core_items__LeatherArmor, true, _alloc_Gd__gd_core_items__Exclusive__EmployeeUniform, &Gd__gd_core_items__Exclusive__EmployeeUniform::get_static_prop_fn, &Gd__gd_core_items__Exclusive__EmployeeUniform::call_static_fn};

void Gd__gd_core_items__Exclusive__FlameWhip::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_spikesNeeded = gd::GdVal::from_int(0);
    this->f_heatGain = gd::GdVal::from_int(0);
    this->f_bonusDamage = gd::GdVal::from_float(0.0);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__FlameWhip::meta() const { return &META_Gd__gd_core_items__Exclusive__FlameWhip; }
gd::GdVal Gd__gd_core_items__Exclusive__FlameWhip::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__FlameWhip::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__FlameWhip::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_spikesNeeded_2110: out = this->f_spikesNeeded; return true;
        case SYM_GEN_heatGain_2261: out = this->f_heatGain; return true;
        case SYM_GEN_bonusDamage_904: out = this->f_bonusDamage; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__FlameWhip::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikesNeeded_2110: this->f_spikesNeeded = gd::gd_coerce_int(val); return true;
        case SYM_GEN_heatGain_2261: this->f_heatGain = gd::gd_coerce_int(val); return true;
        case SYM_GEN_bonusDamage_904: this->f_bonusDamage = gd::gd_coerce_float(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__FlameWhip::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__FlameWhip::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__FlameWhip::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__FlameWhip::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getSpikes_1223, nullptr, 0), this->f_spikesNeeded)))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_spikesNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useSpikes_337, _ca, 1); })();
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), this->f_bonusDamage));
            (void)([&]() { gd::GdVal _ca[] = {this->f_heatGain}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FlameWhip::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_spikesNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[33])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_heatGain = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[34])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_bonusDamage = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[35])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__FlameWhip(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__FlameWhip>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FlameWhip = {CLS_Gd__gd_core_items__Exclusive__FlameWhip, "FlameWhip", "res://gd_core_items/Exclusive/FlameWhip.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__FlameWhip, &Gd__gd_core_items__Exclusive__FlameWhip::get_static_prop_fn, &Gd__gd_core_items__Exclusive__FlameWhip::call_static_fn};

void Gd__gd_core_items__Exclusive__Gigawatz::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_numSpeedboosts = gd::GdVal::from_int(0);
    this->f_curDamageBonus = gd::GdVal::from_int(0);
    this->f_maxNumSpeedBoosts = gd::GdVal::null();
    this->f_speedBonus = gd::GdVal::null();
    this->f_damageBonus = gd::GdVal::null();
    this->f_blind = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Gigawatz::meta() const { return &META_Gd__gd_core_items__Exclusive__Gigawatz; }
gd::GdVal Gd__gd_core_items__Exclusive__Gigawatz::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Gigawatz::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Gigawatz::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_numSpeedboosts_2289: out = this->f_numSpeedboosts; return true;
        case SYM_GEN_curDamageBonus_2290: out = this->f_curDamageBonus; return true;
        case SYM_GEN_maxNumSpeedBoosts_2291: out = this->f_maxNumSpeedBoosts; return true;
        case SYM_GEN_speedBonus_1877: out = this->f_speedBonus; return true;
        case SYM_GEN_damageBonus_2292: out = this->f_damageBonus; return true;
        case SYM_GEN_blind_1911: out = this->f_blind; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Gigawatz::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numSpeedboosts_2289: this->f_numSpeedboosts = gd::gd_coerce_int(val); return true;
        case SYM_GEN_curDamageBonus_2290: this->f_curDamageBonus = gd::gd_coerce_int(val); return true;
        case SYM_GEN_maxNumSpeedBoosts_2291: this->f_maxNumSpeedBoosts = val; return true;
        case SYM_GEN_speedBonus_1877: this->f_speedBonus = val; return true;
        case SYM_GEN_damageBonus_2292: this->f_damageBonus = val; return true;
        case SYM_GEN_blind_1911: this->f_blind = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Gigawatz::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onChargeReceived_2129: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Gigawatz::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onChargeReceived_2129: out = fn_onChargeReceived(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Gigawatz::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Gigawatz::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_curDamageBonus = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_numSpeedboosts = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Gigawatz::fn_onChargeReceived(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_numSpeedboosts, this->f_maxNumSpeedBoosts)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_speedBonus}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
        this->f_numSpeedboosts = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numSpeedboosts, gd::GdVal::from_int(1LL)));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Gigawatz::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_blind}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_213, _ca, 1); })();
    gd::GdVal lv_dam = gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1675), this->f_curDamageBonus);
    gd::GdVal lv_res = ([&]() { gd::GdVal _ca[] = {lv_dam}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealEffectDamage_221, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    this->f_curDamageBonus = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_curDamageBonus, this->f_damageBonus));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Gigawatz::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_maxNumSpeedBoosts = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[36])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_speedBonus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[26])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_damageBonus = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[37])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_blind = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[38])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1550, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Gigawatz(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Gigawatz>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Gigawatz = {CLS_Gd__gd_core_items__Exclusive__Gigawatz, "Gigawatz", "res://gd_core_items/Exclusive/Gigawatz.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Gigawatz, &Gd__gd_core_items__Exclusive__Gigawatz::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Gigawatz::call_static_fn};

void Gd__gd_core_items__Exclusive__Hypercube::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Hypercube::meta() const { return &META_Gd__gd_core_items__Exclusive__Hypercube; }
gd::GdVal Gd__gd_core_items__Exclusive__Hypercube::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Hypercube::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Hypercube::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Hypercube::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Hypercube::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onDropped_2034: return true;
        case SYM_GEN_replaceWithCubes_2312: return true;
        case SYM_GEN_getTextureSize_781: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Hypercube::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDropped_2034: out = fn_onDropped(args, argc); return true;
        case SYM_GEN_replaceWithCubes_2312: out = fn_replaceWithCubes(args, argc); return true;
        case SYM_GEN_getTextureSize_781: out = fn_getTextureSize(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Hypercube::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Hypercube::fn_onDropped(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dropRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_dropRes}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core_items__Exclusive__Hypercube::call_static_fn(gd_ctx, SYM_GEN_wasAddedToInventory_659, _ca, 1, _out); return _out; })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Hypercube::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_AddedToStorageBox_2723)))))))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_prepareReplacement_446, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[39]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_dropRes}))}; return gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_defer_1482, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hypercube::fn_replaceWithCubes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dropResult = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hypercube::fn_getTextureSize(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hypercube::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[40]), gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[41])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_connect, _ca, 3); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Hypercube(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Hypercube>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Hypercube = {CLS_Gd__gd_core_items__Exclusive__Hypercube, "Hypercube", "res://gd_core_items/Exclusive/Hypercube.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Hypercube, &Gd__gd_core_items__Exclusive__Hypercube::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Hypercube::call_static_fn};

void Gd__gd_core_items__Exclusive__Laboratory::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_phase = gd::GdVal::from_int(0);
    this->f_typesDict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_fluidTween = gd::GdVal::null();
    this->f_fluid = gd::GdVal::null();
    this->f_fluidMat = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Laboratory::meta() const { return &META_Gd__gd_core_items__Exclusive__Laboratory; }
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_params_1570: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 15); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[42]), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[43]), gd::GdVal::from_int(4LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[44]), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[34]), gd::GdVal::from_int(4LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[45]), gd::GdVal::from_int(6LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[46]), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[33]), gd::GdVal::from_int(8LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[9]), gd::GdVal::from_int(8LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[47]), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[18]), gd::GdVal::from_int(10LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[48]), gd::GdVal::from_int(12LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[49]), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[50]), gd::GdVal::from_int(10LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[51]), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[7]), gd::GdVal::from_int(14LL)); return gd::GdVal::from_dict(d); })();
        case SYM_GEN_flashColor_2340: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.3), gd::GdVal::from_float(1.3), gd::GdVal::from_float(1.3)}; return gd::make_color_from_args(_ca, 3); })();
        case SYM_GEN_DUR_2341: return gd::GdVal::from_float(0.2);
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Laboratory::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Laboratory::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_phase_2308: out = this->f_phase; return true;
        case SYM_GEN_typesDict_2068: out = this->f_typesDict; return true;
        case SYM_GEN_fluidTween_1839: out = this->f_fluidTween; return true;
        case SYM_GEN_fluid_1841: out = this->f_fluid; return true;
        case SYM_GEN_fluidMat_2342: out = this->f_fluidMat; return true;
        case SYM_GEN_params_1570: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_flashColor_2340: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_DUR_2341: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Laboratory::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_phase_2308: this->f_phase = gd::gd_coerce_int(val); return true;
        case SYM_GEN_typesDict_2068: this->f_typesDict = val; return true;
        case SYM_GEN_fluidTween_1839: this->f_fluidTween = val; return true;
        case SYM_GEN_fluid_1841: this->f_fluid = val; return true;
        case SYM_GEN_fluidMat_2342: this->f_fluidMat = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Laboratory::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_onPreCombatStart_125: return true;
        case SYM_GEN_trigger_143: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN_switchGradient_2343: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Laboratory::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_onPreCombatStart_125: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_trigger_143: out = fn_trigger(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_switchGradient_2343: out = fn_switchGradient(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Laboratory::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_int(1LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_getDescription_642, nullptr, 0);
    {
        gd::GdVal _t1614 = gd::gd_iter_seq(gd_ctx.arena, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570));
        gd::GdArr* _t1615 = (_t1614.kind == gd::GdVal::Kind::Arr) ? _t1614.arr : nullptr;
        uint32_t _len__t1616 = _t1615 ? _t1615->len : 0u;
        for (uint32_t _t1616 = 0; _t1616 < _len__t1616; ++_t1616) {
            gd::GdVal lv_param = _t1615->data[_t1616];
            lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[52]), lv_param}; return gd::gd_str_fn(gd_ctx.arena, _ca, 2); })(), gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570), lv_param), gd::GdVal::from_int(0LL), gd::GdVal::from_bool(false), lv_wrapInColor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
        }
    }
    return ([&]() { gd::GdVal _ca[] = {lv_descr, lv_wrapInColor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameters_643, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    this->f_typesDict = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countTypes_495, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_trigger(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_phase, gd::GdVal::from_int(1LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_trigger_143, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth((gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(27LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(26LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(24LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(6LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isClassItem_248, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_phase, gd::GdVal::from_int(1LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570), gd::GdVal::from_str(&battle_string_literals[42])))))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570), gd::GdVal::from_str(&battle_string_literals[42]))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useLucky_350, _ca, 1); })();
            gd::GdVal lv_numFire = gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(27LL));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570), gd::GdVal::from_str(&battle_string_literals[34])), gd::gd_mul(lv_numFire, gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570), gd::GdVal::from_str(&battle_string_literals[44])))), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 2); })();
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_phase, gd::GdVal::from_int(2LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getHeat_1251, nullptr, 0), gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570), gd::GdVal::from_str(&battle_string_literals[43])))))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570), gd::GdVal::from_str(&battle_string_literals[43]))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useHeat_354, _ca, 1); })();
            gd::GdVal lv_numNature = gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(26LL));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570), gd::GdVal::from_str(&battle_string_literals[33])), gd::gd_mul(lv_numNature, gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570), gd::GdVal::from_str(&battle_string_literals[46])))), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 2); })();
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_phase, gd::GdVal::from_int(3LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getSpikes_1223, nullptr, 0), gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570), gd::GdVal::from_str(&battle_string_literals[45])))))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570), gd::GdVal::from_str(&battle_string_literals[45]))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useSpikes_337, _ca, 1); })();
            gd::GdVal lv_numHoly = gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(22LL));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570), gd::GdVal::from_str(&battle_string_literals[18])), gd::gd_mul(lv_numHoly, gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570), gd::GdVal::from_str(&battle_string_literals[47])))), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 2); })();
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_phase, gd::GdVal::from_int(4LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRegeneration_1233, nullptr, 0), gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570), gd::GdVal::from_str(&battle_string_literals[9])))))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570), gd::GdVal::from_str(&battle_string_literals[9]))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_346, _ca, 1); })();
            gd::GdVal lv_numVamp = gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(24LL));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570), gd::GdVal::from_str(&battle_string_literals[48])), gd::gd_mul(lv_numVamp, gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570), gd::GdVal::from_str(&battle_string_literals[49])))), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 2); })();
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_phase, gd::GdVal::from_int(5LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getVampirism_1226, nullptr, 0), gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570), gd::GdVal::from_str(&battle_string_literals[50])))))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570), gd::GdVal::from_str(&battle_string_literals[50]))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useVampirism_340, _ca, 1); })();
            gd::GdVal lv_numEngineer = gd::GdVal::from_int(0LL);
            {
                gd::GdVal _t1617 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
                gd::GdArr* _t1618 = (_t1617.kind == gd::GdVal::Kind::Arr) ? _t1617.arr : nullptr;
                uint32_t _len__t1619 = _t1618 ? _t1618->len : 0u;
                for (uint32_t _t1619 = 0; _t1619 < _len__t1619; ++_t1619) {
                    gd::GdVal lv_item = _t1618->data[_t1619];
                    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(6LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isClassItem_248, _ca, 1); })())) {
                        lv_numEngineer = gd::gd_add(gd_ctx, lv_numEngineer, gd::GdVal::from_int(1LL));
                    }
                }
            }
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570), gd::GdVal::from_str(&battle_string_literals[7])), gd::gd_mul(lv_numEngineer, gd::native_array_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1570), gd::GdVal::from_str(&battle_string_literals[51])))), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 2); })();
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_phase, gd::GdVal::from_int(5LL))))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    }
    else {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__phase = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__phase = gd::gd_coerce_int(lv__phase);
    this->f_phase = gd::gd_coerce_int(lv__phase);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f_phase, gd::GdVal::from_int(0LL))))) {
        this->f_baseCooldownOverride = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_101, _ca, 1); })());
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_phase, gd::GdVal::from_int(5LL))))) {
        this->f_baseCooldownOverride = gd::gd_coerce_float(gd::gd_sub(([&]() { gd::GdVal _ca[] = {this->f_phase}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_101, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {gd::gd_sub(this->f_phase, gd::GdVal::from_int(1LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_101, _ca, 1); })()));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_switchGradient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_phase = gd::gd_coerce_int(gd::gd_neg(gd::GdVal::from_int(1LL)));
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_switchGradient_2343, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Laboratory(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Laboratory>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Laboratory = {CLS_Gd__gd_core_items__Exclusive__Laboratory, "Laboratory", "res://gd_core_items/Exclusive/Laboratory.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Laboratory, &Gd__gd_core_items__Exclusive__Laboratory::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Laboratory::call_static_fn};

void Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_triggerType = gd::GdVal::from_int(0);
    this->f_stackType = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::meta() const { return &META_Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect; }
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return gd::GdVal::null();
}
bool Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_triggerType_2387: out = this->f_triggerType; return true;
        case SYM_GEN_stackType_2388: out = this->f_stackType; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_triggerType_2387: this->f_triggerType = gd::gd_coerce_int(val); return true;
        case SYM_GEN_stackType_2388: this->f_stackType = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_pushEncoded_2389: return true;
        case SYM_GEN_setFromEncoded_2390: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_pushEncoded_2389: out = fn_pushEncoded(args, argc); return true;
        case SYM_GEN_setFromEncoded_2390: out = fn_setFromEncoded(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::fn_pushEncoded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bitStream = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_normalizedStack = gd::gd_sub(this->f_stackType, gd::GdVal::from_int(101LL));
    (void)([&]() { gd::GdVal _ca[] = {this->f_triggerType, gd::native_inline_call(gd_ctx, Gd__gd_core_items__Exclusive__MagicRing::get_static_const_or_enum(gd_ctx, SYM_GEN_TriggerType_2385), gd::SYM_size, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_bitStream, SYM_GEN_push_2874, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_normalizedStack, gd::GdVal::from_int(16LL)}; return gd::native_inline_call(gd_ctx, lv_bitStream, SYM_GEN_push_2874, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::fn_setFromEncoded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bitStream = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_triggerType = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, Gd__gd_core_items__Exclusive__MagicRing::get_static_const_or_enum(gd_ctx, SYM_GEN_TriggerType_2385), gd::SYM_size, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_bitStream, SYM_GEN_pull_2875, _ca, 1); })());
    this->f_stackType = gd::gd_coerce_int(gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(16LL)}; return gd::native_inline_call(gd_ctx, lv_bitStream, SYM_GEN_pull_2875, _ca, 1); })(), gd::GdVal::from_int(101LL)));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect = {CLS_Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect, "RingEffect", "", nullptr, true, _alloc_Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect, &Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::get_static_prop_fn, &Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::call_static_fn};

void Gd__gd_core_items__Exclusive__MrsStruggles::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_activationParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__MrsStruggles::meta() const { return &META_Gd__gd_core_items__Exclusive__MrsStruggles; }
gd::GdVal Gd__gd_core_items__Exclusive__MrsStruggles::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__MrsStruggles::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__MrsStruggles::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MrsStruggles::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MrsStruggles::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MrsStruggles::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__MrsStruggles::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__MrsStruggles::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(25LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MrsStruggles::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MrsStruggles::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1620 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0));
        gd::GdArr* _t1621 = (_t1620.kind == gd::GdVal::Kind::Arr) ? _t1620.arr : nullptr;
        uint32_t _len__t1622 = _t1621 ? _t1621->len : 0u;
        for (uint32_t _t1622 = 0; _t1622 < _len__t1622; ++_t1622) {
            gd::GdVal lv_buff = _t1621->data[_t1622];
            (void)([&]() { gd::GdVal _ca[] = {lv_buff, gd::GdVal::from_int(1LL), gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_loseStacks_1032, _ca, 3); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MrsStruggles::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MrsStruggles(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__MrsStruggles>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MrsStruggles = {CLS_Gd__gd_core_items__Exclusive__MrsStruggles, "MrsStruggles", "res://gd_core_items/Exclusive/MrsStruggles.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__MrsStruggles, &Gd__gd_core_items__Exclusive__MrsStruggles::get_static_prop_fn, &Gd__gd_core_items__Exclusive__MrsStruggles::call_static_fn};

void Gd__gd_core_items__Exclusive__PlasticCube::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Cube::init_fields(gd_ctx);
    this->f_spikes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PlasticCube::meta() const { return &META_Gd__gd_core_items__Exclusive__PlasticCube; }
gd::GdVal Gd__gd_core_items__Exclusive__PlasticCube::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Cube::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PlasticCube::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PlasticCube::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PlasticCube::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PlasticCube::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PlasticCube::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PlasticCube::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Cube::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PlasticCube::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PlasticCube::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_99, nullptr, 0);
    gd::GdVal lv_affectedItem = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_428, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_affectedItem, gd::GdVal::null())))) {
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_affectedItem, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_cube_advanced_1426)))))) {
            { gd::GdVal _t1623 = gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_cube_advanced_1426); gd::GdVal _t1624 = lv_affectedItem; gd::native_array_set_index(gd_ctx, _t1623, _t1624, gd::GdVal::from_obj(this)); }
            (void)([&]() { gd::GdVal _ca[] = {this->f_cdAdvance}; return gd::native_inline_call(gd_ctx, lv_affectedItem, SYM_GEN_advanceCooldownPercent_146, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_cdAdvance, this->f_penaltyFactor)}; return gd::native_inline_call(gd_ctx, lv_affectedItem, SYM_GEN_advanceCooldownPercent_146, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PlasticCube::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Cube::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[33])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PlasticCube(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__PlasticCube>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PlasticCube = {CLS_Gd__gd_core_items__Exclusive__PlasticCube, "PlasticCube", "res://gd_core_items/Exclusive/PlasticCube.gd", &META_Gd__gd_core_items__Exclusive__Cube, true, _alloc_Gd__gd_core_items__Exclusive__PlasticCube, &Gd__gd_core_items__Exclusive__PlasticCube::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PlasticCube::call_static_fn};

void Gd__gd_core_items__Exclusive__PuzzlebagZ::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bag::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PuzzlebagZ::meta() const { return &META_Gd__gd_core_items__Exclusive__PuzzlebagZ; }
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagZ::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagZ::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PuzzlebagZ::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagZ::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagZ::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagZ::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagZ::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagZ::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_toItem, SYM_GEN_inflictsDebuffs_298, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagZ::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1625 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_927, nullptr, 0));
        gd::GdArr* _t1626 = (_t1625.kind == gd::GdVal::Kind::Arr) ? _t1625.arr : nullptr;
        uint32_t _len__t1627 = _t1626 ? _t1626->len : 0u;
        for (uint32_t _t1627 = 0; _t1627 < _len__t1627; ++_t1627) {
            gd::GdVal lv_item = _t1626->data[_t1627];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_allDebuffs_198, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagZ::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PuzzlebagZ(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__PuzzlebagZ>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PuzzlebagZ = {CLS_Gd__gd_core_items__Exclusive__PuzzlebagZ, "PuzzlebagZ", "res://gd_core_items/Exclusive/PuzzlebagZ.gd", &META_Gd__gd_core_items__Bag, true, _alloc_Gd__gd_core_items__Exclusive__PuzzlebagZ, &Gd__gd_core_items__Exclusive__PuzzlebagZ::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PuzzlebagZ::call_static_fn};

void Gd__gd_core_items__Exclusive__Resistor::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_heatThreshold = gd::GdVal::null();
    this->f_heat = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Resistor::meta() const { return &META_Gd__gd_core_items__Exclusive__Resistor; }
gd::GdVal Gd__gd_core_items__Exclusive__Resistor::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Resistor::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Resistor::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_heatThreshold_1975: out = this->f_heatThreshold; return true;
        case SYM_GEN_heat_1896: out = this->f_heat; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Resistor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heatThreshold_1975: this->f_heatThreshold = val; return true;
        case SYM_GEN_heat_1896: this->f_heat = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Resistor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onChargeReceived_2129: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Resistor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onChargeReceived_2129: out = fn_onChargeReceived(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Resistor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Resistor::fn_onChargeReceived(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getHeat_1251, nullptr, 0), this->f_heatThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Resistor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_heatThreshold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[43])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[34])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Resistor(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Resistor>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Resistor = {CLS_Gd__gd_core_items__Exclusive__Resistor, "Resistor", "res://gd_core_items/Exclusive/Resistor.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Resistor, &Gd__gd_core_items__Exclusive__Resistor::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Resistor::call_static_fn};

void Gd__gd_core_items__Exclusive__ShepherdsCrook::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ShepherdsCrook::meta() const { return &META_Gd__gd_core_items__Exclusive__ShepherdsCrook; }
gd::GdVal Gd__gd_core_items__Exclusive__ShepherdsCrook::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ShepherdsCrook::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ShepherdsCrook::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ShepherdsCrook::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ShepherdsCrook::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ShepherdsCrook::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ShepherdsCrook::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ShepherdsCrook::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShepherdsCrook::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeBuffProtectionChance_1286, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(109LL), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeResistChance_1026, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(110LL), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeResistChance_1026, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShepherdsCrook::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1628 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1629 = (_t1628.kind == gd::GdVal::Kind::Arr) ? _t1628.arr : nullptr;
        uint32_t _len__t1630 = _t1629 ? _t1629->len : 0u;
        for (uint32_t _t1630 = 0; _t1630 < _len__t1630; ++_t1630) {
            gd::GdVal lv_item = _t1629->data[_t1630];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShepherdsCrook::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ShepherdsCrook(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ShepherdsCrook>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ShepherdsCrook = {CLS_Gd__gd_core_items__Exclusive__ShepherdsCrook, "ShepherdsCrook", "res://gd_core_items/Exclusive/ShepherdsCrook.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__ShepherdsCrook, &Gd__gd_core_items__Exclusive__ShepherdsCrook::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ShepherdsCrook::call_static_fn};

void Gd__gd_core_items__Exclusive__SnowStick::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_cold = gd::GdVal::null();
    this->f_selfCold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SnowStick::meta() const { return &META_Gd__gd_core_items__Exclusive__SnowStick; }
gd::GdVal Gd__gd_core_items__Exclusive__SnowStick::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SnowStick::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SnowStick::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_cold_2045: out = this->f_cold; return true;
        case SYM_GEN_selfCold_2517: out = this->f_selfCold; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SnowStick::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_cold_2045: this->f_cold = val; return true;
        case SYM_GEN_selfCold_2517: this->f_selfCold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SnowStick::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SnowStick::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SnowStick::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SnowStick::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_cold}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_351, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_int(110LL), this->f_selfCold}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SnowStick::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_cold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[53])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_selfCold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[54])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SnowStick(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SnowStick>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SnowStick = {CLS_Gd__gd_core_items__Exclusive__SnowStick, "SnowStick", "res://gd_core_items/Exclusive/SnowStick.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__SnowStick, &Gd__gd_core_items__Exclusive__SnowStick::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SnowStick::call_static_fn};

void Gd__gd_core_items__Exclusive__SquirrelArcher::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Squirrel::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SquirrelArcher::meta() const { return &META_Gd__gd_core_items__Exclusive__SquirrelArcher; }
gd::GdVal Gd__gd_core_items__Exclusive__SquirrelArcher::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Squirrel::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SquirrelArcher::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SquirrelArcher::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Exclusive__Squirrel::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SquirrelArcher::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Exclusive__Squirrel::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SquirrelArcher::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Squirrel::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SquirrelArcher::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Squirrel::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SquirrelArcher::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Squirrel::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SquirrelArcher::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_373, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SquirrelArcher::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_res = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_220, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SquirrelArcher::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Squirrel::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1550, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SquirrelArcher(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SquirrelArcher>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SquirrelArcher = {CLS_Gd__gd_core_items__Exclusive__SquirrelArcher, "SquirrelArcher", "res://gd_core_items/Exclusive/SquirrelArcher.gd", &META_Gd__gd_core_items__Exclusive__Squirrel, true, _alloc_Gd__gd_core_items__Exclusive__SquirrelArcher, &Gd__gd_core_items__Exclusive__SquirrelArcher::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SquirrelArcher::call_static_fn};

void Gd__gd_core_items__Exclusive__Thornbloom::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_spikes = gd::GdVal::from_int(0);
    this->f_empower = gd::GdVal::from_int(0);
    this->f_damPerSpike = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Thornbloom::meta() const { return &META_Gd__gd_core_items__Exclusive__Thornbloom; }
gd::GdVal Gd__gd_core_items__Exclusive__Thornbloom::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Thornbloom::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Thornbloom::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        case SYM_GEN_damPerSpike_2582: out = this->f_damPerSpike; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Thornbloom::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikes_898: this->f_spikes = gd::gd_coerce_int(val); return true;
        case SYM_GEN_empower_998: this->f_empower = gd::gd_coerce_int(val); return true;
        case SYM_GEN_damPerSpike_2582: this->f_damPerSpike = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Thornbloom::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onSpikesChanged_944: return true;
        case SYM_GEN_onEmpowerChanged_2113: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Thornbloom::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onSpikesChanged_944: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN_onEmpowerChanged_2113: out = fn_onEmpowerChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Thornbloom::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Thornbloom::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[55]), gd::GdVal::from_str(&battle_string_literals[56])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[13]), gd::GdVal::from_str(&battle_string_literals[14])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Thornbloom::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_damPerSpike, lv_amount)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_162, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Thornbloom::fn_onEmpowerChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), lv_amount), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Thornbloom::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 1); })();
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_empower}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
        }
        else {
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Thornbloom::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[33])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_damPerSpike = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[57])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Thornbloom(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Thornbloom>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Thornbloom = {CLS_Gd__gd_core_items__Exclusive__Thornbloom, "Thornbloom", "res://gd_core_items/Exclusive/Thornbloom.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__Thornbloom, &Gd__gd_core_items__Exclusive__Thornbloom::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Thornbloom::call_static_fn};

void Gd__gd_core_items__Exclusive__Ultima::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_typesDict = gd::GdVal::null();
    this->f_speedPerSpell = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Ultima::meta() const { return &META_Gd__gd_core_items__Exclusive__Ultima; }
gd::GdVal Gd__gd_core_items__Exclusive__Ultima::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Ultima::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Ultima::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_typesDict_2068: out = this->f_typesDict; return true;
        case SYM_GEN_speedPerSpell_2600: out = this->f_speedPerSpell; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Ultima::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_typesDict_2068: this->f_typesDict = val; return true;
        case SYM_GEN_speedPerSpell_2600: this->f_speedPerSpell = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Ultima::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Ultima::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Ultima::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Ultima::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth((gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(26LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(28LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(25LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(18LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ultima::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_typesDict = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countTypes_495, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(18LL)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_speedPerSpell, gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(18LL)))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ultima::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(26LL)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(26LL)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[28])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(26LL)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[33])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 1); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(28LL)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(28LL)), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(28LL)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[53])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_351, _ca, 1); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(22LL)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(22LL)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[18])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(25LL)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(25LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_373, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ultima::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_642, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_placed)))) {
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[58]), gd::GdVal::from_str(&battle_string_literals[59])}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[60]), gd::GdVal::from_str(&battle_string_literals[59])}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[61]), gd::GdVal::from_str(&battle_string_literals[59])}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[62]), gd::GdVal::from_str(&battle_string_literals[59])}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        return lv_descr;
    }
    this->f_typesDict = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countTypes_495, _ca, 1); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[63]), gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(26LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_452, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[64]), gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(28LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_452, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[65]), gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(22LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_452, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[66]), gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(25LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_452, _ca, 3); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ultima::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speedPerSpell = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[26])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Ultima(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Ultima>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Ultima = {CLS_Gd__gd_core_items__Exclusive__Ultima, "Ultima", "res://gd_core_items/Exclusive/Ultima.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Ultima, &Gd__gd_core_items__Exclusive__Ultima::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Ultima::call_static_fn};

void Gd__gd_core_items__FalconBlade::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__FalconBlade::meta() const { return &META_Gd__gd_core_items__FalconBlade; }
gd::GdVal Gd__gd_core_items__FalconBlade::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__FalconBlade::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__FalconBlade::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__FalconBlade::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__FalconBlade::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_getCraftingOffset_850: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__FalconBlade::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getCraftingOffset_850: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__FalconBlade::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__FalconBlade::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__FalconBlade::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1631 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1632 = (_t1631.kind == gd::GdVal::Kind::Arr) ? _t1631.arr : nullptr;
        uint32_t _len__t1633 = _t1632 ? _t1632->len : 0u;
        for (uint32_t _t1633 = 0; _t1633 < _len__t1633; ++_t1633) {
            gd::GdVal lv_item = _t1632->data[_t1633];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::GdVal::from_int(100LL))}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__FalconBlade::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__FalconBlade::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1634 = lv_forDirection;
        if (gd::native_scalar_eq(_t1634, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
        else if (gd::native_scalar_eq(_t1634, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
        else if (gd::native_scalar_eq(_t1634, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::native_scalar_eq(_t1634, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__FalconBlade::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__FalconBlade(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__FalconBlade>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__FalconBlade = {CLS_Gd__gd_core_items__FalconBlade, "FalconBlade", "res://gd_core_items/FalconBlade.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__FalconBlade, &Gd__gd_core_items__FalconBlade::get_static_prop_fn, &Gd__gd_core_items__FalconBlade::call_static_fn};

void Gd__gd_core_items__GlovesofHaste::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_bonusSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__GlovesofHaste::meta() const { return &META_Gd__gd_core_items__GlovesofHaste; }
gd::GdVal Gd__gd_core_items__GlovesofHaste::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__GlovesofHaste::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__GlovesofHaste::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_bonusSpeed_1882: out = this->f_bonusSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__GlovesofHaste::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusSpeed_1882: this->f_bonusSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__GlovesofHaste::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__GlovesofHaste::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__GlovesofHaste::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__GlovesofHaste::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__GlovesofHaste::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1635 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1636 = (_t1635.kind == gd::GdVal::Kind::Arr) ? _t1635.arr : nullptr;
        uint32_t _len__t1637 = _t1636 ? _t1636->len : 0u;
        for (uint32_t _t1637 = 0; _t1637 < _len__t1637; ++_t1637) {
            gd::GdVal lv_item = _t1636->data[_t1637];
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__GlovesofHaste::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_bonusSpeed = gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::GdVal::from_int(100LL));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__GlovesofHaste(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__GlovesofHaste>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__GlovesofHaste = {CLS_Gd__gd_core_items__GlovesofHaste, "GlovesofHaste", "res://gd_core_items/GlovesofHaste.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__GlovesofHaste, &Gd__gd_core_items__GlovesofHaste::get_static_prop_fn, &Gd__gd_core_items__GlovesofHaste::call_static_fn};

void Gd__gd_core_items__LuckyBow::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bow::init_fields(gd_ctx);
    this->f_extraAttack = gd::GdVal::from_bool(false);
}
const gd::GdClassMeta* Gd__gd_core_items__LuckyBow::meta() const { return &META_Gd__gd_core_items__LuckyBow; }
gd::GdVal Gd__gd_core_items__LuckyBow::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Bow::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__LuckyBow::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__LuckyBow::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_extraAttack_1917: out = this->f_extraAttack; return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::get_prop(prop, out);
}
bool Gd__gd_core_items__LuckyBow::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_extraAttack_1917: this->f_extraAttack = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__LuckyBow::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onWeaponAttacked_950: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::has_own_method(m);
}
bool Gd__gd_core_items__LuckyBow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_950: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__LuckyBow::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bow::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__LuckyBow::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyBow::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyBow::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_res = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_220, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 1); })();
        if (gd::gd_truth(this->f_extraAttack)) {
            gd::GdVal lv_res2 = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, lv_res, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_220, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_res2}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false), gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, lv_res2, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyBow::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_wasCriticalHit_1524, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyBow::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyBow::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__extraAttack = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv__extraAttack)) {
    }
    else {
    }
    this->f_extraAttack = lv__extraAttack;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyBow::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bow::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__LuckyBow(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__LuckyBow>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__LuckyBow = {CLS_Gd__gd_core_items__LuckyBow, "LuckyBow", "res://gd_core_items/LuckyBow.gd", &META_Gd__gd_core_items__Bow, true, _alloc_Gd__gd_core_items__LuckyBow, &Gd__gd_core_items__LuckyBow::get_static_prop_fn, &Gd__gd_core_items__LuckyBow::call_static_fn};

void Gd__gd_core_items__PoisonDagger::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Dagger::init_fields(gd_ctx);
    this->f_poison = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__PoisonDagger::meta() const { return &META_Gd__gd_core_items__PoisonDagger; }
gd::GdVal Gd__gd_core_items__PoisonDagger::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Dagger::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__PoisonDagger::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__PoisonDagger::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_poison_1962: out = this->f_poison; return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::get_prop(prop, out);
}
bool Gd__gd_core_items__PoisonDagger::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_poison_1962: this->f_poison = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__PoisonDagger::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::has_own_method(m);
}
bool Gd__gd_core_items__PoisonDagger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__PoisonDagger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Dagger::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__PoisonDagger::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_poison}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonDagger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Dagger::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_poison = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__PoisonDagger(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__PoisonDagger>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__PoisonDagger = {CLS_Gd__gd_core_items__PoisonDagger, "PoisonDagger", "res://gd_core_items/PoisonDagger.gd", &META_Gd__gd_core_items__Dagger, true, _alloc_Gd__gd_core_items__PoisonDagger, &Gd__gd_core_items__PoisonDagger::get_static_prop_fn, &Gd__gd_core_items__PoisonDagger::call_static_fn};

void Gd__gd_core_items__StaffofUnhealing::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_buffActive = gd::GdVal::from_bool(false);
    this->f_activationParticles = gd::GdVal::null();
    this->f_unhealingTimer = gd::GdVal::null();
    this->f_manaCost = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__StaffofUnhealing::meta() const { return &META_Gd__gd_core_items__StaffofUnhealing; }
gd::GdVal Gd__gd_core_items__StaffofUnhealing::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__StaffofUnhealing::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__StaffofUnhealing::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_buffActive_1813: out = this->f_buffActive; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_unhealingTimer_1984: out = this->f_unhealingTimer; return true;
        case SYM_GEN_manaCost_1815: out = this->f_manaCost; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__StaffofUnhealing::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffActive_1813: this->f_buffActive = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_unhealingTimer_1984: this->f_unhealingTimer = val; return true;
        case SYM_GEN_manaCost_1815: this->f_manaCost = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__StaffofUnhealing::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_buffEnded_1817: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__StaffofUnhealing::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_buffEnded_1817: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__StaffofUnhealing::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__StaffofUnhealing::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaffofUnhealing::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_healAmount = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[24])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_manaCost)))) {
            if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_buffActive)))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_giveUnhealing_1178, _ca, 1); })();
            }
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[67])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, this->f_unhealingTimer, SYM_GEN_start_1779, _ca, 1); })();
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_healAmount, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 2); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {lv_healAmount}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 1); })();
        }
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaffofUnhealing::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_reduceUnhealing_1179, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaffofUnhealing::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_unhealingTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaffofUnhealing::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaffofUnhealing::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv_active)) {
    }
    else {
    }
    this->f_buffActive = lv_active;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaffofUnhealing::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_unhealingTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[68]), gd::GdVal::from_str(&battle_string_literals[69]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_manaCost = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__StaffofUnhealing(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__StaffofUnhealing>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__StaffofUnhealing = {CLS_Gd__gd_core_items__StaffofUnhealing, "StaffofUnhealing", "res://gd_core_items/StaffofUnhealing.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__StaffofUnhealing, &Gd__gd_core_items__StaffofUnhealing::get_static_prop_fn, &Gd__gd_core_items__StaffofUnhealing::call_static_fn};

void Gd__gd_core_items__VampiricScythe::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_lastSpeedBonus = gd::GdVal::from_float(0.0);
}
const gd::GdClassMeta* Gd__gd_core_items__VampiricScythe::meta() const { return &META_Gd__gd_core_items__VampiricScythe; }
gd::GdVal Gd__gd_core_items__VampiricScythe::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__VampiricScythe::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__VampiricScythe::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_lastSpeedBonus_1002: out = this->f_lastSpeedBonus; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__VampiricScythe::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_lastSpeedBonus_1002: this->f_lastSpeedBonus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__VampiricScythe::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onVampirismChanged_943: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__VampiricScythe::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onVampirismChanged_943: out = fn_onVampirismChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__VampiricScythe::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__VampiricScythe::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(8LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_gainsStack_86, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__VampiricScythe::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1638 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1639 = (_t1638.kind == gd::GdVal::Kind::Arr) ? _t1638.arr : nullptr;
        uint32_t _len__t1640 = _t1639 ? _t1639->len : 0u;
        for (uint32_t _t1640 = 0; _t1640 < _len__t1640; ++_t1640) {
            gd::GdVal lv_item = _t1639->data[_t1640];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(103LL), gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_giveBuffPower_303, _ca, 2); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[70]), gd::GdVal::from_str(&battle_string_literals[71])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__VampiricScythe::fn_onVampirismChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_scytheSpeedBonus = gd::gd_min(gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getVampirism_1226, nullptr, 0)), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    lv_scytheSpeedBonus = gd::gd_div(gd_ctx, lv_scytheSpeedBonus, gd::GdVal::from_float(100.0));
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(lv_scytheSpeedBonus, this->f_lastSpeedBonus)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    this->f_lastSpeedBonus = lv_scytheSpeedBonus;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__VampiricScythe::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_lastSpeedBonus = gd::GdVal::from_float(0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__VampiricScythe::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__VampiricScythe(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__VampiricScythe>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__VampiricScythe = {CLS_Gd__gd_core_items__VampiricScythe, "VampiricScythe", "res://gd_core_items/VampiricScythe.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__VampiricScythe, &Gd__gd_core_items__VampiricScythe::get_static_prop_fn, &Gd__gd_core_items__VampiricScythe::call_static_fn};
