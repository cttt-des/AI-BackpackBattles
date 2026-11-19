#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core__Food.hpp"
#include "../hdrs/Gd__gd_core__BurningTorch.hpp"
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
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_prepare_120: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Food::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_prepare_120: out = fn_prepare(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Food_2604)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), this->f_descriptor)))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Food::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_prepare_120, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0), gd::GdVal::from_float(0.1))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Food::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_permDamBonus_993: out = this->f_permDamBonus; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__BurningTorch::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_permDamBonus_993: this->f_permDamBonus = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__BurningTorch::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__BurningTorch::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__BurningTorch::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__BurningTorch::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BurningTorch::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_permDamBonus}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_159, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BurningTorch::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_permDamBonus = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0);
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
        case SYM_GEN_filledCells_1507: out = this->f_filledCells; return true;
        case SYM_GEN_bagCells_1508: out = this->f_bagCells; return true;
        case SYM_GEN_items_1088: out = this->f_items; return true;
        case SYM_GEN_character_72: out = this->f_character; return true;
        case SYM_GEN_curHovered_1509: out = this->f_curHovered; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreGrid::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_filledCells_1507: this->f_filledCells = val; return true;
        case SYM_GEN_bagCells_1508: this->f_bagCells = val; return true;
        case SYM_GEN_items_1088: this->f_items = val; return true;
        case SYM_GEN_character_72: this->f_character = val; return true;
        case SYM_GEN_curHovered_1509: this->f_curHovered = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreGrid::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_getCellsForGlobalPositions_399: return true;
        case SYM_GEN_getItems_1510: return true;
        case SYM_GEN_getItemsAndGems_1511: return true;
        case SYM_GEN_isHovered_710: return true;
        case SYM_GEN_isCellEmpty_1512: return true;
        case SYM_GEN_getEmptyCellsInCells_1513: return true;
        case SYM_GEN_getItemInCell_1514: return true;
        case SYM_GEN_getItemsInCells_1515: return true;
        case SYM_GEN_countItemsInCells_1516: return true;
        case SYM_GEN_getBagsInCells_1517: return true;
        case SYM_GEN_getAdjacentItems_1520: return true;
        case SYM_GEN_countSocketedGems_1521: return true;
        case SYM_GEN_changeBuffPower_allItems_1522: return true;
        case SYM_GEN_changeBuffAmplification_allItems_1523: return true;
        case SYM_GEN_addItemCells_1524: return true;
        case SYM_GEN_addItem_1525: return true;
        case SYM_GEN_removeItem_1526: return true;
        case SYM_GEN_clearItemCells_1527: return true;
        case SYM_GEN_moveItem_1528: return true;
        case SYM_GEN_onItemTypeChanged_456: return true;
        case SYM_GEN_cleanUp_1529: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreGrid::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_getCellsForGlobalPositions_399: out = fn_getCellsForGlobalPositions(args, argc); return true;
        case SYM_GEN_getItems_1510: out = fn_getItems(args, argc); return true;
        case SYM_GEN_getItemsAndGems_1511: out = fn_getItemsAndGems(args, argc); return true;
        case SYM_GEN_isHovered_710: out = fn_isHovered(args, argc); return true;
        case SYM_GEN_isCellEmpty_1512: out = fn_isCellEmpty(args, argc); return true;
        case SYM_GEN_getEmptyCellsInCells_1513: out = fn_getEmptyCellsInCells(args, argc); return true;
        case SYM_GEN_getItemInCell_1514: out = fn_getItemInCell(args, argc); return true;
        case SYM_GEN_getItemsInCells_1515: out = fn_getItemsInCells(args, argc); return true;
        case SYM_GEN_countItemsInCells_1516: out = fn_countItemsInCells(args, argc); return true;
        case SYM_GEN_getBagsInCells_1517: out = fn_getBagsInCells(args, argc); return true;
        case SYM_GEN_getCellsInLine_1518: out = sf_getCellsInLine(gd_ctx, args, argc); return true;
        case SYM_GEN_getAdjacentCells_1519: out = sf_getAdjacentCells(gd_ctx, args, argc); return true;
        case SYM_GEN_getAdjacentItems_1520: out = fn_getAdjacentItems(args, argc); return true;
        case SYM_GEN_countSocketedGems_1521: out = fn_countSocketedGems(args, argc); return true;
        case SYM_GEN_changeBuffPower_allItems_1522: out = fn_changeBuffPower_allItems(args, argc); return true;
        case SYM_GEN_changeBuffAmplification_allItems_1523: out = fn_changeBuffAmplification_allItems(args, argc); return true;
        case SYM_GEN_addItemCells_1524: out = fn_addItemCells(args, argc); return true;
        case SYM_GEN_addItem_1525: out = fn_addItem(args, argc); return true;
        case SYM_GEN_removeItem_1526: out = fn_removeItem(args, argc); return true;
        case SYM_GEN_clearItemCells_1527: out = fn_clearItemCells(args, argc); return true;
        case SYM_GEN_moveItem_1528: out = fn_moveItem(args, argc); return true;
        case SYM_GEN_onItemTypeChanged_456: out = fn_onItemTypeChanged(args, argc); return true;
        case SYM_GEN_cleanUp_1529: out = fn_cleanUp(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreGrid::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getCellsInLine_1518: out = sf_getCellsInLine(gd_ctx, args, argc); return true;
        case SYM_GEN_getAdjacentCells_1519: out = sf_getAdjacentCells(gd_ctx, args, argc); return true;
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
        gd::GdVal _t1555 = gd::gd_iter_seq(gd_ctx.arena, this->f_items);
        gd::GdArr* _t1556 = (_t1555.kind == gd::GdVal::Kind::Arr) ? _t1555.arr : nullptr;
        uint32_t _len__t1557 = _t1556 ? _t1556->len : 0u;
        for (uint32_t _t1557 = 0; _t1557 < _len__t1557; ++_t1557) {
            gd::GdVal lv_item = _t1556->data[_t1557];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, lv_item, SYM_GEN_getGemsNoNull_495, nullptr, 0)}; return gd::call_method(gd_ctx, lv_itemsAndGems, gd::SYM_append_array, _ca, 1); })();
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
        gd::GdVal _t1558 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t1559 = (_t1558.kind == gd::GdVal::Kind::Arr) ? _t1558.arr : nullptr;
        uint32_t _len__t1560 = _t1559 ? _t1559->len : 0u;
        for (uint32_t _t1560 = 0; _t1560 < _len__t1560; ++_t1560) {
            gd::GdVal lv_cell = _t1559->data[_t1560];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCellEmpty_1512, _ca, 1); })())) {
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
        gd::GdVal _t1561 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t1562 = (_t1561.kind == gd::GdVal::Kind::Arr) ? _t1561.arr : nullptr;
        uint32_t _len__t1563 = _t1562 ? _t1562->len : 0u;
        for (uint32_t _t1563 = 0; _t1563 < _len__t1563; ++_t1563) {
            gd::GdVal lv_cell = _t1562->data[_t1563];
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
        gd::GdVal _t1564 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t1565 = (_t1564.kind == gd::GdVal::Kind::Arr) ? _t1564.arr : nullptr;
        uint32_t _len__t1566 = _t1565 ? _t1565->len : 0u;
        for (uint32_t _t1566 = 0; _t1566 < _len__t1566; ++_t1566) {
            gd::GdVal lv_cell = _t1565->data[_t1566];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::call_method(gd_ctx, this->f_filledCells, gd::SYM_has, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_itemCounter, gd::get_index(gd_ctx, this->f_filledCells, lv_cell)}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictAdd_1693, _ca, 2); })();
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
        gd::GdVal _t1567 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t1568 = (_t1567.kind == gd::GdVal::Kind::Arr) ? _t1567.arr : nullptr;
        uint32_t _len__t1569 = _t1568 ? _t1568->len : 0u;
        for (uint32_t _t1569 = 0; _t1569 < _len__t1569; ++_t1569) {
            gd::GdVal lv_cell = _t1568->data[_t1569];
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
        gd::GdVal _t1570 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t1571 = (_t1570.kind == gd::GdVal::Kind::Arr) ? _t1570.arr : nullptr;
        uint32_t _len__t1572 = _t1571 ? _t1571->len : 0u;
        for (uint32_t _t1572 = 0; _t1572 < _len__t1572; ++_t1572) {
            gd::GdVal lv_cell = _t1571->data[_t1572];
            {
                gd::GdVal _t1573 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::gd_add(gd_ctx, lv_distance, gd::GdVal::from_int(1LL))}; return gd::gd_range(gd_ctx.arena, _ca, 2); })());
                gd::GdArr* _t1574 = (_t1573.kind == gd::GdVal::Kind::Arr) ? _t1573.arr : nullptr;
                uint32_t _len__t1575 = _t1574 ? _t1574->len : 0u;
                for (uint32_t _t1575 = 0; _t1575 < _len__t1575; ++_t1575) {
                    gd::GdVal lv_offset = _t1574->data[_t1575];
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
        gd::GdVal _t1576 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t1577 = (_t1576.kind == gd::GdVal::Kind::Arr) ? _t1576.arr : nullptr;
        uint32_t _len__t1578 = _t1577 ? _t1577->len : 0u;
        for (uint32_t _t1578 = 0; _t1578 < _len__t1578; ++_t1578) {
            gd::GdVal lv_cell = _t1577->data[_t1578];
            {
                gd::GdVal _t1579 = gd::gd_iter_seq(gd_ctx.arena, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2(1.0, 0.0), gd::GdVal::from_vec2(-1.0, 0.0), gd::GdVal::from_vec2(0.0, -1.0), gd::GdVal::from_vec2(0.0, 1.0)})));
                gd::GdArr* _t1580 = (_t1579.kind == gd::GdVal::Kind::Arr) ? _t1579.arr : nullptr;
                uint32_t _len__t1581 = _t1580 ? _t1580->len : 0u;
                for (uint32_t _t1581 = 0; _t1581 < _len__t1581; ++_t1581) {
                    gd::GdVal lv_offset = _t1580->data[_t1581];
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
    return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, lv_item, SYM_GEN_occupiedCells_50)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreGrid::call_static_fn(gd_ctx, SYM_GEN_getAdjacentCells_1519, _ca, 1, _out); return _out; })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInCells_1515, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_countSocketedGems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numGems = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t1582 = gd::gd_iter_seq(gd_ctx.arena, this->f_items);
        gd::GdArr* _t1583 = (_t1582.kind == gd::GdVal::Kind::Arr) ? _t1582.arr : nullptr;
        uint32_t _len__t1584 = _t1583 ? _t1583->len : 0u;
        for (uint32_t _t1584 = 0; _t1584 < _len__t1584; ++_t1584) {
            gd::GdVal lv_item = _t1583->data[_t1584];
            lv_numGems = gd::gd_add(gd_ctx, lv_numGems, gd::call_method(gd_ctx, gd::call_method(gd_ctx, lv_item, SYM_GEN_getGemsNoNull_495, nullptr, 0), gd::SYM_size, nullptr, 0));
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
        gd::GdVal _t1585 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsAndGems_1511, nullptr, 0));
        gd::GdArr* _t1586 = (_t1585.kind == gd::GdVal::Kind::Arr) ? _t1585.arr : nullptr;
        uint32_t _len__t1587 = _t1586 ? _t1586->len : 0u;
        for (uint32_t _t1587 = 0; _t1587 < _len__t1587; ++_t1587) {
            gd::GdVal lv_item = _t1586->data[_t1587];
            (void)([&]() { gd::GdVal _ca[] = {lv_buffType, lv_amount}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveBuffPower_301, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_changeBuffAmplification_allItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    {
        gd::GdVal _t1588 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsAndGems_1511, nullptr, 0));
        gd::GdArr* _t1589 = (_t1588.kind == gd::GdVal::Kind::Arr) ? _t1588.arr : nullptr;
        uint32_t _len__t1590 = _t1589 ? _t1589->len : 0u;
        for (uint32_t _t1590 = 0; _t1590 < _len__t1590; ++_t1590) {
            gd::GdVal lv_item = _t1589->data[_t1590];
            (void)([&]() { gd::GdVal _ca[] = {lv_buffType, lv_amount}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_194, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_addItemCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isBag_81, nullptr, 0))) {
        {
            gd::GdVal _t1591 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
            gd::GdArr* _t1592 = (_t1591.kind == gd::GdVal::Kind::Arr) ? _t1591.arr : nullptr;
            uint32_t _len__t1593 = _t1592 ? _t1592->len : 0u;
            for (uint32_t _t1593 = 0; _t1593 < _len__t1593; ++_t1593) {
                gd::GdVal lv_cell = _t1592->data[_t1593];
                { gd::GdVal _t1594 = this->f_bagCells; gd::GdVal _t1595 = lv_cell; gd::set_index(gd_ctx, _t1594, _t1595, lv_item); }
            }
        }
    }
    else {
        {
            gd::GdVal _t1596 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
            gd::GdArr* _t1597 = (_t1596.kind == gd::GdVal::Kind::Arr) ? _t1596.arr : nullptr;
            uint32_t _len__t1598 = _t1597 ? _t1597->len : 0u;
            for (uint32_t _t1598 = 0; _t1598 < _len__t1598; ++_t1598) {
                gd::GdVal lv_cell = _t1597->data[_t1598];
                { gd::GdVal _t1599 = this->f_filledCells; gd::GdVal _t1600 = lv_cell; gd::set_index(gd_ctx, _t1599, _t1600, lv_item); }
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
    (void)([&]() { gd::GdVal _ca[] = {lv_item, lv_cells}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addItemCells_1524, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, this->f_items, gd::SYM_push_back, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_cells, lv_placedByPlayer}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addToInventory_118, _ca, 3); })();
    {
        gd::GdVal _t1601 = gd::gd_iter_seq(gd_ctx.arena, this->f_items);
        gd::GdArr* _t1602 = (_t1601.kind == gd::GdVal::Kind::Arr) ? _t1601.arr : nullptr;
        uint32_t _len__t1603 = _t1602 ? _t1602->len : 0u;
        for (uint32_t _t1603 = 0; _t1603 < _len__t1603; ++_t1603) {
            gd::GdVal lv_other = _t1602->data[_t1603];
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, lv_other, SYM_GEN_onItemAdded_435, _ca, 1); })();
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
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearItemCells_1527, _ca, 1); })();
    gd::GdVal lv_idx = ([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, this->f_items, gd::SYM_find, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_idx, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_idx}; return gd::call_method(gd_ctx, this->f_items, gd::SYM_remove, _ca, 1); })();
    }
    {
        gd::GdVal _t1604 = gd::gd_iter_seq(gd_ctx.arena, this->f_items);
        gd::GdArr* _t1605 = (_t1604.kind == gd::GdVal::Kind::Arr) ? _t1604.arr : nullptr;
        uint32_t _len__t1606 = _t1605 ? _t1605->len : 0u;
        for (uint32_t _t1606 = 0; _t1606 < _len__t1606; ++_t1606) {
            gd::GdVal lv_other = _t1605->data[_t1606];
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, lv_other, SYM_GEN_onItemRemoved_436, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_clearItemCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1607 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, lv_item, SYM_GEN_occupiedCells_50));
        gd::GdArr* _t1608 = (_t1607.kind == gd::GdVal::Kind::Arr) ? _t1607.arr : nullptr;
        uint32_t _len__t1609 = _t1608 ? _t1608->len : 0u;
        for (uint32_t _t1609 = 0; _t1609 < _len__t1609; ++_t1609) {
            gd::GdVal lv_cell = _t1608->data[_t1609];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isBag_81, nullptr, 0))) {
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
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearItemCells_1527, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_item, lv_newCells}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addItemCells_1524, _ca, 2); })();
    gd::set_prop(gd_ctx, lv_item, SYM_GEN_occupiedCells_50, lv_newCells);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreGrid::fn_onItemTypeChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1610 = gd::gd_iter_seq(gd_ctx.arena, this->f_items);
        gd::GdArr* _t1611 = (_t1610.kind == gd::GdVal::Kind::Arr) ? _t1610.arr : nullptr;
        uint32_t _len__t1612 = _t1611 ? _t1611->len : 0u;
        for (uint32_t _t1612 = 0; _t1612 < _len__t1612; ++_t1612) {
            gd::GdVal lv_other = _t1611->data[_t1612];
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, lv_other, SYM_GEN_onItemTypeChanged_456, _ca, 1); })();
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
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN_onOpponentDebuffsChanged_1727: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Dagger::has_own_method(m);
}
bool Gd__gd_core__CursedDagger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onOpponentDebuffsChanged_1727: out = fn_onOpponentDebuffsChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canDamage_87, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CursedDagger::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentDebuffsChanged", 24u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToOpponentDebuffs_374, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CursedDagger::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictRandomDebuffs_355, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CursedDagger::fn_onOpponentDebuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_extraCritChance = gd::gd_mul(lv_amount, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0));
    gd::GdVal lv_extraAccuracy = gd::gd_mul(lv_amount, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0));
    (void)([&]() { gd::GdVal _ca[] = {lv_extraCritChance}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addCritChancePercent_177, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_extraAccuracy}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addAccuracy_175, _ca, 1); })();
    {
        gd::GdVal _t1613 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1614 = (_t1613.kind == gd::GdVal::Kind::Arr) ? _t1613.arr : nullptr;
        uint32_t _len__t1615 = _t1614 ? _t1614->len : 0u;
        for (uint32_t _t1615 = 0; _t1615 < _len__t1615; ++_t1615) {
            gd::GdVal lv_item = _t1614->data[_t1615];
            (void)([&]() { gd::GdVal _ca[] = {lv_extraCritChance}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addCritChancePercent_177, _ca, 1); })();
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isWeapon_80, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_extraAccuracy}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addAccuracy_175, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CursedDagger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Dagger::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_getCraftingOffset_846: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__FalconBlade::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getCraftingOffset_846: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_93, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__FalconBlade::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1616 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1617 = (_t1616.kind == gd::GdVal::Kind::Arr) ? _t1616.arr : nullptr;
        uint32_t _len__t1618 = _t1617 ? _t1617->len : 0u;
        for (uint32_t _t1618 = 0; _t1618 < _len__t1618; ++_t1618) {
            gd::GdVal lv_item = _t1617->data[_t1618];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0), gd::GdVal::from_int(100LL))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__FalconBlade::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_114, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1276), SYM_GEN_Sufficient_2603))))) {
        gd::GdVal lv_res = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_218, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 2); })();
        gd::GdVal lv_res2 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_218, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res2, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 2); })();
        gd::GdVal lv_hits = gd::GdVal::from_int(0LL);
        if (gd::gd_truth(gd::call_method(gd_ctx, lv_res, SYM_GEN_hasHit_1430, nullptr, 0))) {
            lv_hits = gd::gd_add(gd_ctx, lv_hits, gd::GdVal::from_int(1LL));
        }
        if (gd::gd_truth(gd::call_method(gd_ctx, lv_res2, SYM_GEN_hasHit_1430, nullptr, 0))) {
            lv_hits = gd::gd_add(gd_ctx, lv_hits, gd::GdVal::from_int(1LL));
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(30.0)), gd::GdVal::from_float(30.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), SYM_GEN_bare_randf_range_1645, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(100.0)), gd::GdVal::from_float(100.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), SYM_GEN_bare_randf_range_1645, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(5.0)), gd::GdVal::from_float(5.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), SYM_GEN_bare_randf_range_1645, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__FalconBlade::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1619 = lv_forDirection;
        if (gd::gd_eq(_t1619, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
        else if (gd::gd_eq(_t1619, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
        else if (gd::gd_eq(_t1619, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::gd_eq(_t1619, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__FalconBlade::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__FalconBlade(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__FalconBlade>(&ctx); }
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
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_getCraftingOffset_846: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__HeroLongsword::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_getCraftingOffset_846: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeroLongsword::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1620 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1621 = (_t1620.kind == gd::GdVal::Kind::Arr) ? _t1620.arr : nullptr;
        uint32_t _len__t1622 = _t1621 ? _t1621->len : 0u;
        for (uint32_t _t1622 = 0; _t1622 < _len__t1622; ++_t1622) {
            gd::GdVal lv_item = _t1621->data[_t1622];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_159, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeroLongsword::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1623 = lv_forDirection;
        if (gd::gd_eq(_t1623, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
        else if (gd::gd_eq(_t1623, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
        else if (gd::gd_eq(_t1623, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::gd_eq(_t1623, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeroLongsword::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__HeroLongsword(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__HeroLongsword>(&ctx); }
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
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_explodeRandomly_1825: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Piggybank::has_own_method(m);
}
bool Gd__gd_core__LuckyPiggy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_explodeRandomly_1825: out = fn_explodeRandomly(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canModifyChance_291, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyPiggy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1624 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1625 = (_t1624.kind == gd::GdVal::Kind::Arr) ? _t1624.arr : nullptr;
        uint32_t _len__t1626 = _t1625 ? _t1625->len : 0u;
        for (uint32_t _t1626 = 0; _t1626 < _len__t1626; ++_t1626) {
            gd::GdVal lv_item = _t1625->data[_t1626];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusChance_173, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyPiggy::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyPiggy::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_852), SYM_GEN_High_2601), gd::GdVal::from_int(5LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyPiggy::fn_explodeRandomly(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyPiggy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Piggybank::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__PocketSand::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__PocketSand::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__PocketSand::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_211, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_379, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PocketSand::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_blockFactor_1881: out = this->f_blockFactor; return true;
        default: break;
    }
    return Gd__gd_core__Shield::get_prop(prop, out);
}
bool Gd__gd_core__ShieldofValor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockFactor_1881: this->f_blockFactor = val; return true;
        default: break;
    }
    return Gd__gd_core__Shield::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__ShieldofValor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_afterBlock_1846: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Shield::has_own_method(m);
}
bool Gd__gd_core__ShieldofValor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_afterBlock_1846: out = fn_afterBlock(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBlock_289, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ShieldofValor::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1627 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1628 = (_t1627.kind == gd::GdVal::Kind::Arr) ? _t1627.arr : nullptr;
        uint32_t _len__t1629 = _t1628 ? _t1628->len : 0u;
        for (uint32_t _t1629 = 0; _t1629 < _len__t1629; ++_t1629) {
            gd::GdVal lv_item = _t1628->data[_t1629];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Block_2563), this->f_blockFactor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveBuffPower_301, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ShieldofValor::fn_afterBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0), gd::get_prop(gd_ctx, this->f_blockedDamageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drainStamina_115, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ShieldofValor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Shield::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_blockFactor = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_onTriggerPotion_1753: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__HealthPotion::has_own_method(m);
}
bool Gd__gd_core__StrongHealthPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1753: out = fn_onTriggerPotion(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__HealthPotion::call_method(gd_ctx, SYM_GEN_onTriggerPotion_1753, _ca, 1, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StrongHealthPotion::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_852), SYM_GEN_High_2601), gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StrongHealthPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__HealthPotion::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_snowflakes_1907: out = this->f_snowflakes; return true;
        case SYM_GEN_damReduction_1777: out = this->f_damReduction; return true;
        default: break;
    }
    return Gd__gd_core__Card::get_prop(prop, out);
}
bool Gd__gd_core__White_EyesBlueDragon::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_snowflakes_1907: this->f_snowflakes = val; return true;
        case SYM_GEN_damReduction_1777: this->f_damReduction = val; return true;
        default: break;
    }
    return Gd__gd_core__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__White_EyesBlueDragon::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doRevealEffect_889: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Card::has_own_method(m);
}
bool Gd__gd_core__White_EyesBlueDragon::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doRevealEffect_889: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__White_EyesBlueDragon::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__White_EyesBlueDragon::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_202, nullptr, 0), gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0), this->f_chainPosition))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_349, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_changeEffectDamageFactor_1261, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__White_EyesBlueDragon::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Card::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_damReduction = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damfactor", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_activations_931: out = this->f_activations; return true;
        case SYM_GEN_goobertAnimation_932: out = this->f_goobertAnimation; return true;
        case SYM_GEN_activationsToTrigger_933: out = this->f_activationsToTrigger; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Goobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activations_931: this->f_activations = gd::gd_coerce_int(val); return true;
        case SYM_GEN_goobertAnimation_932: this->f_goobertAnimation = val; return true;
        case SYM_GEN_activationsToTrigger_933: this->f_activationsToTrigger = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Goobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_logCooldown_755: return true;
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_prepare_120: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onItemActivated_934: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Goobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_logCooldown_755: out = fn_logCooldown(args, argc); return true;
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_prepare_120: out = fn_prepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onItemActivated_934: out = fn_onItemActivated(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canActivate_89, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Goobert::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_activations = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_iterationCooldown = gd::gd_coerce_float(this->f_activationsToTrigger);
    this->f_triggerTime = gd::gd_coerce_float(this->f_iterationCooldown);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1365), SYM_GEN_Cooldown_2545)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1377), SYM_GEN_snapshotItemTooltipStat_1351, _ca, 2); })();
    {
        gd::GdVal _t1630 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1631 = (_t1630.kind == gd::GdVal::Kind::Arr) ? _t1630.arr : nullptr;
        uint32_t _len__t1632 = _t1631 ? _t1631->len : 0u;
        for (uint32_t _t1632 = 0; _t1632 < _len__t1632; ++_t1632) {
            gd::GdVal lv_item = _t1631->data[_t1632];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onItemActivated", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        }
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_prepare_120, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Goobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Goobert::fn_onItemActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_activations = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_activations, gd::GdVal::from_int(1LL)));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_activations, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0))))) {
        this->f_activations = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCooldownEffect_142, nullptr, 0);
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_doubleActivationChance, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_doubleActivationChance}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_flip_1637, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCooldownEffect_142, nullptr, 0);
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, this->f_activations, this->f_activationsToTrigger), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_789, _ca, 2); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, this->f_activations, this->f_activationsToTrigger), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_789, _ca, 2); })();
    }
    this->f_triggerTime = gd::gd_coerce_float(gd::gd_sub(this->f_activationsToTrigger, this->f_activations));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1365), SYM_GEN_Cooldown_2545), gd::GdVal::null(), gd::GdVal::from_bool(false), lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1377), SYM_GEN_snapshotItemTooltipStat_1351, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Goobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_activationsToTrigger = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0);
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
        case SYM_GEN_movedDebuffs_1716: out = this->f_movedDebuffs; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__CorruptedArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_movedDebuffs_1716: this->f_movedDebuffs = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__CorruptedArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_reactToItemTypeChange_455: return true;
        case SYM_GEN_onAffectedItemAdded_433: return true;
        case SYM_GEN_onAffectedItemRemoved_434: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__CorruptedArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_reactToItemTypeChange_455: out = fn_reactToItemTypeChange(args, argc); return true;
        case SYM_GEN_onAffectedItemAdded_433: out = fn_onAffectedItemAdded(args, argc); return true;
        case SYM_GEN_onAffectedItemRemoved_434: out = fn_onAffectedItemRemoved(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Dark_2600)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CorruptedArmor::fn_reactToItemTypeChange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::gd_in(lv_item, gd::get_index(gd_ctx, this->f_currentAffectedItems, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580))))) {
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Dark_2600), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasDynamicType_239, _ca, 2); })())) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_currentAffectedItems, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580)), gd::SYM_erase, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemRemoved_434, _ca, 2); })();
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
    if (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Dark_2600)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Dark_2600), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addDynamicType_240, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CorruptedArmor::fn_onAffectedItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Dark_2600), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_removeDynamicType_241, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CorruptedArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, nullptr, 0);
    gd::GdVal lv_debuffProtectionChance = gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0));
    (void)([&]() { gd::GdVal _ca[] = {lv_debuffProtectionChance}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_changeDebuffProtectionChance_1267, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CorruptedArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_cleansedDebuffs = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1358, nullptr, 0), this->f_movedDebuffs, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_pickRandomStacks_356, _ca, 3); })();
    {
        gd::GdVal _t1633 = gd::gd_iter_seq(gd_ctx.arena, lv_cleansedDebuffs);
        gd::GdArr* _t1634 = (_t1633.kind == gd::GdVal::Kind::Arr) ? _t1633.arr : nullptr;
        uint32_t _len__t1635 = _t1634 ? _t1634->len : 0u;
        for (uint32_t _t1635 = 0; _t1635 < _len__t1635; ++_t1635) {
            gd::GdVal lv_debuff = _t1634->data[_t1635];
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_debuff, gd::get_index(gd_ctx, lv_cleansedDebuffs, lv_debuff), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_loseStacks_1027, _ca, 3); })();
            if (gd::gd_truth(lv_event)) {
                gd::GdVal lv_actuallyCleansed = gd::gd_neg(gd::call_method(gd_ctx, lv_event, SYM_GEN_getAmount_1483, nullptr, 0));
                (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), lv_debuff, lv_actuallyCleansed, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_199, _ca, 4); })();
            }
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CorruptedArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_movedDebuffs = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0));
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
        case SYM_GEN_nullifyApplied_1775: out = this->f_nullifyApplied; return true;
        case SYM_GEN_buffsActive_1776: out = this->f_buffsActive; return true;
        case SYM_GEN_buffTimer_1723: out = this->f_buffTimer; return true;
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        case SYM_GEN_damReduction_1777: out = this->f_damReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__EvilCap::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_nullifyApplied_1775: this->f_nullifyApplied = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_buffsActive_1776: this->f_buffsActive = val; return true;
        case SYM_GEN_buffTimer_1723: this->f_buffTimer = val; return true;
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        case SYM_GEN_damReduction_1777: this->f_damReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__EvilCap::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onPreCombatStart_123: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_buffEnded_1721: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__EvilCap::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreCombatStart_123: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_buffEnded_1721: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__EvilCap::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__EvilCap::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_reduceHealingEfficiency_1163, _ca, 1); })();
    this->f_nullifyApplied = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__EvilCap::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeDamageResistance_1259, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__EvilCap::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_nullifyApplied)))) {
        this->f_nullifyApplied = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_changeBuffNullifyChances_1268, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1683, _ca, 1); })();
    this->f_buffsActive = gd::gd_add(gd_ctx, this->f_buffsActive, gd::GdVal::from_int(1LL));
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__EvilCap::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeDamageResistance_1259, _ca, 1); })();
    this->f_buffsActive = gd::gd_sub(this->f_buffsActive, gd::GdVal::from_int(1LL));
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__EvilCap::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__EvilCap::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_buffsActive = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BuffTimer", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffEnded", 9u)), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_133, _ca, 3); })();
    this->f_damReduction = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0);
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
        case SYM_GEN_hasActivated_1810: out = this->f_hasActivated; return true;
        case SYM_GEN_speedTimer_1943: out = this->f_speedTimer; return true;
        case SYM_GEN_healthThreshold_1758: out = this->f_healthThreshold; return true;
        case SYM_GEN_manaNeeded_1785: out = this->f_manaNeeded; return true;
        case SYM_GEN_luck_893: out = this->f_luck; return true;
        case SYM_GEN_empower_994: out = this->f_empower; return true;
        case SYM_GEN_bonusSpeed_1786: out = this->f_bonusSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ArcaneBoots::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hasActivated_1810: this->f_hasActivated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_speedTimer_1943: this->f_speedTimer = val; return true;
        case SYM_GEN_healthThreshold_1758: this->f_healthThreshold = val; return true;
        case SYM_GEN_manaNeeded_1785: this->f_manaNeeded = val; return true;
        case SYM_GEN_luck_893: this->f_luck = val; return true;
        case SYM_GEN_empower_994: this->f_empower = val; return true;
        case SYM_GEN_bonusSpeed_1786: this->f_bonusSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ArcaneBoots::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onDamaged_1759: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_onSpeedTimerTimeout_1944: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ArcaneBoots::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1759: out = fn_onDamaged(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_onSpeedTimerTimeout_1944: out = fn_onSpeedTimerTimeout(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_93, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneBoots::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDamaged", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneBoots::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(this->f_hasActivated)) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getRelativeHealth_300, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getMana_1224, nullptr, 0), this->f_manaNeeded)))) {
            this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
            gd::GdVal lv_event2 = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_330, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_luck, lv_event2}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_empower, lv_event2}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_202, nullptr, 0), gd::GdVal::from_bool(true), lv_event2}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, _ca, 3); })();
            {
                gd::GdVal _t1636 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
                gd::GdArr* _t1637 = (_t1636.kind == gd::GdVal::Kind::Arr) ? _t1636.arr : nullptr;
                uint32_t _len__t1638 = _t1637 ? _t1637->len : 0u;
                for (uint32_t _t1638 = 0; _t1638 < _len__t1638; ++_t1638) {
                    gd::GdVal lv_item = _t1637->data[_t1638];
                    (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
                }
            }
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_speed", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_speedTimer, SYM_GEN_start_1683, _ca, 1); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_379, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneBoots::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_852), SYM_GEN_High_2601), gd::GdVal::from_int(2LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneBoots::fn_onSpeedTimerTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1639 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1640 = (_t1639.kind == gd::GdVal::Kind::Arr) ? _t1639.arr : nullptr;
        uint32_t _len__t1641 = _t1640 ? _t1640->len : 0u;
        for (uint32_t _t1641 = 0; _t1641 < _len__t1641; ++_t1641) {
            gd::GdVal lv_item = _t1640->data[_t1641];
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_272, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneBoots::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_speedTimer, SYM_GEN_stop_1684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArcaneBoots::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_speedTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "SpeedTimer", 10u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onSpeedTimerTimeout", 19u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_133, _ca, 3); })();
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healtht", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "manat", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_bonusSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_chargeCells_1959: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(2LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(3LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(4LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(5LL))).as_float())}));
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
        case SYM_GEN_flatSpeed_1960: out = this->f_flatSpeed; return true;
        case SYM_GEN_speedPerTile_1961: out = this->f_speedPerTile; return true;
        case SYM_GEN_chargeCells_1959: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Battery::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_flatSpeed_1960: this->f_flatSpeed = val; return true;
        case SYM_GEN_speedPerTile_1961: this->f_speedPerTile = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Battery::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_lightning_287: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_emitCharge_1962: return true;
        case SYM_GEN_onChargeEnteredCell_1963: return true;
        case SYM_GEN_chargedItemStatChange_1964: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Battery::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_lightning_287: out = fn_canAffect_lightning(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_emitCharge_1962: out = fn_emitCharge(args, argc); return true;
        case SYM_GEN_onChargeEnteredCell_1963: out = fn_onChargeEnteredCell(args, argc); return true;
        case SYM_GEN_chargedItemStatChange_1964: out = fn_chargedItemStatChange(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_93, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_reactsToCharges_297, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Battery::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_emitCharge_1962, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "charge_emitted", 14u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_obj(this)}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1375), SYM_GEN_emitSignal_1499, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Battery::fn_emitCharge(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_speedFactor = (_argc > 0) ? _args[0] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_event = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), Gd__gd_core_items__Exclusive__Battery::get_static_const_or_enum(gd_ctx, SYM_GEN_chargeCells_1959), lv_speedFactor, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_sendCharge_318, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Battery::fn_onChargeEnteredCell(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cellIndex = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_charge, lv_cellIndex, this->f_flatSpeed, this->f_speedPerTile}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeChargedItemStat_324, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Battery::fn_chargedItemStatChange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_value}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Battery::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_852), SYM_GEN_High_2601), gd::GdVal::from_int(5LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Battery::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_flatSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_int(100LL));
    this->f_speedPerTile = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed2", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_int(100LL));
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
        case SYM_GEN_staminaReduction_1917: out = this->f_staminaReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Boomerang::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaReduction_1917: this->f_staminaReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Boomerang::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Boomerang::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_staminaReduction)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeStaminaFactor_303, _ca, 1); })();
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_371, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Boomerang::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_staminaReduction = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Boomerang(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Boomerang>(&ctx); }
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
        case SYM_GEN_sawSpeed_2025: return gd::GdVal::from_float(8.0);
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
        case SYM_GEN_sawFrame_2026: out = this->f_sawFrame; return true;
        case SYM_GEN_sawTween_2027: out = this->f_sawTween; return true;
        case SYM_GEN_removeBuffs_2028: out = this->f_removeBuffs; return true;
        case SYM_GEN_slowdown_2029: out = this->f_slowdown; return true;
        case SYM_GEN_sawAnimation_2030: out = this->f_sawAnimation; return true;
        case SYM_GEN_sawSpeed_2025: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chainsaw::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_sawFrame_2026: this->f_sawFrame = val; return true;
        case SYM_GEN_sawTween_2027: this->f_sawTween = val; return true;
        case SYM_GEN_removeBuffs_2028: this->f_removeBuffs = val; return true;
        case SYM_GEN_slowdown_2029: this->f_slowdown = val; return true;
        case SYM_GEN_sawAnimation_2030: this->f_sawAnimation = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chainsaw::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN_pickup_713: return true;
        case SYM_GEN_drop_719: return true;
        case SYM_GEN_setSawTexture_2031: return true;
        case SYM_GEN_onChargeReceived_2032: return true;
        case SYM_GEN_onChargeLeft_2033: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN_playPickupSound_732: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chainsaw::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_pickup_713: out = fn_pickup(args, argc); return true;
        case SYM_GEN_drop_719: out = fn_drop(args, argc); return true;
        case SYM_GEN_setSawTexture_2031: out = fn_setSawTexture(args, argc); return true;
        case SYM_GEN_onChargeReceived_2032: out = fn_onChargeReceived(args, argc); return true;
        case SYM_GEN_onChargeLeft_2033: out = fn_onChargeLeft(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_playPickupSound_732: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Chainsaw::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Chainsaw::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chainsaw::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_numCharges, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_removeBuffs, gd::GdVal::from_int(1000LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealBuffsFraction_363, _ca, 2); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {this->f_removeBuffs, gd::GdVal::from_int(1000LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeBuffsFraction_362, _ca, 2); })();
        }
        (void)([&]() { gd::GdVal _ca[] = {this->f_slowdown}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_reduceSpeed_272, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chainsaw::fn_pickup(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_pickupType = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Chainsaw::get_static_const_or_enum(gd_ctx, SYM_GEN_PickupType_862), SYM_GEN_Grabbed_2633));
    (void)([&]() { gd::GdVal _ca[] = {lv_pickupType}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_pickup_713, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chainsaw::fn_drop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_res = ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_drop_719, nullptr, 0, _out); return _out; })();
    return lv_res;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chainsaw::fn_setSawTexture(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_sawFrame = gd::gd_add(gd_ctx, this->f_sawFrame, gd::GdVal::from_int(1LL));
    this->f_sawFrame = gd::gd_mod(gd_ctx, this->f_sawFrame, gd::GdVal::from_int(4LL));
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadowTexture_785, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chainsaw::fn_onChargeReceived(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_numCharges, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playPickupSound_732, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chainsaw::fn_onChargeLeft(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_numCharges, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chainsaw::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
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
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chainsaw::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_removeBuffs = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_slowdown = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "slow", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Chainsaw(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Chainsaw>(&ctx); }
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
        case SYM_GEN_heat_1800: out = this->f_heat; return true;
        case SYM_GEN_heatFirstCapture_2063: out = this->f_heatFirstCapture; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteQueen::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heat_1800: this->f_heat = val; return true;
        case SYM_GEN_heatFirstCapture_2063: this->f_heatFirstCapture = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteQueen::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2049: return true;
        case SYM_GEN_doEliminatedEffect_2051: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteQueen::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2049: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_doEliminatedEffect_2051: out = fn_doEliminatedEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
        return ([&]() { gd::GdVal _ca[] = {this->f_heatFirstCapture}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteQueen::fn_doEliminatedEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_makeInvulnerable_1191, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteQueen::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat2", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_heatFirstCapture = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat1", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_buffRemoval_2090: out = this->f_buffRemoval; return true;
        case SYM_GEN_buffGain_2091: out = this->f_buffGain; return true;
        case SYM_GEN_speedPerFood_2092: out = this->f_speedPerFood; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__CupcakeDragon::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffRemoval_2090: this->f_buffRemoval = val; return true;
        case SYM_GEN_buffGain_2091: this->f_buffGain = val; return true;
        case SYM_GEN_speedPerFood_2092: this->f_speedPerFood = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__CupcakeDragon::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__CupcakeDragon::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        gd::GdVal lv_buffsLeft = this->f_buffRemoval;
        gd::GdVal lv_ownMostBuffs = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1357, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMostStacks_359, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_ownMostBuffs, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Exclusive/CupcakeDragon.gd:11", 29u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), SYM_GEN_shuffleEngine_1649, _ca, 2); })();
        {
            gd::GdVal _t1642 = gd::gd_iter_seq(gd_ctx.arena, lv_ownMostBuffs);
            gd::GdArr* _t1643 = (_t1642.kind == gd::GdVal::Kind::Arr) ? _t1642.arr : nullptr;
            uint32_t _len__t1644 = _t1643 ? _t1643->len : 0u;
            for (uint32_t _t1644 = 0; _t1644 < _len__t1644; ++_t1644) {
                gd::GdVal lv_buffType = _t1643->data[_t1644];
                gd::GdVal lv_cur = ([&]() { gd::GdVal _ca[] = {lv_buffType}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_getStacks_1018, _ca, 1); })();
                gd::GdVal lv_buffsRemoved = gd::gd_min(lv_cur, lv_buffsLeft);
                (void)([&]() { gd::GdVal _ca[] = {lv_buffType, lv_buffsRemoved, gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_loseStacks_1027, _ca, 3); })();
                lv_buffsLeft = gd::gd_sub(lv_buffsLeft, lv_buffsRemoved);
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_buffsLeft, gd::GdVal::from_int(0LL))))) {
                    break;
                }
            }
        }
        gd::GdVal lv_oppoMostBuffs = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1357, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMostStacks_359, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), ([&]() { gd::GdVal _ca[] = {lv_oppoMostBuffs}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_pickRandomElement_1648, _ca, 1); })(), this->f_buffGain}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_199, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CupcakeDragon::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Food_2604)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CupcakeDragon::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_speedPerFood, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CupcakeDragon::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_buffRemoval = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "remove", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_buffGain = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gain", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_speedPerFood = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_onPreCombatStart_123: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__RubyWhelp::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreCombatStart_123: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__RubyWhelp::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__RubyWhelp::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveReflectStacks_198, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RubyWhelp::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RubyWhelp::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_stackTypes_1830: out = this->f_stackTypes; return true;
        case SYM_GEN_heat_1800: out = this->f_heat; return true;
        case SYM_GEN_heatThreshold_1879: out = this->f_heatThreshold; return true;
        case SYM_GEN_numBuffs_1909: out = this->f_numBuffs; return true;
        case SYM_GEN_speedPerFood_2092: out = this->f_speedPerFood; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__EnergyConversion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stackTypes_1830: this->f_stackTypes = val; return true;
        case SYM_GEN_heat_1800: this->f_heat = val; return true;
        case SYM_GEN_heatThreshold_1879: this->f_heatThreshold = val; return true;
        case SYM_GEN_numBuffs_1909: this->f_numBuffs = val; return true;
        case SYM_GEN_speedPerFood_2092: this->f_speedPerFood = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__EnergyConversion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__EnergyConversion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Food_2604)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EnergyConversion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0), this->f_speedPerFood)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EnergyConversion::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_114, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1276), SYM_GEN_Sufficient_2603))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getHeat_1231, nullptr, 0), this->f_heatThreshold)))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_numBuffs, gd::GdVal::null(), this->f_stackTypes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_367, _ca, 3); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
        }
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EnergyConversion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_heatThreshold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heatt", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_numBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_speedPerFood = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_stackTypes = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1357, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Heat_2572)}; return gd::call_method(gd_ctx, this->f_stackTypes, gd::SYM_erase, _ca, 1); })();
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
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_combatStart_125: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ForestFriend::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_combatStart_125: out = fn_combatStart(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Pet_2598)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Food_2604)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ForestFriend::fn_combatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_combatStart_125, nullptr, 0, _out); return _out; })();
    gd::GdVal lv_numAffected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numAffected, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(lv_numAffected, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ForestFriend::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_gold_2197: out = this->f_gold; return true;
        case SYM_GEN_regen_1903: out = this->f_regen; return true;
        case SYM_GEN_cleanse_1117: out = this->f_cleanse; return true;
        case SYM_GEN_block_1580: out = this->f_block; return true;
        case SYM_GEN_speedMalus_2084: out = this->f_speedMalus; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__GoldArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_gold_2197: this->f_gold = val; return true;
        case SYM_GEN_regen_1903: this->f_regen = val; return true;
        case SYM_GEN_cleanse_1117: this->f_cleanse = val; return true;
        case SYM_GEN_block_1580: this->f_block = val; return true;
        case SYM_GEN_speedMalus_2084: this->f_speedMalus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__GoldArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__GoldArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__GoldArmor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldArmor::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_gold}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveGold_750, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldArmor::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldArmor::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1645 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1510, nullptr, 0));
        gd::GdArr* _t1646 = (_t1645.kind == gd::GdVal::Kind::Arr) ? _t1645.arr : nullptr;
        uint32_t _len__t1647 = _t1646 ? _t1646->len : 0u;
        for (uint32_t _t1647 = 0; _t1647 < _len__t1647; ++_t1647) {
            gd::GdVal lv_item = _t1646->data[_t1647];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Weapon_2666)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_speedMalus}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_272, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0), this->f_regen)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_cleanse}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_354, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getDebuffStacks_1196, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_block}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__GoldArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_gold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_cleanse = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cleanse", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_block = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "block", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_speedMalus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__IceArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__IceArmor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__IceArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_349, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__IceArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getHeat_1231, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useHeat_352, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_349, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__IceArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_stamina_2059: out = this->f_stamina; return true;
        case SYM_GEN_mana_1832: out = this->f_mana; return true;
        case SYM_GEN_luck_893: out = this->f_luck; return true;
        case SYM_GEN_speedPerRound_2248: out = this->f_speedPerRound; return true;
        case SYM_GEN_buyRound_2249: out = this->f_buyRound; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__LevelUp::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stamina_2059: this->f_stamina = val; return true;
        case SYM_GEN_mana_1832: this->f_mana = val; return true;
        case SYM_GEN_luck_893: this->f_luck = val; return true;
        case SYM_GEN_speedPerRound_2248: this->f_speedPerRound = val; return true;
        case SYM_GEN_buyRound_2249: this->f_buyRound = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__LevelUp::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__LevelUp::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__LevelUp::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__LevelUp::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_roundsPassed = gd::gd_sub(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_cur_round_1391), this->f_buyRound);
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_roundsPassed, this->f_speedPerRound)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LevelUp::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_315, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_stamina}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_316, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LevelUp::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_speedPerRound = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_buyRound = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "skillround", 10u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_chargeCells_1959: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(2LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(3LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float())})), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(2LL))).as_float())})), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(2LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(3LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float())})), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(1LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(2LL)).as_float())}))}));
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
        case SYM_GEN_mana1_2296: out = this->f_mana1; return true;
        case SYM_GEN_mana2_2177: out = this->f_mana2; return true;
        case SYM_GEN_chargeCells_1959: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ManaCrystal::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_mana1_2296: this->f_mana1 = val; return true;
        case SYM_GEN_mana2_2177: this->f_mana2 = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ManaCrystal::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_lightning_287: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_emitCharge_1962: return true;
        case SYM_GEN_onChargeEnteredCell_1963: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ManaCrystal::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_lightning_287: out = fn_canAffect_lightning(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_emitCharge_1962: out = fn_emitCharge(args, argc); return true;
        case SYM_GEN_onChargeEnteredCell_1963: out = fn_onChargeEnteredCell(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_emitCharge_1962, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "charge_emitted", 14u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_obj(this)}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1375), SYM_GEN_emitSignal_1499, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaCrystal::fn_emitCharge(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_speedFactor = (_argc > 0) ? _args[0] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_event = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    {
        gd::GdVal _t1648 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, Gd__gd_core_items__Exclusive__ManaCrystal::get_static_const_or_enum(gd_ctx, SYM_GEN_chargeCells_1959), gd::SYM_size, nullptr, 0));
        gd::GdArr* _t1649 = (_t1648.kind == gd::GdVal::Kind::Arr) ? _t1648.arr : nullptr;
        uint32_t _len__t1650 = _t1649 ? _t1649->len : 0u;
        for (uint32_t _t1650 = 0; _t1650 < _len__t1650; ++_t1650) {
            gd::GdVal lv_i = _t1649->data[_t1650];
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__ManaCrystal::get_static_const_or_enum(gd_ctx, SYM_GEN_chargeCells_1959), lv_i), lv_speedFactor, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_sendCharge_318, _ca, 4); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaCrystal::fn_onChargeEnteredCell(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cellIndex = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1555), gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1555), gd::get_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1554))))) : gd::GdVal::from_bool(false)))) {
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Magic_2721)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1555), SYM_GEN_hasType_77, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_mana2}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {this->f_mana1}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ManaCrystal::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_mana1 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana1", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_mana2 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana2", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_cold_1949: out = this->f_cold; return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__NoRushPlease::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_cold_1949: this->f_cold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__NoRushPlease::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onPreCombatStart_123: return true;
        case SYM_GEN_buffEnded_1721: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__NoRushPlease::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreCombatStart_123: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_buffEnded_1721: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN_onPreCombatStart_123, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_changeDamageResistance_1259, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__NoRushPlease::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN_buffEnded_1721, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_changeDamageResistance_1259, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__NoRushPlease::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_cold}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_349, _ca, 1); })();
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN_onCombatStart_930, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__NoRushPlease::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_cold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_poisonCritActive_2333: out = this->f_poisonCritActive; return true;
        case SYM_GEN_tween_2334: out = this->f_tween; return true;
        case SYM_GEN_poison_1866: out = this->f_poison; return true;
        case SYM_GEN_selfPoison_2307: out = this->f_selfPoison; return true;
        case SYM_GEN_cdAdvance_1984: out = this->f_cdAdvance; return true;
        case SYM_GEN_luckNeeded_1778: out = this->f_luckNeeded; return true;
        case SYM_GEN_light_945: out = this->f_light; return true;
        case SYM_GEN_lightAni_2335: out = this->f_lightAni; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PoisonGrenade::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_poisonCritActive_2333: this->f_poisonCritActive = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_tween_2334: this->f_tween = val; return true;
        case SYM_GEN_poison_1866: this->f_poison = val; return true;
        case SYM_GEN_selfPoison_2307: this->f_selfPoison = val; return true;
        case SYM_GEN_cdAdvance_1984: this->f_cdAdvance = val; return true;
        case SYM_GEN_luckNeeded_1778: this->f_luckNeeded = val; return true;
        case SYM_GEN_light_945: this->f_light = val; return true;
        case SYM_GEN_lightAni_2335: this->f_lightAni = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PoisonGrenade::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onChargeReceived_2032: return true;
        case SYM_GEN_onLuckChanged_1968: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PoisonGrenade::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onChargeReceived_2032: out = fn_onChargeReceived(args, argc); return true;
        case SYM_GEN_onLuckChanged_1968: out = fn_onLuckChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PoisonGrenade::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonGrenade::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_lucky_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onLuckChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonGrenade::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_poison}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_209, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_selfPoison}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_selfInflictPoison_210, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_143, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonGrenade::fn_onChargeReceived(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_cdAdvance}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_advanceCooldownSeconds_145, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoisonGrenade::fn_onLuckChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_poisonCritActive)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getLucky_1217, nullptr, 0), this->f_luckNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_changePoisonCritChancePercent_1263, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    }
    else if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(this->f_poisonCritActive)) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getLucky_1217, nullptr, 0), this->f_luckNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_changePoisonCritChancePercent_1263, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_poison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "poison", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_selfPoison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "poison2", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_cdAdvance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cdadvance", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luckt", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_onAddToInventory_417: return true;
        case SYM_GEN_onRemoveFromInventory_416: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_getRelatedItems_457: return true;
        case SYM_GEN_getRelatedItemColumns_695: return true;
        case SYM_GEN_getRelatedItemHeight_696: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__RainbowBadge::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onAddToInventory_417: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_416: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getRelatedItems_457: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_695: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_696: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
        gd::GdVal _t1651 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1357, nullptr, 0));
        gd::GdArr* _t1652 = (_t1651.kind == gd::GdVal::Kind::Arr) ? _t1651.arr : nullptr;
        uint32_t _len__t1653 = _t1652 ? _t1652->len : 0u;
        for (uint32_t _t1653 = 0; _t1653 < _len__t1653; ++_t1653) {
            gd::GdVal lv_buff = _t1652->data[_t1653];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), lv_buff, gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_199, _ca, 3); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_143, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_digUpItems_1882: out = this->f_digUpItems; return true;
        case SYM_GEN_spawnPos_1884: out = this->f_spawnPos; return true;
        case SYM_GEN_luck_893: out = this->f_luck; return true;
        case SYM_GEN_heat_1800: out = this->f_heat; return true;
        case SYM_GEN_cdIncrease_2374: out = this->f_cdIncrease; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Robodog::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_digUpItems_1882: this->f_digUpItems = val; return true;
        case SYM_GEN_spawnPos_1884: this->f_spawnPos = val; return true;
        case SYM_GEN_luck_893: this->f_luck = val; return true;
        case SYM_GEN_heat_1800: this->f_heat = val; return true;
        case SYM_GEN_cdIncrease_2374: this->f_cdIncrease = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Robodog::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onChargeReceived_2032: return true;
        case SYM_GEN_onChargeLeft_2033: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Robodog::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onChargeReceived_2032: out = fn_onChargeReceived(args, argc); return true;
        case SYM_GEN_onChargeLeft_2033: out = fn_onChargeLeft(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetBaseCooldown_107, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_numCharges, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Robodog::fn_onChargeLeft(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_numCharges, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Robodog::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_numCharges, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_baseCooldownOverride, this->f_cdIncrease)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBaseCooldown_106, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_cdIncrease = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cdincrease", 10u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
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
        case SYM_GEN_invuProcced_2397: out = this->f_invuProcced; return true;
        case SYM_GEN_gemDurFactor_2398: out = this->f_gemDurFactor; return true;
        case SYM_GEN_manaNeeded_1785: out = this->f_manaNeeded; return true;
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        case SYM_GEN_buffTimer_1723: out = this->f_buffTimer; return true;
        case SYM_GEN_blind_1815: out = this->f_blind; return true;
        case SYM_GEN_manaNeeded_base_2399: out = this->f_manaNeeded_base; return true;
        case SYM_GEN_manaCostIncrease_2400: out = this->f_manaCostIncrease; return true;
        case SYM_GEN_maxUses_1990: out = this->f_maxUses; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ShinyMantle::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_invuProcced_2397: this->f_invuProcced = gd::gd_coerce_int(val); return true;
        case SYM_GEN_gemDurFactor_2398: this->f_gemDurFactor = gd::gd_coerce_float(val); return true;
        case SYM_GEN_manaNeeded_1785: this->f_manaNeeded = val; return true;
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        case SYM_GEN_buffTimer_1723: this->f_buffTimer = val; return true;
        case SYM_GEN_blind_1815: this->f_blind = val; return true;
        case SYM_GEN_manaNeeded_base_2399: this->f_manaNeeded_base = val; return true;
        case SYM_GEN_manaCostIncrease_2400: this->f_manaCostIncrease = val; return true;
        case SYM_GEN_maxUses_1990: this->f_maxUses = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ShinyMantle::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_readyToFuse_747: return true;
        case SYM_GEN_onFusingFinished_844: return true;
        case SYM_GEN_getCounterValue_2255: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onInvuStarted_2401: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN_buffEnded_1721: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ShinyMantle::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_readyToFuse_747: out = fn_readyToFuse(args, argc); return true;
        case SYM_GEN_onFusingFinished_844: out = fn_onFusingFinished(args, argc); return true;
        case SYM_GEN_getCounterValue_2255: out = fn_getCounterValue(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onInvuStarted_2401: out = fn_onInvuStarted(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_buffEnded_1721: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isBag_81, nullptr, 0)));
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
    (void)([&]() { gd::GdVal _ca[] = {lv_validBonds}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onFusingFinished_844, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_getCounterValue(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_gold = gd::GdVal::from_int(0LL);
    gd::GdVal lv_inv = (gd::gd_truth(this->f_placed) ? (this->f_inventory) : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1280), SYM_GEN_INVENTORY_1089)));
    {
        gd::GdVal _t1654 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, lv_inv, SYM_GEN_getItemsAndGems_1511, nullptr, 0));
        gd::GdArr* _t1655 = (_t1654.kind == gd::GdVal::Kind::Arr) ? _t1654.arr : nullptr;
        uint32_t _len__t1656 = _t1655 ? _t1655->len : 0u;
        for (uint32_t _t1656 = 0; _t1656 < _len__t1656; ++_t1656) {
            gd::GdVal lv_item = _t1655->data[_t1656];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isGem_82, nullptr, 0))) {
                lv_gold = gd::gd_add(gd_ctx, lv_gold, gd::call_method(gd_ctx, lv_item, SYM_GEN_getPrice_390, nullptr, 0));
            }
        }
    }
    if (gd::gd_truth(this->f_dragged)) {
        {
            gd::GdVal _t1657 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_495, nullptr, 0));
            gd::GdArr* _t1658 = (_t1657.kind == gd::GdVal::Kind::Arr) ? _t1657.arr : nullptr;
            uint32_t _len__t1659 = _t1658 ? _t1658->len : 0u;
            for (uint32_t _t1659 = 0; _t1659 < _len__t1659; ++_t1659) {
                gd::GdVal lv_gem = _t1658->data[_t1659];
                lv_gold = gd::gd_add(gd_ctx, lv_gold, gd::call_method(gd_ctx, lv_gem, SYM_GEN_getPrice_390, nullptr, 0));
            }
        }
    }
    return lv_gold;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_invulnerable_start", 28u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onInvuStarted", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    this->f_manaNeeded = this->f_manaNeeded_base;
    this->f_invuProcced = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_gemDurFactor = gd::gd_coerce_float(gd::gd_floor(gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue_2255, nullptr, 0), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })())));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_isVulnerable_1271, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getMana_1224, nullptr, 0), this->f_manaNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
        this->f_invuProcced = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_invuProcced, gd::GdVal::from_int(1LL)));
        gd::GdVal lv_invuDur = gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_base", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_bonus", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), this->f_gemDurFactor));
        (void)([&]() { gd::GdVal _ca[] = {lv_invuDur}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1683, _ca, 1); })();
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_invuDur, gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_makeInvulnerable_1191, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_manaNeeded, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_330, _ca, 2); })();
        this->f_manaNeeded = gd::gd_add(gd_ctx, this->f_manaNeeded, this->f_manaCostIncrease);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_invuProcced, this->f_maxUses)))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_143, nullptr, 0);
            return gd::GdVal::null();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_onInvuStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_blind, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_211, _ca, 2); })();
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
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShinyMantle::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BuffTimer", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffEnded", 9u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_133, _ca, 3); })();
    this->f_blind = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blind", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_manaNeeded_base = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "manat", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_manaCostIncrease = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_maxUses = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "max", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_pets_2428: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Rat", 3u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Squirrel", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Rat Chef", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Hedgehog", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Squirrel Archer", 15u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Hyper Hedgehog", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Carrot Goobert", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Snowmaster", 10u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Forest Dragon", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Toad", 4u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Poison Goobert", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Poison Frog", 11u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Ruby Chonk", 10u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Frog Prince", 11u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Crow", 4u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Ice Dragon", 10u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Courage Puppy", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Wisdom Puppy", 12u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Power Puppy", 11u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Armored Courage Puppy", 21u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Armored Wisdom Puppy", 20u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Armored Power Puppy", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Cheese Goobert", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Steel Dragon", 12u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Chili Goobert", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Fire Shelly", 11u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Phoenix", 7u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Phoenix2", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Emerald Whelp", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Sapphire Whelp", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Amethyst Whelp", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Obsidian Dragon", 15u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Cat Spirit", 10u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Owl Spirit", 10u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Badger Spirit", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Cupcake Goobert", 15u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Cupcake Dragon", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Broccoli Goobert", 16u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Dragon Knight", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Jynx Staff", 10u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Robodog", 7u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Toast Goobert", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Mecha Bat", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Thunder Drake", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Goobling", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Shelly", 6u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Steel Goobert", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Blood Goobert", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Ruby Whelp", 10u))}));
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
        case SYM_GEN_petDescriptors_2429: out = this->f_petDescriptors; return true;
        case SYM_GEN_salesChance_1996: out = this->f_salesChance; return true;
        case SYM_GEN_pets_2428: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SpeakwithAnimals::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_petDescriptors_2429: this->f_petDescriptors = val; return true;
        case SYM_GEN_salesChance_1996: this->f_salesChance = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SpeakwithAnimals::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onSaleRoll_1997: return true;
        case SYM_GEN_getGatedDescriptor_952: return true;
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_getRelatedItems_457: return true;
        case SYM_GEN_getRelatedItemColumns_695: return true;
        case SYM_GEN_getRelatedItemHeight_696: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SpeakwithAnimals::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onSaleRoll_1997: out = fn_onSaleRoll(args, argc); return true;
        case SYM_GEN_getGatedDescriptor_952: out = fn_getGatedDescriptor(args, argc); return true;
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getRelatedItems_457: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_695: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_696: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Pet_2598)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpeakwithAnimals::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1660 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1661 = (_t1660.kind == gd::GdVal::Kind::Arr) ? _t1660.arr : nullptr;
        uint32_t _len__t1662 = _t1661 ? _t1661->len : 0u;
        for (uint32_t _t1662 = 0; _t1662 < _len__t1662; ++_t1662) {
            gd::GdVal lv_item = _t1661->data[_t1662];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveDoubleActivationChance_310, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpeakwithAnimals::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {this->f_petDescriptors}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_flatten_1707, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_salesChance = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "sale", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    {
        gd::GdVal _t1663 = gd::gd_iter_seq(gd_ctx.arena, Gd__gd_core_items__Exclusive__SpeakwithAnimals::get_static_const_or_enum(gd_ctx, SYM_GEN_pets_2428));
        gd::GdArr* _t1664 = (_t1663.kind == gd::GdVal::Kind::Arr) ? _t1663.arr : nullptr;
        uint32_t _len__t1665 = _t1664 ? _t1664->len : 0u;
        for (uint32_t _t1665 = 0; _t1665 < _len__t1665; ++_t1665) {
            gd::GdVal lv_pet = _t1664->data[_t1665];
            gd::GdVal lv_desc = ([&]() { gd::GdVal _ca[] = {lv_pet}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })();
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_desc, SYM_GEN_isReleased_1627, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_desc}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_petDescriptors, gd::call_method(gd_ctx, lv_desc, SYM_GEN_getRarity_234, nullptr, 0)), gd::SYM_push_back, _ca, 1); })();
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
        case SYM_GEN_staminaReduction_1917: out = this->f_staminaReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__StarofCourage::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaReduction_1917: this->f_staminaReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__StarofCourage::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__StarofCourage::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
        gd::GdVal _t1666 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1510, nullptr, 0));
        gd::GdArr* _t1667 = (_t1666.kind == gd::GdVal::Kind::Arr) ? _t1666.arr : nullptr;
        uint32_t _len__t1668 = _t1667 ? _t1667->len : 0u;
        for (uint32_t _t1668 = 0; _t1668 < _len__t1668; ++_t1668) {
            gd::GdVal lv_item = _t1667->data[_t1668];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isWeapon_80, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_staminaReduction}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeStaminaFactor_303, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StarofCourage::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_staminaReduction = gd::gd_neg(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__StarofCourage(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__StarofCourage>(&ctx); }
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
        case SYM_GEN_spikesLimit_2441: out = this->f_spikesLimit; return true;
        case SYM_GEN_spikes_894: out = this->f_spikes; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ThornElemental::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikesLimit_2441: this->f_spikesLimit = val; return true;
        case SYM_GEN_spikes_894: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ThornElemental::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ThornElemental::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Nature_2596)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThornElemental::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_spikesLimit}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeEffectSpikesLimit_1171, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_spikesLimit}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeRangedSpikesLimit_1170, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeSpikesCritChancePercent_1264, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThornElemental::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_207, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThornElemental::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_spikesLimit = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikedam", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ThornElemental(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ThornElemental>(&ctx); }
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
        case SYM_GEN_boosted_2100: out = this->f_boosted; return true;
        case SYM_GEN_baseSpeed_2508: out = this->f_baseSpeed; return true;
        case SYM_GEN_bonusSpeed_1786: out = this->f_bonusSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__UniquelyUnique::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_boosted_2100: this->f_boosted = val; return true;
        case SYM_GEN_baseSpeed_2508: this->f_baseSpeed = val; return true;
        case SYM_GEN_bonusSpeed_1786: this->f_bonusSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__UniquelyUnique::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onBought_453: return true;
        case SYM_GEN_getData_634: return true;
        case SYM_GEN_setData_635: return true;
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_canAffect_secondary_285: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onItemRoll_1922: return true;
        case SYM_GEN_onItemRolled_1923: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__UniquelyUnique::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onBought_453: out = fn_onBought(args, argc); return true;
        case SYM_GEN_getData_634: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_635: out = fn_setData(args, argc); return true;
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_285: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemRoll_1922: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_1923: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_93, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UniquelyUnique::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, lv_item, SYM_GEN_getRarity_234, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Rarity_858), SYM_GEN_Unique_2756)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Platin Customer Card", 20u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })()}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_243, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Customer Card", 13u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })()}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_243, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UniquelyUnique::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_affectedItems = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_affectedItems, gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_baseSpeed, gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Secondary_2582)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, _ca, 1); })(), this->f_bonusSpeed))}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, lv_affectedItems, gd::GdVal::from_int(0LL)), SYM_GEN_addSpeed_271, _ca, 1); })();
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
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_descr, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Customer Card", 13u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })())))) {
        this->f_boosted = gd::gd_sub(this->f_boosted, gd::GdVal::from_int(1LL));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__UniquelyUnique::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_baseSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_bonusSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed2", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_options_1780: out = this->f_options; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Fanfare::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_options_1780: this->f_options = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Fanfare::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Fanfare::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_265, nullptr, 0), gd::GdVal::from_float(100.0)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Fanfare::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rng = ([&]() { gd::GdVal _ca[] = {this->f_options}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_pickRandomElement_1648, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_rng, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_rng, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeMana_332, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drainStamina_115, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    (void)([&]() { gd::GdVal _ca[] = {lv_rng}; return gd::call_method(gd_ctx, this->f_options, gd::SYM_erase, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Fanfare::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__HealingHerbs::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__HealingHerbs::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__HealingHerbs::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_379, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HealingHerbs::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_explodeRandomly_1825: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Piggybank::has_own_method(m);
}
bool Gd__gd_core_items__LuckyPiggy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_explodeRandomly_1825: out = fn_explodeRandomly(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canModifyChance_291, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyPiggy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1669 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1670 = (_t1669.kind == gd::GdVal::Kind::Arr) ? _t1669.arr : nullptr;
        uint32_t _len__t1671 = _t1670 ? _t1670->len : 0u;
        for (uint32_t _t1671 = 0; _t1671 < _len__t1671; ++_t1671) {
            gd::GdVal lv_item = _t1670->data[_t1671];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusChance_173, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyPiggy::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyPiggy::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_852), SYM_GEN_High_2601), gd::GdVal::from_int(5LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyPiggy::fn_explodeRandomly(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyPiggy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Piggybank::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_damageIncreaseActive_1867: out = this->f_damageIncreaseActive; return true;
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        case SYM_GEN_poisonPerSpike_1868: out = this->f_poisonPerSpike; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__PoisonIvy::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damageIncreaseActive_1867: this->f_damageIncreaseActive = val; return true;
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        case SYM_GEN_poisonPerSpike_1868: this->f_poisonPerSpike = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__PoisonIvy::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onSpikesChanged_940: return true;
        case SYM_GEN_onOpponentPoisonChanged_1735: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__PoisonIvy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onSpikesChanged_940: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN_onOpponentPoisonChanged_1735: out = fn_onOpponentPoisonChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Nature_2596)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonIvy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_spikes_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onSpikesChanged", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_poison_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentPoisonChanged", 23u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeDebuffResistChances_1200, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonIvy::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, this->f_poisonPerSpike), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_209, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonIvy::fn_onOpponentPoisonChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_curPoison = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_getPoison_1209, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_damageIncreaseActive))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_curPoison, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_changeDamageResistance_1259, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(false), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonIvy::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_poisonPerSpike = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0));
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
        case SYM_GEN_affectedWeapons_1889: out = this->f_affectedWeapons; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__SteelGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedWeapons_1889: this->f_affectedWeapons = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__SteelGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_secondary_285: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__SteelGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_secondary_285: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__SteelGoobert::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1672 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Secondary_2582)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, _ca, 1); })());
        gd::GdArr* _t1673 = (_t1672.kind == gd::GdVal::Kind::Arr) ? _t1672.arr : nullptr;
        uint32_t _len__t1674 = _t1673 ? _t1673->len : 0u;
        for (uint32_t _t1674 = 0; _t1674 < _len__t1674; ++_t1674) {
            gd::GdVal lv_item = _t1673->data[_t1674];
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, this->f_affectedWeapons, gd::SYM_push_back, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__SteelGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1675 = gd::gd_iter_seq(gd_ctx.arena, this->f_affectedWeapons);
        gd::GdArr* _t1676 = (_t1675.kind == gd::GdVal::Kind::Arr) ? _t1675.arr : nullptr;
        uint32_t _len__t1677 = _t1676 ? _t1676->len : 0u;
        for (uint32_t _t1677 = 0; _t1677 < _len__t1677; ++_t1677) {
            gd::GdVal lv_item = _t1676->data[_t1677];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_159, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__SteelGoobert::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_affectedWeapons, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__SteelGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__WalrusTusk::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__WalrusTusk::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__WalrusTusk::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_207, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_379, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__WalrusTusk::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__WalrusTusk(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__WalrusTusk>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__WalrusTusk = {CLS_Gd__gd_core_items__WalrusTusk, "WalrusTusk", "res://gd_core_items/WalrusTusk.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__WalrusTusk, &Gd__gd_core_items__WalrusTusk::get_static_prop_fn, &Gd__gd_core_items__WalrusTusk::call_static_fn};
