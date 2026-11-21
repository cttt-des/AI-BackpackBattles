#include "../../native_inline_dispatch.hpp"
#include "../../native_scalar_equal.hpp"
#include "../../native_array_index.hpp"
#include "../../native_event_kernel.hpp"
#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core_items__Stone.hpp"
#include "../hdrs/Gd__gd_core__BowandArrow.hpp"
#include "../hdrs/Gd__gd_core__CoreContext.hpp"
#include "../hdrs/Gd__gd_core__CoreUtil.hpp"
#include "../hdrs/Gd__gd_core__DjinnLamp.hpp"
#include "../hdrs/Gd__gd_core__Hammer.hpp"
#include "../hdrs/Gd__gd_core__LeatherHelm.hpp"
#include "../hdrs/Gd__gd_core__Pandamonium.hpp"
#include "../hdrs/Gd__gd_core__RainbowGoobertRanger.hpp"
#include "../hdrs/Gd__gd_core__StoneHelm.hpp"
#include "../hdrs/Gd__gd_core__VampiricArmor.hpp"
#include "../hdrs/Gd__gd_core_items__ArtifactStoneHeat.hpp"
#include "../hdrs/Gd__gd_core_items__BurningCoal.hpp"
#include "../hdrs/Gd__gd_core_items__DeathScythe.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__AmuletofLight.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Axe.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Bomb.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BurningSpikes.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Chess__BlackQueen.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ConTrapTron.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DivinePotion.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ElephantRune.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Shelly.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__FullBodyProtection.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__HeroShield.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__KingCrown.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MagicBadge.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MoltenSpear.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PiggyofRiches.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PuzzlebagJ.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__RatChef.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SerpentStaff.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Snowball.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SpintoWin.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__StrongVampiricPotion.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Turtle.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Wisp.hpp"
#include "../hdrs/Gd__gd_core_items__Gems__Sapphire.hpp"
#include "../hdrs/Gd__gd_core_items__Item__INNER__SignalConnection.hpp"
#include "../hdrs/Gd__gd_core_items__Item.hpp"
#include "../hdrs/Gd__gd_core_items__Pineapple.hpp"
#include "../hdrs/Gd__gd_core_items__ShieldofValor.hpp"
#include "../hdrs/Gd__gd_core_items__ThornWhip.hpp"

namespace {
constexpr gd::GdStr battle_string_literals[] = {
    {"Magic Torch", 11u, 3028014630u},
    {"playAni", 7u, 2857835395u},
    {"flickerPlayAni", 14u, 3538297413u},
    {"limits", 6u, 1434716869u},
    {"position_precise", 16u, 2699138524u},
    {"position", 8u, 2471448074u},
    {"speed_precise", 13u, 2966176314u},
    {"speed", 5u, 2072037248u},
    {"length", 6u, 2211460629u},
    {"playing", 7u, 1911511093u},
    {"inside_tree", 11u, 1323489178u},
    {"loop", 4u, 3723446379u},
    {"native_opponent", 15u, 3386825342u},
    {"pending", 7u, 2579463996u},
    {"order", 5u, 1932267671u},
    {"left_at_first_physics", 21u, 1970080515u},
    {"left", 4u, 306900080u},
    {"_scene_delay_created_before", 27u, 2650176357u},
    {"sort", 4u, 69978321u},
    {"res://gd_core/CoreItemData.gd", 29u, 2751029636u},
    {"character_block_changed", 23u, 4278945901u},
    {"checkStacks", 11u, 2317645022u},
    {"character_spikes_changed", 24u, 3463900413u},
    {"character_mana_changed", 22u, 798563205u},
    {"character_lucky_changed", 23u, 2259242176u},
    {"character_damaged", 17u, 745527748u},
    {"character_healed", 16u, 2989261042u},
    {"dur_stun", 8u, 1388942617u},
    {"dur", 3u, 3509645056u},
    {"BuffTimer", 9u, 194754125u},
    {"buffEnded", 9u, 3457903416u},
    {"activated", 9u, 2866667388u},
    {"onFoodActivated", 15u, 3933616099u},
    {"character_heat_changed", 22u, 2413560104u},
    {"onHeatChanged", 13u, 775078454u},
    {"pre_deal_damage_early", 21u, 2143897571u},
    {"preAttack", 9u, 3919347442u},
    {"character_poison_changed", 24u, 65736246u},
    {"onOpponentPoisonChanged", 23u, 839266911u},
    {"character_regeneration_changed", 30u, 2797934681u},
    {"onRegenChanged", 14u, 661197895u},
    {"onItemActivated", 15u, 1109670618u},
    {"maxhealth", 9u, 429334299u},
    {"regen", 5u, 16724762u},
    {"dam", 3u, 4031722721u},
    {"onSpikesChanged", 15u, 3715123341u},
    {"spikes", 6u, 439106706u},
    {"heat", 4u, 577319571u},
    {"spikest", 7u, 430169618u},
    {"heat2", 5u, 3432690547u},
    {"buffs", 5u, 2149256365u},
    {"onDamaged", 9u, 2303747743u},
    {"charge_emitted", 14u, 395874890u},
    {"cdadvance_base", 14u, 2920893812u},
    {"cdadvance_bonus", 15u, 1251334440u},
    {"healtht", 7u, 1555997217u},
    {"debuffsChanged", 14u, 3997517480u},
    {"attacked", 8u, 3381721668u},
    {"onAttack", 8u, 3086142220u},
    {"dur_resist", 10u, 3688391055u},
    {"DebuffResistTimer", 17u, 3673119626u},
    {"removeDebuffResistance", 22u, 3142924366u},
    {"debuffs", 7u, 504032524u},
    {"pre_take_damage", 15u, 2330033632u},
    {"preTakeDamage", 13u, 311913432u},
    {"block", 5u, 3943480674u},
    {"damreduction", 12u, 2823666870u},
    {"damfactor", 9u, 2846421882u},
    {"gempower", 8u, 2277473285u},
    {"mana", 4u, 3650585354u},
    {"blockremoval", 12u, 875496666u},
    {"missdam", 7u, 948357613u},
    {"heatt", 5u, 312156581u},
    {"Box of Riches", 13u, 862823567u},
    {"_BAGEFFECT", 10u, 2435072665u},
    {"p_bonusdur", 10u, 1594576674u},
    {"bonusdur", 8u, 3225794759u},
    {"stamina", 7u, 3875003702u},
    {"empower", 7u, 2037162760u},
    {"poison", 6u, 3470992305u},
    {"damforpoison", 12u, 1823512596u},
    {"cold", 4u, 3930381583u},
    {"healthreduction", 15u, 4039077536u},
    {"luck", 4u, 4145017712u},
    {"character_attacked", 18u, 2439462988u},
    {"onOpponentDamaged", 17u, 568571164u},
    {"lifesteal", 9u, 1515578962u},
    {"LifestealTimer", 14u, 794105395u},
    {"onLifestealTimeout", 18u, 1877175488u},
    {"damblock", 8u, 2582642454u},
    {"bonus_damblock", 14u, 2046587890u},
    {"block2", 6u, 1426982128u},
    {"pre_deal_damage_late", 20u, 1012238672u},
    {"onManaChanged", 13u, 3105672029u},
};
}

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
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Stone::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
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
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Stone::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Stone::fn_combatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_combatEnd_131, nullptr, 0, _out); return _out; })();
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
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_preHit_907, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Stone::fn_preHit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeBlock_205, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Stone::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_ammunition, gd::GdVal::from_int(1LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
        this->f_ammunition = gd::gd_coerce_int(gd::gd_sub(this->f_ammunition, gd::GdVal::from_int(1LL)));
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
gd::GdVal Gd__gd_core_items__Stone::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onHit_909, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Stone::fn_onHit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Stone::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1550, _ca, 1); })();
    this->f_ammunition = gd::gd_coerce_int(gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Stone(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Stone>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,640u); return object; }
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
        case SYM_GEN_hasAttackEffect_295: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onWeaponAttacked_950: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Bow::has_own_method(m);
}
bool Gd__gd_core__BowandArrow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_hasAttackEffect_295: out = fn_hasAttackEffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_950: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BowandArrow::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        gd::GdVal lv_dmgAdded = gd::GdVal::from_bool(false);
        gd::GdVal lv_attackEffectCount = gd::gd_add(gd_ctx, gd::GdVal::from_int(1LL), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollDoubleAttackEffect_187, nullptr, 0));
        {
            gd::GdVal _t1112 = gd::gd_iter_seq(gd_ctx.arena, lv_attackEffectCount);
            gd::GdArr* _t1113 = (_t1112.kind == gd::GdVal::Kind::Arr) ? _t1112.arr : nullptr;
            uint32_t _len__t1114 = _t1113 ? _t1113->len : 0u;
            for (uint32_t _t1114 = 0; _t1114 < _len__t1114; ++_t1114) {
                gd::GdVal lv_i = _t1113->data[_t1114];
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_bonusDmg, this->f_maxDmg)))) {
                    this->f_bonusDmg = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_bonusDmg, this->f_bonusDmgPerHit));
                    (void)([&]() { gd::GdVal _ca[] = {this->f_bonusDmgPerHit}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
                    lv_dmgAdded = gd::GdVal::from_bool(true);
                }
            }
        }
        if (gd::gd_truth(lv_dmgAdded)) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusDmg, gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BowandArrow::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bow::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_bonusDmgPerHit = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    this->f_maxDmg = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__BowandArrow(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__BowandArrow>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,13u); return object; }
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
    this->f_show_cooldown_progress = gd::GdVal::from_bool(false);
    this->f__deferred = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f__idle_frame_calls = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f__timed = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_deferred_flush_enabled = gd::GdVal::from_bool(true);
    this->f_eb_relay_mirrored = gd::GdVal::from_bool(false);
    this->f_keyed_stop_clears_seen = gd::GdVal::from_bool(false);
    this->f_keyed_cleanse_biggest_first = gd::GdVal::from_bool(false);
    this->f__emptyGrid = gd::GdVal::null();
    this->f_activation_rng_state = gd::GdVal::null();
    this->f_idle_timer_initial = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_timer_pass_epoch = gd::GdVal::from_int(0LL);
    this->f_in_physics_timer_pass = gd::GdVal::from_bool(false);
    this->f_in_item_physics_pass = gd::GdVal::from_bool(false);
    this->f_replay_buff_state = gd::GdVal::null();
    this->f_replay_engine_rng = gd::GdVal::null();
    this->f_native_frame_rng = gd::GdVal::from_bool(false);
    this->f_native_label_mode = gd::GdVal::from_int(0LL);
    this->f_training_start = gd::GdVal::from_bool(false);
    this->f_replay_native_scene_delays = gd::GdVal::from_bool(false);
    this->f__opening_delay_ready = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_replay_util_time = gd::GdVal::from_float(0.0);
    this->f__critical_shake_delta = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f__critical_shake_active = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(0LL), gd::GdVal::from_int(0LL)}));
    this->f__critical_shake_frame = gd::GdVal::from_int(0LL);
    this->f__critical_shake_after_idle = gd::GdVal::from_bool(true);
    this->f__particle_draws = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_particle_draw_frame = gd::GdVal::from_int(0LL);
    this->f__particle_pending_draws = gd::GdVal::from_int(0LL);
    this->f__particle_before_physics = gd::GdVal::from_int(0LL);
    this->f__motion_queue = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_flicker_initial = gd::GdVal::null();
    this->f__flickers = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f__opponent_flickers = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
}
const gd::GdClassMeta* Gd__gd_core__CoreContext::meta() const { return &META_Gd__gd_core__CoreContext; }
gd::GdVal Gd__gd_core__CoreContext::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_PHYSICS_FPS_1403: return gd::GdVal::from_float(60.0);
        case SYM_GEN_PHYSICS_DELTA_1404: return gd::GdVal::from_float(0.01666666753590107);
        case SYM_GEN_COMBAT_DELAY_1405: return gd::GdVal::from_float(2.5);
        case SYM_GEN_FATIGUE_TIME_1299: return gd::GdVal::from_int(17LL);
        case SYM_GEN_CRITICAL_SHAKE_WINDOW_1456: return gd::GdVal::from_int(72LL);
        case SYM_GEN_MEGA_CLOVER_PARTICLE_DRAWS_1461: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(20LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(0LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL)}));
        case SYM_GEN_LOVERS_PARTICLE_DRAWS_1462: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(20LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(0LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL)}));
        case SYM_GEN_LOVERS_PARTICLE_RESTART_DRAWS_1463: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(0LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL), gd::GdVal::from_int(10LL)}));
        case SYM_GEN_NativeFlicker_1509: return gd::GdVal::from_cls(&META_Gd__gd_core__CoreContext__INNER__NativeFlicker);
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
        case SYM_GEN_rng_1406: out = this->f_rng; return true;
        case SYM_GEN_util_1407: out = this->f_util; return true;
        case SYM_GEN_bus_1408: out = this->f_bus; return true;
        case SYM_GEN_hooks_1409: out = this->f_hooks; return true;
        case SYM_GEN_combat_log_1410: out = this->f_combat_log; return true;
        case SYM_GEN_player_1302: out = this->f_player; return true;
        case SYM_GEN_opponent_75: out = this->f_opponent; return true;
        case SYM_GEN_fight_ended_1305: out = this->f_fight_ended; return true;
        case SYM_GEN_time_1411: out = this->f_time; return true;
        case SYM_GEN_probe_pass_1412: out = this->f_probe_pass; return true;
        case SYM_GEN_frame_counter_1413: out = this->f_frame_counter; return true;
        case SYM_GEN_combat_time_1306: out = this->f_combat_time; return true;
        case SYM_GEN_below_master_1414: out = this->f_below_master; return true;
        case SYM_GEN_label_rng_enabled_1415: out = this->f_label_rng_enabled; return true;
        case SYM_GEN_lobbies_mode_1416: out = this->f_lobbies_mode; return true;
        case SYM_GEN_custom_health_multiplier_1417: out = this->f_custom_health_multiplier; return true;
        case SYM_GEN__drawseq_enabled_1418: out = this->f__drawseq_enabled; return true;
        case SYM_GEN_lib_fires_1419: out = this->f_lib_fires; return true;
        case SYM_GEN_combat_1420: out = this->f_combat; return true;
        case SYM_GEN_item_book_1421: out = this->f_item_book; return true;
        case SYM_GEN_sandbag_active_1422: out = this->f_sandbag_active; return true;
        case SYM_GEN_cur_mode_1423: out = this->f_cur_mode; return true;
        case SYM_GEN_cur_round_1424: out = this->f_cur_round; return true;
        case SYM_GEN_rope_speedups_1425: out = this->f_rope_speedups; return true;
        case SYM_GEN_cube_advanced_1426: out = this->f_cube_advanced; return true;
        case SYM_GEN_event_type_keys_1427: out = this->f_event_type_keys; return true;
        case SYM_GEN_class_resources_1428: out = this->f_class_resources; return true;
        case SYM_GEN_unhealingDamageSource_1429: out = this->f_unhealingDamageSource; return true;
        case SYM_GEN_fatigueDamageSource_1430: out = this->f_fatigueDamageSource; return true;
        case SYM_GEN_stealLifeDamageSource_1431: out = this->f_stealLifeDamageSource; return true;
        case SYM_GEN_out_of_stamina_count_1432: out = this->f_out_of_stamina_count; return true;
        case SYM_GEN_warn_unknown_api_1433: out = this->f_warn_unknown_api; return true;
        case SYM_GEN_show_cooldown_progress_1434: out = this->f_show_cooldown_progress; return true;
        case SYM_GEN__deferred_1435: out = this->f__deferred; return true;
        case SYM_GEN__idle_frame_calls_1436: out = this->f__idle_frame_calls; return true;
        case SYM_GEN__timed_1437: out = this->f__timed; return true;
        case SYM_GEN_deferred_flush_enabled_1438: out = this->f_deferred_flush_enabled; return true;
        case SYM_GEN_eb_relay_mirrored_1439: out = this->f_eb_relay_mirrored; return true;
        case SYM_GEN_keyed_stop_clears_seen_1440: out = this->f_keyed_stop_clears_seen; return true;
        case SYM_GEN_keyed_cleanse_biggest_first_1441: out = this->f_keyed_cleanse_biggest_first; return true;
        case SYM_GEN__emptyGrid_1442: out = this->f__emptyGrid; return true;
        case SYM_GEN_activation_rng_state_1443: out = this->f_activation_rng_state; return true;
        case SYM_GEN_idle_timer_initial_1444: out = this->f_idle_timer_initial; return true;
        case SYM_GEN_timer_pass_epoch_1445: out = this->f_timer_pass_epoch; return true;
        case SYM_GEN_in_physics_timer_pass_1446: out = this->f_in_physics_timer_pass; return true;
        case SYM_GEN_in_item_physics_pass_1447: out = this->f_in_item_physics_pass; return true;
        case SYM_GEN_replay_buff_state_1448: out = this->f_replay_buff_state; return true;
        case SYM_GEN_replay_engine_rng_1449: out = this->f_replay_engine_rng; return true;
        case SYM_GEN_native_frame_rng_1450: out = this->f_native_frame_rng; return true;
        case SYM_GEN_native_label_mode_1451: out = this->f_native_label_mode; return true;
        case SYM_GEN_training_start_1452: out = this->f_training_start; return true;
        case SYM_GEN_replay_native_scene_delays_1453: out = this->f_replay_native_scene_delays; return true;
        case SYM_GEN__opening_delay_ready_1454: out = this->f__opening_delay_ready; return true;
        case SYM_GEN_replay_util_time_1455: out = this->f_replay_util_time; return true;
        case SYM_GEN__critical_shake_delta_1457: out = this->f__critical_shake_delta; return true;
        case SYM_GEN__critical_shake_active_1458: out = this->f__critical_shake_active; return true;
        case SYM_GEN__critical_shake_frame_1459: out = this->f__critical_shake_frame; return true;
        case SYM_GEN__critical_shake_after_idle_1460: out = this->f__critical_shake_after_idle; return true;
        case SYM_GEN__particle_draws_1464: out = this->f__particle_draws; return true;
        case SYM_GEN_particle_draw_frame_1465: out = this->f_particle_draw_frame; return true;
        case SYM_GEN__particle_pending_draws_1466: out = this->f__particle_pending_draws; return true;
        case SYM_GEN__particle_before_physics_1467: out = this->f__particle_before_physics; return true;
        case SYM_GEN__motion_queue_1468: out = this->f__motion_queue; return true;
        case SYM_GEN_flicker_initial_1469: out = this->f_flicker_initial; return true;
        case SYM_GEN__flickers_1470: out = this->f__flickers; return true;
        case SYM_GEN__opponent_flickers_1471: out = this->f__opponent_flickers; return true;
        case SYM_GEN_NativeFlicker_1509: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreContext__INNER__NativeFlicker); return true;
        case SYM_GEN_PHYSICS_FPS_1403: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_PHYSICS_DELTA_1404: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_COMBAT_DELAY_1405: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_FATIGUE_TIME_1299: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_CRITICAL_SHAKE_WINDOW_1456: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_MEGA_CLOVER_PARTICLE_DRAWS_1461: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_LOVERS_PARTICLE_DRAWS_1462: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_LOVERS_PARTICLE_RESTART_DRAWS_1463: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreContext::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_rng_1406: this->f_rng = val; return true;
        case SYM_GEN_util_1407: this->f_util = val; return true;
        case SYM_GEN_bus_1408: this->f_bus = val; return true;
        case SYM_GEN_hooks_1409: this->f_hooks = val; return true;
        case SYM_GEN_combat_log_1410: this->f_combat_log = val; return true;
        case SYM_GEN_player_1302: this->f_player = val; return true;
        case SYM_GEN_opponent_75: this->f_opponent = val; return true;
        case SYM_GEN_fight_ended_1305: this->f_fight_ended = val; return true;
        case SYM_GEN_time_1411: this->f_time = val; return true;
        case SYM_GEN_probe_pass_1412: this->f_probe_pass = val; return true;
        case SYM_GEN_frame_counter_1413: this->f_frame_counter = val; return true;
        case SYM_GEN_combat_time_1306: this->f_combat_time = val; return true;
        case SYM_GEN_below_master_1414: this->f_below_master = val; return true;
        case SYM_GEN_label_rng_enabled_1415: this->f_label_rng_enabled = val; return true;
        case SYM_GEN_lobbies_mode_1416: this->f_lobbies_mode = val; return true;
        case SYM_GEN_custom_health_multiplier_1417: this->f_custom_health_multiplier = val; return true;
        case SYM_GEN__drawseq_enabled_1418: this->f__drawseq_enabled = val; return true;
        case SYM_GEN_lib_fires_1419: this->f_lib_fires = val; return true;
        case SYM_GEN_combat_1420: this->f_combat = val; return true;
        case SYM_GEN_item_book_1421: this->f_item_book = val; return true;
        case SYM_GEN_sandbag_active_1422: this->f_sandbag_active = val; return true;
        case SYM_GEN_cur_mode_1423: this->f_cur_mode = val; return true;
        case SYM_GEN_cur_round_1424: this->f_cur_round = val; return true;
        case SYM_GEN_rope_speedups_1425: this->f_rope_speedups = val; return true;
        case SYM_GEN_cube_advanced_1426: this->f_cube_advanced = val; return true;
        case SYM_GEN_event_type_keys_1427: this->f_event_type_keys = val; return true;
        case SYM_GEN_class_resources_1428: this->f_class_resources = val; return true;
        case SYM_GEN_unhealingDamageSource_1429: this->f_unhealingDamageSource = val; return true;
        case SYM_GEN_fatigueDamageSource_1430: this->f_fatigueDamageSource = val; return true;
        case SYM_GEN_stealLifeDamageSource_1431: this->f_stealLifeDamageSource = val; return true;
        case SYM_GEN_out_of_stamina_count_1432: this->f_out_of_stamina_count = val; return true;
        case SYM_GEN_warn_unknown_api_1433: this->f_warn_unknown_api = val; return true;
        case SYM_GEN_show_cooldown_progress_1434: this->f_show_cooldown_progress = val; return true;
        case SYM_GEN__deferred_1435: this->f__deferred = val; return true;
        case SYM_GEN__idle_frame_calls_1436: this->f__idle_frame_calls = val; return true;
        case SYM_GEN__timed_1437: this->f__timed = val; return true;
        case SYM_GEN_deferred_flush_enabled_1438: this->f_deferred_flush_enabled = val; return true;
        case SYM_GEN_eb_relay_mirrored_1439: this->f_eb_relay_mirrored = val; return true;
        case SYM_GEN_keyed_stop_clears_seen_1440: this->f_keyed_stop_clears_seen = val; return true;
        case SYM_GEN_keyed_cleanse_biggest_first_1441: this->f_keyed_cleanse_biggest_first = val; return true;
        case SYM_GEN__emptyGrid_1442: this->f__emptyGrid = val; return true;
        case SYM_GEN_activation_rng_state_1443: this->f_activation_rng_state = val; return true;
        case SYM_GEN_idle_timer_initial_1444: this->f_idle_timer_initial = val; return true;
        case SYM_GEN_timer_pass_epoch_1445: this->f_timer_pass_epoch = val; return true;
        case SYM_GEN_in_physics_timer_pass_1446: this->f_in_physics_timer_pass = val; return true;
        case SYM_GEN_in_item_physics_pass_1447: this->f_in_item_physics_pass = val; return true;
        case SYM_GEN_replay_buff_state_1448: this->f_replay_buff_state = val; return true;
        case SYM_GEN_replay_engine_rng_1449: this->f_replay_engine_rng = val; return true;
        case SYM_GEN_native_frame_rng_1450: this->f_native_frame_rng = val; return true;
        case SYM_GEN_native_label_mode_1451: this->f_native_label_mode = val; return true;
        case SYM_GEN_training_start_1452: this->f_training_start = val; return true;
        case SYM_GEN_replay_native_scene_delays_1453: this->f_replay_native_scene_delays = val; return true;
        case SYM_GEN__opening_delay_ready_1454: this->f__opening_delay_ready = val; return true;
        case SYM_GEN_replay_util_time_1455: this->f_replay_util_time = val; return true;
        case SYM_GEN__critical_shake_delta_1457: this->f__critical_shake_delta = val; return true;
        case SYM_GEN__critical_shake_active_1458: this->f__critical_shake_active = val; return true;
        case SYM_GEN__critical_shake_frame_1459: this->f__critical_shake_frame = val; return true;
        case SYM_GEN__critical_shake_after_idle_1460: this->f__critical_shake_after_idle = val; return true;
        case SYM_GEN__particle_draws_1464: this->f__particle_draws = val; return true;
        case SYM_GEN_particle_draw_frame_1465: this->f_particle_draw_frame = val; return true;
        case SYM_GEN__particle_pending_draws_1466: this->f__particle_pending_draws = val; return true;
        case SYM_GEN__particle_before_physics_1467: this->f__particle_before_physics = val; return true;
        case SYM_GEN__motion_queue_1468: this->f__motion_queue = val; return true;
        case SYM_GEN_flicker_initial_1469: this->f_flicker_initial = val; return true;
        case SYM_GEN__flickers_1470: this->f__flickers = val; return true;
        case SYM_GEN__opponent_flickers_1471: this->f__opponent_flickers = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreContext::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_set_drawseq_enabled_1472: return true;
        case SYM_GEN_lib_fires_tick_1473: return true;
        case SYM_GEN_set_custom_health_multiplier_1474: return true;
        case gd::SYM__init: return true;
        case gd::SYM_set_state: return true;
        case SYM_GEN__newDamageSource_1475: return true;
        case SYM_GEN_getCharacterFromId_1476: return true;
        case SYM_GEN_otherCharacter_1477: return true;
        case SYM_GEN_advancePhysicsFrame_1478: return true;
        case SYM_GEN_callDelayed_1479: return true;
        case SYM_GEN__step_native_delays_1480: return true;
        case SYM_GEN__flushTimed_1481: return true;
        case SYM_GEN_defer_1482: return true;
        case SYM_GEN_hasDeferred_1483: return true;
        case SYM_GEN_flushDeferred_1484: return true;
        case SYM_GEN_connectIdleFrameOnce_1485: return true;
        case SYM_GEN_flushIdleFrameCalls_1486: return true;
        case SYM_GEN_emptyGrid_1487: return true;
        case SYM_GEN_setReplayInitial_1488: return true;
        case SYM_GEN_restoreEngineRng_1489: return true;
        case SYM_GEN_collectCriticalLabels_1490: return true;
        case SYM_GEN_scheduleParticleDraws_1491: return true;
        case SYM_GEN_changeParticleDraws_1492: return true;
        case SYM_GEN_restartLoversParticleDraws_1493: return true;
        case SYM_GEN_stepParticleDraws_1494: return true;
        case SYM_GEN_resetCriticalShake_1495: return true;
        case SYM_GEN_beginCriticalShakeFrame_1496: return true;
        case SYM_GEN_collectCriticalShake_1497: return true;
        case SYM_GEN_stepCriticalShake_1498: return true;
        case SYM_GEN_restoreReplayBuffs_1499: return true;
        case SYM_GEN_registerMotion_1500: return true;
        case SYM_GEN_tickMotion_1501: return true;
        case SYM_GEN_addTrainingFlicker_1503: return true;
        case SYM_GEN_restoreFlickers_1504: return true;
        case SYM_GEN__scene_delay_created_before_1505: return true;
        case SYM_GEN_runOpeningSceneDelays_1506: return true;
        case SYM_GEN_tickOpponentFlickers_1507: return true;
        case SYM_GEN_tickFlickers_1508: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreContext::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_set_drawseq_enabled_1472: out = fn_set_drawseq_enabled(args, argc); return true;
        case SYM_GEN_lib_fires_tick_1473: out = fn_lib_fires_tick(args, argc); return true;
        case SYM_GEN_set_custom_health_multiplier_1474: out = fn_set_custom_health_multiplier(args, argc); return true;
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case gd::SYM_set_state: out = fn_set_state(args, argc); return true;
        case SYM_GEN__newDamageSource_1475: out = fn__newDamageSource(args, argc); return true;
        case SYM_GEN_getCharacterFromId_1476: out = fn_getCharacterFromId(args, argc); return true;
        case SYM_GEN_otherCharacter_1477: out = fn_otherCharacter(args, argc); return true;
        case SYM_GEN_advancePhysicsFrame_1478: out = fn_advancePhysicsFrame(args, argc); return true;
        case SYM_GEN_callDelayed_1479: out = fn_callDelayed(args, argc); return true;
        case SYM_GEN__step_native_delays_1480: out = fn__step_native_delays(args, argc); return true;
        case SYM_GEN__flushTimed_1481: out = fn__flushTimed(args, argc); return true;
        case SYM_GEN_defer_1482: out = fn_defer(args, argc); return true;
        case SYM_GEN_hasDeferred_1483: out = fn_hasDeferred(args, argc); return true;
        case SYM_GEN_flushDeferred_1484: out = fn_flushDeferred(args, argc); return true;
        case SYM_GEN_connectIdleFrameOnce_1485: out = fn_connectIdleFrameOnce(args, argc); return true;
        case SYM_GEN_flushIdleFrameCalls_1486: out = fn_flushIdleFrameCalls(args, argc); return true;
        case SYM_GEN_emptyGrid_1487: out = fn_emptyGrid(args, argc); return true;
        case SYM_GEN_setReplayInitial_1488: out = fn_setReplayInitial(args, argc); return true;
        case SYM_GEN_restoreEngineRng_1489: out = fn_restoreEngineRng(args, argc); return true;
        case SYM_GEN_collectCriticalLabels_1490: out = fn_collectCriticalLabels(args, argc); return true;
        case SYM_GEN_scheduleParticleDraws_1491: out = fn_scheduleParticleDraws(args, argc); return true;
        case SYM_GEN_changeParticleDraws_1492: out = fn_changeParticleDraws(args, argc); return true;
        case SYM_GEN_restartLoversParticleDraws_1493: out = fn_restartLoversParticleDraws(args, argc); return true;
        case SYM_GEN_stepParticleDraws_1494: out = fn_stepParticleDraws(args, argc); return true;
        case SYM_GEN_resetCriticalShake_1495: out = fn_resetCriticalShake(args, argc); return true;
        case SYM_GEN_beginCriticalShakeFrame_1496: out = fn_beginCriticalShakeFrame(args, argc); return true;
        case SYM_GEN_collectCriticalShake_1497: out = fn_collectCriticalShake(args, argc); return true;
        case SYM_GEN_stepCriticalShake_1498: out = fn_stepCriticalShake(args, argc); return true;
        case SYM_GEN_restoreReplayBuffs_1499: out = fn_restoreReplayBuffs(args, argc); return true;
        case SYM_GEN_registerMotion_1500: out = fn_registerMotion(args, argc); return true;
        case SYM_GEN_tickMotion_1501: out = fn_tickMotion(args, argc); return true;
        case SYM_GEN__nativeF32_1502: out = sf__nativeF32(gd_ctx, args, argc); return true;
        case SYM_GEN_addTrainingFlicker_1503: out = fn_addTrainingFlicker(args, argc); return true;
        case SYM_GEN_restoreFlickers_1504: out = fn_restoreFlickers(args, argc); return true;
        case SYM_GEN__scene_delay_created_before_1505: out = fn__scene_delay_created_before(args, argc); return true;
        case SYM_GEN_runOpeningSceneDelays_1506: out = fn_runOpeningSceneDelays(args, argc); return true;
        case SYM_GEN_tickOpponentFlickers_1507: out = fn_tickOpponentFlickers(args, argc); return true;
        case SYM_GEN_tickFlickers_1508: out = fn_tickFlickers(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreContext::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN__nativeF32_1502: out = sf__nativeF32(gd_ctx, args, argc); return true;
        default: break;
    }
    return false;
}
gd::GdVal Gd__gd_core__CoreContext::fn_set_drawseq_enabled(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_v = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_v = gd::gd_coerce_bool(lv_v);
    this->f__drawseq_enabled = lv_v;
    native_event_set<Gd__gd_core__CoreRng>(gd_ctx, this->f_rng, SYM_GEN_draw_seq_1732, (gd::gd_truth(lv_v) ? (gd::GdVal::from_int(0LL)) : (gd::gd_neg(gd::GdVal::from_int(1LL)))));
    return gd::GdVal::null();
    }
    gd::GdVal lv_v = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_v = gd::gd_coerce_bool(lv_v);
    this->f__drawseq_enabled = lv_v;
    gd::set_prop(gd_ctx, this->f_rng, SYM_GEN_draw_seq_1732, (gd::gd_truth(lv_v) ? (gd::GdVal::from_int(0LL)) : (gd::gd_neg(gd::GdVal::from_int(1LL)))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_lib_fires_tick(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_lib_fires, gd::SYM_empty, nullptr, 0))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_keep = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    gd::GdVal lv_due = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1115 = gd::gd_iter_seq(gd_ctx.arena, this->f_lib_fires);
        gd::GdArr* _t1116 = (_t1115.kind == gd::GdVal::Kind::Arr) ? _t1115.arr : nullptr;
        uint32_t _len__t1117 = _t1116 ? _t1116->len : 0u;
        for (uint32_t _t1117 = 0; _t1117 < _len__t1117; ++_t1117) {
            gd::GdVal lv_e = _t1116->data[_t1117];
            { gd::GdVal _t1118 = lv_e; gd::GdVal _t1119 = gd::GdVal::from_int(0LL); gd::native_array_set_index(gd_ctx, _t1118, _t1119, gd::gd_sub(gd::native_array_index(gd_ctx, lv_e, gd::GdVal::from_int(0LL)), lv_delta)); }
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_array_index(gd_ctx, lv_e, gd::GdVal::from_int(0LL)), gd::GdVal::from_float(0.0))))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_e}; return gd::native_inline_call(gd_ctx, lv_keep, gd::SYM_push_back, _ca, 1); })();
            }
            else if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_fight_ended)))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_e}; return gd::native_inline_call(gd_ctx, lv_due, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    this->f_lib_fires = lv_keep;
    {
        gd::GdVal _t1120 = gd::gd_iter_seq(gd_ctx.arena, lv_due);
        gd::GdArr* _t1121 = (_t1120.kind == gd::GdVal::Kind::Arr) ? _t1120.arr : nullptr;
        uint32_t _len__t1122 = _t1121 ? _t1121->len : 0u;
        for (uint32_t _t1122 = 0; _t1122 < _len__t1122; ++_t1122) {
            gd::GdVal lv_e = _t1121->data[_t1122];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_coerce_float(gd::native_array_index(gd_ctx, lv_e, gd::GdVal::from_int(1LL))), gd::gd_coerce_float(gd::native_array_index(gd_ctx, lv_e, gd::GdVal::from_int(2LL)))}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_randf_range>(gd_ctx, this->f_rng, gd::SYM_randf_range, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
    }
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_lib_fires, gd::SYM_empty, nullptr, 0))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_keep = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    gd::GdVal lv_due = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1115 = gd::gd_iter_seq(gd_ctx.arena, this->f_lib_fires);
        gd::GdArr* _t1116 = (_t1115.kind == gd::GdVal::Kind::Arr) ? _t1115.arr : nullptr;
        uint32_t _len__t1117 = _t1116 ? _t1116->len : 0u;
        for (uint32_t _t1117 = 0; _t1117 < _len__t1117; ++_t1117) {
            gd::GdVal lv_e = _t1116->data[_t1117];
            { gd::GdVal _t1118 = lv_e; gd::GdVal _t1119 = gd::GdVal::from_int(0LL); gd::native_array_set_index(gd_ctx, _t1118, _t1119, gd::gd_sub(gd::native_array_index(gd_ctx, lv_e, gd::GdVal::from_int(0LL)), lv_delta)); }
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_array_index(gd_ctx, lv_e, gd::GdVal::from_int(0LL)), gd::GdVal::from_float(0.0))))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_e}; return gd::native_inline_call(gd_ctx, lv_keep, gd::SYM_push_back, _ca, 1); })();
            }
            else if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_fight_ended)))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_e}; return gd::native_inline_call(gd_ctx, lv_due, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    this->f_lib_fires = lv_keep;
    {
        gd::GdVal _t1120 = gd::gd_iter_seq(gd_ctx.arena, lv_due);
        gd::GdArr* _t1121 = (_t1120.kind == gd::GdVal::Kind::Arr) ? _t1120.arr : nullptr;
        uint32_t _len__t1122 = _t1121 ? _t1121->len : 0u;
        for (uint32_t _t1122 = 0; _t1122 < _len__t1122; ++_t1122) {
            gd::GdVal lv_e = _t1121->data[_t1122];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_coerce_float(gd::native_array_index(gd_ctx, lv_e, gd::GdVal::from_int(1LL))), gd::gd_coerce_float(gd::native_array_index(gd_ctx, lv_e, gd::GdVal::from_int(2LL)))}; return gd::native_inline_call(gd_ctx, this->f_rng, gd::SYM_randf_range, _ca, 2); })();
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
    this->f_rng = ([&]() { gd::GdVal _ca[] = {lv__seed}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreRng), gd::SYM_new, _ca, 1); })();
    this->f_util = ([&]() { gd::GdVal _ca[] = {this->f_rng}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), gd::SYM_new, _ca, 1); })();
    gd::set_prop(gd_ctx, this->f_util, SYM_GEN__ctx_1347, gd::GdVal::from_obj(this));
    this->f_hooks = (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv__hooks, gd::GdVal::null()))) ? (lv__hooks) : (gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreHooks), gd::SYM_new, nullptr, 0)));
    this->f_show_cooldown_progress = gd::GdVal::from_bool(gd::native_scalar_ne(lv__hooks, gd::GdVal::null()));
    this->f_bus = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEventBus), gd::SYM_new, nullptr, 0);
    gd::set_prop(gd_ctx, this->f_bus, SYM_GEN__ctx_1347, gd::GdVal::from_obj(this));
    this->f_combat_log = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCombatLog), gd::SYM_new, nullptr, 0);
    gd::set_prop(gd_ctx, this->f_combat_log, SYM_GEN__ctx_1347, gd::GdVal::from_obj(this));
    this->f_item_book = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreItemBook), gd::SYM_new, nullptr, 0);
    gd::set_prop(gd_ctx, this->f_item_book, SYM_GEN__ctx_1347, gd::GdVal::from_obj(this));
    this->f_stealLifeDamageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Effect_2656), gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_effectFlags_1539)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__newDamageSource_1475, _ca, 3); })();
    this->f_unhealingDamageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Unhealing_2790), gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_unhealingFlags_1540)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__newDamageSource_1475, _ca, 3); })();
    this->f_fatigueDamageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2781), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Flags_1565), SYM_GEN_CanBeBlocked_2852)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__newDamageSource_1475, _ca, 3); })();
    this->f_event_type_keys = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1395)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_invertDictionary_1800, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_set_state(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_state = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_state = gd::gd_coerce_int(lv_state);
    (void)([&]() { gd::GdVal _ca[] = {lv_state}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_set_state>(gd_ctx, this->f_rng, gd::SYM_set_state, _ca, 1); })();
    return gd::GdVal::null();
    }
    gd::GdVal lv_state = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_state = gd::gd_coerce_int(lv_state);
    (void)([&]() { gd::GdVal _ca[] = {lv_state}; return gd::native_inline_call(gd_ctx, this->f_rng, gd::SYM_set_state, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn__newDamageSource(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_origin = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_type = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_flags = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_flags = gd::gd_coerce_int(lv_flags);
    gd::GdVal lv_src = native_event_new<Gd__gd_core__CoreDamageSource>(gd_ctx, nullptr, 0);
    gd::set_prop(gd_ctx, lv_src, SYM_GEN__rng_1548, this->f_rng);
    (void)([&]() { gd::GdVal _ca[] = {lv_origin, lv_type}; return gd::native_inline_call(gd_ctx, lv_src, SYM_GEN_init_1022, _ca, 2); })();
    gd::set_prop(gd_ctx, lv_src, SYM_GEN_flags_1547, lv_flags);
    return lv_src;
    return gd::GdVal::null();
    }
    gd::GdVal lv_origin = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_type = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_flags = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_flags = gd::gd_coerce_int(lv_flags);
    gd::GdVal lv_src = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0);
    gd::set_prop(gd_ctx, lv_src, SYM_GEN__rng_1548, this->f_rng);
    (void)([&]() { gd::GdVal _ca[] = {lv_origin, lv_type}; return gd::native_inline_call(gd_ctx, lv_src, SYM_GEN_init_1022, _ca, 2); })();
    gd::set_prop(gd_ctx, lv_src, SYM_GEN_flags_1547, lv_flags);
    return lv_src;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_getCharacterFromId(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_playerId = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_playerId = gd::gd_coerce_int(lv_playerId);
    return (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_playerId, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_ID_1297), SYM_GEN_PLAYER_2637)))) ? (this->f_player) : (this->f_opponent));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_otherCharacter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_character, this->f_player))) ? (this->f_opponent) : (this->f_player));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_advancePhysicsFrame(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : (Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_PHYSICS_DELTA_1404));
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
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_obj, gd::GdVal::null())))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(this->f_replay_native_scene_delays)) {
        lv_delay = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {lv_delay}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreContext::call_static_fn(gd_ctx, SYM_GEN__nativeF32_1502, _ca, 1, _out); return _out; })());
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_obj, lv_methodName, lv_delay, lv_binds}))}; return gd::native_inline_call(gd_ctx, this->f__timed, gd::SYM_push_back, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn__step_native_delays(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    gd::GdVal lv_limit = gd::native_inline_call(gd_ctx, this->f__timed, gd::SYM_size, nullptr, 0);
    gd::GdVal lv_read = gd::GdVal::from_int(0LL);
    gd::GdVal lv_write = gd::GdVal::from_int(0LL);
    while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_read, lv_limit)))) {
        gd::GdVal lv_entry = gd::native_array_index(gd_ctx, this->f__timed, lv_read);
        { gd::GdVal _t1123 = lv_entry; gd::GdVal _t1124 = gd::GdVal::from_int(2LL); gd::native_array_set_index(gd_ctx, _t1123, _t1124, ([&]() { gd::GdVal _ca[] = {gd::gd_sub(gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(2LL)), lv_delta)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreContext::call_static_fn(gd_ctx, SYM_GEN__nativeF32_1502, _ca, 1, _out); return _out; })()); }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(2LL)), gd::GdVal::from_float(0.0))))) {
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_fight_ended))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!(gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(0LL))).is_null()))) : gd::GdVal::from_bool(false)))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(1LL)), gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(3LL))}; return gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(0LL)), gd::SYM_callv, _ca, 2); })();
            }
        }
        else {
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_write, lv_read)))) {
                { gd::GdVal _t1125 = this->f__timed; gd::GdVal _t1126 = lv_write; gd::native_array_set_index(gd_ctx, _t1125, _t1126, lv_entry); }
            }
            lv_write = gd::gd_add(gd_ctx, lv_write, gd::GdVal::from_int(1LL));
        }
        lv_read = gd::gd_add(gd_ctx, lv_read, gd::GdVal::from_int(1LL));
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_write, lv_limit)))) {
        gd::GdVal lv_end = gd::native_inline_call(gd_ctx, this->f__timed, gd::SYM_size, nullptr, 0);
        while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_read, lv_end)))) {
            { gd::GdVal _t1127 = this->f__timed; gd::GdVal _t1128 = lv_write; gd::native_array_set_index(gd_ctx, _t1127, _t1128, gd::native_array_index(gd_ctx, this->f__timed, lv_read)); }
            lv_write = gd::gd_add(gd_ctx, lv_write, gd::GdVal::from_int(1LL));
            lv_read = gd::gd_add(gd_ctx, lv_read, gd::GdVal::from_int(1LL));
        }
        (void)([&]() { gd::GdVal _ca[] = {lv_write}; return gd::native_inline_call(gd_ctx, this->f__timed, gd::SYM_resize, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn__flushTimed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    if (gd::gd_truth(this->f_replay_native_scene_delays)) {
        (void)([&]() { gd::GdVal _ca[] = {Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_PHYSICS_DELTA_1404)}; return this->fn__step_native_delays(_ca, 1); })();
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, this->f__timed, gd::SYM_empty, nullptr, 0))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_due = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    gd::GdVal lv_keep = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1129 = gd::gd_iter_seq(gd_ctx.arena, this->f__timed);
        gd::GdArr* _t1130 = (_t1129.kind == gd::GdVal::Kind::Arr) ? _t1129.arr : nullptr;
        uint32_t _len__t1131 = _t1130 ? _t1130->len : 0u;
        for (uint32_t _t1131 = 0; _t1131 < _len__t1131; ++_t1131) {
            gd::GdVal lv_call = _t1130->data[_t1131];
            { gd::GdVal _t1132 = lv_call; gd::GdVal _t1133 = gd::GdVal::from_int(2LL); gd::native_array_set_index(gd_ctx, _t1132, _t1133, gd::gd_sub(gd::native_array_index(gd_ctx, lv_call, gd::GdVal::from_int(2LL)), Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_PHYSICS_DELTA_1404))); }
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_array_index(gd_ctx, lv_call, gd::GdVal::from_int(2LL)), gd::GdVal::from_float(0.0))))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_call}; return gd::native_inline_call(gd_ctx, lv_keep, gd::SYM_push_back, _ca, 1); })();
            }
            else if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_fight_ended)))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_call}; return gd::native_inline_call(gd_ctx, lv_due, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_due, gd::SYM_empty, nullptr, 0))) {
        this->f__timed = lv_keep;
        return gd::GdVal::null();
    }
    this->f__timed = lv_keep;
    {
        gd::GdVal _t1134 = gd::gd_iter_seq(gd_ctx.arena, lv_due);
        gd::GdArr* _t1135 = (_t1134.kind == gd::GdVal::Kind::Arr) ? _t1134.arr : nullptr;
        uint32_t _len__t1136 = _t1135 ? _t1135->len : 0u;
        for (uint32_t _t1136 = 0; _t1136 < _len__t1136; ++_t1136) {
            gd::GdVal lv_call = _t1135->data[_t1136];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, lv_call, gd::GdVal::from_int(1LL)), gd::native_array_index(gd_ctx, lv_call, gd::GdVal::from_int(3LL))}; return gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, lv_call, gd::GdVal::from_int(0LL)), gd::SYM_callv, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
    }
    if (gd::gd_truth(this->f_replay_native_scene_delays)) {
        (void)([&]() { gd::GdVal _ca[] = {Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_PHYSICS_DELTA_1404)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__step_native_delays_1480, _ca, 1); })();
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, this->f__timed, gd::SYM_empty, nullptr, 0))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_due = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    gd::GdVal lv_keep = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1129 = gd::gd_iter_seq(gd_ctx.arena, this->f__timed);
        gd::GdArr* _t1130 = (_t1129.kind == gd::GdVal::Kind::Arr) ? _t1129.arr : nullptr;
        uint32_t _len__t1131 = _t1130 ? _t1130->len : 0u;
        for (uint32_t _t1131 = 0; _t1131 < _len__t1131; ++_t1131) {
            gd::GdVal lv_call = _t1130->data[_t1131];
            { gd::GdVal _t1132 = lv_call; gd::GdVal _t1133 = gd::GdVal::from_int(2LL); gd::native_array_set_index(gd_ctx, _t1132, _t1133, gd::gd_sub(gd::native_array_index(gd_ctx, lv_call, gd::GdVal::from_int(2LL)), Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_PHYSICS_DELTA_1404))); }
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_array_index(gd_ctx, lv_call, gd::GdVal::from_int(2LL)), gd::GdVal::from_float(0.0))))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_call}; return gd::native_inline_call(gd_ctx, lv_keep, gd::SYM_push_back, _ca, 1); })();
            }
            else if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_fight_ended)))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_call}; return gd::native_inline_call(gd_ctx, lv_due, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_due, gd::SYM_empty, nullptr, 0))) {
        this->f__timed = lv_keep;
        return gd::GdVal::null();
    }
    this->f__timed = lv_keep;
    {
        gd::GdVal _t1134 = gd::gd_iter_seq(gd_ctx.arena, lv_due);
        gd::GdArr* _t1135 = (_t1134.kind == gd::GdVal::Kind::Arr) ? _t1134.arr : nullptr;
        uint32_t _len__t1136 = _t1135 ? _t1135->len : 0u;
        for (uint32_t _t1136 = 0; _t1136 < _len__t1136; ++_t1136) {
            gd::GdVal lv_call = _t1135->data[_t1136];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, lv_call, gd::GdVal::from_int(1LL)), gd::native_array_index(gd_ctx, lv_call, gd::GdVal::from_int(3LL))}; return gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, lv_call, gd::GdVal::from_int(0LL)), gd::SYM_callv, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_defer(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_obj = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_methodName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_args = (_argc > 2) ? _args[2] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_obj, lv_methodName, lv_args}))}; return gd::native_inline_call(gd_ctx, this->f__deferred, gd::SYM_push_back, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_hasDeferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, this->f__deferred, gd::SYM_empty, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_flushDeferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_deferred_flush_enabled)))) {
        return gd::GdVal::null();
    }
    while (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, this->f__deferred, gd::SYM_empty, nullptr, 0))))) {
        gd::GdVal lv_batch = this->f__deferred;
        this->f__deferred = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
        {
            gd::GdVal _t1137 = gd::gd_iter_seq(gd_ctx.arena, lv_batch);
            gd::GdArr* _t1138 = (_t1137.kind == gd::GdVal::Kind::Arr) ? _t1137.arr : nullptr;
            uint32_t _len__t1139 = _t1138 ? _t1138->len : 0u;
            for (uint32_t _t1139 = 0; _t1139 < _len__t1139; ++_t1139) {
                gd::GdVal lv_call = _t1138->data[_t1139];
                gd::GdVal lv_obj = gd::native_array_index(gd_ctx, lv_call, gd::GdVal::from_int(0LL));
                if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_obj, gd::GdVal::null())))) {
                    (void)([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, lv_call, gd::GdVal::from_int(1LL)), gd::native_array_index(gd_ctx, lv_call, gd::GdVal::from_int(2LL))}; return gd::native_inline_call(gd_ctx, lv_obj, gd::SYM_callv, _ca, 2); })();
                }
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_connectIdleFrameOnce(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_obj = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_methodName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_args = (_argc > 2) ? _args[2] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    gd::GdVal lv_position = gd::native_inline_call(gd_ctx, this->f__idle_frame_calls, gd::SYM_size, nullptr, 0);
    {
        gd::GdVal _t1140 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, this->f__idle_frame_calls, gd::SYM_size, nullptr, 0)}; return gd::gd_range(gd_ctx.arena, _ca, 1); })());
        gd::GdArr* _t1141 = (_t1140.kind == gd::GdVal::Kind::Arr) ? _t1140.arr : nullptr;
        uint32_t _len__t1142 = _t1141 ? _t1141->len : 0u;
        for (uint32_t _t1142 = 0; _t1142 < _len__t1142; ++_t1142) {
            gd::GdVal lv_i = _t1141->data[_t1142];
            gd::GdVal lv_call = gd::native_array_index(gd_ctx, this->f__idle_frame_calls, lv_i);
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_array_index(gd_ctx, lv_call, gd::GdVal::from_int(0LL)), lv_obj))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_array_index(gd_ctx, lv_call, gd::GdVal::from_int(1LL)), lv_methodName)))) : gd::GdVal::from_bool(false)))) {
                return gd::GdVal::null();
            }
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_position, gd::native_inline_call(gd_ctx, this->f__idle_frame_calls, gd::SYM_size, nullptr, 0)))) ? gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_obj, this->f_player))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_obj, this->f_opponent))))))) : gd::GdVal::from_bool(false)))) {
                if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_obj, this->f_player))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_array_index(gd_ctx, lv_call, gd::GdVal::from_int(0LL)), this->f_opponent)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_array_index(gd_ctx, lv_call, gd::GdVal::from_int(0LL)), lv_obj))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_methodName, gd::native_array_index(gd_ctx, lv_call, gd::GdVal::from_int(1LL)))))) : gd::GdVal::from_bool(false))))))) {
                    lv_position = lv_i;
                }
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_position, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_obj, lv_methodName, lv_args}))}; return gd::native_inline_call(gd_ctx, this->f__idle_frame_calls, gd::SYM_insert, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_flushIdleFrameCalls(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_deferred_flush_enabled)))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_batch = this->f__idle_frame_calls;
    this->f__idle_frame_calls = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    if (gd::gd_truth(this->f_fight_ended)) {
        return gd::GdVal::null();
    }
    {
        gd::GdVal _t1143 = gd::gd_iter_seq(gd_ctx.arena, lv_batch);
        gd::GdArr* _t1144 = (_t1143.kind == gd::GdVal::Kind::Arr) ? _t1143.arr : nullptr;
        uint32_t _len__t1145 = _t1144 ? _t1144->len : 0u;
        for (uint32_t _t1145 = 0; _t1145 < _len__t1145; ++_t1145) {
            gd::GdVal lv_call = _t1144->data[_t1145];
            gd::GdVal lv_obj = gd::native_array_index(gd_ctx, lv_call, gd::GdVal::from_int(0LL));
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_obj, gd::GdVal::null())))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, lv_call, gd::GdVal::from_int(1LL)), gd::native_array_index(gd_ctx, lv_call, gd::GdVal::from_int(2LL))}; return gd::native_inline_call(gd_ctx, lv_obj, gd::SYM_callv, _ca, 2); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_emptyGrid(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f__emptyGrid, gd::GdVal::null())))) {
        this->f__emptyGrid = ([&]() { gd::GdVal _ca[] = {gd::GdVal::null()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreGrid), gd::SYM_new, _ca, 1); })();
    }
    return this->f__emptyGrid;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_setReplayInitial(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_activation_state = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_idle_left = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_flickers = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_buff_state = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_engine_rng = (_argc > 4) ? _args[4] : (gd::GdVal::null());
    gd::GdVal lv_scene_delays = (_argc > 5) ? _args[5] : (gd::GdVal::from_bool(false));
    lv_scene_delays = gd::gd_coerce_bool(lv_scene_delays);
    gd::GdVal lv_util_time = (_argc > 6) ? _args[6] : (gd::GdVal::from_float(0.0));
    lv_util_time = gd::gd_coerce_float(lv_util_time);
    this->f_activation_rng_state = lv_activation_state;
    this->f_idle_timer_initial = lv_idle_left;
    this->f_flicker_initial = lv_flickers;
    this->f_replay_buff_state = lv_buff_state;
    this->f_replay_engine_rng = lv_engine_rng;
    this->f_native_frame_rng = gd::GdVal::from_bool(gd::native_scalar_ne(lv_engine_rng, gd::GdVal::null()));
    if (gd::gd_truth(this->f_native_frame_rng)) {
        this->f_native_label_mode = gd::gd_coerce_int(gd::native_array_index(gd_ctx, lv_engine_rng, gd::GdVal::from_int(4LL)));
    }
    this->f_replay_native_scene_delays = lv_scene_delays;
    this->f_replay_util_time = lv_util_time;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_restoreEngineRng(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_activating = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_activating = gd::gd_coerce_bool(lv_activating);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_replay_engine_rng, gd::GdVal::null())))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_base = (gd::gd_truth(lv_activating) ? (gd::GdVal::from_int(2LL)) : (gd::GdVal::from_int(0LL)));
    (void)(gd_ctx.math_rng.set_seed(static_cast<uint64_t>(gd::gd_coerce_int(gd::native_array_index(gd_ctx, this->f_replay_engine_rng, lv_base)).as_int())), gd::GdVal::null());
    {
        gd::GdVal _t1146 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(gd::native_array_index(gd_ctx, this->f_replay_engine_rng, gd::gd_add(gd_ctx, lv_base, gd::GdVal::from_int(1LL))))}; return gd::gd_range(gd_ctx.arena, _ca, 1); })());
        gd::GdArr* _t1147 = (_t1146.kind == gd::GdVal::Kind::Arr) ? _t1146.arr : nullptr;
        uint32_t _len__t1148 = _t1147 ? _t1147->len : 0u;
        for (uint32_t _t1148 = 0; _t1148 < _len__t1148; ++_t1148) {
            gd::GdVal lv_i = _t1147->data[_t1148];
            (void)gd::GdVal::from_int(gd_ctx.math_rng.randi());
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_collectCriticalLabels(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_has_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_has_item = gd::gd_coerce_bool(lv_has_item);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_native_label_mode, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_native_label_mode, gd::GdVal::from_int(1LL)))))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return this->fn_collectCriticalShake(_ca, 1); })();
    }
    if (gd::gd_truth((gd::gd_truth(lv_has_item) ? gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_native_label_mode, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_native_label_mode, gd::GdVal::from_int(2LL)))))))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return this->fn_collectCriticalShake(_ca, 1); })();
    }
    return gd::GdVal::null();
    }
    gd::GdVal lv_has_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_has_item = gd::gd_coerce_bool(lv_has_item);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_native_label_mode, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_native_label_mode, gd::GdVal::from_int(1LL)))))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_collectCriticalShake_1497, _ca, 1); })();
    }
    if (gd::gd_truth((gd::gd_truth(lv_has_item) ? gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_native_label_mode, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_native_label_mode, gd::GdVal::from_int(2LL)))))))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_collectCriticalShake_1497, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_scheduleParticleDraws(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_schedule = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_native_frame_rng)))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_phase = (gd::gd_truth(this->f__critical_shake_after_idle) ? (gd::GdVal::from_int(2LL)) : (gd::GdVal::from_int(1LL)));
    (void)([&]() { gd::GdVal _ca[] = {lv_schedule, this->f_particle_draw_frame, lv_phase, gd::GdVal::from_int(1LL)}; return this->fn_changeParticleDraws(_ca, 4); })();
    return gd::GdVal::null();
    }
    gd::GdVal lv_schedule = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_native_frame_rng)))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_phase = (gd::gd_truth(this->f__critical_shake_after_idle) ? (gd::GdVal::from_int(2LL)) : (gd::GdVal::from_int(1LL)));
    (void)([&]() { gd::GdVal _ca[] = {lv_schedule, this->f_particle_draw_frame, lv_phase, gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeParticleDraws_1492, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_changeParticleDraws(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_schedule = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_start = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_start = gd::gd_coerce_int(lv_start);
    gd::GdVal lv_phase = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_phase = gd::gd_coerce_int(lv_phase);
    gd::GdVal lv_direction = (_argc > 3) ? _args[3] : gd::GdVal::null();
    lv_direction = gd::gd_coerce_int(lv_direction);
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, this->f__particle_draws, gd::SYM_empty, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_LOVERS_PARTICLE_RESTART_DRAWS_1463), gd::SYM_size, nullptr, 0)}; return gd::native_inline_call(gd_ctx, this->f__particle_draws, gd::SYM_resize, _ca, 1); })();
        {
            gd::GdVal _t1149 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, this->f__particle_draws, gd::SYM_size, nullptr, 0)}; return gd::gd_range(gd_ctx.arena, _ca, 1); })());
            gd::GdArr* _t1150 = (_t1149.kind == gd::GdVal::Kind::Arr) ? _t1149.arr : nullptr;
            uint32_t _len__t1151 = _t1150 ? _t1150->len : 0u;
            for (uint32_t _t1151 = 0; _t1151 < _len__t1151; ++_t1151) {
                gd::GdVal lv_i = _t1150->data[_t1151];
                { gd::GdVal _t1152 = this->f__particle_draws; gd::GdVal _t1153 = lv_i; gd::native_array_set_index(gd_ctx, _t1152, _t1153, gd::GdVal::from_int(0LL)); }
            }
        }
    }
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_phase, gd::GdVal::from_int(2LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_start, this->f_particle_draw_frame)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(this->f__critical_shake_after_idle)) : gd::GdVal::from_bool(false)))) {
        this->f__particle_before_physics = gd::gd_add(gd_ctx, this->f__particle_before_physics, gd::gd_mul(lv_direction, gd::GdVal::from_int(10LL)));
    }
    {
        gd::GdVal _t1154 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::gd_sub(this->f_particle_draw_frame, lv_start), gd::native_inline_call(gd_ctx, lv_schedule, gd::SYM_size, nullptr, 0)}; return gd::gd_range(gd_ctx.arena, _ca, 2); })());
        gd::GdArr* _t1155 = (_t1154.kind == gd::GdVal::Kind::Arr) ? _t1154.arr : nullptr;
        uint32_t _len__t1156 = _t1155 ? _t1155->len : 0u;
        for (uint32_t _t1156 = 0; _t1156 < _len__t1156; ++_t1156) {
            gd::GdVal lv_i = _t1155->data[_t1156];
            gd::GdVal lv_index = gd::gd_coerce_int(gd::gd_mod(gd_ctx, gd::gd_add(gd_ctx, lv_start, lv_i), gd::native_inline_call(gd_ctx, this->f__particle_draws, gd::SYM_size, nullptr, 0)));
            gd::GdVal lv_count = gd::gd_coerce_int(gd::native_array_index(gd_ctx, lv_schedule, lv_i));
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_i, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_phase, gd::GdVal::from_int(2LL))))) : gd::GdVal::from_bool(false)))) {
                lv_count = gd::gd_coerce_int(gd::gd_sub(lv_count, gd::GdVal::from_int(10LL)));
            }
            { gd::GdVal _t1157 = this->f__particle_draws; gd::GdVal _t1158 = lv_index; gd::native_array_set_index(gd_ctx, _t1157, _t1158, gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, _t1157, _t1158), gd::gd_mul(lv_direction, lv_count))); }
            this->f__particle_pending_draws = gd::gd_add(gd_ctx, this->f__particle_pending_draws, gd::gd_mul(lv_direction, lv_count));
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_restartLoversParticleDraws(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_previous_frame = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_previous_frame = gd::gd_coerce_int(lv_previous_frame);
    gd::GdVal lv_previous_phase = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_previous_phase = gd::gd_coerce_int(lv_previous_phase);
    gd::GdVal lv_visible = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_visible = gd::gd_coerce_bool(lv_visible);
    gd::GdVal lv_redraw_phase = (gd::gd_truth(this->f__critical_shake_after_idle) ? (gd::GdVal::from_int(2LL)) : (gd::GdVal::from_int(1LL)));
    gd::GdVal lv_pending_redraw = (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_previous_frame, this->f_particle_draw_frame))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_previous_phase, lv_redraw_phase)))) : gd::GdVal::from_bool(false));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_previous_frame, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_previous = (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_previous_phase, gd::GdVal::from_int(0LL)))) ? (Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_LOVERS_PARTICLE_RESTART_DRAWS_1463)) : (Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_LOVERS_PARTICLE_DRAWS_1462)));
        (void)([&]() { gd::GdVal _ca[] = {lv_previous, lv_previous_frame, lv_previous_phase, gd::gd_neg(gd::GdVal::from_int(1LL))}; return this->fn_changeParticleDraws(_ca, 4); })();
    }
    if (gd::gd_truth((gd::gd_truth(lv_visible) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_pending_redraw)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_LOVERS_PARTICLE_RESTART_DRAWS_1463), this->f_particle_draw_frame, gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL)}; return this->fn_changeParticleDraws(_ca, 4); })();
        return gd::GdVal::from_int(0LL);
    }
    (void)([&]() { gd::GdVal _ca[] = {Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_LOVERS_PARTICLE_DRAWS_1462), this->f_particle_draw_frame, lv_redraw_phase, gd::GdVal::from_int(1LL)}; return this->fn_changeParticleDraws(_ca, 4); })();
    return lv_redraw_phase;
    return gd::GdVal::null();
    }
    gd::GdVal lv_previous_frame = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_previous_frame = gd::gd_coerce_int(lv_previous_frame);
    gd::GdVal lv_previous_phase = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_previous_phase = gd::gd_coerce_int(lv_previous_phase);
    gd::GdVal lv_visible = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_visible = gd::gd_coerce_bool(lv_visible);
    gd::GdVal lv_redraw_phase = (gd::gd_truth(this->f__critical_shake_after_idle) ? (gd::GdVal::from_int(2LL)) : (gd::GdVal::from_int(1LL)));
    gd::GdVal lv_pending_redraw = (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_previous_frame, this->f_particle_draw_frame))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_previous_phase, lv_redraw_phase)))) : gd::GdVal::from_bool(false));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_previous_frame, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_previous = (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_previous_phase, gd::GdVal::from_int(0LL)))) ? (Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_LOVERS_PARTICLE_RESTART_DRAWS_1463)) : (Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_LOVERS_PARTICLE_DRAWS_1462)));
        (void)([&]() { gd::GdVal _ca[] = {lv_previous, lv_previous_frame, lv_previous_phase, gd::gd_neg(gd::GdVal::from_int(1LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeParticleDraws_1492, _ca, 4); })();
    }
    if (gd::gd_truth((gd::gd_truth(lv_visible) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_pending_redraw)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_LOVERS_PARTICLE_RESTART_DRAWS_1463), this->f_particle_draw_frame, gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeParticleDraws_1492, _ca, 4); })();
        return gd::GdVal::from_int(0LL);
    }
    (void)([&]() { gd::GdVal _ca[] = {Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_LOVERS_PARTICLE_DRAWS_1462), this->f_particle_draw_frame, lv_redraw_phase, gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeParticleDraws_1492, _ca, 4); })();
    return lv_redraw_phase;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_stepParticleDraws(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_index = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_particle_draw_frame, gd::native_inline_call(gd_ctx, this->f__particle_draws, gd::SYM_size, nullptr, 0)));
    gd::GdVal lv_count = gd::gd_coerce_int(gd::native_array_index(gd_ctx, this->f__particle_draws, lv_index));
    { gd::GdVal _t1159 = this->f__particle_draws; gd::GdVal _t1160 = lv_index; gd::native_array_set_index(gd_ctx, _t1159, _t1160, gd::GdVal::from_int(0LL)); }
    this->f_particle_draw_frame = gd::gd_add(gd_ctx, this->f_particle_draw_frame, gd::GdVal::from_int(1LL));
    this->f__particle_pending_draws = gd::gd_sub(this->f__particle_pending_draws, lv_count);
    {
        gd::GdVal _t1161 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_count}; return gd::gd_range(gd_ctx.arena, _ca, 1); })());
        gd::GdArr* _t1162 = (_t1161.kind == gd::GdVal::Kind::Arr) ? _t1161.arr : nullptr;
        uint32_t _len__t1163 = _t1162 ? _t1162->len : 0u;
        for (uint32_t _t1163 = 0; _t1163 < _len__t1163; ++_t1163) {
            gd::GdVal lv__i = _t1162->data[_t1163];
            (void)gd::GdVal::from_int(gd_ctx.math_rng.randi());
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_resetCriticalShake(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f__particle_draws, gd::SYM_clear, nullptr, 0);
    this->f_particle_draw_frame = gd::GdVal::from_int(0LL);
    this->f__particle_pending_draws = gd::GdVal::from_int(0LL);
    this->f__particle_before_physics = gd::GdVal::from_int(0LL);
    (void)gd::native_inline_call(gd_ctx, this->f__critical_shake_delta, gd::SYM_clear, nullptr, 0);
    this->f__critical_shake_active = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(0LL), gd::GdVal::from_int(0LL)}));
    this->f__critical_shake_frame = gd::GdVal::from_int(0LL);
    this->f__critical_shake_after_idle = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_beginCriticalShakeFrame(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f__particle_before_physics, gd::GdVal::from_int(0LL))))) {
        {
            gd::GdVal _t1164 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {this->f__particle_before_physics}; return gd::gd_range(gd_ctx.arena, _ca, 1); })());
            gd::GdArr* _t1165 = (_t1164.kind == gd::GdVal::Kind::Arr) ? _t1164.arr : nullptr;
            uint32_t _len__t1166 = _t1165 ? _t1165->len : 0u;
            for (uint32_t _t1166 = 0; _t1166 < _len__t1166; ++_t1166) {
                gd::GdVal lv__i = _t1165->data[_t1166];
                (void)gd::GdVal::from_int(gd_ctx.math_rng.randi());
            }
        }
        this->f__particle_before_physics = gd::GdVal::from_int(0LL);
    }
    this->f__critical_shake_after_idle = gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_collectCriticalShake(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_on_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_on_item = gd::gd_coerce_bool(lv_on_item);
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, this->f__critical_shake_delta, gd::SYM_empty, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_CRITICAL_SHAKE_WINDOW_1456)}; return gd::native_inline_call(gd_ctx, this->f__critical_shake_delta, gd::SYM_resize, _ca, 1); })();
        {
            gd::GdVal _t1167 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_CRITICAL_SHAKE_WINDOW_1456)}; return gd::gd_range(gd_ctx.arena, _ca, 1); })());
            gd::GdArr* _t1168 = (_t1167.kind == gd::GdVal::Kind::Arr) ? _t1167.arr : nullptr;
            uint32_t _len__t1169 = _t1168 ? _t1168->len : 0u;
            for (uint32_t _t1169 = 0; _t1169 < _len__t1169; ++_t1169) {
                gd::GdVal lv_i = _t1168->data[_t1169];
                { gd::GdVal _t1170 = this->f__critical_shake_delta; gd::GdVal _t1171 = lv_i; gd::native_array_set_index(gd_ctx, _t1170, _t1171, gd::GdVal::from_int(0LL)); }
            }
        }
    }
    gd::GdVal lv_first = gd::gd_add(gd_ctx, this->f__critical_shake_frame, gd::GdVal::from_int(2LL));
    gd::GdVal lv_end_offset = gd::GdVal::from_int(66LL);
    if (gd::gd_truth(lv_on_item)) {
        lv_end_offset = (gd::gd_truth(this->f__critical_shake_after_idle) ? (gd::GdVal::from_int(39LL)) : (gd::GdVal::from_int(42LL)));
    }
    { gd::GdVal _t1172 = this->f__critical_shake_delta; gd::GdVal _t1173 = gd::gd_mod(gd_ctx, lv_first, Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_CRITICAL_SHAKE_WINDOW_1456)); gd::native_array_set_index(gd_ctx, _t1172, _t1173, gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, _t1172, _t1173), gd::GdVal::from_int(1LL))); }
    { gd::GdVal _t1174 = this->f__critical_shake_delta; gd::GdVal _t1175 = gd::gd_mod(gd_ctx, gd::gd_add(gd_ctx, lv_first, lv_end_offset), Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_CRITICAL_SHAKE_WINDOW_1456)); gd::native_array_set_index(gd_ctx, _t1174, _t1175, gd::gd_sub(gd::native_array_index(gd_ctx, _t1174, _t1175), gd::GdVal::from_int(1LL))); }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_stepCriticalShake(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f__particle_pending_draws, gd::GdVal::from_int(0LL))))) {
        (void)this->fn_stepParticleDraws(nullptr, 0);
    }
    this->f__critical_shake_after_idle = gd::GdVal::from_bool(true);
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, this->f__critical_shake_delta, gd::SYM_empty, nullptr, 0))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_phase = gd::gd_mod(gd_ctx, this->f__critical_shake_frame, gd::GdVal::from_int(3LL));
    { gd::GdVal _t1176 = this->f__critical_shake_active; gd::GdVal _t1177 = lv_phase; gd::native_array_set_index(gd_ctx, _t1176, _t1177, gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, _t1176, _t1177), gd::native_array_index(gd_ctx, this->f__critical_shake_delta, this->f__critical_shake_frame))); }
    { gd::GdVal _t1178 = this->f__critical_shake_delta; gd::GdVal _t1179 = this->f__critical_shake_frame; gd::native_array_set_index(gd_ctx, _t1178, _t1179, gd::GdVal::from_int(0LL)); }
    gd::GdVal lv_remaining = gd::gd_coerce_int(gd::native_array_index(gd_ctx, this->f__critical_shake_active, lv_phase));
    while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_remaining, gd::GdVal::from_int(0LL))))) {
        (void)gd::GdVal::from_int(gd_ctx.math_rng.randi());
        lv_remaining = gd::gd_sub(lv_remaining, gd::GdVal::from_int(1LL));
    }
    this->f__critical_shake_frame = gd::gd_mod(gd_ctx, gd::gd_add(gd_ctx, this->f__critical_shake_frame, gd::GdVal::from_int(1LL)), Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_CRITICAL_SHAKE_WINDOW_1456));
    return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f__particle_pending_draws, gd::GdVal::from_int(0LL))))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stepParticleDraws_1494, nullptr, 0);
    }
    this->f__critical_shake_after_idle = gd::GdVal::from_bool(true);
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, this->f__critical_shake_delta, gd::SYM_empty, nullptr, 0))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_phase = gd::gd_mod(gd_ctx, this->f__critical_shake_frame, gd::GdVal::from_int(3LL));
    { gd::GdVal _t1176 = this->f__critical_shake_active; gd::GdVal _t1177 = lv_phase; gd::native_array_set_index(gd_ctx, _t1176, _t1177, gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, _t1176, _t1177), gd::native_array_index(gd_ctx, this->f__critical_shake_delta, this->f__critical_shake_frame))); }
    { gd::GdVal _t1178 = this->f__critical_shake_delta; gd::GdVal _t1179 = this->f__critical_shake_frame; gd::native_array_set_index(gd_ctx, _t1178, _t1179, gd::GdVal::from_int(0LL)); }
    gd::GdVal lv_remaining = gd::gd_coerce_int(gd::native_array_index(gd_ctx, this->f__critical_shake_active, lv_phase));
    while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_remaining, gd::GdVal::from_int(0LL))))) {
        (void)gd::GdVal::from_int(gd_ctx.math_rng.randi());
        lv_remaining = gd::gd_sub(lv_remaining, gd::GdVal::from_int(1LL));
    }
    this->f__critical_shake_frame = gd::gd_mod(gd_ctx, gd::gd_add(gd_ctx, this->f__critical_shake_frame, gd::GdVal::from_int(1LL)), Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_CRITICAL_SHAKE_WINDOW_1456));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_restoreReplayBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_replay_buff_state, gd::GdVal::null())))) {
        return gd::GdVal::null();
    }
    (void)gd::GdVal::null();
    gd::GdVal lv_characters = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {this->f_player, this->f_opponent}));
    {
        gd::GdVal _t1180 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::gd_range(gd_ctx.arena, _ca, 1); })());
        gd::GdArr* _t1181 = (_t1180.kind == gd::GdVal::Kind::Arr) ? _t1180.arr : nullptr;
        uint32_t _len__t1182 = _t1181 ? _t1181->len : 0u;
        for (uint32_t _t1182 = 0; _t1182 < _len__t1182; ++_t1182) {
            gd::GdVal lv_side = _t1181->data[_t1182];
            {
                gd::GdVal _t1183 = gd::gd_iter_seq(gd_ctx.arena, gd::native_array_index(gd_ctx, this->f_replay_buff_state, lv_side));
                gd::GdArr* _t1184 = (_t1183.kind == gd::GdVal::Kind::Arr) ? _t1183.arr : nullptr;
                uint32_t _len__t1185 = _t1184 ? _t1184->len : 0u;
                for (uint32_t _t1185 = 0; _t1185 < _len__t1185; ++_t1185) {
                    gd::GdVal lv_row = _t1184->data[_t1185];
                    gd::GdVal lv_buff = gd::native_array_index(gd_ctx, gd::get_prop(gd_ctx, gd::native_array_index(gd_ctx, lv_characters, lv_side), SYM_GEN_buffs_1048), gd::gd_coerce_int(gd::native_array_index(gd_ctx, lv_row, gd::GdVal::from_int(0LL))));
                    (void)gd::GdVal::null();
                    (void)gd::GdVal::null();
                    gd::set_prop(gd_ctx, lv_buff, SYM_GEN_permanentStacks_1008, gd::gd_coerce_int(gd::native_array_index(gd_ctx, lv_row, gd::GdVal::from_int(2LL))));
                }
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_registerMotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_kind = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_kind = gd::gd_coerce_int(lv_kind);
    gd::GdVal lv_subject = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_token = (_argc > 2) ? _args[2] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_kind, lv_subject, lv_token}))}; return gd::native_inline_call(gd_ctx, this->f__motion_queue, gd::SYM_push_back, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_tickMotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    gd::GdVal lv_limit = gd::native_inline_call(gd_ctx, this->f__motion_queue, gd::SYM_size, nullptr, 0);
    gd::GdVal lv_read = gd::GdVal::from_int(0LL);
    gd::GdVal lv_write = gd::GdVal::from_int(0LL);
    while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_read, lv_limit)))) {
        gd::GdVal lv_entry = gd::native_array_index(gd_ctx, this->f__motion_queue, lv_read);
        gd::GdVal lv_keep = gd::GdVal::from_bool(false);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(0LL)), gd::GdVal::from_int(0LL))))) {
            gd::GdVal lv_character = gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(1LL));
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::get_prop(gd_ctx, lv_character, SYM_GEN__visual_generation_1125), gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(2LL))))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::get_prop(gd_ctx, lv_character, SYM_GEN__visual_kind_1123), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::native_inline_call(gd_ctx, lv_character, SYM_GEN_tickVisualMotion_1137, _ca, 1); })();
                lv_keep = gd::GdVal::from_bool(gd::native_scalar_ne(gd::get_prop(gd_ctx, lv_character, SYM_GEN__visual_kind_1123), gd::GdVal::from_int(0LL)));
            }
        }
        else {
            gd::GdVal lv_charge = gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(2LL));
            (void)([&]() { gd::GdVal _ca[] = {lv_charge, lv_delta}; return gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(1LL)), SYM_GEN__tickChargePath_506, _ca, 2); })();
            lv_keep = gd::get_prop(gd_ctx, lv_charge, SYM_GEN_active_1653);
        }
        if (gd::gd_truth(lv_keep)) {
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_write, lv_read)))) {
                { gd::GdVal _t1186 = this->f__motion_queue; gd::GdVal _t1187 = lv_write; gd::native_array_set_index(gd_ctx, _t1186, _t1187, lv_entry); }
            }
            lv_write = gd::gd_add(gd_ctx, lv_write, gd::GdVal::from_int(1LL));
        }
        lv_read = gd::gd_add(gd_ctx, lv_read, gd::GdVal::from_int(1LL));
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_write, lv_limit)))) {
        gd::GdVal lv_end = gd::native_inline_call(gd_ctx, this->f__motion_queue, gd::SYM_size, nullptr, 0);
        while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_read, lv_end)))) {
            { gd::GdVal _t1188 = this->f__motion_queue; gd::GdVal _t1189 = lv_write; gd::native_array_set_index(gd_ctx, _t1188, _t1189, gd::native_array_index(gd_ctx, this->f__motion_queue, lv_read)); }
            lv_write = gd::gd_add(gd_ctx, lv_write, gd::GdVal::from_int(1LL));
            lv_read = gd::gd_add(gd_ctx, lv_read, gd::GdVal::from_int(1LL));
        }
        (void)([&]() { gd::GdVal _ca[] = {lv_write}; return gd::native_inline_call(gd_ctx, this->f__motion_queue, gd::SYM_resize, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::sf__nativeF32(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    (void)gd_ctx;
    const auto value = gd::gd_coerce_float(_argc > 0 ? _args[0] : gd::GdVal::null());
    return gd::GdVal::from_float(static_cast<double>(static_cast<float>(value.as_float())));
}
gd::GdVal Gd__gd_core__CoreContext::fn_addTrainingFlicker(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_delay = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_delay = gd::gd_coerce_float(lv_delay);
    gd::GdVal lv_flicker = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreContext__INNER__NativeFlicker), gd::SYM_new, nullptr, 0);
    gd::set_prop(gd_ctx, lv_flicker, SYM_GEN_ctx_3, gd::GdVal::from_obj(this));
    gd::GdVal lv_descr = gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2);
    gd::set_prop(gd_ctx, lv_flicker, SYM_GEN_limits_1510, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::get_prop(gd_ctx, lv_descr, SYM_GEN_flickerMinDist_1697), gd::get_prop(gd_ctx, lv_descr, SYM_GEN_flickerMaxDist_1698), gd::get_prop(gd_ctx, lv_descr, SYM_GEN_flickerMinSpeed_1699), gd::get_prop(gd_ctx, lv_descr, SYM_GEN_flickerMaxSpeed_1700)})));
    gd::set_prop(gd_ctx, lv_flicker, gd::SYM_length, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.3)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreContext::call_static_fn(gd_ctx, SYM_GEN__nativeF32_1502, _ca, 1, _out); return _out; })());
    gd::set_prop(gd_ctx, lv_flicker, SYM_GEN_playing_1512, gd::GdVal::from_bool(gd::native_scalar_eq(gd::get_prop(gd_ctx, lv_descr, SYM_GEN_identifier_1673), gd::GdVal::from_str(&battle_string_literals[0]))));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::get_prop(gd_ctx, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0), SYM_GEN_playerId_1046), gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_flicker}; return gd::native_inline_call(gd_ctx, this->f__opponent_flickers, gd::SYM_append, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {lv_flicker}; return gd::native_inline_call(gd_ctx, this->f__flickers, gd::SYM_append, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_flicker, gd::GdVal::from_str(&battle_string_literals[1]), lv_delay}; return this->fn_callDelayed(_ca, 3); })();
    return gd::GdVal::null();
    }
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_delay = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_delay = gd::gd_coerce_float(lv_delay);
    gd::GdVal lv_flicker = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreContext__INNER__NativeFlicker), gd::SYM_new, nullptr, 0);
    gd::set_prop(gd_ctx, lv_flicker, SYM_GEN_ctx_3, gd::GdVal::from_obj(this));
    gd::GdVal lv_descr = gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2);
    gd::set_prop(gd_ctx, lv_flicker, SYM_GEN_limits_1510, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::get_prop(gd_ctx, lv_descr, SYM_GEN_flickerMinDist_1697), gd::get_prop(gd_ctx, lv_descr, SYM_GEN_flickerMaxDist_1698), gd::get_prop(gd_ctx, lv_descr, SYM_GEN_flickerMinSpeed_1699), gd::get_prop(gd_ctx, lv_descr, SYM_GEN_flickerMaxSpeed_1700)})));
    gd::set_prop(gd_ctx, lv_flicker, gd::SYM_length, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.3)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreContext::call_static_fn(gd_ctx, SYM_GEN__nativeF32_1502, _ca, 1, _out); return _out; })());
    gd::set_prop(gd_ctx, lv_flicker, SYM_GEN_playing_1512, gd::GdVal::from_bool(gd::native_scalar_eq(gd::get_prop(gd_ctx, lv_descr, SYM_GEN_identifier_1673), gd::GdVal::from_str(&battle_string_literals[0]))));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::get_prop(gd_ctx, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0), SYM_GEN_playerId_1046), gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_flicker}; return gd::native_inline_call(gd_ctx, this->f__opponent_flickers, gd::SYM_append, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {lv_flicker}; return gd::native_inline_call(gd_ctx, this->f__flickers, gd::SYM_append, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_flicker, gd::GdVal::from_str(&battle_string_literals[1]), lv_delay}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_callDelayed_1479, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_restoreFlickers(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_keep = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1190 = gd::gd_iter_seq(gd_ctx.arena, this->f__timed);
        gd::GdArr* _t1191 = (_t1190.kind == gd::GdVal::Kind::Arr) ? _t1190.arr : nullptr;
        uint32_t _len__t1192 = _t1191 ? _t1191->len : 0u;
        for (uint32_t _t1192 = 0; _t1192 < _len__t1192; ++_t1192) {
            gd::GdVal lv_pending = _t1191->data[_t1192];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_array_index(gd_ctx, lv_pending, gd::GdVal::from_int(1LL)), gd::GdVal::from_str(&battle_string_literals[2]))))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_pending}; return gd::native_inline_call(gd_ctx, lv_keep, gd::SYM_append, _ca, 1); })();
            }
        }
    }
    this->f__timed = lv_keep;
    this->f_lib_fires = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f__flickers = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f__opponent_flickers = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    (void)gd::native_inline_call(gd_ctx, this->f__opening_delay_ready, gd::SYM_clear, nullptr, 0);
    gd::GdVal lv_restored_delays = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1193 = gd::gd_iter_seq(gd_ctx.arena, this->f_flicker_initial);
        gd::GdArr* _t1194 = (_t1193.kind == gd::GdVal::Kind::Arr) ? _t1193.arr : nullptr;
        uint32_t _len__t1195 = _t1194 ? _t1194->len : 0u;
        for (uint32_t _t1195 = 0; _t1195 < _len__t1195; ++_t1195) {
            gd::GdVal lv_snapshot = _t1194->data[_t1195];
            gd::GdVal lv_flicker = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreContext__INNER__NativeFlicker), gd::SYM_new, nullptr, 0);
            gd::set_prop(gd_ctx, lv_flicker, SYM_GEN_ctx_3, gd::GdVal::from_obj(this));
            gd::set_prop(gd_ctx, lv_flicker, SYM_GEN_limits_1510, gd::native_array_index(gd_ctx, lv_snapshot, gd::GdVal::from_str(&battle_string_literals[3])));
            gd::set_prop(gd_ctx, lv_flicker, SYM_GEN_position_1511, ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4]), gd::native_array_index(gd_ctx, lv_snapshot, gd::GdVal::from_str(&battle_string_literals[5]))}; return gd::native_inline_call(gd_ctx, lv_snapshot, gd::SYM_get, _ca, 2); })())}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreContext::call_static_fn(gd_ctx, SYM_GEN__nativeF32_1502, _ca, 1, _out); return _out; })());
            gd::set_prop(gd_ctx, lv_flicker, SYM_GEN_speed_93, ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6]), gd::native_array_index(gd_ctx, lv_snapshot, gd::GdVal::from_str(&battle_string_literals[7]))}; return gd::native_inline_call(gd_ctx, lv_snapshot, gd::SYM_get, _ca, 2); })())}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreContext::call_static_fn(gd_ctx, SYM_GEN__nativeF32_1502, _ca, 1, _out); return _out; })());
            gd::set_prop(gd_ctx, lv_flicker, gd::SYM_length, ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_float(gd::native_array_index(gd_ctx, lv_snapshot, gd::GdVal::from_str(&battle_string_literals[8])))}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreContext::call_static_fn(gd_ctx, SYM_GEN__nativeF32_1502, _ca, 1, _out); return _out; })());
            gd::set_prop(gd_ctx, lv_flicker, SYM_GEN_playing_1512, gd::gd_coerce_bool(gd::native_array_index(gd_ctx, lv_snapshot, gd::GdVal::from_str(&battle_string_literals[9]))));
            gd::set_prop(gd_ctx, lv_flicker, SYM_GEN_inside_tree_1513, gd::gd_coerce_bool(gd::native_array_index(gd_ctx, lv_snapshot, gd::GdVal::from_str(&battle_string_literals[10]))));
            gd::set_prop(gd_ctx, lv_flicker, SYM_GEN_loop_1514, gd::gd_coerce_bool(gd::native_array_index(gd_ctx, lv_snapshot, gd::GdVal::from_str(&battle_string_literals[11]))));
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[12]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, lv_snapshot, gd::SYM_get, _ca, 2); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_flicker}; return gd::native_inline_call(gd_ctx, this->f__opponent_flickers, gd::SYM_append, _ca, 1); })();
            }
            else {
                (void)([&]() { gd::GdVal _ca[] = {lv_flicker}; return gd::native_inline_call(gd_ctx, this->f__flickers, gd::SYM_append, _ca, 1); })();
            }
            {
                gd::GdVal _t1196 = gd::gd_iter_seq(gd_ctx.arena, gd::native_array_index(gd_ctx, lv_snapshot, gd::GdVal::from_str(&battle_string_literals[13])));
                gd::GdArr* _t1197 = (_t1196.kind == gd::GdVal::Kind::Arr) ? _t1196.arr : nullptr;
                uint32_t _len__t1198 = _t1197 ? _t1197->len : 0u;
                for (uint32_t _t1198 = 0; _t1198 < _len__t1198; ++_t1198) {
                    gd::GdVal lv_pending = _t1197->data[_t1198];
                    (void)gd::GdVal::null();
                    if (gd::gd_truth(this->f_replay_native_scene_delays)) {
                        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_array_index(gd_ctx, lv_pending, gd::GdVal::from_str(&battle_string_literals[14])), lv_flicker, gd::gd_coerce_float(gd::native_array_index(gd_ctx, lv_pending, gd::GdVal::from_str(&battle_string_literals[15])))}))}; return gd::native_inline_call(gd_ctx, lv_restored_delays, gd::SYM_append, _ca, 1); })();
                    }
                    else {
                        (void)([&]() { gd::GdVal _ca[] = {lv_flicker, gd::GdVal::from_str(&battle_string_literals[1]), gd::gd_coerce_float(gd::native_array_index(gd_ctx, lv_pending, gd::GdVal::from_str(&battle_string_literals[16])))}; return this->fn_callDelayed(_ca, 3); })();
                    }
                }
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[17])}; return gd::native_inline_call(gd_ctx, lv_restored_delays, gd::SYM_sort_custom, _ca, 2); })();
    {
        gd::GdVal _t1199 = gd::gd_iter_seq(gd_ctx.arena, lv_restored_delays);
        gd::GdArr* _t1200 = (_t1199.kind == gd::GdVal::Kind::Arr) ? _t1199.arr : nullptr;
        uint32_t _len__t1201 = _t1200 ? _t1200->len : 0u;
        for (uint32_t _t1201 = 0; _t1201 < _len__t1201; ++_t1201) {
            gd::GdVal lv_entry = _t1200->data[_t1201];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(2LL)), gd::GdVal::from_int(0LL))))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(1LL))}; return gd::native_inline_call(gd_ctx, this->f__opening_delay_ready, gd::SYM_append, _ca, 1); })();
            }
            else {
                (void)([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(1LL)), gd::GdVal::from_str(&battle_string_literals[1]), gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(2LL))}; return this->fn_callDelayed(_ca, 3); })();
            }
        }
    }
    return gd::GdVal::null();
    }
    gd::GdVal lv_keep = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1190 = gd::gd_iter_seq(gd_ctx.arena, this->f__timed);
        gd::GdArr* _t1191 = (_t1190.kind == gd::GdVal::Kind::Arr) ? _t1190.arr : nullptr;
        uint32_t _len__t1192 = _t1191 ? _t1191->len : 0u;
        for (uint32_t _t1192 = 0; _t1192 < _len__t1192; ++_t1192) {
            gd::GdVal lv_pending = _t1191->data[_t1192];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_array_index(gd_ctx, lv_pending, gd::GdVal::from_int(1LL)), gd::GdVal::from_str(&battle_string_literals[2]))))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_pending}; return gd::native_inline_call(gd_ctx, lv_keep, gd::SYM_append, _ca, 1); })();
            }
        }
    }
    this->f__timed = lv_keep;
    this->f_lib_fires = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f__flickers = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f__opponent_flickers = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    (void)gd::native_inline_call(gd_ctx, this->f__opening_delay_ready, gd::SYM_clear, nullptr, 0);
    gd::GdVal lv_restored_delays = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1193 = gd::gd_iter_seq(gd_ctx.arena, this->f_flicker_initial);
        gd::GdArr* _t1194 = (_t1193.kind == gd::GdVal::Kind::Arr) ? _t1193.arr : nullptr;
        uint32_t _len__t1195 = _t1194 ? _t1194->len : 0u;
        for (uint32_t _t1195 = 0; _t1195 < _len__t1195; ++_t1195) {
            gd::GdVal lv_snapshot = _t1194->data[_t1195];
            gd::GdVal lv_flicker = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreContext__INNER__NativeFlicker), gd::SYM_new, nullptr, 0);
            gd::set_prop(gd_ctx, lv_flicker, SYM_GEN_ctx_3, gd::GdVal::from_obj(this));
            gd::set_prop(gd_ctx, lv_flicker, SYM_GEN_limits_1510, gd::native_array_index(gd_ctx, lv_snapshot, gd::GdVal::from_str(&battle_string_literals[3])));
            gd::set_prop(gd_ctx, lv_flicker, SYM_GEN_position_1511, ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4]), gd::native_array_index(gd_ctx, lv_snapshot, gd::GdVal::from_str(&battle_string_literals[5]))}; return gd::native_inline_call(gd_ctx, lv_snapshot, gd::SYM_get, _ca, 2); })())}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreContext::call_static_fn(gd_ctx, SYM_GEN__nativeF32_1502, _ca, 1, _out); return _out; })());
            gd::set_prop(gd_ctx, lv_flicker, SYM_GEN_speed_93, ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6]), gd::native_array_index(gd_ctx, lv_snapshot, gd::GdVal::from_str(&battle_string_literals[7]))}; return gd::native_inline_call(gd_ctx, lv_snapshot, gd::SYM_get, _ca, 2); })())}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreContext::call_static_fn(gd_ctx, SYM_GEN__nativeF32_1502, _ca, 1, _out); return _out; })());
            gd::set_prop(gd_ctx, lv_flicker, gd::SYM_length, ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_float(gd::native_array_index(gd_ctx, lv_snapshot, gd::GdVal::from_str(&battle_string_literals[8])))}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreContext::call_static_fn(gd_ctx, SYM_GEN__nativeF32_1502, _ca, 1, _out); return _out; })());
            gd::set_prop(gd_ctx, lv_flicker, SYM_GEN_playing_1512, gd::gd_coerce_bool(gd::native_array_index(gd_ctx, lv_snapshot, gd::GdVal::from_str(&battle_string_literals[9]))));
            gd::set_prop(gd_ctx, lv_flicker, SYM_GEN_inside_tree_1513, gd::gd_coerce_bool(gd::native_array_index(gd_ctx, lv_snapshot, gd::GdVal::from_str(&battle_string_literals[10]))));
            gd::set_prop(gd_ctx, lv_flicker, SYM_GEN_loop_1514, gd::gd_coerce_bool(gd::native_array_index(gd_ctx, lv_snapshot, gd::GdVal::from_str(&battle_string_literals[11]))));
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[12]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, lv_snapshot, gd::SYM_get, _ca, 2); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_flicker}; return gd::native_inline_call(gd_ctx, this->f__opponent_flickers, gd::SYM_append, _ca, 1); })();
            }
            else {
                (void)([&]() { gd::GdVal _ca[] = {lv_flicker}; return gd::native_inline_call(gd_ctx, this->f__flickers, gd::SYM_append, _ca, 1); })();
            }
            {
                gd::GdVal _t1196 = gd::gd_iter_seq(gd_ctx.arena, gd::native_array_index(gd_ctx, lv_snapshot, gd::GdVal::from_str(&battle_string_literals[13])));
                gd::GdArr* _t1197 = (_t1196.kind == gd::GdVal::Kind::Arr) ? _t1196.arr : nullptr;
                uint32_t _len__t1198 = _t1197 ? _t1197->len : 0u;
                for (uint32_t _t1198 = 0; _t1198 < _len__t1198; ++_t1198) {
                    gd::GdVal lv_pending = _t1197->data[_t1198];
                    (void)gd::GdVal::null();
                    if (gd::gd_truth(this->f_replay_native_scene_delays)) {
                        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_array_index(gd_ctx, lv_pending, gd::GdVal::from_str(&battle_string_literals[14])), lv_flicker, gd::gd_coerce_float(gd::native_array_index(gd_ctx, lv_pending, gd::GdVal::from_str(&battle_string_literals[15])))}))}; return gd::native_inline_call(gd_ctx, lv_restored_delays, gd::SYM_append, _ca, 1); })();
                    }
                    else {
                        (void)([&]() { gd::GdVal _ca[] = {lv_flicker, gd::GdVal::from_str(&battle_string_literals[1]), gd::gd_coerce_float(gd::native_array_index(gd_ctx, lv_pending, gd::GdVal::from_str(&battle_string_literals[16])))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_callDelayed_1479, _ca, 3); })();
                    }
                }
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[17])}; return gd::native_inline_call(gd_ctx, lv_restored_delays, gd::SYM_sort_custom, _ca, 2); })();
    {
        gd::GdVal _t1199 = gd::gd_iter_seq(gd_ctx.arena, lv_restored_delays);
        gd::GdArr* _t1200 = (_t1199.kind == gd::GdVal::Kind::Arr) ? _t1199.arr : nullptr;
        uint32_t _len__t1201 = _t1200 ? _t1200->len : 0u;
        for (uint32_t _t1201 = 0; _t1201 < _len__t1201; ++_t1201) {
            gd::GdVal lv_entry = _t1200->data[_t1201];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(2LL)), gd::GdVal::from_int(0LL))))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(1LL))}; return gd::native_inline_call(gd_ctx, this->f__opening_delay_ready, gd::SYM_append, _ca, 1); })();
            }
            else {
                (void)([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(1LL)), gd::GdVal::from_str(&battle_string_literals[1]), gd::native_array_index(gd_ctx, lv_entry, gd::GdVal::from_int(2LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_callDelayed_1479, _ca, 3); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn__scene_delay_created_before(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_left = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_right = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::from_bool(gd::gd_lt(gd::native_array_index(gd_ctx, lv_left, gd::GdVal::from_int(0LL)), gd::native_array_index(gd_ctx, lv_right, gd::GdVal::from_int(0LL))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_runOpeningSceneDelays(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1202 = gd::gd_iter_seq(gd_ctx.arena, this->f__opening_delay_ready);
        gd::GdArr* _t1203 = (_t1202.kind == gd::GdVal::Kind::Arr) ? _t1202.arr : nullptr;
        uint32_t _len__t1204 = _t1203 ? _t1203->len : 0u;
        for (uint32_t _t1204 = 0; _t1204 < _len__t1204; ++_t1204) {
            gd::GdVal lv_flicker = _t1203->data[_t1204];
            (void)gd::native_inline_call(gd_ctx, lv_flicker, SYM_GEN_playAni_1515, nullptr, 0);
        }
    }
    (void)gd::native_inline_call(gd_ctx, this->f__opening_delay_ready, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_tickOpponentFlickers(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    {
        gd::GdVal _t1205 = gd::gd_iter_seq(gd_ctx.arena, this->f__opponent_flickers);
        gd::GdArr* _t1206 = (_t1205.kind == gd::GdVal::Kind::Arr) ? _t1205.arr : nullptr;
        uint32_t _len__t1207 = _t1206 ? _t1206->len : 0u;
        for (uint32_t _t1207 = 0; _t1207 < _len__t1207; ++_t1207) {
            gd::GdVal lv_flicker = _t1206->data[_t1207];
            (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::native_inline_call(gd_ctx, lv_flicker, SYM_GEN_tick_1516, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_tickFlickers(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    {
        gd::GdVal _t1208 = gd::gd_iter_seq(gd_ctx.arena, this->f__flickers);
        gd::GdArr* _t1209 = (_t1208.kind == gd::GdVal::Kind::Arr) ? _t1208.arr : nullptr;
        uint32_t _len__t1210 = _t1209 ? _t1209->len : 0u;
        for (uint32_t _t1210 = 0; _t1210 < _len__t1210; ++_t1210) {
            gd::GdVal lv_flicker = _t1209->data[_t1210];
            (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::native_inline_call(gd_ctx, lv_flicker, SYM_GEN_tick_1516, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreContext(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__CoreContext>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,27u); return object; }
const gd::GdClassMeta META_Gd__gd_core__CoreContext = {CLS_Gd__gd_core__CoreContext, "CoreContext", "res://gd_core/CoreContext.gd", nullptr, false, _alloc_Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::get_static_prop_fn, &Gd__gd_core__CoreContext::call_static_fn};

void Gd__gd_core__CoreUtil::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_rng = gd::GdVal::null();
    this->f__ctx = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__CoreUtil::meta() const { return &META_Gd__gd_core__CoreUtil; }
gd::GdVal Gd__gd_core__CoreUtil::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_DictSorter_1808: return gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil__INNER__DictSorter);
        default: break;
    }
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreUtil::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreUtil::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_rng_1406: out = this->f_rng; return true;
        case SYM_GEN__ctx_1347: out = this->f__ctx; return true;
        case SYM_GEN_DictSorter_1808: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil__INNER__DictSorter); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreUtil::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_rng_1406: this->f_rng = val; return true;
        case SYM_GEN__ctx_1347: this->f__ctx = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreUtil::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_roll_1734: return true;
        case SYM_GEN_flip_1735: return true;
        case SYM_GEN_flipPercent_1736: return true;
        case SYM_GEN_flipRound_1737: return true;
        case SYM_GEN_flipWeighted_1738: return true;
        case SYM_GEN_pickRandomElement_1746: return true;
        case SYM_GEN_getArrayElement_1795: return true;
        case SYM_GEN_callNextFrame_1797: return true;
        case SYM_GEN_callDelayed_1479: return true;
        case SYM_GEN_callDelayed_process_1798: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreUtil::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_truth_1389: out = sf_truth(gd_ctx, args, argc); return true;
        case SYM_GEN_vec2_tile_data_1787: out = sf_vec2_tile_data(gd_ctx, args, argc); return true;
        case SYM_GEN_vec2_less_yx_1788: out = sf_vec2_less_yx(gd_ctx, args, argc); return true;
        case SYM_GEN_dictAdd_1789: out = sf_dictAdd(gd_ctx, args, argc); return true;
        case SYM_GEN_dictSub_1790: out = sf_dictSub(gd_ctx, args, argc); return true;
        case SYM_GEN_dictAddDict_1791: out = sf_dictAddDict(gd_ctx, args, argc); return true;
        case SYM_GEN_dictAppend_1792: out = sf_dictAppend(gd_ctx, args, argc); return true;
        case SYM_GEN_dictErase_1793: out = sf_dictErase(gd_ctx, args, argc); return true;
        case SYM_GEN_sortDict_1794: out = sf_sortDict(gd_ctx, args, argc); return true;
        case SYM_GEN_roll_1734: out = fn_roll(args, argc); return true;
        case SYM_GEN_flip_1735: out = fn_flip(args, argc); return true;
        case SYM_GEN_flipPercent_1736: out = fn_flipPercent(args, argc); return true;
        case SYM_GEN_flipRound_1737: out = fn_flipRound(args, argc); return true;
        case SYM_GEN_flipWeighted_1738: out = fn_flipWeighted(args, argc); return true;
        case SYM_GEN_pickRandomElement_1746: out = fn_pickRandomElement(args, argc); return true;
        case SYM_GEN_getArrayElement_1795: out = fn_getArrayElement(args, argc); return true;
        case SYM_GEN_changeTimer_1796: out = sf_changeTimer(gd_ctx, args, argc); return true;
        case SYM_GEN_callNextFrame_1797: out = fn_callNextFrame(args, argc); return true;
        case SYM_GEN_callDelayed_1479: out = fn_callDelayed(args, argc); return true;
        case SYM_GEN_callDelayed_process_1798: out = fn_callDelayed_process(args, argc); return true;
        case SYM_GEN_arrayAsIndexDict_1799: out = sf_arrayAsIndexDict(gd_ctx, args, argc); return true;
        case SYM_GEN_invertDictionary_1800: out = sf_invertDictionary(gd_ctx, args, argc); return true;
        case SYM_GEN_filterDuplicates_1801: out = sf_filterDuplicates(gd_ctx, args, argc); return true;
        case SYM_GEN_countDuplicates_1802: out = sf_countDuplicates(gd_ctx, args, argc); return true;
        case SYM_GEN_flatten_1803: out = sf_flatten(gd_ctx, args, argc); return true;
        case SYM_GEN_rotDif_1804: out = sf_rotDif(gd_ctx, args, argc); return true;
        case SYM_GEN_isItemDescriptor_1805: out = sf_isItemDescriptor(gd_ctx, args, argc); return true;
        case SYM_GEN_eassert_1806: out = sf_eassert(gd_ctx, args, argc); return true;
        case SYM_GEN_eprint_1807: out = sf_eprint(gd_ctx, args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreUtil::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_truth_1389: out = sf_truth(gd_ctx, args, argc); return true;
        case SYM_GEN_vec2_tile_data_1787: out = sf_vec2_tile_data(gd_ctx, args, argc); return true;
        case SYM_GEN_vec2_less_yx_1788: out = sf_vec2_less_yx(gd_ctx, args, argc); return true;
        case SYM_GEN_dictAdd_1789: out = sf_dictAdd(gd_ctx, args, argc); return true;
        case SYM_GEN_dictSub_1790: out = sf_dictSub(gd_ctx, args, argc); return true;
        case SYM_GEN_dictAddDict_1791: out = sf_dictAddDict(gd_ctx, args, argc); return true;
        case SYM_GEN_dictAppend_1792: out = sf_dictAppend(gd_ctx, args, argc); return true;
        case SYM_GEN_dictErase_1793: out = sf_dictErase(gd_ctx, args, argc); return true;
        case SYM_GEN_sortDict_1794: out = sf_sortDict(gd_ctx, args, argc); return true;
        case SYM_GEN_changeTimer_1796: out = sf_changeTimer(gd_ctx, args, argc); return true;
        case SYM_GEN_arrayAsIndexDict_1799: out = sf_arrayAsIndexDict(gd_ctx, args, argc); return true;
        case SYM_GEN_invertDictionary_1800: out = sf_invertDictionary(gd_ctx, args, argc); return true;
        case SYM_GEN_filterDuplicates_1801: out = sf_filterDuplicates(gd_ctx, args, argc); return true;
        case SYM_GEN_countDuplicates_1802: out = sf_countDuplicates(gd_ctx, args, argc); return true;
        case SYM_GEN_flatten_1803: out = sf_flatten(gd_ctx, args, argc); return true;
        case SYM_GEN_rotDif_1804: out = sf_rotDif(gd_ctx, args, argc); return true;
        case SYM_GEN_isItemDescriptor_1805: out = sf_isItemDescriptor(gd_ctx, args, argc); return true;
        case SYM_GEN_eassert_1806: out = sf_eassert(gd_ctx, args, argc); return true;
        case SYM_GEN_eprint_1807: out = sf_eprint(gd_ctx, args, argc); return true;
        default: break;
    }
    return false;
}
gd::GdVal Gd__gd_core__CoreUtil::fn__init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__rng = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    this->f_rng = lv__rng;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_truth(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_v = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_v}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1389, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_vec2_tile_data(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_a = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_b = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::get_prop(gd_ctx, lv_a, gd::SYM_x), gd::get_prop(gd_ctx, lv_b, gd::SYM_x))))) {
        return gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, lv_a, gd::SYM_y), gd::get_prop(gd_ctx, lv_b, gd::SYM_y)));
    }
    return gd::GdVal::from_bool(gd::gd_lt(gd::get_prop(gd_ctx, lv_a, gd::SYM_x), gd::get_prop(gd_ctx, lv_b, gd::SYM_x)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_vec2_less_yx(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_a = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_b = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::get_prop(gd_ctx, lv_a, gd::SYM_y), gd::get_prop(gd_ctx, lv_b, gd::SYM_y))))) {
        return gd::GdVal::from_bool(gd::gd_lt(gd::get_prop(gd_ctx, lv_a, gd::SYM_x), gd::get_prop(gd_ctx, lv_b, gd::SYM_x)));
    }
    return gd::GdVal::from_bool(gd::gd_lt(gd::get_prop(gd_ctx, lv_a, gd::SYM_y), gd::get_prop(gd_ctx, lv_b, gd::SYM_y)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_dictAdd(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dict = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_key = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_val = (_argc > 2) ? _args[2] : (gd::GdVal::from_int(1LL));
    gd::GdVal lv_base = (_argc > 3) ? _args[3] : (gd::GdVal::from_int(0LL));
    gd::GdVal lv_newVal = gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_key, lv_base}; return gd::native_inline_call(gd_ctx, lv_dict, gd::SYM_get, _ca, 2); })(), lv_val);
    { gd::GdVal _t1211 = lv_dict; gd::GdVal _t1212 = lv_key; gd::native_array_set_index(gd_ctx, _t1211, _t1212, lv_newVal); }
    return lv_newVal;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_dictSub(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dict = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_key = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_val = (_argc > 2) ? _args[2] : (gd::GdVal::from_int(1LL));
    gd::GdVal lv_val2 = gd::gd_sub(([&]() { gd::GdVal _ca[] = {lv_key, gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, lv_dict, gd::SYM_get, _ca, 2); })(), lv_val);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(lv_val2, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_key}; return gd::native_inline_call(gd_ctx, lv_dict, gd::SYM_erase, _ca, 1); })();
    }
    else {
        { gd::GdVal _t1213 = lv_dict; gd::GdVal _t1214 = lv_key; gd::native_array_set_index(gd_ctx, _t1213, _t1214, lv_val2); }
    }
    return lv_val2;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_dictAddDict(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dict1 = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_dict2 = (_argc > 1) ? _args[1] : gd::GdVal::null();
    {
        gd::GdVal _t1215 = gd::gd_iter_seq(gd_ctx.arena, lv_dict2);
        gd::GdArr* _t1216 = (_t1215.kind == gd::GdVal::Kind::Arr) ? _t1215.arr : nullptr;
        uint32_t _len__t1217 = _t1216 ? _t1216->len : 0u;
        for (uint32_t _t1217 = 0; _t1217 < _len__t1217; ++_t1217) {
            gd::GdVal lv_key = _t1216->data[_t1217];
            (void)([&]() { gd::GdVal _ca[] = {lv_dict1, lv_key, gd::native_array_index(gd_ctx, lv_dict2, lv_key)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreUtil::call_static_fn(gd_ctx, SYM_GEN_dictAdd_1789, _ca, 3, _out); return _out; })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_dictAppend(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dict = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_key = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 2) ? _args[2] : gd::GdVal::null();
    if (gd::gd_truth(gd::gd_in(lv_key, lv_dict))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_value}; return gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, lv_dict, lv_key), gd::SYM_append, _ca, 1); })();
    }
    else {
        { gd::GdVal _t1218 = lv_dict; gd::GdVal _t1219 = lv_key; gd::native_array_set_index(gd_ctx, _t1218, _t1219, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_value}))); }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_dictErase(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dict = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_key = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_valueToErase = (_argc > 2) ? _args[2] : gd::GdVal::null();
    if (gd::gd_truth(gd::gd_in(lv_key, lv_dict))) {
        gd::GdVal lv_arr = gd::native_array_index(gd_ctx, lv_dict, lv_key);
        (void)([&]() { gd::GdVal _ca[] = {lv_valueToErase}; return gd::native_inline_call(gd_ctx, lv_arr, gd::SYM_erase, _ca, 1); })();
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_arr, gd::SYM_empty, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_key}; return gd::native_inline_call(gd_ctx, lv_dict, gd::SYM_erase, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_sortDict(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dict = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_rng = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_shuffleBeforeSort = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    gd::GdVal lv_sorted = gd::native_inline_call(gd_ctx, lv_dict, gd::SYM_keys, nullptr, 0);
    if (gd::gd_truth(lv_shuffleBeforeSort)) {
        (void)([&]() { gd::GdVal _ca[] = {lv_sorted}; return gd::native_inline_call(gd_ctx, lv_rng, gd::SYM_shuffle, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_dict}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil__INNER__DictSorter), gd::SYM_new, _ca, 1); })(), gd::GdVal::from_str(&battle_string_literals[18])}; return gd::native_inline_call(gd_ctx, lv_sorted, gd::SYM_sort_custom, _ca, 2); })();
    return lv_sorted;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_roll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_maximum = (_argc > 0) ? _args[0] : (gd::GdVal::from_float(100.0));
    return ([&]() { gd::GdVal _ca[] = {lv_maximum}; return gd::native_inline_call(gd_ctx, this->f_rng, SYM_GEN_roll_1734, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_flip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : (gd::GdVal::from_float(0.5));
    return ([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::native_inline_call(gd_ctx, this->f_rng, SYM_GEN_flip_1735, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_flipPercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::native_inline_call(gd_ctx, this->f_rng, SYM_GEN_flipPercent_1736, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_flipRound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::native_inline_call(gd_ctx, this->f_rng, SYM_GEN_flipRound_1737, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_flipWeighted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_weights = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_weights}; return gd::native_inline_call(gd_ctx, this->f_rng, SYM_GEN_flipWeighted_1738, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_pickRandomElement(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_array = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_array}; return gd::native_inline_call(gd_ctx, this->f_rng, SYM_GEN_pickRandomElement_1746, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_getArrayElement(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_array = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_index = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_index = gd::gd_coerce_int(lv_index);
    gd::GdVal lv_default = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_index, gd::gd_sub(gd::native_inline_call(gd_ctx, lv_array, gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL)))))) {
        return lv_default;
    }
    else {
        return gd::native_array_index(gd_ctx, lv_array, lv_index);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_changeTimer(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_timer = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_t = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_t = gd::gd_coerce_float(lv_t);
    gd::GdVal lv_timeLeft = gd::native_inline_call(gd_ctx, lv_timer, SYM_GEN_get_time_left_1777, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, lv_t, lv_timeLeft)}; return gd::native_inline_call(gd_ctx, lv_timer, SYM_GEN_start_1779, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_callNextFrame(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_methodName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_arguments = (_argc > 2) ? _args[2] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    (void)([&]() { gd::GdVal _ca[] = {lv_target, lv_methodName, lv_arguments}; return gd::native_inline_call(gd_ctx, this->f__ctx, SYM_GEN_connectIdleFrameOnce_1485, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_callDelayed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_methodName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_delay = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_delay = gd::gd_coerce_float(lv_delay);
    gd::GdVal lv_binds = (_argc > 3) ? _args[3] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    (void)([&]() { gd::GdVal _ca[] = {lv_target, lv_methodName, lv_delay, lv_binds}; return gd::native_inline_call(gd_ctx, this->f__ctx, SYM_GEN_callDelayed_1479, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_callDelayed_process(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_methodName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_delay = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_delay = gd::gd_coerce_float(lv_delay);
    gd::GdVal lv_binds = (_argc > 3) ? _args[3] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    (void)([&]() { gd::GdVal _ca[] = {lv_target, lv_methodName, lv_delay, lv_binds}; return gd::native_inline_call(gd_ctx, this->f__ctx, SYM_GEN_callDelayed_1479, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_arrayAsIndexDict(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_array = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_invertedDict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t1220 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, lv_array, gd::SYM_size, nullptr, 0));
        gd::GdArr* _t1221 = (_t1220.kind == gd::GdVal::Kind::Arr) ? _t1220.arr : nullptr;
        uint32_t _len__t1222 = _t1221 ? _t1221->len : 0u;
        for (uint32_t _t1222 = 0; _t1222 < _len__t1222; ++_t1222) {
            gd::GdVal lv_i = _t1221->data[_t1222];
            { gd::GdVal _t1223 = lv_invertedDict; gd::GdVal _t1224 = gd::native_array_index(gd_ctx, lv_array, lv_i); gd::native_array_set_index(gd_ctx, _t1223, _t1224, lv_i); }
        }
    }
    return lv_invertedDict;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_invertDictionary(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dict = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_invertedDict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t1225 = gd::gd_iter_seq(gd_ctx.arena, lv_dict);
        gd::GdArr* _t1226 = (_t1225.kind == gd::GdVal::Kind::Arr) ? _t1225.arr : nullptr;
        uint32_t _len__t1227 = _t1226 ? _t1226->len : 0u;
        for (uint32_t _t1227 = 0; _t1227 < _len__t1227; ++_t1227) {
            gd::GdVal lv_key = _t1226->data[_t1227];
            { gd::GdVal _t1228 = lv_invertedDict; gd::GdVal _t1229 = gd::native_array_index(gd_ctx, lv_dict, lv_key); gd::native_array_set_index(gd_ctx, _t1228, _t1229, lv_key); }
        }
    }
    return lv_invertedDict;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_filterDuplicates(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_arr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_dict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t1230 = gd::gd_iter_seq(gd_ctx.arena, lv_arr);
        gd::GdArr* _t1231 = (_t1230.kind == gd::GdVal::Kind::Arr) ? _t1230.arr : nullptr;
        uint32_t _len__t1232 = _t1231 ? _t1231->len : 0u;
        for (uint32_t _t1232 = 0; _t1232 < _len__t1232; ++_t1232) {
            gd::GdVal lv_a = _t1231->data[_t1232];
            { gd::GdVal _t1233 = lv_dict; gd::GdVal _t1234 = lv_a; gd::native_array_set_index(gd_ctx, _t1233, _t1234, gd::GdVal::from_bool(true)); }
        }
    }
    return gd::native_inline_call(gd_ctx, lv_dict, gd::SYM_keys, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_countDuplicates(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_arr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_before = gd::native_inline_call(gd_ctx, lv_arr, gd::SYM_size, nullptr, 0);
    gd::GdVal lv_filtered = ([&]() { gd::GdVal _ca[] = {lv_arr}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreUtil::call_static_fn(gd_ctx, SYM_GEN_filterDuplicates_1801, _ca, 1, _out); return _out; })();
    return gd::gd_sub(lv_before, gd::native_inline_call(gd_ctx, lv_filtered, gd::SYM_size, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_flatten(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_arr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_flattened = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1235 = gd::gd_iter_seq(gd_ctx.arena, lv_arr);
        gd::GdArr* _t1236 = (_t1235.kind == gd::GdVal::Kind::Arr) ? _t1235.arr : nullptr;
        uint32_t _len__t1237 = _t1236 ? _t1236->len : 0u;
        for (uint32_t _t1237 = 0; _t1237 < _len__t1237; ++_t1237) {
            gd::GdVal lv_inner = _t1236->data[_t1237];
            (void)([&]() { gd::GdVal _ca[] = {lv_inner}; return gd::native_inline_call(gd_ctx, lv_flattened, gd::SYM_append_array, _ca, 1); })();
        }
    }
    return lv_flattened;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_rotDif(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_rot1 = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_rot2 = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_rot = gd::gd_abs(gd::gd_sub(lv_rot1, lv_rot2));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_rot, gd::GdVal::from_float(3.14159265358979323846))))) {
        return gd::gd_sub(gd::gd_mul(gd::GdVal::from_int(2LL), gd::GdVal::from_float(3.14159265358979323846)), lv_rot);
    }
    return lv_rot;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_isItemDescriptor(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_object = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_object, gd::GdVal::null())))) {
        return gd::GdVal::from_bool(false);
    }
    return gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, lv_object, gd::SYM_get_script, nullptr, 0), gd::load_resource(((gd::GdVal::from_str(&battle_string_literals[19])).kind == gd::GdVal::Kind::Str && (gd::GdVal::from_str(&battle_string_literals[19])).str) ? std::string_view((gd::GdVal::from_str(&battle_string_literals[19])).str->data, (gd::GdVal::from_str(&battle_string_literals[19])).str->len) : std::string_view(""))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_eassert(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_toTest = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(false));
    lv_toTest = gd::gd_coerce_bool(lv_toTest);
    if (gd::gd_truth(gd::GdVal::from_bool(false))) {
        (void)gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_eprint(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_text = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_arg1 = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_arg2 = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_arg3 = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(false))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_arg3, gd::GdVal::null())))) {
            (void)gd::GdVal::null();
        }
        else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_arg2, gd::GdVal::null())))) {
            (void)gd::GdVal::null();
        }
        else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_arg1, gd::GdVal::null())))) {
            (void)gd::GdVal::null();
        }
        else {
            (void)gd::GdVal::null();
        }
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreUtil(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__CoreUtil>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,42u); return object; }
const gd::GdClassMeta META_Gd__gd_core__CoreUtil = {CLS_Gd__gd_core__CoreUtil, "CoreUtil", "res://gd_core/CoreUtil.gd", nullptr, false, _alloc_Gd__gd_core__CoreUtil, &Gd__gd_core__CoreUtil::get_static_prop_fn, &Gd__gd_core__CoreUtil::call_static_fn};

void Gd__gd_core__DjinnLamp::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_activated = gd::GdVal::from_bool(false);
    this->f_affectedWeapon = gd::GdVal::null();
    this->f_stacksNeeded = gd::GdVal::null();
    this->f_healthNeeded = gd::GdVal::null();
    this->f_activationParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__DjinnLamp::meta() const { return &META_Gd__gd_core__DjinnLamp; }
gd::GdVal Gd__gd_core__DjinnLamp::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_numIngredients_1856: return gd::GdVal::from_float(5.0);
        default: break;
    }
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__DjinnLamp::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__DjinnLamp::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activated_1314: out = this->f_activated; return true;
        case SYM_GEN_affectedWeapon_948: out = this->f_affectedWeapon; return true;
        case SYM_GEN_stacksNeeded_1857: out = this->f_stacksNeeded; return true;
        case SYM_GEN_healthNeeded_1858: out = this->f_healthNeeded; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_numIngredients_1856: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__DjinnLamp::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1314: this->f_activated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_affectedWeapon_948: this->f_affectedWeapon = val; return true;
        case SYM_GEN_stacksNeeded_1857: this->f_stacksNeeded = val; return true;
        case SYM_GEN_healthNeeded_1858: this->f_healthNeeded = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__DjinnLamp::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_checkStacks_1859: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__DjinnLamp::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_checkStacks_1859: out = fn_checkStacks(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__DjinnLamp::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__DjinnLamp::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DjinnLamp::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    this->f_affectedWeapon = gd::GdVal::null();
    gd::GdVal lv_affectedItems = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, lv_affectedItems, gd::SYM_empty, nullptr, 0))))) {
        this->f_affectedWeapon = gd::native_array_index(gd_ctx, lv_affectedItems, gd::GdVal::from_int(0LL));
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[20]), gd::GdVal::from_str(&battle_string_literals[21])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[22]), gd::GdVal::from_str(&battle_string_literals[21])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[23]), gd::GdVal::from_str(&battle_string_literals[21])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[24]), gd::GdVal::from_str(&battle_string_literals[21])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[25]), gd::GdVal::from_str(&battle_string_literals[21])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[26]), gd::GdVal::from_str(&battle_string_literals[21])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DjinnLamp::fn_checkStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_changeAmount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(this->f_activated)) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_progress = gd::GdVal::from_float(0.0);
    lv_progress = gd::gd_add(gd_ctx, lv_progress, gd::gd_div(gd_ctx, gd::gd_min(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getBlock_204, nullptr, 0), this->f_stacksNeeded), gd::gd_coerce_float(this->f_stacksNeeded)));
    lv_progress = gd::gd_add(gd_ctx, lv_progress, gd::gd_div(gd_ctx, gd::gd_min(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getSpikes_1223, nullptr, 0), this->f_stacksNeeded), gd::gd_coerce_float(this->f_stacksNeeded)));
    lv_progress = gd::gd_add(gd_ctx, lv_progress, gd::gd_div(gd_ctx, gd::gd_min(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_stacksNeeded), gd::gd_coerce_float(this->f_stacksNeeded)));
    lv_progress = gd::gd_add(gd_ctx, lv_progress, gd::gd_div(gd_ctx, gd::gd_min(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), this->f_stacksNeeded), gd::gd_coerce_float(this->f_stacksNeeded)));
    lv_progress = gd::gd_add(gd_ctx, lv_progress, gd::gd_div(gd_ctx, gd::gd_min(gd::gd_sub(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getCurrentHealth_1154, nullptr, 0), gd::GdVal::from_int(1LL)), this->f_healthNeeded), gd::gd_coerce_float(this->f_healthNeeded)));
    lv_progress = gd::gd_div(gd_ctx, lv_progress, Gd__gd_core__DjinnLamp::get_static_const_or_enum(gd_ctx, SYM_GEN_numIngredients_1856));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_changeAmount, gd::GdVal::from_int(0LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_progress, gd::GdVal::from_float(0.9999))))) {
            this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_LoggingMode_1599), SYM_GEN_Delayed_2686)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_setLoggingMode_1588, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_stacksNeeded, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useBlock_207, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_stacksNeeded, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useSpikes_337, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_stacksNeeded, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_stacksNeeded, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useLucky_350, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_healthNeeded, gd::GdVal::from_obj(this), lv_event}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_loseHealth_1157, _ca, 3); })();
            gd::GdVal lv_bonusDamage = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {lv_bonusDamage}; return gd::native_inline_call(gd_ctx, this->f_affectedWeapon, SYM_GEN_addBonusDamage_161, _ca, 1); })();
            gd::GdVal lv_dmgBuffEvent = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), this->f_affectedWeapon, lv_bonusDamage, gd::get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_playerId_1046), lv_event}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_DamageBuff_1374, _ca, 5); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_dmgBuffEvent}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_logEvent_1357, _ca, 1); })();
            (void)gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_flushLoggingQueue_1591, nullptr, 0);
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DjinnLamp::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numLucky = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0);
    gd::GdVal lv_numSpikes = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getSpikes_1223, nullptr, 0);
    gd::GdVal lv_numMana = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_numLucky, lv_numSpikes)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_numLucky, lv_numMana)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
        }
    }
    else {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_numSpikes, lv_numMana)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DjinnLamp::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_stacksNeeded = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0);
    this->f_healthNeeded = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__DjinnLamp(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__DjinnLamp>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,57u); return object; }
const gd::GdClassMeta META_Gd__gd_core__DjinnLamp = {CLS_Gd__gd_core__DjinnLamp, "DjinnLamp", "res://gd_core/DjinnLamp.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__DjinnLamp, &Gd__gd_core__DjinnLamp::get_static_prop_fn, &Gd__gd_core__DjinnLamp::call_static_fn};

void Gd__gd_core__Hammer::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__Hammer::meta() const { return &META_Gd__gd_core__Hammer; }
gd::GdVal Gd__gd_core__Hammer::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Hammer::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Hammer::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__Hammer::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Hammer::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN_onFusingAsCatalystFinished_843: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Hammer::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onFusingAsCatalystFinished_843: out = fn_onFusingAsCatalystFinished(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Hammer::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Hammer::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[27])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_330, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Hammer::fn_onFusingAsCatalystFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN_onFusingAsCatalystFinished_843, nullptr, 0, _out); return _out; })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_778, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Hammer::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Hammer(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__Hammer>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,73u); return object; }
const gd::GdClassMeta META_Gd__gd_core__Hammer = {CLS_Gd__gd_core__Hammer, "Hammer", "res://gd_core/Hammer.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__Hammer, &Gd__gd_core__Hammer::get_static_prop_fn, &Gd__gd_core__Hammer::call_static_fn};

void Gd__gd_core__LeatherHelm::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_buffsActive = gd::GdVal::from_int(0LL);
    this->f_buffTimer = gd::GdVal::null();
    this->f_activationParticles = gd::GdVal::null();
    this->f_damReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__LeatherHelm::meta() const { return &META_Gd__gd_core__LeatherHelm; }
gd::GdVal Gd__gd_core__LeatherHelm::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__LeatherHelm::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__LeatherHelm::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_buffsActive_1872: out = this->f_buffsActive; return true;
        case SYM_GEN_buffTimer_1819: out = this->f_buffTimer; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_damReduction_1873: out = this->f_damReduction; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__LeatherHelm::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffsActive_1872: this->f_buffsActive = val; return true;
        case SYM_GEN_buffTimer_1819: this->f_buffTimer = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_damReduction_1873: this->f_damReduction = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__LeatherHelm::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getStunProtectChance_1907: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreCombatStart_125: return true;
        case SYM_GEN_getBuffDur_1908: return true;
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
bool Gd__gd_core__LeatherHelm::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getStunProtectChance_1907: out = fn_getStunProtectChance(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreCombatStart_125: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_getBuffDur_1908: out = fn_getBuffDur(args, argc); return true;
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
bool Gd__gd_core__LeatherHelm::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_getStunProtectChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeCritResistance_1173, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStunProtectChance_1907, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeStunResistance_1176, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
    this->f_buffsActive = gd::gd_add(gd_ctx, this->f_buffsActive, gd::GdVal::from_int(1LL));
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBuffDur_1908, nullptr, 0)}; return gd::native_inline_call(gd_ctx, this->f_buffTimer, SYM_GEN_start_1779, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_getBuffDur(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[28])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
    this->f_buffsActive = gd::gd_sub(this->f_buffsActive, gd::GdVal::from_int(1LL));
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_buffsActive = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__buffsActive = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv__buffsActive, gd::GdVal::from_int(0LL))))) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[29]), gd::GdVal::from_str(&battle_string_literals[30]), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_damReduction = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__LeatherHelm(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__LeatherHelm>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,89u); return object; }
const gd::GdClassMeta META_Gd__gd_core__LeatherHelm = {CLS_Gd__gd_core__LeatherHelm, "LeatherHelm", "res://gd_core/LeatherHelm.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__LeatherHelm, &Gd__gd_core__LeatherHelm::get_static_prop_fn, &Gd__gd_core__LeatherHelm::call_static_fn};

void Gd__gd_core__Pandamonium::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__Pandamonium::meta() const { return &META_Gd__gd_core__Pandamonium; }
gd::GdVal Gd__gd_core__Pandamonium::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Pandamonium::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Pandamonium::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__Pandamonium::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Pandamonium::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onFoodActivated_1956: return true;
        case SYM_GEN_getCraftingOffset_850: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Pandamonium::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onFoodActivated_1956: out = fn_onFoodActivated(args, argc); return true;
        case SYM_GEN_getCraftingOffset_850: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Pandamonium::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Pandamonium::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Pandamonium::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1238 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1239 = (_t1238.kind == gd::GdVal::Kind::Arr) ? _t1238.arr : nullptr;
        uint32_t _len__t1240 = _t1239 ? _t1239->len : 0u;
        for (uint32_t _t1240 = 0; _t1240 < _len__t1240; ++_t1240) {
            gd::GdVal lv_item = _t1239->data[_t1240];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[31]), gd::GdVal::from_str(&battle_string_literals[32])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changePoisonCritChancePercent_1283, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Pandamonium::fn_onFoodActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Pandamonium::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1241 = lv_forDirection;
        if (gd::native_scalar_eq(_t1241, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(1LL)).as_float());
        }
        else if (gd::native_scalar_eq(_t1241, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
        else if (gd::native_scalar_eq(_t1241, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::native_scalar_eq(_t1241, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Pandamonium::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Pandamonium(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__Pandamonium>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,103u); return object; }
const gd::GdClassMeta META_Gd__gd_core__Pandamonium = {CLS_Gd__gd_core__Pandamonium, "Pandamonium", "res://gd_core/Pandamonium.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__Pandamonium, &Gd__gd_core__Pandamonium::get_static_prop_fn, &Gd__gd_core__Pandamonium::call_static_fn};

void Gd__gd_core__RainbowGoobertRanger::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Goobert::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__RainbowGoobertRanger::meta() const { return &META_Gd__gd_core__RainbowGoobertRanger; }
gd::GdVal Gd__gd_core__RainbowGoobertRanger::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__RainbowGoobertRanger::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__RainbowGoobertRanger::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Goobert::get_prop(prop, out);
}
bool Gd__gd_core__RainbowGoobertRanger::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__RainbowGoobertRanger::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Goobert::has_own_method(m);
}
bool Gd__gd_core__RainbowGoobertRanger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__RainbowGoobertRanger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__RainbowGoobertRanger::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_267, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_213, _ca, 1); })();
    {
        gd::GdVal _t1242 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1243 = (_t1242.kind == gd::GdVal::Kind::Arr) ? _t1242.arr : nullptr;
        uint32_t _len__t1244 = _t1243 ? _t1243->len : 0u;
        for (uint32_t _t1244 = 0; _t1244 < _len__t1244; ++_t1244) {
            gd::GdVal lv_item = _t1243->data[_t1244];
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP6_268, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RainbowGoobertRanger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__RainbowGoobertRanger(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__RainbowGoobertRanger>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,120u); return object; }
const gd::GdClassMeta META_Gd__gd_core__RainbowGoobertRanger = {CLS_Gd__gd_core__RainbowGoobertRanger, "RainbowGoobertRanger", "res://gd_core/RainbowGoobertRanger.gd", &META_Gd__gd_core__Goobert, false, _alloc_Gd__gd_core__RainbowGoobertRanger, &Gd__gd_core__RainbowGoobertRanger::get_static_prop_fn, &Gd__gd_core__RainbowGoobertRanger::call_static_fn};

void Gd__gd_core__StoneHelm::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__LeatherHelm::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__StoneHelm::meta() const { return &META_Gd__gd_core__StoneHelm; }
gd::GdVal Gd__gd_core__StoneHelm::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__LeatherHelm::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__StoneHelm::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__StoneHelm::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__LeatherHelm::get_prop(prop, out);
}
bool Gd__gd_core__StoneHelm::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__LeatherHelm::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__StoneHelm::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getStunProtectChance_1907: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::has_own_method(m);
}
bool Gd__gd_core__StoneHelm::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getStunProtectChance_1907: out = fn_getStunProtectChance(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__StoneHelm::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__LeatherHelm::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__StoneHelm::fn_getStunProtectChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StoneHelm::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN_onCombatStart_934, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StoneHelm::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__StoneHelm(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__StoneHelm>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,137u); return object; }
const gd::GdClassMeta META_Gd__gd_core__StoneHelm = {CLS_Gd__gd_core__StoneHelm, "StoneHelm", "res://gd_core/StoneHelm.gd", &META_Gd__gd_core_items__LeatherHelm, false, _alloc_Gd__gd_core__StoneHelm, &Gd__gd_core__StoneHelm::get_static_prop_fn, &Gd__gd_core__StoneHelm::call_static_fn};

void Gd__gd_core__VampiricArmor::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__VampiricArmor::meta() const { return &META_Gd__gd_core__VampiricArmor; }
gd::GdVal Gd__gd_core__VampiricArmor::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__VampiricArmor::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__VampiricArmor::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__VampiricArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__VampiricArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__VampiricArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__VampiricArmor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__VampiricArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_healthToBlock_328, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__VampiricArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_healthToBlock_328, _ca, 2); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__VampiricArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__VampiricArmor(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__VampiricArmor>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,149u); return object; }
const gd::GdClassMeta META_Gd__gd_core__VampiricArmor = {CLS_Gd__gd_core__VampiricArmor, "VampiricArmor", "res://gd_core/VampiricArmor.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__VampiricArmor, &Gd__gd_core__VampiricArmor::get_static_prop_fn, &Gd__gd_core__VampiricArmor::call_static_fn};

void Gd__gd_core_items__ArtifactStoneHeat::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Stone::init_fields(gd_ctx);
    this->f_dmgBonusActive = gd::GdVal::from_bool(false);
    this->f_activationParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__ArtifactStoneHeat::meta() const { return &META_Gd__gd_core_items__ArtifactStoneHeat; }
gd::GdVal Gd__gd_core_items__ArtifactStoneHeat::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Stone::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__ArtifactStoneHeat::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__ArtifactStoneHeat::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_dmgBonusActive_911: out = this->f_dmgBonusActive; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Stone::get_prop(prop, out);
}
bool Gd__gd_core_items__ArtifactStoneHeat::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_dmgBonusActive_911: this->f_dmgBonusActive = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Stone::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__ArtifactStoneHeat::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onHeatChanged_913: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN_preHit_907: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Stone::has_own_method(m);
}
bool Gd__gd_core_items__ArtifactStoneHeat::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onHeatChanged_913: out = fn_onHeatChanged(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_preHit_907: out = fn_preHit(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Stone::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__ArtifactStoneHeat::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Stone::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__ArtifactStoneHeat::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ArtifactStoneHeat::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[33]), gd::GdVal::from_str(&battle_string_literals[34])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    this->f_dmgBonusActive = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ArtifactStoneHeat::fn_onHeatChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_dmgBonusActive))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getHeat_1251, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0))))) {
            this->f_dmgBonusActive = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
            {
                gd::GdVal _t1245 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
                gd::GdArr* _t1246 = (_t1245.kind == gd::GdVal::Kind::Arr) ? _t1245.arr : nullptr;
                uint32_t _len__t1247 = _t1246 ? _t1246->len : 0u;
                for (uint32_t _t1247 = 0; _t1247 < _len__t1247; ++_t1247) {
                    gd::GdVal lv_weapon = _t1246->data[_t1247];
                    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_weapon, SYM_GEN_addBonusDamage_161, _ca, 1); })();
                }
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ArtifactStoneHeat::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ArtifactStoneHeat::fn_preHit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ArtifactStoneHeat::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Stone::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__ArtifactStoneHeat(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__ArtifactStoneHeat>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,164u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__ArtifactStoneHeat = {CLS_Gd__gd_core_items__ArtifactStoneHeat, "ArtifactStoneHeat", "res://gd_core_items/ArtifactStoneHeat.gd", &META_Gd__gd_core_items__Stone, true, _alloc_Gd__gd_core_items__ArtifactStoneHeat, &Gd__gd_core_items__ArtifactStoneHeat::get_static_prop_fn, &Gd__gd_core_items__ArtifactStoneHeat::call_static_fn};

void Gd__gd_core_items__BurningCoal::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Gems__Gem::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__BurningCoal::meta() const { return &META_Gd__gd_core_items__BurningCoal; }
gd::GdVal Gd__gd_core_items__BurningCoal::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_gemColor_995: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.5), gd::GdVal::from_int(1LL), gd::GdVal::from_float(0.7)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__BurningCoal::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__BurningCoal::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_gemColor_995: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__BurningCoal::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__BurningCoal::has_own_method(gd::SymId m) const {
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
bool Gd__gd_core_items__BurningCoal::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
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
bool Gd__gd_core_items__BurningCoal::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__BurningCoal::fn_canBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningCoal::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, this->f_socket, SYM_GEN_getItem_389, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[35]), gd::GdVal::from_str(&battle_string_literals[36])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningCoal::fn_preAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)));
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningCoal::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(110LL), gd::gd_round(gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0)))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeResistStacks_1027, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningCoal::fn_combatStartArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningCoal::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_267, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_356, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningCoal::fn_onHotSwapHoverWithGemEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningCoal::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__BurningCoal(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__BurningCoal>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,177u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__BurningCoal = {CLS_Gd__gd_core_items__BurningCoal, "BurningCoal", "res://gd_core_items/BurningCoal.gd", &META_Gd__gd_core_items__Gems__Gem, true, _alloc_Gd__gd_core_items__BurningCoal, &Gd__gd_core_items__BurningCoal::get_static_prop_fn, &Gd__gd_core_items__BurningCoal::call_static_fn};

void Gd__gd_core_items__DeathScythe::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_critBonusActive = gd::GdVal::from_bool(false);
    this->f_poisonThreshold = gd::GdVal::from_int(0);
    this->f_activationParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__DeathScythe::meta() const { return &META_Gd__gd_core_items__DeathScythe; }
gd::GdVal Gd__gd_core_items__DeathScythe::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__DeathScythe::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__DeathScythe::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_critBonusActive_1829: out = this->f_critBonusActive; return true;
        case SYM_GEN_poisonThreshold_1830: out = this->f_poisonThreshold; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__DeathScythe::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_critBonusActive_1829: this->f_critBonusActive = val; return true;
        case SYM_GEN_poisonThreshold_1830: this->f_poisonThreshold = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__DeathScythe::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onOpponentPoisonChanged_1831: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__DeathScythe::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onOpponentPoisonChanged_1831: out = fn_onOpponentPoisonChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__DeathScythe::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__DeathScythe::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(256LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_gainsStack_86, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeathScythe::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[37]), gd::GdVal::from_str(&battle_string_literals[38])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    {
        gd::GdVal _t1248 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1249 = (_t1248.kind == gd::GdVal::Kind::Arr) ? _t1248.arr : nullptr;
        uint32_t _len__t1250 = _t1249 ? _t1249->len : 0u;
        for (uint32_t _t1250 = 0; _t1250 < _len__t1250; ++_t1250) {
            gd::GdVal lv_item = _t1249->data[_t1250];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(108LL), gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_giveBuffPower_303, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeathScythe::fn_onOpponentPoisonChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_curPoison = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getPoison_1229, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_critBonusActive))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_curPoison, this->f_poisonThreshold)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeCritChancePercent_181, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeathScythe::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeathScythe::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__critBonusActive = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv__critBonusActive)) {
    }
    else {
    }
    this->f_critBonusActive = lv__critBonusActive;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeathScythe::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_poisonThreshold = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__DeathScythe(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__DeathScythe>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,195u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__DeathScythe = {CLS_Gd__gd_core_items__DeathScythe, "DeathScythe", "res://gd_core_items/DeathScythe.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__DeathScythe, &Gd__gd_core_items__DeathScythe::get_static_prop_fn, &Gd__gd_core_items__DeathScythe::call_static_fn};

void Gd__gd_core_items__Exclusive__AmuletofLight::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_regenOnActivate = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__AmuletofLight::meta() const { return &META_Gd__gd_core_items__Exclusive__AmuletofLight; }
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofLight::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_amuletColor_2020: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::GdVal::from_float(0.850098), gd::GdVal::from_float(0.400391)}; return gd::make_color_from_args(_ca, 3); })();
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
        case SYM_GEN_regenOnActivate_2031: out = this->f_regenOnActivate; return true;
        case SYM_GEN_amuletColor_2020: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofLight::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_regenOnActivate_2031: this->f_regenOnActivate = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__AmuletofLight::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onItemActivated_938: return true;
        case SYM_GEN_onRegenChanged_1891: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AmuletofLight::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemActivated_938: out = fn_onItemActivated(args, argc); return true;
        case SYM_GEN_onRegenChanged_1891: out = fn_onRegenChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canActivate_91, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofLight::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[39]), gd::GdVal::from_str(&battle_string_literals[40])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    {
        gd::GdVal _t1251 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1252 = (_t1251.kind == gd::GdVal::Kind::Arr) ? _t1251.arr : nullptr;
        uint32_t _len__t1253 = _t1252 ? _t1252->len : 0u;
        for (uint32_t _t1253 = 0; _t1253 < _len__t1253; ++_t1253) {
            gd::GdVal lv_item = _t1252->data[_t1253];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[31]), gd::GdVal::from_str(&battle_string_literals[41])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofLight::fn_onItemActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, lv_event, SYM_GEN_origin_1546), SYM_GEN_hasType_79, _ca, 1); })())) {
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance2_174, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_regenOnActivate, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 2); })();
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
        }
    }
    else {
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_regenOnActivate, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 2); })();
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofLight::fn_onRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[42])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofLight::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_regenOnActivate = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[43])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__AmuletofLight(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__AmuletofLight>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,211u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletofLight = {CLS_Gd__gd_core_items__Exclusive__AmuletofLight, "AmuletofLight", "res://gd_core_items/Exclusive/AmuletofLight.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__AmuletofLight, &Gd__gd_core_items__Exclusive__AmuletofLight::get_static_prop_fn, &Gd__gd_core_items__Exclusive__AmuletofLight::call_static_fn};

void Gd__gd_core_items__Exclusive__Axe::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_permDamBonus = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Axe::meta() const { return &META_Gd__gd_core_items__Exclusive__Axe; }
gd::GdVal Gd__gd_core_items__Exclusive__Axe::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Axe::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Axe::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_permDamBonus_997: out = this->f_permDamBonus; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Axe::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_permDamBonus_997: this->f_permDamBonus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Axe::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Axe::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Axe::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Axe::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_permDamBonus}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Axe::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_permDamBonus = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Axe(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Axe>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,224u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Axe = {CLS_Gd__gd_core_items__Exclusive__Axe, "Axe", "res://gd_core_items/Exclusive/Axe.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__Axe, &Gd__gd_core_items__Exclusive__Axe::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Axe::call_static_fn};

void Gd__gd_core_items__Exclusive__Bomb::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_activationParticles = gd::GdVal::null();
    this->f_damFactor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Bomb::meta() const { return &META_Gd__gd_core_items__Exclusive__Bomb; }
gd::GdVal Gd__gd_core_items__Exclusive__Bomb::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Bomb::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Bomb::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_damFactor_1895: out = this->f_damFactor; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Bomb::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_damFactor_1895: this->f_damFactor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Bomb::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Bomb::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Bomb::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Bomb::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_LoggingMode_1599), SYM_GEN_Delayed_2686)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_setLoggingMode_1588, _ca, 1); })();
        gd::GdVal lv_removedBuffs = gd::GdVal::from_int(0LL);
        {
            gd::GdVal _t1254 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0));
            gd::GdArr* _t1255 = (_t1254.kind == gd::GdVal::Kind::Arr) ? _t1254.arr : nullptr;
            uint32_t _len__t1256 = _t1255 ? _t1255->len : 0u;
            for (uint32_t _t1256 = 0; _t1256 < _len__t1256; ++_t1256) {
                gd::GdVal lv_buff = _t1255->data[_t1256];
                gd::GdVal lv_numStacks = ([&]() { gd::GdVal _ca[] = {lv_buff}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getStacks_1023, _ca, 1); })();
                lv_removedBuffs = gd::gd_add(gd_ctx, lv_removedBuffs, lv_numStacks);
                (void)([&]() { gd::GdVal _ca[] = {lv_buff, lv_numStacks, gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_useStacks_1219, _ca, 3); })();
            }
        }
        (void)gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_flushLoggingQueue_1591, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_neg(this->f_damFactor), lv_removedBuffs)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
        gd::GdVal lv_dam = gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1675);
        gd::GdVal lv_damageRes = ([&]() { gd::GdVal _ca[] = {lv_dam}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealEffectDamage_221, _ca, 1); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Bomb::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_damFactor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[44])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1550, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Bomb(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Bomb>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,237u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Bomb = {CLS_Gd__gd_core_items__Exclusive__Bomb, "Bomb", "res://gd_core_items/Exclusive/Bomb.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Bomb, &Gd__gd_core_items__Exclusive__Bomb::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Bomb::call_static_fn};

void Gd__gd_core_items__Exclusive__BurningSpikes::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_spikesAcc = gd::GdVal::from_int(0LL);
    this->f_affectedItemsDict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_spikes = gd::GdVal::null();
    this->f_heat = gd::GdVal::null();
    this->f_spikesNeeded = gd::GdVal::null();
    this->f_heatForSpikes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__BurningSpikes::meta() const { return &META_Gd__gd_core_items__Exclusive__BurningSpikes; }
gd::GdVal Gd__gd_core_items__Exclusive__BurningSpikes::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__BurningSpikes::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__BurningSpikes::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_spikesAcc_2108: out = this->f_spikesAcc; return true;
        case SYM_GEN_affectedItemsDict_2109: out = this->f_affectedItemsDict; return true;
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        case SYM_GEN_heat_1896: out = this->f_heat; return true;
        case SYM_GEN_spikesNeeded_2110: out = this->f_spikesNeeded; return true;
        case SYM_GEN_heatForSpikes_2111: out = this->f_heatForSpikes; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BurningSpikes::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikesAcc_2108: this->f_spikesAcc = val; return true;
        case SYM_GEN_affectedItemsDict_2109: this->f_affectedItemsDict = val; return true;
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        case SYM_GEN_heat_1896: this->f_heat = val; return true;
        case SYM_GEN_spikesNeeded_2110: this->f_spikesNeeded = val; return true;
        case SYM_GEN_heatForSpikes_2111: this->f_heatForSpikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BurningSpikes::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onSpikesChanged_944: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BurningSpikes::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onSpikesChanged_944: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BurningSpikes::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningSpikes::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(16LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_gainsStack_86, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningSpikes::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_spikesAcc = gd::GdVal::from_int(0LL);
    this->f_affectedItemsDict = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_arrayAsIndexDict_1799, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[22]), gd::GdVal::from_str(&battle_string_literals[45])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningSpikes::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::gd_in(gd::get_prop(gd_ctx, lv_event, SYM_GEN_origin_1546), this->f_affectedItemsDict))) : gd::GdVal::from_bool(false)))) {
        this->f_spikesAcc = gd::gd_add(gd_ctx, this->f_spikesAcc, lv_amount);
        gd::GdVal lv_numProccs = gd::gd_div(gd_ctx, this->f_spikesAcc, this->f_spikesNeeded);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numProccs, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_heatForSpikes, lv_numProccs)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
            this->f_spikesAcc = gd::gd_mod(gd_ctx, this->f_spikesAcc, this->f_spikesNeeded);
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningSpikes::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningSpikes::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[46])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[47])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_spikesNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[48])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_heatForSpikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[49])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BurningSpikes(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__BurningSpikes>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,252u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BurningSpikes = {CLS_Gd__gd_core_items__Exclusive__BurningSpikes, "BurningSpikes", "res://gd_core_items/Exclusive/BurningSpikes.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__BurningSpikes, &Gd__gd_core_items__Exclusive__BurningSpikes::get_static_prop_fn, &Gd__gd_core_items__Exclusive__BurningSpikes::call_static_fn};

void Gd__gd_core_items__Exclusive__Chess__BlackQueen::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Chess__ChessPiece::init_fields(gd_ctx);
    this->f_buffs = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Chess__BlackQueen::meta() const { return &META_Gd__gd_core_items__Exclusive__Chess__BlackQueen; }
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackQueen::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackQueen::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Chess__BlackQueen::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_buffs_1048: out = this->f_buffs; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackQueen::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffs_1048: this->f_buffs = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackQueen::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2146: return true;
        case SYM_GEN_doEliminatedEffect_2148: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackQueen::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2146: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_doEliminatedEffect_2148: out = fn_doEliminatedEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackQueen::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackQueen::fn_doCapturingEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__eliminatedPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_numCaptures, gd::GdVal::from_int(1LL))))) {
        return ([&]() { gd::GdVal _ca[] = {this->f_buffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_373, _ca, 1); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_373, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackQueen::fn_doEliminatedEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[28])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_330, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackQueen::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_buffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[50])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Chess__BlackQueen(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Chess__BlackQueen>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,268u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__BlackQueen = {CLS_Gd__gd_core_items__Exclusive__Chess__BlackQueen, "BlackQueen", "res://gd_core_items/Exclusive/Chess/BlackQueen.gd", &META_Gd__gd_core_items__Exclusive__Chess__ChessPiece, true, _alloc_Gd__gd_core_items__Exclusive__Chess__BlackQueen, &Gd__gd_core_items__Exclusive__Chess__BlackQueen::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Chess__BlackQueen::call_static_fn};

void Gd__gd_core_items__Exclusive__ConTrapTron::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_hasActivated = gd::GdVal::from_bool(false);
    this->f_speedMalus = gd::GdVal::null();
    this->f_cdAdvanceBase = gd::GdVal::null();
    this->f_cdAdvanceBonus = gd::GdVal::null();
    this->f_healthThreshold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ConTrapTron::meta() const { return &META_Gd__gd_core_items__Exclusive__ConTrapTron; }
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_chargeCells1_2133: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(2LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(3LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(2LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(2LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(2LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float())}));
        case SYM_GEN_chargeCells2_2134: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(1LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(2LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::GdVal::from_int(1LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(2LL)).as_float(), (gd::GdVal::from_int(1LL)).as_float())}));
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ConTrapTron::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ConTrapTron::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_hasActivated_1906: out = this->f_hasActivated; return true;
        case SYM_GEN_speedMalus_2181: out = this->f_speedMalus; return true;
        case SYM_GEN_cdAdvanceBase_2182: out = this->f_cdAdvanceBase; return true;
        case SYM_GEN_cdAdvanceBonus_2183: out = this->f_cdAdvanceBonus; return true;
        case SYM_GEN_healthThreshold_1854: out = this->f_healthThreshold; return true;
        case SYM_GEN_chargeCells1_2133: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_chargeCells2_2134: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ConTrapTron::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hasActivated_1906: this->f_hasActivated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_speedMalus_2181: this->f_speedMalus = val; return true;
        case SYM_GEN_cdAdvanceBase_2182: this->f_cdAdvanceBase = val; return true;
        case SYM_GEN_cdAdvanceBonus_2183: this->f_cdAdvanceBonus = val; return true;
        case SYM_GEN_healthThreshold_1854: this->f_healthThreshold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ConTrapTron::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_lightning_289: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onDamaged_1855: return true;
        case SYM_GEN_emitCharge_2058: return true;
        case SYM_GEN_onChargeEnteredCell_2059: return true;
        case SYM_GEN_chargedItemStatChange_2060: return true;
        case SYM_GEN_getTextureSize_781: return true;
        case SYM_GEN_getSpriteOffset_783: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ConTrapTron::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_lightning_289: out = fn_canAffect_lightning(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1855: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN_emitCharge_2058: out = fn_emitCharge(args, argc); return true;
        case SYM_GEN_onChargeEnteredCell_2059: out = fn_onChargeEnteredCell(args, argc); return true;
        case SYM_GEN_chargedItemStatChange_2060: out = fn_chargedItemStatChange(args, argc); return true;
        case SYM_GEN_getTextureSize_781: out = fn_getTextureSize(args, argc); return true;
        case SYM_GEN_getSpriteOffset_783: out = fn_getSpriteOffset(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ConTrapTron::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn_canAffect_lightning(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_gainsBuffs_296, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_reactsToCharges_299, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    gd::GdVal lv_item = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_428, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_speedMalus}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_reduceSpeed_274, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[25]), gd::GdVal::from_str(&battle_string_literals[51])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(this->f_hasActivated)) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRelativeHealth_302, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_emitCharge_2058, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[52]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_obj(this)}))}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
        gd::GdVal lv_item = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_428, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null())))) {
            gd::GdVal lv_cdAdvance = this->f_cdAdvanceBase;
            if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isWeapon_82, nullptr, 0))))) {
                lv_cdAdvance = gd::gd_add(gd_ctx, lv_cdAdvance, this->f_cdAdvanceBonus);
            }
            (void)([&]() { gd::GdVal _ca[] = {lv_cdAdvance}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_advanceCooldownSeconds_147, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn_emitCharge(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_speedFactor = (_argc > 0) ? _args[0] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_event = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[28])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), Gd__gd_core_items__Exclusive__ConTrapTron::get_static_const_or_enum(gd_ctx, SYM_GEN_chargeCells1_2133), lv_speedFactor, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_sendCharge_320, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[28])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), Gd__gd_core_items__Exclusive__ConTrapTron::get_static_const_or_enum(gd_ctx, SYM_GEN_chargeCells2_2134), lv_speedFactor, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_sendCharge_320, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn_onChargeEnteredCell(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cellIndex = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_charge, lv_cellIndex, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeChargedItemStat_326, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn_chargedItemStatChange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_value}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_allBuffs_197, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn_getTextureSize(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn_getSpriteOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speedMalus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_cdAdvanceBase = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[53])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_cdAdvanceBonus = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[54])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[55])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ConTrapTron(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__ConTrapTron>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,285u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ConTrapTron = {CLS_Gd__gd_core_items__Exclusive__ConTrapTron, "ConTrapTron", "res://gd_core_items/Exclusive/ConTrapTron.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__ConTrapTron, &Gd__gd_core_items__Exclusive__ConTrapTron::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ConTrapTron::call_static_fn};

void Gd__gd_core_items__Exclusive__DivinePotion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Potion::init_fields(gd_ctx);
    this->f_debuffsNeeded = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__DivinePotion::meta() const { return &META_Gd__gd_core_items__Exclusive__DivinePotion; }
gd::GdVal Gd__gd_core_items__Exclusive__DivinePotion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Potion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__DivinePotion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__DivinePotion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_debuffsNeeded_2207: out = this->f_debuffsNeeded; return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DivinePotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_debuffsNeeded_2207: this->f_debuffsNeeded = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DivinePotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_debuffsChanged_2208: return true;
        case SYM_GEN_onTriggerPotion_1849: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DivinePotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_debuffsChanged_2208: out = fn_debuffsChanged(args, argc); return true;
        case SYM_GEN_onTriggerPotion_1849: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DivinePotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Potion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DivinePotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[56])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterDebuffs_375, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DivinePotion::fn_debuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getDebuffStacks_1216, nullptr, 0), this->f_debuffsNeeded)))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1848, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DivinePotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_356, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DivinePotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Potion::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_debuffsNeeded = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DivinePotion(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__DivinePotion>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,303u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DivinePotion = {CLS_Gd__gd_core_items__Exclusive__DivinePotion, "DivinePotion", "res://gd_core_items/Exclusive/DivinePotion.gd", &META_Gd__gd_core_items__Potion, true, _alloc_Gd__gd_core_items__Exclusive__DivinePotion, &Gd__gd_core_items__Exclusive__DivinePotion::get_static_prop_fn, &Gd__gd_core_items__Exclusive__DivinePotion::call_static_fn};

void Gd__gd_core_items__Exclusive__ElephantRune::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Gems__Gem::init_fields(gd_ctx);
    this->f_stunReadyTime = gd::GdVal::from_float(0.0);
    this->f_debuffResistChance = gd::GdVal::from_float(0.0);
    this->f_debuffResistTimer = gd::GdVal::null();
    this->f_stunCd = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ElephantRune::meta() const { return &META_Gd__gd_core_items__Exclusive__ElephantRune; }
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_gemColor_995: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.466766), gd::GdVal::from_float(0.625994), gd::GdVal::from_float(0.742188)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ElephantRune::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ElephantRune::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_stunReadyTime_2238: out = this->f_stunReadyTime; return true;
        case SYM_GEN_debuffResistChance_2239: out = this->f_debuffResistChance; return true;
        case SYM_GEN_debuffResistTimer_2240: out = this->f_debuffResistTimer; return true;
        case SYM_GEN_stunCd_2241: out = this->f_stunCd; return true;
        case SYM_GEN_gemColor_995: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ElephantRune::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stunReadyTime_2238: this->f_stunReadyTime = val; return true;
        case SYM_GEN_debuffResistChance_2239: this->f_debuffResistChance = gd::gd_coerce_float(val); return true;
        case SYM_GEN_debuffResistTimer_2240: this->f_debuffResistTimer = val; return true;
        case SYM_GEN_stunCd_2241: this->f_stunCd = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ElephantRune::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepareWeapon_982: return true;
        case SYM_GEN_onAttack_2052: return true;
        case SYM_GEN_prepareArmor_983: return true;
        case SYM_GEN_combatStartArmor_986: return true;
        case SYM_GEN_removeDebuffResistance_2242: return true;
        case SYM_GEN_combatEndArmor_989: return true;
        case SYM_GEN_hasCooldown_95: return true;
        case SYM_GEN_combatStartInventory_984: return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: return true;
        case SYM_GEN_hasInventoryDuration_797: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ElephantRune::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepareWeapon_982: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_onAttack_2052: out = fn_onAttack(args, argc); return true;
        case SYM_GEN_prepareArmor_983: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_combatStartArmor_986: out = fn_combatStartArmor(args, argc); return true;
        case SYM_GEN_removeDebuffResistance_2242: out = fn_removeDebuffResistance(args, argc); return true;
        case SYM_GEN_combatEndArmor_989: out = fn_combatEndArmor(args, argc); return true;
        case SYM_GEN_hasCooldown_95: out = fn_hasCooldown(args, argc); return true;
        case SYM_GEN_combatStartInventory_984: out = fn_combatStartInventory(args, argc); return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: out = fn_onHotSwapHoverWithGemEnd(args, argc); return true;
        case SYM_GEN_hasInventoryDuration_797: out = fn_hasInventoryDuration(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ElephantRune::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_389, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[57]), gd::GdVal::from_str(&battle_string_literals[58])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_onAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1411), this->f_stunReadyTime)))) {
            this->f_stunReadyTime = gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1411), this->f_stunCd);
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[27])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_330, _ca, 2); })();
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_debuffResistChance = gd::gd_coerce_float(gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0)));
    (void)([&]() { gd::GdVal _ca[] = {this->f_debuffResistChance}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDebuffResistChances_1220, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_combatStartArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[59])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, this->f_debuffResistTimer, SYM_GEN_start_1779, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_removeDebuffResistance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_debuffResistChance)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDebuffResistChances_1220, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_combatEndArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_debuffResistTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_hasCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_combatStartInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_381, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_onHotSwapHoverWithGemEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_hasInventoryDuration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_debuffResistTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[60]), gd::GdVal::from_str(&battle_string_literals[61]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_stunCd = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldown_100, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ElephantRune(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__ElephantRune>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,318u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ElephantRune = {CLS_Gd__gd_core_items__Exclusive__ElephantRune, "ElephantRune", "res://gd_core_items/Exclusive/ElephantRune.gd", &META_Gd__gd_core_items__Gems__Gem, true, _alloc_Gd__gd_core_items__Exclusive__ElephantRune, &Gd__gd_core_items__Exclusive__ElephantRune::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ElephantRune::call_static_fn};

void Gd__gd_core_items__Exclusive__Shelly::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_cleanses = gd::GdVal::null();
    this->f_potionSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Shelly::meta() const { return &META_Gd__gd_core_items__Exclusive__Shelly; }
gd::GdVal Gd__gd_core_items__Exclusive__Shelly::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Shelly::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Shelly::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_cleanses_1898: out = this->f_cleanses; return true;
        case SYM_GEN_potionSpeed_2260: out = this->f_potionSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Shelly::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_cleanses_1898: this->f_cleanses = val; return true;
        case SYM_GEN_potionSpeed_2260: this->f_potionSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Shelly::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onPrepare_123: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Shelly::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Shelly::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Shelly::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(11LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Shelly::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_cleanses}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_356, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Shelly::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDebuffProtectionChance_1287, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_potionSpeed, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Shelly::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(1000LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Shelly::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_cleanses = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[62])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_potionSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Shelly(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Shelly>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,474u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Shelly = {CLS_Gd__gd_core_items__Exclusive__Shelly, "Shelly", "res://gd_core_items/Exclusive/Shelly.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Shelly, &Gd__gd_core_items__Exclusive__Shelly::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Shelly::call_static_fn};

void Gd__gd_core_items__Exclusive__FullBodyProtection::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_active = gd::GdVal::null();
    this->f_blockAmp = gd::GdVal::null();
    this->f_damReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__FullBodyProtection::meta() const { return &META_Gd__gd_core_items__Exclusive__FullBodyProtection; }
gd::GdVal Gd__gd_core_items__Exclusive__FullBodyProtection::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__FullBodyProtection::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__FullBodyProtection::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_active_1653: out = this->f_active; return true;
        case SYM_GEN_blockAmp_2285: out = this->f_blockAmp; return true;
        case SYM_GEN_damReduction_1873: out = this->f_damReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__FullBodyProtection::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_active_1653: this->f_active = val; return true;
        case SYM_GEN_blockAmp_2285: this->f_blockAmp = val; return true;
        case SYM_GEN_damReduction_1873: this->f_damReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__FullBodyProtection::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onItemAdded_437: return true;
        case SYM_GEN_onItemRemoved_438: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_checkItems_2224: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_preTakeDamage_1944: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__FullBodyProtection::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onItemAdded_437: out = fn_onItemAdded(args, argc); return true;
        case SYM_GEN_onItemRemoved_438: out = fn_onItemRemoved(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_checkItems_2224: out = fn_checkItems(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_preTakeDamage_1944: out = fn_preTakeDamage(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__FullBodyProtection::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__FullBodyProtection::fn_onItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemAdded_437, _ca, 1, _out); return _out; })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkItems_2224, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FullBodyProtection::fn_onItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemRemoved_438, _ca, 1, _out); return _out; })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkItems_2224, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FullBodyProtection::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_active = gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FullBodyProtection::fn_checkItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numArmor = gd::GdVal::from_int(0LL);
    gd::GdVal lv_numHelmets = gd::GdVal::from_int(0LL);
    gd::GdVal lv_numShoes = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t1257 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t1258 = (_t1257.kind == gd::GdVal::Kind::Arr) ? _t1257.arr : nullptr;
        uint32_t _len__t1259 = _t1258 ? _t1258->len : 0u;
        for (uint32_t _t1259 = 0; _t1259 < _len__t1259; ++_t1259) {
            gd::GdVal lv_item = _t1258->data[_t1259];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(6LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
                lv_numArmor = gd::gd_add(gd_ctx, lv_numArmor, gd::GdVal::from_int(1LL));
            }
            else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(9LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
                lv_numHelmets = gd::gd_add(gd_ctx, lv_numHelmets, gd::GdVal::from_int(1LL));
            }
            else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(8LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
                lv_numShoes = gd::gd_add(gd_ctx, lv_numShoes, gd::GdVal::from_int(1LL));
            }
        }
    }
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_numArmor, gd::GdVal::from_int(1LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_numHelmets, gd::GdVal::from_int(1LL))))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_numShoes, gd::GdVal::from_int(1LL))))) : gd::GdVal::from_bool(false)))) {
        this->f_active = gd::GdVal::from_bool(true);
    }
    else {
        this->f_active = gd::GdVal::from_bool(false);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FullBodyProtection::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBlock_291, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FullBodyProtection::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1260 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1261 = (_t1260.kind == gd::GdVal::Kind::Arr) ? _t1260.arr : nullptr;
        uint32_t _len__t1262 = _t1261 ? _t1261->len : 0u;
        for (uint32_t _t1262 = 0; _t1262 < _len__t1262; ++_t1262) {
            gd::GdVal lv_item = _t1261->data[_t1262];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(100LL), this->f_blockAmp}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_giveBuffPower_303, _ca, 2); })();
        }
    }
    if (gd::gd_truth(this->f_active)) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[63]), gd::GdVal::from_str(&battle_string_literals[64])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FullBodyProtection::fn_preTakeDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_isAttackOrEffect_1562, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction, gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_applyDamageReduction_1526, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FullBodyProtection::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FullBodyProtection::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_blockAmp = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[65])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_damReduction = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[66])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__FullBodyProtection(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__FullBodyProtection>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,346u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FullBodyProtection = {CLS_Gd__gd_core_items__Exclusive__FullBodyProtection, "FullBodyProtection", "res://gd_core_items/Exclusive/FullBodyProtection.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__FullBodyProtection, &Gd__gd_core_items__Exclusive__FullBodyProtection::get_static_prop_fn, &Gd__gd_core_items__Exclusive__FullBodyProtection::call_static_fn};

void Gd__gd_core_items__Exclusive__HeroShield::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__WoodenBuckler::init_fields(gd_ctx);
    this->f_flatDam = gd::GdVal::null();
    this->f_damFactor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__HeroShield::meta() const { return &META_Gd__gd_core_items__Exclusive__HeroShield; }
gd::GdVal Gd__gd_core_items__Exclusive__HeroShield::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__WoodenBuckler::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__HeroShield::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__HeroShield::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_flatDam_2307: out = this->f_flatDam; return true;
        case SYM_GEN_damFactor_1895: out = this->f_damFactor; return true;
        default: break;
    }
    return Gd__gd_core_items__WoodenBuckler::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__HeroShield::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_flatDam_2307: this->f_flatDam = val; return true;
        case SYM_GEN_damFactor_1895: this->f_damFactor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__WoodenBuckler::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__HeroShield::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__WoodenBuckler::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__HeroShield::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__WoodenBuckler::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__HeroShield::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__WoodenBuckler::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__HeroShield::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeroShield::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1263 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1264 = (_t1263.kind == gd::GdVal::Kind::Arr) ? _t1263.arr : nullptr;
        uint32_t _len__t1265 = _t1264 ? _t1264->len : 0u;
        for (uint32_t _t1265 = 0; _t1265 < _len__t1265; ++_t1265) {
            gd::GdVal lv_item = _t1264->data[_t1265];
            (void)([&]() { gd::GdVal _ca[] = {this->f_flatDam}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_damFactor}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamageFactor_306, _ca, 1); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeroShield::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__WoodenBuckler::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_flatDam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[44])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_damFactor = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[67])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__HeroShield(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__HeroShield>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,361u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__HeroShield = {CLS_Gd__gd_core_items__Exclusive__HeroShield, "HeroShield", "res://gd_core_items/Exclusive/HeroShield.gd", &META_Gd__gd_core_items__WoodenBuckler, true, _alloc_Gd__gd_core_items__Exclusive__HeroShield, &Gd__gd_core_items__Exclusive__HeroShield::get_static_prop_fn, &Gd__gd_core_items__Exclusive__HeroShield::call_static_fn};

void Gd__gd_core_items__Exclusive__KingCrown::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Crown::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__KingCrown::meta() const { return &META_Gd__gd_core_items__Exclusive__KingCrown; }
gd::GdVal Gd__gd_core_items__Exclusive__KingCrown::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Crown::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__KingCrown::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__KingCrown::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Crown::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__KingCrown::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Crown::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__KingCrown::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepare_122: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Crown::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__KingCrown::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepare_122: out = fn_prepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Crown::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__KingCrown::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Crown::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__KingCrown::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_gemPower = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[68])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    {
        gd::GdVal _t1266 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_497, nullptr, 0));
        gd::GdArr* _t1267 = (_t1266.kind == gd::GdVal::Kind::Arr) ? _t1266.arr : nullptr;
        uint32_t _len__t1268 = _t1267 ? _t1267->len : 0u;
        for (uint32_t _t1268 = 0; _t1268 < _len__t1268; ++_t1268) {
            gd::GdVal lv_gem = _t1267->data[_t1268];
            (void)([&]() { gd::GdVal _ca[] = {lv_gemPower}; return gd::native_inline_call(gd_ctx, lv_gem, SYM_GEN_changeGemPower_974, _ca, 1); })();
        }
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Crown::call_method(gd_ctx, SYM_GEN_prepare_122, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KingCrown::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeBuffProtectStacks_1187, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KingCrown::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KingCrown::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Crown::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__KingCrown(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__KingCrown>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,376u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__KingCrown = {CLS_Gd__gd_core_items__Exclusive__KingCrown, "KingCrown", "res://gd_core_items/Exclusive/KingCrown.gd", &META_Gd__gd_core_items__Crown, true, _alloc_Gd__gd_core_items__Exclusive__KingCrown, &Gd__gd_core_items__Exclusive__KingCrown::get_static_prop_fn, &Gd__gd_core_items__Exclusive__KingCrown::call_static_fn};

void Gd__gd_core_items__Exclusive__MagicBadge::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_mana = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__MagicBadge::meta() const { return &META_Gd__gd_core_items__Exclusive__MagicBadge; }
gd::GdVal Gd__gd_core_items__Exclusive__MagicBadge::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__MagicBadge::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__MagicBadge::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_mana_1928: out = this->f_mana; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MagicBadge::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_mana_1928: this->f_mana = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MagicBadge::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onAddToInventory_419: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_getRelatedItems_459: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MagicBadge::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onAddToInventory_419: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_getRelatedItems_459: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__MagicBadge::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicBadge::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicBadge::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicBadge::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(32LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_gainsStack_86, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicBadge::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicBadge::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1269 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1270 = (_t1269.kind == gd::GdVal::Kind::Arr) ? _t1269.arr : nullptr;
        uint32_t _len__t1271 = _t1270 ? _t1270->len : 0u;
        for (uint32_t _t1271 = 0; _t1271 < _len__t1271; ++_t1271) {
            gd::GdVal lv_item = _t1270->data[_t1271];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(105LL), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_196, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicBadge::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicBadge::fn_getRelatedItemColumns(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(4LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicBadge::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_mana = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[69])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MagicBadge(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__MagicBadge>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,392u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MagicBadge = {CLS_Gd__gd_core_items__Exclusive__MagicBadge, "MagicBadge", "res://gd_core_items/Exclusive/MagicBadge.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__MagicBadge, &Gd__gd_core_items__Exclusive__MagicBadge::get_static_prop_fn, &Gd__gd_core_items__Exclusive__MagicBadge::call_static_fn};

void Gd__gd_core_items__Exclusive__MoltenSpear::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_totalBlockRemoval = gd::GdVal::from_int(0);
    this->f_blockRemoval = gd::GdVal::null();
    this->f_missDamage = gd::GdVal::null();
    this->f_heatNeeded = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__MoltenSpear::meta() const { return &META_Gd__gd_core_items__Exclusive__MoltenSpear; }
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__MoltenSpear::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__MoltenSpear::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_totalBlockRemoval_1981: out = this->f_totalBlockRemoval; return true;
        case SYM_GEN_blockRemoval_1897: out = this->f_blockRemoval; return true;
        case SYM_GEN_missDamage_2407: out = this->f_missDamage; return true;
        case SYM_GEN_heatNeeded_1880: out = this->f_heatNeeded; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MoltenSpear::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_totalBlockRemoval_1981: this->f_totalBlockRemoval = gd::gd_coerce_int(val); return true;
        case SYM_GEN_blockRemoval_1897: this->f_blockRemoval = val; return true;
        case SYM_GEN_missDamage_2407: this->f_missDamage = val; return true;
        case SYM_GEN_heatNeeded_1880: this->f_heatNeeded = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MoltenSpear::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_affectsEmpty_255: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_onPreDealDamage_late_906: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MoltenSpear::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_affectsEmpty_255: out = fn_affectsEmpty(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onPreDealDamage_late_906: out = fn_onPreDealDamage_late(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__MoltenSpear::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear::fn_affectsEmpty(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(27LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_totalBlockRemoval = gd::gd_coerce_int(gd::gd_mul(this->f_blockRemoval, gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(27LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffected_type_429, _ca, 1); })(), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumEmptyAffectedCells_426, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getHeat_1251, nullptr, 0), this->f_heatNeeded)))) {
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), this->f_missDamage));
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_hit_1520, gd::GdVal::from_bool(true));
            (void)([&]() { gd::GdVal _ca[] = {this->f_heatNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useHeat_354, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear::fn_onPreDealDamage_late(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_totalBlockRemoval}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeBlock_205, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_blockRemoval = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[70])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_missDamage = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[71])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_heatNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[72])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MoltenSpear(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__MoltenSpear>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,407u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MoltenSpear = {CLS_Gd__gd_core_items__Exclusive__MoltenSpear, "MoltenSpear", "res://gd_core_items/Exclusive/MoltenSpear.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__MoltenSpear, &Gd__gd_core_items__Exclusive__MoltenSpear::get_static_prop_fn, &Gd__gd_core_items__Exclusive__MoltenSpear::call_static_fn};

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
        case SYM_GEN_getRelatedItems_459: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__BoxofRiches::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PiggyofRiches::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_getRelatedItems_459: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__BoxofRiches::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PiggyofRiches::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__BoxofRiches::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PiggyofRiches::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_countSocketedGems_1614, nullptr, 0), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[42])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_381, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PiggyofRiches::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[73])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })(), SYM_GEN_gatedItems_1691);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PiggyofRiches::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__BoxofRiches::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_numGems = gd::GdVal::from_int(2LL);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PiggyofRiches(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__PiggyofRiches>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,423u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PiggyofRiches = {CLS_Gd__gd_core_items__Exclusive__PiggyofRiches, "PiggyofRiches", "res://gd_core_items/Exclusive/PiggyofRiches.gd", &META_Gd__gd_core_items__BoxofRiches, true, _alloc_Gd__gd_core_items__Exclusive__PiggyofRiches, &Gd__gd_core_items__Exclusive__PiggyofRiches::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PiggyofRiches::call_static_fn};

void Gd__gd_core_items__Exclusive__PuzzlebagJ::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bag::init_fields(gd_ctx);
    this->f_bonusdur = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PuzzlebagJ::meta() const { return &META_Gd__gd_core_items__Exclusive__PuzzlebagJ; }
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagJ::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagJ::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PuzzlebagJ::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_bonusdur_2450: out = this->f_bonusdur; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagJ::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusdur_2450: this->f_bonusdur = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagJ::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN_onPrepare_123: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_getBagEffect_480: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagJ::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_getBagEffect_480: out = fn_getBagEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagJ::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagJ::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_toItem, SYM_GEN_hasInventoryDuration_797, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagJ::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1272 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_927, nullptr, 0));
        gd::GdArr* _t1273 = (_t1272.kind == gd::GdVal::Kind::Arr) ? _t1272.arr : nullptr;
        uint32_t _len__t1274 = _t1273 ? _t1273->len : 0u;
        for (uint32_t _t1274 = 0; _t1274 < _len__t1274; ++_t1274) {
            gd::GdVal lv_item = _t1273->data[_t1274];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[28]), this->f_bonusdur}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_modifyParam_191, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagJ::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::GdVal::from_int(1000LL), gd::GdVal::from_int(100LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagJ::fn_getBagEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_number = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getName_234, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[74]))}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_tra_2715, _ca, 1); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[75]), gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[76])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), lv_number)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 3); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagJ::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_bonusdur = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[76])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PuzzlebagJ(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__PuzzlebagJ>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,439u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PuzzlebagJ = {CLS_Gd__gd_core_items__Exclusive__PuzzlebagJ, "PuzzlebagJ", "res://gd_core_items/Exclusive/PuzzlebagJ.gd", &META_Gd__gd_core_items__Bag, true, _alloc_Gd__gd_core_items__Exclusive__PuzzlebagJ, &Gd__gd_core_items__Exclusive__PuzzlebagJ::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PuzzlebagJ::call_static_fn};

void Gd__gd_core_items__Exclusive__RatChef::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Rat::init_fields(gd_ctx);
    this->f_stamina = gd::GdVal::null();
    this->f_empower = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__RatChef::meta() const { return &META_Gd__gd_core_items__Exclusive__RatChef; }
gd::GdVal Gd__gd_core_items__Exclusive__RatChef::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Rat::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__RatChef::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__RatChef::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_stamina_2156: out = this->f_stamina; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Rat::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__RatChef::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stamina_2156: this->f_stamina = val; return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Rat::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__RatChef::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_initRat_2466: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_getCraftingOffset_850: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Rat::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__RatChef::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_initRat_2466: out = fn_initRat(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getCraftingOffset_850: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Rat::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__RatChef::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Rat::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__RatChef::fn_initRat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RatChef::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numAffectedFood = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t1275 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1276 = (_t1275.kind == gd::GdVal::Kind::Arr) ? _t1275.arr : nullptr;
        uint32_t _len__t1277 = _t1276 ? _t1276->len : 0u;
        for (uint32_t _t1277 = 0; _t1277 < _len__t1277; ++_t1277) {
            gd::GdVal lv_item = _t1276->data[_t1277];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
                lv_numAffectedFood = gd::gd_add(gd_ctx, lv_numAffectedFood, gd::GdVal::from_int(1LL));
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_numAffectedFood}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RatChef::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_stamina}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_318, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_empower}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RatChef::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1278 = lv_forDirection;
        if (gd::native_scalar_eq(_t1278, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
        else if (gd::native_scalar_eq(_t1278, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::native_scalar_eq(_t1278, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(1LL)).as_float());
        }
        else if (gd::native_scalar_eq(_t1278, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RatChef::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Rat::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[77])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_empower = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[78])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__RatChef(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__RatChef>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,455u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RatChef = {CLS_Gd__gd_core_items__Exclusive__RatChef, "RatChef", "res://gd_core_items/Exclusive/RatChef.gd", &META_Gd__gd_core_items__Exclusive__Rat, true, _alloc_Gd__gd_core_items__Exclusive__RatChef, &Gd__gd_core_items__Exclusive__RatChef::get_static_prop_fn, &Gd__gd_core_items__Exclusive__RatChef::call_static_fn};

void Gd__gd_core_items__Exclusive__SerpentStaff::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_damageAcc = gd::GdVal::from_int(0LL);
    this->f_manaUseEvents = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_manaCost = gd::GdVal::null();
    this->f_permDamBonus = gd::GdVal::null();
    this->f_poison = gd::GdVal::null();
    this->f_damageForPoison = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SerpentStaff::meta() const { return &META_Gd__gd_core_items__Exclusive__SerpentStaff; }
gd::GdVal Gd__gd_core_items__Exclusive__SerpentStaff::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SerpentStaff::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SerpentStaff::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_damageAcc_1960: out = this->f_damageAcc; return true;
        case SYM_GEN_manaUseEvents_2486: out = this->f_manaUseEvents; return true;
        case SYM_GEN_manaCost_1815: out = this->f_manaCost; return true;
        case SYM_GEN_permDamBonus_997: out = this->f_permDamBonus; return true;
        case SYM_GEN_poison_1962: out = this->f_poison; return true;
        case SYM_GEN_damageForPoison_2487: out = this->f_damageForPoison; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SerpentStaff::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damageAcc_1960: this->f_damageAcc = val; return true;
        case SYM_GEN_manaUseEvents_2486: this->f_manaUseEvents = val; return true;
        case SYM_GEN_manaCost_1815: this->f_manaCost = val; return true;
        case SYM_GEN_permDamBonus_997: this->f_permDamBonus = val; return true;
        case SYM_GEN_poison_1962: this->f_poison = val; return true;
        case SYM_GEN_damageForPoison_2487: this->f_damageForPoison = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SerpentStaff::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SerpentStaff::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SerpentStaff::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SerpentStaff::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_manaUseEvents, gd::SYM_clear, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(108LL), gd::gd_neg(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeResistChance_1026, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SerpentStaff::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_manaUseEvent = ([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_333, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_manaUseEvent, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_permDamBonus}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_manaUseEvent}; return gd::native_inline_call(gd_ctx, this->f_manaUseEvents, gd::SYM_push_back, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SerpentStaff::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_manaUseEvents, gd::SYM_empty, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
        this->f_damageAcc = gd::gd_add(gd_ctx, this->f_damageAcc, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518));
        gd::GdVal lv_curPoison = gd::gd_div(gd_ctx, this->f_damageAcc, this->f_damageForPoison);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_curPoison, gd::GdVal::from_int(0LL))))) {
            this->f_damageAcc = gd::gd_mod(gd_ctx, this->f_damageAcc, this->f_damageForPoison);
            (void)([&]() { gd::GdVal _ca[] = {lv_curPoison, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 2); })();
        }
        (void)gd::native_inline_call(gd_ctx, this->f_manaUseEvents, gd::SYM_pop_back, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SerpentStaff::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_manaCost = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[69])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_permDamBonus = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[44])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_poison = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[79])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_damageForPoison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[80])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SerpentStaff(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__SerpentStaff>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,470u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SerpentStaff = {CLS_Gd__gd_core_items__Exclusive__SerpentStaff, "SerpentStaff", "res://gd_core_items/Exclusive/SerpentStaff.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__SerpentStaff, &Gd__gd_core_items__Exclusive__SerpentStaff::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SerpentStaff::call_static_fn};

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
        case SYM_GEN_cold_2045: out = this->f_cold; return true;
        case SYM_GEN_maxHealthReduction_2153: out = this->f_maxHealthReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Snowball::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_cold_2045: this->f_cold = val; return true;
        case SYM_GEN_maxHealthReduction_2153: this->f_maxHealthReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Snowball::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Snowball::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Snowball::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Snowball::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_maxHealthReduction}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeMaxHealthGain_1277, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Snowball::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_cold}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_351, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_381, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Snowball::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_cold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[81])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_maxHealthReduction = gd::gd_div(gd_ctx, gd::gd_neg(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[82])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Snowball(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Snowball>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,487u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Snowball = {CLS_Gd__gd_core_items__Exclusive__Snowball, "Snowball", "res://gd_core_items/Exclusive/Snowball.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Snowball, &Gd__gd_core_items__Exclusive__Snowball::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Snowball::call_static_fn};

void Gd__gd_core_items__Exclusive__SpintoWin::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_heat = gd::GdVal::null();
    this->f_luck = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
    this->f_mana = gd::GdVal::null();
    this->f_frame = gd::GdVal::null();
    this->f_skillLight = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SpintoWin::meta() const { return &META_Gd__gd_core_items__Exclusive__SpintoWin; }
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_colors_2538: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 4); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.941176), gd::GdVal::from_float(0.489231), gd::GdVal::from_float(0.301961)}; return gd::make_color_from_args(_ca, 3); })()); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.301961), gd::GdVal::from_float(0.941176), gd::GdVal::from_float(0.41682)}; return gd::make_color_from_args(_ca, 3); })()); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.941176), gd::GdVal::from_float(0.301961), gd::GdVal::from_float(0.513726)}; return gd::make_color_from_args(_ca, 3); })()); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.320312), gd::GdVal::from_float(0.466339), gd::GdVal::from_int(1LL)}; return gd::make_color_from_args(_ca, 3); })()); return gd::GdVal::from_dict(d); })();
        case SYM_GEN_neutralColor_2539: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(1LL), gd::GdVal::from_float(0.364706)}; return gd::make_color_from_args(_ca, 4); })();
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SpintoWin::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SpintoWin::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_heat_1896: out = this->f_heat; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        case SYM_GEN_mana_1928: out = this->f_mana; return true;
        case SYM_GEN_frame_2540: out = this->f_frame; return true;
        case SYM_GEN_skillLight_2541: out = this->f_skillLight; return true;
        case SYM_GEN_colors_2538: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_neutralColor_2539: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SpintoWin::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heat_1896: this->f_heat = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        case SYM_GEN_mana_1928: this->f_mana = val; return true;
        case SYM_GEN_frame_2540: this->f_frame = val; return true;
        case SYM_GEN_skillLight_2541: this->f_skillLight = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SpintoWin::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_ready_deferred_463: return true;
        case SYM_GEN_updateColor_2542: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_gainsStack_86: return true;
        case SYM_GEN_rotateTo_476: return true;
        case SYM_GEN_setFaceDirectionInstant_467: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SpintoWin::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_ready_deferred_463: out = fn_ready_deferred(args, argc); return true;
        case SYM_GEN_updateColor_2542: out = fn_updateColor(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_gainsStack_86: out = fn_gainsStack(args, argc); return true;
        case SYM_GEN_rotateTo_476: out = fn_rotateTo(args, argc); return true;
        case SYM_GEN_setFaceDirectionInstant_467: out = fn_setFaceDirectionInstant(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SpintoWin::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn_ready_deferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_ready_deferred_463, nullptr, 0, _out); return _out; })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateColor_2542, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn_updateColor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_642, _ca, 1, _out); return _out; })();
    gd::GdVal lv_colors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_inactiveColor_2834), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_inactiveColor_2834), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_inactiveColor_2834), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_inactiveColor_2834)}));
    gd::GdVal lv_gold = gd::GdVal::from_int(0);
    if (gd::gd_truth(this->f_placed)) {
        { gd::GdVal _t1279 = lv_colors; gd::GdVal _t1280 = this->f_faceDirection; gd::native_array_set_index(gd_ctx, _t1279, _t1280, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_modifiedColor_2829)); }
    }
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, lv_colors, gd::GdVal::from_bool(false), lv_wrapInColor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModeDescription_645, _ca, 4); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1281 = this->f_faceDirection;
        if (gd::native_scalar_eq(_t1281, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
        }
        else if (gd::native_scalar_eq(_t1281, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
        }
        else if (gd::native_scalar_eq(_t1281, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
        }
        else if (gd::native_scalar_eq(_t1281, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn_gainsStack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stackType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1282 = this->f_faceDirection;
        if (gd::native_scalar_eq(_t1282, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            return gd::GdVal::from_bool(gd::native_scalar_eq(lv_stackType, gd::GdVal::from_int(128LL)));
        }
        else if (gd::native_scalar_eq(_t1282, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            return gd::GdVal::from_bool(gd::native_scalar_eq(lv_stackType, gd::GdVal::from_int(2LL)));
        }
        else if (gd::native_scalar_eq(_t1282, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            return gd::GdVal::from_bool(gd::native_scalar_eq(lv_stackType, gd::GdVal::from_int(4LL)));
        }
        else if (gd::native_scalar_eq(_t1282, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            return gd::GdVal::from_bool(gd::native_scalar_eq(lv_stackType, gd::GdVal::from_int(32LL)));
        }
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn_rotateTo(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_targetRotation = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 1) ? _args[1] : (gd::GdVal::from_float(0.15));
    (void)([&]() { gd::GdVal _ca[] = {lv_targetRotation, lv_duration}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_rotateTo_476, _ca, 2, _out); return _out; })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateColor_2542, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn_setFaceDirectionInstant(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__faceDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv__faceDirection}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_setFaceDirectionInstant_467, _ca, 1, _out); return _out; })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateColor_2542, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[47])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[83])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[43])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[69])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SpintoWin(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__SpintoWin>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,503u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpintoWin = {CLS_Gd__gd_core_items__Exclusive__SpintoWin, "SpintoWin", "res://gd_core_items/Exclusive/SpintoWin.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__SpintoWin, &Gd__gd_core_items__Exclusive__SpintoWin::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SpintoWin::call_static_fn};

void Gd__gd_core_items__Exclusive__StrongVampiricPotion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__VampiricPotion::init_fields(gd_ctx);
    this->f_curLifesteal = gd::GdVal::from_float(0.0);
    this->f_lifestealGiven = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_lifestealTimer = gd::GdVal::null();
    this->f_lifestealPerTrigger = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__StrongVampiricPotion::meta() const { return &META_Gd__gd_core_items__Exclusive__StrongVampiricPotion; }
gd::GdVal Gd__gd_core_items__Exclusive__StrongVampiricPotion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__VampiricPotion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__StrongVampiricPotion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__StrongVampiricPotion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_curLifesteal_2565: out = this->f_curLifesteal; return true;
        case SYM_GEN_lifestealGiven_2566: out = this->f_lifestealGiven; return true;
        case SYM_GEN_lifestealTimer_2567: out = this->f_lifestealTimer; return true;
        case SYM_GEN_lifestealPerTrigger_2568: out = this->f_lifestealPerTrigger; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__VampiricPotion::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__StrongVampiricPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_curLifesteal_2565: this->f_curLifesteal = gd::gd_coerce_float(val); return true;
        case SYM_GEN_lifestealGiven_2566: this->f_lifestealGiven = val; return true;
        case SYM_GEN_lifestealTimer_2567: this->f_lifestealTimer = val; return true;
        case SYM_GEN_lifestealPerTrigger_2568: this->f_lifestealPerTrigger = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__VampiricPotion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__StrongVampiricPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onTriggerPotion_1849: return true;
        case SYM_GEN_onOpponentDamaged_1992: return true;
        case SYM_GEN_onLifestealTimeout_2569: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__VampiricPotion::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__StrongVampiricPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onTriggerPotion_1849: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onOpponentDamaged_1992: out = fn_onOpponentDamaged(args, argc); return true;
        case SYM_GEN_onLifestealTimeout_2569: out = fn_onLifestealTimeout(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__VampiricPotion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__StrongVampiricPotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__VampiricPotion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__StrongVampiricPotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__VampiricPotion::call_method(gd_ctx, SYM_GEN_onPrepare_123, nullptr, 0, _out); return _out; })();
    this->f_curLifesteal = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    (void)gd::native_inline_call(gd_ctx, this->f_lifestealGiven, gd::SYM_clear, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[84]), gd::GdVal::from_str(&battle_string_literals[85])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StrongVampiricPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_amount = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[86])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_curLifesteal = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_curLifesteal, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::native_inline_call(gd_ctx, this->f_lifestealGiven, gd::SYM_push_back, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[28])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, this->f_lifestealTimer, SYM_GEN_start_1779, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StrongVampiricPotion::fn_onOpponentDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_curLifesteal, gd::GdVal::from_int(0LL))))) {
        if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_canApplyLifesteal_1563, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_ceil(gd::gd_mul(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), this->f_curLifesteal)), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StrongVampiricPotion::fn_onLifestealTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_curLifesteal = gd::gd_coerce_float(gd::gd_sub(this->f_curLifesteal, gd::native_inline_call(gd_ctx, this->f_lifestealGiven, gd::SYM_pop_front, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StrongVampiricPotion::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_lifestealTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StrongVampiricPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__VampiricPotion::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_lifestealTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[87]), gd::GdVal::from_str(&battle_string_literals[88]), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_lifestealPerTrigger = gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__StrongVampiricPotion(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__StrongVampiricPotion>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,519u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StrongVampiricPotion = {CLS_Gd__gd_core_items__Exclusive__StrongVampiricPotion, "StrongVampiricPotion", "res://gd_core_items/Exclusive/StrongVampiricPotion.gd", &META_Gd__gd_core_items__Exclusive__VampiricPotion, true, _alloc_Gd__gd_core_items__Exclusive__StrongVampiricPotion, &Gd__gd_core_items__Exclusive__StrongVampiricPotion::get_static_prop_fn, &Gd__gd_core_items__Exclusive__StrongVampiricPotion::call_static_fn};

void Gd__gd_core_items__Exclusive__Turtle::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__LeatherHelm::init_fields(gd_ctx);
    this->f_extraDamBlock = gd::GdVal::null();
    this->f_maxHealthBlock = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Turtle::meta() const { return &META_Gd__gd_core_items__Exclusive__Turtle; }
gd::GdVal Gd__gd_core_items__Exclusive__Turtle::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__LeatherHelm::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Turtle::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Turtle::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_extraDamBlock_2596: out = this->f_extraDamBlock; return true;
        case SYM_GEN_maxHealthBlock_2597: out = this->f_maxHealthBlock; return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Turtle::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_extraDamBlock_2596: this->f_extraDamBlock = val; return true;
        case SYM_GEN_maxHealthBlock_2597: this->f_maxHealthBlock = val; return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Turtle::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreCombatStart_125: return true;
        case SYM_GEN_buffEnded_1817: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Turtle::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreCombatStart_125: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_buffEnded_1817: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Turtle::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__LeatherHelm::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Turtle::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(5LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Turtle::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1283 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1284 = (_t1283.kind == gd::GdVal::Kind::Arr) ? _t1283.arr : nullptr;
        uint32_t _len__t1285 = _t1284 ? _t1284->len : 0u;
        for (uint32_t _t1285 = 0; _t1285 < _len__t1285; ++_t1285) {
            gd::GdVal lv_item = _t1284->data[_t1285];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[89]), this->f_extraDamBlock}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_modifyParam_191, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Turtle::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN_onPreCombatStart_125, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Turtle::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN_buffEnded_1817, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Turtle::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_blockAmount = gd::gd_add(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), gd::gd_mul(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMaxHealth_1160, nullptr, 0), this->f_maxHealthBlock));
    (void)([&]() { gd::GdVal _ca[] = {lv_blockAmount}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Turtle::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_extraDamBlock = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[90])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_maxHealthBlock = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[91])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Turtle(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Turtle>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,536u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Turtle = {CLS_Gd__gd_core_items__Exclusive__Turtle, "Turtle", "res://gd_core_items/Exclusive/Turtle.gd", &META_Gd__gd_core_items__LeatherHelm, true, _alloc_Gd__gd_core_items__Exclusive__Turtle, &Gd__gd_core_items__Exclusive__Turtle::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Turtle::call_static_fn};

void Gd__gd_core_items__Exclusive__Wisp::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Gems__Gem::init_fields(gd_ctx);
    this->f_damageAcc = gd::GdVal::from_int(0);
    this->f_luck = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
    this->f_natureSpeed = gd::GdVal::null();
    this->f_damageForSpikes = gd::GdVal::null();
    this->f_spikes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Wisp::meta() const { return &META_Gd__gd_core_items__Exclusive__Wisp; }
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_gemColor_995: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.783203), gd::GdVal::from_float(0.972054), gd::GdVal::from_int(1LL)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Wisp::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Wisp::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_damageAcc_1960: out = this->f_damageAcc; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        case SYM_GEN_natureSpeed_2623: out = this->f_natureSpeed; return true;
        case SYM_GEN_damageForSpikes_2624: out = this->f_damageForSpikes; return true;
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        case SYM_GEN_gemColor_995: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Wisp::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damageAcc_1960: this->f_damageAcc = gd::gd_coerce_int(val); return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        case SYM_GEN_natureSpeed_2623: this->f_natureSpeed = val; return true;
        case SYM_GEN_damageForSpikes_2624: this->f_damageForSpikes = val; return true;
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Wisp::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_hasCooldown_95: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_prepareInventory_981: return true;
        case SYM_GEN_prepareWeapon_982: return true;
        case SYM_GEN_onAttack_2052: return true;
        case SYM_GEN_combatStart_127: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_149: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Wisp::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_hasCooldown_95: out = fn_hasCooldown(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_prepareInventory_981: out = fn_prepareInventory(args, argc); return true;
        case SYM_GEN_prepareWeapon_982: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_onAttack_2052: out = fn_onAttack(args, argc); return true;
        case SYM_GEN_combatStart_127: out = fn_combatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_149: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Wisp::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_hasCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0), gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Wisp::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Inventory_2856)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0), gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Wisp::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Armor_2704))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(26LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_prepareInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0), this->f_natureSpeed)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_damageAcc = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, this->f_socket, SYM_GEN_getItem_389, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[57]), gd::GdVal::from_str(&battle_string_literals[58])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_onAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        this->f_damageAcc = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_damageAcc, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518)));
        gd::GdVal lv_numProccs = gd::gd_div(gd_ctx, this->f_damageAcc, this->f_damageForSpikes);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numProccs, gd::GdVal::from_int(0LL))))) {
            this->f_damageAcc = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_damageAcc, this->f_damageForSpikes));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_spikes, lv_numProccs)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 1); })();
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_combatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1286 = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0);
        if (gd::native_scalar_eq(_t1286, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Wisp::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Inventory_2856))) {
            this->f_baseCooldownOverride = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_101, _ca, 1); })());
        }
        else if (gd::native_scalar_eq(_t1286, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Wisp::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Armor_2704))) {
            this->f_baseCooldownOverride = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_101, _ca, 1); })());
        }
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN_combatStart_127, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1287 = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0);
        if (gd::native_scalar_eq(_t1287, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Wisp::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Inventory_2856))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
        }
        else if (gd::native_scalar_eq(_t1287, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Wisp::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Armor_2704))) {
            gd::GdVal lv_bonusHealth = gd::gd_mul(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[42])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getCurrentHealth_1154, nullptr, 0));
            lv_bonusHealth = gd::gd_mul(lv_bonusHealth, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0));
            (void)([&]() { gd::GdVal _ca[] = {lv_bonusHealth}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, _ca, 1); })();
            this->f_consumed = gd::GdVal::from_bool(true);
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[83])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[43])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_natureSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_damageForSpikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[44])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[46])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Wisp(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Wisp>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,553u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Wisp = {CLS_Gd__gd_core_items__Exclusive__Wisp, "Wisp", "res://gd_core_items/Exclusive/Wisp.gd", &META_Gd__gd_core_items__Gems__Gem, true, _alloc_Gd__gd_core_items__Exclusive__Wisp, &Gd__gd_core_items__Exclusive__Wisp::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Wisp::call_static_fn};

void Gd__gd_core_items__Gems__Sapphire::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Gems__Gem::init_fields(gd_ctx);
    this->f_manaCounter = gd::GdVal::from_int(0LL);
    this->f_spectral = gd::GdVal::from_bool(false);
    this->f_manaNeeded = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Gems__Sapphire::meta() const { return &META_Gd__gd_core_items__Gems__Sapphire; }
gd::GdVal Gd__gd_core_items__Gems__Sapphire::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_gemColor_995: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.8), gd::GdVal::from_float(0.8), gd::GdVal::from_int(3LL)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Gems__Sapphire::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Gems__Sapphire::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_manaCounter_2632: out = this->f_manaCounter; return true;
        case SYM_GEN_spectral_2633: out = this->f_spectral; return true;
        case SYM_GEN_manaNeeded_1881: out = this->f_manaNeeded; return true;
        case SYM_GEN_gemColor_995: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Gems__Sapphire::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaCounter_2632: this->f_manaCounter = val; return true;
        case SYM_GEN_spectral_2633: this->f_spectral = val; return true;
        case SYM_GEN_manaNeeded_1881: this->f_manaNeeded = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Gems__Sapphire::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_prepareWeapon_982: return true;
        case SYM_GEN_preAttack_996: return true;
        case SYM_GEN_onAttack_2052: return true;
        case SYM_GEN_prepareArmor_983: return true;
        case SYM_GEN_onManaChanged_1929: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Gems__Sapphire::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_prepareWeapon_982: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_preAttack_996: out = fn_preAttack(args, argc); return true;
        case SYM_GEN_onAttack_2052: out = fn_onAttack(args, argc); return true;
        case SYM_GEN_prepareArmor_983: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_onManaChanged_1929: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Gems__Sapphire::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Gems__Sapphire::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_267, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_351, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Sapphire::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_spectral = gd::GdVal::from_bool(false);
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, this->f_socket, SYM_GEN_getItem_389, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[92]), gd::GdVal::from_str(&battle_string_literals[36])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, this->f_socket, SYM_GEN_getItem_389, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[57]), gd::GdVal::from_str(&battle_string_literals[58])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Sapphire::fn_preAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_spectral = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0);
    if (gd::gd_truth(this->f_spectral)) {
        (void)gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_makeSpectral_1564, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Sapphire::fn_onAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(this->f_spectral) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_351, _ca, 2); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Sapphire::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_manaCounter = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[23]), gd::GdVal::from_str(&battle_string_literals[93])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Sapphire::fn_onManaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        this->f_manaCounter = gd::gd_add(gd_ctx, this->f_manaCounter, lv_amount);
        gd::GdVal lv_relMana = gd::gd_div(gd_ctx, this->f_manaCounter, this->f_manaNeeded);
        gd::GdVal lv_block = gd::gd_mul(lv_relMana, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0));
        this->f_manaCounter = gd::gd_mod(gd_ctx, this->f_manaCounter, this->f_manaNeeded);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_block, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0), lv_block), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 2); })();
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {lv_relMana, gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 2); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {lv_relMana, gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Sapphire::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Gems__Sapphire(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Gems__Sapphire>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,571u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Gems__Sapphire = {CLS_Gd__gd_core_items__Gems__Sapphire, "Sapphire", "res://gd_core_items/Gems/Sapphire.gd", &META_Gd__gd_core_items__Gems__Gem, true, _alloc_Gd__gd_core_items__Gems__Sapphire, &Gd__gd_core_items__Gems__Sapphire::get_static_prop_fn, &Gd__gd_core_items__Gems__Sapphire::call_static_fn};

void Gd__gd_core_items__Item__INNER__SignalConnection::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_emitter = gd::GdVal::null();
    this->f_signalName = gd::GdVal::null();
    this->f_receiver = gd::GdVal::null();
    this->f_methodName = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Item__INNER__SignalConnection::meta() const { return &META_Gd__gd_core_items__Item__INNER__SignalConnection; }
gd::GdVal Gd__gd_core_items__Item__INNER__SignalConnection::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return gd::GdVal::null();
}
bool Gd__gd_core_items__Item__INNER__SignalConnection::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Item__INNER__SignalConnection::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_emitter_1654: out = this->f_emitter; return true;
        case SYM_GEN_signalName_1013: out = this->f_signalName; return true;
        case SYM_GEN_receiver_1655: out = this->f_receiver; return true;
        case SYM_GEN_methodName_1656: out = this->f_methodName; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core_items__Item__INNER__SignalConnection::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_emitter_1654: this->f_emitter = val; return true;
        case SYM_GEN_signalName_1013: this->f_signalName = val; return true;
        case SYM_GEN_receiver_1655: this->f_receiver = val; return true;
        case SYM_GEN_methodName_1656: this->f_methodName = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core_items__Item__INNER__SignalConnection::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_destroy_1657: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core_items__Item__INNER__SignalConnection::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_destroy_1657: out = fn_destroy(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core_items__Item__INNER__SignalConnection::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core_items__Item__INNER__SignalConnection::fn__init(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item__INNER__SignalConnection::fn_destroy(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Item__INNER__SignalConnection(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Item__INNER__SignalConnection>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,23u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Item__INNER__SignalConnection = {CLS_Gd__gd_core_items__Item__INNER__SignalConnection, "SignalConnection", "", nullptr, true, _alloc_Gd__gd_core_items__Item__INNER__SignalConnection, &Gd__gd_core_items__Item__INNER__SignalConnection::get_static_prop_fn, &Gd__gd_core_items__Item__INNER__SignalConnection::call_static_fn};

void Gd__gd_core_items__Pineapple::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Pineapple::meta() const { return &META_Gd__gd_core_items__Pineapple; }
gd::GdVal Gd__gd_core_items__Pineapple::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Pineapple::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Pineapple::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Pineapple::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Pineapple::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Pineapple::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Pineapple::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Pineapple::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Pineapple::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Pineapple(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Pineapple>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,611u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Pineapple = {CLS_Gd__gd_core_items__Pineapple, "Pineapple", "res://gd_core_items/Pineapple.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Pineapple, &Gd__gd_core_items__Pineapple::get_static_prop_fn, &Gd__gd_core_items__Pineapple::call_static_fn};

void Gd__gd_core_items__ShieldofValor::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Shield::init_fields(gd_ctx);
    this->f_blockFactor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__ShieldofValor::meta() const { return &META_Gd__gd_core_items__ShieldofValor; }
gd::GdVal Gd__gd_core_items__ShieldofValor::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Shield::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__ShieldofValor::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__ShieldofValor::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_blockFactor_1977: out = this->f_blockFactor; return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::get_prop(prop, out);
}
bool Gd__gd_core_items__ShieldofValor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockFactor_1977: this->f_blockFactor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__ShieldofValor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_afterBlock_1942: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::has_own_method(m);
}
bool Gd__gd_core_items__ShieldofValor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_afterBlock_1942: out = fn_afterBlock(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__ShieldofValor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Shield::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__ShieldofValor::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBlock_291, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ShieldofValor::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1288 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1289 = (_t1288.kind == gd::GdVal::Kind::Arr) ? _t1288.arr : nullptr;
        uint32_t _len__t1290 = _t1289 ? _t1289->len : 0u;
        for (uint32_t _t1290 = 0; _t1290 < _len__t1290; ++_t1290) {
            gd::GdVal lv_item = _t1289->data[_t1290];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(100LL), this->f_blockFactor}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_giveBuffPower_303, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ShieldofValor::fn_afterBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), gd::get_prop(gd_ctx, this->f_blockedDamageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drainStamina_117, _ca, 2); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ShieldofValor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Shield::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_blockFactor = gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__ShieldofValor(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__ShieldofValor>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,632u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__ShieldofValor = {CLS_Gd__gd_core_items__ShieldofValor, "ShieldofValor", "res://gd_core_items/ShieldofValor.gd", &META_Gd__gd_core_items__Shield, true, _alloc_Gd__gd_core_items__ShieldofValor, &Gd__gd_core_items__ShieldofValor::get_static_prop_fn, &Gd__gd_core_items__ShieldofValor::call_static_fn};

void Gd__gd_core_items__ThornWhip::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__ThornWhip::meta() const { return &META_Gd__gd_core_items__ThornWhip; }
gd::GdVal Gd__gd_core_items__ThornWhip::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__ThornWhip::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__ThornWhip::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__ThornWhip::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__ThornWhip::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_onSpikesChanged_944: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__ThornWhip::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onSpikesChanged_944: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__ThornWhip::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__ThornWhip::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[22]), gd::GdVal::from_str(&battle_string_literals[45])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ThornWhip::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ThornWhip::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), lv_amount)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_162, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ThornWhip::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__ThornWhip(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__ThornWhip>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,651u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__ThornWhip = {CLS_Gd__gd_core_items__ThornWhip, "ThornWhip", "res://gd_core_items/ThornWhip.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__ThornWhip, &Gd__gd_core_items__ThornWhip::get_static_prop_fn, &Gd__gd_core_items__ThornWhip::call_static_fn};
