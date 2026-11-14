#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core__BagofStones.hpp"
#include "../hdrs/Gd__gd_core__BurningCoal.hpp"
#include "../hdrs/Gd__gd_core__CoreEventBus.hpp"
#include "../hdrs/Gd__gd_core__Crown.hpp"
#include "../hdrs/Gd__gd_core__EvilCap.hpp"
#include "../hdrs/Gd__gd_core__HeroLongsword.hpp"
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
#include "../hdrs/Gd__gd_core_items__Exclusive__Hypercube.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__LeafBadge.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MagiteccArmor.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MushroomFarm.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PoisonFrog.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Puzzlebox.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Reverse.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Shielded.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Solaris.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__StaffofFire.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ThornShortbow.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__UnidentifiedSkill.hpp"
#include "../hdrs/Gd__gd_core_items__FancyFencingRapier.hpp"
#include "../hdrs/Gd__gd_core_items__Hammer.hpp"
#include "../hdrs/Gd__gd_core_items__LuckyClover.hpp"
#include "../hdrs/Gd__gd_core_items__PoisonGoobert.hpp"
#include "../hdrs/Gd__gd_core_items__StaminaSack.hpp"
#include "../hdrs/Gd__gd_core_items__VillainSword.hpp"

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
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_getAffectedCellsAfterRotate_primary_412: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__BagofStones::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_getAffectedCellsAfterRotate_primary_412: out = fn_getAffectedCellsAfterRotate_primary(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Tag_858), SYM_GEN_Stone_2734)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasTag_83, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BagofStones::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1490 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1491 = (_t1490.kind == gd::GdVal::Kind::Arr) ? _t1490.arr : nullptr;
        uint32_t _len__t1492 = _t1491 ? _t1491->len : 0u;
        for (uint32_t _t1492 = 0; _t1492 < _len__t1492; ++_t1492) {
            gd::GdVal lv_item = _t1491->data[_t1492];
            (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_setBagOfStones_905, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BagofStones::fn_getAffectedCellsAfterRotate_primary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rotatedCells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_rotatedCells, gd::GdVal::from_vec2(0.0, -1.0), gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1284), SYM_GEN_INVENTORY_1093), SYM_GEN_getCellsInLine_1520, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BagofStones::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_canBlock_293: return true;
        case SYM_GEN_prepareWeapon_982: return true;
        case SYM_GEN_preAttack_996: return true;
        case SYM_GEN_prepareArmor_983: return true;
        case SYM_GEN_combatStartArmor_986: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core__BurningCoal::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canBlock_293: out = fn_canBlock(args, argc); return true;
        case SYM_GEN_prepareWeapon_982: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_preAttack_996: out = fn_preAttack(args, argc); return true;
        case SYM_GEN_prepareArmor_983: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_combatStartArmor_986: out = fn_combatStartArmor(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: out = fn_onHotSwapHoverWithGemEnd(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_391, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pre_deal_damage_early", 21u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "preAttack", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BurningCoal::fn_preAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)));
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BurningCoal::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Cold_2574), gd::gd_round(gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0)))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeResistStacks_1026, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BurningCoal::fn_combatStartArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BurningCoal::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_269, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_358, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BurningCoal::fn_onHotSwapHoverWithGemEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BurningCoal::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__BurningCoal(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__BurningCoal>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__BurningCoal = {CLS_Gd__gd_core__BurningCoal, "BurningCoal", "res://gd_core/BurningCoal.gd", &META_Gd__gd_core_items__Gems__Gem, false, _alloc_Gd__gd_core__BurningCoal, &Gd__gd_core__BurningCoal::get_static_prop_fn, &Gd__gd_core__BurningCoal::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreEventBus_LoggingMode[] = {{"None", 0LL}, {"Instant", 1LL}, {"Delayed", 2LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreEventBus_LoggingMode = {"LoggingMode", _ekv_Gd__gd_core__CoreEventBus_LoggingMode, 3u};
void Gd__gd_core__CoreEventBus::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_loggingMode = gd::get_prop(gd_ctx, Gd__gd_core__CoreEventBus::get_static_const_or_enum(gd_ctx, SYM_GEN_LoggingMode_1508), SYM_GEN_Instant_2778);
    this->f_signalQueue = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_connections = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_signalIDs = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f__ctx = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__CoreEventBus::meta() const { return &META_Gd__gd_core__CoreEventBus; }
gd::GdVal Gd__gd_core__CoreEventBus::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_LoggingMode_1508: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreEventBus_LoggingMode);
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
        case SYM_GEN_loggingMode_1493: out = this->f_loggingMode; return true;
        case SYM_GEN_signalQueue_1494: out = this->f_signalQueue; return true;
        case SYM_GEN_connections_1495: out = this->f_connections; return true;
        case SYM_GEN_signalIDs_1496: out = this->f_signalIDs; return true;
        case SYM_GEN__ctx_1325: out = this->f__ctx; return true;
        case SYM_GEN_LoggingMode_1508: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreEventBus_LoggingMode); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreEventBus::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_loggingMode_1493: this->f_loggingMode = val; return true;
        case SYM_GEN_signalQueue_1494: this->f_signalQueue = val; return true;
        case SYM_GEN_connections_1495: this->f_connections = val; return true;
        case SYM_GEN_signalIDs_1496: this->f_signalIDs = val; return true;
        case SYM_GEN__ctx_1325: this->f__ctx = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreEventBus::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_setLoggingMode_1497: return true;
        case SYM_GEN_getLoggingMode_1498: return true;
        case SYM_GEN_queueSignal_1499: return true;
        case SYM_GEN_flushLoggingQueue_1500: return true;
        case SYM_GEN_emitSignal_1501: return true;
        case SYM_GEN_emitEvent_1502: return true;
        case SYM_GEN_logEvent_1328: return true;
        case SYM_GEN_emitAndLog_1503: return true;
        case SYM_GEN_connectEvent_1504: return true;
        case SYM_GEN_getEmissionID_1505: return true;
        case SYM_GEN_disconnectAll_1506: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreEventBus::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_setLoggingMode_1497: out = fn_setLoggingMode(args, argc); return true;
        case SYM_GEN_getLoggingMode_1498: out = fn_getLoggingMode(args, argc); return true;
        case SYM_GEN_queueSignal_1499: out = fn_queueSignal(args, argc); return true;
        case SYM_GEN_flushLoggingQueue_1500: out = fn_flushLoggingQueue(args, argc); return true;
        case SYM_GEN_emitSignal_1501: out = fn_emitSignal(args, argc); return true;
        case SYM_GEN_emitEvent_1502: out = fn_emitEvent(args, argc); return true;
        case SYM_GEN_logEvent_1328: out = fn_logEvent(args, argc); return true;
        case SYM_GEN_emitAndLog_1503: out = fn_emitAndLog(args, argc); return true;
        case SYM_GEN_connectEvent_1504: out = fn_connectEvent(args, argc); return true;
        case SYM_GEN_getEmissionID_1505: out = fn_getEmissionID(args, argc); return true;
        case SYM_GEN_disconnectAll_1506: out = fn_disconnectAll(args, argc); return true;
        case SYM_GEN_Util_dictAppend_1507: out = sf_Util_dictAppend(gd_ctx, args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreEventBus::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_Util_dictAppend_1507: out = sf_Util_dictAppend(gd_ctx, args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core__CoreEventBus::get_static_const_or_enum(gd_ctx, SYM_GEN_LoggingMode_1508), SYM_GEN_Instant_2778)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setLoggingMode_1497, _ca, 1); })();
    gd::GdVal lv_queueDuplicate = gd::call_method(gd_ctx, this->f_signalQueue, gd::SYM_duplicate, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_signalQueue, gd::SYM_clear, nullptr, 0);
    {
        gd::GdVal _t1493 = gd::gd_iter_seq(gd_ctx.arena, lv_queueDuplicate);
        gd::GdArr* _t1494 = (_t1493.kind == gd::GdVal::Kind::Arr) ? _t1493.arr : nullptr;
        uint32_t _len__t1495 = _t1494 ? _t1494->len : 0u;
        for (uint32_t _t1495 = 0; _t1495 < _len__t1495; ++_t1495) {
            gd::GdVal lv_tuple = _t1494->data[_t1495];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, lv_tuple, gd::GdVal::from_int(0LL)), gd::get_index(gd_ctx, lv_tuple, gd::GdVal::from_int(1LL)), gd::get_index(gd_ctx, lv_tuple, gd::GdVal::from_int(2LL)), gd::get_index(gd_ctx, lv_tuple, gd::GdVal::from_int(3LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_emitAndLog_1503, _ca, 4); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEventBus::fn_emitSignal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_emitter = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_signalName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_arguments = (_argc > 2) ? _args[2] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    (void)([&]() { gd::GdVal _ca[] = {lv_emitter, lv_signalName, gd::GdVal::null(), lv_arguments}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_emitEvent_1502, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEventBus::fn_emitEvent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_emitter = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_signalName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_arguments = (_argc > 3) ? _args[3] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_loggingMode, gd::get_prop(gd_ctx, Gd__gd_core__CoreEventBus::get_static_const_or_enum(gd_ctx, SYM_GEN_LoggingMode_1508), SYM_GEN_Delayed_2589))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_emitter, lv_signalName, lv_event, lv_arguments}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_queueSignal_1499, _ca, 4); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {lv_emitter, lv_signalName, lv_event, lv_arguments}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_emitAndLog_1503, _ca, 4); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEventBus::fn_logEvent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_loggingMode, gd::get_prop(gd_ctx, Gd__gd_core__CoreEventBus::get_static_const_or_enum(gd_ctx, SYM_GEN_LoggingMode_1508), SYM_GEN_Delayed_2589))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u)), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_queueSignal_1499, _ca, 4); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u)), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_emitAndLog_1503, _ca, 4); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEventBus::fn_emitAndLog(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_emitter = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_signalName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_arguments = (_argc > 3) ? _args[3] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_event, gd::GdVal::null())))) {
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_fight_ended_1287))))) {
            if (gd::gd_truth(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1377), SYM_GEN_oracle_trace_1633))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, lv_event, SYM_GEN_type_1005)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1377), SYM_GEN_trace_event_1644, _ca, 1); })();
            }
            (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_hooks_1380), SYM_GEN_logEvent_1328, _ca, 1); })();
        }
    }
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_emitter, gd::GdVal::null()))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_signalName, this->f_signalIDs)))))))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_signalID = gd::get_index(gd_ctx, this->f_signalIDs, lv_signalName);
    gd::GdVal lv_emissionID = ([&]() { gd::GdVal _ca[] = {lv_emitter, lv_signalID}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getEmissionID_1505, _ca, 2); })();
    gd::GdVal lv__bus_list = ([&]() { gd::GdVal _ca[] = {lv_emissionID, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, this->f_connections, gd::SYM_get, _ca, 2); })();
    if (gd::gd_truth((gd::gd_truth(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1377), SYM_GEN_oracle_trace_1633)) ? gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1377), SYM_GEN__stacktrace_1635))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv__eid = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "?", 1u));
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_emitter, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "isCoreItem", 10u))}; return gd::call_method(gd_ctx, lv_emitter, gd::SYM_has_method, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
            lv__eid = gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv_emitter, SYM_GEN_descriptor_2), SYM_GEN_identifier_1577))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "/ot", 3u))), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(gd::get_prop(gd_ctx, lv_emitter, SYM_GEN_ownerType_51))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BUS", 3u)), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, lv_signalName)), ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, lv__bus_list, gd::SYM_size, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "emitter=", 8u)), lv__eid)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1377), SYM_GEN_trace_diag_1645, _ca, 4); })();
    }
    gd::GdVal lv__bus_i = gd::GdVal::from_int(0LL);
    gd::GdVal lv__eid2 = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "?", 1u));
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_emitter, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "isCoreItem", 10u))}; return gd::call_method(gd_ctx, lv_emitter, gd::SYM_has_method, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        lv__eid2 = gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv_emitter, SYM_GEN_descriptor_2), SYM_GEN_identifier_1577))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "/ot", 3u))), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(gd::get_prop(gd_ctx, lv_emitter, SYM_GEN_ownerType_51))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
    }
    {
        gd::GdVal _t1496 = gd::gd_iter_seq(gd_ctx.arena, lv__bus_list);
        gd::GdArr* _t1497 = (_t1496.kind == gd::GdVal::Kind::Arr) ? _t1496.arr : nullptr;
        uint32_t _len__t1498 = _t1497 ? _t1497->len : 0u;
        for (uint32_t _t1498 = 0; _t1498 < _len__t1498; ++_t1498) {
            gd::GdVal lv__bus_pair = _t1497->data[_t1498];
            if (gd::gd_truth(gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_fight_ended_1287))) {
                return gd::GdVal::null();
            }
            if (gd::gd_truth((gd::gd_truth(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1377), SYM_GEN_oracle_trace_1633)) ? gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1377), SYM_GEN__stacktrace_1635))) : gd::GdVal::from_bool(false)))) {
                gd::GdVal lv__rid = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "?", 1u));
                gd::GdVal lv__recv = gd::get_index(gd_ctx, lv__bus_pair, gd::GdVal::from_int(1LL));
                if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv__recv, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "isCoreItem", 10u))}; return gd::call_method(gd_ctx, lv__recv, gd::SYM_has_method, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
                    lv__rid = gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv__recv, SYM_GEN_descriptor_2), SYM_GEN_identifier_1577))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "/ot", 3u))), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(gd::get_prop(gd_ctx, lv__recv, SYM_GEN_ownerType_51))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
                }
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BUSL", 4u)), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, lv_signalName)), ([&]() { gd::GdVal _ca[] = {lv__bus_i}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), lv__rid}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1377), SYM_GEN_trace_diag_1645, _ca, 4); })();
            }
            lv__bus_i = gd::gd_add(gd_ctx, lv__bus_i, gd::GdVal::from_int(1LL));
            (void)([&]() { gd::GdVal _ca[] = {lv_arguments}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, lv__bus_pair, gd::GdVal::from_int(0LL)), gd::SYM_call_funcv, _ca, 1); })();
        }
    }
    if (gd::gd_truth((gd::gd_truth(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1377), SYM_GEN_oracle_trace_1633)) ? gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1377), SYM_GEN__stacktrace_1635))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BUSD", 4u)), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, lv_signalName)), ([&]() { gd::GdVal _ca[] = {lv__bus_i}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "emitter=", 8u)), lv__eid2)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_rng_1377), SYM_GEN_trace_diag_1645, _ca, 4); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEventBus::fn_connectEvent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_emitter = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_signalName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_receiver = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_method = (_argc > 3) ? _args[3] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_signalName, this->f_signalIDs))))) {
        { gd::GdVal _t1499 = this->f_signalIDs; gd::GdVal _t1500 = lv_signalName; gd::set_index(gd_ctx, _t1499, _t1500, gd::call_method(gd_ctx, this->f_signalIDs, gd::SYM_size, nullptr, 0)); }
    }
    gd::GdVal lv_signalID = gd::get_index(gd_ctx, this->f_signalIDs, lv_signalName);
    gd::GdVal lv_emissionID = ([&]() { gd::GdVal _ca[] = {lv_emitter, lv_signalID}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getEmissionID_1505, _ca, 2); })();
    gd::GdVal lv_funcRef = gd::GdVal::from_funcref(gd_ctx.arena.make<gd::GdFuncRef>());
    (void)([&]() { gd::GdVal _ca[] = {lv_method}; return gd::call_method(gd_ctx, lv_funcRef, gd::SYM_set_function, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_receiver}; return gd::call_method(gd_ctx, lv_funcRef, gd::SYM_set_instance, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_connections, lv_emissionID, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_funcRef, lv_receiver}))}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreEventBus::call_static_fn(gd_ctx, SYM_GEN_Util_dictAppend_1507, _ca, 3, _out); return _out; })();
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
        { gd::GdVal _t1501 = lv_dict; gd::GdVal _t1502 = lv_key; gd::set_index(gd_ctx, _t1501, _t1502, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))); }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_value}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, lv_dict, lv_key), gd::SYM_push_back, _ca, 1); })();
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
        case SYM_GEN_CrownState_1727: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Crown_CrownState);
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
        case SYM_GEN_crownState_1723: out = this->f_crownState; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_buffTimer_1724: out = this->f_buffTimer; return true;
        case SYM_GEN_manaCost_1720: out = this->f_manaCost; return true;
        case SYM_GEN_light_949: out = this->f_light; return true;
        case SYM_GEN_CrownState_1727: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Crown_CrownState); return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Crown::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_crownState_1723: this->f_crownState = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_buffTimer_1724: this->f_buffTimer = val; return true;
        case SYM_GEN_manaCost_1720: this->f_manaCost = val; return true;
        case SYM_GEN_light_949: this->f_light = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Crown::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onInvuEnded_1725: return true;
        case SYM_GEN_checkTrigger_1726: return true;
        case SYM_GEN_buffEnded_1722: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onCombatEnd_134: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Crown::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onInvuEnded_1725: out = fn_onInvuEnded(args, argc); return true;
        case SYM_GEN_checkTrigger_1726: out = fn_checkTrigger(args, argc); return true;
        case SYM_GEN_buffEnded_1722: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onCombatEnd_134: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Crown::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Crown::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core__Crown::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1727), SYM_GEN_Inactive_2594)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_mana_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkTrigger", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_invulnerable_end", 26u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onInvuEnded", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crown::fn_onInvuEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkTrigger_1726, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crown::fn_checkTrigger(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_crownState, gd::get_prop(gd_ctx, Gd__gd_core__Crown::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1727), SYM_GEN_Inactive_2594)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_isVulnerable_1275, nullptr, 0))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkMana_333, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core__Crown::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1727), SYM_GEN_Active_2595), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 2); })();
        gd::GdVal lv_invuDur = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_invu", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })();
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_invuDur, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_makeInvulnerable_1195, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_invuDur}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1685, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_manaCost, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_334, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crown::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core__Crown::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1727), SYM_GEN_Used_2596), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crown::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseBlind_346, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crown::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1686, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crown::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core__Crown::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1727), SYM_GEN_Inactive_2594)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crown::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__crownState = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__crownState, gd::get_prop(gd_ctx, Gd__gd_core__Crown::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1727), SYM_GEN_Inactive_2594))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__crownState, gd::get_prop(gd_ctx, Gd__gd_core__Crown::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1727), SYM_GEN_Active_2595))))) {
    }
    else {
    }
    this->f_crownState = gd::gd_coerce_int(lv__crownState);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crown::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BuffTimer", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffEnded", 9u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_137, _ca, 3); })();
    this->f_manaCost = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
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
        case SYM_GEN_nullifyApplied_1776: out = this->f_nullifyApplied; return true;
        case SYM_GEN_buffsActive_1777: out = this->f_buffsActive; return true;
        case SYM_GEN_buffTimer_1724: out = this->f_buffTimer; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_damReduction_1778: out = this->f_damReduction; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__EvilCap::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_nullifyApplied_1776: this->f_nullifyApplied = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_buffsActive_1777: this->f_buffsActive = val; return true;
        case SYM_GEN_buffTimer_1724: this->f_buffTimer = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_damReduction_1778: this->f_damReduction = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__EvilCap::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onPreCombatStart_127: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_buffEnded_1722: return true;
        case SYM_GEN_onCombatEnd_134: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__EvilCap::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreCombatStart_127: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_buffEnded_1722: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_134: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__EvilCap::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__EvilCap::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_reduceHealingEfficiency_1167, _ca, 1); })();
    this->f_nullifyApplied = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__EvilCap::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeDamageResistance_1263, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__EvilCap::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_nullifyApplied)))) {
        this->f_nullifyApplied = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changeBuffNullifyChances_1272, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1685, _ca, 1); })();
    this->f_buffsActive = gd::gd_add(gd_ctx, this->f_buffsActive, gd::GdVal::from_int(1LL));
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__EvilCap::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeDamageResistance_1263, _ca, 1); })();
    this->f_buffsActive = gd::gd_sub(this->f_buffsActive, gd::GdVal::from_int(1LL));
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__EvilCap::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1686, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__EvilCap::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_buffsActive = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BuffTimer", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffEnded", 9u)), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_137, _ca, 3); })();
    this->f_damReduction = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__EvilCap(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__EvilCap>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__EvilCap = {CLS_Gd__gd_core__EvilCap, "EvilCap", "res://gd_core/EvilCap.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__EvilCap, &Gd__gd_core__EvilCap::get_static_prop_fn, &Gd__gd_core__EvilCap::call_static_fn};

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
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_getCraftingOffset_850: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__HeroLongsword::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_getCraftingOffset_850: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_92, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeroLongsword::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1503 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1504 = (_t1503.kind == gd::GdVal::Kind::Arr) ? _t1503.arr : nullptr;
        uint32_t _len__t1505 = _t1504 ? _t1504->len : 0u;
        for (uint32_t _t1505 = 0; _t1505 < _len__t1505; ++_t1505) {
            gd::GdVal lv_item = _t1504->data[_t1505];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_163, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeroLongsword::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1506 = lv_forDirection;
        if (gd::gd_eq(_t1506, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
        else if (gd::gd_eq(_t1506, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
        else if (gd::gd_eq(_t1506, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::gd_eq(_t1506, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeroLongsword::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__HeroLongsword(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__HeroLongsword>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__HeroLongsword = {CLS_Gd__gd_core__HeroLongsword, "HeroLongsword", "res://gd_core/HeroLongsword.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__HeroLongsword, &Gd__gd_core__HeroLongsword::get_static_prop_fn, &Gd__gd_core__HeroLongsword::call_static_fn};

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
        case SYM_GEN_piggyPinataDescriptor_1823: out = this->f_piggyPinataDescriptor; return true;
        case SYM_GEN_hammerDescriptor_1824: out = this->f_hammerDescriptor; return true;
        case SYM_GEN_thorsHammerDescriptor_1825: out = this->f_thorsHammerDescriptor; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Piggybank::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_piggyPinataDescriptor_1823: this->f_piggyPinataDescriptor = val; return true;
        case SYM_GEN_hammerDescriptor_1824: this->f_hammerDescriptor = val; return true;
        case SYM_GEN_thorsHammerDescriptor_1825: this->f_thorsHammerDescriptor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Piggybank::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_explodeRandomly_1826: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_hasPinata_1827: return true;
        case SYM_GEN_isSmashRecipe_1828: return true;
        case SYM_GEN_getFusionItemName_836: return true;
        case SYM_GEN_allowGeneratingFusionItem_846: return true;
        case SYM_GEN_explode_1829: return true;
        case SYM_GEN_finishFusing_845: return true;
        case SYM_GEN_getShopPriority_853: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Piggybank::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_explodeRandomly_1826: out = fn_explodeRandomly(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_hasPinata_1827: out = fn_hasPinata(args, argc); return true;
        case SYM_GEN_isSmashRecipe_1828: out = fn_isSmashRecipe(args, argc); return true;
        case SYM_GEN_getFusionItemName_836: out = fn_getFusionItemName(args, argc); return true;
        case SYM_GEN_allowGeneratingFusionItem_846: out = fn_allowGeneratingFusionItem(args, argc); return true;
        case SYM_GEN_explode_1829: out = fn_explode(args, argc); return true;
        case SYM_GEN_finishFusing_845: out = fn_finishFusing(args, argc); return true;
        case SYM_GEN_getShopPriority_853: out = fn_getShopPriority(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Piggybank::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Piggybank::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveGold_754, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_explodeRandomly_1826, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Piggybank::fn_explodeRandomly(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBaseItem_260, nullptr, 0)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBoundAsIngredient_262, nullptr, 0))))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasPinata_1827, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_piggyPinataDescriptor, SYM_GEN_shopChance_1587)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_flipPercent_1640, _ca, 1); })())) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_explode_1829, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_removeItem_1528, _ca, 1); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_discard_764, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Piggybank::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasStartofBattle_128, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Piggybank::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_383, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Piggybank::fn_hasPinata(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {this->f_piggyPinataDescriptor}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_isItemInInventory_1575, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Piggybank::fn_isSmashRecipe(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_index(gd_ctx, gd::get_prop(gd_ctx, this->f_curRecipe, SYM_GEN_ingredients_2766), gd::GdVal::from_int(0LL)), this->f_hammerDescriptor))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_index(gd_ctx, gd::get_prop(gd_ctx, this->f_curRecipe, SYM_GEN_ingredients_2766), gd::GdVal::from_int(0LL)), this->f_thorsHammerDescriptor)))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Piggybank::fn_getFusionItemName(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isSmashRecipe_1828, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasPinata_1827, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Piggy Pinata_CRAFT", 18u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_tr_2719, _ca, 1); })();
    }
    return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getFusionItemName_836, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Piggybank::fn_allowGeneratingFusionItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isSmashRecipe_1828, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasPinata_1827, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
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
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isSmashRecipe_1828, nullptr, 0))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_explode_1829, nullptr, 0);
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_finishFusing_845, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Piggybank::fn_getShopPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_Lowest_2604);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Piggybank::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_piggyPinataDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Piggy Pinata", 12u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })();
    this->f_hammerDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Hammer", 6u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })();
    this->f_thorsHammerDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Thors Hammer", 12u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })();
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
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPreCombatStart_127: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onCalcTradeChance_1730: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__PlatinCustomerCard::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPreCombatStart_127: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onCalcTradeChance_1730: out = fn_onCalcTradeChance(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, lv_item, SYM_GEN_getRarity_238, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Rarity_862), SYM_GEN_Legendary_2738)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PlatinCustomerCard::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveReflectStacks_202, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_onPreCombatStart_127: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__RubyWhelp::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreCombatStart_127: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__RubyWhelp::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__RubyWhelp::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveReflectStacks_202, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RubyWhelp::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RubyWhelp::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_healthThreshold_1759: out = this->f_healthThreshold; return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::get_prop(prop, out);
}
bool Gd__gd_core_items__HealthPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_healthThreshold_1759: this->f_healthThreshold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__HealthPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1754: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onDamaged_1760: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::has_own_method(m);
}
bool Gd__gd_core_items__HealthPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1754: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1760: out = fn_onDamaged(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleansePoison_344, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HealthPotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDamaged", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HealthPotion::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__healthChange = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getRelativeHealth_304, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1753, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HealthPotion::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_High_2603);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HealthPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Potion::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_healthThreshold = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Whetstone::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_92, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Whetstone::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1507 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1508 = (_t1507.kind == gd::GdVal::Kind::Arr) ? _t1507.arr : nullptr;
        uint32_t _len__t1509 = _t1508 ? _t1508->len : 0u;
        for (uint32_t _t1509 = 0; _t1509 < _len__t1509; ++_t1509) {
            gd::GdVal lv_item = _t1508->data[_t1509];
            (void)([&]() { gd::GdVal _ca[] = {this->f_dam}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_163, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Whetstone::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_dam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
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
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__BloodAmulet::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__BloodAmulet::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__BloodAmulet::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BloodAmulet::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Pan::has_own_method(m);
}
bool Gd__gd_core_items__Eggscalibur::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_335, _ca, 2); })();
    if (gd::gd_truth(lv_event)) {
        gd::GdVal lv_affected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_affected, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Eggscalibur.gd:9", 16u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_shuffleEngine_1651, _ca, 2); })();
        gd::GdVal lv__ids = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u));
        {
            gd::GdVal _t1510 = gd::gd_iter_seq(gd_ctx.arena, lv_affected);
            gd::GdArr* _t1511 = (_t1510.kind == gd::GdVal::Kind::Arr) ? _t1510.arr : nullptr;
            uint32_t _len__t1512 = _t1511 ? _t1511->len : 0u;
            for (uint32_t _t1512 = 0; _t1512 < _len__t1512; ++_t1512) {
                gd::GdVal lv_food = _t1511->data[_t1512];
                lv__ids = gd::gd_add(gd_ctx, lv__ids, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv_food, SYM_GEN_descriptor_2), SYM_GEN_identifier_1577))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "|", 1u))));
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "ESHUF", 5u)), ([&]() { gd::GdVal _ca[] = {lv__ids}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "t=", 2u)), ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1382)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_trace_diag_1645, _ca, 4); })();
        {
            gd::GdVal _t1513 = gd::gd_iter_seq(gd_ctx.arena, lv_affected);
            gd::GdArr* _t1514 = (_t1513.kind == gd::GdVal::Kind::Arr) ? _t1513.arr : nullptr;
            uint32_t _len__t1515 = _t1514 ? _t1514->len : 0u;
            for (uint32_t _t1515 = 0; _t1515 < _len__t1515; ++_t1515) {
                gd::GdVal lv_food = _t1514->data[_t1515];
                (void)gd::call_method(gd_ctx, lv_food, SYM_GEN_doCooldownEffect_146, nullptr, 0);
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Eggscalibur::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Pan::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_addToInventory_122: return true;
        case SYM_GEN_onRemoveFromInventory_420: return true;
        case SYM_GEN_onCraft_1943: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_canAffect_secondary_289: return true;
        case SYM_GEN_onPreCombatStart_127: return true;
        case SYM_GEN_getRelatedItems_461: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Anvil::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_addToInventory_122: out = fn_addToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_420: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_onCraft_1943: out = fn_onCraft(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_289: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPreCombatStart_127: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_getRelatedItems_461: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {lv__inventory, lv__occupiedCells, lv__placedByPlayer}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_addToInventory_122, _ca, 3, _out); return _out; })();
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_isWeapon_84, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Anvil::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numCrafted = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0), gd::SYM_size, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numCrafted, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_bonusDamage = gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), lv_numCrafted);
        gd::GdVal lv_staminaReduction = gd::gd_mul(gd::gd_neg(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)), lv_numCrafted);
        {
            gd::GdVal _t1516 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, _ca, 1); })());
            gd::GdArr* _t1517 = (_t1516.kind == gd::GdVal::Kind::Arr) ? _t1516.arr : nullptr;
            uint32_t _len__t1518 = _t1517 ? _t1517->len : 0u;
            for (uint32_t _t1518 = 0; _t1518 < _len__t1518; ++_t1518) {
                gd::GdVal lv_affectedWeapon = _t1517->data[_t1518];
                if (gd::gd_truth(gd::call_method(gd_ctx, lv_affectedWeapon, SYM_GEN_canBeEmpowered_92, nullptr, 0))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_bonusDamage}; return gd::call_method(gd_ctx, lv_affectedWeapon, SYM_GEN_addBonusDamage_163, _ca, 1); })();
                    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_affectedWeapon, lv_bonusDamage, gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_playerId_1046)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_DamageBuff_1345, _ca, 4); })();
                    (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_logEvent_1328, _ca, 1); })();
                }
                (void)([&]() { gd::GdVal _ca[] = {lv_staminaReduction}; return gd::call_method(gd_ctx, lv_affectedWeapon, SYM_GEN_changeStaminaFactor_307, _ca, 1); })();
            }
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Anvil::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Flame", 5u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })()}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Anvil::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_affectedBagDescriptors_1959: out = this->f_affectedBagDescriptors; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Bagtacular::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedBagDescriptors_1959: this->f_affectedBagDescriptors = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Bagtacular::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_global_1919: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Bagtacular::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_global_1919: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_affectedBagDescriptors = ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 4); d->set(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Fanny Pack", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })(), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Stamina Sack", 12u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })(), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Potion Belt", 11u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })(), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Protective Purse", 16u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })(), gd::GdVal::from_bool(true)); return gd::GdVal::from_dict(d); })();
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
        case SYM_GEN_lucky_2000: out = this->f_lucky; return true;
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        case SYM_GEN_spellSpeed_1999: out = this->f_spellSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BookofNature::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_regenNeeded_942: this->f_regenNeeded = val; return true;
        case SYM_GEN_lucky_2000: this->f_lucky = val; return true;
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        case SYM_GEN_spellSpeed_1999: this->f_spellSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BookofNature::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BookofNature::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Spell_2607)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofNature::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_speed = gd::GdVal::from_float(0.0);
    {
        gd::GdVal _t1519 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1520 = (_t1519.kind == gd::GdVal::Kind::Arr) ? _t1519.arr : nullptr;
        uint32_t _len__t1521 = _t1520 ? _t1520->len : 0u;
        for (uint32_t _t1521 = 0; _t1521 < _len__t1521; ++_t1521) {
            gd::GdVal lv_item = _t1520->data[_t1521];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Nature_2597)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())) {
                lv_speed = gd::gd_add(gd_ctx, lv_speed, gd::gd_mul(this->f_spellSpeed, gd::GdVal::from_int(2LL)));
            }
            else {
                lv_speed = gd::gd_add(gd_ctx, lv_speed, this->f_spellSpeed);
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_speed}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofNature::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getRegeneration_1217, nullptr, 0), this->f_regenNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_regenNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_348, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_lucky, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_spikes, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_211, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofNature::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_regenNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_lucky = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_spellSpeed = gd::gd_div(gd_ctx, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })()), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_healColor_2023: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.384314), gd::GdVal::from_float(0.913725), gd::GdVal::from_float(0.423529)}; return gd::make_color_from_args(_ca, 3); })();
        case SYM_GEN_manaColor_2024: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.329412), gd::GdVal::from_float(0.392157), gd::GdVal::from_float(0.992157)}; return gd::make_color_from_args(_ca, 3); })();
        case SYM_GEN_heatColor_2025: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.996078), gd::GdVal::from_float(0.458824), gd::GdVal::from_float(0.290196)}; return gd::make_color_from_args(_ca, 3); })();
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
        case SYM_GEN_options_1781: out = this->f_options; return true;
        case SYM_GEN_healColor_2023: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_manaColor_2024: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_heatColor_2025: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Cauldron::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_options_1781: this->f_options = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Cauldron::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Cauldron::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Food_2606)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Potion_2652)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cauldron::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0), gd::GdVal::from_float(100.0)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cauldron::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rng = ([&]() { gd::GdVal _ca[] = {this->f_options}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_pickRandomElement_1650, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_rng, gd::GdVal::from_int(0LL))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_rng, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    (void)([&]() { gd::GdVal _ca[] = {lv_rng}; return gd::call_method(gd_ctx, this->f_options, gd::SYM_erase, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cauldron::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_regen_1904: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__WhitePawn::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_regen_1904: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__WhitePawn::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2050: return true;
        case SYM_GEN_doEliminatedEffect_2052: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__WhitePawn::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2050: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_doEliminatedEffect_2052: out = fn_doEliminatedEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhitePawn::fn_doEliminatedEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhitePawn::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
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
        case SYM_GEN_numBuffs_1910: out = this->f_numBuffs; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Cupcake::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numBuffs_1910: this->f_numBuffs = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Cupcake::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Cupcake::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Cupcake::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Cupcake::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {this->f_numBuffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMostBuffs_369, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cupcake::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_numBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
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
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onBattleRageStarted_1971: return true;
        case SYM_GEN_onBattleRageEnded_1972: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DragonClaws::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_1971: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN_onBattleRageEnded_1972: out = fn_onBattleRageEnded(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonClaws::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_started", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageStarted", 19u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_ended", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageEnded", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Poison_2567), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeResistChance_1025, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonClaws::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1522 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1523 = (_t1522.kind == gd::GdVal::Kind::Arr) ? _t1522.arr : nullptr;
        uint32_t _len__t1524 = _t1523 ? _t1523->len : 0u;
        for (uint32_t _t1524 = 0; _t1524 < _len__t1524; ++_t1524) {
            gd::GdVal lv_item = _t1523->data[_t1524];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), gd::GdVal::from_int(100LL))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_275, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonClaws::fn_onBattleRageEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1525 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1526 = (_t1525.kind == gd::GdVal::Kind::Arr) ? _t1525.arr : nullptr;
        uint32_t _len__t1527 = _t1526 ? _t1526->len : 0u;
        for (uint32_t _t1527 = 0; _t1527 < _len__t1527; ++_t1527) {
            gd::GdVal lv_item = _t1526->data[_t1527];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), gd::GdVal::from_int(100LL))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_276, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonClaws::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__EnchantedWeapons::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasAttackEffect_297, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EnchantedWeapons::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1528 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1529 = (_t1528.kind == gd::GdVal::Kind::Arr) ? _t1528.arr : nullptr;
        uint32_t _len__t1530 = _t1529 ? _t1529->len : 0u;
        for (uint32_t _t1530 = 0; _t1530 < _len__t1530; ++_t1530) {
            gd::GdVal lv_item = _t1529->data[_t1530];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveDoubleAttackEffectChance_315, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EnchantedWeapons::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLeastBuffs_368, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EnchantedWeapons::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_buffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
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
        case SYM_GEN_regen_1904: out = this->f_regen; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_damPerRegen_2167: out = this->f_damPerRegen; return true;
        case SYM_GEN_speedPerNature_2168: out = this->f_speedPerNature; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ForestDragon::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_regen_1904: this->f_regen = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_damPerRegen_2167: this->f_damPerRegen = val; return true;
        case SYM_GEN_speedPerNature_2168: this->f_speedPerNature = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ForestDragon::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onRegenChanged_1796: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ForestDragon::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onRegenChanged_1796: out = fn_onRegenChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Nature_2597)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ForestDragon::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_regeneration_changed", 30u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onRegenChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_speedPerNature, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ForestDragon::fn_onRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, this->f_damPerRegen)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_164, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ForestDragon::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ForestDragon::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_damPerRegen = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_speedPerNature = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_regen_1904: out = this->f_regen; return true;
        case SYM_GEN_speed_v_2083: out = this->f_speed_v; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__GirlPower::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        case SYM_GEN_regen_1904: this->f_regen = val; return true;
        case SYM_GEN_speed_v_2083: this->f_speed_v = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__GirlPower::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_isAffectingDistinct_256: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onItemRoll_1923: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__GirlPower::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_isAffectingDistinct_256: out = fn_isAffectingDistinct(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onItemRoll_1923: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__GirlPower::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__GirlPower::fn_isAffectingDistinct(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    return gd::GdVal::from_bool(gd::gd_eq(lv_color, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GirlPower::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_isClassItem_250, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GirlPower::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_speed_v, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumDistinctAffectedItems_432, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GirlPower::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_curEmpower = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getEmpower_1232, nullptr, 0);
    gd::GdVal lv_curRegen = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getRegeneration_1217, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_curRegen, lv_curEmpower)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_curRegen, lv_curEmpower)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_empower}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 1); })();
    }
    else {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_flip_1639, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {this->f_empower}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GirlPower::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GirlPower::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_speed_v = gd::gd_div(gd_ctx, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })()), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__GirlPower(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__GirlPower>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__GirlPower = {CLS_Gd__gd_core_items__Exclusive__GirlPower, "GirlPower", "res://gd_core_items/Exclusive/GirlPower.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__GirlPower, &Gd__gd_core_items__Exclusive__GirlPower::get_static_prop_fn, &Gd__gd_core_items__Exclusive__GirlPower::call_static_fn};

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
        case SYM_GEN_onDropped_1925: return true;
        case SYM_GEN_replaceWithCubes_2218: return true;
        case SYM_GEN_getTextureSize_781: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Hypercube::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDropped_1925: out = fn_onDropped(args, argc); return true;
        case SYM_GEN_replaceWithCubes_2218: out = fn_replaceWithCubes(args, argc); return true;
        case SYM_GEN_getTextureSize_781: out = fn_getTextureSize(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_dropRes}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core_items__Exclusive__Hypercube::call_static_fn(gd_ctx, SYM_GEN_wasAddedToInventory_659, _ca, 1, _out); return _out; })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Hypercube::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_AddedToStorageBox_2599)))))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_prepareReplacement_448, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "replaceWithCubes", 16u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_dropRes}))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1422, _ca, 3); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dropped", 7u)), gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDropped", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_connect, _ca, 3); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Hypercube(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Hypercube>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Hypercube = {CLS_Gd__gd_core_items__Exclusive__Hypercube, "Hypercube", "res://gd_core_items/Exclusive/Hypercube.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Hypercube, &Gd__gd_core_items__Exclusive__Hypercube::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Hypercube::call_static_fn};

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
        case SYM_GEN_onAddToInventory_421: return true;
        case SYM_GEN_onRemoveFromInventory_420: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onLuckyChanged_901: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_getRelatedItems_461: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__LeafBadge::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onAddToInventory_421: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_420: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onLuckyChanged_901: out = fn_onLuckyChanged(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getRelatedItems_461: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canDamage_91, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LeafBadge::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0), gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_lucky_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onLuckyChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LeafBadge::fn_onLuckyChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    {
        gd::GdVal _t1531 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1532 = (_t1531.kind == gd::GdVal::Kind::Arr) ? _t1531.arr : nullptr;
        uint32_t _len__t1533 = _t1532 ? _t1532->len : 0u;
        for (uint32_t _t1533 = 0; _t1533 < _len__t1533; ++_t1533) {
            gd::GdVal lv_item = _t1532->data[_t1533];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeCritChancePercent_183, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LeafBadge::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_speedPerAffected_2296: out = this->f_speedPerAffected; return true;
        case SYM_GEN_manaNeeded_1786: out = this->f_manaNeeded; return true;
        case SYM_GEN_numDebuffs_1953: out = this->f_numDebuffs; return true;
        case SYM_GEN_block2_1982: out = this->f_block2; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MagiteccArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_speedPerAffected_2296: this->f_speedPerAffected = val; return true;
        case SYM_GEN_manaNeeded_1786: this->f_manaNeeded = val; return true;
        case SYM_GEN_numDebuffs_1953: this->f_numDebuffs = val; return true;
        case SYM_GEN_block2_1982: this->f_block2 = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MagiteccArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MagiteccArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Magic_2721)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagiteccArmor::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0), this->f_speedPerAffected)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagiteccArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagiteccArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMana_1228, nullptr, 0), this->f_manaNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_334, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_numDebuffs, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_358, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_block2, gd::GdVal::from_bool(true), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 3); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagiteccArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_speedPerAffected = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "manat", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_numDebuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cleanse", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_block2 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "block", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
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
        case SYM_GEN_flyAgaricDescriptor_2316: out = this->f_flyAgaricDescriptor; return true;
        case SYM_GEN_doomCapDescriptor_2317: out = this->f_doomCapDescriptor; return true;
        case SYM_GEN_mushroomSpeed_2318: out = this->f_mushroomSpeed; return true;
        case SYM_GEN_mushroomsNeeded_2319: out = this->f_mushroomsNeeded; return true;
        case SYM_GEN_activeLight_2320: out = this->f_activeLight; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MushroomFarm::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_flyAgaricDescriptor_2316: this->f_flyAgaricDescriptor = val; return true;
        case SYM_GEN_doomCapDescriptor_2317: this->f_doomCapDescriptor = val; return true;
        case SYM_GEN_mushroomSpeed_2318: this->f_mushroomSpeed = val; return true;
        case SYM_GEN_mushroomsNeeded_2319: this->f_mushroomsNeeded = val; return true;
        case SYM_GEN_activeLight_2320: this->f_activeLight = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MushroomFarm::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onItemAdded_439: return true;
        case SYM_GEN_onItemRemoved_440: return true;
        case SYM_GEN_onRemoveFromInventory_420: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_isActive_2321: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onItemRoll_1923: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MushroomFarm::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onItemAdded_439: out = fn_onItemAdded(args, argc); return true;
        case SYM_GEN_onItemRemoved_440: out = fn_onItemRemoved(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_420: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_isActive_2321: out = fn_isActive(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onItemRoll_1923: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemAdded_439, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isActive_2321, nullptr, 0))) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MushroomFarm::fn_onItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemRemoved_440, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isActive_2321, nullptr, 0))))) {
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
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_flyAgaricDescriptor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_247, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_doomCapDescriptor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_247, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MushroomFarm::fn_isActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numMushrooms = ([&]() { gd::GdVal _ca[] = {this->f_flyAgaricDescriptor}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_countPlacedItemsInInventoryOfType_1574, _ca, 1); })();
    lv_numMushrooms = gd::gd_add(gd_ctx, lv_numMushrooms, ([&]() { gd::GdVal _ca[] = {this->f_doomCapDescriptor}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_countPlacedItemsInInventoryOfType_1574, _ca, 1); })());
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
        gd::GdVal _t1534 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1535 = (_t1534.kind == gd::GdVal::Kind::Arr) ? _t1534.arr : nullptr;
        uint32_t _len__t1536 = _t1535 ? _t1535->len : 0u;
        for (uint32_t _t1536 = 0; _t1536 < _len__t1536; ++_t1536) {
            gd::GdVal lv_mushroom = _t1535->data[_t1536];
            (void)([&]() { gd::GdVal _ca[] = {this->f_mushroomSpeed}; return gd::call_method(gd_ctx, lv_mushroom, SYM_GEN_addSpeed_275, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MushroomFarm::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MushroomFarm::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_flyAgaricDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Fly Agaric", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })();
    this->f_doomCapDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Doom Cap", 8u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })();
    this->f_mushroomSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_mushroomsNeeded = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "num", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
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
        case SYM_GEN_affectedItemsDict_2014: out = this->f_affectedItemsDict; return true;
        case SYM_GEN_gainedBuffs_2173: out = this->f_gainedBuffs; return true;
        case SYM_GEN_usedBuffs_2174: out = this->f_usedBuffs; return true;
        case SYM_GEN_gainedThreshold_2175: out = this->f_gainedThreshold; return true;
        case SYM_GEN_usedThreshold_2176: out = this->f_usedThreshold; return true;
        case SYM_GEN_poison_1867: out = this->f_poison; return true;
        case SYM_GEN_mana_1833: out = this->f_mana; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PoisonFrog::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedItemsDict_2014: this->f_affectedItemsDict = val; return true;
        case SYM_GEN_gainedBuffs_2173: this->f_gainedBuffs = gd::gd_coerce_int(val); return true;
        case SYM_GEN_usedBuffs_2174: this->f_usedBuffs = gd::gd_coerce_int(val); return true;
        case SYM_GEN_gainedThreshold_2175: this->f_gainedThreshold = gd::gd_coerce_int(val); return true;
        case SYM_GEN_usedThreshold_2176: this->f_usedThreshold = gd::gd_coerce_int(val); return true;
        case SYM_GEN_poison_1867: this->f_poison = val; return true;
        case SYM_GEN_mana_1833: this->f_mana = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PoisonFrog::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onBuffsChanged_1992: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_151: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PoisonFrog::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBuffsChanged_1992: out = fn_onBuffsChanged(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_151: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsBuffs_298, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_usesBuffs_299, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonFrog::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_affectedItemsDict, gd::SYM_clear, nullptr, 0);
    {
        gd::GdVal _t1537 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1538 = (_t1537.kind == gd::GdVal::Kind::Arr) ? _t1537.arr : nullptr;
        uint32_t _len__t1539 = _t1538 ? _t1538->len : 0u;
        for (uint32_t _t1539 = 0; _t1539 < _len__t1539; ++_t1539) {
            gd::GdVal lv_item = _t1538->data[_t1539];
            { gd::GdVal _t1540 = this->f_affectedItemsDict; gd::GdVal _t1541 = lv_item; gd::set_index(gd_ctx, _t1540, _t1541, gd::GdVal::from_bool(true)); }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBuffsChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterBuffs_376, _ca, 1); })();
    this->f_gainedBuffs = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_usedBuffs = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonFrog::fn_onBuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::gd_in(gd::call_method(gd_ctx, lv_event, SYM_GEN_getOrigin_1489, nullptr, 0), this->f_affectedItemsDict))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
            this->f_gainedBuffs = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_gainedBuffs, lv_amount));
            gd::GdVal lv_ticks = gd::gd_div(gd_ctx, this->f_gainedBuffs, this->f_gainedThreshold);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_ticks, gd::GdVal::from_int(0LL))))) {
                (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
                this->f_gainedBuffs = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_gainedBuffs, this->f_gainedThreshold));
                (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
            }
        }
        else {
            this->f_usedBuffs = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_usedBuffs, gd::gd_coerce_int(gd::gd_abs(lv_amount))));
            gd::GdVal lv_ticks = gd::gd_div(gd_ctx, this->f_usedBuffs, this->f_usedThreshold);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_ticks, gd::GdVal::from_int(0LL))))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_ticks, this->f_poison), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_213, _ca, 2); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_ticks, this->f_mana), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 2); })();
                this->f_usedBuffs = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_usedBuffs, this->f_usedThreshold));
                (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonFrog::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "poison2", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_213, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana2", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonFrog::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_pitch = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonFrog::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    gd::GdVal lv_pitch = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonFrog::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_gainedThreshold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gained", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_usedThreshold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "used", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_poison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "poison", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
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
        case SYM_GEN_puzzlebags_2352: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "L", 1u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "S", 1u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Z", 1u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "T", 1u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "J", 1u))}));
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
        case SYM_GEN_slowSpeed_2353: out = this->f_slowSpeed; return true;
        case SYM_GEN_fastSpeed_2354: out = this->f_fastSpeed; return true;
        case SYM_GEN_puzzlebags_2352: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Puzzlebox::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_slowSpeed_2353: this->f_slowSpeed = val; return true;
        case SYM_GEN_fastSpeed_2354: this->f_fastSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Puzzlebox::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_getReplaceDescriptor_1936: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Puzzlebox::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getReplaceDescriptor_1936: out = fn_getReplaceDescriptor(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_toItem, SYM_GEN_hasCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Puzzlebox::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1542 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_927, nullptr, 0));
        gd::GdArr* _t1543 = (_t1542.kind == gd::GdVal::Kind::Arr) ? _t1542.arr : nullptr;
        uint32_t _len__t1544 = _t1543 ? _t1543->len : 0u;
        for (uint32_t _t1544 = 0; _t1544 < _len__t1544; ++_t1544) {
            gd::GdVal lv_item = _t1543->data[_t1544];
            (void)([&]() { gd::GdVal _ca[] = {this->f_slowSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_276, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Puzzlebox::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1545 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_927, nullptr, 0));
        gd::GdArr* _t1546 = (_t1545.kind == gd::GdVal::Kind::Arr) ? _t1545.arr : nullptr;
        uint32_t _len__t1547 = _t1546 ? _t1546->len : 0u;
        for (uint32_t _t1547 = 0; _t1547 < _len__t1547; ++_t1547) {
            gd::GdVal lv_item = _t1546->data[_t1547];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_slowSpeed, this->f_fastSpeed)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_275, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_slowSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_fastSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed2", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Card::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Reverse::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_890: out = fn_cardSecondaryEffectActive(args, argc); return true;
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN_getCardDescription_895: out = fn_getCardDescription(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Reverse::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Reverse::fn_cardSecondaryEffectActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(this->f_deck) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(([&]() { gd::GdVal _ca[] = {this->f_chainPosition}; return gd::call_method(gd_ctx, this->f_deck, SYM_GEN_countDuplicates_1707, _ca, 1); })(), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Reverse::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "reflect", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveReflectStacks_202, _ca, 1); })();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cardSecondaryEffectActive_890, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "steal", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_375, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Reverse::fn_getCardDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(this->f_deck)) {
        gd::GdVal lv_duplicates = ([&]() { gd::GdVal _ca[] = {this->f_chainPosition}; return gd::call_method(gd_ctx, this->f_deck, SYM_GEN_countDuplicates_1707, _ca, 1); })();
        gd::GdVal lv_state = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_No_2548);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_duplicates, gd::GdVal::from_int(0LL))))) {
            lv_state = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_Positive_2549);
        }
        else {
            lv_state = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_Negative_2550);
        }
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n", 1u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "CARD_DUPLICATES", 15u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "num", 3u)), lv_duplicates, lv_state, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 5); })()));
    }
    else if (gd::gd_truth(this->f_placed)) {
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n", 1u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "CARD_HINT", 9u)), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_paramColor_2622)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_wrapInColor_2673, _ca, 2); })()));
    }
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Reverse::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Card::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_boostedShields_2394: out = this->f_boostedShields; return true;
        case SYM_GEN_shieldOfValorDescriptor_2395: out = this->f_shieldOfValorDescriptor; return true;
        case SYM_GEN_shieldChance_2396: out = this->f_shieldChance; return true;
        case SYM_GEN_armorSpeed_2397: out = this->f_armorSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Shielded::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_boostedShields_2394: this->f_boostedShields = val; return true;
        case SYM_GEN_shieldOfValorDescriptor_2395: this->f_shieldOfValorDescriptor = val; return true;
        case SYM_GEN_shieldChance_2396: this->f_shieldChance = val; return true;
        case SYM_GEN_armorSpeed_2397: this->f_armorSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Shielded::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_onBought_457: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onItemRoll_1923: return true;
        case SYM_GEN_onItemRolled_1924: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Shielded::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_onBought_457: out = fn_onBought(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemRoll_1923: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_1924: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Shield_2754)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Armor_2751)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_97, nullptr, 0))) : gd::GdVal::from_bool(false)))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Shielded::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1548 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1549 = (_t1548.kind == gd::GdVal::Kind::Arr) ? _t1548.arr : nullptr;
        uint32_t _len__t1550 = _t1549 ? _t1549->len : 0u;
        for (uint32_t _t1550 = 0; _t1550 < _len__t1550; ++_t1550) {
            gd::GdVal lv_item = _t1549->data[_t1550];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Shield_2754)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_shieldChance, gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusChance_additive_178, _ca, 2); })();
            }
            else {
                (void)([&]() { gd::GdVal _ca[] = {this->f_armorSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_275, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_shieldOfValorDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Shield of Valor", 15u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })();
    this->f_shieldChance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chance", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_armorSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_boosted_2101: out = this->f_boosted; return true;
        case SYM_GEN_sunShieldDescriptor_2423: out = this->f_sunShieldDescriptor; return true;
        case SYM_GEN_sunArmorDescriptor_2424: out = this->f_sunArmorDescriptor; return true;
        case SYM_GEN_holyArmorDescriptor_2425: out = this->f_holyArmorDescriptor; return true;
        case SYM_GEN_shieldOfValorDescriptor_2395: out = this->f_shieldOfValorDescriptor; return true;
        case SYM_GEN_heatPerShieldBlock_2426: out = this->f_heatPerShieldBlock; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Solaris::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_boosted_2101: this->f_boosted = val; return true;
        case SYM_GEN_sunShieldDescriptor_2423: this->f_sunShieldDescriptor = val; return true;
        case SYM_GEN_sunArmorDescriptor_2424: this->f_sunArmorDescriptor = val; return true;
        case SYM_GEN_holyArmorDescriptor_2425: this->f_holyArmorDescriptor = val; return true;
        case SYM_GEN_shieldOfValorDescriptor_2395: this->f_shieldOfValorDescriptor = val; return true;
        case SYM_GEN_heatPerShieldBlock_2426: this->f_heatPerShieldBlock = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Solaris::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onBought_457: return true;
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onArmorUsedHeat_2427: return true;
        case SYM_GEN_onShieldBlocked_2428: return true;
        case SYM_GEN_onItemRoll_1923: return true;
        case SYM_GEN_onItemRolled_1924: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Solaris::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onBought_457: out = fn_onBought(args, argc); return true;
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onArmorUsedHeat_2427: out = fn_onArmorUsedHeat(args, argc); return true;
        case SYM_GEN_onShieldBlocked_2428: out = fn_onShieldBlocked(args, argc); return true;
        case SYM_GEN_onItemRoll_1923: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_1924: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_sunShieldDescriptor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_247, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_sunArmorDescriptor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_247, _ca, 1); })())));
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
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Heat_2573), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_174, nullptr, 0)}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_changeBuffAmplification_allItems_1525, _ca, 2); })();
    {
        gd::GdVal _t1551 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1552 = (_t1551.kind == gd::GdVal::Kind::Arr) ? _t1551.arr : nullptr;
        uint32_t _len__t1553 = _t1552 ? _t1552->len : 0u;
        for (uint32_t _t1553 = 0; _t1553 < _len__t1553; ++_t1553) {
            gd::GdVal lv_item = _t1552->data[_t1553];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_sunShieldDescriptor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_247, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blocked", 7u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onShieldBlocked", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
            }
            else {
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "used_heat", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onArmorUsedHeat", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Solaris::fn_onArmorUsedHeat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0), gd::GdVal::from_bool(true), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 3); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Solaris::fn_onShieldBlocked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_blockedDamageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_heatPerShieldBlock}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_sunShieldDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Sun Shield", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })();
    this->f_sunArmorDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Sun Armor", 9u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })();
    this->f_holyArmorDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Holy Armor", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })();
    this->f_shieldOfValorDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Shield of Valor", 15u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })();
    this->f_heatPerShieldBlock = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
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
        case SYM_GEN_numActivations_1809: out = this->f_numActivations; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_manaCost_1720: out = this->f_manaCost; return true;
        case SYM_GEN_heatCost_2451: out = this->f_heatCost; return true;
        case SYM_GEN_damBonus_1830: out = this->f_damBonus; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__StaffofFire::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numActivations_1809: this->f_numActivations = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_manaCost_1720: this->f_manaCost = gd::gd_coerce_int(val); return true;
        case SYM_GEN_heatCost_2451: this->f_heatCost = gd::gd_coerce_int(val); return true;
        case SYM_GEN_damBonus_1830: this->f_damBonus = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__StaffofFire::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__StaffofFire::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getHeat_1235, nullptr, 0), this->f_heatCost)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_335, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_event, gd::GdVal::null())))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_heatCost, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useHeat_356, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_damBonus}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_163, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_manaCost = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0));
    this->f_heatCost = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0));
    this->f_damBonus = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__StaffofFire(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__StaffofFire>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StaffofFire = {CLS_Gd__gd_core_items__Exclusive__StaffofFire, "StaffofFire", "res://gd_core_items/Exclusive/StaffofFire.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__StaffofFire, &Gd__gd_core_items__Exclusive__StaffofFire::get_static_prop_fn, &Gd__gd_core_items__Exclusive__StaffofFire::call_static_fn};

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
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ThornShortbow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_211, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThornShortbow::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ThornShortbow(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ThornShortbow>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ThornShortbow = {CLS_Gd__gd_core_items__Exclusive__ThornShortbow, "ThornShortbow", "res://gd_core_items/Exclusive/ThornShortbow.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__ThornShortbow, &Gd__gd_core_items__Exclusive__ThornShortbow::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ThornShortbow::call_static_fn};

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
        case SYM_GEN_skillPool_2506: out = this->f_skillPool; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__UnidentifiedSkill::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_skillPool_2506: this->f_skillPool = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__UnidentifiedSkill::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getSkillPool_2507: return true;
        case SYM_GEN_onDropped_1925: return true;
        case SYM_GEN_identifySkill_2508: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_getRelatedItems_461: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN_getRelatedItemHeight_700: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__UnidentifiedSkill::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getSkillPool_2507: out = fn_getSkillPool(args, argc); return true;
        case SYM_GEN_onDropped_1925: out = fn_onDropped(args, argc); return true;
        case SYM_GEN_identifySkill_2508: out = fn_identifySkill(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_getRelatedItems_461: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_700: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_dropRes}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core_items__Exclusive__UnidentifiedSkill::call_static_fn(gd_ctx, SYM_GEN_wasAddedToInventory_659, _ca, 1, _out); return _out; })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__UnidentifiedSkill::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_AddedToStorageBox_2599)))))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_prepareReplacement_448, nullptr, 0);
        gd::GdVal lv_skill = ([&]() { gd::GdVal _ca[] = {this->f_skillPool, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Exclusive/UnidentifiedSkill.gd:23", 33u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_pickRandomEngine_1652, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "identifySkill", 13u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_dropRes, lv_skill}))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1422, _ca, 3); })();
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
        lv_string = ([&]() { gd::GdVal _ca[] = {([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 2); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "round1", 6u)), gd::GdVal::null()); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "round2", 6u)), gd::GdVal::null()); return gd::GdVal::from_dict(d); })()}; return gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "TOOLTIP_Always Offered2", 23u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_tr_2719, _ca, 1); })(), SYM_GEN_format_2621, _ca, 1); })();
    }
    else {
        lv_string = ([&]() { gd::GdVal _ca[] = {([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 2); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "round1", 6u)), gd::get_index(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_appearRounds_2720), gd::GdVal::from_int(0LL))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "round2", 6u)), gd::get_index(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_appearRounds_2720), gd::GdVal::from_int(1LL))); return gd::GdVal::from_dict(d); })()}; return gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "TOOLTIP_Always Offered2", 23u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_tr_2719, _ca, 1); })(), SYM_GEN_format_2621, _ca, 1); })();
    }
    lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n\n", 2u)), lv_string));
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dropped", 7u)), gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDropped", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_connect, _ca, 3); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_Shop_2579))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "getSkillPool", 12u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1422, _ca, 3); })();
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
        case SYM_GEN_luckNeeded_1779: out = this->f_luckNeeded; return true;
        case SYM_GEN_bonusDam_1780: out = this->f_bonusDam; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__FancyFencingRapier::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_luckNeeded_1779: this->f_luckNeeded = val; return true;
        case SYM_GEN_bonusDam_1780: this->f_bonusDam = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__FancyFencingRapier::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__FancyFencingRapier::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_luckNeeded, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseLucky_349, _ca, 2); })())) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusDam}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_163, _ca, 1); })();
        }
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__FancyFencingRapier::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luckt", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_bonusDam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
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
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Hammer::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onFusingAsCatalystFinished_843: out = fn_onFusingAsCatalystFinished(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_stun", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_332, _ca, 2); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__LuckyClover::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__LuckyClover::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__LuckyClover::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_383, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyClover::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__PoisonGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__PoisonGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__PoisonGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_213, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_addToInventory_122: return true;
        case SYM_GEN_onRemoveFromInventory_420: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__StaminaSack::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_addToInventory_122: out = fn_addToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_420: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {lv__inventory, lv__occupiedCells, lv__placedByPlayer}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN_addToInventory_122, _ca, 3, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_PlayerInventory_2555))))) {
        (void)gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeBaseMaxStamina_1256, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaminaSack::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN_onRemoveFromInventory_420, nullptr, 0, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_BuildViewer_2554))))) {
        (void)gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeBaseMaxStamina_1256, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaminaSack::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Bagtacular", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isTypeInInventory_805, _ca, 1); })())) {
        gd::GdVal lv_stamina = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Bagtacular", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })(), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
        (void)([&]() { gd::GdVal _ca[] = {lv_stamina}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_giveStaminaRegeneration_1254, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaminaSack::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPreCombatStart_127: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__VillainSword::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPreCombatStart_127: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_92, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), SYM_GEN_isMeleeWeapon_1626, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__VillainSword::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1554 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1555 = (_t1554.kind == gd::GdVal::Kind::Arr) ? _t1554.arr : nullptr;
        uint32_t _len__t1556 = _t1555 ? _t1555->len : 0u;
        for (uint32_t _t1556 = 0; _t1556 < _len__t1556; ++_t1556) {
            gd::GdVal lv_item = _t1555->data[_t1556];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceBonusDamage_312, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_163, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__VillainSword::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__VillainSword(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__VillainSword>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__VillainSword = {CLS_Gd__gd_core_items__VillainSword, "VillainSword", "res://gd_core_items/VillainSword.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__VillainSword, &Gd__gd_core_items__VillainSword::get_static_prop_fn, &Gd__gd_core_items__VillainSword::call_static_fn};
