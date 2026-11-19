#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core__AceofSpades.hpp"
#include "../hdrs/Gd__gd_core__Dagger.hpp"
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
        case SYM_GEN_spadesParticles_892: out = this->f_spadesParticles; return true;
        case SYM_GEN_luck_893: out = this->f_luck; return true;
        case SYM_GEN_spikes_894: out = this->f_spikes; return true;
        default: break;
    }
    return Gd__gd_core__Card::get_prop(prop, out);
}
bool Gd__gd_core__AceofSpades::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spadesParticles_892: this->f_spadesParticles = val; return true;
        case SYM_GEN_luck_893: this->f_luck = val; return true;
        case SYM_GEN_spikes_894: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__AceofSpades::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_886: return true;
        case SYM_GEN_doRevealEffect_889: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Card::has_own_method(m);
}
bool Gd__gd_core__AceofSpades::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_886: out = fn_cardSecondaryEffectActive(args, argc); return true;
        case SYM_GEN_doRevealEffect_889: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__AceofSpades::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__AceofSpades::fn_cardSecondaryEffectActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_eq(gd::gd_mod(gd_ctx, this->f_chainPosition, gd::GdVal::from_int(2LL)), gd::GdVal::from_int(1LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__AceofSpades::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveCritTokens_312, _ca, 1); })();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cardSecondaryEffectActive_886, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_207, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__AceofSpades::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Card::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__AceofSpades(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__AceofSpades>(&ctx); }
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
        case SYM_GEN_prepare_120: return true;
        case SYM_GEN_onStun_942: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Dagger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepare_120: out = fn_prepare(args, argc); return true;
        case SYM_GEN_onStun_942: out = fn_onStun(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Dagger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Dagger::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN_prepare_120, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_stunned", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onStun", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Dagger::fn_onStun(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_attack_937, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Dagger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Dagger(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Dagger>(&ctx); }
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
    this->f__dbg_spdt = gd::GdVal::from_bool(gd::gd_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))));
    this->f__tick_timer_left = gd::GdVal::from_float(0.0);
    this->f__tick_timer_active = gd::GdVal::from_bool(false);
    this->f_max_time = gd::GdVal::from_float(180.0);
    this->f_timed_out = gd::GdVal::from_bool(false);
    this->f__pending_deferred = gd::GdVal::from_bool(false);
}
const gd::GdClassMeta* Gd__gd_core__CoreCombat::meta() const { return &META_Gd__gd_core__CoreCombat; }
gd::GdVal Gd__gd_core__CoreCombat::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_RoundResult_1314: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreCombat_RoundResult);
        case SYM_GEN_FATIGUE_TIME_1277: return gd::GdVal::from_float(17.0);
        case SYM_GEN_FATIGUE_START_DELAY_1278: return gd::GdVal::from_float(3.0);
        case SYM_GEN_FATIGUE_SLOW_TIME_1279: return gd::GdVal::from_float(60.0);
        case SYM_GEN_CoreItemSort_1318: return gd::GdVal::from_cls(&META_Gd__gd_core__CoreCombat__INNER__CoreItemSort);
        default: break;
    }
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreCombat::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
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
        case SYM_GEN_player_1280: out = this->f_player; return true;
        case SYM_GEN_opponent_73: out = this->f_opponent; return true;
        case SYM_GEN_ordered_items_1281: out = this->f_ordered_items; return true;
        case SYM_GEN_result_1282: out = this->f_result; return true;
        case SYM_GEN_fight_ended_1283: out = this->f_fight_ended; return true;
        case SYM_GEN_combat_time_1284: out = this->f_combat_time; return true;
        case SYM_GEN_fatigue_counter_1285: out = this->f_fatigue_counter; return true;
        case SYM_GEN_fatigue_started_1286: out = this->f_fatigue_started; return true;
        case SYM_GEN_fatigue_next_tick_1287: out = this->f_fatigue_next_tick; return true;
        case SYM_GEN_fatigue_interval_1288: out = this->f_fatigue_interval; return true;
        case SYM_GEN_time_advance_1289: out = this->f_time_advance; return true;
        case SYM_GEN_speed_scale_1290: out = this->f_speed_scale; return true;
        case SYM_GEN__activate_countdown_1291: out = this->f__activate_countdown; return true;
        case SYM_GEN_activated_1292: out = this->f_activated; return true;
        case SYM_GEN__dbg_spdt_1293: out = this->f__dbg_spdt; return true;
        case SYM_GEN__tick_timer_left_1109: out = this->f__tick_timer_left; return true;
        case SYM_GEN__tick_timer_active_1110: out = this->f__tick_timer_active; return true;
        case SYM_GEN_max_time_1294: out = this->f_max_time; return true;
        case SYM_GEN_timed_out_1295: out = this->f_timed_out; return true;
        case SYM_GEN__pending_deferred_1296: out = this->f__pending_deferred; return true;
        case SYM_GEN_RoundResult_1314: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreCombat_RoundResult); return true;
        case SYM_GEN_CoreItemSort_1318: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreCombat__INNER__CoreItemSort); return true;
        case SYM_GEN_FATIGUE_TIME_1277: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_FATIGUE_START_DELAY_1278: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_FATIGUE_SLOW_TIME_1279: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreCombat::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_ctx_3: this->f_ctx = val; return true;
        case SYM_GEN_player_1280: this->f_player = val; return true;
        case SYM_GEN_opponent_73: this->f_opponent = val; return true;
        case SYM_GEN_ordered_items_1281: this->f_ordered_items = val; return true;
        case SYM_GEN_result_1282: this->f_result = gd::gd_coerce_int(val); return true;
        case SYM_GEN_fight_ended_1283: this->f_fight_ended = val; return true;
        case SYM_GEN_combat_time_1284: this->f_combat_time = val; return true;
        case SYM_GEN_fatigue_counter_1285: this->f_fatigue_counter = val; return true;
        case SYM_GEN_fatigue_started_1286: this->f_fatigue_started = val; return true;
        case SYM_GEN_fatigue_next_tick_1287: this->f_fatigue_next_tick = val; return true;
        case SYM_GEN_fatigue_interval_1288: this->f_fatigue_interval = val; return true;
        case SYM_GEN_time_advance_1289: this->f_time_advance = val; return true;
        case SYM_GEN_speed_scale_1290: this->f_speed_scale = val; return true;
        case SYM_GEN__activate_countdown_1291: this->f__activate_countdown = val; return true;
        case SYM_GEN_activated_1292: this->f_activated = val; return true;
        case SYM_GEN__dbg_spdt_1293: this->f__dbg_spdt = val; return true;
        case SYM_GEN__tick_timer_left_1109: this->f__tick_timer_left = val; return true;
        case SYM_GEN__tick_timer_active_1110: this->f__tick_timer_active = val; return true;
        case SYM_GEN_max_time_1294: this->f_max_time = val; return true;
        case SYM_GEN_timed_out_1295: this->f_timed_out = val; return true;
        case SYM_GEN__pending_deferred_1296: this->f__pending_deferred = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreCombat::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_setup_70: return true;
        case SYM_GEN_startBattle_1297: return true;
        case SYM_GEN_prepareItems_1298: return true;
        case SYM_GEN_resetInventories_1299: return true;
        case SYM_GEN_activateItems_1300: return true;
        case SYM_GEN_physicsTick_132: return true;
        case SYM_GEN_run_1301: return true;
        case SYM_GEN__fatigueTick_1302: return true;
        case SYM_GEN_startFatigue_1303: return true;
        case SYM_GEN_dealFatigueDamage_1304: return true;
        case SYM_GEN_hasFatigueStarted_1305: return true;
        case SYM_GEN_advanceTime_1306: return true;
        case SYM_GEN_getEffectiveTime_1307: return true;
        case SYM_GEN_endCombat_1308: return true;
        case SYM_GEN_forceLoseCombat_1309: return true;
        case SYM_GEN__flushDeferred_1310: return true;
        case SYM_GEN_combatEndDeferred_1311: return true;
        case SYM_GEN_playerWins_1312: return true;
        case SYM_GEN_winner_1313: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreCombat::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_setup_70: out = fn_setup(args, argc); return true;
        case SYM_GEN_startBattle_1297: out = fn_startBattle(args, argc); return true;
        case SYM_GEN_prepareItems_1298: out = fn_prepareItems(args, argc); return true;
        case SYM_GEN_resetInventories_1299: out = fn_resetInventories(args, argc); return true;
        case SYM_GEN_activateItems_1300: out = fn_activateItems(args, argc); return true;
        case SYM_GEN_physicsTick_132: out = fn_physicsTick(args, argc); return true;
        case SYM_GEN_run_1301: out = fn_run(args, argc); return true;
        case SYM_GEN__fatigueTick_1302: out = fn__fatigueTick(args, argc); return true;
        case SYM_GEN_startFatigue_1303: out = fn_startFatigue(args, argc); return true;
        case SYM_GEN_dealFatigueDamage_1304: out = fn_dealFatigueDamage(args, argc); return true;
        case SYM_GEN_hasFatigueStarted_1305: out = fn_hasFatigueStarted(args, argc); return true;
        case SYM_GEN_advanceTime_1306: out = fn_advanceTime(args, argc); return true;
        case SYM_GEN_getEffectiveTime_1307: out = fn_getEffectiveTime(args, argc); return true;
        case SYM_GEN_endCombat_1308: out = fn_endCombat(args, argc); return true;
        case SYM_GEN_forceLoseCombat_1309: out = fn_forceLoseCombat(args, argc); return true;
        case SYM_GEN__flushDeferred_1310: out = fn__flushDeferred(args, argc); return true;
        case SYM_GEN_combatEndDeferred_1311: out = fn_combatEndDeferred(args, argc); return true;
        case SYM_GEN_playerWins_1312: out = fn_playerWins(args, argc); return true;
        case SYM_GEN_winner_1313: out = fn_winner(args, argc); return true;
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
    gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1280, lv__player);
    gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_opponent_73, lv__opponent);
    gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_1387, gd::GdVal::from_obj(this));
    (void)([&]() { gd::GdVal _ca[] = {this->f_opponent}; return gd::call_method(gd_ctx, this->f_player, SYM_GEN_setOpponent_1113, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_player}; return gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_setOpponent_1113, _ca, 1); })();
    (void)gd::call_method(gd_ctx, this->f_player, SYM_GEN_clearCharacterDiedHandlers_1115, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_clearCharacterDiedHandlers_1115, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {([&]() { auto* fr = gd_ctx.arena.make<gd::GdFuncRef>(); gd::GdVal inst = gd::GdVal::from_obj(this); gd::GdVal mname = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "endCombat", 9u)); fr->instance = (inst.kind == gd::GdVal::Kind::Obj) ? inst.obj : nullptr; fr->method = (mname.kind == gd::GdVal::Kind::Str && mname.str) ? gd::intern_sym(std::string_view(mname.str->data, mname.str->len)) : gd::SYM_NONE; return gd::GdVal::from_funcref(fr); })()}; return gd::call_method(gd_ctx, this->f_player, SYM_GEN_registerCharacterDied_1114, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { auto* fr = gd_ctx.arena.make<gd::GdFuncRef>(); gd::GdVal inst = gd::GdVal::from_obj(this); gd::GdVal mname = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "endCombat", 9u)); fr->instance = (inst.kind == gd::GdVal::Kind::Obj) ? inst.obj : nullptr; fr->method = (mname.kind == gd::GdVal::Kind::Str && mname.str) ? gd::intern_sym(std::string_view(mname.str->data, mname.str->len)) : gd::SYM_NONE; return gd::GdVal::from_funcref(fr); })()}; return gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_registerCharacterDied_1114, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_startBattle(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_player_items = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_opponent_items = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_preordered = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    lv_preordered = gd::gd_coerce_bool(lv_preordered);
    gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_fight_ended_1283, gd::GdVal::from_bool(false));
    this->f_fight_ended = gd::GdVal::from_bool(false);
    this->f_result = gd::gd_coerce_int(gd::gd_neg(gd::GdVal::from_int(1LL)));
    this->f_timed_out = gd::GdVal::from_bool(false);
    this->f_activated = gd::GdVal::from_bool(false);
    this->f__pending_deferred = gd::GdVal::from_bool(false);
    gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_out_of_stamina_count_1399, gd::GdVal::from_int(0LL));
    this->f_combat_time = gd::GdVal::from_float(0.0);
    gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_time_1284, gd::GdVal::from_float(0.0));
    this->f_fatigue_counter = gd::GdVal::from_int(0LL);
    this->f_fatigue_started = gd::GdVal::from_bool(false);
    this->f_fatigue_interval = gd::GdVal::from_float(0.0);
    this->f_fatigue_next_tick = gd::GdVal::from_float(0.0);
    this->f_speed_scale = gd::GdVal::from_float(1.0);
    if (gd::gd_truth(lv_preordered)) {
        this->f_ordered_items = gd::gd_add(gd_ctx, lv_player_items, lv_opponent_items);
        { gd::GdVal _t731 = gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373); gd::set_prop(gd_ctx, _t731, SYM_GEN_globalChainOpen_1635, gd::GdVal::from_bool(true)); }
    }
    else {
        gd::GdVal lv_p_items = gd::call_method(gd_ctx, lv_player_items, gd::SYM_duplicate, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_p_items}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), gd::SYM_shuffle, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCombat__INNER__CoreItemSort), gd::SYM_new, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "sort_TriggerPriority", 20u))}; return gd::call_method(gd_ctx, lv_p_items, gd::SYM_sort_custom, _ca, 2); })();
        gd::GdVal lv_o_items = gd::call_method(gd_ctx, lv_opponent_items, gd::SYM_duplicate, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_o_items}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), gd::SYM_shuffle, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCombat__INNER__CoreItemSort), gd::SYM_new, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "sort_TriggerPriority", 20u))}; return gd::call_method(gd_ctx, lv_o_items, gd::SYM_sort_custom, _ca, 2); })();
        this->f_ordered_items = gd::gd_add(gd_ctx, lv_p_items, lv_o_items);
    }
    (void)([&]() { gd::GdVal _ca[] = {this->f_ordered_items}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_prepareItems_1298, _ca, 1); })();
    this->f__activate_countdown = gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreContext), SYM_GEN_COMBAT_DELAY_1372);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_prepareItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_items = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t732 = gd::gd_iter_seq(gd_ctx.arena, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {this->f_player, this->f_opponent})));
        gd::GdArr* _t733 = (_t732.kind == gd::GdVal::Kind::Arr) ? _t732.arr : nullptr;
        uint32_t _len__t734 = _t733 ? _t733->len : 0u;
        for (uint32_t _t734 = 0; _t734 < _len__t734; ++_t734) {
            gd::GdVal lv_character = _t733->data[_t734];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_character, SYM_GEN_inventory_5), gd::GdVal::null())))) {
                gd::set_prop(gd_ctx, lv_character, SYM_GEN_inventory_5, ([&]() { gd::GdVal _ca[] = {lv_character}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreGrid), gd::SYM_new, _ca, 1); })());
            }
        }
    }
    {
        gd::GdVal _t735 = gd::gd_iter_seq(gd_ctx.arena, lv_items);
        gd::GdArr* _t736 = (_t735.kind == gd::GdVal::Kind::Arr) ? _t735.arr : nullptr;
        uint32_t _len__t737 = _t736 ? _t736->len : 0u;
        for (uint32_t _t737 = 0; _t737 < _len__t737; ++_t737) {
            gd::GdVal lv_item = _t736->data[_t737];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_item, SYM_GEN_ctx_3), gd::GdVal::null())))) {
                gd::set_prop(gd_ctx, lv_item, SYM_GEN_ctx_3, this->f_ctx);
            }
            if (gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_placed_6))) {
                continue;
            }
            gd::GdVal lv_ch = gd::call_method(gd_ctx, lv_item, SYM_GEN_character_72, nullptr, 0);
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_ch, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_ch, SYM_GEN_inventory_5), gd::GdVal::null())))) : gd::GdVal::from_bool(false)))) {
                gd::set_prop(gd_ctx, lv_ch, SYM_GEN_inventory_5, ([&]() { gd::GdVal _ca[] = {lv_ch}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreGrid), gd::SYM_new, _ca, 1); })());
            }
            gd::GdVal lv_grid = (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_ch, gd::GdVal::null()))) ? (gd::get_prop(gd_ctx, lv_ch, SYM_GEN_inventory_5)) : (gd::get_prop(gd_ctx, this->f_player, SYM_GEN_inventory_5)));
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::get_prop(gd_ctx, lv_item, SYM_GEN_occupiedCells_50)}; return gd::call_method(gd_ctx, lv_grid, SYM_GEN_addItem_1525, _ca, 2); })();
        }
    }
    (void)gd::call_method(gd_ctx, this->f_player, SYM_GEN_prepare_120, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_prepare_120, nullptr, 0);
    {
        gd::GdVal _t738 = gd::gd_iter_seq(gd_ctx.arena, lv_items);
        gd::GdArr* _t739 = (_t738.kind == gd::GdVal::Kind::Arr) ? _t738.arr : nullptr;
        uint32_t _len__t740 = _t739 ? _t739->len : 0u;
        for (uint32_t _t740 = 0; _t740 < _len__t740; ++_t740) {
            gd::GdVal lv_item = _t739->data[_t740];
            (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_prepare_120, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_resetInventories(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t741 = gd::gd_iter_seq(gd_ctx.arena, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {this->f_player, this->f_opponent})));
        gd::GdArr* _t742 = (_t741.kind == gd::GdVal::Kind::Arr) ? _t741.arr : nullptr;
        uint32_t _len__t743 = _t742 ? _t742->len : 0u;
        for (uint32_t _t743 = 0; _t743 < _len__t743; ++_t743) {
            gd::GdVal lv_character = _t742->data[_t743];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_character, SYM_GEN_inventory_5), gd::GdVal::null())))) {
                (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_character, SYM_GEN_inventory_5), SYM_GEN_cleanUp_1529, nullptr, 0);
            }
            {
                gd::GdVal _t744 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, lv_character, SYM_GEN_items_1088));
                gd::GdArr* _t745 = (_t744.kind == gd::GdVal::Kind::Arr) ? _t744.arr : nullptr;
                uint32_t _len__t746 = _t745 ? _t745->len : 0u;
                for (uint32_t _t746 = 0; _t746 < _len__t746; ++_t746) {
                    gd::GdVal lv_item = _t745->data[_t746];
                    gd::set_prop(gd_ctx, lv_item, SYM_GEN_placed_6, gd::GdVal::from_bool(false));
                    gd::set_prop(gd_ctx, lv_item, SYM_GEN_consumed_58, gd::GdVal::from_bool(false));
                }
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_activateItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_items = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "combat_start", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_emit_signal, _ca, 1); })();
    this->f_combat_time = gd::GdVal::from_float(0.0);
    gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_time_1284, gd::GdVal::from_float(0.0));
    this->f_fatigue_next_tick = gd::gd_sub(gd::gd_sub(Gd__gd_core__CoreCombat::get_static_const_or_enum(gd_ctx, SYM_GEN_FATIGUE_TIME_1277), Gd__gd_core__CoreCombat::get_static_const_or_enum(gd_ctx, SYM_GEN_FATIGUE_START_DELAY_1278)), this->f_time_advance);
    this->f_fatigue_interval = gd::GdVal::from_float(0.0);
    this->f_fatigue_started = gd::GdVal::from_bool(false);
    (void)gd::call_method(gd_ctx, this->f_player, SYM_GEN_combatStart_125, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_combatStart_125, nullptr, 0);
    {
        gd::GdVal _t747 = gd::gd_iter_seq(gd_ctx.arena, lv_items);
        gd::GdArr* _t748 = (_t747.kind == gd::GdVal::Kind::Arr) ? _t747.arr : nullptr;
        uint32_t _len__t749 = _t748 ? _t748->len : 0u;
        for (uint32_t _t749 = 0; _t749 < _len__t749; ++_t749) {
            gd::GdVal lv_item = _t748->data[_t749];
            (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_preCombatStart_122, nullptr, 0);
        }
    }
    gd::GdVal lv__inj_at = gd::GdVal::from_int(0LL);
    gd::GdVal lv__inj_at_s = gd::GdVal::from_cstr(gd_ctx.arena, "");
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv__inj_at_s, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u)))))) {
        lv__inj_at = gd::gd_coerce_int(lv__inj_at_s);
    }
    gd::GdVal lv__inj_idx = gd::GdVal::from_int(0LL);
    (void)gd::GdVal::null();
    {
        gd::GdVal _t750 = gd::gd_iter_seq(gd_ctx.arena, lv_items);
        gd::GdArr* _t751 = (_t750.kind == gd::GdVal::Kind::Arr) ? _t750.arr : nullptr;
        uint32_t _len__t752 = _t751 ? _t751->len : 0u;
        for (uint32_t _t752 = 0; _t752 < _len__t752; ++_t752) {
            gd::GdVal lv_item = _t751->data[_t752];
            (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_combatStart_125, nullptr, 0);
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv__inj_at, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__inj_idx, lv__inj_at)))) : gd::GdVal::from_bool(false)))) {
                (void)gd::GdVal::null();
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.0), gd::GdVal::from_float(1.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), gd::SYM_randf_range, _ca, 2); })();
            }
            lv__inj_idx = gd::gd_add(gd_ctx, lv__inj_idx, gd::GdVal::from_int(1LL));
        }
    }
    {
        gd::GdVal _t753 = gd::gd_iter_seq(gd_ctx.arena, lv_items);
        gd::GdArr* _t754 = (_t753.kind == gd::GdVal::Kind::Arr) ? _t753.arr : nullptr;
        uint32_t _len__t755 = _t754 ? _t754->len : 0u;
        for (uint32_t _t755 = 0; _t755 < _len__t755; ++_t755) {
            gd::GdVal lv_item = _t754->data[_t755];
            (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_postCombatStart_126, nullptr, 0);
        }
    }
    this->f_activated = gd::GdVal::from_bool(true);
    (void)gd::call_method(gd_ctx, this->f_player, SYM_GEN_rebuildTimerSeen_137, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_rebuildTimerSeen_137, nullptr, 0);
    {
        gd::GdVal _t756 = gd::gd_iter_seq(gd_ctx.arena, lv_items);
        gd::GdArr* _t757 = (_t756.kind == gd::GdVal::Kind::Arr) ? _t756.arr : nullptr;
        uint32_t _len__t758 = _t757 ? _t757->len : 0u;
        for (uint32_t _t758 = 0; _t758 < _len__t758; ++_t758) {
            gd::GdVal lv_item = _t757->data[_t758];
            (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_rebuildTimerSeen_137, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_physicsTick(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (gd::gd_truth(this->f__pending_deferred)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__flushDeferred_1310, nullptr, 0);
        return gd::GdVal::null();
    }
    if (gd::gd_truth(this->f_fight_ended)) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated)))) {
        (void)gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_flushDeferred_1420, nullptr, 0);
        (void)gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_flushIdleFrameCalls_1422, nullptr, 0);
        (void)gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_flushDeferred_1420, nullptr, 0);
        this->f__activate_countdown = gd::gd_sub(this->f__activate_countdown, lv_delta);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f__activate_countdown, gd::GdVal::from_float(0.0))))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_ordered_items}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activateItems_1300, _ca, 1); })();
        }
        (void)gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_flushDeferred_1420, nullptr, 0);
        return gd::GdVal::null();
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_advancePhysicsFrame_1415, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_physicsTickCharacter_1272, _ca, 1); })();
    {
        gd::GdVal _t759 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_opponent, SYM_GEN_inventory_5), SYM_GEN_getItems_1510, nullptr, 0));
        gd::GdArr* _t760 = (_t759.kind == gd::GdVal::Kind::Arr) ? _t759.arr : nullptr;
        uint32_t _len__t761 = _t760 ? _t760->len : 0u;
        for (uint32_t _t761 = 0; _t761 < _len__t761; ++_t761) {
            gd::GdVal lv_item = _t760->data[_t761];
            (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_physicsTick_132, _ca, 1); })();
            if (gd::gd_truth((gd::gd_truth(this->f__dbg_spdt) ? gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN__cooldown_active_44))) : gd::GdVal::from_bool(false)))) {
                (void)gd::GdVal::null();
            }
        }
    }
    this->f_combat_time = gd::gd_add(gd_ctx, this->f_combat_time, lv_delta);
    gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_time_1284, this->f_combat_time);
    (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::call_method(gd_ctx, this->f_player, SYM_GEN_physicsTickCharacter_1272, _ca, 1); })();
    {
        gd::GdVal _t762 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_player, SYM_GEN_inventory_5), SYM_GEN_getItems_1510, nullptr, 0));
        gd::GdArr* _t763 = (_t762.kind == gd::GdVal::Kind::Arr) ? _t762.arr : nullptr;
        uint32_t _len__t764 = _t763 ? _t763->len : 0u;
        for (uint32_t _t764 = 0; _t764 < _len__t764; ++_t764) {
            gd::GdVal lv_item = _t763->data[_t764];
            (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_physicsTick_132, _ca, 1); })();
            if (gd::gd_truth((gd::gd_truth(this->f__dbg_spdt) ? gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN__cooldown_active_44))) : gd::GdVal::from_bool(false)))) {
                (void)gd::GdVal::null();
            }
        }
    }
    {
        gd::GdVal _t765 = gd::gd_iter_seq(gd_ctx.arena, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {this->f_opponent, this->f_player})));
        gd::GdArr* _t766 = (_t765.kind == gd::GdVal::Kind::Arr) ? _t765.arr : nullptr;
        uint32_t _len__t767 = _t766 ? _t766->len : 0u;
        for (uint32_t _t767 = 0; _t767 < _len__t767; ++_t767) {
            gd::GdVal lv_character = _t766->data[_t767];
            (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::call_method(gd_ctx, lv_character, SYM_GEN_tickPhysicsTimers_1273, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::call_method(gd_ctx, lv_character, SYM_GEN_tickBuffs_1274, _ca, 1); })();
            {
                gd::GdVal _t768 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_character, SYM_GEN_inventory_5), SYM_GEN_getItems_1510, nullptr, 0));
                gd::GdArr* _t769 = (_t768.kind == gd::GdVal::Kind::Arr) ? _t768.arr : nullptr;
                uint32_t _len__t770 = _t769 ? _t769->len : 0u;
                for (uint32_t _t770 = 0; _t770 < _len__t770; ++_t770) {
                    gd::GdVal lv_item = _t769->data[_t770];
                    (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_tickTimersPass_136, _ca, 1); })();
                }
            }
        }
    }
    (void)gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_flushDeferred_1420, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_flushIdleFrameCalls_1422, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__fatigueTick_1302, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_flushDeferred_1420, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_fight_ended_1283))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_PHYSICS_DELTA_1371)}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_lib_fires_tick_1410, _ca, 1); })();
        (void)gd::call_method(gd_ctx, this->f_ctx, SYM_GEN__flushTimed_1417, nullptr, 0);
    }
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_fight_ended))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_combat_time, this->f_max_time)))) : gd::GdVal::from_bool(false)))) {
        this->f_timed_out = gd::GdVal::from_bool(true);
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_forceLoseCombat_1309, nullptr, 0);
    }
    if (gd::gd_truth(this->f__pending_deferred)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__flushDeferred_1310, nullptr, 0);
    }
    (void)gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_flushDeferred_1420, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_run(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    while (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_fight_ended)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreContext), SYM_GEN_PHYSICS_DELTA_1371)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_physicsTick_132, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn__fatigueTick(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_fatigue_next_tick = gd::gd_sub(this->f_fatigue_next_tick, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreContext), SYM_GEN_PHYSICS_DELTA_1371));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_fatigue_next_tick, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_fatigue_started)))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_startFatigue_1303, nullptr, 0);
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealFatigueDamage_1304, nullptr, 0);
    }
    this->f_fatigue_next_tick = this->f_fatigue_interval;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_startFatigue(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Start", 5u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1376), SYM_GEN_playFatigueAnimation_1532, _ca, 1); })();
    this->f_fatigue_started = gd::GdVal::from_bool(true);
    this->f_fatigue_counter = gd::GdVal::from_int(0LL);
    this->f_fatigue_interval = Gd__gd_core__CoreCombat::get_static_const_or_enum(gd_ctx, SYM_GEN_FATIGUE_START_DELAY_1278);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_dealFatigueDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_fatigue_counter, gd::GdVal::from_int(0LL))))) {
        (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1376), SYM_GEN_playFatigueSound_1533, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "fatigue_start", 13u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1375), SYM_GEN_emitSignal_1499, _ca, 2); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_combat_time, Gd__gd_core__CoreCombat::get_static_const_or_enum(gd_ctx, SYM_GEN_FATIGUE_SLOW_TIME_1279))))) {
        this->f_fatigue_counter = gd::gd_add(gd_ctx, this->f_fatigue_counter, gd::gd_add(gd_ctx, gd::GdVal::from_int(1LL), gd::gd_coerce_int(gd::gd_floor(gd::gd_mul(gd::GdVal::from_float(0.1), this->f_fatigue_counter)))));
    }
    else {
        this->f_fatigue_counter = gd::gd_add(gd_ctx, this->f_fatigue_counter, gd::gd_add(gd_ctx, gd::GdVal::from_int(1LL), gd::gd_coerce_int(gd::gd_floor(gd::gd_mul(gd::GdVal::from_float(0.2), this->f_fatigue_counter)))));
    }
    (void)([&]() { gd::GdVal _ca[] = {this->f_fatigue_counter}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_fatigueDamageSource_1397), SYM_GEN_setDamage_1458, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "fatigue_damage_changed", 22u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1375), SYM_GEN_emitSignal_1499, _ca, 2); })();
    (void)gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_takeFatigueDamage_1176, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_player, SYM_GEN_takeFatigueDamage_1176, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Tick", 4u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1376), SYM_GEN_playFatigueAnimation_1532, _ca, 1); })();
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
    gd::GdVal lv_time_left = this->f_fatigue_next_tick;
    gd::GdVal lv_new_time = gd::gd_sub(lv_time_left, lv__time);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_new_time, gd::GdVal::from_int(0LL))))) {
        this->f_fatigue_next_tick = lv_new_time;
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_startFatigue_1303, nullptr, 0);
        this->f_fatigue_next_tick = this->f_fatigue_interval;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_getEffectiveTime(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreContext), SYM_GEN_COMBAT_DELAY_1372), this->f_combat_time), this->f_time_advance);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_endCombat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_fight_ended)) {
        return gd::GdVal::null();
    }
    this->f_fight_ended = gd::GdVal::from_bool(true);
    gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_fight_ended_1283, gd::GdVal::from_bool(true));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(gd::get_prop(gd_ctx, this->f_opponent, SYM_GEN_curHealth_1046), gd::GdVal::from_int(0LL))))) {
        this->f_result = gd::gd_coerce_int(gd::get_prop(gd_ctx, Gd__gd_core__CoreCombat::get_static_const_or_enum(gd_ctx, SYM_GEN_RoundResult_1314), SYM_GEN_Win_2725));
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), gd::gd_sub(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, this->f_player, SYM_GEN_classRoundSoundCount_1121, _ca, 1); })(), gd::GdVal::from_int(1LL))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), gd::SYM_randi_range, _ca, 2); })();
    }
    else {
        this->f_result = gd::gd_coerce_int(gd::get_prop(gd_ctx, Gd__gd_core__CoreCombat::get_static_const_or_enum(gd_ctx, SYM_GEN_RoundResult_1314), SYM_GEN_Loss_2726));
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), gd::gd_sub(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, this->f_player, SYM_GEN_classRoundSoundCount_1121, _ca, 1); })(), gd::GdVal::from_int(1LL))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), gd::SYM_randi_range, _ca, 2); })();
    }
    this->f__pending_deferred = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_forceLoseCombat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_fight_ended)) {
        return gd::GdVal::null();
    }
    this->f_fight_ended = gd::GdVal::from_bool(true);
    gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_fight_ended_1283, gd::GdVal::from_bool(true));
    this->f_result = gd::gd_coerce_int(gd::get_prop(gd_ctx, Gd__gd_core__CoreCombat::get_static_const_or_enum(gd_ctx, SYM_GEN_RoundResult_1314), SYM_GEN_Loss_2726));
    this->f__pending_deferred = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn__flushDeferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f__pending_deferred = gd::GdVal::from_bool(false);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_combatEndDeferred_1311, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_combatEndDeferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "combat_end", 10u)), this->f_result}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_emit_signal, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "round_result", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_emit_signal, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1375), SYM_GEN_disconnectAll_1504, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_player, SYM_GEN_combatEnd_129, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_combatEnd_129, nullptr, 0);
    this->f__tick_timer_active = gd::GdVal::from_bool(false);
    this->f__tick_timer_left = gd::GdVal::from_float(0.0);
    this->f__tick_timer_active = gd::GdVal::from_bool(false);
    this->f__tick_timer_left = gd::GdVal::from_float(0.0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Hide", 4u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1376), SYM_GEN_playFatigueAnimation_1532, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_fatigueDamageSource_1397), SYM_GEN_setDamage_1458, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_result, gd::get_prop(gd_ctx, Gd__gd_core__CoreCombat::get_static_const_or_enum(gd_ctx, SYM_GEN_RoundResult_1314), SYM_GEN_Win_2725))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_setCurrentHealth_1136, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_max(gd::GdVal::from_int(1LL), gd::call_method(gd_ctx, this->f_player, SYM_GEN_getCurrentHealth_1134, nullptr, 0))}; return gd::call_method(gd_ctx, this->f_player, SYM_GEN_setCurrentHealth_1136, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, this->f_player, SYM_GEN_setCurrentHealth_1136, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_max(gd::GdVal::from_int(1LL), gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_getCurrentHealth_1134, nullptr, 0))}; return gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_setCurrentHealth_1136, _ca, 1); })();
    }
    {
        gd::GdVal _t771 = gd::gd_iter_seq(gd_ctx.arena, this->f_ordered_items);
        gd::GdArr* _t772 = (_t771.kind == gd::GdVal::Kind::Arr) ? _t771.arr : nullptr;
        uint32_t _len__t773 = _t772 ? _t772->len : 0u;
        for (uint32_t _t773 = 0; _t773 < _len__t773; ++_t773) {
            gd::GdVal lv_item = _t772->data[_t773];
            (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_combatEnd_129, nullptr, 0);
        }
    }
    (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rope_speedups_1392), gd::SYM_clear, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_cube_advanced_1393), gd::SYM_clear, nullptr, 0);
    gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_sandbag_active_1389, gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_playerWins(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_eq(this->f_result, gd::get_prop(gd_ctx, Gd__gd_core__CoreCombat::get_static_const_or_enum(gd_ctx, SYM_GEN_RoundResult_1314), SYM_GEN_Win_2725)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCombat::fn_winner(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_result, gd::get_prop(gd_ctx, Gd__gd_core__CoreCombat::get_static_const_or_enum(gd_ctx, SYM_GEN_RoundResult_1314), SYM_GEN_Win_2725))))) {
        return this->f_player;
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_result, gd::get_prop(gd_ctx, Gd__gd_core__CoreCombat::get_static_const_or_enum(gd_ctx, SYM_GEN_RoundResult_1314), SYM_GEN_Loss_2726))))) {
        return this->f_opponent;
    }
    return gd::GdVal::null();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreCombat(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreCombat>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__CoreCombat = {CLS_Gd__gd_core__CoreCombat, "CoreCombat", "res://gd_core/CoreCombat.gd", nullptr, false, _alloc_Gd__gd_core__CoreCombat, &Gd__gd_core__CoreCombat::get_static_prop_fn, &Gd__gd_core__CoreCombat::call_static_fn};

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
        case SYM_GEN_luckBalance_1660: return gd::GdVal::from_float(0.2);
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
        case SYM_GEN_expectedWins_1653: out = this->f_expectedWins; return true;
        case SYM_GEN_wins_1654: out = this->f_wins; return true;
        case SYM_GEN_balancedness_1655: out = this->f_balancedness; return true;
        case SYM_GEN_lastResult_1656: out = this->f_lastResult; return true;
        case SYM_GEN_extraLuck_1657: out = this->f_extraLuck; return true;
        case SYM_GEN_lastTarget_1658: out = this->f_lastTarget; return true;
        case SYM_GEN_accChance_1659: out = this->f_accChance; return true;
        case SYM_GEN__rng_1455: out = this->f__rng; return true;
        case SYM_GEN_luckBalance_1660: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreRng__INNER__BalancedRng::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_expectedWins_1653: this->f_expectedWins = gd::gd_coerce_float(val); return true;
        case SYM_GEN_wins_1654: this->f_wins = val; return true;
        case SYM_GEN_balancedness_1655: this->f_balancedness = val; return true;
        case SYM_GEN_lastResult_1656: this->f_lastResult = val; return true;
        case SYM_GEN_extraLuck_1657: this->f_extraLuck = val; return true;
        case SYM_GEN_lastTarget_1658: this->f_lastTarget = val; return true;
        case SYM_GEN_accChance_1659: this->f_accChance = val; return true;
        case SYM_GEN__rng_1455: this->f__rng = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreRng__INNER__BalancedRng::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_setBias_1661: return true;
        case SYM_GEN_rollPercent_1662: return true;
        case SYM_GEN_roll_1636: return true;
        case SYM_GEN_roll2_1663: return true;
        case SYM_GEN_roll1_1664: return true;
        case SYM_GEN_reset_1020: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreRng__INNER__BalancedRng::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_setBias_1661: out = fn_setBias(args, argc); return true;
        case SYM_GEN_rollPercent_1662: out = fn_rollPercent(args, argc); return true;
        case SYM_GEN_roll_1636: out = fn_roll(args, argc); return true;
        case SYM_GEN_roll2_1663: out = fn_roll2(args, argc); return true;
        case SYM_GEN_roll1_1664: out = fn_roll1(args, argc); return true;
        case SYM_GEN_reset_1020: out = fn_reset(args, argc); return true;
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
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f__rng, gd::GdVal::null())))) {
        this->f_expectedWins = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.2), gd::gd_neg(gd::GdVal::from_float(0.2))}; return gd::call_method(gd_ctx, this->f__rng, gd::SYM_randf_range, _ca, 2); })());
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
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_target = gd::gd_coerce_float(lv_target);
    return ([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, lv_target, gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_roll_1636, _ca, 1); })();
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
    if (gd::gd_truth((gd::gd_truth(gd::get_prop(gd_ctx, this->f__rng, SYM_GEN_oracle_trace_1631)) ? gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, this->f__rng, SYM_GEN__stacktrace_1633))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BALROLL", 7u)), gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "ch=", 3u)), ([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "ew=", 3u)), ([&]() { gd::GdVal _ca[] = {this->f_expectedWins}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " w=", 3u))), ([&]() { gd::GdVal _ca[] = {this->f_wins}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lr=", 3u)), ([&]() { gd::GdVal _ca[] = {this->f_lastResult}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::call_method(gd_ctx, this->f__rng, SYM_GEN_trace_diag_1643, _ca, 4); })();
    }
    gd::GdVal lv_result = ([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::call_method(gd_ctx, this->f__rng, SYM_GEN_flip_1637, _ca, 1); })();
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
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::call_method(gd_ctx, this->f__rng, SYM_GEN_flip_1637, _ca, 1); })())) {
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
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_accChance}; return gd::call_method(gd_ctx, this->f__rng, SYM_GEN_flip_1637, _ca, 1); })())) {
        this->f_accChance = gd::gd_sub(lv_target, this->f_extraLuck);
        return gd::GdVal::from_bool(true);
    }
    else {
        this->f_accChance = gd::gd_add(gd_ctx, this->f_accChance, Gd__gd_core__CoreRng__INNER__BalancedRng::get_static_const_or_enum(gd_ctx, SYM_GEN_luckBalance_1660));
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
static gd::GdObj* _alloc_Gd__gd_core__CoreRng__INNER__BalancedRng(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreRng__INNER__BalancedRng>(&ctx); }
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
        case SYM_GEN_cards_1736: out = this->f_cards; return true;
        case SYM_GEN_cardActivations_1737: out = this->f_cardActivations; return true;
        case SYM_GEN_chainStarted_1738: out = this->f_chainStarted; return true;
        case SYM_GEN_connector_881: out = this->f_connector; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__DeckofCards::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_cards_1736: this->f_cards = val; return true;
        case SYM_GEN_cardActivations_1737: this->f_cardActivations = val; return true;
        case SYM_GEN_chainStarted_1738: this->f_chainStarted = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_connector_881: this->f_connector = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__DeckofCards::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onAddToInventory_417: return true;
        case SYM_GEN_onRemoveFromInventory_416: return true;
        case SYM_GEN_resetChain_1739: return true;
        case SYM_GEN_countDuplicates_1706: return true;
        case SYM_GEN_updateCards_1740: return true;
        case SYM_GEN_onItemAdded_435: return true;
        case SYM_GEN_onItemRemoved_436: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_notifyActivation_1741: return true;
        case SYM_GEN_getGatedDescriptor_952: return true;
        case SYM_GEN_getRelatedItemColumns_695: return true;
        case SYM_GEN_getRelatedItemHeight_696: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__DeckofCards::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onAddToInventory_417: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_416: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_resetChain_1739: out = fn_resetChain(args, argc); return true;
        case SYM_GEN_countDuplicates_1706: out = fn_countDuplicates(args, argc); return true;
        case SYM_GEN_updateCards_1740: out = fn_updateCards(args, argc); return true;
        case SYM_GEN_onItemAdded_435: out = fn_onItemAdded(args, argc); return true;
        case SYM_GEN_onItemRemoved_436: out = fn_onItemRemoved(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_notifyActivation_1741: out = fn_notifyActivation(args, argc); return true;
        case SYM_GEN_getGatedDescriptor_952: out = fn_getGatedDescriptor(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_695: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_696: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Card_2672)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeckofCards::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateCards_1740, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeckofCards::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetChain_1739, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeckofCards::fn_resetChain(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t774 = gd::gd_iter_seq(gd_ctx.arena, this->f_cards);
        gd::GdArr* _t775 = (_t774.kind == gd::GdVal::Kind::Arr) ? _t774.arr : nullptr;
        uint32_t _len__t776 = _t775 ? _t775->len : 0u;
        for (uint32_t _t776 = 0; _t776 < _len__t776; ++_t776) {
            gd::GdVal lv_card = _t775->data[_t776];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::gd_neg(gd::GdVal::from_int(1LL)), gd::call_method(gd_ctx, this->f_cards, gd::SYM_size, nullptr, 0)}; return gd::call_method(gd_ctx, lv_card, SYM_GEN_notifyChainPosition_890, _ca, 3); })();
        }
    }
    (void)gd::call_method(gd_ctx, this->f_cards, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeckofCards::fn_countDuplicates(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_untilCardIndex = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_descriptors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t777 = gd::gd_iter_seq(gd_ctx.arena, lv_untilCardIndex);
        gd::GdArr* _t778 = (_t777.kind == gd::GdVal::Kind::Arr) ? _t777.arr : nullptr;
        uint32_t _len__t779 = _t778 ? _t778->len : 0u;
        for (uint32_t _t779 = 0; _t779 < _len__t779; ++_t779) {
            gd::GdVal lv_i = _t778->data[_t779];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_index(gd_ctx, this->f_cards, lv_i), SYM_GEN_descriptor_2)}; return gd::call_method(gd_ctx, lv_descriptors, gd::SYM_push_back, _ca, 1); })();
        }
    }
    return ([&]() { gd::GdVal _ca[] = {lv_descriptors}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_countDuplicates_1706, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeckofCards::fn_updateCards(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetChain_1739, nullptr, 0);
    gd::GdVal lv_affected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_affected, gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL))}; return gd::call_method(gd_ctx, this->f_cards, gd::SYM_push_back, _ca, 1); })();
        gd::GdVal lv_nextCard = gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_cards, gd::GdVal::from_int(0LL)), SYM_GEN_getNextCard_887, nullptr, 0);
        while (gd::gd_truth((gd::gd_truth(lv_nextCard) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_nextCard, this->f_cards))))) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_nextCard}; return gd::call_method(gd_ctx, this->f_cards, gd::SYM_push_back, _ca, 1); })();
            lv_nextCard = gd::call_method(gd_ctx, lv_nextCard, SYM_GEN_getNextCard_887, nullptr, 0);
        }
    }
    else {
    }
    gd::GdVal lv_chainLength = gd::call_method(gd_ctx, this->f_cards, gd::SYM_size, nullptr, 0);
    {
        gd::GdVal _t780 = gd::gd_iter_seq(gd_ctx.arena, lv_chainLength);
        gd::GdArr* _t781 = (_t780.kind == gd::GdVal::Kind::Arr) ? _t780.arr : nullptr;
        uint32_t _len__t782 = _t781 ? _t781->len : 0u;
        for (uint32_t _t782 = 0; _t782 < _len__t782; ++_t782) {
            gd::GdVal lv_i = _t781->data[_t782];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_i, lv_chainLength}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_cards, lv_i), SYM_GEN_notifyChainPosition_890, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeckofCards::fn_onItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_onItemAdded_435, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(lv_item, &META_Gd__gd_core_items__Card)))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateCards_1740, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeckofCards::fn_onItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_onItemRemoved_436, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(lv_item, &META_Gd__gd_core_items__Card)))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateCards_1740, nullptr, 0);
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_chainStarted)))) {
        this->f_chainStarted = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        this->f_cardActivations = gd::GdVal::from_int(0LL);
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, this->f_cards, gd::SYM_empty, nullptr, 0))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, this->f_cards, gd::GdVal::from_int(0LL)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "startActivation", 15u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1418, _ca, 3); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__DeckofCards(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__DeckofCards>(&ctx); }
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
        case SYM_GEN_luckNeeded_1778: out = this->f_luckNeeded; return true;
        case SYM_GEN_heatNeeded_1784: out = this->f_heatNeeded; return true;
        case SYM_GEN_manaNeeded_1785: out = this->f_manaNeeded; return true;
        default: break;
    }
    return Gd__gd_core__Food::get_prop(prop, out);
}
bool Gd__gd_core__GingerbreadMan::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_luckNeeded_1778: this->f_luckNeeded = gd::gd_coerce_int(val); return true;
        case SYM_GEN_heatNeeded_1784: this->f_heatNeeded = gd::gd_coerce_int(val); return true;
        case SYM_GEN_manaNeeded_1785: this->f_manaNeeded = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__GingerbreadMan::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Food::has_own_method(m);
}
bool Gd__gd_core__GingerbreadMan::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__GingerbreadMan::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__GingerbreadMan::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_315, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__GingerbreadMan::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getLucky_1217, nullptr, 0), this->f_luckNeeded)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getHeat_1231, nullptr, 0), this->f_heatNeeded)))) {
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getMana_1224, nullptr, 0), this->f_manaNeeded)))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1375), SYM_GEN_LoggingMode_1506), SYM_GEN_Delayed_2588)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1375), SYM_GEN_setLoggingMode_1495, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {this->f_luckNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useLucky_348, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {this->f_heatNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useHeat_352, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_330, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP6_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 1); })();
                (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1375), SYM_GEN_flushLoggingQueue_1498, nullptr, 0);
                (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth_use", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_315, _ca, 1); })();
            }
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__GingerbreadMan::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Food::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_luckNeeded = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0));
    this->f_heatNeeded = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0));
    this->f_manaNeeded = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__GingerbreadMan(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__GingerbreadMan>(&ctx); }
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
        case SYM_GEN_numActivations_1808: out = this->f_numActivations; return true;
        case SYM_GEN_speedBonus_1781: out = this->f_speedBonus; return true;
        case SYM_GEN_maxActivations_1809: out = this->f_maxActivations; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Jynxtorquilla::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numActivations_1808: this->f_numActivations = gd::gd_coerce_int(val); return true;
        case SYM_GEN_speedBonus_1781: this->f_speedBonus = val; return true;
        case SYM_GEN_maxActivations_1809: this->f_maxActivations = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Jynxtorquilla::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Jynxtorquilla::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_93, nullptr, 0);
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
            gd::GdVal _t783 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
            gd::GdArr* _t784 = (_t783.kind == gd::GdVal::Kind::Arr) ? _t783.arr : nullptr;
            uint32_t _len__t785 = _t784 ? _t784->len : 0u;
            for (uint32_t _t785 = 0; _t785 < _len__t785; ++_t785) {
                gd::GdVal lv_item = _t784->data[_t785];
                (void)([&]() { gd::GdVal _ca[] = {this->f_speedBonus}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
            }
        }
        this->f_numActivations = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numActivations, gd::GdVal::from_int(1LL)));
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_getLucky_1217, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeLucky_347, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Jynxtorquilla::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_speedBonus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_maxActivations = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "max", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Jynxtorquilla(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Jynxtorquilla>(&ctx); }
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
        case SYM_GEN_blockAcc_1850: out = this->f_blockAcc; return true;
        case SYM_GEN_blockForMana_1851: out = this->f_blockForMana; return true;
        default: break;
    }
    return Gd__gd_core__Shield::get_prop(prop, out);
}
bool Gd__gd_core__MoonShield::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockAcc_1850: this->f_blockAcc = gd::gd_coerce_int(val); return true;
        case SYM_GEN_blockForMana_1851: this->f_blockForMana = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core__Shield::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__MoonShield::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_afterBlock_1846: return true;
        case SYM_GEN_onItemGaveBlock_1852: return true;
        case SYM_GEN_canBlockDamageRes_1847: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Shield::has_own_method(m);
}
bool Gd__gd_core__MoonShield::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_afterBlock_1846: out = fn_afterBlock(args, argc); return true;
        case SYM_GEN_onItemGaveBlock_1852: out = fn_onItemGaveBlock(args, argc); return true;
        case SYM_GEN_canBlockDamageRes_1847: out = fn_canBlockDamageRes(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBlock_289, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MoonShield::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t786 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t787 = (_t786.kind == gd::GdVal::Kind::Arr) ? _t786.arr : nullptr;
        uint32_t _len__t788 = _t787 ? _t787->len : 0u;
        for (uint32_t _t788 = 0; _t788 < _len__t788; ++_t788) {
            gd::GdVal lv_item = _t787->data[_t788];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Block_2563), gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveBuffPower_301, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gave_block", 10u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onItemGaveBlock", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        }
    }
    this->f_blockAcc = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MoonShield::fn_afterBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0), gd::get_prop(gd_ctx, this->f_blockedDamageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drainStamina_115, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
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
        (void)([&]() { gd::GdVal _ca[] = {lv_mana, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MoonShield::fn_canBlockDamageRes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_triggerOnAttacked_1437, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__MoonShield::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Shield::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_blockForMana = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__MoonShield(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__MoonShield>(&ctx); }
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
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Bag::has_own_method(m);
}
bool Gd__gd_core__ProtectivePurse::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__ProtectivePurse::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__ProtectivePurse::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_totalBlock = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_202, nullptr, 0);
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Bagtacular", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isTypeInInventory_801, _ca, 1); })())) {
        lv_totalBlock = gd::gd_add(gd_ctx, lv_totalBlock, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "block", 5u))}; return gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Bagtacular", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })(), SYM_GEN_getP_186, _ca, 1); })());
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_totalBlock}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ProtectivePurse::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bag::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__ProtectivePurse(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__ProtectivePurse>(&ctx); }
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
        case SYM_GEN_affectedWeapons_1889: out = this->f_affectedWeapons; return true;
        default: break;
    }
    return Gd__gd_core__Goobert::get_prop(prop, out);
}
bool Gd__gd_core__SteelGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedWeapons_1889: this->f_affectedWeapons = val; return true;
        default: break;
    }
    return Gd__gd_core__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__SteelGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_secondary_285: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Goobert::has_own_method(m);
}
bool Gd__gd_core__SteelGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_secondary_285: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__SteelGoobert::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t789 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Secondary_2582)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, _ca, 1); })());
        gd::GdArr* _t790 = (_t789.kind == gd::GdVal::Kind::Arr) ? _t789.arr : nullptr;
        uint32_t _len__t791 = _t790 ? _t790->len : 0u;
        for (uint32_t _t791 = 0; _t791 < _len__t791; ++_t791) {
            gd::GdVal lv_item = _t790->data[_t791];
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, this->f_affectedWeapons, gd::SYM_push_back, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__SteelGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t792 = gd::gd_iter_seq(gd_ctx.arena, this->f_affectedWeapons);
        gd::GdArr* _t793 = (_t792.kind == gd::GdVal::Kind::Arr) ? _t792.arr : nullptr;
        uint32_t _len__t794 = _t793 ? _t793->len : 0u;
        for (uint32_t _t794 = 0; _t794 < _len__t794; ++_t794) {
            gd::GdVal lv_item = _t793->data[_t794];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_159, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__SteelGoobert::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_affectedWeapons, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__SteelGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__SteelGoobert(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__SteelGoobert>(&ctx); }
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
        case SYM_GEN_bonusCounter_1904: out = this->f_bonusCounter; return true;
        case SYM_GEN_tempBonusDam_1905: out = this->f_tempBonusDam; return true;
        default: break;
    }
    return Gd__gd_core__Bow::get_prop(prop, out);
}
bool Gd__gd_core__ThornBow::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusCounter_1904: this->f_bonusCounter = val; return true;
        case SYM_GEN_tempBonusDam_1905: this->f_tempBonusDam = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core__Bow::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__ThornBow::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_hasAttackEffect_293: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onWeaponAttacked_946: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Bow::has_own_method(m);
}
bool Gd__gd_core__ThornBow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_hasAttackEffect_293: out = fn_hasAttackEffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_946: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {this->f_bonusCounter}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ThornBow::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_207, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ThornBow::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_114, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1276), SYM_GEN_Sufficient_2603))))) {
        gd::GdVal lv_res = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_218, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_bonusCounter, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_tempBonusDam, this->f_bonusCounter), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_reduceBonusDamage_308, _ca, 2); })();
            this->f_bonusCounter = gd::GdVal::from_int(0LL);
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusCounter, gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, lv_res, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ThornBow::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        gd::GdVal lv_attackEffectCount = gd::gd_add(gd_ctx, gd::GdVal::from_int(1LL), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollDoubleAttackEffect_185, nullptr, 0));
        {
            gd::GdVal _t795 = gd::gd_iter_seq(gd_ctx.arena, lv_attackEffectCount);
            gd::GdArr* _t796 = (_t795.kind == gd::GdVal::Kind::Arr) ? _t795.arr : nullptr;
            uint32_t _len__t797 = _t796 ? _t796->len : 0u;
            for (uint32_t _t797 = 0; _t797 < _len__t797; ++_t797) {
                gd::GdVal lv_i = _t796->data[_t797];
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getSpikes_1203, nullptr, 0), gd::GdVal::from_int(0LL))))) {
                    this->f_bonusCounter = gd::gd_add(gd_ctx, this->f_bonusCounter, gd::GdVal::from_int(1LL));
                    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useSpikes_335, _ca, 2); })();
                    (void)([&]() { gd::GdVal _ca[] = {this->f_tempBonusDam}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_159, _ca, 1); })();
                }
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {this->f_bonusCounter, gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ThornBow::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bow::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_tempBonusDam = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__ThornBow(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__ThornBow>(&ctx); }
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
        case SYM_GEN_affectedItems_895: out = this->f_affectedItems; return true;
        case SYM_GEN_acornAceDescriptor_896: out = this->f_acornAceDescriptor; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__RangerCollar::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedItems_895: this->f_affectedItems = val; return true;
        case SYM_GEN_acornAceDescriptor_896: this->f_acornAceDescriptor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__RangerCollar::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepare_120: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__RangerCollar::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepare_120: out = fn_prepare(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__RangerCollar::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__RangerCollar::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_affectedItems = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0);
    gd::GdVal lv_numAces = ([&]() { gd::GdVal _ca[] = {this->f_acornAceDescriptor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countAllInInventoryOfType_800, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numAces, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_staminaReduction = gd::gd_mul(lv_numAces, gd::gd_neg(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, this->f_acornAceDescriptor, SYM_GEN_getP_186, _ca, 1); })()));
        {
            gd::GdVal _t798 = gd::gd_iter_seq(gd_ctx.arena, this->f_affectedItems);
            gd::GdArr* _t799 = (_t798.kind == gd::GdVal::Kind::Arr) ? _t798.arr : nullptr;
            uint32_t _len__t800 = _t799 ? _t799->len : 0u;
            for (uint32_t _t800 = 0; _t800 < _len__t800; ++_t800) {
                gd::GdVal lv_item = _t799->data[_t800];
                (void)([&]() { gd::GdVal _ca[] = {lv_staminaReduction}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeStaminaFactor_303, _ca, 1); })();
            }
        }
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_prepare_120, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RangerCollar::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_acornAceDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Acorn Ace", 9u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__RangerCollar(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__RangerCollar>(&ctx); }
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
        case SYM_GEN_bonusDmg_947: out = this->f_bonusDmg; return true;
        case SYM_GEN_bonusDmgPerHit_948: out = this->f_bonusDmgPerHit; return true;
        case SYM_GEN_maxDmg_949: out = this->f_maxDmg; return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::get_prop(prop, out);
}
bool Gd__gd_core_items__BowandArrow::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusDmg_947: this->f_bonusDmg = gd::gd_coerce_int(val); return true;
        case SYM_GEN_bonusDmgPerHit_948: this->f_bonusDmgPerHit = gd::gd_coerce_int(val); return true;
        case SYM_GEN_maxDmg_949: this->f_maxDmg = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__BowandArrow::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_hasAttackEffect_293: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onWeaponAttacked_946: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::has_own_method(m);
}
bool Gd__gd_core_items__BowandArrow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_hasAttackEffect_293: out = fn_hasAttackEffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_946: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BowandArrow::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        gd::GdVal lv_dmgAdded = gd::GdVal::from_bool(false);
        gd::GdVal lv_attackEffectCount = gd::gd_add(gd_ctx, gd::GdVal::from_int(1LL), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollDoubleAttackEffect_185, nullptr, 0));
        {
            gd::GdVal _t801 = gd::gd_iter_seq(gd_ctx.arena, lv_attackEffectCount);
            gd::GdArr* _t802 = (_t801.kind == gd::GdVal::Kind::Arr) ? _t801.arr : nullptr;
            uint32_t _len__t803 = _t802 ? _t802->len : 0u;
            for (uint32_t _t803 = 0; _t803 < _len__t803; ++_t803) {
                gd::GdVal lv_i = _t802->data[_t803];
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_bonusDmg, this->f_maxDmg)))) {
                    this->f_bonusDmg = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_bonusDmg, this->f_bonusDmgPerHit));
                    (void)([&]() { gd::GdVal _ca[] = {this->f_bonusDmgPerHit}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_159, _ca, 1); })();
                    lv_dmgAdded = gd::GdVal::from_bool(true);
                }
            }
        }
        if (gd::gd_truth(lv_dmgAdded)) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusDmg, gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BowandArrow::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bow::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_bonusDmgPerHit = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0));
    this->f_maxDmg = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__BowandArrow(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__BowandArrow>(&ctx); }
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
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_onHeatChanged_909: return true;
        case SYM_GEN_onLuckyChanged_897: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__DancingDragon::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onHeatChanged_909: out = fn_onHeatChanged(args, argc); return true;
        case SYM_GEN_onLuckyChanged_897: out = fn_onLuckyChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Magic_2721)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DancingDragon::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_heat_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onHeatChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_lucky_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onLuckyChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DancingDragon::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numAffected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numAffected, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0), lv_numAffected)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0), lv_numAffected)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DancingDragon::fn_onHeatChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0), lv_amount)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_160, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DancingDragon::fn_onLuckyChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0), lv_amount)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeDebuffResistChances_1200, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DancingDragon::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__DancingDragon(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__DancingDragon>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__DancingDragon = {CLS_Gd__gd_core_items__DancingDragon, "DancingDragon", "res://gd_core_items/DancingDragon.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__DancingDragon, &Gd__gd_core_items__DancingDragon::get_static_prop_fn, &Gd__gd_core_items__DancingDragon::call_static_fn};

void Gd__gd_core_items__Exclusive__AmuletofFeasting::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_foodSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__AmuletofFeasting::meta() const { return &META_Gd__gd_core_items__Exclusive__AmuletofFeasting; }
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofFeasting::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_amuletColor_1924: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.929412), gd::GdVal::from_float(0.498039), gd::GdVal::from_float(0.180392)}; return gd::make_color_from_args(_ca, 3); })();
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
        case SYM_GEN_foodSpeed_1932: out = this->f_foodSpeed; return true;
        case SYM_GEN_amuletColor_1924: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofFeasting::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_foodSpeed_1932: this->f_foodSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__AmuletofFeasting::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_getReplaceDescriptor_1933: return true;
        case SYM_GEN_getRelatedItems_457: return true;
        case SYM_GEN_getRelatedItemColumns_695: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AmuletofFeasting::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_getReplaceDescriptor_1933: out = fn_getReplaceDescriptor(args, argc); return true;
        case SYM_GEN_getRelatedItems_457: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_695: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Food_2604)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofFeasting::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t804 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t805 = (_t804.kind == gd::GdVal::Kind::Arr) ? _t804.arr : nullptr;
        uint32_t _len__t806 = _t805 ? _t805->len : 0u;
        for (uint32_t _t806 = 0; _t806 < _len__t806; ++_t806) {
            gd::GdVal lv_item = _t805->data[_t806];
            (void)([&]() { gd::GdVal _ca[] = {this->f_foodSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_foodSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "foodspeed", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__AmuletofFeasting(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__AmuletofFeasting>(&ctx); }
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
        case SYM_GEN_bonusBlock_1948: out = this->f_bonusBlock; return true;
        case SYM_GEN_cold_1949: out = this->f_cold; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__WisdomPuppy::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusBlock_1948: this->f_bonusBlock = val; return true;
        case SYM_GEN_cold_1949: this->f_cold = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__WisdomPuppy::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__WisdomPuppy::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__WisdomPuppy::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__WisdomPuppy::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__WisdomPuppy::call_method(gd_ctx, SYM_GEN_onPrepare_121, nullptr, 0, _out); return _out; })();
    this->f_bonusBlock = gd::GdVal::from_int(0LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_202, nullptr, 0), this->f_bonusBlock)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_cold}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseCold_350, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    this->f_bonusBlock = gd::gd_add(gd_ctx, this->f_bonusBlock, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__WisdomPuppy::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_cold = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy>(&ctx); }
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
        case SYM_GEN_affectedItem_1983: out = this->f_affectedItem; return true;
        case SYM_GEN_cdAdvance_1984: out = this->f_cdAdvance; return true;
        case SYM_GEN_penaltyFactor_1985: out = this->f_penaltyFactor; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Cube::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedItem_1983: this->f_affectedItem = val; return true;
        case SYM_GEN_cdAdvance_1984: this->f_cdAdvance = val; return true;
        case SYM_GEN_penaltyFactor_1985: this->f_penaltyFactor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Cube::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getDescription_638: return true;
        case SYM_GEN_advanceAffectedItem_1986: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Cube::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getDescription_638: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_advanceAffectedItem_1986: out = fn_advanceAffectedItem(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    gd::GdVal lv_descr = gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getDescription_638, nullptr, 0);
    lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n\n", 2u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Cube_HINT", 9u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_tra_2618, _ca, 1); })()));
    return ([&]() { gd::GdVal _ca[] = {lv_descr, lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameters_639, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cube::fn_advanceAffectedItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(this->f_affectedItem, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_cube_advanced_1393)))))) {
        { gd::GdVal _t807 = gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_cube_advanced_1393); gd::GdVal _t808 = this->f_affectedItem; gd::set_index(gd_ctx, _t807, _t808, gd::GdVal::from_obj(this)); }
        (void)([&]() { gd::GdVal _ca[] = {this->f_cdAdvance}; return gd::call_method(gd_ctx, this->f_affectedItem, SYM_GEN_advanceCooldownSeconds_145, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_cdAdvance, this->f_penaltyFactor)}; return gd::call_method(gd_ctx, this->f_affectedItem, SYM_GEN_advanceCooldownSeconds_145, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cube::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_cdAdvance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cdadvance", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_penaltyFactor = gd::gd_sub(gd::GdVal::from_float(1.0), gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "penalty", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0)));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Cube(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Cube>(&ctx); }
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
        case SYM_GEN_regeneration_2007: out = this->f_regeneration; return true;
        case SYM_GEN_buffsToRemove_2008: out = this->f_buffsToRemove; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BurningBanner::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_regeneration_2007: this->f_regeneration = val; return true;
        case SYM_GEN_buffsToRemove_2008: this->f_buffsToRemove = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BurningBanner::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onItemActivated_934: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BurningBanner::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemActivated_934: out = fn_onItemActivated(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canActivate_89, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningBanner::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t809 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t810 = (_t809.kind == gd::GdVal::Kind::Arr) ? _t809.arr : nullptr;
        uint32_t _len__t811 = _t810 ? _t810->len : 0u;
        for (uint32_t _t811 = 0; _t811 < _len__t811; ++_t811) {
            gd::GdVal lv_item = _t810->data[_t811];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onItemActivated", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_170, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_changeDebuffProtectionChance_1267, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_170, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeBuffProtectionChance_1266, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningBanner::fn_onItemActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Blind_2567), gd::GdVal::from_int(1LL), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_blind", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacksTemporary_200, _ca, 4); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningBanner::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsToRemove}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeRandomBuffs_370, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_regeneration}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningBanner::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_regeneration = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_buffsToRemove = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BurningBanner(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__BurningBanner>(&ctx); }
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
        case SYM_GEN_weaponSpeed_2057: out = this->f_weaponSpeed; return true;
        case SYM_GEN_buffs_1044: out = this->f_buffs; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackKing::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_weaponSpeed_2057: this->f_weaponSpeed = val; return true;
        case SYM_GEN_buffs_1044: this->f_buffs = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackKing::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCapturingEffect_2049: return true;
        case SYM_GEN_onAnyPieceCaptured_2058: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackKing::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCapturingEffect_2049: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_onAnyPieceCaptured_2058: out = fn_onAnyPieceCaptured(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackKing::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackKing::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_board, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_board, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "piece_captured", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onAnyPieceCaptured", 18u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackKing::fn_doCapturingEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__eliminatedPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t812 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1510, nullptr, 0));
        gd::GdArr* _t813 = (_t812.kind == gd::GdVal::Kind::Arr) ? _t812.arr : nullptr;
        uint32_t _len__t814 = _t813 ? _t813->len : 0u;
        for (uint32_t _t814 = 0; _t814 < _len__t814; ++_t814) {
            gd::GdVal lv_item = _t813->data[_t814];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isWeapon_80, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_weaponSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackKing::fn_onAnyPieceCaptured(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__eliminatedPiece = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_capturingPiece, SYM_GEN_pieceColor_2038), gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Chess__BlackKing::get_static_const_or_enum(gd_ctx, SYM_GEN_PieceColor_2053), SYM_GEN_Black_2676))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_capturingPiece, SYM_GEN_numCaptures_2041), gd::GdVal::from_int(1LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_buffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeRandomBuffs_370, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeRandomBuffs_370, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackKing::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_weaponSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_buffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Chess__BlackKing(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Chess__BlackKing>(&ctx); }
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
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_onSold_454: return true;
        case SYM_GEN_getSellPrice_392: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Cog::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onSold_454: out = fn_onSold(args, argc); return true;
        case SYM_GEN_getSellPrice_392: out = fn_getSellPrice(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_isCrafted_796, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cog::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numAffected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numAffected, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_202, nullptr, 0), lv_numAffected)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Cog(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Cog>(&ctx); }
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
        case SYM_GEN_normalTex_2103: out = this->f_normalTex; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DeerTotem::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_normalTex_2103: this->f_normalTex = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DeerTotem::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_preCombatStart_122: return true;
        case SYM_GEN_onBattleRageStarted_1970: return true;
        case SYM_GEN_onBattleRageEnded_1971: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DeerTotem::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_preCombatStart_122: out = fn_preCombatStart(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_1970: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN_onBattleRageEnded_1971: out = fn_onBattleRageEnded(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Nature_2596)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeerTotem::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeDamageResistance_1259, _ca, 1); })();
    gd::GdVal lv_numNatureItems = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_rage", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), lv_numNatureItems)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_addBattleRageDuration_1270, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_started", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageStarted", 19u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_ended", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageEnded", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeerTotem::fn_preCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_preCombatStart_122, nullptr, 0, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeerTotem::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activateCooldown_96, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeerTotem::fn_onBattleRageEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeerTotem::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeerTotem::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
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
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_852), SYM_GEN_Highest_2727);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeerTotem::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DeerTotem(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__DeerTotem>(&ctx); }
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
        case SYM_GEN_ArmState_2140: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__Eat_o_matic_ArmState);
        case SYM_GEN_SLOW_SPEED_2132: return gd::GdVal::from_float(0.2);
        case SYM_GEN_FAST_SPEED_2133: return gd::GdVal::from_float(1.0);
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
        case SYM_GEN_affectedFood_2087: out = this->f_affectedFood; return true;
        case SYM_GEN_otherFood_2130: out = this->f_otherFood; return true;
        case SYM_GEN_armTween_2131: out = this->f_armTween; return true;
        case SYM_GEN_armState_2134: out = this->f_armState; return true;
        case SYM_GEN_foodSpeed_1932: out = this->f_foodSpeed; return true;
        case SYM_GEN_chargedSpeed_2135: out = this->f_chargedSpeed; return true;
        case SYM_GEN_otherSpeed_2136: out = this->f_otherSpeed; return true;
        case SYM_GEN_arm_2137: out = this->f_arm; return true;
        case SYM_GEN_armAnimation_2138: out = this->f_armAnimation; return true;
        case SYM_GEN_ArmState_2140: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__Eat_o_matic_ArmState); return true;
        case SYM_GEN_SLOW_SPEED_2132: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_FAST_SPEED_2133: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Eat_o_matic::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedFood_2087: this->f_affectedFood = val; return true;
        case SYM_GEN_otherFood_2130: this->f_otherFood = val; return true;
        case SYM_GEN_armTween_2131: this->f_armTween = val; return true;
        case SYM_GEN_armState_2134: this->f_armState = gd::gd_coerce_int(val); return true;
        case SYM_GEN_foodSpeed_1932: this->f_foodSpeed = val; return true;
        case SYM_GEN_chargedSpeed_2135: this->f_chargedSpeed = val; return true;
        case SYM_GEN_otherSpeed_2136: this->f_otherSpeed = val; return true;
        case SYM_GEN_arm_2137: this->f_arm = val; return true;
        case SYM_GEN_armAnimation_2138: this->f_armAnimation = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Eat_o_matic::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_canAffect_global_1918: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_combatStart_125: return true;
        case SYM_GEN_onChargeReceived_2032: return true;
        case SYM_GEN_onChargeLeft_2033: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_stopArmAni_2139: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Eat_o_matic::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_global_1918: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_combatStart_125: out = fn_combatStart(args, argc); return true;
        case SYM_GEN_onChargeReceived_2032: out = fn_onChargeReceived(args, argc); return true;
        case SYM_GEN_onChargeLeft_2033: out = fn_onChargeLeft(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_stopArmAni_2139: out = fn_stopArmAni(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Food_2604)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Eat_o_matic::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Food_2604)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())))) {
        return gd::GdVal::from_bool(false);
    }
    if (gd::gd_truth(gd::gd_in(lv_item, gd::get_index(gd_ctx, this->f_currentAffectedItems, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580))))) {
        return gd::GdVal::from_bool(false);
    }
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Eat_o_matic::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Eat_o_matic::get_static_const_or_enum(gd_ctx, SYM_GEN_ArmState_2140), SYM_GEN_Off_2728)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    this->f_affectedFood = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_426, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_affectedFood, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_foodSpeed}; return gd::call_method(gd_ctx, this->f_affectedFood, SYM_GEN_addSpeed_271, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, this->f_otherFood, gd::SYM_clear, nullptr, 0);
    {
        gd::GdVal _t815 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1510, nullptr, 0));
        gd::GdArr* _t816 = (_t815.kind == gd::GdVal::Kind::Arr) ? _t815.arr : nullptr;
        uint32_t _len__t817 = _t816 ? _t816->len : 0u;
        for (uint32_t _t817 = 0; _t817 < _len__t817; ++_t817) {
            gd::GdVal lv_item = _t816->data[_t817];
            if (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_global_1918, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, this->f_affectedFood)))) : gd::GdVal::from_bool(false)))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, this->f_otherFood, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Eat_o_matic::fn_combatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_combatStart_125, nullptr, 0, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_armState, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Eat_o_matic::get_static_const_or_enum(gd_ctx, SYM_GEN_ArmState_2140), SYM_GEN_Fast_2729))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Eat_o_matic::get_static_const_or_enum(gd_ctx, SYM_GEN_ArmState_2140), SYM_GEN_Slow_2730)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Eat_o_matic::fn_onChargeReceived(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_numCharges, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Eat_o_matic::get_static_const_or_enum(gd_ctx, SYM_GEN_ArmState_2140), SYM_GEN_Fast_2729)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_affectedFood, gd::GdVal::null())))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(this->f_chargedSpeed, this->f_foodSpeed)}; return gd::call_method(gd_ctx, this->f_affectedFood, SYM_GEN_addSpeed_271, _ca, 1); })();
        }
        {
            gd::GdVal _t818 = gd::gd_iter_seq(gd_ctx.arena, this->f_otherFood);
            gd::GdArr* _t819 = (_t818.kind == gd::GdVal::Kind::Arr) ? _t818.arr : nullptr;
            uint32_t _len__t820 = _t819 ? _t819->len : 0u;
            for (uint32_t _t820 = 0; _t820 < _len__t820; ++_t820) {
                gd::GdVal lv_food = _t819->data[_t820];
                (void)([&]() { gd::GdVal _ca[] = {this->f_otherSpeed}; return gd::call_method(gd_ctx, lv_food, SYM_GEN_addSpeed_271, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Eat_o_matic::fn_onChargeLeft(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_numCharges, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Eat_o_matic::get_static_const_or_enum(gd_ctx, SYM_GEN_ArmState_2140), SYM_GEN_Slow_2730)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_affectedFood, gd::GdVal::null())))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(this->f_chargedSpeed, this->f_foodSpeed)}; return gd::call_method(gd_ctx, this->f_affectedFood, SYM_GEN_reduceSpeed_272, _ca, 1); })();
        }
        {
            gd::GdVal _t821 = gd::gd_iter_seq(gd_ctx.arena, this->f_otherFood);
            gd::GdArr* _t822 = (_t821.kind == gd::GdVal::Kind::Arr) ? _t821.arr : nullptr;
            uint32_t _len__t823 = _t822 ? _t822->len : 0u;
            for (uint32_t _t823 = 0; _t823 < _len__t823; ++_t823) {
                gd::GdVal lv_food = _t822->data[_t823];
                (void)([&]() { gd::GdVal _ca[] = {this->f_otherSpeed}; return gd::call_method(gd_ctx, lv_food, SYM_GEN_reduceSpeed_272, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Eat_o_matic::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Eat_o_matic::get_static_const_or_enum(gd_ctx, SYM_GEN_ArmState_2140), SYM_GEN_Off_2728)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Eat_o_matic::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Eat_o_matic::get_static_const_or_enum(gd_ctx, SYM_GEN_ArmState_2140), SYM_GEN_Off_2728)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
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
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_armState, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Eat_o_matic::get_static_const_or_enum(gd_ctx, SYM_GEN_ArmState_2140), SYM_GEN_Off_2728))))) {
    }
    else {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_armState, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Eat_o_matic::get_static_const_or_enum(gd_ctx, SYM_GEN_ArmState_2140), SYM_GEN_Slow_2730))))) {
        }
        else {
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Eat_o_matic::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_foodSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_chargedSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed2", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_otherSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed3", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Eat_o_matic(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Eat_o_matic>(&ctx); }
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
        case SYM_GEN_maxHealthAmp_2160: out = this->f_maxHealthAmp; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__FalseLife::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_maxHealthAmp_2160: this->f_maxHealthAmp = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__FalseLife::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_canAffect_global_1918: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onOverheal_2161: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__FalseLife::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_global_1918: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onOverheal_2161: out = fn_onOverheal(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Dark_2600)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FalseLife::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), SYM_GEN_hasParam_1485, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FalseLife::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_maxHealthAmp}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeMaxHealthGain_1257, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_overhealed", 20u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOverheal", 10u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FalseLife::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_healAmount = gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal_dark", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0)));
    (void)([&]() { gd::GdVal _ca[] = {lv_healAmount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FalseLife::fn_onOverheal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_overheal = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_healEvent = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_overheal, lv_healEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_315, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FalseLife::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_maxHealthAmp = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healthamp", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__FalseLife(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__FalseLife>(&ctx); }
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
        case SYM_GEN_blockedDamageRes_1843: out = this->f_blockedDamageRes; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Shield::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockedDamageRes_1843: this->f_blockedDamageRes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Shield::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepare_120: return true;
        case SYM_GEN_getDamageBlock_1844: return true;
        case SYM_GEN_beforeBlock_1845: return true;
        case SYM_GEN_afterBlock_1846: return true;
        case SYM_GEN_canBlockDamageRes_1847: return true;
        case SYM_GEN_preTakeDamage_1848: return true;
        case SYM_GEN_onCharacterAttacked_1849: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Shield::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepare_120: out = fn_prepare(args, argc); return true;
        case SYM_GEN_getDamageBlock_1844: out = fn_getDamageBlock(args, argc); return true;
        case SYM_GEN_beforeBlock_1845: out = fn_beforeBlock(args, argc); return true;
        case SYM_GEN_afterBlock_1846: out = fn_afterBlock(args, argc); return true;
        case SYM_GEN_canBlockDamageRes_1847: out = fn_canBlockDamageRes(args, argc); return true;
        case SYM_GEN_preTakeDamage_1848: out = fn_preTakeDamage(args, argc); return true;
        case SYM_GEN_onCharacterAttacked_1849: out = fn_onCharacterAttacked(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pre_take_damage", 15u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "preTakeDamage", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_attacked", 18u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onCharacterAttacked", 19u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_prepare_120, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Shield::fn_getDamageBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damblock", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Shield::fn_beforeBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getDamageBlock_1844, nullptr, 0), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, this->f_blockedDamageRes, SYM_GEN_applyDamageReduction_1433, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Shield::fn_afterBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Shield::fn_canBlockDamageRes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_triggerOnMeleeAttacked_1436, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Shield::fn_preTakeDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_damageRes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canBlockDamageRes_1847, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        this->f_blockedDamageRes = lv_damageRes;
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_beforeBlock_1845, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Shield::fn_onCharacterAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_blockedDamageRes, lv_damageRes)))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_afterBlock_1846, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blocked", 7u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {this->f_blockedDamageRes}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1375), SYM_GEN_emitSignal_1499, _ca, 3); })();
        this->f_blockedDamageRes = gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Shield::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Shield(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Shield>(&ctx); }
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
        case SYM_GEN_allPotions_2206: out = this->f_allPotions; return true;
        case SYM_GEN_boostedPotions_2207: out = this->f_boostedPotions; return true;
        case SYM_GEN_potionSpeed_2164: out = this->f_potionSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__HeavyDrinking::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_allPotions_2206: this->f_allPotions = val; return true;
        case SYM_GEN_boostedPotions_2207: this->f_boostedPotions = val; return true;
        case SYM_GEN_potionSpeed_2164: this->f_potionSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__HeavyDrinking::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getData_634: return true;
        case SYM_GEN_setData_635: return true;
        case SYM_GEN_onBought_453: return true;
        case SYM_GEN_isAffectingDistinct_252: return true;
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_canAffect_global_1918: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onItemRoll_1922: return true;
        case SYM_GEN_onItemRolled_1923: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__HeavyDrinking::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getData_634: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_635: out = fn_setData(args, argc); return true;
        case SYM_GEN_onBought_453: out = fn_onBought(args, argc); return true;
        case SYM_GEN_isAffectingDistinct_252: out = fn_isAffectingDistinct(args, argc); return true;
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_global_1918: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onItemRoll_1922: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_1923: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_data, gd::GdVal::null())))) {
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
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580));
    return gd::GdVal::from_bool(gd::gd_eq(lv_color, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeavyDrinking::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Potion_2652)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeavyDrinking::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Potion_2652)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeavyDrinking::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumDistinctAffectedItems_428, nullptr, 0), this->f_potionSpeed)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    (void)gd::call_method(gd_ctx, this->f_allPotions, gd::SYM_clear, nullptr, 0);
    {
        gd::GdVal _t824 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1510, nullptr, 0));
        gd::GdArr* _t825 = (_t824.kind == gd::GdVal::Kind::Arr) ? _t824.arr : nullptr;
        uint32_t _len__t826 = _t825 ? _t825->len : 0u;
        for (uint32_t _t826 = 0; _t826 < _len__t826; ++_t826) {
            gd::GdVal lv_item = _t825->data[_t826];
            if (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Potion_2652)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::from_obj(this))))) : gd::GdVal::from_bool(false)))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, this->f_allPotions, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeavyDrinking::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, this->f_allPotions, gd::SYM_empty, nullptr, 0))))) {
        gd::GdVal lv_potionToTrigger = ([&]() { gd::GdVal _ca[] = {this->f_allPotions}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_pickRandomElement_1648, _ca, 1); })();
        (void)gd::call_method(gd_ctx, lv_potionToTrigger, SYM_GEN_triggerPotion_1754, nullptr, 0);
        (void)gd::call_method(gd_ctx, lv_potionToTrigger, SYM_GEN_miniActivate_468, nullptr, 0);
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
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
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Potion_2652)}; return gd::call_method(gd_ctx, lv_descr, SYM_GEN_hasType_77, _ca, 1); })())) {
        this->f_boostedPotions = gd::gd_sub(this->f_boostedPotions, gd::GdVal::from_int(1LL));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeavyDrinking::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_potionSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__HeavyDrinking(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__HeavyDrinking>(&ctx); }
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
        case SYM_GEN_numActivations_1808: out = this->f_numActivations; return true;
        case SYM_GEN_manaCost_1719: out = this->f_manaCost; return true;
        case SYM_GEN_permDamBonus_993: out = this->f_permDamBonus; return true;
        case SYM_GEN_speedBonus_1781: out = this->f_speedBonus; return true;
        case SYM_GEN_maxActivations_1809: out = this->f_maxActivations; return true;
        case SYM_GEN_luckRemoval_2234: out = this->f_luckRemoval; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__JynxStaff::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numActivations_1808: this->f_numActivations = gd::gd_coerce_int(val); return true;
        case SYM_GEN_manaCost_1719: this->f_manaCost = val; return true;
        case SYM_GEN_permDamBonus_993: this->f_permDamBonus = val; return true;
        case SYM_GEN_speedBonus_1781: this->f_speedBonus = val; return true;
        case SYM_GEN_maxActivations_1809: this->f_maxActivations = val; return true;
        case SYM_GEN_luckRemoval_2234: this->f_luckRemoval = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__JynxStaff::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__JynxStaff::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_93, nullptr, 0);
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
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_331, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_event, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_permDamBonus}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_159, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_numActivations, this->f_maxActivations)))) {
            {
                gd::GdVal _t827 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
                gd::GdArr* _t828 = (_t827.kind == gd::GdVal::Kind::Arr) ? _t827.arr : nullptr;
                uint32_t _len__t829 = _t828 ? _t828->len : 0u;
                for (uint32_t _t829 = 0; _t829 < _len__t829; ++_t829) {
                    gd::GdVal lv_item = _t828->data[_t829];
                    (void)([&]() { gd::GdVal _ca[] = {this->f_speedBonus}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
                }
            }
            this->f_numActivations = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numActivations, gd::GdVal::from_int(1LL)));
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_getLucky_1217, nullptr, 0), gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_luckRemoval}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeLucky_347, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__JynxStaff::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_manaCost = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "manat", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_permDamBonus = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_speedBonus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_maxActivations = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "max", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_luckRemoval = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__JynxStaff(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__JynxStaff>(&ctx); }
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
        case SYM_GEN_sales_2260: out = this->f_sales; return true;
        case SYM_GEN_goldThreshold1_2261: out = this->f_goldThreshold1; return true;
        case SYM_GEN_goldThreshold2_2262: out = this->f_goldThreshold2; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__LuckyCat::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_sales_2260: this->f_sales = val; return true;
        case SYM_GEN_goldThreshold1_2261: this->f_goldThreshold1 = val; return true;
        case SYM_GEN_goldThreshold2_2262: this->f_goldThreshold2 = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__LuckyCat::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_getCounterValue_2255: return true;
        case SYM_GEN_condition1Fulfilled_2263: return true;
        case SYM_GEN_condition2Fulfilled_2264: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_getDescription_638: return true;
        case SYM_GEN_updatePaws_2265: return true;
        case SYM_GEN_onAffectedItemAdded_433: return true;
        case SYM_GEN_onAffectedItemRemoved_434: return true;
        case SYM_GEN_onAddToInventory_417: return true;
        case SYM_GEN_onRemoveFromInventory_416: return true;
        case SYM_GEN_canAffect_global_1918: return true;
        case SYM_GEN_onSaleRoll_1997: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__LuckyCat::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_getCounterValue_2255: out = fn_getCounterValue(args, argc); return true;
        case SYM_GEN_condition1Fulfilled_2263: out = fn_condition1Fulfilled(args, argc); return true;
        case SYM_GEN_condition2Fulfilled_2264: out = fn_condition2Fulfilled(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_getDescription_638: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_updatePaws_2265: out = fn_updatePaws(args, argc); return true;
        case SYM_GEN_onAffectedItemAdded_433: out = fn_onAffectedItemAdded(args, argc); return true;
        case SYM_GEN_onAffectedItemRemoved_434: out = fn_onAffectedItemRemoved(args, argc); return true;
        case SYM_GEN_onAddToInventory_417: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_416: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_canAffect_global_1918: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN_onSaleRoll_1997: out = fn_onSaleRoll(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedGoldValue_492, nullptr, 0);
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
    gd::GdVal lv_gold = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue_2255, nullptr, 0);
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_gold}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_condition1Fulfilled_2263, _ca, 1); })())) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeCritResistance_1153, _ca, 1); })();
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_gold}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_condition2Fulfilled_2264, _ca, 1); })())) {
            gd::GdVal lv_bonusSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
            {
                gd::GdVal _t830 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1510, nullptr, 0));
                gd::GdArr* _t831 = (_t830.kind == gd::GdVal::Kind::Arr) ? _t830.arr : nullptr;
                uint32_t _len__t832 = _t831 ? _t831->len : 0u;
                for (uint32_t _t832 = 0; _t832 < _len__t832; ++_t832) {
                    gd::GdVal lv_item = _t831->data[_t832];
                    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_global_1918, _ca, 1); })())) {
                        (void)([&]() { gd::GdVal _ca[] = {lv_bonusSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
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
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_638, _ca, 1, _out); return _out; })();
    gd::GdVal lv_colors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_inactiveColor_2731), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_inactiveColor_2731)}));
    gd::GdVal lv_gold = gd::GdVal::from_int(0);
    if (gd::gd_truth(this->f_placed)) {
        lv_gold = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue_2255, nullptr, 0));
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_gold}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_condition1Fulfilled_2263, _ca, 1); })())) {
            { gd::GdVal _t833 = lv_colors; gd::GdVal _t834 = gd::GdVal::from_int(0LL); gd::set_index(gd_ctx, _t833, _t834, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_modifiedColor_2724)); }
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_gold}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_condition2Fulfilled_2264, _ca, 1); })())) {
                { gd::GdVal _t835 = lv_colors; gd::GdVal _t836 = gd::GdVal::from_int(1LL); gd::set_index(gd_ctx, _t835, _t836, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_modifiedColor_2724)); }
            }
        }
    }
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, lv_colors, gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModeDescription_641, _ca, 4); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn_updatePaws(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_gold = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue_2255, nullptr, 0);
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_gold}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_condition1Fulfilled_2263, _ca, 1); })())) {
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_gold}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_condition2Fulfilled_2264, _ca, 1); })())) {
        }
        else {
        }
    }
    else {
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadowTexture_785, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn_onAffectedItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updatePaws_2265, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn_onAffectedItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updatePaws_2265, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updatePaws_2265, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadowTexture_785, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, lv_item, SYM_GEN_getRarity_234, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Rarity_858), SYM_GEN_Godly_2677)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_93, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn_onSaleRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LuckyCat::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_sales = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "sales", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_goldThreshold1 = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gold1", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_goldThreshold2 = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gold2", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__LuckyCat(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__LuckyCat>(&ctx); }
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
        case SYM_GEN_luckNeeded_1778: out = this->f_luckNeeded; return true;
        case SYM_GEN_numBuffs_1909: out = this->f_numBuffs; return true;
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MissFortune::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_luckNeeded_1778: this->f_luckNeeded = val; return true;
        case SYM_GEN_numBuffs_1909: this->f_numBuffs = val; return true;
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MissFortune::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MissFortune::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__MissFortune::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__MissFortune::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getLucky_1217, nullptr, 0), this->f_luckNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_luckNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useLucky_348, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_numBuffs, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMostBuffs_365, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MissFortune::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_luckNeeded = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_numBuffs = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MissFortune(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__MissFortune>(&ctx); }
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
        case SYM_GEN_usedStacks_1618: out = this->f_usedStacks; return true;
        case SYM_GEN_staminaUsed_1980: out = this->f_staminaUsed; return true;
        case SYM_GEN_stamina_2059: out = this->f_stamina; return true;
        case SYM_GEN_buffRefund_2324: out = this->f_buffRefund; return true;
        case SYM_GEN_staminaRefund_2325: out = this->f_staminaRefund; return true;
        case SYM_GEN_speed_v_2082: out = this->f_speed_v; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PerpetuumMobile::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_usedStacks_1618: this->f_usedStacks = val; return true;
        case SYM_GEN_staminaUsed_1980: this->f_staminaUsed = val; return true;
        case SYM_GEN_stamina_2059: this->f_stamina = val; return true;
        case SYM_GEN_buffRefund_2324: this->f_buffRefund = val; return true;
        case SYM_GEN_staminaRefund_2325: this->f_staminaRefund = val; return true;
        case SYM_GEN_speed_v_2082: this->f_speed_v = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PerpetuumMobile::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_onBuffChanged_1910: return true;
        case SYM_GEN_onStaminaUsed_2309: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PerpetuumMobile::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onBuffChanged_1910: out = fn_onBuffChanged(args, argc); return true;
        case SYM_GEN_onStaminaUsed_2309: out = fn_onStaminaUsed(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Classes_Full_1369), SYM_GEN_Engineer_2684)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isClassItem_246, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PerpetuumMobile::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBuffChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterBuffs_372, _ca, 1); })();
    {
        gd::GdVal _t837 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1357, nullptr, 0));
        gd::GdArr* _t838 = (_t837.kind == gd::GdVal::Kind::Arr) ? _t837.arr : nullptr;
        uint32_t _len__t839 = _t838 ? _t838->len : 0u;
        for (uint32_t _t839 = 0; _t839 < _len__t839; ++_t839) {
            gd::GdVal lv_buff = _t838->data[_t839];
            { gd::GdVal _t840 = this->f_usedStacks; gd::GdVal _t841 = lv_buff; gd::set_index(gd_ctx, _t840, _t841, gd::GdVal::from_float(0.0)); }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_used_stamina", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onStaminaUsed", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    this->f_staminaUsed = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_speed_v, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PerpetuumMobile::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_stamina, gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxStaminaTemporary_314, _ca, 3); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PerpetuumMobile::fn_onBuffChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "used", 4u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_event, SYM_GEN_getParam_1482, _ca, 2); })())) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv_used = gd::gd_neg(lv_amount);
        gd::GdVal lv_buffType = gd::call_method(gd_ctx, lv_event, SYM_GEN_getType_1479, nullptr, 0);
        { gd::GdVal _t842 = this->f_usedStacks; gd::GdVal _t843 = lv_buffType; gd::set_index(gd_ctx, _t842, _t843, gd::gd_add(gd_ctx, gd::get_index(gd_ctx, _t842, _t843), lv_used)); }
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
        gd::GdVal _t844 = gd::gd_iter_seq(gd_ctx.arena, this->f_usedStacks);
        gd::GdArr* _t845 = (_t844.kind == gd::GdVal::Kind::Arr) ? _t844.arr : nullptr;
        uint32_t _len__t846 = _t845 ? _t845->len : 0u;
        for (uint32_t _t846 = 0; _t846 < _len__t846; ++_t846) {
            gd::GdVal lv_buffType = _t845->data[_t846];
            gd::GdVal lv_toRefund = gd::gd_coerce_int(gd::gd_round(gd::gd_mul(gd::get_index(gd_ctx, this->f_usedStacks, lv_buffType), this->f_buffRefund)));
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_toRefund, gd::GdVal::from_int(0LL))))) {
                { gd::GdVal _t847 = this->f_usedStacks; gd::GdVal _t848 = lv_buffType; gd::set_index(gd_ctx, _t847, _t848, gd::gd_sub(gd::get_index(gd_ctx, _t847, _t848), lv_toRefund)); }
                (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), lv_buffType, lv_toRefund}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_199, _ca, 3); })();
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_staminaUsed, this->f_staminaRefund)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_316, _ca, 1); })();
    this->f_staminaUsed = gd::GdVal::from_int(0LL);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PerpetuumMobile::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_buffRefund = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "refund_buffs", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_staminaRefund = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "refund_stamina", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_speed_v = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PerpetuumMobile(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__PerpetuumMobile>(&ctx); }
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
        case SYM_GEN_affectedTypes_2348: out = this->f_affectedTypes; return true;
        case SYM_GEN_holyDam_2349: out = this->f_holyDam; return true;
        case SYM_GEN_debuffs_2054: out = this->f_debuffs; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PrismaticSword::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedTypes_2348: this->f_affectedTypes = val; return true;
        case SYM_GEN_holyDam_2349: this->f_holyDam = val; return true;
        case SYM_GEN_debuffs_2054: this->f_debuffs = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PrismaticSword::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN_onPreDealDamage_late_902: return true;
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_getDescription_638: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PrismaticSword::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onPreDealDamage_late_902: out = fn_onPreDealDamage_late(args, argc); return true;
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_getDescription_638: out = fn_getDescription(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PrismaticSword::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PrismaticSword::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_affectedTypes = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countTypes_493, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_index(gd_ctx, this->f_affectedTypes, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Magic_2721)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(gd::get_index(gd_ctx, this->f_affectedTypes, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Magic_2721)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })()), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PrismaticSword::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_holyDam, gd::get_index(gd_ctx, this->f_affectedTypes, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_159, _ca, 1); })();
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseChance2_167, nullptr, 0), gd::get_index(gd_ctx, this->f_affectedTypes, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Dark_2600)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_debuffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictRandomDebuffs_355, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PrismaticSword::fn_onPreDealDamage_late(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_ceil(gd::gd_mul(gd::gd_div(gd_ctx, gd::gd_mul(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1425), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lifesteal", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()), gd::GdVal::from_float(100.0)), gd::get_index(gd_ctx, this->f_affectedTypes, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Vampiric_2597))))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PrismaticSword::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Vampiric_2597)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Magic_2721)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Dark_2600)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PrismaticSword::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_getDescription_638, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_placed)))) {
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$n_magic", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$n_vampiric", 11u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$n_holy", 7u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$n_dark", 7u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        return lv_descr;
    }
    gd::GdVal lv_typesDict = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countTypes_493, _ca, 1); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n_magic", 7u)), gd::get_index(gd_ctx, lv_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Magic_2721))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_450, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n_vampiric", 10u)), gd::get_index(gd_ctx, lv_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Vampiric_2597))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_450, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n_holy", 6u)), gd::get_index(gd_ctx, lv_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_450, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n_dark", 6u)), gd::get_index(gd_ctx, lv_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Dark_2600))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_450, _ca, 3); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PrismaticSword::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_holyDam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_debuffs = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "debuffs", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PrismaticSword(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__PrismaticSword>(&ctx); }
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
        case SYM_GEN_usedBuffs_2173: out = this->f_usedBuffs; return true;
        case SYM_GEN_buffsNeeded_1989: out = this->f_buffsNeeded; return true;
        case SYM_GEN_numPotions_2357: out = this->f_numPotions; return true;
        case SYM_GEN_buffsPerStaff_2358: out = this->f_buffsPerStaff; return true;
        case SYM_GEN_manaPerBook_2359: out = this->f_manaPerBook; return true;
        case SYM_GEN_staminaPerBook_2360: out = this->f_staminaPerBook; return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__RainbowPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_usedBuffs_2173: this->f_usedBuffs = gd::gd_coerce_int(val); return true;
        case SYM_GEN_buffsNeeded_1989: this->f_buffsNeeded = val; return true;
        case SYM_GEN_numPotions_2357: this->f_numPotions = val; return true;
        case SYM_GEN_buffsPerStaff_2358: this->f_buffsPerStaff = val; return true;
        case SYM_GEN_manaPerBook_2359: this->f_manaPerBook = val; return true;
        case SYM_GEN_staminaPerBook_2360: this->f_staminaPerBook = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__RainbowPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_global_1918: return true;
        case SYM_GEN_getAffectedCellsAfterRotate_primary_408: return true;
        case SYM_GEN_isAffectingDistinct_252: return true;
        case SYM_GEN_canAffect_secondary_285: return true;
        case SYM_GEN_canAffect_tertiary_286: return true;
        case SYM_GEN_onTriggerPotion_1753: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_onBuffsChanged_1991: return true;
        case SYM_GEN_getGatedDescriptor_952: return true;
        case SYM_GEN_getStarPosition_1757: return true;
        case SYM_GEN_getRelatedItems_457: return true;
        case SYM_GEN_getRelatedItemColumns_695: return true;
        case SYM_GEN_getRelatedItemHeight_696: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__RainbowPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_global_1918: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN_getAffectedCellsAfterRotate_primary_408: out = fn_getAffectedCellsAfterRotate_primary(args, argc); return true;
        case SYM_GEN_isAffectingDistinct_252: out = fn_isAffectingDistinct(args, argc); return true;
        case SYM_GEN_canAffect_secondary_285: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_canAffect_tertiary_286: out = fn_canAffect_tertiary(args, argc); return true;
        case SYM_GEN_onTriggerPotion_1753: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onBuffsChanged_1991: out = fn_onBuffsChanged(args, argc); return true;
        case SYM_GEN_getGatedDescriptor_952: out = fn_getGatedDescriptor(args, argc); return true;
        case SYM_GEN_getStarPosition_1757: out = fn_getStarPosition(args, argc); return true;
        case SYM_GEN_getRelatedItems_457: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_695: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_696: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Potion_2652)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::from_obj(this))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_getAffectedCellsAfterRotate_primary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rotatedCells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_faceDirection, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_LEFT))))) {
        return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::gd_add(gd_ctx, gd::get_index(gd_ctx, lv_rotatedCells, gd::GdVal::from_int(1LL)), gd::GdVal::from_vec2(0.0, -1.0))}));
    }
    else {
        return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::gd_add(gd_ctx, gd::get_index(gd_ctx, lv_rotatedCells, gd::GdVal::from_int(0LL)), gd::GdVal::from_vec2(0.0, -1.0))}));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_isAffectingDistinct(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580));
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_color, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Secondary_2582)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_color, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Tertiary_2583))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Book_2732)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_canAffect_tertiary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Tag_854), SYM_GEN_Staff_2733)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasTag_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_allPotions = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t849 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1510, nullptr, 0));
        gd::GdArr* _t850 = (_t849.kind == gd::GdVal::Kind::Arr) ? _t849.arr : nullptr;
        uint32_t _len__t851 = _t850 ? _t850->len : 0u;
        for (uint32_t _t851 = 0; _t851 < _len__t851; ++_t851) {
            gd::GdVal lv_item = _t850->data[_t851];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_global_1918, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, lv_allPotions, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_allPotions, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Exclusive/RainbowPotion.gd:37", 29u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), SYM_GEN_shuffleEngine_1649, _ca, 2); })();
    gd::GdVal lv_potionsToTrigger = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t852 = gd::gd_iter_seq(gd_ctx.arena, lv_allPotions);
        gd::GdArr* _t853 = (_t852.kind == gd::GdVal::Kind::Arr) ? _t852.arr : nullptr;
        uint32_t _len__t854 = _t853 ? _t853->len : 0u;
        for (uint32_t _t854 = 0; _t854 < _len__t854; ++_t854) {
            gd::GdVal lv_potion = _t853->data[_t854];
            gd::GdVal lv_typeExists = gd::GdVal::from_bool(false);
            {
                gd::GdVal _t855 = gd::gd_iter_seq(gd_ctx.arena, lv_potionsToTrigger);
                gd::GdArr* _t856 = (_t855.kind == gd::GdVal::Kind::Arr) ? _t855.arr : nullptr;
                uint32_t _len__t857 = _t856 ? _t856->len : 0u;
                for (uint32_t _t857 = 0; _t857 < _len__t857; ++_t857) {
                    gd::GdVal lv_triggeredPotion = _t856->data[_t857];
                    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, lv_triggeredPotion, SYM_GEN_descriptor_2)}; return gd::call_method(gd_ctx, lv_potion, SYM_GEN_isA_243, _ca, 1); })())) {
                        lv_typeExists = gd::GdVal::from_bool(true);
                        break;
                    }
                }
            }
            if (gd::gd_truth(lv_typeExists)) {
                continue;
            }
            (void)([&]() { gd::GdVal _ca[] = {lv_potion}; return gd::call_method(gd_ctx, lv_potionsToTrigger, gd::SYM_push_back, _ca, 1); })();
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, lv_potionsToTrigger, gd::SYM_size, nullptr, 0), this->f_numPotions)))) {
                break;
            }
        }
    }
    {
        gd::GdVal _t858 = gd::gd_iter_seq(gd_ctx.arena, lv_potionsToTrigger);
        gd::GdArr* _t859 = (_t858.kind == gd::GdVal::Kind::Arr) ? _t858.arr : nullptr;
        uint32_t _len__t860 = _t859 ? _t859->len : 0u;
        for (uint32_t _t860 = 0; _t860 < _len__t860; ++_t860) {
            gd::GdVal lv_potion = _t859->data[_t860];
            (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, lv_potion, SYM_GEN_triggerPotion_1754, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBuffsChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterBuffs_372, _ca, 1); })();
    this->f_usedBuffs = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_books = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Secondary_2582)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumDistinctAffectedItems_428, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_books, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_books, this->f_manaPerBook)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_books, this->f_staminaPerBook)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxStaminaTemporary_314, _ca, 1); })();
    }
    gd::GdVal lv_staffs = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Tertiary_2583)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumDistinctAffectedItems_428, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_staffs, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_buffsPerStaff, lv_staffs)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_367, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false), gd::GdVal::from_bool(false), gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowPotion::fn_onBuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_919, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "used", 4u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_event, SYM_GEN_getParam_1482, _ca, 2); })())) : gd::GdVal::from_bool(false)))) {
        this->f_usedBuffs = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_usedBuffs, gd::gd_coerce_int(gd::gd_abs(lv_amount))));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_usedBuffs, this->f_buffsNeeded)))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1752, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Potion::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_buffsNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffst", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_numPotions = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "potions", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_buffsPerStaff = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_manaPerBook = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_staminaPerBook = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__RainbowPotion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__RainbowPotion>(&ctx); }
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
        case SYM_GEN_blindingLightTimer_1814: out = this->f_blindingLightTimer; return true;
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        case SYM_GEN_regenNeeded_938: out = this->f_regenNeeded; return true;
        case SYM_GEN_blind_1815: out = this->f_blind; return true;
        case SYM_GEN_damPerBlind_1816: out = this->f_damPerBlind; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Lightsaber::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blindingLightTimer_1814: this->f_blindingLightTimer = val; return true;
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        case SYM_GEN_regenNeeded_938: this->f_regenNeeded = val; return true;
        case SYM_GEN_blind_1815: this->f_blind = val; return true;
        case SYM_GEN_damPerBlind_1816: this->f_damPerBlind = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Lightsaber::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_inflict_1817: return true;
        case SYM_GEN_onRegenChanged_1795: return true;
        case SYM_GEN_onOpponentBlindChanged_1818: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case SYM_GEN_onBlindingLightTimeout_1819: return true;
        case SYM_GEN_onBlindingLightEnded_1820: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Lightsaber::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_inflict_1817: out = fn_inflict(args, argc); return true;
        case SYM_GEN_onRegenChanged_1795: out = fn_onRegenChanged(args, argc); return true;
        case SYM_GEN_onOpponentBlindChanged_1818: out = fn_onOpponentBlindChanged(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onBlindingLightTimeout_1819: out = fn_onBlindingLightTimeout(args, argc); return true;
        case SYM_GEN_onBlindingLightEnded_1820: out = fn_onBlindingLightEnded(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Lightsaber::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Lightsaber::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blinding_light_ended", 20u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBlindingLightEnded", 20u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_blind_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentBlindChanged", 22u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_regeneration_changed", 30u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onRegenChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Lightsaber::fn_inflict(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_duration = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Blind_2567), this->f_blind, lv_duration, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacksTemporary_200, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Lightsaber::fn_onRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_blindingLightActive_1073)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getRegeneration_1213, nullptr, 0), this->f_regenNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_startBlindingLight_1177, nullptr, 0);
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_regenNeeded, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_344, _ca, 2); })();
        gd::GdVal lv_duration = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_blind", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_duration, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflict_1817, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_duration}; return gd::call_method(gd_ctx, this->f_blindingLightTimer, SYM_GEN_start_1683, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Lightsaber::fn_onOpponentBlindChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_damPerBlind, lv_amount)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_160, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Lightsaber::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_blindingLightTimer, SYM_GEN_stop_1684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Lightsaber::fn_onBlindingLightTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "endBlindingLight", 16u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_callNextFrame_1701, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Lightsaber::fn_onBlindingLightEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onRegenChanged_1795, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Lightsaber::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_blindingLightTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BlindingLightTimer", 18u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBlindingLightTimeout", 22u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_133, _ca, 3); })();
    this->f_regenNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regent", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_blind = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blind", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_damPerBlind = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam_blind", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Lightsaber(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Lightsaber>(&ctx); }
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
        case SYM_GEN_blockAcc_1850: out = this->f_blockAcc; return true;
        case SYM_GEN_boostedGarlic_2409: out = this->f_boostedGarlic; return true;
        case SYM_GEN_garlicDescriptor_2410: out = this->f_garlicDescriptor; return true;
        case SYM_GEN_garlicBlockBonus_2411: out = this->f_garlicBlockBonus; return true;
        case SYM_GEN_blockForPoison_2412: out = this->f_blockForPoison; return true;
        case SYM_GEN_poisonForBlock_2413: out = this->f_poisonForBlock; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SmellyBarrier::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockAcc_1850: this->f_blockAcc = gd::gd_coerce_int(val); return true;
        case SYM_GEN_boostedGarlic_2409: this->f_boostedGarlic = val; return true;
        case SYM_GEN_garlicDescriptor_2410: this->f_garlicDescriptor = val; return true;
        case SYM_GEN_garlicBlockBonus_2411: this->f_garlicBlockBonus = val; return true;
        case SYM_GEN_blockForPoison_2412: this->f_blockForPoison = val; return true;
        case SYM_GEN_poisonForBlock_2413: this->f_poisonForBlock = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SmellyBarrier::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onBought_453: return true;
        case SYM_GEN_getData_634: return true;
        case SYM_GEN_setData_635: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onItemGaveBlock_1852: return true;
        case SYM_GEN_onItemRoll_1922: return true;
        case SYM_GEN_onItemRolled_1923: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SmellyBarrier::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onBought_453: out = fn_onBought(args, argc); return true;
        case SYM_GEN_getData_634: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_635: out = fn_setData(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemGaveBlock_1852: out = fn_onItemGaveBlock(args, argc); return true;
        case SYM_GEN_onItemRoll_1922: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_1923: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_garlicDescriptor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_243, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canBlock_289, nullptr, 0))));
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
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_data, gd::GdVal::null())))) {
        this->f_boostedGarlic = lv_data;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SmellyBarrier::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_blockAcc = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    {
        gd::GdVal _t861 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t862 = (_t861.kind == gd::GdVal::Kind::Arr) ? _t861.arr : nullptr;
        uint32_t _len__t863 = _t862 ? _t862->len : 0u;
        for (uint32_t _t863 = 0; _t863 < _len__t863; ++_t863) {
            gd::GdVal lv_item = _t862->data[_t863];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_garlicDescriptor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_243, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_garlicBlockBonus}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusBlock_1783, _ca, 1); })();
            }
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canBlock_289, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gave_block", 10u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onItemGaveBlock", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
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
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_poison, this->f_poisonForBlock), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_209, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
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
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_descr, this->f_garlicDescriptor)))) {
        this->f_boostedGarlic = gd::gd_sub(this->f_boostedGarlic, gd::GdVal::from_int(1LL));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SmellyBarrier::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_garlicDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Garlic", 6u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })();
    this->f_garlicBlockBonus = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blockbonus", 10u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_blockForPoison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blockt", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_poisonForBlock = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "poison", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SmellyBarrier(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SmellyBarrier>(&ctx); }
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
        case SYM_GEN_spikes_894: out = this->f_spikes; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SpikedCollar::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikes_894: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SpikedCollar::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onBattleRageStarted_1970: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SpikedCollar::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_1970: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SpikedCollar::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SpikedCollar::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_started", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageStarted", 19u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_rage", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_addBattleRageDuration_1270, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpikedCollar::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_spikes, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_207, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpikedCollar::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SpikedCollar(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SpikedCollar>(&ctx); }
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
        case SYM_GEN_hasActivated_1810: out = this->f_hasActivated; return true;
        case SYM_GEN_luck_893: out = this->f_luck; return true;
        case SYM_GEN_empower_994: out = this->f_empower; return true;
        case SYM_GEN_damReduction_1777: out = this->f_damReduction; return true;
        case SYM_GEN_healthThreshold_1758: out = this->f_healthThreshold; return true;
        case SYM_GEN_buffTimer_1723: out = this->f_buffTimer; return true;
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__StoneShoes::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hasActivated_1810: this->f_hasActivated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_luck_893: this->f_luck = val; return true;
        case SYM_GEN_empower_994: this->f_empower = val; return true;
        case SYM_GEN_damReduction_1777: this->f_damReduction = val; return true;
        case SYM_GEN_healthThreshold_1758: this->f_healthThreshold = val; return true;
        case SYM_GEN_buffTimer_1723: this->f_buffTimer = val; return true;
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__StoneShoes::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onDamaged_1759: return true;
        case SYM_GEN_onBuffTimeout_1926: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__StoneShoes::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1759: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN_onBuffTimeout_1926: out = fn_onBuffTimeout(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__StoneShoes::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneShoes::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDamaged", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneShoes::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(this->f_hasActivated)) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getRelativeHealth_300, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_202, nullptr, 0), gd::GdVal::from_bool(true), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1683, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_851), SYM_GEN_Ranged_2670), gd::gd_neg(this->f_damReduction)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_changeTypedDamageFactor_1260, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_changeEffectDamageFactor_1261, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_379, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneShoes::fn_onBuffTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_851), SYM_GEN_Ranged_2670), this->f_damReduction}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_changeTypedDamageFactor_1260, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_changeEffectDamageFactor_1261, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneShoes::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneShoes::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
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
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_852), SYM_GEN_High_2601), gd::GdVal::from_int(3LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneShoes::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_luck = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_empower = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_damReduction = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damreduction", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BuffTimer", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBuffTimeout", 13u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_133, _ca, 3); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__StoneShoes(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__StoneShoes>(&ctx); }
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
        case SYM_GEN_cdAdvance_1984: out = this->f_cdAdvance; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__TimePendant::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_cdAdvance_1984: this->f_cdAdvance = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__TimePendant::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__TimePendant::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_93, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TimePendant::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_426, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isCooldownActive_94, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_cdAdvance}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_advanceCooldownSeconds_145, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TimePendant::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_cdAdvance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cdadvance", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__TimePendant(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__TimePendant>(&ctx); }
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
        case SYM_GEN_dam_935: out = this->f_dam; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Whetstone::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_dam_935: this->f_dam = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Whetstone::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Whetstone::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Whetstone::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t864 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t865 = (_t864.kind == gd::GdVal::Kind::Arr) ? _t864.arr : nullptr;
        uint32_t _len__t866 = _t865 ? _t865->len : 0u;
        for (uint32_t _t866 = 0; _t866 < _len__t866; ++_t866) {
            gd::GdVal lv_item = _t865->data[_t866];
            (void)([&]() { gd::GdVal _ca[] = {this->f_dam}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_159, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Whetstone::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_dam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Whetstone(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Whetstone>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Whetstone = {CLS_Gd__gd_core_items__Whetstone, "Whetstone", "res://gd_core_items/Whetstone.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Whetstone, &Gd__gd_core_items__Whetstone::get_static_prop_fn, &Gd__gd_core_items__Whetstone::call_static_fn};

void Gd__gd_core_items__Gems__Emerald::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Gems__Gem::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Gems__Emerald::meta() const { return &META_Gd__gd_core_items__Gems__Emerald; }
gd::GdVal Gd__gd_core_items__Gems__Emerald::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_gemColor_991: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.8), gd::GdVal::from_int(3LL), gd::GdVal::from_float(0.8)}; return gd::make_color_from_args(_ca, 3); })();
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
        case SYM_GEN_gemColor_991: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Gems__Emerald::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Gems__Emerald::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_prepareWeapon_978: return true;
        case SYM_GEN_onAttack_1956: return true;
        case SYM_GEN_prepareArmor_979: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Gems__Emerald::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_prepareWeapon_978: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_onAttack_1956: out = fn_onAttack(args, argc); return true;
        case SYM_GEN_prepareArmor_979: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Gems__Emerald::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Gems__Emerald::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_143, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Emerald::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_387, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onAttack", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Emerald::fn_onAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_209, _ca, 2); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Emerald::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Poison_2566), gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_969, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeResistChance_1021, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Emerald::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Gems__Emerald(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Gems__Emerald>(&ctx); }
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
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__HolyArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HolyArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, nullptr, 0);
    gd::GdVal lv_numAffected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numAffected, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_numAffected, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HolyArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleansePoison_340, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HolyArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__HolyArmor(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__HolyArmor>(&ctx); }
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
        case SYM_GEN_plushies_1853: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Mrs Struggles", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Miss Fortune", 12u))}));
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
        case SYM_GEN_hasActivated_1810: out = this->f_hasActivated; return true;
        case SYM_GEN_speedbuffTimer_1854: out = this->f_speedbuffTimer; return true;
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        case SYM_GEN_healthThreshold_1758: out = this->f_healthThreshold; return true;
        case SYM_GEN_bonusSpeed_1786: out = this->f_bonusSpeed; return true;
        case SYM_GEN_fatigueDam_1855: out = this->f_fatigueDam; return true;
        case SYM_GEN_speedBuffParticles1_1856: out = this->f_speedBuffParticles1; return true;
        case SYM_GEN_speedBuffParticles2_1857: out = this->f_speedBuffParticles2; return true;
        case SYM_GEN_plushies_1853: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__MrStruggles::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hasActivated_1810: this->f_hasActivated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_speedbuffTimer_1854: this->f_speedbuffTimer = val; return true;
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        case SYM_GEN_healthThreshold_1758: this->f_healthThreshold = val; return true;
        case SYM_GEN_bonusSpeed_1786: this->f_bonusSpeed = val; return true;
        case SYM_GEN_fatigueDam_1855: this->f_fatigueDam = val; return true;
        case SYM_GEN_speedBuffParticles1_1856: this->f_speedBuffParticles1 = val; return true;
        case SYM_GEN_speedBuffParticles2_1857: this->f_speedBuffParticles2 = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__MrStruggles::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onDamaged_1759: return true;
        case SYM_GEN_onSpeedbuffTimeout_1858: return true;
        case SYM_GEN_onDebuffed_1859: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_getDescription_638: return true;
        case SYM_GEN_rollShopChance_769: return true;
        case SYM_GEN_getGatedDescriptor_952: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__MrStruggles::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1759: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN_onSpeedbuffTimeout_1858: out = fn_onSpeedbuffTimeout(args, argc); return true;
        case SYM_GEN_onDebuffed_1859: out = fn_onDebuffed(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_getDescription_638: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_rollShopChance_769: out = fn_rollShopChance(args, argc); return true;
        case SYM_GEN_getGatedDescriptor_952: out = fn_getGatedDescriptor(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_93, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t867 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1358, nullptr, 0));
        gd::GdArr* _t868 = (_t867.kind == gd::GdVal::Kind::Arr) ? _t867.arr : nullptr;
        uint32_t _len__t869 = _t868 ? _t868->len : 0u;
        for (uint32_t _t869 = 0; _t869 < _len__t869; ++_t869) {
            gd::GdVal lv_debuff = _t868->data[_t869];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::get_prop(gd_ctx, gd::get_index(gd_ctx, gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_buffs_1044), lv_debuff), SYM_GEN_signalName_1009), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDebuffed", 10u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        }
    }
    this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDamaged", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(this->f_hasActivated)) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getRelativeHealth_300, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
        {
            gd::GdVal _t870 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
            gd::GdArr* _t871 = (_t870.kind == gd::GdVal::Kind::Arr) ? _t870.arr : nullptr;
            uint32_t _len__t872 = _t871 ? _t871->len : 0u;
            for (uint32_t _t872 = 0; _t872 < _len__t872; ++_t872) {
                gd::GdVal lv_item = _t871->data[_t872];
                (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_speed", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_speedbuffTimer, SYM_GEN_start_1683, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_onSpeedbuffTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    {
        gd::GdVal _t873 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t874 = (_t873.kind == gd::GdVal::Kind::Arr) ? _t873.arr : nullptr;
        uint32_t _len__t875 = _t874 ? _t874->len : 0u;
        for (uint32_t _t875 = 0; _t875 < _len__t875; ++_t875) {
            gd::GdVal lv_item = _t874->data[_t875];
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_272, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_onDebuffed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "MSROLL", 6u)), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1575))), gd::gd_coerce_int(this->f_ownerType), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "type=", 5u)), ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, lv_event, SYM_GEN_type_1001)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " amt=", 5u))), ([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " ew=", 4u))), ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_chanceRng, SYM_GEN_expectedWins_1653)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " w=", 3u))), ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_chanceRng, SYM_GEN_wins_1654)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " lr=", 4u))), ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_chanceRng, SYM_GEN_lastResult_1656)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), SYM_GEN_trace_diag_1643, _ca, 4); })();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(10LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkTriggerCount_140, _ca, 1); })())) {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) {
            gd::GdVal lv_debuffType = gd::get_prop(gd_ctx, lv_event, SYM_GEN_type_1001);
            gd::GdVal lv_dur = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "duration", 8u)), gd::gd_neg(gd::GdVal::from_int(1LL))}; return gd::call_method(gd_ctx, lv_event, SYM_GEN_getParam_1482, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), lv_debuffType, lv_amount, lv_dur, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacksTemporary_200, _ca, 5); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_fatigueDam}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictFatigueDamage_317, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_speedbuffTimer, SYM_GEN_stop_1684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_852), SYM_GEN_High_2601), gd::GdVal::from_int(3LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    return gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_rollShopChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_shopChance = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_shopChance_1585));
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_getGatedDescriptor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rarity = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {Gd__gd_core_items__MrStruggles::get_static_const_or_enum(gd_ctx, SYM_GEN_plushies_1853)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_pickRandomElement_1648, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MrStruggles::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_speedbuffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "SpeedbuffTimer", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onSpeedbuffTimeout", 18u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_133, _ca, 3); })();
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    this->f_bonusSpeed = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0), gd::GdVal::from_float(100.0));
    this->f_fatigueDam = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__MrStruggles(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__MrStruggles>(&ctx); }
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
        case SYM_GEN_itemsInside_1874: out = this->f_itemsInside; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__RangerBag::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_itemsInside_1874: this->f_itemsInside = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__RangerBag::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onLuckyChanged_897: return true;
        case SYM_GEN_canApplyEffect_916: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__RangerBag::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onLuckyChanged_897: out = fn_onLuckyChanged(args, argc); return true;
        case SYM_GEN_canApplyEffect_916: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__RangerBag::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__RangerBag::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_itemsInside = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_920, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_920, nullptr, 0), gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_lucky_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onLuckyChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    }
    {
        gd::GdVal _t876 = gd::gd_iter_seq(gd_ctx.arena, this->f_itemsInside);
        gd::GdArr* _t877 = (_t876.kind == gd::GdVal::Kind::Arr) ? _t876.arr : nullptr;
        uint32_t _len__t878 = _t877 ? _t877->len : 0u;
        for (uint32_t _t878 = 0; _t878 < _len__t878; ++_t878) {
            gd::GdVal lv_item = _t877->data[_t878];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeCritChancePercent_179, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RangerBag::fn_onLuckyChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_change = gd::gd_mul(lv_amount, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_170, nullptr, 0));
    {
        gd::GdVal _t879 = gd::gd_iter_seq(gd_ctx.arena, this->f_itemsInside);
        gd::GdArr* _t880 = (_t879.kind == gd::GdVal::Kind::Arr) ? _t879.arr : nullptr;
        uint32_t _len__t881 = _t880 ? _t880->len : 0u;
        for (uint32_t _t881 = 0; _t881 < _len__t881; ++_t881) {
            gd::GdVal lv_item = _t880->data[_t881];
            (void)([&]() { gd::GdVal _ca[] = {lv_change}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeCritChancePercent_179, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RangerBag::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_toItem, SYM_GEN_canDamage_87, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RangerBag::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__RangerBag(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__RangerBag>(&ctx); }
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
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::get_prop(prop, out);
}
bool Gd__gd_core_items__TheFool::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__TheFool::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_886: return true;
        case SYM_GEN_doRevealEffect_889: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Card::has_own_method(m);
}
bool Gd__gd_core_items__TheFool::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_886: out = fn_cardSecondaryEffectActive(args, argc); return true;
        case SYM_GEN_doRevealEffect_889: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__TheFool::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__TheFool::fn_cardSecondaryEffectActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_eq(this->f_chainPosition, gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__TheFool::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bonusSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "revealspeed", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    {
        gd::GdVal _t882 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_deck, SYM_GEN_cards_1736));
        gd::GdArr* _t883 = (_t882.kind == gd::GdVal::Kind::Arr) ? _t882.arr : nullptr;
        uint32_t _len__t884 = _t883 ? _t883->len : 0u;
        for (uint32_t _t884 = 0; _t884 < _len__t884; ++_t884) {
            gd::GdVal lv_card = _t883->data[_t884];
            (void)([&]() { gd::GdVal _ca[] = {lv_bonusSpeed}; return gd::call_method(gd_ctx, lv_card, SYM_GEN_addSpeed_271, _ca, 1); })();
        }
    }
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cardSecondaryEffectActive_886, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__TheFool::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Card::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__TheFool(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__TheFool>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__TheFool = {CLS_Gd__gd_core_items__TheFool, "TheFool", "res://gd_core_items/TheFool.gd", &META_Gd__gd_core_items__Card, true, _alloc_Gd__gd_core_items__TheFool, &Gd__gd_core_items__TheFool::get_static_prop_fn, &Gd__gd_core_items__TheFool::call_static_fn};
