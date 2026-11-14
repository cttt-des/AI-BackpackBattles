#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core__Food.hpp"
#include "../hdrs/Gd__gd_core__BurningTorch.hpp"
#include "../hdrs/Gd__gd_core__CoreGrid.hpp"
#include "../hdrs/Gd__gd_core__CursedDagger.hpp"
#include "../hdrs/Gd__gd_core__FalconBlade.hpp"
#include "../hdrs/Gd__gd_core__HeroSword.hpp"
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
#include "../hdrs/Gd__gd_core_items__Exclusive__ChainWhip.hpp"
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
#include "../hdrs/Gd__gd_core_items__Exclusive__Thornbloom.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__UniquelyUnique.hpp"
#include "../hdrs/Gd__gd_core_items__Fanfare.hpp"
#include "../hdrs/Gd__gd_core_items__HealingHerbs.hpp"
#include "../hdrs/Gd__gd_core_items__LuckyPiggy.hpp"
#include "../hdrs/Gd__gd_core_items__PoisonIvy.hpp"
#include "../hdrs/Gd__gd_core_items__SteelGoobert.hpp"
#include "../hdrs/Gd__gd_core_items__WalrusTusk.hpp"

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
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_prepare_124: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Food::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_prepare_124: out = fn_prepare(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Food_2606)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), this->f_descriptor)))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Food::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_prepare_124, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0), gd::GdVal::from_float(0.1))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Food::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__BurningTorch::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__BurningTorch::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__BurningTorch::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BurningTorch::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_permDamBonus}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_163, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BurningTorch::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_permDamBonus = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__BurningTorch(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__BurningTorch>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__BurningTorch = {CLS_Gd__gd_core__BurningTorch, "BurningTorch", "res://gd_core/BurningTorch.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__BurningTorch, &Gd__gd_core__BurningTorch::get_static_prop_fn, &Gd__gd_core__BurningTorch::call_static_fn};

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
        case SYM_GEN_filledCells_1509: out = this->f_filledCells; return true;
        case SYM_GEN_bagCells_1510: out = this->f_bagCells; return true;
        case SYM_GEN_items_1092: out = this->f_items; return true;
        case SYM_GEN_character_76: out = this->f_character; return true;
        case SYM_GEN_curHovered_1511: out = this->f_curHovered; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreGrid::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_filledCells_1509: this->f_filledCells = val; return true;
        case SYM_GEN_bagCells_1510: this->f_bagCells = val; return true;
        case SYM_GEN_items_1092: this->f_items = val; return true;
        case SYM_GEN_character_76: this->f_character = val; return true;
        case SYM_GEN_curHovered_1511: this->f_curHovered = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreGrid::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_getCellsForGlobalPositions_403: return true;
        case SYM_GEN_getItems_1512: return true;
        case SYM_GEN_getItemsAndGems_1513: return true;
        case SYM_GEN_isHovered_714: return true;
        case SYM_GEN_isCellEmpty_1514: return true;
        case SYM_GEN_getEmptyCellsInCells_1515: return true;
        case SYM_GEN_getItemInCell_1516: return true;
        case SYM_GEN_getItemsInCells_1517: return true;
        case SYM_GEN_countItemsInCells_1518: return true;
        case SYM_GEN_getBagsInCells_1519: return true;
        case SYM_GEN_getAdjacentItems_1522: return true;
        case SYM_GEN_countSocketedGems_1523: return true;
        case SYM_GEN_changeBuffPower_allItems_1524: return true;
        case SYM_GEN_changeBuffAmplification_allItems_1525: return true;
        case SYM_GEN_addItemCells_1526: return true;
        case SYM_GEN_addItem_1527: return true;
        case SYM_GEN_removeItem_1528: return true;
        case SYM_GEN_clearItemCells_1529: return true;
        case SYM_GEN_moveItem_1530: return true;
        case SYM_GEN_onItemTypeChanged_460: return true;
        case SYM_GEN_cleanUp_1531: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreGrid::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_getCellsForGlobalPositions_403: out = fn_getCellsForGlobalPositions(args, argc); return true;
        case SYM_GEN_getItems_1512: out = fn_getItems(args, argc); return true;
        case SYM_GEN_getItemsAndGems_1513: out = fn_getItemsAndGems(args, argc); return true;
        case SYM_GEN_isHovered_714: out = fn_isHovered(args, argc); return true;
        case SYM_GEN_isCellEmpty_1514: out = fn_isCellEmpty(args, argc); return true;
        case SYM_GEN_getEmptyCellsInCells_1515: out = fn_getEmptyCellsInCells(args, argc); return true;
        case SYM_GEN_getItemInCell_1516: out = fn_getItemInCell(args, argc); return true;
        case SYM_GEN_getItemsInCells_1517: out = fn_getItemsInCells(args, argc); return true;
        case SYM_GEN_countItemsInCells_1518: out = fn_countItemsInCells(args, argc); return true;
        case SYM_GEN_getBagsInCells_1519: out = fn_getBagsInCells(args, argc); return true;
        case SYM_GEN_getCellsInLine_1520: out = sf_getCellsInLine(gd_ctx, args, argc); return true;
        case SYM_GEN_getAdjacentCells_1521: out = sf_getAdjacentCells(gd_ctx, args, argc); return true;
        case SYM_GEN_getAdjacentItems_1522: out = fn_getAdjacentItems(args, argc); return true;
        case SYM_GEN_countSocketedGems_1523: out = fn_countSocketedGems(args, argc); return true;
        case SYM_GEN_changeBuffPower_allItems_1524: out = fn_changeBuffPower_allItems(args, argc); return true;
        case SYM_GEN_changeBuffAmplification_allItems_1525: out = fn_changeBuffAmplification_allItems(args, argc); return true;
        case SYM_GEN_addItemCells_1526: out = fn_addItemCells(args, argc); return true;
        case SYM_GEN_addItem_1527: out = fn_addItem(args, argc); return true;
        case SYM_GEN_removeItem_1528: out = fn_removeItem(args, argc); return true;
        case SYM_GEN_clearItemCells_1529: out = fn_clearItemCells(args, argc); return true;
        case SYM_GEN_moveItem_1530: out = fn_moveItem(args, argc); return true;
        case SYM_GEN_onItemTypeChanged_460: out = fn_onItemTypeChanged(args, argc); return true;
        case SYM_GEN_cleanUp_1531: out = fn_cleanUp(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreGrid::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getCellsInLine_1520: out = sf_getCellsInLine(gd_ctx, args, argc); return true;
        case SYM_GEN_getAdjacentCells_1521: out = sf_getAdjacentCells(gd_ctx, args, argc); return true;
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
    gd::GdVal lv_itemsAndGems = gd::call_method(gd_ctx, this->f_items, gd::SYM_duplicate, nullptr, 0);
    {
        gd::GdVal _t1557 = gd::gd_iter_seq(gd_ctx.arena, this->f_items);
        gd::GdArr* _t1558 = (_t1557.kind == gd::GdVal::Kind::Arr) ? _t1557.arr : nullptr;
        uint32_t _len__t1559 = _t1558 ? _t1558->len : 0u;
        for (uint32_t _t1559 = 0; _t1559 < _len__t1559; ++_t1559) {
            gd::GdVal lv_item = _t1558->data[_t1559];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, lv_item, SYM_GEN_getGemsNoNull_499, nullptr, 0)}; return gd::call_method(gd_ctx, lv_itemsAndGems, gd::SYM_append_array, _ca, 1); })();
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
        gd::GdVal _t1560 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t1561 = (_t1560.kind == gd::GdVal::Kind::Arr) ? _t1560.arr : nullptr;
        uint32_t _len__t1562 = _t1561 ? _t1561->len : 0u;
        for (uint32_t _t1562 = 0; _t1562 < _len__t1562; ++_t1562) {
            gd::GdVal lv_cell = _t1561->data[_t1562];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCellEmpty_1514, _ca, 1); })())) {
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
    return ([&]() { gd::GdVal _ca[] = {lv_cell, gd::GdVal::null()}; return gd::call_method(gd_ctx, this->f_filledCells, gd::SYM_get, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_getItemsInCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_cells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_itemsInCells = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1563 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t1564 = (_t1563.kind == gd::GdVal::Kind::Arr) ? _t1563.arr : nullptr;
        uint32_t _len__t1565 = _t1564 ? _t1564->len : 0u;
        for (uint32_t _t1565 = 0; _t1565 < _len__t1565; ++_t1565) {
            gd::GdVal lv_cell = _t1564->data[_t1565];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::call_method(gd_ctx, this->f_filledCells, gd::SYM_has, _ca, 1); })())) {
                gd::GdVal lv_item = gd::get_index(gd_ctx, this->f_filledCells, lv_cell);
                if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_item, lv_itemsInCells)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_placed_6))) : gd::GdVal::from_bool(false)))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, lv_itemsInCells, gd::SYM_push_back, _ca, 1); })();
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
        gd::GdVal _t1566 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t1567 = (_t1566.kind == gd::GdVal::Kind::Arr) ? _t1566.arr : nullptr;
        uint32_t _len__t1568 = _t1567 ? _t1567->len : 0u;
        for (uint32_t _t1568 = 0; _t1568 < _len__t1568; ++_t1568) {
            gd::GdVal lv_cell = _t1567->data[_t1568];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::call_method(gd_ctx, this->f_filledCells, gd::SYM_has, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_itemCounter, gd::get_index(gd_ctx, this->f_filledCells, lv_cell)}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictAdd_1694, _ca, 2); })();
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
        gd::GdVal _t1569 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t1570 = (_t1569.kind == gd::GdVal::Kind::Arr) ? _t1569.arr : nullptr;
        uint32_t _len__t1571 = _t1570 ? _t1570->len : 0u;
        for (uint32_t _t1571 = 0; _t1571 < _len__t1571; ++_t1571) {
            gd::GdVal lv_cell = _t1570->data[_t1571];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::call_method(gd_ctx, this->f_bagCells, gd::SYM_has, _ca, 1); })())) {
                gd::GdVal lv_bag = gd::get_index(gd_ctx, this->f_bagCells, lv_cell);
                if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_bag, lv_bags))))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_bag}; return gd::call_method(gd_ctx, lv_bags, gd::SYM_push_back, _ca, 1); })();
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
        gd::GdVal _t1572 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t1573 = (_t1572.kind == gd::GdVal::Kind::Arr) ? _t1572.arr : nullptr;
        uint32_t _len__t1574 = _t1573 ? _t1573->len : 0u;
        for (uint32_t _t1574 = 0; _t1574 < _len__t1574; ++_t1574) {
            gd::GdVal lv_cell = _t1573->data[_t1574];
            {
                gd::GdVal _t1575 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::gd_add(gd_ctx, lv_distance, gd::GdVal::from_int(1LL))}; return gd::gd_range(gd_ctx.arena, _ca, 2); })());
                gd::GdArr* _t1576 = (_t1575.kind == gd::GdVal::Kind::Arr) ? _t1575.arr : nullptr;
                uint32_t _len__t1577 = _t1576 ? _t1576->len : 0u;
                for (uint32_t _t1577 = 0; _t1577 < _len__t1577; ++_t1577) {
                    gd::GdVal lv_offset = _t1576->data[_t1577];
                    gd::GdVal lv_neighbor = gd::gd_add(gd_ctx, lv_cell, gd::gd_mul(lv_direction, lv_offset));
                    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_neighbor, lv_cells)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_neighbor, lv_lineCells))))) : gd::GdVal::from_bool(false)))) {
                        (void)([&]() { gd::GdVal _ca[] = {lv_neighbor}; return gd::call_method(gd_ctx, lv_lineCells, gd::SYM_push_back, _ca, 1); })();
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
        gd::GdVal _t1578 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t1579 = (_t1578.kind == gd::GdVal::Kind::Arr) ? _t1578.arr : nullptr;
        uint32_t _len__t1580 = _t1579 ? _t1579->len : 0u;
        for (uint32_t _t1580 = 0; _t1580 < _len__t1580; ++_t1580) {
            gd::GdVal lv_cell = _t1579->data[_t1580];
            {
                gd::GdVal _t1581 = gd::gd_iter_seq(gd_ctx.arena, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2(1.0, 0.0), gd::GdVal::from_vec2(-1.0, 0.0), gd::GdVal::from_vec2(0.0, -1.0), gd::GdVal::from_vec2(0.0, 1.0)})));
                gd::GdArr* _t1582 = (_t1581.kind == gd::GdVal::Kind::Arr) ? _t1581.arr : nullptr;
                uint32_t _len__t1583 = _t1582 ? _t1582->len : 0u;
                for (uint32_t _t1583 = 0; _t1583 < _len__t1583; ++_t1583) {
                    gd::GdVal lv_offset = _t1582->data[_t1583];
                    gd::GdVal lv_neighbor = gd::gd_add(gd_ctx, lv_cell, lv_offset);
                    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_neighbor, lv_cells)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_neighbor, lv_adjacentCells))))) : gd::GdVal::from_bool(false)))) {
                        (void)([&]() { gd::GdVal _ca[] = {lv_neighbor}; return gd::call_method(gd_ctx, lv_adjacentCells, gd::SYM_push_back, _ca, 1); })();
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
    return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, lv_item, SYM_GEN_occupiedCells_54)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreGrid::call_static_fn(gd_ctx, SYM_GEN_getAdjacentCells_1521, _ca, 1, _out); return _out; })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInCells_1517, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_countSocketedGems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numGems = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t1584 = gd::gd_iter_seq(gd_ctx.arena, this->f_items);
        gd::GdArr* _t1585 = (_t1584.kind == gd::GdVal::Kind::Arr) ? _t1584.arr : nullptr;
        uint32_t _len__t1586 = _t1585 ? _t1585->len : 0u;
        for (uint32_t _t1586 = 0; _t1586 < _len__t1586; ++_t1586) {
            gd::GdVal lv_item = _t1585->data[_t1586];
            lv_numGems = gd::gd_add(gd_ctx, lv_numGems, gd::call_method(gd_ctx, gd::call_method(gd_ctx, lv_item, SYM_GEN_getGemsNoNull_499, nullptr, 0), gd::SYM_size, nullptr, 0));
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
        gd::GdVal _t1587 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsAndGems_1513, nullptr, 0));
        gd::GdArr* _t1588 = (_t1587.kind == gd::GdVal::Kind::Arr) ? _t1587.arr : nullptr;
        uint32_t _len__t1589 = _t1588 ? _t1588->len : 0u;
        for (uint32_t _t1589 = 0; _t1589 < _len__t1589; ++_t1589) {
            gd::GdVal lv_item = _t1588->data[_t1589];
            (void)([&]() { gd::GdVal _ca[] = {lv_buffType, lv_amount}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveBuffPower_305, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_changeBuffAmplification_allItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    {
        gd::GdVal _t1590 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsAndGems_1513, nullptr, 0));
        gd::GdArr* _t1591 = (_t1590.kind == gd::GdVal::Kind::Arr) ? _t1590.arr : nullptr;
        uint32_t _len__t1592 = _t1591 ? _t1591->len : 0u;
        for (uint32_t _t1592 = 0; _t1592 < _len__t1592; ++_t1592) {
            gd::GdVal lv_item = _t1591->data[_t1592];
            (void)([&]() { gd::GdVal _ca[] = {lv_buffType, lv_amount}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_198, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_addItemCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isBag_85, nullptr, 0))) {
        {
            gd::GdVal _t1593 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
            gd::GdArr* _t1594 = (_t1593.kind == gd::GdVal::Kind::Arr) ? _t1593.arr : nullptr;
            uint32_t _len__t1595 = _t1594 ? _t1594->len : 0u;
            for (uint32_t _t1595 = 0; _t1595 < _len__t1595; ++_t1595) {
                gd::GdVal lv_cell = _t1594->data[_t1595];
                { gd::GdVal _t1596 = this->f_bagCells; gd::GdVal _t1597 = lv_cell; gd::set_index(gd_ctx, _t1596, _t1597, lv_item); }
            }
        }
    }
    else {
        {
            gd::GdVal _t1598 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
            gd::GdArr* _t1599 = (_t1598.kind == gd::GdVal::Kind::Arr) ? _t1598.arr : nullptr;
            uint32_t _len__t1600 = _t1599 ? _t1599->len : 0u;
            for (uint32_t _t1600 = 0; _t1600 < _len__t1600; ++_t1600) {
                gd::GdVal lv_cell = _t1599->data[_t1600];
                { gd::GdVal _t1601 = this->f_filledCells; gd::GdVal _t1602 = lv_cell; gd::set_index(gd_ctx, _t1601, _t1602, lv_item); }
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
    (void)([&]() { gd::GdVal _ca[] = {lv_item, lv_cells}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addItemCells_1526, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, this->f_items, gd::SYM_push_back, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_cells, lv_placedByPlayer}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addToInventory_122, _ca, 3); })();
    {
        gd::GdVal _t1603 = gd::gd_iter_seq(gd_ctx.arena, this->f_items);
        gd::GdArr* _t1604 = (_t1603.kind == gd::GdVal::Kind::Arr) ? _t1603.arr : nullptr;
        uint32_t _len__t1605 = _t1604 ? _t1604->len : 0u;
        for (uint32_t _t1605 = 0; _t1605 < _len__t1605; ++_t1605) {
            gd::GdVal lv_other = _t1604->data[_t1605];
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, lv_other, SYM_GEN_onItemAdded_439, _ca, 1); })();
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
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearItemCells_1529, _ca, 1); })();
    gd::GdVal lv_idx = ([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, this->f_items, gd::SYM_find, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_idx, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_idx}; return gd::call_method(gd_ctx, this->f_items, gd::SYM_remove, _ca, 1); })();
    }
    {
        gd::GdVal _t1606 = gd::gd_iter_seq(gd_ctx.arena, this->f_items);
        gd::GdArr* _t1607 = (_t1606.kind == gd::GdVal::Kind::Arr) ? _t1606.arr : nullptr;
        uint32_t _len__t1608 = _t1607 ? _t1607->len : 0u;
        for (uint32_t _t1608 = 0; _t1608 < _len__t1608; ++_t1608) {
            gd::GdVal lv_other = _t1607->data[_t1608];
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, lv_other, SYM_GEN_onItemRemoved_440, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_clearItemCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1609 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, lv_item, SYM_GEN_occupiedCells_54));
        gd::GdArr* _t1610 = (_t1609.kind == gd::GdVal::Kind::Arr) ? _t1609.arr : nullptr;
        uint32_t _len__t1611 = _t1610 ? _t1610->len : 0u;
        for (uint32_t _t1611 = 0; _t1611 < _len__t1611; ++_t1611) {
            gd::GdVal lv_cell = _t1610->data[_t1611];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isBag_85, nullptr, 0))) {
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(([&]() { gd::GdVal _ca[] = {lv_cell, gd::GdVal::null()}; return gd::call_method(gd_ctx, this->f_bagCells, gd::SYM_get, _ca, 2); })(), lv_item)))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::call_method(gd_ctx, this->f_bagCells, gd::SYM_erase, _ca, 1); })();
                }
            }
            else {
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(([&]() { gd::GdVal _ca[] = {lv_cell, gd::GdVal::null()}; return gd::call_method(gd_ctx, this->f_filledCells, gd::SYM_get, _ca, 2); })(), lv_item)))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::call_method(gd_ctx, this->f_filledCells, gd::SYM_erase, _ca, 1); })();
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
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearItemCells_1529, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_item, lv_newCells}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addItemCells_1526, _ca, 2); })();
    gd::set_prop(gd_ctx, lv_item, SYM_GEN_occupiedCells_54, lv_newCells);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_onItemTypeChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1612 = gd::gd_iter_seq(gd_ctx.arena, this->f_items);
        gd::GdArr* _t1613 = (_t1612.kind == gd::GdVal::Kind::Arr) ? _t1612.arr : nullptr;
        uint32_t _len__t1614 = _t1613 ? _t1613->len : 0u;
        for (uint32_t _t1614 = 0; _t1614 < _len__t1614; ++_t1614) {
            gd::GdVal lv_other = _t1613->data[_t1614];
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, lv_other, SYM_GEN_onItemTypeChanged_460, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_cleanUp(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_filledCells, gd::SYM_clear, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_bagCells, gd::SYM_clear, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_items, gd::SYM_clear, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_curHovered, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreGrid(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreGrid>(&ctx); }
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
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_onOpponentDebuffsChanged_1728: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Dagger::has_own_method(m);
}
bool Gd__gd_core__CursedDagger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onOpponentDebuffsChanged_1728: out = fn_onOpponentDebuffsChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canDamage_91, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CursedDagger::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentDebuffsChanged", 24u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToOpponentDebuffs_378, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CursedDagger::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictRandomDebuffs_359, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CursedDagger::fn_onOpponentDebuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_extraCritChance = gd::gd_mul(lv_amount, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0));
    gd::GdVal lv_extraAccuracy = gd::gd_mul(lv_amount, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0));
    (void)([&]() { gd::GdVal _ca[] = {lv_extraCritChance}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addCritChancePercent_181, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_extraAccuracy}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addAccuracy_179, _ca, 1); })();
    {
        gd::GdVal _t1615 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1616 = (_t1615.kind == gd::GdVal::Kind::Arr) ? _t1615.arr : nullptr;
        uint32_t _len__t1617 = _t1616 ? _t1616->len : 0u;
        for (uint32_t _t1617 = 0; _t1617 < _len__t1617; ++_t1617) {
            gd::GdVal lv_item = _t1616->data[_t1617];
            (void)([&]() { gd::GdVal _ca[] = {lv_extraCritChance}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addCritChancePercent_181, _ca, 1); })();
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isWeapon_84, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_extraAccuracy}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addAccuracy_179, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CursedDagger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Dagger::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CursedDagger(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CursedDagger>(&ctx); }
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
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_getCraftingOffset_850: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__FalconBlade::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getCraftingOffset_850: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__FalconBlade::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1618 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1619 = (_t1618.kind == gd::GdVal::Kind::Arr) ? _t1618.arr : nullptr;
        uint32_t _len__t1620 = _t1619 ? _t1619->len : 0u;
        for (uint32_t _t1620 = 0; _t1620 < _len__t1620; ++_t1620) {
            gd::GdVal lv_item = _t1619->data[_t1620];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), gd::GdVal::from_int(100LL))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_275, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__FalconBlade::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_118, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1280), SYM_GEN_Sufficient_2605))))) {
        gd::GdVal lv_res = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_222, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 2); })();
        gd::GdVal lv_res2 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_222, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res2, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 2); })();
        gd::GdVal lv_hits = gd::GdVal::from_int(0LL);
        if (gd::gd_truth(gd::call_method(gd_ctx, lv_res, SYM_GEN_hasHit_1432, nullptr, 0))) {
            lv_hits = gd::gd_add(gd_ctx, lv_hits, gd::GdVal::from_int(1LL));
        }
        if (gd::gd_truth(gd::call_method(gd_ctx, lv_res2, SYM_GEN_hasHit_1432, nullptr, 0))) {
            lv_hits = gd::gd_add(gd_ctx, lv_hits, gd::GdVal::from_int(1LL));
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(30.0)), gd::GdVal::from_float(30.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_bare_randf_range_1647, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(100.0)), gd::GdVal::from_float(100.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_bare_randf_range_1647, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(5.0)), gd::GdVal::from_float(5.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_bare_randf_range_1647, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__FalconBlade::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1621 = lv_forDirection;
        if (gd::gd_eq(_t1621, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
        else if (gd::gd_eq(_t1621, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
        else if (gd::gd_eq(_t1621, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::gd_eq(_t1621, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__FalconBlade::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__FalconBlade(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__FalconBlade>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__FalconBlade = {CLS_Gd__gd_core__FalconBlade, "FalconBlade", "res://gd_core/FalconBlade.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__FalconBlade, &Gd__gd_core__FalconBlade::get_static_prop_fn, &Gd__gd_core__FalconBlade::call_static_fn};

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
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__HeroSword::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_92, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeroSword::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1622 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1623 = (_t1622.kind == gd::GdVal::Kind::Arr) ? _t1622.arr : nullptr;
        uint32_t _len__t1624 = _t1623 ? _t1623->len : 0u;
        for (uint32_t _t1624 = 0; _t1624 < _len__t1624; ++_t1624) {
            gd::GdVal lv_item = _t1623->data[_t1624];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_163, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false), gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, Gd__gd_core__HeroSword::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Jump_2608)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeroSword::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__HeroSword(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__HeroSword>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__HeroSword = {CLS_Gd__gd_core__HeroSword, "HeroSword", "res://gd_core/HeroSword.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__HeroSword, &Gd__gd_core__HeroSword::get_static_prop_fn, &Gd__gd_core__HeroSword::call_static_fn};

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
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_explodeRandomly_1826: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Piggybank::has_own_method(m);
}
bool Gd__gd_core__LuckyPiggy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_explodeRandomly_1826: out = fn_explodeRandomly(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canModifyChance_295, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyPiggy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1625 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1626 = (_t1625.kind == gd::GdVal::Kind::Arr) ? _t1625.arr : nullptr;
        uint32_t _len__t1627 = _t1626 ? _t1626->len : 0u;
        for (uint32_t _t1627 = 0; _t1627 < _len__t1627; ++_t1627) {
            gd::GdVal lv_item = _t1626->data[_t1627];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusChance_177, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyPiggy::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyPiggy::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_High_2603), gd::GdVal::from_int(5LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyPiggy::fn_explodeRandomly(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyPiggy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Piggybank::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__LuckyPiggy(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__LuckyPiggy>(&ctx); }
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
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__PocketSand::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__PocketSand::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__PocketSand::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_215, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_383, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PocketSand::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__PocketSand(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__PocketSand>(&ctx); }
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
        case SYM_GEN_blockFactor_1882: out = this->f_blockFactor; return true;
        default: break;
    }
    return Gd__gd_core__Shield::get_prop(prop, out);
}
bool Gd__gd_core__ShieldofValor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockFactor_1882: this->f_blockFactor = val; return true;
        default: break;
    }
    return Gd__gd_core__Shield::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__ShieldofValor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_afterBlock_1847: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Shield::has_own_method(m);
}
bool Gd__gd_core__ShieldofValor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_afterBlock_1847: out = fn_afterBlock(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBlock_293, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ShieldofValor::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1628 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1629 = (_t1628.kind == gd::GdVal::Kind::Arr) ? _t1628.arr : nullptr;
        uint32_t _len__t1630 = _t1629 ? _t1629->len : 0u;
        for (uint32_t _t1630 = 0; _t1630 < _len__t1630; ++_t1630) {
            gd::GdVal lv_item = _t1629->data[_t1630];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Block_2564), this->f_blockFactor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveBuffPower_305, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ShieldofValor::fn_afterBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), gd::get_prop(gd_ctx, this->f_blockedDamageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drainStamina_119, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ShieldofValor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Shield::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_blockFactor = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__ShieldofValor(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__ShieldofValor>(&ctx); }
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
        case SYM_GEN_onTriggerPotion_1754: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__HealthPotion::has_own_method(m);
}
bool Gd__gd_core__StrongHealthPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1754: out = fn_onTriggerPotion(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__HealthPotion::call_method(gd_ctx, SYM_GEN_onTriggerPotion_1754, _ca, 1, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StrongHealthPotion::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_High_2603), gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StrongHealthPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__HealthPotion::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__StrongHealthPotion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__StrongHealthPotion>(&ctx); }
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
        case SYM_GEN_snowflakes_1908: out = this->f_snowflakes; return true;
        case SYM_GEN_damReduction_1778: out = this->f_damReduction; return true;
        default: break;
    }
    return Gd__gd_core__Card::get_prop(prop, out);
}
bool Gd__gd_core__White_EyesBlueDragon::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_snowflakes_1908: this->f_snowflakes = val; return true;
        case SYM_GEN_damReduction_1778: this->f_damReduction = val; return true;
        default: break;
    }
    return Gd__gd_core__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__White_EyesBlueDragon::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Card::has_own_method(m);
}
bool Gd__gd_core__White_EyesBlueDragon::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__White_EyesBlueDragon::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__White_EyesBlueDragon::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0), gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), this->f_chainPosition))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_353, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changeEffectDamageFactor_1265, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__White_EyesBlueDragon::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Card::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_damReduction = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damfactor", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__White_EyesBlueDragon(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__White_EyesBlueDragon>(&ctx); }
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
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_prepare_124: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onItemActivated_938: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Goobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_logCooldown_759: out = fn_logCooldown(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_prepare_124: out = fn_prepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onItemActivated_938: out = fn_onItemActivated(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canActivate_93, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Goobert::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_activations = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_iterationCooldown = gd::gd_coerce_float(this->f_activationsToTrigger);
    this->f_triggerTime = gd::gd_coerce_float(this->f_iterationCooldown);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Cooldown_2546)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    {
        gd::GdVal _t1631 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1632 = (_t1631.kind == gd::GdVal::Kind::Arr) ? _t1631.arr : nullptr;
        uint32_t _len__t1633 = _t1632 ? _t1632->len : 0u;
        for (uint32_t _t1633 = 0; _t1633 < _len__t1633; ++_t1633) {
            gd::GdVal lv_item = _t1632->data[_t1633];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onItemActivated", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        }
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_prepare_124, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Goobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Goobert::fn_onItemActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_activations = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_activations, gd::GdVal::from_int(1LL)));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_activations, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0))))) {
        this->f_activations = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCooldownEffect_146, nullptr, 0);
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_doubleActivationChance, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_doubleActivationChance}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_flip_1639, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCooldownEffect_146, nullptr, 0);
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, this->f_activations, this->f_activationsToTrigger), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 2); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, this->f_activations, this->f_activationsToTrigger), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 2); })();
    }
    this->f_triggerTime = gd::gd_coerce_float(gd::gd_sub(this->f_activationsToTrigger, this->f_activations));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Cooldown_2546), gd::GdVal::null(), gd::GdVal::from_bool(false), lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Goobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_activationsToTrigger = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Goobert(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Goobert>(&ctx); }
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
        case SYM_GEN_movedDebuffs_1717: out = this->f_movedDebuffs; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__CorruptedArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_movedDebuffs_1717: this->f_movedDebuffs = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__CorruptedArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_reactToItemTypeChange_459: return true;
        case SYM_GEN_onAffectedItemAdded_437: return true;
        case SYM_GEN_onAffectedItemRemoved_438: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__CorruptedArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_reactToItemTypeChange_459: out = fn_reactToItemTypeChange(args, argc); return true;
        case SYM_GEN_onAffectedItemAdded_437: out = fn_onAffectedItemAdded(args, argc); return true;
        case SYM_GEN_onAffectedItemRemoved_438: out = fn_onAffectedItemRemoved(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Dark_2602)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CorruptedArmor::fn_reactToItemTypeChange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::gd_in(lv_item, gd::get_index(gd_ctx, this->f_currentAffectedItems, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581))))) {
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Dark_2602), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasDynamicType_243, _ca, 2); })())) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_currentAffectedItems, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581)), gd::SYM_erase, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemRemoved_438, _ca, 2); })();
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
    if (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Dark_2602)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Dark_2602), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addDynamicType_244, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CorruptedArmor::fn_onAffectedItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Dark_2602), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_removeDynamicType_245, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CorruptedArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, nullptr, 0);
    gd::GdVal lv_debuffProtectionChance = gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0));
    (void)([&]() { gd::GdVal _ca[] = {lv_debuffProtectionChance}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changeDebuffProtectionChance_1271, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CorruptedArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_cleansedDebuffs = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1362, nullptr, 0), this->f_movedDebuffs, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_pickRandomStacks_360, _ca, 3); })();
    {
        gd::GdVal _t1634 = gd::gd_iter_seq(gd_ctx.arena, lv_cleansedDebuffs);
        gd::GdArr* _t1635 = (_t1634.kind == gd::GdVal::Kind::Arr) ? _t1634.arr : nullptr;
        uint32_t _len__t1636 = _t1635 ? _t1635->len : 0u;
        for (uint32_t _t1636 = 0; _t1636 < _len__t1636; ++_t1636) {
            gd::GdVal lv_debuff = _t1635->data[_t1636];
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_debuff, gd::get_index(gd_ctx, lv_cleansedDebuffs, lv_debuff), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_loseStacks_1031, _ca, 3); })();
            if (gd::gd_truth(lv_event)) {
                gd::GdVal lv_actuallyCleansed = gd::gd_neg(gd::call_method(gd_ctx, lv_event, SYM_GEN_getAmount_1485, nullptr, 0));
                (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), lv_debuff, lv_actuallyCleansed, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
            }
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CorruptedArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_movedDebuffs = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__CorruptedArmor(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__CorruptedArmor>(&ctx); }
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
        case SYM_GEN_nullifyApplied_1776: out = this->f_nullifyApplied; return true;
        case SYM_GEN_buffsActive_1777: out = this->f_buffsActive; return true;
        case SYM_GEN_buffTimer_1724: out = this->f_buffTimer; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_damReduction_1778: out = this->f_damReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__EvilCap::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_nullifyApplied_1776: this->f_nullifyApplied = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_buffsActive_1777: this->f_buffsActive = val; return true;
        case SYM_GEN_buffTimer_1724: this->f_buffTimer = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_damReduction_1778: this->f_damReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__EvilCap::has_own_method(gd::SymId m) const {
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
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__EvilCap::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
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
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__EvilCap::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__EvilCap::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_reduceHealingEfficiency_1167, _ca, 1); })();
    this->f_nullifyApplied = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__EvilCap::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeDamageResistance_1263, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__EvilCap::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__EvilCap::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeDamageResistance_1263, _ca, 1); })();
    this->f_buffsActive = gd::gd_sub(this->f_buffsActive, gd::GdVal::from_int(1LL));
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__EvilCap::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1686, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__EvilCap::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_buffsActive = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BuffTimer", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffEnded", 9u)), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_137, _ca, 3); })();
    this->f_damReduction = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__EvilCap(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__EvilCap>(&ctx); }
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
        case SYM_GEN_hasActivated_1811: out = this->f_hasActivated; return true;
        case SYM_GEN_speedTimer_1944: out = this->f_speedTimer; return true;
        case SYM_GEN_healthThreshold_1759: out = this->f_healthThreshold; return true;
        case SYM_GEN_manaNeeded_1786: out = this->f_manaNeeded; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        case SYM_GEN_bonusSpeed_1787: out = this->f_bonusSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ArcaneBoots::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hasActivated_1811: this->f_hasActivated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_speedTimer_1944: this->f_speedTimer = val; return true;
        case SYM_GEN_healthThreshold_1759: this->f_healthThreshold = val; return true;
        case SYM_GEN_manaNeeded_1786: this->f_manaNeeded = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        case SYM_GEN_bonusSpeed_1787: this->f_bonusSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ArcaneBoots::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onDamaged_1760: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_onSpeedTimerTimeout_1945: return true;
        case SYM_GEN_onCombatEnd_134: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ArcaneBoots::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1760: out = fn_onDamaged(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_onSpeedTimerTimeout_1945: out = fn_onSpeedTimerTimeout(args, argc); return true;
        case SYM_GEN_onCombatEnd_134: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneBoots::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDamaged", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneBoots::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(this->f_hasActivated)) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getRelativeHealth_304, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMana_1228, nullptr, 0), this->f_manaNeeded)))) {
            this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
            gd::GdVal lv_event2 = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_334, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_luck, lv_event2}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_empower, lv_event2}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0), gd::GdVal::from_bool(true), lv_event2}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 3); })();
            {
                gd::GdVal _t1637 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
                gd::GdArr* _t1638 = (_t1637.kind == gd::GdVal::Kind::Arr) ? _t1637.arr : nullptr;
                uint32_t _len__t1639 = _t1638 ? _t1638->len : 0u;
                for (uint32_t _t1639 = 0; _t1639 < _len__t1639; ++_t1639) {
                    gd::GdVal lv_item = _t1638->data[_t1639];
                    (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_275, _ca, 1); })();
                }
            }
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_speed", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_speedTimer, SYM_GEN_start_1685, _ca, 1); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_383, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneBoots::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_High_2603), gd::GdVal::from_int(2LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneBoots::fn_onSpeedTimerTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1640 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1641 = (_t1640.kind == gd::GdVal::Kind::Arr) ? _t1640.arr : nullptr;
        uint32_t _len__t1642 = _t1641 ? _t1641->len : 0u;
        for (uint32_t _t1642 = 0; _t1642 < _len__t1642; ++_t1642) {
            gd::GdVal lv_item = _t1641->data[_t1642];
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_276, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneBoots::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_speedTimer, SYM_GEN_stop_1686, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneBoots::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_speedTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "SpeedTimer", 10u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onSpeedTimerTimeout", 19u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_137, _ca, 3); })();
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healtht", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "manat", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_bonusSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ArcaneBoots(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ArcaneBoots>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ArcaneBoots = {CLS_Gd__gd_core_items__Exclusive__ArcaneBoots, "ArcaneBoots", "res://gd_core_items/Exclusive/ArcaneBoots.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__ArcaneBoots, &Gd__gd_core_items__Exclusive__ArcaneBoots::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ArcaneBoots::call_static_fn};

void Gd__gd_core_items__Exclusive__Battery::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_flatSpeed = gd::GdVal::null();
    this->f_speedPerTile = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Battery::meta() const { return &META_Gd__gd_core_items__Exclusive__Battery; }
gd::GdVal Gd__gd_core_items__Exclusive__Battery::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_chargeCells_1960: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(2LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(3LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(4LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(5LL))).as_float())}));
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
        case SYM_GEN_flatSpeed_1961: out = this->f_flatSpeed; return true;
        case SYM_GEN_speedPerTile_1962: out = this->f_speedPerTile; return true;
        case SYM_GEN_chargeCells_1960: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Battery::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_flatSpeed_1961: this->f_flatSpeed = val; return true;
        case SYM_GEN_speedPerTile_1962: this->f_speedPerTile = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Battery::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_lightning_291: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_emitCharge_1963: return true;
        case SYM_GEN_onChargeEnteredCell_1964: return true;
        case SYM_GEN_chargedItemStatChange_1965: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Battery::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_lightning_291: out = fn_canAffect_lightning(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_emitCharge_1963: out = fn_emitCharge(args, argc); return true;
        case SYM_GEN_onChargeEnteredCell_1964: out = fn_onChargeEnteredCell(args, argc); return true;
        case SYM_GEN_chargedItemStatChange_1965: out = fn_chargedItemStatChange(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_97, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_reactsToCharges_301, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Battery::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_emitCharge_1963, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "charge_emitted", 14u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_obj(this)}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Battery::fn_emitCharge(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_speedFactor = (_argc > 0) ? _args[0] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_event = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), Gd__gd_core_items__Exclusive__Battery::get_static_const_or_enum(gd_ctx, SYM_GEN_chargeCells_1960), lv_speedFactor, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_sendCharge_322, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Battery::fn_onChargeEnteredCell(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cellIndex = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_charge, lv_cellIndex, this->f_flatSpeed, this->f_speedPerTile}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeChargedItemStat_328, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Battery::fn_chargedItemStatChange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_value}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_275, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Battery::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_High_2603), gd::GdVal::from_int(5LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Battery::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_flatSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_int(100LL));
    this->f_speedPerTile = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed2", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_int(100LL));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Battery(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Battery>(&ctx); }
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
        case SYM_GEN_staminaReduction_1918: out = this->f_staminaReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Boomerang::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaReduction_1918: this->f_staminaReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Boomerang::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Boomerang::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_staminaReduction)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeStaminaFactor_307, _ca, 1); })();
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_375, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Boomerang::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_staminaReduction = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Boomerang(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Boomerang>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Boomerang = {CLS_Gd__gd_core_items__Exclusive__Boomerang, "Boomerang", "res://gd_core_items/Exclusive/Boomerang.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__Boomerang, &Gd__gd_core_items__Exclusive__Boomerang::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Boomerang::call_static_fn};

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
        case SYM_GEN_buffsPurged_2026: out = this->f_buffsPurged; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ChainWhip::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffsPurged_2026: this->f_buffsPurged = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ChainWhip::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onOpponentBuffsChanged_2027: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ChainWhip::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onOpponentBuffsChanged_2027: out = fn_onOpponentBuffsChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentBuffsChanged", 22u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToOpponentBuffs_379, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ChainWhip::fn_onOpponentBuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL))))) {
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(gd::call_method(gd_ctx, lv_event, SYM_GEN_getOrigin_1489, nullptr, 0), &META_Gd__gd_core_items__Item))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::call_method(gd_ctx, lv_event, SYM_GEN_getOrigin_1489, nullptr, 0), SYM_GEN_character_76, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
            this->f_buffsPurged = gd::gd_add(gd_ctx, this->f_buffsPurged, gd::gd_neg(lv_amount));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_neg(lv_amount), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_163, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ChainWhip::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeRandomBuffs_374, _ca, 1); })();
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_isBattleRaging_1191, nullptr, 0))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ChainWhip::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ChainWhip(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ChainWhip>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ChainWhip = {CLS_Gd__gd_core_items__Exclusive__ChainWhip, "ChainWhip", "res://gd_core_items/Exclusive/ChainWhip.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__ChainWhip, &Gd__gd_core_items__Exclusive__ChainWhip::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ChainWhip::call_static_fn};

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
        case SYM_GEN_heat_1801: out = this->f_heat; return true;
        case SYM_GEN_heatFirstCapture_2064: out = this->f_heatFirstCapture; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteQueen::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heat_1801: this->f_heat = val; return true;
        case SYM_GEN_heatFirstCapture_2064: this->f_heatFirstCapture = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteQueen::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2050: return true;
        case SYM_GEN_doEliminatedEffect_2052: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteQueen::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2050: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_doEliminatedEffect_2052: out = fn_doEliminatedEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_numCaptures, gd::GdVal::from_int(1LL))))) {
        return ([&]() { gd::GdVal _ca[] = {this->f_heatFirstCapture}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteQueen::fn_doEliminatedEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_makeInvulnerable_1195, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteQueen::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat2", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_heatFirstCapture = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat1", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Chess__WhiteQueen(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Chess__WhiteQueen>(&ctx); }
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
        case SYM_GEN_buffRemoval_2091: out = this->f_buffRemoval; return true;
        case SYM_GEN_buffGain_2092: out = this->f_buffGain; return true;
        case SYM_GEN_speedPerFood_2093: out = this->f_speedPerFood; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__CupcakeDragon::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffRemoval_2091: this->f_buffRemoval = val; return true;
        case SYM_GEN_buffGain_2092: this->f_buffGain = val; return true;
        case SYM_GEN_speedPerFood_2093: this->f_speedPerFood = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__CupcakeDragon::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__CupcakeDragon::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        gd::GdVal lv_buffsLeft = this->f_buffRemoval;
        gd::GdVal lv_ownMostBuffs = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMostStacks_363, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_ownMostBuffs, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Exclusive/CupcakeDragon.gd:11", 29u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_shuffleEngine_1651, _ca, 2); })();
        {
            gd::GdVal _t1643 = gd::gd_iter_seq(gd_ctx.arena, lv_ownMostBuffs);
            gd::GdArr* _t1644 = (_t1643.kind == gd::GdVal::Kind::Arr) ? _t1643.arr : nullptr;
            uint32_t _len__t1645 = _t1644 ? _t1644->len : 0u;
            for (uint32_t _t1645 = 0; _t1645 < _len__t1645; ++_t1645) {
                gd::GdVal lv_buffType = _t1644->data[_t1645];
                gd::GdVal lv_cur = ([&]() { gd::GdVal _ca[] = {lv_buffType}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_getStacks_1022, _ca, 1); })();
                gd::GdVal lv_buffsRemoved = gd::gd_min(lv_cur, lv_buffsLeft);
                (void)([&]() { gd::GdVal _ca[] = {lv_buffType, lv_buffsRemoved, gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_loseStacks_1031, _ca, 3); })();
                lv_buffsLeft = gd::gd_sub(lv_buffsLeft, lv_buffsRemoved);
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_buffsLeft, gd::GdVal::from_int(0LL))))) {
                    break;
                }
            }
        }
        gd::GdVal lv_oppoMostBuffs = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMostStacks_363, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), ([&]() { gd::GdVal _ca[] = {lv_oppoMostBuffs}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_pickRandomElement_1650, _ca, 1); })(), this->f_buffGain}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CupcakeDragon::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Food_2606)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CupcakeDragon::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_speedPerFood, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CupcakeDragon::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_buffRemoval = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "remove", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_buffGain = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gain", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_speedPerFood = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__CupcakeDragon(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__CupcakeDragon>(&ctx); }
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
        case SYM_GEN_onPreCombatStart_127: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__RubyWhelp::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreCombatStart_127: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__RubyWhelp::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__RubyWhelp::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveReflectStacks_202, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RubyWhelp::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RubyWhelp::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__RubyWhelp(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__RubyWhelp>(&ctx); }
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
        case SYM_GEN_stackTypes_1831: out = this->f_stackTypes; return true;
        case SYM_GEN_heat_1801: out = this->f_heat; return true;
        case SYM_GEN_heatThreshold_1880: out = this->f_heatThreshold; return true;
        case SYM_GEN_numBuffs_1910: out = this->f_numBuffs; return true;
        case SYM_GEN_speedPerFood_2093: out = this->f_speedPerFood; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__EnergyConversion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stackTypes_1831: this->f_stackTypes = val; return true;
        case SYM_GEN_heat_1801: this->f_heat = val; return true;
        case SYM_GEN_heatThreshold_1880: this->f_heatThreshold = val; return true;
        case SYM_GEN_numBuffs_1910: this->f_numBuffs = val; return true;
        case SYM_GEN_speedPerFood_2093: this->f_speedPerFood = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__EnergyConversion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__EnergyConversion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Food_2606)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EnergyConversion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0), this->f_speedPerFood)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EnergyConversion::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_118, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1280), SYM_GEN_Sufficient_2605))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getHeat_1235, nullptr, 0), this->f_heatThreshold)))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_numBuffs, gd::GdVal::null(), this->f_stackTypes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_371, _ca, 3); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
        }
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EnergyConversion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_heatThreshold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heatt", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_numBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_speedPerFood = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_stackTypes = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Heat_2573)}; return gd::call_method(gd_ctx, this->f_stackTypes, gd::SYM_erase, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__EnergyConversion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__EnergyConversion>(&ctx); }
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
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_combatStart_129: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ForestFriend::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_combatStart_129: out = fn_combatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Pet_2600)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Food_2606)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ForestFriend::fn_combatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_combatStart_129, nullptr, 0, _out); return _out; })();
    gd::GdVal lv_numAffected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numAffected, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(lv_numAffected, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ForestFriend::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ForestFriend(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ForestFriend>(&ctx); }
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
        case SYM_GEN_gold_2198: out = this->f_gold; return true;
        case SYM_GEN_regen_1904: out = this->f_regen; return true;
        case SYM_GEN_cleanse_1121: out = this->f_cleanse; return true;
        case SYM_GEN_block_1582: out = this->f_block; return true;
        case SYM_GEN_speedMalus_2085: out = this->f_speedMalus; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__GoldArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_gold_2198: this->f_gold = val; return true;
        case SYM_GEN_regen_1904: this->f_regen = val; return true;
        case SYM_GEN_cleanse_1121: this->f_cleanse = val; return true;
        case SYM_GEN_block_1582: this->f_block = val; return true;
        case SYM_GEN_speedMalus_2085: this->f_speedMalus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__GoldArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__GoldArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__GoldArmor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldArmor::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_gold}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveGold_754, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldArmor::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldArmor::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1646 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1512, nullptr, 0));
        gd::GdArr* _t1647 = (_t1646.kind == gd::GdVal::Kind::Arr) ? _t1646.arr : nullptr;
        uint32_t _len__t1648 = _t1647 ? _t1647->len : 0u;
        for (uint32_t _t1648 = 0; _t1648 < _len__t1648; ++_t1648) {
            gd::GdVal lv_item = _t1647->data[_t1648];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Weapon_2666)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_speedMalus}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_276, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0), this->f_regen)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_cleanse}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_358, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getDebuffStacks_1200, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_block}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_gold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_cleanse = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cleanse", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_block = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "block", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_speedMalus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__GoldArmor(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__GoldArmor>(&ctx); }
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
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__IceArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__IceArmor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__IceArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_353, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__IceArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getHeat_1235, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useHeat_356, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_353, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__IceArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__IceArmor(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__IceArmor>(&ctx); }
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
        case SYM_GEN_stamina_2060: out = this->f_stamina; return true;
        case SYM_GEN_mana_1833: out = this->f_mana; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_speedPerRound_2249: out = this->f_speedPerRound; return true;
        case SYM_GEN_buyRound_2250: out = this->f_buyRound; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__LevelUp::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stamina_2060: this->f_stamina = val; return true;
        case SYM_GEN_mana_1833: this->f_mana = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_speedPerRound_2249: this->f_speedPerRound = val; return true;
        case SYM_GEN_buyRound_2250: this->f_buyRound = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__LevelUp::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__LevelUp::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__LevelUp::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__LevelUp::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_roundsPassed = gd::gd_sub(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_cur_round_1396), this->f_buyRound);
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_roundsPassed, this->f_speedPerRound)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LevelUp::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_stamina}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_320, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LevelUp::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_speedPerRound = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_buyRound = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "skillround", 10u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__LevelUp(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__LevelUp>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__LevelUp = {CLS_Gd__gd_core_items__Exclusive__LevelUp, "LevelUp", "res://gd_core_items/Exclusive/LevelUp.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__LevelUp, &Gd__gd_core_items__Exclusive__LevelUp::get_static_prop_fn, &Gd__gd_core_items__Exclusive__LevelUp::call_static_fn};

void Gd__gd_core_items__Exclusive__ManaCrystal::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_mana1 = gd::GdVal::null();
    this->f_mana2 = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ManaCrystal::meta() const { return &META_Gd__gd_core_items__Exclusive__ManaCrystal; }
gd::GdVal Gd__gd_core_items__Exclusive__ManaCrystal::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_chargeCells_1960: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(2LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(3LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float())})), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(2LL))).as_float())})), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(2LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(3LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float())})), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(1LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(2LL)).as_float())}))}));
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
        case SYM_GEN_mana1_2297: out = this->f_mana1; return true;
        case SYM_GEN_mana2_2178: out = this->f_mana2; return true;
        case SYM_GEN_chargeCells_1960: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ManaCrystal::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_mana1_2297: this->f_mana1 = val; return true;
        case SYM_GEN_mana2_2178: this->f_mana2 = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ManaCrystal::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_lightning_291: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_emitCharge_1963: return true;
        case SYM_GEN_onChargeEnteredCell_1964: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ManaCrystal::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_lightning_291: out = fn_canAffect_lightning(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_emitCharge_1963: out = fn_emitCharge(args, argc); return true;
        case SYM_GEN_onChargeEnteredCell_1964: out = fn_onChargeEnteredCell(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_emitCharge_1963, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "charge_emitted", 14u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_obj(this)}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaCrystal::fn_emitCharge(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_speedFactor = (_argc > 0) ? _args[0] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_event = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    {
        gd::GdVal _t1649 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, Gd__gd_core_items__Exclusive__ManaCrystal::get_static_const_or_enum(gd_ctx, SYM_GEN_chargeCells_1960), gd::SYM_size, nullptr, 0));
        gd::GdArr* _t1650 = (_t1649.kind == gd::GdVal::Kind::Arr) ? _t1649.arr : nullptr;
        uint32_t _len__t1651 = _t1650 ? _t1650->len : 0u;
        for (uint32_t _t1651 = 0; _t1651 < _len__t1651; ++_t1651) {
            gd::GdVal lv_i = _t1650->data[_t1651];
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__ManaCrystal::get_static_const_or_enum(gd_ctx, SYM_GEN_chargeCells_1960), lv_i), lv_speedFactor, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_sendCharge_322, _ca, 4); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaCrystal::fn_onChargeEnteredCell(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cellIndex = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1557), gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1557), gd::get_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1556))))) : gd::GdVal::from_bool(false)))) {
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Magic_2721)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1557), SYM_GEN_hasType_81, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_mana2}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {this->f_mana1}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaCrystal::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_mana1 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana1", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_mana2 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana2", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ManaCrystal(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ManaCrystal>(&ctx); }
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
        case SYM_GEN_cold_1950: out = this->f_cold; return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__NoRushPlease::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_cold_1950: this->f_cold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__NoRushPlease::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onPreCombatStart_127: return true;
        case SYM_GEN_buffEnded_1722: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__NoRushPlease::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreCombatStart_127: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_buffEnded_1722: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN_onPreCombatStart_127, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changeDamageResistance_1263, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__NoRushPlease::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN_buffEnded_1722, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changeDamageResistance_1263, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__NoRushPlease::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_cold}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_353, _ca, 1); })();
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN_onCombatStart_934, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__NoRushPlease::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_cold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__NoRushPlease(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__NoRushPlease>(&ctx); }
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
        case SYM_GEN_poisonCritActive_2334: out = this->f_poisonCritActive; return true;
        case SYM_GEN_tween_2335: out = this->f_tween; return true;
        case SYM_GEN_poison_1867: out = this->f_poison; return true;
        case SYM_GEN_selfPoison_2308: out = this->f_selfPoison; return true;
        case SYM_GEN_cdAdvance_1985: out = this->f_cdAdvance; return true;
        case SYM_GEN_luckNeeded_1779: out = this->f_luckNeeded; return true;
        case SYM_GEN_light_949: out = this->f_light; return true;
        case SYM_GEN_lightAni_2336: out = this->f_lightAni; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PoisonGrenade::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_poisonCritActive_2334: this->f_poisonCritActive = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_tween_2335: this->f_tween = val; return true;
        case SYM_GEN_poison_1867: this->f_poison = val; return true;
        case SYM_GEN_selfPoison_2308: this->f_selfPoison = val; return true;
        case SYM_GEN_cdAdvance_1985: this->f_cdAdvance = val; return true;
        case SYM_GEN_luckNeeded_1779: this->f_luckNeeded = val; return true;
        case SYM_GEN_light_949: this->f_light = val; return true;
        case SYM_GEN_lightAni_2336: this->f_lightAni = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PoisonGrenade::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onChargeReceived_2035: return true;
        case SYM_GEN_onLuckChanged_1969: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PoisonGrenade::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onChargeReceived_2035: out = fn_onChargeReceived(args, argc); return true;
        case SYM_GEN_onLuckChanged_1969: out = fn_onLuckChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PoisonGrenade::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonGrenade::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_lucky_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onLuckChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonGrenade::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_poison}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_213, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_selfPoison}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_selfInflictPoison_214, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonGrenade::fn_onChargeReceived(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_cdAdvance}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_advanceCooldownSeconds_149, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonGrenade::fn_onLuckChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_poisonCritActive)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getLucky_1221, nullptr, 0), this->f_luckNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changePoisonCritChancePercent_1267, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    }
    else if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(this->f_poisonCritActive)) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getLucky_1221, nullptr, 0), this->f_luckNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changePoisonCritChancePercent_1267, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_poison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "poison", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_selfPoison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "poison2", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_cdAdvance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cdadvance", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luckt", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PoisonGrenade(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__PoisonGrenade>(&ctx); }
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
        case SYM_GEN_onAddToInventory_421: return true;
        case SYM_GEN_onRemoveFromInventory_420: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_getRelatedItems_461: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN_getRelatedItemHeight_700: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__RainbowBadge::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onAddToInventory_421: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_420: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getRelatedItems_461: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_700: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
        gd::GdVal _t1652 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0));
        gd::GdArr* _t1653 = (_t1652.kind == gd::GdVal::Kind::Arr) ? _t1652.arr : nullptr;
        uint32_t _len__t1654 = _t1653 ? _t1653->len : 0u;
        for (uint32_t _t1654 = 0; _t1654 < _len__t1654; ++_t1654) {
            gd::GdVal lv_buff = _t1653->data[_t1654];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), lv_buff, gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 3); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__RainbowBadge(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__RainbowBadge>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RainbowBadge = {CLS_Gd__gd_core_items__Exclusive__RainbowBadge, "RainbowBadge", "res://gd_core_items/Exclusive/RainbowBadge.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__RainbowBadge, &Gd__gd_core_items__Exclusive__RainbowBadge::get_static_prop_fn, &Gd__gd_core_items__Exclusive__RainbowBadge::call_static_fn};

void Gd__gd_core_items__Exclusive__Robodog::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_digUpItems = ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 25); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Stone", 5u)), gd::GdVal::from_int(4LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Garlic", 6u)), gd::GdVal::from_int(3LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Blueberries", 11u)), gd::GdVal::from_int(2LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Lump of Coal", 12u)), gd::GdVal::from_int(3LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Pocket Sand", 11u)), gd::GdVal::from_int(3LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Chipped Ruby", 12u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Chipped Sapphire", 16u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Chipped Emerald", 15u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Chipped Topaz", 13u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Chipped Amethyst", 16u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Healing Herbs", 13u)), gd::GdVal::from_float(0.5)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Bag of Stones", 13u)), gd::GdVal::from_float(0.5)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Walrus Tusk", 11u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Whetstone", 9u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Piggybank", 9u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Pan", 3u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Customer Card", 13u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Gloves of Haste", 15u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Dagger", 6u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Protective Purse", 16u)), gd::GdVal::from_float(0.1)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Flawed Ruby", 11u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Flawed Sapphire", 15u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Flawed Emerald", 14u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Flawed Topaz", 12u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Flawed Amethyst", 15u)), gd::GdVal::from_float(0.2)); return gd::GdVal::from_dict(d); })();
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
        case SYM_GEN_digUpItems_1883: out = this->f_digUpItems; return true;
        case SYM_GEN_spawnPos_1885: out = this->f_spawnPos; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_heat_1801: out = this->f_heat; return true;
        case SYM_GEN_cdIncrease_2375: out = this->f_cdIncrease; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Robodog::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_digUpItems_1883: this->f_digUpItems = val; return true;
        case SYM_GEN_spawnPos_1885: this->f_spawnPos = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_heat_1801: this->f_heat = val; return true;
        case SYM_GEN_cdIncrease_2375: this->f_cdIncrease = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Robodog::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onChargeReceived_2035: return true;
        case SYM_GEN_onChargeLeft_2036: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Robodog::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onChargeReceived_2035: out = fn_onChargeReceived(args, argc); return true;
        case SYM_GEN_onChargeLeft_2036: out = fn_onChargeLeft(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetBaseCooldown_111, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_numCharges, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Robodog::fn_onChargeLeft(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_numCharges, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Robodog::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_numCharges, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_baseCooldownOverride, this->f_cdIncrease)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBaseCooldown_110, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_cdIncrease = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cdincrease", 10u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Robodog(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Robodog>(&ctx); }
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
        case SYM_GEN_invuProcced_2398: out = this->f_invuProcced; return true;
        case SYM_GEN_gemDurFactor_2399: out = this->f_gemDurFactor; return true;
        case SYM_GEN_manaNeeded_1786: out = this->f_manaNeeded; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_buffTimer_1724: out = this->f_buffTimer; return true;
        case SYM_GEN_blind_1816: out = this->f_blind; return true;
        case SYM_GEN_manaNeeded_base_2400: out = this->f_manaNeeded_base; return true;
        case SYM_GEN_manaCostIncrease_2401: out = this->f_manaCostIncrease; return true;
        case SYM_GEN_maxUses_1991: out = this->f_maxUses; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ShinyMantle::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_invuProcced_2398: this->f_invuProcced = gd::gd_coerce_int(val); return true;
        case SYM_GEN_gemDurFactor_2399: this->f_gemDurFactor = gd::gd_coerce_float(val); return true;
        case SYM_GEN_manaNeeded_1786: this->f_manaNeeded = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_buffTimer_1724: this->f_buffTimer = val; return true;
        case SYM_GEN_blind_1816: this->f_blind = val; return true;
        case SYM_GEN_manaNeeded_base_2400: this->f_manaNeeded_base = val; return true;
        case SYM_GEN_manaCostIncrease_2401: this->f_manaCostIncrease = val; return true;
        case SYM_GEN_maxUses_1991: this->f_maxUses = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ShinyMantle::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_readyToFuse_751: return true;
        case SYM_GEN_onFusingFinished_848: return true;
        case SYM_GEN_getCounterValue_2256: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onInvuStarted_2402: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN_buffEnded_1722: return true;
        case SYM_GEN_onCombatEnd_134: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ShinyMantle::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_readyToFuse_751: out = fn_readyToFuse(args, argc); return true;
        case SYM_GEN_onFusingFinished_848: out = fn_onFusingFinished(args, argc); return true;
        case SYM_GEN_getCounterValue_2256: out = fn_getCounterValue(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onInvuStarted_2402: out = fn_onInvuStarted(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_buffEnded_1722: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_134: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isBag_85, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_readyToFuse(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, this->f_bondedIngredients, gd::SYM_empty, nullptr, 0)));
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
    gd::GdVal lv_inv = (gd::gd_truth(this->f_placed) ? (this->f_inventory) : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1284), SYM_GEN_INVENTORY_1093)));
    {
        gd::GdVal _t1655 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, lv_inv, SYM_GEN_getItemsAndGems_1513, nullptr, 0));
        gd::GdArr* _t1656 = (_t1655.kind == gd::GdVal::Kind::Arr) ? _t1655.arr : nullptr;
        uint32_t _len__t1657 = _t1656 ? _t1656->len : 0u;
        for (uint32_t _t1657 = 0; _t1657 < _len__t1657; ++_t1657) {
            gd::GdVal lv_item = _t1656->data[_t1657];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isGem_86, nullptr, 0))) {
                lv_gold = gd::gd_add(gd_ctx, lv_gold, gd::call_method(gd_ctx, lv_item, SYM_GEN_getPrice_394, nullptr, 0));
            }
        }
    }
    if (gd::gd_truth(this->f_dragged)) {
        {
            gd::GdVal _t1658 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_499, nullptr, 0));
            gd::GdArr* _t1659 = (_t1658.kind == gd::GdVal::Kind::Arr) ? _t1658.arr : nullptr;
            uint32_t _len__t1660 = _t1659 ? _t1659->len : 0u;
            for (uint32_t _t1660 = 0; _t1660 < _len__t1660; ++_t1660) {
                gd::GdVal lv_gem = _t1659->data[_t1660];
                lv_gold = gd::gd_add(gd_ctx, lv_gold, gd::call_method(gd_ctx, lv_gem, SYM_GEN_getPrice_394, nullptr, 0));
            }
        }
    }
    return lv_gold;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_invulnerable_start", 28u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onInvuStarted", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    this->f_manaNeeded = this->f_manaNeeded_base;
    this->f_invuProcced = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_gemDurFactor = gd::gd_coerce_float(gd::gd_floor(gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue_2256, nullptr, 0), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })())));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_isVulnerable_1275, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMana_1228, nullptr, 0), this->f_manaNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
        this->f_invuProcced = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_invuProcced, gd::GdVal::from_int(1LL)));
        gd::GdVal lv_invuDur = gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_base", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_bonus", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), this->f_gemDurFactor));
        (void)([&]() { gd::GdVal _ca[] = {lv_invuDur}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1685, _ca, 1); })();
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_invuDur, gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_makeInvulnerable_1195, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_manaNeeded, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_334, _ca, 2); })();
        this->f_manaNeeded = gd::gd_add(gd_ctx, this->f_manaNeeded, this->f_manaCostIncrease);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_invuProcced, this->f_maxUses)))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, nullptr, 0);
            return gd::GdVal::null();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_onInvuStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_blind, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_215, _ca, 2); })();
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
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1686, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BuffTimer", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffEnded", 9u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_137, _ca, 3); })();
    this->f_blind = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blind", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_manaNeeded_base = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "manat", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_manaCostIncrease = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_maxUses = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "max", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ShinyMantle(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ShinyMantle>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ShinyMantle = {CLS_Gd__gd_core_items__Exclusive__ShinyMantle, "ShinyMantle", "res://gd_core_items/Exclusive/ShinyMantle.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__ShinyMantle, &Gd__gd_core_items__Exclusive__ShinyMantle::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ShinyMantle::call_static_fn};

void Gd__gd_core_items__Exclusive__SpeakwithAnimals::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_petDescriptors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}));
    this->f_salesChance = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SpeakwithAnimals::meta() const { return &META_Gd__gd_core_items__Exclusive__SpeakwithAnimals; }
gd::GdVal Gd__gd_core_items__Exclusive__SpeakwithAnimals::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_pets_2429: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Rat", 3u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Squirrel", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Rat Chef", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Hedgehog", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Squirrel Archer", 15u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Hyper Hedgehog", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Carrot Goobert", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Snowmaster", 10u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Forest Dragon", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Toad", 4u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Poison Goobert", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Poison Frog", 11u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Ruby Chonk", 10u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Frog Prince", 11u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Crow", 4u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Ice Dragon", 10u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Courage Puppy", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Wisdom Puppy", 12u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Power Puppy", 11u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Armored Courage Puppy", 21u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Armored Wisdom Puppy", 20u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Armored Power Puppy", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Cheese Goobert", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Steel Dragon", 12u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Chili Goobert", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Fire Shelly", 11u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Phoenix", 7u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Phoenix2", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Emerald Whelp", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Sapphire Whelp", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Amethyst Whelp", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Obsidian Dragon", 15u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Cat Spirit", 10u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Owl Spirit", 10u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Badger Spirit", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Cupcake Goobert", 15u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Cupcake Dragon", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Broccoli Goobert", 16u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Dragon Knight", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Jynx Staff", 10u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Robodog", 7u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Toast Goobert", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Mecha Bat", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Thunder Drake", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Goobling", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Shelly", 6u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Steel Goobert", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Blood Goobert", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Ruby Whelp", 10u))}));
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
        case SYM_GEN_petDescriptors_2430: out = this->f_petDescriptors; return true;
        case SYM_GEN_salesChance_1997: out = this->f_salesChance; return true;
        case SYM_GEN_pets_2429: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SpeakwithAnimals::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_petDescriptors_2430: this->f_petDescriptors = val; return true;
        case SYM_GEN_salesChance_1997: this->f_salesChance = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SpeakwithAnimals::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onSaleRoll_1998: return true;
        case SYM_GEN_getGatedDescriptor_956: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_getRelatedItems_461: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN_getRelatedItemHeight_700: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SpeakwithAnimals::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onSaleRoll_1998: out = fn_onSaleRoll(args, argc); return true;
        case SYM_GEN_getGatedDescriptor_956: out = fn_getGatedDescriptor(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getRelatedItems_461: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_700: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Pet_2600)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpeakwithAnimals::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1661 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1662 = (_t1661.kind == gd::GdVal::Kind::Arr) ? _t1661.arr : nullptr;
        uint32_t _len__t1663 = _t1662 ? _t1662->len : 0u;
        for (uint32_t _t1663 = 0; _t1663 < _len__t1663; ++_t1663) {
            gd::GdVal lv_item = _t1662->data[_t1663];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveDoubleActivationChance_314, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpeakwithAnimals::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {this->f_petDescriptors}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_flatten_1708, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_salesChance = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "sale", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    {
        gd::GdVal _t1664 = gd::gd_iter_seq(gd_ctx.arena, Gd__gd_core_items__Exclusive__SpeakwithAnimals::get_static_const_or_enum(gd_ctx, SYM_GEN_pets_2429));
        gd::GdArr* _t1665 = (_t1664.kind == gd::GdVal::Kind::Arr) ? _t1664.arr : nullptr;
        uint32_t _len__t1666 = _t1665 ? _t1665->len : 0u;
        for (uint32_t _t1666 = 0; _t1666 < _len__t1666; ++_t1666) {
            gd::GdVal lv_pet = _t1665->data[_t1666];
            gd::GdVal lv_desc = ([&]() { gd::GdVal _ca[] = {lv_pet}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })();
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_desc, SYM_GEN_isReleased_1629, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_desc}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_petDescriptors, gd::call_method(gd_ctx, lv_desc, SYM_GEN_getRarity_238, nullptr, 0)), gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SpeakwithAnimals(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SpeakwithAnimals>(&ctx); }
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
        case SYM_GEN_staminaReduction_1918: out = this->f_staminaReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__StarofCourage::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaReduction_1918: this->f_staminaReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__StarofCourage::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__StarofCourage::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
        gd::GdVal _t1667 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1512, nullptr, 0));
        gd::GdArr* _t1668 = (_t1667.kind == gd::GdVal::Kind::Arr) ? _t1667.arr : nullptr;
        uint32_t _len__t1669 = _t1668 ? _t1668->len : 0u;
        for (uint32_t _t1669 = 0; _t1669 < _len__t1669; ++_t1669) {
            gd::GdVal lv_item = _t1668->data[_t1669];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isWeapon_84, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_staminaReduction}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeStaminaFactor_307, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StarofCourage::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_staminaReduction = gd::gd_neg(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__StarofCourage(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__StarofCourage>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StarofCourage = {CLS_Gd__gd_core_items__Exclusive__StarofCourage, "StarofCourage", "res://gd_core_items/Exclusive/StarofCourage.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__StarofCourage, &Gd__gd_core_items__Exclusive__StarofCourage::get_static_prop_fn, &Gd__gd_core_items__Exclusive__StarofCourage::call_static_fn};

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
        case SYM_GEN_damPerSpike_2487: out = this->f_damPerSpike; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Thornbloom::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikes_898: this->f_spikes = gd::gd_coerce_int(val); return true;
        case SYM_GEN_empower_998: this->f_empower = gd::gd_coerce_int(val); return true;
        case SYM_GEN_damPerSpike_2487: this->f_damPerSpike = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Thornbloom::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onSpikesChanged_944: return true;
        case SYM_GEN_onEmpowerChanged_2018: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Thornbloom::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onSpikesChanged_944: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN_onEmpowerChanged_2018: out = fn_onEmpowerChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Thornbloom::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Thornbloom::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_empower_changed", 25u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onEmpowerChanged", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_spikes_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onSpikesChanged", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Thornbloom::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_damPerSpike, lv_amount)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_164, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Thornbloom::fn_onEmpowerChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), lv_amount), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Thornbloom::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_211, _ca, 1); })();
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_empower}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 1); })();
        }
        else {
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Thornbloom::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_damPerSpike = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damperspike", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Thornbloom(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Thornbloom>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Thornbloom = {CLS_Gd__gd_core_items__Exclusive__Thornbloom, "Thornbloom", "res://gd_core_items/Exclusive/Thornbloom.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__Thornbloom, &Gd__gd_core_items__Exclusive__Thornbloom::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Thornbloom::call_static_fn};

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
        case SYM_GEN_boosted_2101: out = this->f_boosted; return true;
        case SYM_GEN_baseSpeed_2509: out = this->f_baseSpeed; return true;
        case SYM_GEN_bonusSpeed_1787: out = this->f_bonusSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__UniquelyUnique::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_boosted_2101: this->f_boosted = val; return true;
        case SYM_GEN_baseSpeed_2509: this->f_baseSpeed = val; return true;
        case SYM_GEN_bonusSpeed_1787: this->f_bonusSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__UniquelyUnique::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onBought_457: return true;
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_canAffect_secondary_289: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onItemRoll_1923: return true;
        case SYM_GEN_onItemRolled_1924: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__UniquelyUnique::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onBought_457: out = fn_onBought(args, argc); return true;
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_289: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemRoll_1923: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_1924: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_data, gd::GdVal::null())))) {
        this->f_boosted = lv_data;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UniquelyUnique::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UniquelyUnique::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, lv_item, SYM_GEN_getRarity_238, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Rarity_862), SYM_GEN_Unique_2757)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Platin Customer Card", 20u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })()}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_247, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Customer Card", 13u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })()}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_247, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UniquelyUnique::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_affectedItems = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_affectedItems, gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_baseSpeed, gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, _ca, 1); })(), this->f_bonusSpeed))}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, lv_affectedItems, gd::GdVal::from_int(0LL)), SYM_GEN_addSpeed_275, _ca, 1); })();
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
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_descr, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Customer Card", 13u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })())))) {
        this->f_boosted = gd::gd_sub(this->f_boosted, gd::GdVal::from_int(1LL));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UniquelyUnique::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_baseSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_bonusSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed2", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__UniquelyUnique(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__UniquelyUnique>(&ctx); }
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
        case SYM_GEN_options_1781: out = this->f_options; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Fanfare::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_options_1781: this->f_options = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Fanfare::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Fanfare::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_269, nullptr, 0), gd::GdVal::from_float(100.0)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Fanfare::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rng = ([&]() { gd::GdVal _ca[] = {this->f_options}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_pickRandomElement_1650, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_rng, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_rng, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeMana_336, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drainStamina_119, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    (void)([&]() { gd::GdVal _ca[] = {lv_rng}; return gd::call_method(gd_ctx, this->f_options, gd::SYM_erase, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Fanfare::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Fanfare(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Fanfare>(&ctx); }
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
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__HealingHerbs::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__HealingHerbs::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__HealingHerbs::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_383, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HealingHerbs::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__HealingHerbs(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__HealingHerbs>(&ctx); }
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
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_explodeRandomly_1826: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Piggybank::has_own_method(m);
}
bool Gd__gd_core_items__LuckyPiggy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_explodeRandomly_1826: out = fn_explodeRandomly(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canModifyChance_295, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyPiggy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1670 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1671 = (_t1670.kind == gd::GdVal::Kind::Arr) ? _t1670.arr : nullptr;
        uint32_t _len__t1672 = _t1671 ? _t1671->len : 0u;
        for (uint32_t _t1672 = 0; _t1672 < _len__t1672; ++_t1672) {
            gd::GdVal lv_item = _t1671->data[_t1672];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusChance_177, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyPiggy::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyPiggy::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_High_2603), gd::GdVal::from_int(5LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyPiggy::fn_explodeRandomly(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyPiggy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Piggybank::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__LuckyPiggy(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__LuckyPiggy>(&ctx); }
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
        case SYM_GEN_damageIncreaseActive_1868: out = this->f_damageIncreaseActive; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_poisonPerSpike_1869: out = this->f_poisonPerSpike; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__PoisonIvy::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damageIncreaseActive_1868: this->f_damageIncreaseActive = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_poisonPerSpike_1869: this->f_poisonPerSpike = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__PoisonIvy::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onSpikesChanged_944: return true;
        case SYM_GEN_onOpponentPoisonChanged_1736: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__PoisonIvy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onSpikesChanged_944: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN_onOpponentPoisonChanged_1736: out = fn_onOpponentPoisonChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Nature_2597)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonIvy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_spikes_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onSpikesChanged", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_poison_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentPoisonChanged", 23u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeDebuffResistChances_1204, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonIvy::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, this->f_poisonPerSpike), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_213, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonIvy::fn_onOpponentPoisonChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_curPoison = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_getPoison_1213, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_damageIncreaseActive))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_curPoison, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changeDamageResistance_1263, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(false), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonIvy::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_poisonPerSpike = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__PoisonIvy(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__PoisonIvy>(&ctx); }
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
        case SYM_GEN_affectedWeapons_1890: out = this->f_affectedWeapons; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__SteelGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedWeapons_1890: this->f_affectedWeapons = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__SteelGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_secondary_289: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onCombatEnd_134: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__SteelGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_secondary_289: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onCombatEnd_134: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_92, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__SteelGoobert::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1673 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, _ca, 1); })());
        gd::GdArr* _t1674 = (_t1673.kind == gd::GdVal::Kind::Arr) ? _t1673.arr : nullptr;
        uint32_t _len__t1675 = _t1674 ? _t1674->len : 0u;
        for (uint32_t _t1675 = 0; _t1675 < _len__t1675; ++_t1675) {
            gd::GdVal lv_item = _t1674->data[_t1675];
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, this->f_affectedWeapons, gd::SYM_push_back, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__SteelGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1676 = gd::gd_iter_seq(gd_ctx.arena, this->f_affectedWeapons);
        gd::GdArr* _t1677 = (_t1676.kind == gd::GdVal::Kind::Arr) ? _t1676.arr : nullptr;
        uint32_t _len__t1678 = _t1677 ? _t1677->len : 0u;
        for (uint32_t _t1678 = 0; _t1678 < _len__t1678; ++_t1678) {
            gd::GdVal lv_item = _t1677->data[_t1678];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_163, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__SteelGoobert::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_affectedWeapons, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__SteelGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__SteelGoobert(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__SteelGoobert>(&ctx); }
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
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__WalrusTusk::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__WalrusTusk::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__WalrusTusk::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_211, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_383, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__WalrusTusk::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__WalrusTusk(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__WalrusTusk>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__WalrusTusk = {CLS_Gd__gd_core_items__WalrusTusk, "WalrusTusk", "res://gd_core_items/WalrusTusk.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__WalrusTusk, &Gd__gd_core_items__WalrusTusk::get_static_prop_fn, &Gd__gd_core_items__WalrusTusk::call_static_fn};
