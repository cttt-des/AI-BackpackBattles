#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core__CoreBuff.hpp"
#include "../hdrs/Gd__gd_core__Card.hpp"
#include "../hdrs/Gd__gd_core__Bloodthorne.hpp"
#include "../hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "../hdrs/Gd__gd_core__CoreItemData.hpp"
#include "../hdrs/Gd__gd_core__Darksaber.hpp"
#include "../hdrs/Gd__gd_core__FlyAgaric.hpp"
#include "../hdrs/Gd__gd_core__HungryBlade.hpp"
#include "../hdrs/Gd__gd_core__Manathirst.hpp"
#include "../hdrs/Gd__gd_core__PotionBelt.hpp"
#include "../hdrs/Gd__gd_core__StaffofUnhealing.hpp"
#include "../hdrs/Gd__gd_core__TheFool.hpp"
#include "../hdrs/Gd__gd_core_items__Card.hpp"
#include "../hdrs/Gd__gd_core_items__Blueberries.hpp"
#include "../hdrs/Gd__gd_core_items__CursedHairComb.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__AmuletofAlchemy.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ArmoredPowerPuppy.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BigBloodthorne.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BroccoliGoobert.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Chess__ChessPiece.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ChiliPepper.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DarkRitual.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DragonskinBoots.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ExtraAngy.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__FrogPrince.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__HeartoftheCards.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Joker.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__LongSpear.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MegaClover.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__OwlSpirit.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Pot.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Scale.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SlimeTime.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SpellScrollNature.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__StoneGloves.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__TimeDilator.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__WarScythe.hpp"
#include "../hdrs/Gd__gd_core_items__Gems__Amethyst.hpp"
#include "../hdrs/Gd__gd_core_items__HeroSword.hpp"
#include "../hdrs/Gd__gd_core_items__Manathirst.hpp"
#include "../hdrs/Gd__gd_core_items__RainbowGoobert.hpp"
#include "../hdrs/Gd__gd_core_items__StrongPestilenceFlask.hpp"

namespace {
constexpr gd::GdStr battle_string_literals[] = {
    {"\n\n", 2u, 2274317941u},
    {"CARD_COUNT", 10u, 1490789295u},
    {"num", 3u, 242376115u},
    {"CARD_HINT", 9u, 4169059801u},
    {"character_vampirism_changed", 27u, 75150398u},
    {"onVampirismChanged", 18u, 3624660862u},
    {"character_spikes_changed", 24u, 3463900413u},
    {"onSpikesChanged", 15u, 3715123341u},
    {"", 0u, 2166136261u},
    {"attack", 6u, 1167440125u},
    {"win", 3u, 200788825u},
    {"lose", 4u, 3509868664u},
    {"unknown", 7u, 2608177081u},
    {"character_", 10u, 2085970269u},
    {"_changed", 8u, 3417166458u},
    {"Player", 6u, 477166624u},
    {"Opponent", 8u, 1032749700u},
    {"Character.gd:327", 16u, 3219899945u},
    {"onPreDealDamage_early", 21u, 1141032398u},
    {"pre_take_damage", 15u, 2330033632u},
    {"onPreDealDamage_late", 20u, 4290954099u},
    {"pre_take_damage_late", 20u, 571519801u},
    {"Poison", 6u, 3158204625u},
    {"Block", 5u, 3171368962u},
    {"Fatigue", 7u, 1556357630u},
    {"Hit", 3u, 1700614218u},
    {"dealt_damage_signal_placeholder", 31u, 1864214166u},
    {"character_attacked", 18u, 2439462988u},
    {"character_damaged", 17u, 745527748u},
    {"onDealtDamage", 13u, 1467360435u},
    {"character_healed", 16u, 2989261042u},
    {"character_overhealed", 20u, 177632284u},
    {"reincarnated", 12u, 2408540175u},
    {"temporary_max_health_changed", 28u, 310654751u},
    {"character_pre_use_stamina", 25u, 4061960724u},
    {"character_used_stamina", 22u, 4094391974u},
    {"character_stunned", 17u, 4164697708u},
    {"fatigue_damage_changed", 22u, 2103754981u},
    {"blinding_light_ended", 20u, 2616732264u},
    {"battle_rage_started", 19u, 3997014835u},
    {"battle_rage_ended", 17u, 4230921894u},
    {"class_changed", 13u, 1615855124u},
    {"health", 6u, 1805184399u},
    {"stamina", 7u, 3875003702u},
    {"randPitch", 9u, 1151803428u},
    {"character_invulnerable_start", 28u, 2327172069u},
    {"character_invulnerable_end", 26u, 3350240732u},
    {"recalculateMaxStamina", 21u, 508469027u},
    {"Stamina Sack", 12u, 3135812348u},
    {"_", 1u, 3658226030u},
    {"Stone", 5u, 1842662042u},
    {"name", 4u, 2369371622u},
    {"identifier", 10u, 681945150u},
    {"index", 5u, 151693739u},
    {"minDam", 6u, 3647452719u},
    {"maxDam", 6u, 592428749u},
    {"staminaCost", 11u, 692264327u},
    {"block", 5u, 3943480674u},
    {"cd", 2u, 1529452802u},
    {"extraCds", 8u, 295123783u},
    {"accuracy", 8u, 1889185700u},
    {"canActivate", 11u, 2277690352u},
    {"chance", 6u, 2459084481u},
    {"chance2", 7u, 2950484105u},
    {"shopChance", 10u, 1435148261u},
    {"types", 5u, 4292920474u},
    {"tags", 4u, 4095142816u},
    {"physics", 7u, 2267225250u},
    {"rarity", 6u, 1266615690u},
    {"price", 5u, 189023530u},
    {"classes", 7u, 1882039975u},
    {"randomUniquePool", 16u, 3614658971u},
    {"hasBattleRageEffect", 19u, 3074838841u},
    {"gatedItems", 10u, 4187939518u},
    {"startsSubclass", 14u, 2130492966u},
    {"gateItem", 8u, 1563718697u},
    {"gate_item", 9u, 968161264u},
    {"originatingRecipes", 18u, 3632248325u},
    {"originating_recipes", 19u, 1356245250u},
    {"animationScene", 14u, 1958236555u},
    {"flickerAni", 10u, 869505055u},
    {"flicker_animation", 17u, 599064606u},
    {"flickerMinDist", 14u, 3154533517u},
    {"flicker_min_dist", 16u, 1027794029u},
    {"flickerMaxDist", 14u, 766191159u},
    {"flicker_max_dist", 16u, 1768726851u},
    {"flickerMinSpeed", 15u, 3355891604u},
    {"flicker_min_speed", 17u, 1515266548u},
    {"flickerMaxSpeed", 15u, 2566538706u},
    {"flicker_max_speed", 17u, 3198618670u},
    {"connectorReadyRoll", 18u, 3610243000u},
    {"connector_ready_roll", 20u, 516633754u},
    {"gemRoll", 7u, 352763615u},
    {"gem_roll", 8u, 1358800554u},
    {"sceneDepth", 10u, 637688668u},
    {"scene_depth", 11u, 3992921433u},
    {"releaseState", 12u, 2486442979u},
    {"release_state", 13u, 725990852u},
    {"params", 6u, 559900755u},
    {"namedParams", 11u, 212769148u},
    {"named_params", 12u, 3034422257u},
    {"gainedStacks", 12u, 1306778278u},
    {"removedStacks", 13u, 140807226u},
    {"usedStacks", 10u, 3590608929u},
    {"onDebuffsChanged", 16u, 4096794781u},
    {"character_mana_changed", 22u, 798563205u},
    {"onManaChanged", 13u, 3105672029u},
    {"lifesteal", 9u, 1515578962u},
    {"dam", 3u, 4031722721u},
    {"mana", 4u, 3650585354u},
    {"potion_emptied", 14u, 70999789u},
    {"onPotionEmptied", 15u, 4255313949u},
    {"Bagtacular", 10u, 2131747329u},
    {"buffs", 5u, 2149256365u},
    {"heal", 4u, 979982427u},
    {"dur_unhealing", 13u, 3047247524u},
    {"UnhealingTimer", 14u, 2986033917u},
    {"buffEnded", 9u, 3457903416u},
    {"revealspeed", 11u, 3267256187u},
    {"empower", 7u, 2037162760u},
    {"attacked", 8u, 3381721668u},
    {"onAffectedAttacked", 18u, 2827661201u},
    {"lifesteal_scaling", 17u, 610492256u},
    {"PotionTriggerTimer", 18u, 999831227u},
    {"triggerNextPotion", 17u, 745728413u},
    {"delay", 5u, 1322381784u},
    {"regent", 6u, 4290639402u},
    {"vampirism", 9u, 773404377u},
    {"spikes", 6u, 439106706u},
    {"luck", 4u, 4145017712u},
    {"luckt", 5u, 4061892428u},
    {"regen", 5u, 16724762u},
    {"Exclusive/Chess/ChessPiece.gd:74", 32u, 2209030417u},
    {"HINT_Chess", 10u, 68829135u},
    {"White", 5u, 1827351814u},
    {"Corrupted Crystal", 17u, 1233848549u},
    {"debuffs", 7u, 504032524u},
    {"speed", 5u, 2072037248u},
    {"onBattleRageStarted", 19u, 3330696088u},
    {"onBattleRageEnded", 17u, 1252110145u},
    {"duration", 8u, 799079693u},
    {"dur", 3u, 3509645056u},
    {"dur_1", 5u, 1189330420u},
    {"BuffTimer", 9u, 194754125u},
    {"blind", 5u, 274826164u},
    {"activated", 9u, 2866667388u},
    {"onCardRevealed", 14u, 755762322u},
    {"pos", 3u, 1412654217u},
    {"Joker_COUNTER", 13u, 333425847u},
    {"pairs", 5u, 1637539686u},
    {"triplets", 8u, 3869841120u},
    {"quadruples", 10u, 3542246839u},
    {"\n", 1u, 252472541u},
    {"cards", 5u, 2180079684u},
    {"character_lucky_changed", 23u, 2259242176u},
    {"onLuckyChanged", 14u, 1760969932u},
    {"sales", 5u, 2258376375u},
    {"luckneeded", 10u, 1930291013u},
    {"manat", 5u, 126091098u},
    {"fatiguemana", 11u, 2121368953u},
    {"potion_triggered", 16u, 729283976u},
    {"onPotionTriggered", 17u, 2537318808u},
    {"heal_food", 9u, 2824253696u},
    {"heat", 4u, 577319571u},
    {"gold", 4u, 3966162835u},
    {"speed2", 6u, 498752822u},
    {"Goobling", 8u, 1161906606u},
    {"used_stamina", 12u, 2801525262u},
    {"onItemUsedStamina", 17u, 2944104951u},
    {"staminat", 8u, 3660664550u},
    {"onWeaponAttacked", 16u, 3445043441u},
    {"speedreduction", 14u, 1031897425u},
    {"dambonus", 8u, 2769252496u},
    {"slow", 4u, 1838498488u},
    {"poisont", 7u, 1955680031u},
    {"critdam", 7u, 4140065929u},
    {"onAttack", 8u, 3086142220u},
    {"Perfect Amethyst_DESCR", 22u, 2265897535u},
    {"@", 1u, 3305896031u},
    {",", 1u, 688690635u},
    {"GRD", 3u, 2769401224u},
    {"fd=", 3u, 4228204814u},
    {" cp=", 4u, 3282868099u},
    {" aff=", 5u, 2844077393u},
    {"n=", 2u, 271970020u},
    {"PoisonTimer", 11u, 1785938446u},
    {"poisonTimerTimeout", 18u, 792798457u},
};
}

void Gd__gd_core__Card::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_back = gd::GdVal::null();
    this->f_activeFront = gd::GdVal::null();
    this->f_curActivationDelay = gd::GdVal::from_float(0.0);
    this->f_faceUp = gd::GdVal::from_bool(true);
    this->f_activating = gd::GdVal::from_bool(false);
    this->f_chainPosition = gd::gd_neg(gd::GdVal::from_int(1LL));
    this->f_deck = gd::GdVal::null();
    this->f_cardAnimation = gd::GdVal::null();
    this->f_front = gd::GdVal::null();
    this->f_connector = gd::GdVal::null();
    this->f_notInChainMark = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__Card::meta() const { return &META_Gd__gd_core__Card; }
gd::GdVal Gd__gd_core__Card::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Card::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Card::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case gd::SYM_back: out = this->f_back; return true;
        case SYM_GEN_activeFront_878: out = this->f_activeFront; return true;
        case SYM_GEN_curActivationDelay_879: out = this->f_curActivationDelay; return true;
        case SYM_GEN_faceUp_880: out = this->f_faceUp; return true;
        case SYM_GEN_activating_881: out = this->f_activating; return true;
        case SYM_GEN_chainPosition_882: out = this->f_chainPosition; return true;
        case SYM_GEN_deck_883: out = this->f_deck; return true;
        case SYM_GEN_cardAnimation_884: out = this->f_cardAnimation; return true;
        case gd::SYM_front: out = this->f_front; return true;
        case SYM_GEN_connector_885: out = this->f_connector; return true;
        case SYM_GEN_notInChainMark_886: out = this->f_notInChainMark; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Card::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case gd::SYM_back: this->f_back = val; return true;
        case SYM_GEN_activeFront_878: this->f_activeFront = val; return true;
        case SYM_GEN_curActivationDelay_879: this->f_curActivationDelay = gd::gd_coerce_float(val); return true;
        case SYM_GEN_faceUp_880: this->f_faceUp = val; return true;
        case SYM_GEN_activating_881: this->f_activating = val; return true;
        case SYM_GEN_chainPosition_882: this->f_chainPosition = val; return true;
        case SYM_GEN_deck_883: this->f_deck = val; return true;
        case SYM_GEN_cardAnimation_884: this->f_cardAnimation = val; return true;
        case gd::SYM_front: this->f_front = val; return true;
        case SYM_GEN_connector_885: this->f_connector = val; return true;
        case SYM_GEN_notInChainMark_886: this->f_notInChainMark = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Card::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_setFaceUp_887: return true;
        case SYM_GEN_setFaceDown_888: return true;
        case SYM_GEN_updateTexture_889: return true;
        case SYM_GEN_cardSecondaryEffectActive_890: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_prepare_122: return true;
        case SYM_GEN_preCombatStart_124: return true;
        case SYM_GEN_getNextCard_891: return true;
        case SYM_GEN_startActivation_892: return true;
        case SYM_GEN_playActivationAnimation_778: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN_trigger_143: return true;
        case SYM_GEN_combatEnd_131: return true;
        case SYM_GEN_shopEntered_745: return true;
        case SYM_GEN_addToInventory_120: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_notifyChainPosition_894: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_getCardDescription_895: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Card::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_setFaceUp_887: out = fn_setFaceUp(args, argc); return true;
        case SYM_GEN_setFaceDown_888: out = fn_setFaceDown(args, argc); return true;
        case SYM_GEN_updateTexture_889: out = fn_updateTexture(args, argc); return true;
        case SYM_GEN_cardSecondaryEffectActive_890: out = fn_cardSecondaryEffectActive(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_prepare_122: out = fn_prepare(args, argc); return true;
        case SYM_GEN_preCombatStart_124: out = fn_preCombatStart(args, argc); return true;
        case SYM_GEN_getNextCard_891: out = fn_getNextCard(args, argc); return true;
        case SYM_GEN_startActivation_892: out = fn_startActivation(args, argc); return true;
        case SYM_GEN_playActivationAnimation_778: out = fn_playActivationAnimation(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN_trigger_143: out = fn_trigger(args, argc); return true;
        case SYM_GEN_combatEnd_131: out = fn_combatEnd(args, argc); return true;
        case SYM_GEN_shopEntered_745: out = fn_shopEntered(args, argc); return true;
        case SYM_GEN_addToInventory_120: out = fn_addToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_notifyChainPosition_894: out = fn_notifyChainPosition(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_getCardDescription_895: out = fn_getCardDescription(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Card::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Card::fn_setFaceUp(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_faceUp)))) {
        this->f_faceUp = gd::GdVal::from_bool(true);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_setFaceDown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_faceUp)) {
        this->f_faceUp = gd::GdVal::from_bool(false);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_updateTexture(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_faceUp)) {
        if (gd::gd_truth((gd::gd_truth((gd::gd_truth(this->f_deck) ? gd::GdVal::from_bool(gd::gd_truth(this->f_activeFront)) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cardSecondaryEffectActive_890, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        }
        else {
        }
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_cardSecondaryEffectActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(this->f_placed)) {
        return (gd::gd_truth((gd::gd_truth(this->f_deck) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(12LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, lv_item, SYM_GEN_chainPosition_882), this->f_chainPosition))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_item, SYM_GEN_chainPosition_882), gd::gd_neg(gd::GdVal::from_int(1LL))))))))) : gd::GdVal::from_bool(false));
    }
    else {
        return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(12LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_deck_883))))) : gd::GdVal::from_bool(false));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_prepare_122, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_preCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_preCombatStart_124, nullptr, 0, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_99, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_getNextCard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_affected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInAffectedCells_cached_423, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_affected, gd::SYM_empty, nullptr, 0)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(12LL)}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL)), SYM_GEN_hasType_79, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        return gd::get_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL));
    }
    else {
        return gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_startActivation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(this->f_activating) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(this->f_faceUp))))) {
        return gd::GdVal::null();
    }
    this->f_activating = gd::GdVal::from_bool(true);
    this->f_iterationCooldown = gd::gd_coerce_float(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCooldown_102, nullptr, 0));
    this->f_triggerTime = gd::gd_coerce_float(this->f_iterationCooldown);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activateCooldown_98, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(9LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_playActivationAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_aniType = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_activationAni_1717));
    gd::GdVal lv_consume = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(false));
    lv_consume = gd::gd_coerce_bool(lv_consume);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__faceUp = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__faceUp = gd::gd_coerce_bool(lv__faceUp);
    if (gd::gd_truth(lv__faceUp)) {
        if (gd::gd_truth(this->f_faceUp)) {
        }
        else {
        }
    }
    else {
        if (gd::gd_truth(this->f_faceUp)) {
        }
    }
    this->f_faceUp = lv__faceUp;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_trigger(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_activating = gd::GdVal::from_bool(false);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldown_794, _ca, 1); })();
    gd::GdVal lv_nextCard = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNextCard_891, nullptr, 0);
    if (gd::gd_truth(lv_nextCard)) {
        (void)gd::call_method(gd_ctx, lv_nextCard, SYM_GEN_startActivation_892, nullptr, 0);
    }
    this->f_triggerTime = gd::gd_coerce_float(this->f_iterationCooldown);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_99, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doRevealEffect_893, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_combatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_combatEnd_131, nullptr, 0, _out); return _out; })();
    this->f_activating = gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_shopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craft = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_craft = gd::gd_coerce_bool(lv_craft);
    (void)([&]() { gd::GdVal _ca[] = {lv_craft}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_shopEntered_745, _ca, 1, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setFaceUp_887, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_addToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__inventory = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__occupiedCells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__placedByPlayer = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv__placedByPlayer = gd::gd_coerce_bool(lv__placedByPlayer);
    (void)([&]() { gd::GdVal _ca[] = {lv__inventory, lv__occupiedCells, lv__placedByPlayer}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_addToInventory_120, _ca, 3, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_deck = gd::GdVal::null();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateTexture_889, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_notifyChainPosition(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__deck = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__chainPos = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_chainLength = (_argc > 2) ? _args[2] : gd::GdVal::null();
    this->f_chainPosition = lv__chainPos;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_chainPosition, gd::gd_neg(gd::GdVal::from_int(1LL)))))) {
        this->f_deck = gd::GdVal::null();
        if (gd::gd_truth(this->f_placed)) {
        }
    }
    else {
        this->f_deck = lv__deck;
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_chainPosition, gd::gd_sub(lv_chainLength, gd::GdVal::from_int(1LL)))))) {
        }
        else {
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateTexture_889, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_getDescription_642, _ca, 1, _out); return _out; })();
    return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCardDescription_895, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_getCardDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(this->f_deck)) {
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[0]), ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[1])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_tra_2715, _ca, 1); })(), gd::GdVal::from_str(&battle_string_literals[2]), this->f_chainPosition, gd::GdVal::from_int(0LL), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 5); })()));
    }
    else if (gd::gd_truth(this->f_placed)) {
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[0]), ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[3])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_tra_2715, _ca, 1); })(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_paramColor_2717)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_wrapInColor_2771, _ca, 2); })()));
    }
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Card(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Card>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Card = {CLS_Gd__gd_core__Card, "Card", "res://gd_core/Card.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__Card, &Gd__gd_core__Card::get_static_prop_fn, &Gd__gd_core__Card::call_static_fn};

void Gd__gd_core__Bloodthorne::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
    this->f_regenNeeded = gd::GdVal::null();
    this->f_vampirism = gd::GdVal::null();
    this->f_spikes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__Bloodthorne::meta() const { return &META_Gd__gd_core__Bloodthorne; }
gd::GdVal Gd__gd_core__Bloodthorne::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Bloodthorne::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Bloodthorne::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_regenNeeded_942: out = this->f_regenNeeded; return true;
        case SYM_GEN_vampirism_940: out = this->f_vampirism; return true;
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__Bloodthorne::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_regenNeeded_942: this->f_regenNeeded = val; return true;
        case SYM_GEN_vampirism_940: this->f_vampirism = val; return true;
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Bloodthorne::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onVampirismChanged_943: return true;
        case SYM_GEN_onSpikesChanged_944: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Bloodthorne::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onVampirismChanged_943: out = fn_onVampirismChanged(args, argc); return true;
        case SYM_GEN_onSpikesChanged_944: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Bloodthorne::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Bloodthorne::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[4]), gd::GdVal::from_str(&battle_string_literals[5])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[6]), gd::GdVal::from_str(&battle_string_literals[7])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bloodthorne::fn_onVampirismChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_162, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bloodthorne::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_162, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bloodthorne::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        gd::GdVal lv_numRegen = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRegeneration_1233, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_numRegen, this->f_regenNeeded)))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_regenNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_346, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_vampirism, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_spikes, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bloodthorne::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_regenNeeded = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    this->f_vampirism = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    this->f_spikes = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Bloodthorne(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Bloodthorne>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Bloodthorne = {CLS_Gd__gd_core__Bloodthorne, "Bloodthorne", "res://gd_core/Bloodthorne.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__Bloodthorne, &Gd__gd_core__Bloodthorne::get_static_prop_fn, &Gd__gd_core__Bloodthorne::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreCharacter_ID[] = {{"PLAYER", 0LL}, {"OPPONENT", 1LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreCharacter_ID = {"ID", _ekv_Gd__gd_core__CoreCharacter_ID, 2u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreCharacter_Stat[] = {{"Health", 0LL}, {"MaxHealth", 1LL}, {"Stamina", 2LL}, {"MaxStamina", 3LL}, {"Invulnerable", 4LL}, {"Stunned", 5LL}, {"BattleRage", 6LL}, {"ReflectStacks", 7LL}, {"DebuffResistStacks", 8LL}, {"CritStacks", 9LL}, {"DodgeStacks", 10LL}, {"CritResistStacks", 11LL}, {"CritResistance", 12LL}, {"StunResistance", 13LL}, {"HealEfficiency", 14LL}, {"DamageResistance", 15LL}, {"MeleeDmgFactor", 16LL}, {"RangedDmgFactor", 17LL}, {"EffectDmgFactor", 18LL}, {"Unhealing", 19LL}, {"StaminaRegen", 20LL}, {"MaxHealthGain", 21LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreCharacter_Stat = {"Stat", _ekv_Gd__gd_core__CoreCharacter_Stat, 22u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreCharacter_StaminaResult[] = {{"Sufficient", 0LL}, {"Insufficient", 1LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreCharacter_StaminaResult = {"StaminaResult", _ekv_Gd__gd_core__CoreCharacter_StaminaResult, 2u};
void Gd__gd_core__CoreCharacter::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_ctx = gd::GdVal::null();
    this->f_playerId = gd::GdVal::from_int(0);
    this->f_opponent = gd::GdVal::null();
    this->f_isDead = gd::GdVal::from_bool(false);
    this->f_buffs = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_maxHealth = gd::gd_coerce_float(gd::GdVal::from_float(30.0));
    this->f_curHealth = gd::GdVal::from_float(0.0);
    this->f_temporaryMaxHealth = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_temporaryMaxHealthGain = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_baseMaxStamina = gd::GdVal::from_float(0.0);
    this->f_maxStamina = gd::gd_coerce_float(gd::GdVal::from_float(5.0));
    this->f_curStamina = gd::GdVal::from_float(0.0);
    this->f_temporaryMaxStamina = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_baseStaminaRegen = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_staminaRegen = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_allowStaminaOverflow = gd::GdVal::from_bool(false);
    this->f_staminaUpdateQueued = gd::GdVal::from_bool(false);
    this->f_statsDisplay = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_damageResistance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_damageReduction = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_invulnerable = gd::GdVal::from_bool(false);
    this->f_dodgeStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_critResistance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_critResistStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_critTokens = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_stunResistance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_unhealingAmount = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_healingEfficiency = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_critTokensUsed = gd::GdVal::from_int(0LL);
    this->f_debuffResistStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_debuffReflectStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_buffProtectStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_bonusFatigueDamage = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_empowerDamage = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_blindingLightActive = gd::GdVal::from_bool(false);
    this->f_stunnedDuration = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_tickCounter = gd::GdVal::from_int(0LL);
    this->f_typedDamageFactors = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_meleeSpikesLimit = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_rangedSpikesLimit = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_effectSpikesLimit = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_meleeVampirismLimit = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_rangedVampirismLimit = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_battleRageAura = gd::GdVal::null();
    this->f_battleRageBonusDur = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_accuracyRng = gd::GdVal::null();
    this->f_critRng = gd::GdVal::null();
    this->f_critResistanceRng = gd::GdVal::null();
    this->f_stunResistanceRng = gd::GdVal::null();
    this->f_items = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_inventory = gd::GdVal::null();
    this->f_INVENTORY = gd::GdVal::null();
    this->f_character_died_handlers = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_poisonDamageSource = gd::GdVal::null();
    this->f_spikeDamageSource = gd::GdVal::null();
    this->f_characterClass = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_chibi = gd::GdVal::from_bool(false);
    this->f_invulnerabilityItem = gd::GdVal::null();
    this->f__invul_left = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f__invul_active = gd::GdVal::from_bool(false);
    this->f_autoRageItem = gd::GdVal::null();
    this->f__rage_left = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f__rage_active = gd::GdVal::from_bool(false);
    this->f__autoRage_left = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f__autoRage_active = gd::GdVal::from_bool(false);
    this->f__rage_wait = gd::GdVal::from_float(1.0);
    this->f__invul_wait = gd::GdVal::from_float(1.0);
    this->f_attack_moving_forward = gd::GdVal::from_bool(false);
    this->f_attack_sound_ready_time = gd::gd_neg(gd::GdVal::from_float(1.0));
    this->f__tick_timer_left = gd::GdVal::from_float(0.0);
    this->f__tick_timer_active = gd::GdVal::from_bool(false);
    this->f_damage_anim_current = gd::GdVal::from_str(&battle_string_literals[8]);
    this->f__visual_x = gd::GdVal::from_float(0.0);
    this->f__visual_y = gd::GdVal::from_float(0.0);
    this->f__visual_from_x = gd::GdVal::from_float(0.0);
    this->f__visual_from_y = gd::GdVal::from_float(0.0);
    this->f__visual_to_x = gd::GdVal::from_float(0.0);
    this->f__visual_to_y = gd::GdVal::from_float(0.0);
    this->f__visual_forward = gd::GdVal::from_float(0.0);
    this->f__visual_back = gd::GdVal::from_float(0.0);
    this->f__visual_elapsed = gd::GdVal::from_float(0.0);
    this->f__visual_kind = gd::GdVal::from_int(0LL);
    this->f__visual_stage = gd::GdVal::from_int(0LL);
    this->f__visual_generation = gd::GdVal::from_int(0LL);
    this->f__idle_animation_left = gd::GdVal::from_float(1.0);
    this->f__physics_timer_mask = gd::GdVal::from_int(0LL);
}
const gd::GdClassMeta* Gd__gd_core__CoreCharacter::meta() const { return &META_Gd__gd_core__CoreCharacter; }
gd::GdVal Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_ID_1297: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreCharacter_ID);
        case SYM_GEN_Stat_870: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreCharacter_Stat);
        case SYM_GEN_StaminaResult_1298: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreCharacter_StaminaResult);
        case SYM_GEN_AUTO_RAGE_DELAY_1044: return gd::GdVal::from_float(5.0);
        case SYM_GEN_AUTO_RAGE_DUR_1045: return gd::GdVal::from_float(4.0);
        case SYM_GEN_CLASS_SOUND_COUNTS_1127: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 7); d->set(gd_ctx.arena, gd::GdVal::from_int(0LL), ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 3); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[9]), gd::GdVal::from_int(3LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[10]), gd::GdVal::from_int(6LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[11]), gd::GdVal::from_int(6LL)); return gd::GdVal::from_dict(d); })()); d->set(gd_ctx.arena, gd::GdVal::from_int(1LL), ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 3); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[9]), gd::GdVal::from_int(3LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[10]), gd::GdVal::from_int(2LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[11]), gd::GdVal::from_int(4LL)); return gd::GdVal::from_dict(d); })()); d->set(gd_ctx.arena, gd::GdVal::from_int(2LL), ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 3); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[9]), gd::GdVal::from_int(3LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[10]), gd::GdVal::from_int(4LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[11]), gd::GdVal::from_int(6LL)); return gd::GdVal::from_dict(d); })()); d->set(gd_ctx.arena, gd::GdVal::from_int(3LL), ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 3); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[9]), gd::GdVal::from_int(5LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[10]), gd::GdVal::from_int(4LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[11]), gd::GdVal::from_int(4LL)); return gd::GdVal::from_dict(d); })()); d->set(gd_ctx.arena, gd::GdVal::from_int(4LL), ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 3); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[9]), gd::GdVal::from_int(3LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[10]), gd::GdVal::from_int(6LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[11]), gd::GdVal::from_int(5LL)); return gd::GdVal::from_dict(d); })()); d->set(gd_ctx.arena, gd::GdVal::from_int(5LL), ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 3); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[9]), gd::GdVal::from_int(4LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[10]), gd::GdVal::from_int(7LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[11]), gd::GdVal::from_int(6LL)); return gd::GdVal::from_dict(d); })()); d->set(gd_ctx.arena, gd::GdVal::from_int(6LL), ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 3); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[9]), gd::GdVal::from_int(6LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[10]), gd::GdVal::from_int(5LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[11]), gd::GdVal::from_int(8LL)); return gd::GdVal::from_dict(d); })()); return gd::GdVal::from_dict(d); })();
        default: break;
    }
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreCharacter::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreCharacter::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_ctx_3: out = this->f_ctx; return true;
        case SYM_GEN_playerId_1046: out = this->f_playerId; return true;
        case SYM_GEN_opponent_75: out = this->f_opponent; return true;
        case SYM_GEN_isDead_1047: out = this->f_isDead; return true;
        case SYM_GEN_buffs_1048: out = this->f_buffs; return true;
        case SYM_GEN_maxHealth_1049: out = this->f_maxHealth; return true;
        case SYM_GEN_curHealth_1050: out = this->f_curHealth; return true;
        case SYM_GEN_temporaryMaxHealth_1051: out = this->f_temporaryMaxHealth; return true;
        case SYM_GEN_temporaryMaxHealthGain_1052: out = this->f_temporaryMaxHealthGain; return true;
        case SYM_GEN_baseMaxStamina_1053: out = this->f_baseMaxStamina; return true;
        case SYM_GEN_maxStamina_1054: out = this->f_maxStamina; return true;
        case SYM_GEN_curStamina_1055: out = this->f_curStamina; return true;
        case SYM_GEN_temporaryMaxStamina_1056: out = this->f_temporaryMaxStamina; return true;
        case SYM_GEN_baseStaminaRegen_1057: out = this->f_baseStaminaRegen; return true;
        case SYM_GEN_staminaRegen_1058: out = this->f_staminaRegen; return true;
        case SYM_GEN_allowStaminaOverflow_1059: out = this->f_allowStaminaOverflow; return true;
        case SYM_GEN_staminaUpdateQueued_1060: out = this->f_staminaUpdateQueued; return true;
        case SYM_GEN_statsDisplay_1061: out = this->f_statsDisplay; return true;
        case SYM_GEN_damageResistance_1062: out = this->f_damageResistance; return true;
        case SYM_GEN_damageReduction_1063: out = this->f_damageReduction; return true;
        case SYM_GEN_invulnerable_1064: out = this->f_invulnerable; return true;
        case SYM_GEN_dodgeStacks_1065: out = this->f_dodgeStacks; return true;
        case SYM_GEN_critResistance_1066: out = this->f_critResistance; return true;
        case SYM_GEN_critResistStacks_1067: out = this->f_critResistStacks; return true;
        case SYM_GEN_critTokens_16: out = this->f_critTokens; return true;
        case SYM_GEN_stunResistance_1068: out = this->f_stunResistance; return true;
        case SYM_GEN_unhealingAmount_1069: out = this->f_unhealingAmount; return true;
        case SYM_GEN_healingEfficiency_1070: out = this->f_healingEfficiency; return true;
        case SYM_GEN_critTokensUsed_1071: out = this->f_critTokensUsed; return true;
        case SYM_GEN_debuffResistStacks_1072: out = this->f_debuffResistStacks; return true;
        case SYM_GEN_debuffReflectStacks_1073: out = this->f_debuffReflectStacks; return true;
        case SYM_GEN_buffProtectStacks_1074: out = this->f_buffProtectStacks; return true;
        case SYM_GEN_bonusFatigueDamage_1075: out = this->f_bonusFatigueDamage; return true;
        case SYM_GEN_empowerDamage_1076: out = this->f_empowerDamage; return true;
        case SYM_GEN_blindingLightActive_1077: out = this->f_blindingLightActive; return true;
        case SYM_GEN_stunnedDuration_1078: out = this->f_stunnedDuration; return true;
        case SYM_GEN_tickCounter_1079: out = this->f_tickCounter; return true;
        case SYM_GEN_typedDamageFactors_1080: out = this->f_typedDamageFactors; return true;
        case SYM_GEN_meleeSpikesLimit_1081: out = this->f_meleeSpikesLimit; return true;
        case SYM_GEN_rangedSpikesLimit_1082: out = this->f_rangedSpikesLimit; return true;
        case SYM_GEN_effectSpikesLimit_1083: out = this->f_effectSpikesLimit; return true;
        case SYM_GEN_meleeVampirismLimit_1084: out = this->f_meleeVampirismLimit; return true;
        case SYM_GEN_rangedVampirismLimit_1085: out = this->f_rangedVampirismLimit; return true;
        case SYM_GEN_battleRageAura_1086: out = this->f_battleRageAura; return true;
        case SYM_GEN_battleRageBonusDur_1087: out = this->f_battleRageBonusDur; return true;
        case SYM_GEN_accuracyRng_1088: out = this->f_accuracyRng; return true;
        case SYM_GEN_critRng_1089: out = this->f_critRng; return true;
        case SYM_GEN_critResistanceRng_1090: out = this->f_critResistanceRng; return true;
        case SYM_GEN_stunResistanceRng_1091: out = this->f_stunResistanceRng; return true;
        case SYM_GEN_items_1092: out = this->f_items; return true;
        case SYM_GEN_inventory_5: out = this->f_inventory; return true;
        case SYM_GEN_INVENTORY_1093: out = this->f_INVENTORY; return true;
        case SYM_GEN_character_died_handlers_1094: out = this->f_character_died_handlers; return true;
        case SYM_GEN_poisonDamageSource_1095: out = this->f_poisonDamageSource; return true;
        case SYM_GEN_spikeDamageSource_1096: out = this->f_spikeDamageSource; return true;
        case SYM_GEN_characterClass_1097: out = this->f_characterClass; return true;
        case SYM_GEN_chibi_1098: out = this->f_chibi; return true;
        case SYM_GEN_invulnerabilityItem_1099: out = this->f_invulnerabilityItem; return true;
        case SYM_GEN__invul_left_1100: out = this->f__invul_left; return true;
        case SYM_GEN__invul_active_1101: out = this->f__invul_active; return true;
        case SYM_GEN_autoRageItem_1102: out = this->f_autoRageItem; return true;
        case SYM_GEN__rage_left_1103: out = this->f__rage_left; return true;
        case SYM_GEN__rage_active_1104: out = this->f__rage_active; return true;
        case SYM_GEN__autoRage_left_1105: out = this->f__autoRage_left; return true;
        case SYM_GEN__autoRage_active_1106: out = this->f__autoRage_active; return true;
        case SYM_GEN__rage_wait_1107: out = this->f__rage_wait; return true;
        case SYM_GEN__invul_wait_1108: out = this->f__invul_wait; return true;
        case SYM_GEN_attack_moving_forward_1109: out = this->f_attack_moving_forward; return true;
        case SYM_GEN_attack_sound_ready_time_1110: out = this->f_attack_sound_ready_time; return true;
        case SYM_GEN__tick_timer_left_1111: out = this->f__tick_timer_left; return true;
        case SYM_GEN__tick_timer_active_1112: out = this->f__tick_timer_active; return true;
        case SYM_GEN_damage_anim_current_1113: out = this->f_damage_anim_current; return true;
        case SYM_GEN__visual_x_1114: out = this->f__visual_x; return true;
        case SYM_GEN__visual_y_1115: out = this->f__visual_y; return true;
        case SYM_GEN__visual_from_x_1116: out = this->f__visual_from_x; return true;
        case SYM_GEN__visual_from_y_1117: out = this->f__visual_from_y; return true;
        case SYM_GEN__visual_to_x_1118: out = this->f__visual_to_x; return true;
        case SYM_GEN__visual_to_y_1119: out = this->f__visual_to_y; return true;
        case SYM_GEN__visual_forward_1120: out = this->f__visual_forward; return true;
        case SYM_GEN__visual_back_1121: out = this->f__visual_back; return true;
        case SYM_GEN__visual_elapsed_1122: out = this->f__visual_elapsed; return true;
        case SYM_GEN__visual_kind_1123: out = this->f__visual_kind; return true;
        case SYM_GEN__visual_stage_1124: out = this->f__visual_stage; return true;
        case SYM_GEN__visual_generation_1125: out = this->f__visual_generation; return true;
        case SYM_GEN__idle_animation_left_1126: out = this->f__idle_animation_left; return true;
        case SYM_GEN__physics_timer_mask_1128: out = this->f__physics_timer_mask; return true;
        case SYM_GEN_ID_1297: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreCharacter_ID); return true;
        case SYM_GEN_Stat_870: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreCharacter_Stat); return true;
        case SYM_GEN_StaminaResult_1298: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreCharacter_StaminaResult); return true;
        case SYM_GEN_AUTO_RAGE_DELAY_1044: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_AUTO_RAGE_DUR_1045: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_CLASS_SOUND_COUNTS_1127: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreCharacter::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_ctx_3: this->f_ctx = val; return true;
        case SYM_GEN_playerId_1046: this->f_playerId = gd::gd_coerce_int(val); return true;
        case SYM_GEN_opponent_75: this->f_opponent = val; return true;
        case SYM_GEN_isDead_1047: this->f_isDead = val; return true;
        case SYM_GEN_buffs_1048: this->f_buffs = val; return true;
        case SYM_GEN_maxHealth_1049: this->f_maxHealth = gd::gd_coerce_float(val); return true;
        case SYM_GEN_curHealth_1050: this->f_curHealth = gd::gd_coerce_float(val); return true;
        case SYM_GEN_temporaryMaxHealth_1051: this->f_temporaryMaxHealth = gd::gd_coerce_float(val); return true;
        case SYM_GEN_temporaryMaxHealthGain_1052: this->f_temporaryMaxHealthGain = gd::gd_coerce_float(val); return true;
        case SYM_GEN_baseMaxStamina_1053: this->f_baseMaxStamina = gd::gd_coerce_float(val); return true;
        case SYM_GEN_maxStamina_1054: this->f_maxStamina = gd::gd_coerce_float(val); return true;
        case SYM_GEN_curStamina_1055: this->f_curStamina = gd::gd_coerce_float(val); return true;
        case SYM_GEN_temporaryMaxStamina_1056: this->f_temporaryMaxStamina = gd::gd_coerce_float(val); return true;
        case SYM_GEN_baseStaminaRegen_1057: this->f_baseStaminaRegen = gd::gd_coerce_float(val); return true;
        case SYM_GEN_staminaRegen_1058: this->f_staminaRegen = gd::gd_coerce_float(val); return true;
        case SYM_GEN_allowStaminaOverflow_1059: this->f_allowStaminaOverflow = val; return true;
        case SYM_GEN_staminaUpdateQueued_1060: this->f_staminaUpdateQueued = val; return true;
        case SYM_GEN_statsDisplay_1061: this->f_statsDisplay = val; return true;
        case SYM_GEN_damageResistance_1062: this->f_damageResistance = gd::gd_coerce_float(val); return true;
        case SYM_GEN_damageReduction_1063: this->f_damageReduction = gd::gd_coerce_int(val); return true;
        case SYM_GEN_invulnerable_1064: this->f_invulnerable = val; return true;
        case SYM_GEN_dodgeStacks_1065: this->f_dodgeStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_critResistance_1066: this->f_critResistance = gd::gd_coerce_float(val); return true;
        case SYM_GEN_critResistStacks_1067: this->f_critResistStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_critTokens_16: this->f_critTokens = gd::gd_coerce_int(val); return true;
        case SYM_GEN_stunResistance_1068: this->f_stunResistance = gd::gd_coerce_float(val); return true;
        case SYM_GEN_unhealingAmount_1069: this->f_unhealingAmount = gd::gd_coerce_float(val); return true;
        case SYM_GEN_healingEfficiency_1070: this->f_healingEfficiency = gd::gd_coerce_float(val); return true;
        case SYM_GEN_critTokensUsed_1071: this->f_critTokensUsed = val; return true;
        case SYM_GEN_debuffResistStacks_1072: this->f_debuffResistStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_debuffReflectStacks_1073: this->f_debuffReflectStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_buffProtectStacks_1074: this->f_buffProtectStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_bonusFatigueDamage_1075: this->f_bonusFatigueDamage = gd::gd_coerce_int(val); return true;
        case SYM_GEN_empowerDamage_1076: this->f_empowerDamage = gd::gd_coerce_float(val); return true;
        case SYM_GEN_blindingLightActive_1077: this->f_blindingLightActive = val; return true;
        case SYM_GEN_stunnedDuration_1078: this->f_stunnedDuration = gd::gd_coerce_float(val); return true;
        case SYM_GEN_tickCounter_1079: this->f_tickCounter = val; return true;
        case SYM_GEN_typedDamageFactors_1080: this->f_typedDamageFactors = val; return true;
        case SYM_GEN_meleeSpikesLimit_1081: this->f_meleeSpikesLimit = gd::gd_coerce_float(val); return true;
        case SYM_GEN_rangedSpikesLimit_1082: this->f_rangedSpikesLimit = gd::gd_coerce_float(val); return true;
        case SYM_GEN_effectSpikesLimit_1083: this->f_effectSpikesLimit = gd::gd_coerce_float(val); return true;
        case SYM_GEN_meleeVampirismLimit_1084: this->f_meleeVampirismLimit = gd::gd_coerce_float(val); return true;
        case SYM_GEN_rangedVampirismLimit_1085: this->f_rangedVampirismLimit = gd::gd_coerce_float(val); return true;
        case SYM_GEN_battleRageAura_1086: this->f_battleRageAura = val; return true;
        case SYM_GEN_battleRageBonusDur_1087: this->f_battleRageBonusDur = gd::gd_coerce_float(val); return true;
        case SYM_GEN_accuracyRng_1088: this->f_accuracyRng = val; return true;
        case SYM_GEN_critRng_1089: this->f_critRng = val; return true;
        case SYM_GEN_critResistanceRng_1090: this->f_critResistanceRng = val; return true;
        case SYM_GEN_stunResistanceRng_1091: this->f_stunResistanceRng = val; return true;
        case SYM_GEN_items_1092: this->f_items = val; return true;
        case SYM_GEN_inventory_5: this->f_inventory = val; return true;
        case SYM_GEN_INVENTORY_1093: this->f_INVENTORY = val; return true;
        case SYM_GEN_character_died_handlers_1094: this->f_character_died_handlers = val; return true;
        case SYM_GEN_poisonDamageSource_1095: this->f_poisonDamageSource = val; return true;
        case SYM_GEN_spikeDamageSource_1096: this->f_spikeDamageSource = val; return true;
        case SYM_GEN_characterClass_1097: this->f_characterClass = gd::gd_coerce_int(val); return true;
        case SYM_GEN_chibi_1098: this->f_chibi = val; return true;
        case SYM_GEN_invulnerabilityItem_1099: this->f_invulnerabilityItem = val; return true;
        case SYM_GEN__invul_left_1100: this->f__invul_left = gd::gd_coerce_float(val); return true;
        case SYM_GEN__invul_active_1101: this->f__invul_active = val; return true;
        case SYM_GEN_autoRageItem_1102: this->f_autoRageItem = val; return true;
        case SYM_GEN__rage_left_1103: this->f__rage_left = gd::gd_coerce_float(val); return true;
        case SYM_GEN__rage_active_1104: this->f__rage_active = val; return true;
        case SYM_GEN__autoRage_left_1105: this->f__autoRage_left = gd::gd_coerce_float(val); return true;
        case SYM_GEN__autoRage_active_1106: this->f__autoRage_active = val; return true;
        case SYM_GEN__rage_wait_1107: this->f__rage_wait = val; return true;
        case SYM_GEN__invul_wait_1108: this->f__invul_wait = val; return true;
        case SYM_GEN_attack_moving_forward_1109: this->f_attack_moving_forward = val; return true;
        case SYM_GEN_attack_sound_ready_time_1110: this->f_attack_sound_ready_time = val; return true;
        case SYM_GEN__tick_timer_left_1111: this->f__tick_timer_left = val; return true;
        case SYM_GEN__tick_timer_active_1112: this->f__tick_timer_active = val; return true;
        case SYM_GEN_damage_anim_current_1113: this->f_damage_anim_current = val; return true;
        case SYM_GEN__visual_x_1114: this->f__visual_x = val; return true;
        case SYM_GEN__visual_y_1115: this->f__visual_y = val; return true;
        case SYM_GEN__visual_from_x_1116: this->f__visual_from_x = val; return true;
        case SYM_GEN__visual_from_y_1117: this->f__visual_from_y = val; return true;
        case SYM_GEN__visual_to_x_1118: this->f__visual_to_x = val; return true;
        case SYM_GEN__visual_to_y_1119: this->f__visual_to_y = val; return true;
        case SYM_GEN__visual_forward_1120: this->f__visual_forward = val; return true;
        case SYM_GEN__visual_back_1121: this->f__visual_back = val; return true;
        case SYM_GEN__visual_elapsed_1122: this->f__visual_elapsed = val; return true;
        case SYM_GEN__visual_kind_1123: this->f__visual_kind = val; return true;
        case SYM_GEN__visual_stage_1124: this->f__visual_stage = val; return true;
        case SYM_GEN__visual_generation_1125: this->f__visual_generation = val; return true;
        case SYM_GEN__idle_animation_left_1126: this->f__idle_animation_left = val; return true;
        case SYM_GEN__physics_timer_mask_1128: this->f__physics_timer_mask = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreCharacter::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_setOpponent_1129: return true;
        case SYM_GEN_isPlayer_78: return true;
        case SYM_GEN_getName_234: return true;
        case SYM_GEN_registerCharacterDied_1130: return true;
        case SYM_GEN_clearCharacterDiedHandlers_1131: return true;
        case SYM_GEN_prepare_122: return true;
        case SYM_GEN_combatStart_127: return true;
        case SYM_GEN_combatEnd_131: return true;
        case SYM_GEN_attackMovingForward_reset_1132: return true;
        case SYM_GEN_cleanse_1133: return true;
        case SYM_GEN_onTick_1134: return true;
        case SYM_GEN__beginVisualMotion_1135: return true;
        case SYM_GEN_tickVisualMotion_1137: return true;
        case SYM_GEN_tickIdleAnimation_1138: return true;
        case SYM_GEN_playAttackAnimation_1139: return true;
        case SYM_GEN_classAttackSoundCount_1140: return true;
        case SYM_GEN_classRoundSoundCount_1141: return true;
        case SYM_GEN_playActivateAnimation_1142: return true;
        case SYM_GEN_randBuffLabelPos_1143: return true;
        case SYM_GEN_randBuffLabelDir_1144: return true;
        case SYM_GEN_randDmgNumberPos_1145: return true;
        case SYM_GEN_randDmgNumberDir_1146: return true;
        case SYM_GEN_randHealNumberPos_1147: return true;
        case SYM_GEN_dealDamage_220: return true;
        case SYM_GEN_takeDamage_1148: return true;
        case SYM_GEN_spawnLabel_native_1149: return true;
        case SYM_GEN_applySpikes_1150: return true;
        case SYM_GEN_applyVampirism_1151: return true;
        case SYM_GEN_heal_327: return true;
        case SYM_GEN_healToFull_1152: return true;
        case SYM_GEN_reincarnate_1153: return true;
        case SYM_GEN_getCurrentHealth_1154: return true;
        case SYM_GEN_getRelativeHealth_302: return true;
        case SYM_GEN_getMissingHealth_1155: return true;
        case SYM_GEN_setCurrentHealth_1156: return true;
        case SYM_GEN_loseHealth_1157: return true;
        case SYM_GEN_setMaxHealth_1158: return true;
        case SYM_GEN_giveMaxHealth_317: return true;
        case SYM_GEN_getBaseMaxHealth_1159: return true;
        case SYM_GEN_getMaxHealth_1160: return true;
        case SYM_GEN_applyTemporaryMaxHealthGain_1161: return true;
        case SYM_GEN_changeMaxHealthTemporary_1162: return true;
        case SYM_GEN_getMaxStamina_1163: return true;
        case SYM_GEN_gainStamina_1164: return true;
        case SYM_GEN_addStamina_1165: return true;
        case SYM_GEN_clampStamina_1166: return true;
        case SYM_GEN_fillUpStamina_300: return true;
        case SYM_GEN_useStamina_116: return true;
        case SYM_GEN_drainStamina_117: return true;
        case SYM_GEN_setTemporaryMaxStamina_1167: return true;
        case SYM_GEN_setTemporaryMaxHealthGain_1168: return true;
        case SYM_GEN_death_1169: return true;
        case SYM_GEN_stun_330: return true;
        case SYM_GEN_endStun_1170: return true;
        case SYM_GEN_isStunned_1171: return true;
        case SYM_GEN_changeDodgeStacks_1172: return true;
        case SYM_GEN_changeCritResistance_1173: return true;
        case SYM_GEN_critResisted_1174: return true;
        case SYM_GEN_gainCritResistStacks_1175: return true;
        case SYM_GEN_changeStunResistance_1176: return true;
        case SYM_GEN_stunResisted_1177: return true;
        case SYM_GEN_giveUnhealing_1178: return true;
        case SYM_GEN_reduceUnhealing_1179: return true;
        case SYM_GEN_getUnhealing_1180: return true;
        case SYM_GEN_getHealingEfficiency_1181: return true;
        case SYM_GEN_addHealingEfficiency_1182: return true;
        case SYM_GEN_reduceHealingEfficiency_1183: return true;
        case SYM_GEN_getCritTokens_182: return true;
        case SYM_GEN_gainCritTokens_1184: return true;
        case SYM_GEN_changeDebuffResistStacks_1185: return true;
        case SYM_GEN_changeDebuffReflectStacks_1186: return true;
        case SYM_GEN_changeBuffProtectStacks_1187: return true;
        case SYM_GEN_changeReflectChance_1029: return true;
        case SYM_GEN_changeAllDebuffsReflectChance_1188: return true;
        case SYM_GEN_changeMeleeSpikesLimit_1189: return true;
        case SYM_GEN_changeRangedSpikesLimit_1190: return true;
        case SYM_GEN_changeEffectSpikesLimit_1191: return true;
        case SYM_GEN_changeMeleeVampirismLimit_1192: return true;
        case SYM_GEN_changeRangedVampirismLimit_1193: return true;
        case SYM_GEN_getBonusFatigueDamage_1194: return true;
        case SYM_GEN_addFatigueDamage_1195: return true;
        case SYM_GEN_takeFatigueDamage_1196: return true;
        case SYM_GEN_startBlindingLight_1197: return true;
        case SYM_GEN_endBlindingLight_1198: return true;
        case SYM_GEN_startBattleRage_1199: return true;
        case SYM_GEN_endBattleRage_1200: return true;
        case SYM_GEN_getClass_1201: return true;
        case SYM_GEN_isChibi_1202: return true;
        case SYM_GEN_setClass_1203: return true;
        case SYM_GEN_setClassResource_1204: return true;
        case SYM_GEN_lose_1205: return true;
        case SYM_GEN_win_1206: return true;
        case SYM_GEN_setStat_115: return true;
        case SYM_GEN_getStat_261: return true;
        case SYM_GEN_isBattleRaging_1207: return true;
        case SYM_GEN_startAutoRage_1208: return true;
        case SYM_GEN_playBattleRageAnimation_1209: return true;
        case SYM_GEN__setRageTimer_1210: return true;
        case SYM_GEN_makeInvulnerable_1211: return true;
        case SYM_GEN_makeVulnerable_1212: return true;
        case SYM_GEN_invulnerabilityEnded_1213: return true;
        case SYM_GEN_setInvulnerable_1214: return true;
        case SYM_GEN_getStacks_1023: return true;
        case SYM_GEN_getBuffStacks_1215: return true;
        case SYM_GEN_getDebuffStacks_1216: return true;
        case SYM_GEN_setStacks_1024: return true;
        case SYM_GEN_setStacksLogged_1217: return true;
        case SYM_GEN_gainStacks_1030: return true;
        case SYM_GEN_gainStacksTemporary_1218: return true;
        case SYM_GEN_loseStacks_1032: return true;
        case SYM_GEN_useStacks_1219: return true;
        case SYM_GEN_changeResistChance_1026: return true;
        case SYM_GEN_changeDebuffResistChances_1220: return true;
        case SYM_GEN_changeResistStacks_1027: return true;
        case SYM_GEN_getBlock_204: return true;
        case SYM_GEN_setBlock_1221: return true;
        case SYM_GEN_gainBlock_1222: return true;
        case SYM_GEN_loseBlock_206: return true;
        case SYM_GEN_getSpikes_1223: return true;
        case SYM_GEN_setSpikes_1224: return true;
        case SYM_GEN_gainSpikes_1225: return true;
        case SYM_GEN_loseSpikes_338: return true;
        case SYM_GEN_getVampirism_1226: return true;
        case SYM_GEN_setVampirism_1227: return true;
        case SYM_GEN_gainVampirism_1228: return true;
        case SYM_GEN_loseVampirism_341: return true;
        case SYM_GEN_getPoison_1229: return true;
        case SYM_GEN_setPoison_1230: return true;
        case SYM_GEN_gainPoison_1231: return true;
        case SYM_GEN_losePoison_1232: return true;
        case SYM_GEN_getRegeneration_1233: return true;
        case SYM_GEN_setRegeneration_1234: return true;
        case SYM_GEN_gainRegeneration_1235: return true;
        case SYM_GEN_loseRegeneration_1236: return true;
        case SYM_GEN_getLucky_1237: return true;
        case SYM_GEN_setLucky_1238: return true;
        case SYM_GEN_gainLucky_1239: return true;
        case SYM_GEN_loseLucky_348: return true;
        case SYM_GEN_getBlind_1240: return true;
        case SYM_GEN_setBlind_1241: return true;
        case SYM_GEN_gainBlind_1242: return true;
        case SYM_GEN_loseBlind_1243: return true;
        case SYM_GEN_getMana_1244: return true;
        case SYM_GEN_setMana_1245: return true;
        case SYM_GEN_gainMana_1246: return true;
        case SYM_GEN_loseMana_1247: return true;
        case SYM_GEN_getEmpower_1248: return true;
        case SYM_GEN_setEmpower_1249: return true;
        case SYM_GEN_gainEmpower_1250: return true;
        case SYM_GEN_loseEmpower_355: return true;
        case SYM_GEN_getHeat_1251: return true;
        case SYM_GEN_setHeat_1252: return true;
        case SYM_GEN_gainHeat_1253: return true;
        case SYM_GEN_loseHeat_353: return true;
        case SYM_GEN_getCold_1254: return true;
        case SYM_GEN_setCold_1255: return true;
        case SYM_GEN_gainCold_1256: return true;
        case SYM_GEN_loseCold_1257: return true;
        case SYM_GEN_getBuffDamageMod_1258: return true;
        case SYM_GEN_getBuffAccuracyMod_1259: return true;
        case SYM_GEN_getBaseMaxStamina_1260: return true;
        case SYM_GEN_getMaxBaseStamina_1261: return true;
        case SYM_GEN_getCurrentStamina_1262: return true;
        case SYM_GEN_setCurrentStamina_1263: return true;
        case SYM_GEN_getMissingStamina_1264: return true;
        case SYM_GEN_isFullStamina_1265: return true;
        case SYM_GEN_setMaxStamina_1266: return true;
        case SYM_GEN_giveMaxStamina_315: return true;
        case SYM_GEN_reduceMaxStamina_1267: return true;
        case SYM_GEN_gainMaxStaminaTemporary_1268: return true;
        case SYM_GEN_getStaminaRegeneration_1269: return true;
        case SYM_GEN_giveStaminaRegeneration_1270: return true;
        case SYM_GEN_getTotalStaminaUsage_1271: return true;
        case SYM_GEN_changeBaseMaxStamina_1272: return true;
        case SYM_GEN_recalculateMaxStamina_1273: return true;
        case SYM_GEN_getTemporaryMaxHealth_1274: return true;
        case SYM_GEN_setTemporaryMaxHealth_1275: return true;
        case SYM_GEN_reduceMaxHealth_1276: return true;
        case SYM_GEN_changeMaxHealthGain_1277: return true;
        case SYM_GEN_changeDamageReduction_1278: return true;
        case SYM_GEN_changeDamageResistance_1279: return true;
        case SYM_GEN_changeTypedDamageFactor_1280: return true;
        case SYM_GEN_changeEffectDamageFactor_1281: return true;
        case SYM_GEN_changeEmpowerDamage_1282: return true;
        case SYM_GEN_changePoisonCritChancePercent_1283: return true;
        case SYM_GEN_changeSpikesCritChancePercent_1284: return true;
        case SYM_GEN_useCritToken_184: return true;
        case SYM_GEN_useMana_332: return true;
        case SYM_GEN_changeProtectionChance_1285: return true;
        case SYM_GEN_changeBuffProtectionChance_1286: return true;
        case SYM_GEN_changeDebuffProtectionChance_1287: return true;
        case SYM_GEN_changeBuffNullifyChances_1288: return true;
        case SYM_GEN_changeDebuffNullifyChances_1289: return true;
        case SYM_GEN_addBattleRageDuration_1290: return true;
        case SYM_GEN_isVulnerable_1291: return true;
        case SYM_GEN_physicsTickCharacter_1292: return true;
        case SYM_GEN_tickPhysicsTimers_1293: return true;
        case SYM_GEN_tickBuffs_1294: return true;
        case SYM_GEN_rebuildTimerSeen_139: return true;
        case SYM_GEN_snapshotPhysicsTimers_1295: return true;
        case SYM_GEN__startInvulnerability_1296: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreCharacter::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_setOpponent_1129: out = fn_setOpponent(args, argc); return true;
        case SYM_GEN_isPlayer_78: out = fn_isPlayer(args, argc); return true;
        case SYM_GEN_getName_234: out = fn_getName(args, argc); return true;
        case SYM_GEN_registerCharacterDied_1130: out = fn_registerCharacterDied(args, argc); return true;
        case SYM_GEN_clearCharacterDiedHandlers_1131: out = fn_clearCharacterDiedHandlers(args, argc); return true;
        case SYM_GEN_prepare_122: out = fn_prepare(args, argc); return true;
        case SYM_GEN_combatStart_127: out = fn_combatStart(args, argc); return true;
        case SYM_GEN_combatEnd_131: out = fn_combatEnd(args, argc); return true;
        case SYM_GEN_attackMovingForward_reset_1132: out = fn_attackMovingForward_reset(args, argc); return true;
        case SYM_GEN_cleanse_1133: out = fn_cleanse(args, argc); return true;
        case SYM_GEN_onTick_1134: out = fn_onTick(args, argc); return true;
        case SYM_GEN__beginVisualMotion_1135: out = fn__beginVisualMotion(args, argc); return true;
        case SYM_GEN__visualLerp_1136: out = sf__visualLerp(gd_ctx, args, argc); return true;
        case SYM_GEN_tickVisualMotion_1137: out = fn_tickVisualMotion(args, argc); return true;
        case SYM_GEN_tickIdleAnimation_1138: out = fn_tickIdleAnimation(args, argc); return true;
        case SYM_GEN_playAttackAnimation_1139: out = fn_playAttackAnimation(args, argc); return true;
        case SYM_GEN_classAttackSoundCount_1140: out = fn_classAttackSoundCount(args, argc); return true;
        case SYM_GEN_classRoundSoundCount_1141: out = fn_classRoundSoundCount(args, argc); return true;
        case SYM_GEN_playActivateAnimation_1142: out = fn_playActivateAnimation(args, argc); return true;
        case SYM_GEN_randBuffLabelPos_1143: out = fn_randBuffLabelPos(args, argc); return true;
        case SYM_GEN_randBuffLabelDir_1144: out = fn_randBuffLabelDir(args, argc); return true;
        case SYM_GEN_randDmgNumberPos_1145: out = fn_randDmgNumberPos(args, argc); return true;
        case SYM_GEN_randDmgNumberDir_1146: out = fn_randDmgNumberDir(args, argc); return true;
        case SYM_GEN_randHealNumberPos_1147: out = fn_randHealNumberPos(args, argc); return true;
        case SYM_GEN_dealDamage_220: out = fn_dealDamage(args, argc); return true;
        case SYM_GEN_takeDamage_1148: out = fn_takeDamage(args, argc); return true;
        case SYM_GEN_spawnLabel_native_1149: out = fn_spawnLabel_native(args, argc); return true;
        case SYM_GEN_applySpikes_1150: out = fn_applySpikes(args, argc); return true;
        case SYM_GEN_applyVampirism_1151: out = fn_applyVampirism(args, argc); return true;
        case SYM_GEN_heal_327: out = fn_heal(args, argc); return true;
        case SYM_GEN_healToFull_1152: out = fn_healToFull(args, argc); return true;
        case SYM_GEN_reincarnate_1153: out = fn_reincarnate(args, argc); return true;
        case SYM_GEN_getCurrentHealth_1154: out = fn_getCurrentHealth(args, argc); return true;
        case SYM_GEN_getRelativeHealth_302: out = fn_getRelativeHealth(args, argc); return true;
        case SYM_GEN_getMissingHealth_1155: out = fn_getMissingHealth(args, argc); return true;
        case SYM_GEN_setCurrentHealth_1156: out = fn_setCurrentHealth(args, argc); return true;
        case SYM_GEN_loseHealth_1157: out = fn_loseHealth(args, argc); return true;
        case SYM_GEN_setMaxHealth_1158: out = fn_setMaxHealth(args, argc); return true;
        case SYM_GEN_giveMaxHealth_317: out = fn_giveMaxHealth(args, argc); return true;
        case SYM_GEN_getBaseMaxHealth_1159: out = fn_getBaseMaxHealth(args, argc); return true;
        case SYM_GEN_getMaxHealth_1160: out = fn_getMaxHealth(args, argc); return true;
        case SYM_GEN_applyTemporaryMaxHealthGain_1161: out = fn_applyTemporaryMaxHealthGain(args, argc); return true;
        case SYM_GEN_changeMaxHealthTemporary_1162: out = fn_changeMaxHealthTemporary(args, argc); return true;
        case SYM_GEN_getMaxStamina_1163: out = fn_getMaxStamina(args, argc); return true;
        case SYM_GEN_gainStamina_1164: out = fn_gainStamina(args, argc); return true;
        case SYM_GEN_addStamina_1165: out = fn_addStamina(args, argc); return true;
        case SYM_GEN_clampStamina_1166: out = fn_clampStamina(args, argc); return true;
        case SYM_GEN_fillUpStamina_300: out = fn_fillUpStamina(args, argc); return true;
        case SYM_GEN_useStamina_116: out = fn_useStamina(args, argc); return true;
        case SYM_GEN_drainStamina_117: out = fn_drainStamina(args, argc); return true;
        case SYM_GEN_setTemporaryMaxStamina_1167: out = fn_setTemporaryMaxStamina(args, argc); return true;
        case SYM_GEN_setTemporaryMaxHealthGain_1168: out = fn_setTemporaryMaxHealthGain(args, argc); return true;
        case SYM_GEN_death_1169: out = fn_death(args, argc); return true;
        case SYM_GEN_stun_330: out = fn_stun(args, argc); return true;
        case SYM_GEN_endStun_1170: out = fn_endStun(args, argc); return true;
        case SYM_GEN_isStunned_1171: out = fn_isStunned(args, argc); return true;
        case SYM_GEN_changeDodgeStacks_1172: out = fn_changeDodgeStacks(args, argc); return true;
        case SYM_GEN_changeCritResistance_1173: out = fn_changeCritResistance(args, argc); return true;
        case SYM_GEN_critResisted_1174: out = fn_critResisted(args, argc); return true;
        case SYM_GEN_gainCritResistStacks_1175: out = fn_gainCritResistStacks(args, argc); return true;
        case SYM_GEN_changeStunResistance_1176: out = fn_changeStunResistance(args, argc); return true;
        case SYM_GEN_stunResisted_1177: out = fn_stunResisted(args, argc); return true;
        case SYM_GEN_giveUnhealing_1178: out = fn_giveUnhealing(args, argc); return true;
        case SYM_GEN_reduceUnhealing_1179: out = fn_reduceUnhealing(args, argc); return true;
        case SYM_GEN_getUnhealing_1180: out = fn_getUnhealing(args, argc); return true;
        case SYM_GEN_getHealingEfficiency_1181: out = fn_getHealingEfficiency(args, argc); return true;
        case SYM_GEN_addHealingEfficiency_1182: out = fn_addHealingEfficiency(args, argc); return true;
        case SYM_GEN_reduceHealingEfficiency_1183: out = fn_reduceHealingEfficiency(args, argc); return true;
        case SYM_GEN_getCritTokens_182: out = fn_getCritTokens(args, argc); return true;
        case SYM_GEN_gainCritTokens_1184: out = fn_gainCritTokens(args, argc); return true;
        case SYM_GEN_changeDebuffResistStacks_1185: out = fn_changeDebuffResistStacks(args, argc); return true;
        case SYM_GEN_changeDebuffReflectStacks_1186: out = fn_changeDebuffReflectStacks(args, argc); return true;
        case SYM_GEN_changeBuffProtectStacks_1187: out = fn_changeBuffProtectStacks(args, argc); return true;
        case SYM_GEN_changeReflectChance_1029: out = fn_changeReflectChance(args, argc); return true;
        case SYM_GEN_changeAllDebuffsReflectChance_1188: out = fn_changeAllDebuffsReflectChance(args, argc); return true;
        case SYM_GEN_changeMeleeSpikesLimit_1189: out = fn_changeMeleeSpikesLimit(args, argc); return true;
        case SYM_GEN_changeRangedSpikesLimit_1190: out = fn_changeRangedSpikesLimit(args, argc); return true;
        case SYM_GEN_changeEffectSpikesLimit_1191: out = fn_changeEffectSpikesLimit(args, argc); return true;
        case SYM_GEN_changeMeleeVampirismLimit_1192: out = fn_changeMeleeVampirismLimit(args, argc); return true;
        case SYM_GEN_changeRangedVampirismLimit_1193: out = fn_changeRangedVampirismLimit(args, argc); return true;
        case SYM_GEN_getBonusFatigueDamage_1194: out = fn_getBonusFatigueDamage(args, argc); return true;
        case SYM_GEN_addFatigueDamage_1195: out = fn_addFatigueDamage(args, argc); return true;
        case SYM_GEN_takeFatigueDamage_1196: out = fn_takeFatigueDamage(args, argc); return true;
        case SYM_GEN_startBlindingLight_1197: out = fn_startBlindingLight(args, argc); return true;
        case SYM_GEN_endBlindingLight_1198: out = fn_endBlindingLight(args, argc); return true;
        case SYM_GEN_startBattleRage_1199: out = fn_startBattleRage(args, argc); return true;
        case SYM_GEN_endBattleRage_1200: out = fn_endBattleRage(args, argc); return true;
        case SYM_GEN_getClass_1201: out = fn_getClass(args, argc); return true;
        case SYM_GEN_isChibi_1202: out = fn_isChibi(args, argc); return true;
        case SYM_GEN_setClass_1203: out = fn_setClass(args, argc); return true;
        case SYM_GEN_setClassResource_1204: out = fn_setClassResource(args, argc); return true;
        case SYM_GEN_lose_1205: out = fn_lose(args, argc); return true;
        case SYM_GEN_win_1206: out = fn_win(args, argc); return true;
        case SYM_GEN_setStat_115: out = fn_setStat(args, argc); return true;
        case SYM_GEN_getStat_261: out = fn_getStat(args, argc); return true;
        case SYM_GEN_isBattleRaging_1207: out = fn_isBattleRaging(args, argc); return true;
        case SYM_GEN_startAutoRage_1208: out = fn_startAutoRage(args, argc); return true;
        case SYM_GEN_playBattleRageAnimation_1209: out = fn_playBattleRageAnimation(args, argc); return true;
        case SYM_GEN__setRageTimer_1210: out = fn__setRageTimer(args, argc); return true;
        case SYM_GEN__f32eng_505: out = sf__f32eng(gd_ctx, args, argc); return true;
        case SYM_GEN_makeInvulnerable_1211: out = fn_makeInvulnerable(args, argc); return true;
        case SYM_GEN_makeVulnerable_1212: out = fn_makeVulnerable(args, argc); return true;
        case SYM_GEN_invulnerabilityEnded_1213: out = fn_invulnerabilityEnded(args, argc); return true;
        case SYM_GEN_setInvulnerable_1214: out = fn_setInvulnerable(args, argc); return true;
        case SYM_GEN_getStacks_1023: out = fn_getStacks(args, argc); return true;
        case SYM_GEN_getBuffStacks_1215: out = fn_getBuffStacks(args, argc); return true;
        case SYM_GEN_getDebuffStacks_1216: out = fn_getDebuffStacks(args, argc); return true;
        case SYM_GEN_setStacks_1024: out = fn_setStacks(args, argc); return true;
        case SYM_GEN_setStacksLogged_1217: out = fn_setStacksLogged(args, argc); return true;
        case SYM_GEN_gainStacks_1030: out = fn_gainStacks(args, argc); return true;
        case SYM_GEN_gainStacksTemporary_1218: out = fn_gainStacksTemporary(args, argc); return true;
        case SYM_GEN_loseStacks_1032: out = fn_loseStacks(args, argc); return true;
        case SYM_GEN_useStacks_1219: out = fn_useStacks(args, argc); return true;
        case SYM_GEN_changeResistChance_1026: out = fn_changeResistChance(args, argc); return true;
        case SYM_GEN_changeDebuffResistChances_1220: out = fn_changeDebuffResistChances(args, argc); return true;
        case SYM_GEN_changeResistStacks_1027: out = fn_changeResistStacks(args, argc); return true;
        case SYM_GEN_getBlock_204: out = fn_getBlock(args, argc); return true;
        case SYM_GEN_setBlock_1221: out = fn_setBlock(args, argc); return true;
        case SYM_GEN_gainBlock_1222: out = fn_gainBlock(args, argc); return true;
        case SYM_GEN_loseBlock_206: out = fn_loseBlock(args, argc); return true;
        case SYM_GEN_getSpikes_1223: out = fn_getSpikes(args, argc); return true;
        case SYM_GEN_setSpikes_1224: out = fn_setSpikes(args, argc); return true;
        case SYM_GEN_gainSpikes_1225: out = fn_gainSpikes(args, argc); return true;
        case SYM_GEN_loseSpikes_338: out = fn_loseSpikes(args, argc); return true;
        case SYM_GEN_getVampirism_1226: out = fn_getVampirism(args, argc); return true;
        case SYM_GEN_setVampirism_1227: out = fn_setVampirism(args, argc); return true;
        case SYM_GEN_gainVampirism_1228: out = fn_gainVampirism(args, argc); return true;
        case SYM_GEN_loseVampirism_341: out = fn_loseVampirism(args, argc); return true;
        case SYM_GEN_getPoison_1229: out = fn_getPoison(args, argc); return true;
        case SYM_GEN_setPoison_1230: out = fn_setPoison(args, argc); return true;
        case SYM_GEN_gainPoison_1231: out = fn_gainPoison(args, argc); return true;
        case SYM_GEN_losePoison_1232: out = fn_losePoison(args, argc); return true;
        case SYM_GEN_getRegeneration_1233: out = fn_getRegeneration(args, argc); return true;
        case SYM_GEN_setRegeneration_1234: out = fn_setRegeneration(args, argc); return true;
        case SYM_GEN_gainRegeneration_1235: out = fn_gainRegeneration(args, argc); return true;
        case SYM_GEN_loseRegeneration_1236: out = fn_loseRegeneration(args, argc); return true;
        case SYM_GEN_getLucky_1237: out = fn_getLucky(args, argc); return true;
        case SYM_GEN_setLucky_1238: out = fn_setLucky(args, argc); return true;
        case SYM_GEN_gainLucky_1239: out = fn_gainLucky(args, argc); return true;
        case SYM_GEN_loseLucky_348: out = fn_loseLucky(args, argc); return true;
        case SYM_GEN_getBlind_1240: out = fn_getBlind(args, argc); return true;
        case SYM_GEN_setBlind_1241: out = fn_setBlind(args, argc); return true;
        case SYM_GEN_gainBlind_1242: out = fn_gainBlind(args, argc); return true;
        case SYM_GEN_loseBlind_1243: out = fn_loseBlind(args, argc); return true;
        case SYM_GEN_getMana_1244: out = fn_getMana(args, argc); return true;
        case SYM_GEN_setMana_1245: out = fn_setMana(args, argc); return true;
        case SYM_GEN_gainMana_1246: out = fn_gainMana(args, argc); return true;
        case SYM_GEN_loseMana_1247: out = fn_loseMana(args, argc); return true;
        case SYM_GEN_getEmpower_1248: out = fn_getEmpower(args, argc); return true;
        case SYM_GEN_setEmpower_1249: out = fn_setEmpower(args, argc); return true;
        case SYM_GEN_gainEmpower_1250: out = fn_gainEmpower(args, argc); return true;
        case SYM_GEN_loseEmpower_355: out = fn_loseEmpower(args, argc); return true;
        case SYM_GEN_getHeat_1251: out = fn_getHeat(args, argc); return true;
        case SYM_GEN_setHeat_1252: out = fn_setHeat(args, argc); return true;
        case SYM_GEN_gainHeat_1253: out = fn_gainHeat(args, argc); return true;
        case SYM_GEN_loseHeat_353: out = fn_loseHeat(args, argc); return true;
        case SYM_GEN_getCold_1254: out = fn_getCold(args, argc); return true;
        case SYM_GEN_setCold_1255: out = fn_setCold(args, argc); return true;
        case SYM_GEN_gainCold_1256: out = fn_gainCold(args, argc); return true;
        case SYM_GEN_loseCold_1257: out = fn_loseCold(args, argc); return true;
        case SYM_GEN_getBuffDamageMod_1258: out = fn_getBuffDamageMod(args, argc); return true;
        case SYM_GEN_getBuffAccuracyMod_1259: out = fn_getBuffAccuracyMod(args, argc); return true;
        case SYM_GEN_getBaseMaxStamina_1260: out = fn_getBaseMaxStamina(args, argc); return true;
        case SYM_GEN_getMaxBaseStamina_1261: out = fn_getMaxBaseStamina(args, argc); return true;
        case SYM_GEN_getCurrentStamina_1262: out = fn_getCurrentStamina(args, argc); return true;
        case SYM_GEN_setCurrentStamina_1263: out = fn_setCurrentStamina(args, argc); return true;
        case SYM_GEN_getMissingStamina_1264: out = fn_getMissingStamina(args, argc); return true;
        case SYM_GEN_isFullStamina_1265: out = fn_isFullStamina(args, argc); return true;
        case SYM_GEN_setMaxStamina_1266: out = fn_setMaxStamina(args, argc); return true;
        case SYM_GEN_giveMaxStamina_315: out = fn_giveMaxStamina(args, argc); return true;
        case SYM_GEN_reduceMaxStamina_1267: out = fn_reduceMaxStamina(args, argc); return true;
        case SYM_GEN_gainMaxStaminaTemporary_1268: out = fn_gainMaxStaminaTemporary(args, argc); return true;
        case SYM_GEN_getStaminaRegeneration_1269: out = fn_getStaminaRegeneration(args, argc); return true;
        case SYM_GEN_giveStaminaRegeneration_1270: out = fn_giveStaminaRegeneration(args, argc); return true;
        case SYM_GEN_getTotalStaminaUsage_1271: out = fn_getTotalStaminaUsage(args, argc); return true;
        case SYM_GEN_changeBaseMaxStamina_1272: out = fn_changeBaseMaxStamina(args, argc); return true;
        case SYM_GEN_recalculateMaxStamina_1273: out = fn_recalculateMaxStamina(args, argc); return true;
        case SYM_GEN_getTemporaryMaxHealth_1274: out = fn_getTemporaryMaxHealth(args, argc); return true;
        case SYM_GEN_setTemporaryMaxHealth_1275: out = fn_setTemporaryMaxHealth(args, argc); return true;
        case SYM_GEN_reduceMaxHealth_1276: out = fn_reduceMaxHealth(args, argc); return true;
        case SYM_GEN_changeMaxHealthGain_1277: out = fn_changeMaxHealthGain(args, argc); return true;
        case SYM_GEN_changeDamageReduction_1278: out = fn_changeDamageReduction(args, argc); return true;
        case SYM_GEN_changeDamageResistance_1279: out = fn_changeDamageResistance(args, argc); return true;
        case SYM_GEN_changeTypedDamageFactor_1280: out = fn_changeTypedDamageFactor(args, argc); return true;
        case SYM_GEN_changeEffectDamageFactor_1281: out = fn_changeEffectDamageFactor(args, argc); return true;
        case SYM_GEN_changeEmpowerDamage_1282: out = fn_changeEmpowerDamage(args, argc); return true;
        case SYM_GEN_changePoisonCritChancePercent_1283: out = fn_changePoisonCritChancePercent(args, argc); return true;
        case SYM_GEN_changeSpikesCritChancePercent_1284: out = fn_changeSpikesCritChancePercent(args, argc); return true;
        case SYM_GEN_useCritToken_184: out = fn_useCritToken(args, argc); return true;
        case SYM_GEN_useMana_332: out = fn_useMana(args, argc); return true;
        case SYM_GEN_changeProtectionChance_1285: out = fn_changeProtectionChance(args, argc); return true;
        case SYM_GEN_changeBuffProtectionChance_1286: out = fn_changeBuffProtectionChance(args, argc); return true;
        case SYM_GEN_changeDebuffProtectionChance_1287: out = fn_changeDebuffProtectionChance(args, argc); return true;
        case SYM_GEN_changeBuffNullifyChances_1288: out = fn_changeBuffNullifyChances(args, argc); return true;
        case SYM_GEN_changeDebuffNullifyChances_1289: out = fn_changeDebuffNullifyChances(args, argc); return true;
        case SYM_GEN_addBattleRageDuration_1290: out = fn_addBattleRageDuration(args, argc); return true;
        case SYM_GEN_isVulnerable_1291: out = fn_isVulnerable(args, argc); return true;
        case SYM_GEN_physicsTickCharacter_1292: out = fn_physicsTickCharacter(args, argc); return true;
        case SYM_GEN_tickPhysicsTimers_1293: out = fn_tickPhysicsTimers(args, argc); return true;
        case SYM_GEN_tickBuffs_1294: out = fn_tickBuffs(args, argc); return true;
        case SYM_GEN_rebuildTimerSeen_139: out = fn_rebuildTimerSeen(args, argc); return true;
        case SYM_GEN_snapshotPhysicsTimers_1295: out = fn_snapshotPhysicsTimers(args, argc); return true;
        case SYM_GEN__startInvulnerability_1296: out = fn__startInvulnerability(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreCharacter::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN__visualLerp_1136: out = sf__visualLerp(gd_ctx, args, argc); return true;
        case SYM_GEN__f32eng_505: out = sf__f32eng(gd_ctx, args, argc); return true;
        default: break;
    }
    return false;
}
gd::GdVal Gd__gd_core__CoreCharacter::fn__init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__ctx = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__playerId = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv__playerId = gd::gd_coerce_int(lv__playerId);
    this->f_ctx = lv__ctx;
    this->f_playerId = gd::gd_coerce_int(lv__playerId);
    this->f_accuracyRng = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_BalancedRng_1749), gd::SYM_new, _ca, 1); })();
    this->f_critRng = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_BalancedRng_1749), gd::SYM_new, _ca, 1); })();
    this->f_critResistanceRng = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_BalancedRng_1749), gd::SYM_new, _ca, 1); })();
    this->f_stunResistanceRng = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_BalancedRng_1749), gd::SYM_new, _ca, 1); })();
    this->f_inventory = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreGrid), gd::SYM_new, _ca, 1); })();
    this->f_INVENTORY = this->f_inventory;
    this->f_spikeDamageSource = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0);
    gd::set_prop(gd_ctx, this->f_spikeDamageSource, SYM_GEN__rng_1548, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Spikes_2662), gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, this->f_spikeDamageSource, SYM_GEN_init_1022, _ca, 3); })();
    gd::set_prop(gd_ctx, this->f_spikeDamageSource, SYM_GEN_flags_1547, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_chipDamageFlags_1536), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Flags_1565), SYM_GEN_CanCrit_2779)));
    this->f_poisonDamageSource = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0);
    gd::set_prop(gd_ctx, this->f_poisonDamageSource, SYM_GEN__rng_1548, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Poison_2664), gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, this->f_poisonDamageSource, SYM_GEN_init_1022, _ca, 3); })();
    gd::set_prop(gd_ctx, this->f_poisonDamageSource, SYM_GEN_flags_1547, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_chipDamageFlags_1536), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Flags_1565), SYM_GEN_CanCrit_2779)));
    {
        gd::GdVal _t539 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getStacks_1023, nullptr, 0));
        gd::GdArr* _t540 = (_t539.kind == gd::GdVal::Kind::Arr) ? _t539.arr : nullptr;
        uint32_t _len__t541 = _t540 ? _t540->len : 0u;
        for (uint32_t _t541 = 0; _t541 < _len__t541; ++_t541) {
            gd::GdVal lv_stackType = _t540->data[_t541];
            gd::GdVal lv_buff = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreBuff), gd::SYM_new, nullptr, 0);
            gd::GdVal lv__stack_type_name = gd::GdVal::from_str(&battle_string_literals[12]);
            {
                gd::GdVal _t542 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1395));
                gd::GdArr* _t543 = (_t542.kind == gd::GdVal::Kind::Arr) ? _t542.arr : nullptr;
                uint32_t _len__t544 = _t543 ? _t543->len : 0u;
                for (uint32_t _t544 = 0; _t544 < _len__t544; ++_t544) {
                    gd::GdVal lv__k = _t543->data[_t544];
                    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_index(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1395), lv__k), lv_stackType)))) {
                        lv__stack_type_name = lv__k;
                        break;
                    }
                }
            }
            (void)([&]() { gd::GdVal _ca[] = {lv_stackType, gd::GdVal::from_obj(this), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[13]), gd::call_method(gd_ctx, lv__stack_type_name, gd::SYM_to_lower, nullptr, 0)), gd::GdVal::from_str(&battle_string_literals[14]))}; return gd::call_method(gd_ctx, lv_buff, SYM_GEN_init_1022, _ca, 3); })();
            { gd::GdVal _t545 = this->f_buffs; gd::GdVal _t546 = lv_stackType; gd::set_index(gd_ctx, _t545, _t546, lv_buff); }
        }
    }
    this->f_curHealth = gd::gd_coerce_float(this->f_maxHealth);
    this->f_baseMaxStamina = gd::gd_coerce_float(this->f_maxStamina);
    this->f_curStamina = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_staminaRegen = gd::gd_coerce_float(this->f_baseStaminaRegen);
    {
        gd::GdVal _t547 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), gd::SYM_values, nullptr, 0));
        gd::GdArr* _t548 = (_t547.kind == gd::GdVal::Kind::Arr) ? _t547.arr : nullptr;
        uint32_t _len__t549 = _t548 ? _t548->len : 0u;
        for (uint32_t _t549 = 0; _t549 < _len__t549; ++_t549) {
            gd::GdVal lv_type = _t548->data[_t549];
            { gd::GdVal _t550 = this->f_typedDamageFactors; gd::GdVal _t551 = lv_type; gd::set_index(gd_ctx, _t550, _t551, gd::GdVal::from_float(0.0)); }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setOpponent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__opponent = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_opponent = lv__opponent;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_isPlayer(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_eq(this->f_playerId, gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getName(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_index(gd_ctx, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_str(&battle_string_literals[15]), gd::GdVal::from_str(&battle_string_literals[16])})), this->f_playerId);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_registerCharacterDied(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_handler = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_handler}; return gd::call_method(gd_ctx, this->f_character_died_handlers, gd::SYM_push_back, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_clearCharacterDiedHandlers(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_character_died_handlers, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_staminaRegen = gd::gd_coerce_float(this->f_baseStaminaRegen);
    gd::GdVal lv_bonusHealth = gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxHealth_1160, nullptr, 0), gd::gd_div(gd_ctx, gd::gd_sub(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_custom_health_multiplier_1417), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(100.0)));
    (void)([&]() { gd::GdVal _ca[] = {lv_bonusHealth}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeMaxHealthTemporary_1162, _ca, 1); })();
    (void)gd::call_method(gd_ctx, this->f_accuracyRng, SYM_GEN_reset_1025, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_critRng, SYM_GEN_reset_1025, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_critResistanceRng, SYM_GEN_reset_1025, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_stunResistanceRng, SYM_GEN_reset_1025, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_below_master_1414)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_lobbies_mode_1416)))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_playerId, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(0.2))}; return gd::call_method(gd_ctx, this->f_accuracyRng, SYM_GEN_setBias_1759, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(0.2))}; return gd::call_method(gd_ctx, this->f_critRng, SYM_GEN_setBias_1759, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.2)}; return gd::call_method(gd_ctx, this->f_accuracyRng, SYM_GEN_setBias_1759, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.2)}; return gd::call_method(gd_ctx, this->f_critRng, SYM_GEN_setBias_1759, _ca, 1); })();
        }
    }
    this->f_autoRageItem = gd::GdVal::null();
    gd::GdVal lv_hasBattleRageStarter = gd::GdVal::from_bool(false);
    {
        gd::GdVal _t552 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t553 = (_t552.kind == gd::GdVal::Kind::Arr) ? _t552.arr : nullptr;
        uint32_t _len__t554 = _t553 ? _t553->len : 0u;
        for (uint32_t _t554 = 0; _t554 < _len__t554; ++_t554) {
            gd::GdVal lv_item = _t553->data[_t554];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(64LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasTag_81, _ca, 1); })())) {
                lv_hasBattleRageStarter = gd::GdVal::from_bool(true);
                break;
            }
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_hasBattleRageStarter)))) {
        gd::GdVal lv_battleRageItems = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
        {
            gd::GdVal _t555 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItemsAndGems_1604, nullptr, 0));
            gd::GdArr* _t556 = (_t555.kind == gd::GdVal::Kind::Arr) ? _t555.arr : nullptr;
            uint32_t _len__t557 = _t556 ? _t556->len : 0u;
            for (uint32_t _t557 = 0; _t557 < _len__t557; ++_t557) {
                gd::GdVal lv_item = _t556->data[_t557];
                if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isBattleRageItem_85, nullptr, 0))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, lv_battleRageItems, gd::SYM_push_back, _ca, 1); })();
                }
            }
        }
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_battleRageItems, gd::SYM_empty, nullptr, 0))))) {
            this->f_autoRageItem = ([&]() { gd::GdVal _ca[] = {lv_battleRageItems, gd::GdVal::from_str(&battle_string_literals[17])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_pickRandomEngine_1748, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_combatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_stunnedDuration = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_tickCounter = gd::GdVal::from_int(0LL);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_autoRageItem, gd::GdVal::null())))) {
        this->f__autoRage_left = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_AUTO_RAGE_DELAY_1044)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })());
        this->f__autoRage_active = gd::GdVal::from_bool(true);
    }
    this->f__tick_timer_left = gd::GdVal::from_float(1.0);
    this->f__tick_timer_active = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_combatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_attackMovingForward_reset_1132, nullptr, 0);
    this->f__tick_timer_active = gd::GdVal::from_bool(false);
    {
        gd::GdVal _t558 = gd::gd_iter_seq(gd_ctx.arena, this->f_buffs);
        gd::GdArr* _t559 = (_t558.kind == gd::GdVal::Kind::Arr) ? _t558.arr : nullptr;
        uint32_t _len__t560 = _t559 ? _t559->len : 0u;
        for (uint32_t _t560 = 0; _t560 < _len__t560; ++_t560) {
            gd::GdVal lv_buffType = _t559->data[_t560];
            (void)gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_combatEnd_131, nullptr, 0);
        }
    }
    this->f__rage_left = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f__rage_active = gd::GdVal::from_bool(false);
    this->f__autoRage_left = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f__autoRage_active = gd::GdVal::from_bool(false);
    this->f__invul_left = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f__invul_active = gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_attackMovingForward_reset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_attack_moving_forward = gd::GdVal::from_bool(false);
    this->f__visual_kind = gd::GdVal::from_int(0LL);
    this->f__visual_x = gd::GdVal::from_float(0.0);
    this->f__visual_y = gd::GdVal::from_float(0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_cleanse(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_isDead = gd::GdVal::from_bool(false);
    this->f_temporaryMaxHealth = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    this->f_temporaryMaxHealthGain = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_staminaRegen = gd::gd_coerce_float(this->f_baseStaminaRegen);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_healToFull_1152, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setTemporaryMaxStamina_1167, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_fillUpStamina_300, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_endStun_1170, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBlock_1221, _ca, 1); })();
    {
        gd::GdVal _t561 = gd::gd_iter_seq(gd_ctx.arena, this->f_buffs);
        gd::GdArr* _t562 = (_t561.kind == gd::GdVal::Kind::Arr) ? _t561.arr : nullptr;
        uint32_t _len__t563 = _t562 ? _t562->len : 0u;
        for (uint32_t _t563 = 0; _t563 < _len__t563; ++_t563) {
            gd::GdVal lv_buffType = _t562->data[_t563];
            (void)gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_reset_1025, nullptr, 0);
        }
    }
    this->f_invulnerable = gd::GdVal::from_bool(false);
    this->f_damageResistance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_damageReduction = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_dodgeStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_critResistance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_critResistStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_stunResistance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_unhealingAmount = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_healingEfficiency = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_critTokens = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_debuffResistStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_debuffReflectStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_buffProtectStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_battleRageBonusDur = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusFatigueDamage = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_blindingLightActive = gd::GdVal::from_bool(false);
    this->f_meleeSpikesLimit = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_rangedSpikesLimit = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_effectSpikesLimit = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_meleeVampirismLimit = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_rangedVampirismLimit = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_empowerDamage = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    {
        gd::GdVal _t564 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), gd::SYM_values, nullptr, 0));
        gd::GdArr* _t565 = (_t564.kind == gd::GdVal::Kind::Arr) ? _t564.arr : nullptr;
        uint32_t _len__t566 = _t565 ? _t565->len : 0u;
        for (uint32_t _t566 = 0; _t566 < _len__t566; ++_t566) {
            gd::GdVal lv_damageType = _t565->data[_t566];
            { gd::GdVal _t567 = this->f_typedDamageFactors; gd::GdVal _t568 = lv_damageType; gd::set_index(gd_ctx, _t567, _t568, gd::GdVal::from_float(0.0)); }
        }
    }
    gd::set_prop(gd_ctx, this->f_poisonDamageSource, SYM_GEN_critChancePercent_15, gd::GdVal::from_int(0LL));
    gd::set_prop(gd_ctx, this->f_spikeDamageSource, SYM_GEN_critChancePercent_15, gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_onTick(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::gd_mod(gd_ctx, this->f_tickCounter, gd::GdVal::from_int(2LL)), gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_regen = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRegeneration_1233, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_regen, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_regen, gd::GdVal::from_int(102LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(102LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_activateBuffCounter_1623, _ca, 2); })();
        }
    }
    else {
        gd::GdVal lv_poison = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getPoison_1229, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_poison, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_poison}; return gd::call_method(gd_ctx, this->f_poisonDamageSource, SYM_GEN_setDamage_1551, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_poisonDamageSource}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_takeDamage_1148, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(108LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_activateBuffCounter_1623, _ca, 2); })();
        }
    }
    this->f_tickCounter = gd::gd_add(gd_ctx, this->f_tickCounter, gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn__beginVisualMotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_kind = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_kind = gd::gd_coerce_int(lv_kind);
    gd::GdVal lv_to_x = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_to_x = gd::gd_coerce_float(lv_to_x);
    gd::GdVal lv_to_y = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_to_y = gd::gd_coerce_float(lv_to_y);
    gd::GdVal lv_forward = (_argc > 3) ? _args[3] : gd::GdVal::null();
    lv_forward = gd::gd_coerce_float(lv_forward);
    gd::GdVal lv_back = (_argc > 4) ? _args[4] : gd::GdVal::null();
    lv_back = gd::gd_coerce_float(lv_back);
    this->f__visual_generation = gd::gd_add(gd_ctx, this->f__visual_generation, gd::GdVal::from_int(1LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), gd::GdVal::from_obj(this), this->f__visual_generation}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_registerMotion_1500, _ca, 3); })();
    this->f__visual_from_x = this->f__visual_x;
    this->f__visual_from_y = this->f__visual_y;
    this->f__visual_to_x = lv_to_x;
    this->f__visual_to_y = lv_to_y;
    this->f__visual_forward = ([&]() { gd::GdVal _ca[] = {lv_forward}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })();
    this->f__visual_back = ([&]() { gd::GdVal _ca[] = {lv_back}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })();
    this->f__visual_elapsed = gd::GdVal::from_float(0.0);
    this->f__visual_kind = lv_kind;
    this->f__visual_stage = gd::GdVal::from_int(0LL);
    this->f_attack_moving_forward = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::sf__visualLerp(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_a = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_a = gd::gd_coerce_float(lv_a);
    gd::GdVal lv_b = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_b = gd::gd_coerce_float(lv_b);
    gd::GdVal lv_elapsed = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_elapsed = gd::gd_coerce_float(lv_elapsed);
    gd::GdVal lv_duration = (_argc > 3) ? _args[3] : gd::GdVal::null();
    lv_duration = gd::gd_coerce_float(lv_duration);
    return ([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, lv_a, ([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::gd_sub(lv_b, lv_a)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })(), lv_elapsed)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })(), lv_duration)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })())}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_tickVisualMotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f__visual_kind, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_remaining = lv_delta;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f__visual_stage, gd::GdVal::from_int(0LL))))) {
        this->f__visual_elapsed = ([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f__visual_elapsed, lv_remaining)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f__visual_elapsed, this->f__visual_forward)))) {
            this->f__visual_x = ([&]() { gd::GdVal _ca[] = {this->f__visual_from_x, this->f__visual_to_x, this->f__visual_elapsed, this->f__visual_forward}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__visualLerp_1136, _ca, 4, _out); return _out; })();
            this->f__visual_y = ([&]() { gd::GdVal _ca[] = {this->f__visual_from_y, this->f__visual_to_y, this->f__visual_elapsed, this->f__visual_forward}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__visualLerp_1136, _ca, 4, _out); return _out; })();
            return gd::GdVal::null();
        }
        this->f__visual_x = this->f__visual_to_x;
        this->f__visual_y = this->f__visual_to_y;
        lv_remaining = gd::gd_min(lv_delta, ([&]() { gd::GdVal _ca[] = {gd::gd_sub(this->f__visual_elapsed, this->f__visual_forward)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })());
        this->f__visual_elapsed = gd::GdVal::from_float(0.0);
        this->f__visual_stage = gd::GdVal::from_int(1LL);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f__visual_stage, gd::GdVal::from_int(1LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(lv_remaining, gd::GdVal::from_float(0.0))))) {
            return gd::GdVal::null();
        }
        this->f_attack_moving_forward = gd::GdVal::from_bool(false);
        this->f__visual_stage = gd::GdVal::from_int(2LL);
    }
    this->f__visual_elapsed = ([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f__visual_elapsed, lv_remaining)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })();
    gd::GdVal lv_back_x = (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f__visual_kind, gd::GdVal::from_int(1LL)))) ? (gd::GdVal::from_float(0.0)) : (this->f__visual_from_x));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f__visual_elapsed, this->f__visual_back)))) {
        this->f__visual_x = ([&]() { gd::GdVal _ca[] = {this->f__visual_to_x, lv_back_x, this->f__visual_elapsed, this->f__visual_back}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__visualLerp_1136, _ca, 4, _out); return _out; })();
        this->f__visual_y = ([&]() { gd::GdVal _ca[] = {this->f__visual_to_y, gd::GdVal::from_float(0.0), this->f__visual_elapsed, this->f__visual_back}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__visualLerp_1136, _ca, 4, _out); return _out; })();
    }
    else {
        this->f__visual_x = lv_back_x;
        this->f__visual_y = gd::GdVal::from_float(0.0);
        this->f__visual_kind = gd::GdVal::from_int(0LL);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_tickIdleAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    this->f__idle_animation_left = gd::gd_sub(this->f__idle_animation_left, lv_delta);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f__idle_animation_left, gd::GdVal::from_float(0.0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.8), gd::GdVal::from_float(1.2)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
        this->f__idle_animation_left = ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(2.0), gd::GdVal::from_float(5.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })()}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_playAttackAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_distance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(100.0), gd::GdVal::from_float(160.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    if (gd::gd_truth(this->f_attack_moving_forward)) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_forward = gd::gd_mul(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::gd_sub(lv_distance, this->f__visual_x)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })(), gd::GdVal::from_float(2600.0)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })());
    gd::GdVal lv_back = gd::gd_mul(gd::gd_div(gd_ctx, lv_distance, gd::GdVal::from_float(1000.0)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })());
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), lv_distance, gd::GdVal::from_float(0.0), lv_forward, lv_back}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__beginVisualMotion_1135, _ca, 5); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), gd::GdVal::from_int(2LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randi_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.8), gd::GdVal::from_float(1.2)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1411), this->f_attack_sound_ready_time)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), gd::gd_sub(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_classAttackSoundCount_1140, nullptr, 0), gd::GdVal::from_int(1LL))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randi_range, _ca, 2); })();
        this->f_attack_sound_ready_time = gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1411), gd::GdVal::from_float(0.1));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_classAttackSoundCount(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_characterClass}; return gd::call_method(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_CLASS_SOUND_COUNTS_1127), gd::SYM_has, _ca, 1); })())))) {
        (void)gd::GdVal::null();
    }
    return gd::get_index(gd_ctx, gd::get_index(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_CLASS_SOUND_COUNTS_1127), this->f_characterClass), gd::GdVal::from_str(&battle_string_literals[9]));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_classRoundSoundCount(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_win = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_win = gd::gd_coerce_bool(lv_win);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_characterClass}; return gd::call_method(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_CLASS_SOUND_COUNTS_1127), gd::SYM_has, _ca, 1); })())))) {
        (void)gd::GdVal::null();
    }
    return gd::get_index(gd_ctx, gd::get_index(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_CLASS_SOUND_COUNTS_1127), this->f_characterClass), (gd::gd_truth(lv_win) ? (gd::GdVal::from_str(&battle_string_literals[10])) : (gd::GdVal::from_str(&battle_string_literals[11]))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_playActivateAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_attack_moving_forward)) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_forward = gd::gd_mul(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::gd_sub(gd::gd_neg(gd::GdVal::from_float(40.0)), this->f__visual_y)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })(), gd::GdVal::from_float(300.0)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })());
    gd::GdVal lv_back = gd::gd_mul(gd::gd_div(gd_ctx, gd::GdVal::from_float(40.0), gd::GdVal::from_float(300.0)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })());
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL), this->f__visual_x, gd::gd_neg(gd::GdVal::from_float(40.0)), lv_forward, lv_back}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__beginVisualMotion_1135, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_randBuffLabelPos(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(60.0)), gd::GdVal::from_float(60.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(40.0)), gd::GdVal::from_float(40.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_randBuffLabelDir(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(75.0)), gd::gd_neg(gd::GdVal::from_float(120.0))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_randDmgNumberPos(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(50.0)), gd::GdVal::from_float(50.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(70.0)), gd::GdVal::from_float(70.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_randDmgNumberDir(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(0.3665191429188092)), gd::gd_neg(gd::GdVal::from_float(0.05235987755982988))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_randHealNumberPos(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(50.0)), gd::GdVal::from_float(50.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(70.0)), gd::GdVal::from_float(70.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_dealDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageSource = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playAttackAnimation_1139, nullptr, 0);
    gd::GdVal lv_res = ([&]() { gd::GdVal _ca[] = {lv_damageSource, lv_triggerEvent}; return gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_takeDamage_1148, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_applyVampirism_1151, _ca, 1); })();
    return lv_res;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_takeDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageSource = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_damageRes = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageResult), gd::SYM_new, nullptr, 0);
    lv_damageSource = ([&]() { gd::GdVal _ca[] = {lv_damageSource}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_fromDamageSource_1549, _ca, 1); })();
    gd::set_prop(gd_ctx, lv_damageSource, SYM_GEN__rng_1548, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406));
    gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24, lv_damageSource);
    (void)gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_reset_1025, nullptr, 0);
    if (gd::gd_truth(this->f_isDead)) {
        return lv_damageRes;
    }
    gd::GdVal lv_item = gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(gd::get_prop(gd_ctx, lv_damageSource, SYM_GEN_origin_1546), &META_Gd__gd_core__CoreItem)))) {
        lv_item = gd::get_prop(gd_ctx, lv_damageSource, SYM_GEN_origin_1546);
    }
    gd::GdVal lv_attackEffectCount = gd::GdVal::from_int(1LL);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null())))) {
        lv_attackEffectCount = gd::gd_add(gd_ctx, lv_attackEffectCount, gd::call_method(gd_ctx, lv_item, SYM_GEN_rollDoubleAttackEffect_187, nullptr, 0));
    }
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_canMiss_1557, nullptr, 0))) {
        gd::GdVal lv_accuracy = gd::get_prop(gd_ctx, lv_damageSource, SYM_GEN_accuracy_1545);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(&battle_string_literals[8]))))) {
            (void)gd::GdVal::null();
        }
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_hit_1520, ([&]() { gd::GdVal _ca[] = {lv_accuracy}; return gd::call_method(gd_ctx, this->f_accuracyRng, SYM_GEN_rollPercent_1760, _ca, 1); })());
        if (gd::gd_truth((gd::gd_truth(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_hit_1520)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_dodgeStacks, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_int(1LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeDodgeStacks_1172, _ca, 1); })();
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_hit_1520, gd::GdVal::from_bool(false));
        }
    }
    else {
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_hit_1520, gd::GdVal::from_bool(true));
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(50.0)), gd::GdVal::from_float(50.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(70.0)), gd::GdVal::from_float(70.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(0.3665191429188092)), gd::gd_neg(gd::GdVal::from_float(0.05235987755982988))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_isAttack_1560, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_damageRes}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_preDealDamage_early_222, _ca, 1); })();
        if (gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_hasPreDealDamageEarlyEffect_62))) {
            {
                gd::GdVal _t569 = gd::gd_iter_seq(gd_ctx.arena, lv_attackEffectCount);
                gd::GdArr* _t570 = (_t569.kind == gd::GdVal::Kind::Arr) ? _t569.arr : nullptr;
                uint32_t _len__t571 = _t570 ? _t570->len : 0u;
                for (uint32_t _t571 = 0; _t571 < _len__t571; ++_t571) {
                    gd::GdVal lv_i = _t570->data[_t571];
                    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[18]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN__behavior_call_504, _ca, 2); })();
                }
            }
        }
    }
    if (gd::gd_truth(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_hit_1520))) {
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_randDamage_159, nullptr, 0)));
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2781)}; return gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_hasType_79, _ca, 1); })())) {
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), this->f_bonusFatigueDamage));
        }
        if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_canCrit_1559, nullptr, 0))) {
            gd::GdVal lv_critical = gd::GdVal::from_bool(false);
            gd::GdVal lv_critChancePercent = gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_getCritChancePercent_178, nullptr, 0);
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_critChancePercent, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_critChancePercent}; return gd::call_method(gd_ctx, this->f_critRng, SYM_GEN_rollPercent_1760, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
                lv_critical = gd::GdVal::from_bool(true);
            }
            else if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, lv_item, SYM_GEN_getCritTokens_182, nullptr, 0), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
                (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_useCritToken_184, nullptr, 0);
                lv_critical = gd::GdVal::from_bool(true);
            }
            else if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_getCritTokens_182, nullptr, 0), gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_isAttackOrEffect_1562, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
                (void)gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_useCritToken_184, nullptr, 0);
                lv_critical = gd::GdVal::from_bool(true);
            }
            if (gd::gd_truth(lv_critical)) {
                if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_critResisted_1174, nullptr, 0))) {
                    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_randBuffLabelPos_1143, nullptr, 0);
                    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_randBuffLabelDir_1144, nullptr, 0);
                    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(11LL), gd::GdVal::null()}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_spawnBuffLabel_1636, _ca, 2); })();
                }
                else {
                    (void)gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_makeCritical_1525, nullptr, 0);
                }
            }
        }
        gd::GdVal lv_activeDmgResi = gd::gd_clamp(gd::gd_div(gd_ctx, this->f_damageResistance, gd::GdVal::from_int(100LL)), gd::gd_neg(gd::GdVal::from_int(10LL)), gd::GdVal::from_int(1LL));
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_round(gd::gd_mul(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), gd::gd_sub(gd::GdVal::from_float(1.0), lv_activeDmgResi))));
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_isAttack_1560, nullptr, 0))) {
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_sub(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), this->f_damageReduction));
        }
        if (gd::gd_truth(this->f_invulnerable)) {
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::GdVal::from_int(0LL));
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[19]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_sub(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageReduction_1063)));
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_max(gd::GdVal::from_int(0LL), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518)));
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_isAttack_1560, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_damageRes}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_preDealDamage_late_223, _ca, 1); })();
            if (gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_hasPreDealDamageLateEffect_63))) {
                {
                    gd::GdVal _t572 = gd::gd_iter_seq(gd_ctx.arena, lv_attackEffectCount);
                    gd::GdArr* _t573 = (_t572.kind == gd::GdVal::Kind::Arr) ? _t572.arr : nullptr;
                    uint32_t _len__t574 = _t573 ? _t573->len : 0u;
                    for (uint32_t _t574 = 0; _t574 < _len__t574; ++_t574) {
                        gd::GdVal lv_i = _t573->data[_t574];
                        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[20]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN__behavior_call_504, _ca, 2); })();
                    }
                }
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[21]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1519, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518));
        if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_canBeBlocked_1558, nullptr, 0))) {
            gd::GdVal lv_curBlock = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_curBlock)))) {
                gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1519, gd::gd_sub(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1519), lv_curBlock));
                (void)([&]() { gd::GdVal _ca[] = {lv_curBlock}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseBlock_206, _ca, 1); })();
            }
            else {
                (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseBlock_206, _ca, 1); })();
                gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1519, gd::GdVal::from_int(0LL));
            }
        }
        this->f_curHealth = gd::gd_coerce_float(gd::gd_sub(this->f_curHealth, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1519)));
        if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_wasCriticalHit_1524, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_spawnLabel_native_1149, _ca, 3); })();
        }
        else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2781)}; return gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_hasType_79, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(99LL), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_spawnLabel_native_1149, _ca, 3); })();
        }
        else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Poison_2664)}; return gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_hasType_79, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(108LL), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_spawnLabel_native_1149, _ca, 3); })();
        }
        else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Spikes_2662)}; return gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_hasType_79, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(104LL), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_spawnLabel_native_1149, _ca, 3); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_spawnLabel_native_1149, _ca, 3); })();
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_damage_anim_current, gd::GdVal::from_str(&battle_string_literals[22]))))) {
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1519), gd::GdVal::from_int(0LL))))) {
                this->f_damage_anim_current = gd::GdVal::from_str(&battle_string_literals[23]);
            }
            else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2781)}; return gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_hasType_79, _ca, 1); })())) {
                this->f_damage_anim_current = gd::GdVal::from_str(&battle_string_literals[24]);
            }
            else {
                this->f_damage_anim_current = gd::GdVal::from_str(&battle_string_literals[25]);
            }
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2781)}; return gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_hasType_79, _ca, 1); })()) ? (gd::GdVal::from_str(&battle_string_literals[24])) : (gd::GdVal::from_str(&battle_string_literals[25])))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_damageAnimation_1639, _ca, 2); })();
        }
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(3LL), gd::GdVal::from_int(0LL), lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_spawnLabel_native_1149, _ca, 3); })();
    }
    gd::GdVal lv_event = gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null())))) {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_damageRes, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_Attack_1358, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[26]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_damageRes}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_dealtDamage_224, _ca, 1); })();
    }
    else {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_damageRes, gd::get_prop(gd_ctx, this->f_opponent, SYM_GEN_playerId_1046), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_Damage_1359, _ca, 3); })();
    }
    gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517, lv_event);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[27]), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitEvent_1593, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[28]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1519), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onHealthChangedUI_1641, _ca, 1); })();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_isAttack_1560, nullptr, 0))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_hasDealtDamageEffect_64))) : gd::GdVal::from_bool(false)))) {
        {
            gd::GdVal _t575 = gd::gd_iter_seq(gd_ctx.arena, lv_attackEffectCount);
            gd::GdArr* _t576 = (_t575.kind == gd::GdVal::Kind::Arr) ? _t575.arr : nullptr;
            uint32_t _len__t577 = _t576 ? _t576->len : 0u;
            for (uint32_t _t577 = 0; _t577 < _len__t577; ++_t577) {
                gd::GdVal lv_i = _t576->data[_t577];
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[29]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN__behavior_call_504, _ca, 2); })();
            }
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f_curHealth, gd::GdVal::from_int(0LL))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_death_1169, nullptr, 0);
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_damageRes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_applySpikes_1150, _ca, 1); })();
    return lv_damageRes;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_spawnLabel_native(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_damage = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_damage = gd::gd_coerce_int(lv_damage);
    gd::GdVal lv_item = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(10.0)), gd::GdVal::from_float(10.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(10.0)), gd::GdVal::from_float(10.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    }
    if (gd::gd_truth((gd::gd_truth(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_native_frame_rng_1450)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_type, gd::GdVal::from_int(2LL))))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(gd::gd_is_type(lv_item, &META_Gd__gd_core__CoreItem))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_collectCriticalLabels_1490, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_type, lv_damage, lv_item}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_spawnLabel_character_1631, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_applySpikes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpikes_1223, nullptr, 0), gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_canTriggerSpikes_1532, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv_spikesLimit = gd::GdVal::from_float(0.0);
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Ranged_2786)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_hasType_79, _ca, 1); })())) {
            lv_spikesLimit = gd::gd_coerce_float(this->f_rangedSpikesLimit);
        }
        else {
            lv_spikesLimit = gd::gd_coerce_float(this->f_meleeSpikesLimit);
        }
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Effect_2656)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_hasType_79, _ca, 1); })())) {
            lv_spikesLimit = gd::gd_coerce_float(gd::gd_max(this->f_effectSpikesLimit, lv_spikesLimit));
        }
        gd::GdVal lv_spikeDam = gd::gd_min(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpikes_1223, nullptr, 0), gd::gd_round(gd::gd_mul(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_spikesLimit)));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_spikeDam, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_spikeDam}; return gd::call_method(gd_ctx, this->f_spikeDamageSource, SYM_GEN_setDamage_1551, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_spikeDamageSource, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_takeDamage_1148, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(104LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_activateBuffCounter_1623, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_applyVampirism(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getVampirism_1226, nullptr, 0), gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_canTriggerVampirism_1533, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv_vampLimit = gd::GdVal::from_float(0.0);
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Ranged_2786)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_hasType_79, _ca, 1); })())) {
            lv_vampLimit = gd::gd_coerce_float(this->f_rangedVampirismLimit);
        }
        else {
            lv_vampLimit = gd::gd_coerce_float(this->f_meleeVampirismLimit);
        }
        gd::GdVal lv_healAmount = gd::gd_min(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getVampirism_1226, nullptr, 0), gd::gd_round(gd::gd_mul(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_vampLimit)));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_healAmount, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_healAmount, gd::GdVal::from_int(103LL), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 3); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(103LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_activateBuffCounter_1623, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_heal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_origin = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    lv_amount = gd::gd_mul(lv_amount, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getHealingEfficiency_1181, nullptr, 0));
    lv_amount = gd::gd_round(lv_amount);
    gd::GdVal lv_missingHealth = gd::gd_sub(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxHealth_1160, nullptr, 0), this->f_curHealth);
    gd::GdVal lv_overheal = gd::gd_max(gd::GdVal::from_int(0LL), gd::gd_sub(lv_amount, lv_missingHealth));
    this->f_curHealth = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_curHealth, lv_amount));
    this->f_curHealth = gd::gd_coerce_float(gd::gd_min(this->f_curHealth, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxHealth_1160, nullptr, 0)));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onHealthChangedUI_1641, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_randHealNumberPos_1147, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_randDmgNumberDir_1146, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_origin, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(lv_origin, &META_Gd__gd_core__CoreItem)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(10.0)), gd::GdVal::from_float(10.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(10.0)), gd::GdVal::from_float(10.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(12LL), lv_amount, lv_origin}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_spawnLabel_character_1631, _ca, 4); })();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_amount, this->f_playerId, lv_origin, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_Heal_1360, _ca, 4); })();
    if (gd::gd_truth(lv_origin)) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(lv_origin, &META_Gd__gd_core__CoreItem)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), lv_amount}; return gd::call_method(gd_ctx, lv_origin, SYM_GEN_addMetric_230, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL), lv_overheal}; return gd::call_method(gd_ctx, lv_origin, SYM_GEN_addMetric_230, _ca, 2); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {this->f_playerId, gd::GdVal::from_int(1LL), lv_origin, lv_amount}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotMetric_1382, _ca, 4); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_playerId, gd::GdVal::from_int(2LL), lv_origin, lv_overheal}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotMetric_1382, _ca, 4); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[30]), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::call_method(gd_ctx, lv_event, SYM_GEN_getAmount_1576, nullptr, 0), lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitEvent_1593, _ca, 4); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_overheal, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[31]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_overheal, lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getUnhealing_1180, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_unhealing = gd::gd_ceil(gd::gd_mul(gd::gd_mul(lv_amount, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getUnhealing_1180, nullptr, 0)), gd::gd_add(gd_ctx, gd::GdVal::from_int(1LL), gd::get_index(gd_ctx, this->f_typedDamageFactors, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Unhealing_2790)))));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_unhealing, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_unhealing}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_unhealingDamageSource_1429), SYM_GEN_setDamage_1551, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_unhealingDamageSource_1429), lv_event}; return gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_takeDamage_1148, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_healToFull(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_curHealth = gd::gd_coerce_float(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxHealth_1160, nullptr, 0));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onHealthChangedUI_1641, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_reincarnate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_healAmount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_healAmount = gd::gd_coerce_int(lv_healAmount);
    gd::GdVal lv_isHeal = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_isHeal = gd::gd_coerce_bool(lv_isHeal);
    gd::GdVal lv_item = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setCurrentHealth_1156, _ca, 1); })();
    lv_healAmount = gd::gd_coerce_int(gd::gd_min(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxHealth_1160, nullptr, 0), lv_healAmount));
    (void)([&]() { gd::GdVal _ca[] = {lv_healAmount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setCurrentHealth_1156, _ca, 1); })();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_item, lv_healAmount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_Reincarnate_1379, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), lv_healAmount}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addMetric_230, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[32]), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitEvent_1593, _ca, 4); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getCurrentHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_curHealth;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getRelativeHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCurrentHealth_1154, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxHealth_1160, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getMissingHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_coerce_int(gd::gd_ceil(gd::gd_sub(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxHealth_1160, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCurrentHealth_1154, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setCurrentHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__curHealth = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_curHealth = gd::gd_coerce_float(lv__curHealth);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onHealthChangedUI_1641, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    this->f_curHealth = gd::gd_coerce_float(gd::gd_sub(this->f_curHealth, lv_amount));
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_randDmgNumberPos_1145, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_randDmgNumberDir_1146, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(5LL), gd::GdVal::null(), gd::GdVal::null(), lv_amount}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_spawnNumberLabel_1637, _ca, 4); })();
    gd::GdVal lv_event = gd::GdVal::null();
    if (gd::gd_truth(lv_item)) {
        lv_event = ([&]() { gd::GdVal _ca[] = {gd::gd_neg(lv_amount), this->f_playerId, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_LoseHealth_1361, _ca, 4); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[28]), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::call_method(gd_ctx, lv_event, SYM_GEN_getAmount_1576, nullptr, 0), lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitEvent_1593, _ca, 4); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onHealthChangedUI_1641, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f_curHealth, gd::GdVal::from_int(0LL))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_death_1169, nullptr, 0);
    }
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setMaxHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__maxHealth = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_maxHealth = gd::gd_coerce_float(lv__maxHealth);
    this->f_curHealth = gd::gd_coerce_float(this->f_maxHealth);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onHealthChangedUI_1641, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_giveMaxHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_maxHealth = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_maxHealth, lv_amount));
    this->f_curHealth = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_curHealth, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onHealthChangedUI_1641, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getBaseMaxHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_maxHealth;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getMaxHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, this->f_maxHealth, this->f_temporaryMaxHealth);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_applyTemporaryMaxHealthGain(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::gd_round(gd::gd_mul(lv_amount, this->f_temporaryMaxHealthGain));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeMaxHealthTemporary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_amount, gd::GdVal::from_int(0LL))))) {
        this->f_temporaryMaxHealth = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_temporaryMaxHealth, lv_amount));
        this->f_curHealth = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_curHealth, lv_amount));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null())))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_item, lv_amount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_TemporaryMaxHealth_1375, _ca, 3); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[33]), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitEvent_1593, _ca, 4); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getMaxStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, this->f_maxStamina, this->f_temporaryMaxStamina);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    this->f_curStamina = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_curStamina, lv_amount));
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_allowStaminaOverflow)))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clampStamina_1166, nullptr, 0);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null())))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_amount, lv_item, this->f_playerId, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_Stamina_1371, _ca, 4); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_logEvent_1357, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_staminaChanged_233, _ca, 2); })();
        (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_getNextFreeLabelPosition_378, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_addStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (this->f_curStamina.kind == gd::GdVal::Kind::Float
            && lv_amount.kind == gd::GdVal::Kind::Float
            && this->f_maxStamina.kind == gd::GdVal::Kind::Float
            && this->f_temporaryMaxStamina.kind == gd::GdVal::Kind::Float) {
        const double stamina = this->f_curStamina.f + lv_amount.f;
        const double limit = this->f_maxStamina.f + this->f_temporaryMaxStamina.f;
        // Preserve gd_clamp's ordered comparisons, including NaN and signed zero.
        this->f_curStamina = gd::GdVal::from_float(stamina < 0.0 ? 0.0 : (stamina > limit ? limit : stamina));
        return gd::GdVal::null();
    }
    this->f_curStamina = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_curStamina, lv_amount));
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clampStamina_1166, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_clampStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_curStamina = gd::gd_coerce_float(gd::gd_clamp(this->f_curStamina, gd::GdVal::from_int(0LL), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxStamina_1163, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_fillUpStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_maxStamina}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addStamina_1165, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_useStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_allowStaminaOverflow = gd::GdVal::from_bool(true);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[34]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_amount}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
    this->f_allowStaminaOverflow = gd::GdVal::from_bool(false);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(&battle_string_literals[8])))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_1420), gd::GdVal::null())))) : gd::GdVal::from_bool(false)))) {
        (void)gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_curStamina, lv_amount)))) {
        this->f_curStamina = gd::gd_coerce_float(gd::gd_max(gd::gd_sub(this->f_curStamina, lv_amount), gd::GdVal::from_int(0LL)));
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clampStamina_1166, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[35]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_amount}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
        return gd::GdVal::from_int(0LL);
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clampStamina_1166, nullptr, 0);
        return gd::GdVal::from_int(1LL);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_drainStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_drained = gd::gd_min(this->f_curStamina, lv_amount);
    this->f_curStamina = gd::gd_coerce_float(gd::gd_sub(this->f_curStamina, lv_drained));
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_drained, lv_item, this->f_playerId, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_DrainStamina_1372, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_logEvent_1357, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_drained, gd::GdVal::from_int(3LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_staminaChanged_233, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setTemporaryMaxStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(&battle_string_literals[8])))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_ctx, gd::GdVal::null())))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_1420), gd::GdVal::null())))) : gd::GdVal::from_bool(false)))) {
        (void)gd::GdVal::null();
    }
    this->f_temporaryMaxStamina = gd::gd_coerce_float(lv_amount);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setTemporaryMaxHealthGain(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_temporaryMaxHealthGain = gd::gd_coerce_float(lv_amount);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_death(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_isDead = gd::GdVal::from_bool(true);
    {
        gd::GdVal _t578 = gd::gd_iter_seq(gd_ctx.arena, this->f_character_died_handlers);
        gd::GdArr* _t579 = (_t578.kind == gd::GdVal::Kind::Arr) ? _t578.arr : nullptr;
        uint32_t _len__t580 = _t579 ? _t579->len : 0u;
        for (uint32_t _t580 = 0; _t580 < _len__t580; ++_t580) {
            gd::GdVal lv_handler = _t579->data[_t580];
            (void)gd::call_method(gd_ctx, lv_handler, gd::SYM_call_func, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_stun(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_duration = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stunResisted_1177, nullptr, 0))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_randBuffLabelPos_1143, nullptr, 0);
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_randBuffLabelDir_1144, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(10LL), gd::GdVal::null()}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_spawnBuffLabel_1636, _ca, 2); })();
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_item, this->f_playerId, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_StunResist_1368, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_logEvent_1357, _ca, 1); })();
    }
    else {
        this->f_stunnedDuration = gd::gd_coerce_float(gd::gd_max(this->f_stunnedDuration, lv_duration));
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_item, lv_duration, this->f_playerId, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_Stun_1367, _ca, 4); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[36]), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitEvent_1593, _ca, 4); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_duration, gd::GdVal::from_int(0LL))))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_randBuffLabelPos_1143, nullptr, 0);
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_randBuffLabelDir_1144, nullptr, 0);
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_duration}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_playStunAnimation_1624, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_endStun(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_stunnedDuration = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(5LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_isStunned(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_gt(this->f_stunnedDuration, gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeDodgeStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    this->f_dodgeStacks = gd::gd_coerce_int(gd::gd_coerce_int(gd::gd_max(gd::GdVal::from_int(0LL), gd::gd_add(gd_ctx, this->f_dodgeStacks, lv_amount))));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(10LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeCritResistance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    this->f_critResistance = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_critResistance, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(12LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_critResisted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_resisted = ([&]() { gd::GdVal _ca[] = {this->f_critResistance}; return gd::call_method(gd_ctx, this->f_critResistanceRng, SYM_GEN_rollPercent_1760, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_resisted)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_critResistStacks, gd::GdVal::from_int(0LL))))) {
            this->f_critResistStacks = gd::gd_coerce_int(gd::gd_sub(this->f_critResistStacks, gd::GdVal::from_int(1LL)));
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(11LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
            return gd::GdVal::from_bool(true);
        }
    }
    return lv_resisted;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainCritResistStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_num = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_num = gd::gd_coerce_int(lv_num);
    this->f_critResistStacks = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_critResistStacks, lv_num));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(11LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeStunResistance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    this->f_stunResistance = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_stunResistance, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_stunResisted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {this->f_stunResistance}; return gd::call_method(gd_ctx, this->f_stunResistanceRng, SYM_GEN_rollPercent_1760, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_giveUnhealing(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    this->f_unhealingAmount = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_unhealingAmount, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(19LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_reduceUnhealing(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    this->f_unhealingAmount = gd::gd_coerce_float(gd::gd_max(gd::GdVal::from_float(0.0), gd::gd_sub(this->f_unhealingAmount, lv_amount)));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(19LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getUnhealing(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_unhealingAmount;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getHealingEfficiency(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_max(gd::GdVal::from_float(0.0), this->f_healingEfficiency);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_addHealingEfficiency(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    this->f_healingEfficiency = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_healingEfficiency, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(14LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_reduceHealingEfficiency(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    this->f_healingEfficiency = gd::gd_coerce_float(gd::gd_sub(this->f_healingEfficiency, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(14LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getCritTokens(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_critTokens;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainCritTokens(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_critTokens = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_critTokens, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeDebuffResistStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_debuffResistStacks = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_debuffResistStacks, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(8LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeDebuffReflectStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_debuffReflectStacks = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_debuffReflectStacks, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(7LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeBuffProtectStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_buffProtectStacks = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_buffProtectStacks, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeReflectChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_debuff = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_debuff), SYM_GEN_changeReflectChance_1029, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeAllDebuffsReflectChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t581 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1391, nullptr, 0));
        gd::GdArr* _t582 = (_t581.kind == gd::GdVal::Kind::Arr) ? _t581.arr : nullptr;
        uint32_t _len__t583 = _t582 ? _t582->len : 0u;
        for (uint32_t _t583 = 0; _t583 < _len__t583; ++_t583) {
            gd::GdVal lv_debuff = _t582->data[_t583];
            (void)([&]() { gd::GdVal _ca[] = {lv_debuff, lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeReflectChance_1029, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeMeleeSpikesLimit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_meleeSpikesLimit = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_meleeSpikesLimit, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeRangedSpikesLimit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_rangedSpikesLimit = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_rangedSpikesLimit, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeEffectSpikesLimit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_effectSpikesLimit = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_effectSpikesLimit, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeMeleeVampirismLimit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_meleeVampirismLimit = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_meleeVampirismLimit, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeRangedVampirismLimit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_rangedVampirismLimit = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_rangedVampirismLimit, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getBonusFatigueDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_bonusFatigueDamage;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_addFatigueDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_bonusFatigueDamage = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_bonusFatigueDamage, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[37])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_takeFatigueDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_fatigueDamageSource_1430)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_takeDamage_1148, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_startBlindingLight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_blindingLightActive = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_endBlindingLight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    this->f_blindingLightActive = gd::GdVal::from_bool(false);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[38]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_startBattleRage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_applyBonus = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_fullDur = lv_duration;
    if (gd::gd_truth(lv_applyBonus)) {
        lv_fullDur = gd::gd_add(gd_ctx, lv_fullDur, this->f_battleRageBonusDur);
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_fullDur}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__setRageTimer_1210, _ca, 1); })();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_item, lv_fullDur, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_BattleRageStart_1377, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[39]), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitEvent_1593, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(6LL), gd::GdVal::from_bool(false), lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_playBattleRageAnimation_1209, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_endBattleRage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f__rage_active = gd::GdVal::from_bool(false);
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_playerId}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_BattleRageEnd_1378, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[40]), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitEvent_1593, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(6LL), gd::GdVal::from_bool(false), lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_playBattleRageAnimation_1209, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getClass(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_characterClass;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_isChibi(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_chibi;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setClass(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__class = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__class = gd::gd_coerce_int(lv__class);
    gd::GdVal lv__chibi = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv__chibi = gd::gd_coerce_bool(lv__chibi);
    gd::GdVal lv_classResource = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    this->f_characterClass = gd::gd_coerce_int(lv__class);
    this->f_chibi = lv__chibi;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_classResource, gd::GdVal::null())))) {
        lv_classResource = (gd::gd_truth(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_class_resources_1428)) ? (([&]() { gd::GdVal _ca[] = {lv__class, gd::GdVal::null()}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_class_resources_1428), gd::SYM_get, _ca, 2); })()) : (gd::GdVal::null()));
    }
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_classResource, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_playerId, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_classResource}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setClassResource_1204, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_classResource}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onClassChanged_1628, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[41]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setClassResource(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_classResource = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_classResource, gd::GdVal::null())))) {
        return gd::GdVal::null();
    }
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[42])}; return gd::call_method(gd_ctx, lv_classResource, gd::SYM_get, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setMaxHealth_1158, _ca, 1); })();
    this->f_baseMaxStamina = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[43])}; return gd::call_method(gd_ctx, lv_classResource, gd::SYM_get, _ca, 1); })());
    (void)([&]() { gd::GdVal _ca[] = {this->f_baseMaxStamina}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setMaxStamina_1266, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_classResource}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onClassChanged_1628, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_lose(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_playWinLoseAnimation_1627, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_win(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_playWinLoseAnimation_1627, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setStat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stat = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 1) ? _args[1] : gd::GdVal::null();
    {
        gd::GdVal _t584 = lv_stat;
        if (gd::gd_eq(_t584, gd::GdVal::from_int(0LL))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_value}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setCurrentHealth_1156, _ca, 1); })();
        }
        else if (gd::gd_eq(_t584, gd::GdVal::from_int(1LL))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_value}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setTemporaryMaxHealth_1275, _ca, 1); })();
        }
        else if (gd::gd_eq(_t584, gd::GdVal::from_int(2LL))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_value}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setCurrentStamina_1263, _ca, 1); })();
        }
        else if (gd::gd_eq(_t584, gd::GdVal::from_int(3LL))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(lv_value, this->f_maxStamina)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setTemporaryMaxStamina_1167, _ca, 1); })();
        }
        else if (gd::gd_eq(_t584, gd::GdVal::from_int(5LL))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_value}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_playStunAnimation_1624, _ca, 2); })();
        }
        else if (gd::gd_eq(_t584, gd::GdVal::from_int(4LL))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_value}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_playInvulnerableAnimation_1629, _ca, 2); })();
        }
        else if (gd::gd_eq(_t584, gd::GdVal::from_int(6LL))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_value}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_playBattleRageAnimation_1209, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getStat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stat = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t585 = lv_stat;
        if (gd::gd_eq(_t585, gd::GdVal::from_int(20LL))) {
            return gd::gd_mul(gd::gd_sub(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStaminaRegeneration_1269, nullptr, 0), gd::GdVal::from_int(1LL)), gd::GdVal::from_float(100.0));
        }
        else if (gd::gd_eq(_t585, gd::GdVal::from_int(0LL))) {
            return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCurrentHealth_1154, nullptr, 0);
        }
        else if (gd::gd_eq(_t585, gd::GdVal::from_int(1LL))) {
            return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getTemporaryMaxHealth_1274, nullptr, 0);
        }
        else if (gd::gd_eq(_t585, gd::GdVal::from_int(2LL))) {
            return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCurrentStamina_1262, nullptr, 0);
        }
        else if (gd::gd_eq(_t585, gd::GdVal::from_int(3LL))) {
            return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxStamina_1163, nullptr, 0);
        }
        else if (gd::gd_eq(_t585, gd::GdVal::from_int(5LL))) {
            return this->f_stunnedDuration;
        }
        else if (gd::gd_eq(_t585, gd::GdVal::from_int(4LL))) {
            return this->f_invulnerable;
        }
        else if (gd::gd_eq(_t585, gd::GdVal::from_int(6LL))) {
            return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBattleRaging_1207, nullptr, 0);
        }
        else if (gd::gd_eq(_t585, gd::GdVal::from_int(7LL))) {
            return this->f_debuffReflectStacks;
        }
        else if (gd::gd_eq(_t585, gd::GdVal::from_int(8LL))) {
            return this->f_debuffResistStacks;
        }
        else if (gd::gd_eq(_t585, gd::GdVal::from_int(9LL))) {
            return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCritTokens_182, nullptr, 0);
        }
        else if (gd::gd_eq(_t585, gd::GdVal::from_int(10LL))) {
            return this->f_dodgeStacks;
        }
        else if (gd::gd_eq(_t585, gd::GdVal::from_int(11LL))) {
            return this->f_critResistStacks;
        }
        else if (gd::gd_eq(_t585, gd::GdVal::from_int(12LL))) {
            return this->f_critResistance;
        }
        else if (gd::gd_eq(_t585, gd::GdVal::from_int(13LL))) {
            return this->f_stunResistance;
        }
        else if (gd::gd_eq(_t585, gd::GdVal::from_int(14LL))) {
            return gd::gd_mul(gd::gd_sub(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getHealingEfficiency_1181, nullptr, 0), gd::GdVal::from_int(1LL)), gd::GdVal::from_int(100LL));
        }
        else if (gd::gd_eq(_t585, gd::GdVal::from_int(15LL))) {
            return this->f_damageResistance;
        }
        else if (gd::gd_eq(_t585, gd::GdVal::from_int(16LL))) {
            return gd::gd_mul(gd::get_index(gd_ctx, this->f_typedDamageFactors, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Melee_2808)), gd::GdVal::from_int(100LL));
        }
        else if (gd::gd_eq(_t585, gd::GdVal::from_int(17LL))) {
            return gd::gd_mul(gd::get_index(gd_ctx, this->f_typedDamageFactors, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Ranged_2786)), gd::GdVal::from_int(100LL));
        }
        else if (gd::gd_eq(_t585, gd::GdVal::from_int(18LL))) {
            return gd::gd_mul(gd::get_index(gd_ctx, this->f_typedDamageFactors, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Effect_2656)), gd::GdVal::from_int(100LL));
        }
        else if (gd::gd_eq(_t585, gd::GdVal::from_int(19LL))) {
            return gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getUnhealing_1180, nullptr, 0), gd::GdVal::from_int(100LL));
        }
        else if (gd::gd_eq(_t585, gd::GdVal::from_int(21LL))) {
            return gd::gd_mul(gd::gd_sub(this->f_temporaryMaxHealthGain, gd::GdVal::from_float(1.0)), gd::GdVal::from_int(100LL));
        }
    }
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_isBattleRaging(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(this->f__rage_active) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f__rage_left, gd::GdVal::from_float(0.0))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_startAutoRage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_autoRageItem, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_AUTO_RAGE_DUR_1045)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_startBattleRage_1199, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_playBattleRageAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rageStart = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_rageStart}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_playBattleRageAnimation_1209, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn__setRageTimer(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_duration = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_duration = gd::gd_coerce_float(lv_duration);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_duration, gd::GdVal::from_float(0.0))))) {
        this->f__rage_wait = ([&]() { gd::GdVal _ca[] = {lv_duration}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })();
    }
    this->f__rage_left = gd::gd_coerce_float(this->f__rage_wait);
    this->f__rage_active = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::sf__f32eng(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    (void)gd_ctx;
    const auto value = gd::gd_coerce_float(_argc > 0 ? _args[0] : gd::GdVal::null());
    return gd::GdVal::from_float(static_cast<double>(static_cast<float>(value.as_float())));
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_makeInvulnerable(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_duration = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    this->f_invulnerabilityItem = lv_item;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_invulnerable)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_duration}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__startInvulnerability_1296, _ca, 1); })();
        this->f_invulnerable = gd::GdVal::from_bool(true);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_playInvulnerableAnimation_1629, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1), gd::GdVal::from_str(&battle_string_literals[44])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 3); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, lv_duration, ([&]() { gd::GdVal _ca[] = {gd::gd_max(gd::GdVal::from_float(0.0), this->f__invul_left)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })())}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__startInvulnerability_1296, _ca, 1); })();
    }
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_item, lv_duration, this->f_playerId, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_InvulnerableStart_1369, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[45]), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitEvent_1593, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(4LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_makeVulnerable(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_invulnerabilityEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_invulnerable = gd::GdVal::from_bool(false);
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_invulnerabilityItem, this->f_playerId}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_InvulnerableEnd_1370, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[46]), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitEvent_1593, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(4LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_playInvulnerableAnimation_1629, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setInvulnerable(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_active = gd::gd_coerce_bool(lv_active);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    this->f_invulnerable = lv_active;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_getStacks_1023, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getBuffStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stacks = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t586 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0));
        gd::GdArr* _t587 = (_t586.kind == gd::GdVal::Kind::Arr) ? _t586.arr : nullptr;
        uint32_t _len__t588 = _t587 ? _t587->len : 0u;
        for (uint32_t _t588 = 0; _t588 < _len__t588; ++_t588) {
            gd::GdVal lv_buff = _t587->data[_t588];
            lv_stacks = gd::gd_add(gd_ctx, lv_stacks, ([&]() { gd::GdVal _ca[] = {lv_buff}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1023, _ca, 1); })());
        }
    }
    return lv_stacks;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getDebuffStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stacks = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t589 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1391, nullptr, 0));
        gd::GdArr* _t590 = (_t589.kind == gd::GdVal::Kind::Arr) ? _t589.arr : nullptr;
        uint32_t _len__t591 = _t590 ? _t590->len : 0u;
        for (uint32_t _t591 = 0; _t591 < _len__t591; ++_t591) {
            gd::GdVal lv_debuff = _t590->data[_t591];
            lv_stacks = gd::gd_add(gd_ctx, lv_stacks, ([&]() { gd::GdVal _ca[] = {lv_debuff}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1023, _ca, 1); })());
        }
    }
    return lv_stacks;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_setStacks_1024, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setStacksLogged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_curStacks = ([&]() { gd::GdVal _ca[] = {lv_buffType}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1023, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, lv_curStacks)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_buffType, gd::gd_sub(lv_curStacks, lv_amount), lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1032, _ca, 4); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, lv_curStacks)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_buffType, gd::gd_sub(lv_amount, lv_curStacks), lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1030, _ca, 4); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_reflect = (_argc > 4) ? _args[4] : (gd::GdVal::from_bool(false));
    lv_reflect = gd::gd_coerce_bool(lv_reflect);
    return ([&]() { gd::GdVal _ca[] = {lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_gainStacks_1030, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainStacksTemporary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_duration = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 4) ? _args[4] : (gd::GdVal::null());
    gd::GdVal lv_reflect = (_argc > 5) ? _args[5] : (gd::GdVal::from_bool(false));
    lv_reflect = gd::gd_coerce_bool(lv_reflect);
    return ([&]() { gd::GdVal _ca[] = {lv_amount, lv_duration, lv_item, lv_triggerEvent, lv_reflect}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_gainTemporary_1031, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_loseStacks_1032, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_useStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {lv_amount, lv_item, lv_triggerEvent, gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_loseStacks_1032, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeResistChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_chance = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_changeResistChance_1026, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeDebuffResistChances(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t592 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1391, nullptr, 0));
        gd::GdArr* _t593 = (_t592.kind == gd::GdVal::Kind::Arr) ? _t592.arr : nullptr;
        uint32_t _len__t594 = _t593 ? _t593->len : 0u;
        for (uint32_t _t594 = 0; _t594 < _len__t594; ++_t594) {
            gd::GdVal lv_debuff = _t593->data[_t594];
            (void)([&]() { gd::GdVal _ca[] = {lv_debuff, lv_chance}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeResistChance_1026, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeResistStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_changeResistStacks_1027, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(100LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1023, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(104LL), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1024, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(100LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1030, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(100LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1032, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getSpikes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(104LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1023, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setSpikes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(104LL), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1024, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainSpikes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(104LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1030, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseSpikes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(104LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1032, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getVampirism(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(103LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1023, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setVampirism(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(103LL), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1024, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainVampirism(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(103LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1030, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseVampirism(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(103LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1032, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getPoison(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(108LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1023, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setPoison(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(108LL), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1024, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainPoison(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(108LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1030, _ca, 4); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        this->f_damage_anim_current = gd::GdVal::from_str(&battle_string_literals[22]);
    }
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_losePoison(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(108LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1032, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getRegeneration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(102LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1023, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setRegeneration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(102LL), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1024, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainRegeneration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(102LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1030, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseRegeneration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(102LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1032, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getLucky(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(101LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1023, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setLucky(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(101LL), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1024, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainLucky(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(101LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1030, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseLucky(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(101LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1032, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getBlind(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(109LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1023, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setBlind(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(109LL), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1024, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainBlind(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(109LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1030, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseBlind(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(109LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1032, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getMana(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(105LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1023, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setMana(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(105LL), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1024, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainMana(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(105LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1030, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseMana(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(105LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1032, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getEmpower(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(106LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1023, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setEmpower(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(106LL), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1024, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainEmpower(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(106LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1030, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseEmpower(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(106LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1032, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getHeat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(107LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1023, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setHeat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(107LL), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1024, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainHeat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(107LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1030, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseHeat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(107LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1032, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getCold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(110LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1023, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setCold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(110LL), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1024, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainCold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(110LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1030, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseCold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(110LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1032, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getBuffDamageMod(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getEmpower_1248, nullptr, 0), this->f_empowerDamage);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getBuffAccuracyMod(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_mul(gd::gd_sub(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getLucky_1237, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlind_1240, nullptr, 0)), gd::GdVal::from_int(5LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getBaseMaxStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_baseMaxStamina;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getMaxBaseStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_maxStamina;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getCurrentStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_curStamina;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setCurrentStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stamina = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_stamina = gd::gd_coerce_float(lv_stamina);
    this->f_curStamina = gd::gd_coerce_float(lv_stamina);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getMissingStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_sub(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxStamina_1163, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCurrentStamina_1262, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_isFullStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_le(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMissingStamina_1264, nullptr, 0), gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setMaxStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__maxStamina = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(&battle_string_literals[8])))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_ctx, gd::GdVal::null())))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_1420), gd::GdVal::null())))) : gd::GdVal::from_bool(false)))) {
        (void)gd::GdVal::null();
    }
    this->f_maxStamina = gd::gd_coerce_float(lv__maxStamina);
    this->f_curStamina = gd::gd_coerce_float(this->f_maxStamina);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onMaxStaminaChangedUI_1642, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_giveMaxStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_maxStamina = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_maxStamina, lv_amount));
    this->f_curStamina = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_curStamina, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onMaxStaminaChangedUI_1642, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_reduceMaxStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_maxStamina = gd::gd_coerce_float(gd::gd_max(gd::GdVal::from_int(1LL), gd::gd_sub(this->f_maxStamina, lv_amount)));
    this->f_curStamina = gd::gd_coerce_float(gd::gd_min(this->f_maxStamina, this->f_curStamina));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onMaxStaminaChangedUI_1642, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainMaxStaminaTemporary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_filled = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(true));
    lv_filled = gd::gd_coerce_bool(lv_filled);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_amount, gd::GdVal::from_int(0LL))))) {
        this->f_temporaryMaxStamina = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_temporaryMaxStamina, lv_amount));
        if (gd::gd_truth((gd::gd_truth(lv_filled) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
            this->f_curStamina = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_curStamina, lv_amount));
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null())))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_item, lv_amount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_TemporaryMaxStamina_1376, _ca, 3); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_logEvent_1357, _ca, 1); })();
            if (gd::gd_truth(lv_filled)) {
                (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_staminaChanged_233, _ca, 2); })();
            }
            (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_getNextFreeLabelPosition_378, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(20LL), lv_item, lv_amount}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_spawnLabelOnItem_1643, _ca, 3); })();
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onMaxStaminaChangedUI_1642, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getStaminaRegeneration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_staminaRegen;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_giveStaminaRegeneration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_staminaRegen = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_staminaRegen, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(20LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getTotalStaminaUsage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_totalStaminaUse = gd::GdVal::from_float(0.0);
    {
        gd::GdVal _t595 = gd::gd_iter_seq(gd_ctx.arena, this->f_items);
        gd::GdArr* _t596 = (_t595.kind == gd::GdVal::Kind::Arr) ? _t595.arr : nullptr;
        uint32_t _len__t597 = _t596 ? _t596->len : 0u;
        for (uint32_t _t597 = 0; _t597 < _len__t597; ++_t597) {
            gd::GdVal lv_item = _t596->data[_t597];
            gd::GdVal lv_staminaUse = gd::call_method(gd_ctx, lv_item, SYM_GEN_getStaminaCost_112, nullptr, 0);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, lv_item, SYM_GEN_getCooldown_102, nullptr, 0), gd::GdVal::from_int(0LL))))) {
                lv_staminaUse = gd::gd_div(gd_ctx, lv_staminaUse, gd::call_method(gd_ctx, lv_item, SYM_GEN_getCooldown_102, nullptr, 0));
            }
            lv_totalStaminaUse = gd::gd_add(gd_ctx, lv_totalStaminaUse, lv_staminaUse);
        }
    }
    return lv_totalStaminaUse;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeBaseMaxStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_playerId, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_staminaUpdateQueued)))) : gd::GdVal::from_bool(false)))) {
        this->f_staminaUpdateQueued = gd::GdVal::from_bool(true);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[47])}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1482, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_recalculateMaxStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_staminaUpdateQueued = gd::GdVal::from_bool(false);
    this->f_maxStamina = gd::gd_coerce_float(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseMaxStamina_1260, nullptr, 0));
    gd::GdVal lv__sack = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t598 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t599 = (_t598.kind == gd::GdVal::Kind::Arr) ? _t598.arr : nullptr;
        uint32_t _len__t600 = _t599 ? _t599->len : 0u;
        for (uint32_t _t600 = 0; _t600 < _len__t600; ++_t600) {
            gd::GdVal lv_item = _t599->data[_t600];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), SYM_GEN_name_7), gd::GdVal::from_str(&battle_string_literals[48]))))) {
                this->f_maxStamina = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_maxStamina, gd::GdVal::from_int(1LL)));
                lv__sack = gd::gd_add(gd_ctx, lv__sack, gd::GdVal::from_int(1LL));
            }
        }
    }
    this->f_curStamina = gd::gd_coerce_float(this->f_maxStamina);
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(&battle_string_literals[8])))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_ctx, gd::GdVal::null())))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_1420), gd::GdVal::null())))) : gd::GdVal::from_bool(false)))) {
        (void)gd::GdVal::null();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onMaxStaminaChangedUI_1642, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getTemporaryMaxHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_temporaryMaxHealth;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setTemporaryMaxHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_tempHealth = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_temporaryMaxHealth = gd::gd_coerce_float(lv_tempHealth);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onHealthChangedUI_1641, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_reduceMaxHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_maxHealth = gd::gd_coerce_float(gd::gd_max(gd::GdVal::from_int(1LL), gd::gd_sub(this->f_maxHealth, lv_amount)));
    this->f_curHealth = gd::gd_coerce_float(gd::gd_min(this->f_maxHealth, this->f_curHealth));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onHealthChangedUI_1641, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeMaxHealthGain(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_temporaryMaxHealthGain = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_temporaryMaxHealthGain, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(21LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeDamageReduction(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    this->f_damageReduction = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_damageReduction, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeDamageResistance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_duration = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    this->f_damageResistance = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_damageResistance, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(15LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null())))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_item, gd::gd_neg(lv_amount), gd::GdVal::from_bool(true), lv_duration, gd::GdVal::null(), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_DamChange_1381, _ca, 6); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_logEvent_1357, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeTypedDamageFactor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_damageType = gd::gd_coerce_int(lv_damageType);
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    { gd::GdVal _t601 = this->f_typedDamageFactors; gd::GdVal _t602 = lv_damageType; gd::set_index(gd_ctx, _t601, _t602, gd::gd_add(gd_ctx, gd::get_index(gd_ctx, _t601, _t602), lv_amount)); }
    {
        gd::GdVal _t603 = gd::gd_iter_seq(gd_ctx.arena, this->f_items);
        gd::GdArr* _t604 = (_t603.kind == gd::GdVal::Kind::Arr) ? _t603.arr : nullptr;
        uint32_t _len__t605 = _t604 ? _t604->len : 0u;
        for (uint32_t _t605 = 0; _t605 < _len__t605; ++_t605) {
            gd::GdVal lv_item = _t604->data[_t605];
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_item, SYM_GEN_damageSource_24), gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_damageType}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_item, SYM_GEN_damageSource_24), SYM_GEN_hasType_79, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
            }
        }
    }
    {
        gd::GdVal _t606 = lv_damageType;
        if (gd::gd_eq(_t606, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Melee_2808))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(16LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
        }
        else if (gd::gd_eq(_t606, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Ranged_2786))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(17LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
        }
        else if (gd::gd_eq(_t606, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Effect_2656))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(18LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeEffectDamageFactor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    { gd::GdVal _t607 = this->f_typedDamageFactors; gd::GdVal _t608 = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Effect_2656); gd::set_index(gd_ctx, _t607, _t608, gd::gd_add(gd_ctx, gd::get_index(gd_ctx, _t607, _t608), lv_amount)); }
    { gd::GdVal _t609 = this->f_typedDamageFactors; gd::GdVal _t610 = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Unhealing_2790); gd::set_index(gd_ctx, _t609, _t610, gd::gd_add(gd_ctx, gd::get_index(gd_ctx, _t609, _t610), lv_amount)); }
    {
        gd::GdVal _t611 = gd::gd_iter_seq(gd_ctx.arena, this->f_items);
        gd::GdArr* _t612 = (_t611.kind == gd::GdVal::Kind::Arr) ? _t611.arr : nullptr;
        uint32_t _len__t613 = _t612 ? _t612->len : 0u;
        for (uint32_t _t613 = 0; _t613 < _len__t613; ++_t613) {
            gd::GdVal lv_item = _t612->data[_t613];
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_item, SYM_GEN_damageSource_24), gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Effect_2656)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_item, SYM_GEN_damageSource_24), SYM_GEN_hasType_79, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(18LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeEmpowerDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_empowerDamage = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_empowerDamage, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changePoisonCritChancePercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, this->f_poisonDamageSource, SYM_GEN_addCritChancePercent_179, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeSpikesCritChancePercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, this->f_spikeDamageSource, SYM_GEN_addCritChancePercent_179, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_useCritToken(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_critTokens = gd::gd_coerce_int(gd::gd_sub(this->f_critTokens, gd::GdVal::from_int(1LL)));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(9LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotCharacterStat_1387, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_useMana(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(105LL), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStacks_1219, _ca, 4); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeProtectionChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_chance = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_changeCleanseProtectionChance_1028, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeBuffProtectionChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t614 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0));
        gd::GdArr* _t615 = (_t614.kind == gd::GdVal::Kind::Arr) ? _t614.arr : nullptr;
        uint32_t _len__t616 = _t615 ? _t615->len : 0u;
        for (uint32_t _t616 = 0; _t616 < _len__t616; ++_t616) {
            gd::GdVal lv_buff = _t615->data[_t616];
            (void)([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buff), SYM_GEN_changeCleanseProtectionChance_1028, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeDebuffProtectionChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t617 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1391, nullptr, 0));
        gd::GdArr* _t618 = (_t617.kind == gd::GdVal::Kind::Arr) ? _t617.arr : nullptr;
        uint32_t _len__t619 = _t618 ? _t618->len : 0u;
        for (uint32_t _t619 = 0; _t619 < _len__t619; ++_t619) {
            gd::GdVal lv_debuff = _t618->data[_t619];
            (void)([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_debuff), SYM_GEN_changeCleanseProtectionChance_1028, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeBuffNullifyChances(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t620 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0));
        gd::GdArr* _t621 = (_t620.kind == gd::GdVal::Kind::Arr) ? _t620.arr : nullptr;
        uint32_t _len__t622 = _t621 ? _t621->len : 0u;
        for (uint32_t _t622 = 0; _t622 < _len__t622; ++_t622) {
            gd::GdVal lv_buff = _t621->data[_t622];
            (void)([&]() { gd::GdVal _ca[] = {lv_buff, lv_chance}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeResistChance_1026, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeDebuffNullifyChances(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t623 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1391, nullptr, 0));
        gd::GdArr* _t624 = (_t623.kind == gd::GdVal::Kind::Arr) ? _t623.arr : nullptr;
        uint32_t _len__t625 = _t624 ? _t624->len : 0u;
        for (uint32_t _t625 = 0; _t625 < _len__t625; ++_t625) {
            gd::GdVal lv_debuff = _t624->data[_t625];
            (void)([&]() { gd::GdVal _ca[] = {lv_debuff, lv_chance}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeResistChance_1026, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_addBattleRageDuration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dur = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_battleRageBonusDur = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_battleRageBonusDur, lv_dur));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_isVulnerable(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(!gd::gd_truth(this->f_invulnerable));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_physicsTickCharacter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (gd::gd_truth(this->fn_isStunned(nullptr, 0))) {
        this->f_stunnedDuration = gd::gd_coerce_float(gd::gd_sub(this->f_stunnedDuration, lv_delta));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f_stunnedDuration, gd::GdVal::from_float(0.0))))) {
            this->f_stunnedDuration = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
            (void)this->fn_endStun(nullptr, 0);
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_staminaRegen, lv_delta)}; return this->fn_addStamina(_ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_tickPhysicsTimers(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (gd::gd_truth(this->f__tick_timer_active) && (this->f__physics_timer_mask.as_int() & 1)) {
        this->f__tick_timer_left = gd::gd_sub(this->f__tick_timer_left, lv_delta);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f__tick_timer_left, gd::GdVal::from_float(0.0))))) {
            this->f__tick_timer_left = gd::gd_add(gd_ctx, this->f__tick_timer_left, gd::GdVal::from_float(1.0));
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onTick_1134, nullptr, 0);
        }
    }
    if (gd::gd_truth(this->f__rage_active) && (this->f__physics_timer_mask.as_int() & 2)) {
        this->f__rage_left = gd::gd_coerce_float(gd::gd_sub(this->f__rage_left, lv_delta));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f__rage_left, gd::GdVal::from_float(0.0))))) {
            this->f__rage_active = gd::GdVal::from_bool(false);
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_endBattleRage_1200, nullptr, 0);
        }
    }
    if (gd::gd_truth(this->f__invul_active) && (this->f__physics_timer_mask.as_int() & 4)) {
        this->f__invul_left = gd::gd_coerce_float(gd::gd_sub(this->f__invul_left, lv_delta));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f__invul_left, gd::GdVal::from_float(0.0))))) {
            this->f__invul_active = gd::GdVal::from_bool(false);
            this->f__invul_left = gd::gd_coerce_float(gd::gd_neg(gd::GdVal::from_float(1.0)));
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_invulnerabilityEnded_1213, nullptr, 0);
        }
    }
    if (gd::gd_truth(this->f__autoRage_active) && (this->f__physics_timer_mask.as_int() & 8)) {
        this->f__autoRage_left = gd::gd_coerce_float(gd::gd_sub(this->f__autoRage_left, lv_delta));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f__autoRage_left, gd::GdVal::from_float(0.0))))) {
            this->f__autoRage_left = gd::gd_coerce_float(gd::gd_neg(gd::GdVal::from_float(1.0)));
            this->f__autoRage_active = gd::GdVal::from_bool(false);
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_startAutoRage_1208, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_tickBuffs(const gd::GdVal* args, int argc) {
    const auto delta = gd::gd_coerce_float(argc > 0 ? args[0] : gd::GdVal::null());
    const auto* buffs = this->f_buffs.dict;
    const auto* entries = buffs->entries;
    for (uint32_t i = 0, count = buffs->len; i < count; ++i) {
        auto* buff = static_cast<Gd__gd_core__CoreBuff*>(entries[i].val.obj);
        const auto& active = buff->f__timer_active;
        if (active.kind == gd::GdVal::Kind::Bool ? active.b : gd::gd_truth(active)) buff->fn__tick(&delta, 1);
    }
    return gd::GdVal::null();
}

gd::GdVal Gd__gd_core__CoreCharacter::fn_rebuildTimerSeen(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_snapshotPhysicsTimers(const gd::GdVal*, int) {
    const int64_t mask = (gd::gd_truth(this->f__tick_timer_active) ? 1 : 0)
                       | (gd::gd_truth(this->f__rage_active) ? 2 : 0)
                       | (gd::gd_truth(this->f__invul_active) ? 4 : 0)
                       | (gd::gd_truth(this->f__autoRage_active) ? 8 : 0);
    this->f__physics_timer_mask = gd::GdVal::from_int(mask);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn__startInvulnerability(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_duration = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_duration = gd::gd_coerce_float(lv_duration);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_duration, gd::GdVal::from_float(0.0))))) {
        this->f__invul_wait = ([&]() { gd::GdVal _ca[] = {lv_duration}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })();
    }
    this->f__invul_left = gd::gd_coerce_float(this->f__invul_wait);
    this->f__invul_active = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreCharacter(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreCharacter>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__CoreCharacter = {CLS_Gd__gd_core__CoreCharacter, "CoreCharacter", "res://gd_core/CoreCharacter.gd", nullptr, false, _alloc_Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::get_static_prop_fn, &Gd__gd_core__CoreCharacter::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreItemData_ReleaseState[] = {{"Demo", 0LL}, {"Full", 1LL}, {"Unreleased", 2LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreItemData_ReleaseState = {"ReleaseState", _ekv_Gd__gd_core__CoreItemData_ReleaseState, 3u};
void Gd__gd_core__CoreItemData::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_name = gd::GdVal::from_str(&battle_string_literals[8]);
    this->f_identifier = gd::GdVal::from_str(&battle_string_literals[8]);
    this->f_itemIndex = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_minDam = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_maxDam = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_staminaCost = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_block = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_cd = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_extraCds = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_accuracy = gd::gd_coerce_float(gd::GdVal::from_float(100.0));
    this->f_canActivate = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
    this->f_chance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_chance2 = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_shopChance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_types = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_tags = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_physics = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_rarity = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_price = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_classes = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_randomUniquePool = gd::GdVal::from_bool(false);
    this->f_hasBattleRageEffect = gd::GdVal::from_bool(false);
    this->f_gatedItems = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_startsSubclass = gd::GdVal::from_str(&battle_string_literals[8]);
    this->f_gateItem = gd::GdVal::null();
    this->f_originatingRecipes = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_animationScene = gd::GdVal::from_bool(false);
    this->f_flickerAni = gd::GdVal::from_bool(false);
    this->f_flickerMinDist = gd::GdVal::from_float(0.1);
    this->f_flickerMaxDist = gd::GdVal::from_float(3.0);
    this->f_flickerMinSpeed = gd::GdVal::from_float(0.3);
    this->f_flickerMaxSpeed = gd::GdVal::from_float(1.0);
    this->f_connectorReadyRoll = gd::GdVal::from_bool(false);
    this->f_gemRoll = gd::GdVal::from_bool(false);
    this->f_sceneDepth = gd::GdVal::from_int(2LL);
    this->f_releaseState = gd::gd_coerce_int(gd::GdVal::from_int(1LL));
    this->f__editor = gd::GdVal::from_bool(false);
    this->f__playtest = gd::GdVal::from_bool(false);
    this->f__full_version = gd::GdVal::from_bool(false);
    this->f__engineer_test = gd::GdVal::from_bool(false);
    this->f_params = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_namedParams = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_sortedParamNames = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_paramBases = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_paramBases_inverted = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_gainedStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_removedStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_usedStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_activationAni = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__CoreItemData::meta() const { return &META_Gd__gd_core__CoreItemData; }
gd::GdVal Gd__gd_core__CoreItemData::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_ReleaseState_1727: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreItemData_ReleaseState);
        case SYM_GEN_PARAM_DELIMITER_1710: return gd::GdVal::from_str(&battle_string_literals[49]);
        default: break;
    }
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreItemData::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreItemData::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_name_7: out = this->f_name; return true;
        case SYM_GEN_identifier_1673: out = this->f_identifier; return true;
        case SYM_GEN_itemIndex_1674: out = this->f_itemIndex; return true;
        case SYM_GEN_minDam_1675: out = this->f_minDam; return true;
        case SYM_GEN_maxDam_1676: out = this->f_maxDam; return true;
        case SYM_GEN_staminaCost_1677: out = this->f_staminaCost; return true;
        case SYM_GEN_block_1678: out = this->f_block; return true;
        case SYM_GEN_cd_1679: out = this->f_cd; return true;
        case SYM_GEN_extraCds_1680: out = this->f_extraCds; return true;
        case SYM_GEN_accuracy_1545: out = this->f_accuracy; return true;
        case SYM_GEN_canActivate_91: out = this->f_canActivate; return true;
        case SYM_GEN_chance_1681: out = this->f_chance; return true;
        case SYM_GEN_chance2_1682: out = this->f_chance2; return true;
        case SYM_GEN_shopChance_1683: out = this->f_shopChance; return true;
        case SYM_GEN_types_1544: out = this->f_types; return true;
        case SYM_GEN_tags_1684: out = this->f_tags; return true;
        case SYM_GEN_physics_1685: out = this->f_physics; return true;
        case SYM_GEN_rarity_1686: out = this->f_rarity; return true;
        case SYM_GEN_price_1687: out = this->f_price; return true;
        case SYM_GEN_classes_1688: out = this->f_classes; return true;
        case SYM_GEN_randomUniquePool_1689: out = this->f_randomUniquePool; return true;
        case SYM_GEN_hasBattleRageEffect_1690: out = this->f_hasBattleRageEffect; return true;
        case SYM_GEN_gatedItems_1691: out = this->f_gatedItems; return true;
        case SYM_GEN_startsSubclass_1692: out = this->f_startsSubclass; return true;
        case SYM_GEN_gateItem_1693: out = this->f_gateItem; return true;
        case SYM_GEN_originatingRecipes_1694: out = this->f_originatingRecipes; return true;
        case SYM_GEN_animationScene_1695: out = this->f_animationScene; return true;
        case SYM_GEN_flickerAni_1696: out = this->f_flickerAni; return true;
        case SYM_GEN_flickerMinDist_1697: out = this->f_flickerMinDist; return true;
        case SYM_GEN_flickerMaxDist_1698: out = this->f_flickerMaxDist; return true;
        case SYM_GEN_flickerMinSpeed_1699: out = this->f_flickerMinSpeed; return true;
        case SYM_GEN_flickerMaxSpeed_1700: out = this->f_flickerMaxSpeed; return true;
        case SYM_GEN_connectorReadyRoll_1701: out = this->f_connectorReadyRoll; return true;
        case SYM_GEN_gemRoll_1702: out = this->f_gemRoll; return true;
        case SYM_GEN_sceneDepth_1703: out = this->f_sceneDepth; return true;
        case SYM_GEN_releaseState_1704: out = this->f_releaseState; return true;
        case SYM_GEN__editor_1705: out = this->f__editor; return true;
        case SYM_GEN__playtest_1706: out = this->f__playtest; return true;
        case SYM_GEN__full_version_1707: out = this->f__full_version; return true;
        case SYM_GEN__engineer_test_1708: out = this->f__engineer_test; return true;
        case SYM_GEN_params_1570: out = this->f_params; return true;
        case SYM_GEN_namedParams_1709: out = this->f_namedParams; return true;
        case SYM_GEN_sortedParamNames_1711: out = this->f_sortedParamNames; return true;
        case SYM_GEN_paramBases_1712: out = this->f_paramBases; return true;
        case SYM_GEN_paramBases_inverted_1713: out = this->f_paramBases_inverted; return true;
        case SYM_GEN_gainedStacks_1714: out = this->f_gainedStacks; return true;
        case SYM_GEN_removedStacks_1715: out = this->f_removedStacks; return true;
        case SYM_GEN_usedStacks_1716: out = this->f_usedStacks; return true;
        case SYM_GEN_activationAni_1717: out = this->f_activationAni; return true;
        case SYM_GEN_ReleaseState_1727: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreItemData_ReleaseState); return true;
        case SYM_GEN_PARAM_DELIMITER_1710: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItemData::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_name_7: this->f_name = val; return true;
        case SYM_GEN_identifier_1673: this->f_identifier = val; return true;
        case SYM_GEN_itemIndex_1674: this->f_itemIndex = gd::gd_coerce_int(val); return true;
        case SYM_GEN_minDam_1675: this->f_minDam = gd::gd_coerce_int(val); return true;
        case SYM_GEN_maxDam_1676: this->f_maxDam = gd::gd_coerce_int(val); return true;
        case SYM_GEN_staminaCost_1677: this->f_staminaCost = gd::gd_coerce_float(val); return true;
        case SYM_GEN_block_1678: this->f_block = gd::gd_coerce_int(val); return true;
        case SYM_GEN_cd_1679: this->f_cd = gd::gd_coerce_float(val); return true;
        case SYM_GEN_extraCds_1680: this->f_extraCds = val; return true;
        case SYM_GEN_accuracy_1545: this->f_accuracy = gd::gd_coerce_float(val); return true;
        case SYM_GEN_canActivate_91: this->f_canActivate = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_chance_1681: this->f_chance = gd::gd_coerce_float(val); return true;
        case SYM_GEN_chance2_1682: this->f_chance2 = gd::gd_coerce_float(val); return true;
        case SYM_GEN_shopChance_1683: this->f_shopChance = gd::gd_coerce_float(val); return true;
        case SYM_GEN_types_1544: this->f_types = val; return true;
        case SYM_GEN_tags_1684: this->f_tags = gd::gd_coerce_int(val); return true;
        case SYM_GEN_physics_1685: this->f_physics = gd::gd_coerce_int(val); return true;
        case SYM_GEN_rarity_1686: this->f_rarity = gd::gd_coerce_int(val); return true;
        case SYM_GEN_price_1687: this->f_price = gd::gd_coerce_int(val); return true;
        case SYM_GEN_classes_1688: this->f_classes = gd::gd_coerce_int(val); return true;
        case SYM_GEN_randomUniquePool_1689: this->f_randomUniquePool = val; return true;
        case SYM_GEN_hasBattleRageEffect_1690: this->f_hasBattleRageEffect = val; return true;
        case SYM_GEN_gatedItems_1691: this->f_gatedItems = val; return true;
        case SYM_GEN_startsSubclass_1692: this->f_startsSubclass = val; return true;
        case SYM_GEN_gateItem_1693: this->f_gateItem = val; return true;
        case SYM_GEN_originatingRecipes_1694: this->f_originatingRecipes = val; return true;
        case SYM_GEN_animationScene_1695: this->f_animationScene = val; return true;
        case SYM_GEN_flickerAni_1696: this->f_flickerAni = val; return true;
        case SYM_GEN_flickerMinDist_1697: this->f_flickerMinDist = val; return true;
        case SYM_GEN_flickerMaxDist_1698: this->f_flickerMaxDist = val; return true;
        case SYM_GEN_flickerMinSpeed_1699: this->f_flickerMinSpeed = val; return true;
        case SYM_GEN_flickerMaxSpeed_1700: this->f_flickerMaxSpeed = val; return true;
        case SYM_GEN_connectorReadyRoll_1701: this->f_connectorReadyRoll = val; return true;
        case SYM_GEN_gemRoll_1702: this->f_gemRoll = val; return true;
        case SYM_GEN_sceneDepth_1703: this->f_sceneDepth = val; return true;
        case SYM_GEN_releaseState_1704: this->f_releaseState = gd::gd_coerce_int(val); return true;
        case SYM_GEN__editor_1705: this->f__editor = val; return true;
        case SYM_GEN__playtest_1706: this->f__playtest = val; return true;
        case SYM_GEN__full_version_1707: this->f__full_version = val; return true;
        case SYM_GEN__engineer_test_1708: this->f__engineer_test = val; return true;
        case SYM_GEN_params_1570: this->f_params = val; return true;
        case SYM_GEN_namedParams_1709: this->f_namedParams = val; return true;
        case SYM_GEN_sortedParamNames_1711: this->f_sortedParamNames = val; return true;
        case SYM_GEN_paramBases_1712: this->f_paramBases = val; return true;
        case SYM_GEN_paramBases_inverted_1713: this->f_paramBases_inverted = val; return true;
        case SYM_GEN_gainedStacks_1714: this->f_gainedStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_removedStacks_1715: this->f_removedStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_usedStacks_1716: this->f_usedStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activationAni_1717: this->f_activationAni = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItemData::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getP_188: return true;
        case SYM_GEN_hasParam_1578: return true;
        case SYM_GEN_addNamedParam_1718: return true;
        case SYM_GEN_hasTag_81: return true;
        case SYM_GEN_isWeapon_82: return true;
        case SYM_GEN_getIndex_235: return true;
        case SYM_GEN_getName_234: return true;
        case SYM_GEN_getRarity_236: return true;
        case SYM_GEN_getShopChance_237: return true;
        case SYM_GEN_getTypes_240: return true;
        case SYM_GEN_isAvailableFor_1719: return true;
        case SYM_GEN_isNeutral_246: return true;
        case SYM_GEN_isClassItem_248: return true;
        case SYM_GEN_isSubclassItem_249: return true;
        case SYM_GEN_isCraftedItem_1720: return true;
        case SYM_GEN_isGatedItem_1721: return true;
        case SYM_GEN_isMeleeWeapon_1722: return true;
        case SYM_GEN_isRangedWeapon_1723: return true;
        case SYM_GEN_isStartingWeapon_1724: return true;
        case SYM_GEN_isReleased_1725: return true;
        case SYM_GEN_getPrice_392: return true;
        case SYM_GEN_getSellPrice_394: return true;
        case SYM_GEN_getSalePrice_395: return true;
        case SYM_GEN_getTranslatedName_641: return true;
        case SYM_GEN_fromDict_1726: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItemData::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getP_188: out = fn_getP(args, argc); return true;
        case SYM_GEN_hasParam_1578: out = fn_hasParam(args, argc); return true;
        case SYM_GEN_addNamedParam_1718: out = fn_addNamedParam(args, argc); return true;
        case SYM_GEN_hasTag_81: out = fn_hasTag(args, argc); return true;
        case SYM_GEN_isWeapon_82: out = fn_isWeapon(args, argc); return true;
        case SYM_GEN_getIndex_235: out = fn_getIndex(args, argc); return true;
        case SYM_GEN_getName_234: out = fn_getName(args, argc); return true;
        case SYM_GEN_getRarity_236: out = fn_getRarity(args, argc); return true;
        case SYM_GEN_getShopChance_237: out = fn_getShopChance(args, argc); return true;
        case SYM_GEN_getTypes_240: out = fn_getTypes(args, argc); return true;
        case SYM_GEN_isAvailableFor_1719: out = fn_isAvailableFor(args, argc); return true;
        case SYM_GEN_isNeutral_246: out = fn_isNeutral(args, argc); return true;
        case SYM_GEN_isClassItem_248: out = fn_isClassItem(args, argc); return true;
        case SYM_GEN_isSubclassItem_249: out = fn_isSubclassItem(args, argc); return true;
        case SYM_GEN_isCraftedItem_1720: out = fn_isCraftedItem(args, argc); return true;
        case SYM_GEN_isGatedItem_1721: out = fn_isGatedItem(args, argc); return true;
        case SYM_GEN_isMeleeWeapon_1722: out = fn_isMeleeWeapon(args, argc); return true;
        case SYM_GEN_isRangedWeapon_1723: out = fn_isRangedWeapon(args, argc); return true;
        case SYM_GEN_isStartingWeapon_1724: out = fn_isStartingWeapon(args, argc); return true;
        case SYM_GEN_isReleased_1725: out = fn_isReleased(args, argc); return true;
        case SYM_GEN_getPrice_392: out = fn_getPrice(args, argc); return true;
        case SYM_GEN_getSellPrice_394: out = fn_getSellPrice(args, argc); return true;
        case SYM_GEN_getSalePrice_395: out = fn_getSalePrice(args, argc); return true;
        case SYM_GEN_getTranslatedName_641: out = fn_getTranslatedName(args, argc); return true;
        case SYM_GEN_fromDict_1726: out = fn_fromDict(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItemData::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core__CoreItemData::fn_getP(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_index = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_builtin(lv_index, 4)))) {
        return ([&]() { gd::GdVal _ca[] = {lv_index, gd::GdVal::from_float(0.0)}; return gd::call_method(gd_ctx, this->f_namedParams, gd::SYM_get, _ca, 2); })();
    }
    return gd::get_index(gd_ctx, this->f_params, lv_index);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_hasParam(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_paramName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::gd_in(lv_paramName, this->f_paramBases_inverted);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_addNamedParam(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_paramName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_paramVal = (_argc > 1) ? _args[1] : gd::GdVal::null();
    { gd::GdVal _t629 = this->f_namedParams; gd::GdVal _t630 = lv_paramName; gd::set_index(gd_ctx, _t629, _t630, lv_paramVal); }
    gd::GdVal lv_sortedPos = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t631 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_sortedParamNames, gd::SYM_size, nullptr, 0));
        gd::GdArr* _t632 = (_t631.kind == gd::GdVal::Kind::Arr) ? _t631.arr : nullptr;
        uint32_t _len__t633 = _t632 ? _t632->len : 0u;
        for (uint32_t _t633 = 0; _t633 < _len__t633; ++_t633) {
            gd::GdVal lv_i = _t632->data[_t633];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_paramName}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_sortedParamNames, lv_i), gd::SYM_begins_with, _ca, 1); })())) {
                lv_sortedPos = gd::gd_add(gd_ctx, lv_i, gd::GdVal::from_int(1LL));
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_sortedPos, lv_paramName}; return gd::call_method(gd_ctx, this->f_sortedParamNames, gd::SYM_insert, _ca, 2); })();
    { gd::GdVal _t634 = this->f_paramBases; gd::GdVal _t635 = lv_paramName; gd::set_index(gd_ctx, _t634, _t635, ([&]() { gd::GdVal _ca[] = {Gd__gd_core__CoreItemData::get_static_const_or_enum(gd_ctx, SYM_GEN_PARAM_DELIMITER_1710), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_paramName, gd::SYM_get_slice, _ca, 2); })()); }
    { gd::GdVal _t636 = this->f_paramBases_inverted; gd::GdVal _t637 = gd::get_index(gd_ctx, this->f_paramBases, lv_paramName); gd::set_index(gd_ctx, _t636, _t637, lv_paramName); }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_hasTag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_tag = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::gd_bitand(this->f_tags, lv_tag);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_isWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_in(gd::GdVal::from_int(4LL), this->f_types);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_getIndex(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_itemIndex;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_getName(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_identifier;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_getRarity(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_rarity;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_getShopChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_shopChance;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_getTypes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_types;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_isAvailableFor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_classId = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_classId = gd::gd_coerce_int(lv_classId);
    return gd::GdVal::from_bool(gd::gd_ne(gd::gd_bitand(this->f_classes, gd::gd_shl(gd::GdVal::from_int(1LL), lv_classId)), gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_isNeutral(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_eq(this->f_classes, gd::GdVal::from_int(127LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_isClassItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_classes, gd::GdVal::from_int(127LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_classes, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_isSubclassItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_ne(this->f_startsSubclass, gd::GdVal::from_str(&battle_string_literals[8])));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_isCraftedItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, this->f_originatingRecipes, gd::SYM_empty, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_isGatedItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_ne(this->f_gateItem, gd::GdVal::null()));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_isMeleeWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::gd_in(gd::GdVal::from_int(19LL), this->f_types)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isWeapon_82, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_isRangedWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::gd_in(gd::GdVal::from_int(20LL), this->f_types)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isWeapon_82, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_isStartingWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isWeapon_82, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_identifier, gd::GdVal::from_str(&battle_string_literals[50]))))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_isReleased(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_releaseState, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_bool(true);
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_releaseState, gd::GdVal::from_int(1LL))))) {
        return (gd::gd_truth((gd::gd_truth(this->f__playtest) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(this->f__full_version)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(this->f__editor)));
    }
    else {
        return (gd::gd_truth(this->f__full_version) ? gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth((gd::gd_truth(this->f__editor) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(this->f__playtest)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(this->f__engineer_test))))) : gd::GdVal::from_bool(false));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_getPrice(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_price;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_getSellPrice(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_ceil(gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getPrice_392, nullptr, 0), gd::GdVal::from_float(0.5)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_getSalePrice(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_ceil(gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getPrice_392, nullptr, 0), gd::GdVal::from_float(0.5)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_getTranslatedName(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_name;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_fromDict(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_d = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_o = gd::GdVal::from_obj(this);
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_name_7, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[51]), gd::GdVal::from_str(&battle_string_literals[8])}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_identifier_1673, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[52]), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[51]), gd::GdVal::from_str(&battle_string_literals[8])}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_itemIndex_1674, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[53]), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_minDam_1675, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[54]), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_maxDam_1676, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[55]), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_staminaCost_1677, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[56]), gd::GdVal::from_float(0.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_block_1678, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[57]), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_cd_1679, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[58]), gd::GdVal::from_float(0.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_extraCds_1680, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[59]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_accuracy_1545, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[60]), gd::GdVal::from_float(100.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_canActivate_91, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[61]), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1389, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_chance_1681, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[62]), gd::GdVal::from_float(0.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_chance2_1682, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[63]), gd::GdVal::from_float(0.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_shopChance_1683, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[64]), gd::GdVal::from_float(0.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_types_1544, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[65]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_tags_1684, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[66]), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_physics_1685, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[67]), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_rarity_1686, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[68]), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_price_1687, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[69]), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_classes_1688, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[70]), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_randomUniquePool_1689, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[71]), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1389, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_hasBattleRageEffect_1690, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[72]), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1389, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_gatedItems_1691, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[73]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_startsSubclass_1692, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[74]), gd::GdVal::from_str(&battle_string_literals[8])}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_gateItem_1693, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[75]), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[76]), gd::GdVal::null()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_originatingRecipes_1694, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[77]), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[78]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_animationScene_1695, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[79]), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1389, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_flickerAni_1696, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[80]), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[81]), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1389, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_flickerMinDist_1697, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[82]), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[83]), gd::GdVal::from_float(0.1)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_flickerMaxDist_1698, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[84]), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[85]), gd::GdVal::from_float(3.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_flickerMinSpeed_1699, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[86]), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[87]), gd::GdVal::from_float(0.3)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_flickerMaxSpeed_1700, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[88]), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[89]), gd::GdVal::from_float(1.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_connectorReadyRoll_1701, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[90]), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[91]), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1389, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_gemRoll_1702, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[92]), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[93]), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1389, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_sceneDepth_1703, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[94]), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[95]), gd::GdVal::from_int(2LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_releaseState_1704, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[96]), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[97]), gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_params_1570, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[98]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })());
    gd::GdVal lv_np = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[99]), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[100]), gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })();
    {
        gd::GdVal _t638 = gd::gd_iter_seq(gd_ctx.arena, lv_np);
        gd::GdArr* _t639 = (_t638.kind == gd::GdVal::Kind::Arr) ? _t638.arr : nullptr;
        uint32_t _len__t640 = _t639 ? _t639->len : 0u;
        for (uint32_t _t640 = 0; _t640 < _len__t640; ++_t640) {
            gd::GdVal lv_k = _t639->data[_t640];
            (void)([&]() { gd::GdVal _ca[] = {lv_k, gd::get_index(gd_ctx, lv_np, lv_k)}; return gd::call_method(gd_ctx, lv_o, SYM_GEN_addNamedParam_1718, _ca, 2); })();
        }
    }
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_gainedStacks_1714, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[101]), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_removedStacks_1715, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[102]), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_usedStacks_1716, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[103]), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    return lv_o;
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreItemData(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreItemData>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__CoreItemData = {CLS_Gd__gd_core__CoreItemData, "CoreItemData", "res://gd_core/CoreItemData.gd", nullptr, false, _alloc_Gd__gd_core__CoreItemData, &Gd__gd_core__CoreItemData::get_static_prop_fn, &Gd__gd_core__CoreItemData::call_static_fn};

void Gd__gd_core__Darksaber::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
    this->f_damPerDebuff = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__Darksaber::meta() const { return &META_Gd__gd_core__Darksaber; }
gd::GdVal Gd__gd_core__Darksaber::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Darksaber::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Darksaber::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_damPerDebuff_1827: out = this->f_damPerDebuff; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__Darksaber::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damPerDebuff_1827: this->f_damPerDebuff = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Darksaber::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onDebuffsChanged_1828: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Darksaber::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDebuffsChanged_1828: out = fn_onDebuffsChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Darksaber::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Darksaber::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[104])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToOpponentDebuffs_376, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Darksaber::fn_onDebuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, this->f_damPerDebuff)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_162, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Darksaber::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_333, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_event, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_213, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Darksaber::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_damPerDebuff = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Darksaber(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Darksaber>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Darksaber = {CLS_Gd__gd_core__Darksaber, "Darksaber", "res://gd_core/Darksaber.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__Darksaber, &Gd__gd_core__Darksaber::get_static_prop_fn, &Gd__gd_core__Darksaber::call_static_fn};

void Gd__gd_core__FlyAgaric::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Food::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__FlyAgaric::meta() const { return &META_Gd__gd_core__FlyAgaric; }
gd::GdVal Gd__gd_core__FlyAgaric::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__FlyAgaric::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__FlyAgaric::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Food::get_prop(prop, out);
}
bool Gd__gd_core__FlyAgaric::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__FlyAgaric::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Food::has_own_method(m);
}
bool Gd__gd_core__FlyAgaric::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__FlyAgaric::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__FlyAgaric::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__FlyAgaric::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__FlyAgaric(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__FlyAgaric>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__FlyAgaric = {CLS_Gd__gd_core__FlyAgaric, "FlyAgaric", "res://gd_core/FlyAgaric.gd", &META_Gd__gd_core__Food, false, _alloc_Gd__gd_core__FlyAgaric, &Gd__gd_core__FlyAgaric::get_static_prop_fn, &Gd__gd_core__FlyAgaric::call_static_fn};

void Gd__gd_core__HungryBlade::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
    this->f_vampirism = gd::GdVal::null();
    this->f_regenNeeded = gd::GdVal::null();
    this->f_vampirismForRegen = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__HungryBlade::meta() const { return &META_Gd__gd_core__HungryBlade; }
gd::GdVal Gd__gd_core__HungryBlade::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__HungryBlade::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__HungryBlade::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_vampirism_940: out = this->f_vampirism; return true;
        case SYM_GEN_regenNeeded_942: out = this->f_regenNeeded; return true;
        case SYM_GEN_vampirismForRegen_1903: out = this->f_vampirismForRegen; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__HungryBlade::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_vampirism_940: this->f_vampirism = val; return true;
        case SYM_GEN_regenNeeded_942: this->f_regenNeeded = val; return true;
        case SYM_GEN_vampirismForRegen_1903: this->f_vampirismForRegen = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__HungryBlade::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onVampirismChanged_943: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__HungryBlade::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onVampirismChanged_943: out = fn_onVampirismChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__HungryBlade::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__HungryBlade::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[4]), gd::GdVal::from_str(&battle_string_literals[5])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HungryBlade::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_vampirism}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false), gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, Gd__gd_core__HungryBlade::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Jump_2736)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HungryBlade::fn_onVampirismChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addMaxDamage_164, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HungryBlade::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        gd::GdVal lv_numRegen = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRegeneration_1233, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_numRegen, this->f_regenNeeded)))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_regenNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_346, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_vampirismForRegen, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HungryBlade::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_vampirism = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    this->f_regenNeeded = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    this->f_vampirismForRegen = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__HungryBlade(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__HungryBlade>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__HungryBlade = {CLS_Gd__gd_core__HungryBlade, "HungryBlade", "res://gd_core/HungryBlade.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__HungryBlade, &Gd__gd_core__HungryBlade::get_static_prop_fn, &Gd__gd_core__HungryBlade::call_static_fn};

void Gd__gd_core__Manathirst::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
    this->f_manaGained = gd::GdVal::from_int(0);
    this->f_fillingTween = gd::GdVal::null();
    this->f_filling = gd::GdVal::null();
    this->f_fillingGlow = gd::GdVal::null();
    this->f_fillingHeight = gd::GdVal::null();
    this->f_fillingAnimation = gd::GdVal::null();
    this->f_manaNeededForLifesteal = gd::GdVal::null();
    this->f_dam = gd::GdVal::null();
    this->f_mana = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__Manathirst::meta() const { return &META_Gd__gd_core__Manathirst; }
gd::GdVal Gd__gd_core__Manathirst::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Manathirst::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Manathirst::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_manaGained_1931: out = this->f_manaGained; return true;
        case SYM_GEN_fillingTween_1932: out = this->f_fillingTween; return true;
        case SYM_GEN_filling_1933: out = this->f_filling; return true;
        case SYM_GEN_fillingGlow_1934: out = this->f_fillingGlow; return true;
        case SYM_GEN_fillingHeight_1935: out = this->f_fillingHeight; return true;
        case SYM_GEN_fillingAnimation_1936: out = this->f_fillingAnimation; return true;
        case SYM_GEN_manaNeededForLifesteal_1937: out = this->f_manaNeededForLifesteal; return true;
        case SYM_GEN_dam_939: out = this->f_dam; return true;
        case SYM_GEN_mana_1928: out = this->f_mana; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__Manathirst::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaGained_1931: this->f_manaGained = gd::gd_coerce_int(val); return true;
        case SYM_GEN_fillingTween_1932: this->f_fillingTween = val; return true;
        case SYM_GEN_filling_1933: this->f_filling = val; return true;
        case SYM_GEN_fillingGlow_1934: this->f_fillingGlow = val; return true;
        case SYM_GEN_fillingHeight_1935: this->f_fillingHeight = val; return true;
        case SYM_GEN_fillingAnimation_1936: this->f_fillingAnimation = val; return true;
        case SYM_GEN_manaNeededForLifesteal_1937: this->f_manaNeededForLifesteal = val; return true;
        case SYM_GEN_dam_939: this->f_dam = val; return true;
        case SYM_GEN_mana_1928: this->f_mana = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Manathirst::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_tweenFilling_1938: return true;
        case SYM_GEN_onManaChanged_1929: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Manathirst::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_tweenFilling_1938: out = fn_tweenFilling(args, argc); return true;
        case SYM_GEN_onManaChanged_1929: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Manathirst::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Manathirst::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_manaGained = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[105]), gd::GdVal::from_str(&battle_string_literals[106])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tweenFilling_1938, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Manathirst::fn_tweenFilling(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_relHeight = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_relHeight = gd::gd_coerce_float(lv_relHeight);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Manathirst::fn_onManaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        this->f_manaGained = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_manaGained, lv_amount));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_manaGained, this->f_manaNeededForLifesteal)))) {
            this->f_manaGained = gd::gd_coerce_int(gd::gd_sub(this->f_manaGained, this->f_manaNeededForLifesteal));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_dam, gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getVampirism_1226, nullptr, 0)), gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[107])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::GdVal::from_float(100.0)), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealLife_329, _ca, 3); })();
        }
        gd::GdVal lv_relHeight = gd::gd_div(gd_ctx, this->f_manaGained, this->f_manaNeededForLifesteal);
        (void)([&]() { gd::GdVal _ca[] = {lv_relHeight}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tweenFilling_1938, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Manathirst::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_mana, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Manathirst::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tweenFilling_1938, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Manathirst::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_manaNeededForLifesteal = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0);
    this->f_dam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[108])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[109])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Manathirst(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Manathirst>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Manathirst = {CLS_Gd__gd_core__Manathirst, "Manathirst", "res://gd_core/Manathirst.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__Manathirst, &Gd__gd_core__Manathirst::get_static_prop_fn, &Gd__gd_core__Manathirst::call_static_fn};

void Gd__gd_core__PotionBelt::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Bag::init_fields(gd_ctx);
    this->f_affectedPotions = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_numConsumed = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core__PotionBelt::meta() const { return &META_Gd__gd_core__PotionBelt; }
gd::GdVal Gd__gd_core__PotionBelt::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__PotionBelt::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__PotionBelt::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_affectedPotions_1965: out = this->f_affectedPotions; return true;
        case SYM_GEN_numConsumed_1966: out = this->f_numConsumed; return true;
        default: break;
    }
    return Gd__gd_core__Bag::get_prop(prop, out);
}
bool Gd__gd_core__PotionBelt::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedPotions_1965: this->f_affectedPotions = val; return true;
        case SYM_GEN_numConsumed_1966: this->f_numConsumed = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__PotionBelt::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPotionEmptied_1967: return true;
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Bag::has_own_method(m);
}
bool Gd__gd_core__PotionBelt::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPotionEmptied_1967: out = fn_onPotionEmptied(args, argc); return true;
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__PotionBelt::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__PotionBelt::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_numConsumed = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)gd::call_method(gd_ctx, this->f_affectedPotions, gd::SYM_clear, nullptr, 0);
    gd::GdVal lv_affectedItems = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0);
    {
        gd::GdVal _t641 = gd::gd_iter_seq(gd_ctx.arena, lv_affectedItems);
        gd::GdArr* _t642 = (_t641.kind == gd::GdVal::Kind::Arr) ? _t641.arr : nullptr;
        uint32_t _len__t643 = _t642 ? _t642->len : 0u;
        for (uint32_t _t643 = 0; _t643 < _len__t643; ++_t643) {
            gd::GdVal lv_item = _t642->data[_t643];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_920, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, this->f_affectedPotions, gd::SYM_push_back, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[110]), gd::GdVal::from_str(&battle_string_literals[111])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PotionBelt::fn_onPotionEmptied(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__potion = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_numBuffs = gd::GdVal::from_int(0LL);
    gd::GdVal lv_active = gd::GdVal::from_bool(false);
    this->f_numConsumed = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numConsumed, gd::GdVal::from_int(1LL)));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_numConsumed, gd::GdVal::from_int(1LL))))) {
        lv_numBuffs = gd::GdVal::from_int(1LL);
        lv_active = gd::GdVal::from_bool(true);
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_numConsumed, gd::GdVal::from_int(4LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_356, _ca, 1); })();
        lv_active = gd::GdVal::from_bool(true);
    }
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[112])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isTypeInInventory_805, _ca, 1); })())) {
        lv_numBuffs = gd::gd_add(gd_ctx, lv_numBuffs, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[113])}; return gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[112])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })(), SYM_GEN_getP_188, _ca, 1); })()));
        lv_active = gd::GdVal::from_bool(true);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numBuffs, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_numBuffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 1); })();
    }
    if (gd::gd_truth(lv_active)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PotionBelt::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(11LL)}; return gd::call_method(gd_ctx, lv_toItem, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PotionBelt::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bag::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__PotionBelt(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__PotionBelt>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__PotionBelt = {CLS_Gd__gd_core__PotionBelt, "PotionBelt", "res://gd_core/PotionBelt.gd", &META_Gd__gd_core__Bag, false, _alloc_Gd__gd_core__PotionBelt, &Gd__gd_core__PotionBelt::get_static_prop_fn, &Gd__gd_core__PotionBelt::call_static_fn};

void Gd__gd_core__StaffofUnhealing::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_buffActive = gd::GdVal::from_bool(false);
    this->f_activationParticles = gd::GdVal::null();
    this->f_unhealingTimer = gd::GdVal::null();
    this->f_manaCost = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__StaffofUnhealing::meta() const { return &META_Gd__gd_core__StaffofUnhealing; }
gd::GdVal Gd__gd_core__StaffofUnhealing::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__StaffofUnhealing::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__StaffofUnhealing::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_buffActive_1813: out = this->f_buffActive; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_unhealingTimer_1984: out = this->f_unhealingTimer; return true;
        case SYM_GEN_manaCost_1815: out = this->f_manaCost; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__StaffofUnhealing::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffActive_1813: this->f_buffActive = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_unhealingTimer_1984: this->f_unhealingTimer = val; return true;
        case SYM_GEN_manaCost_1815: this->f_manaCost = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__StaffofUnhealing::has_own_method(gd::SymId m) const {
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
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__StaffofUnhealing::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
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
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__StaffofUnhealing::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__StaffofUnhealing::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StaffofUnhealing::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_healAmount = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[114])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_manaCost)))) {
            if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_buffActive)))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_giveUnhealing_1178, _ca, 1); })();
            }
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[115])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_unhealingTimer, SYM_GEN_start_1779, _ca, 1); })();
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_healAmount, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 2); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {lv_healAmount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 1); })();
        }
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StaffofUnhealing::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_reduceUnhealing_1179, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StaffofUnhealing::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_unhealingTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StaffofUnhealing::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StaffofUnhealing::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv_active)) {
    }
    else {
    }
    this->f_buffActive = lv_active;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StaffofUnhealing::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_unhealingTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[116]), gd::GdVal::from_str(&battle_string_literals[117]), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_manaCost = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__StaffofUnhealing(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__StaffofUnhealing>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__StaffofUnhealing = {CLS_Gd__gd_core__StaffofUnhealing, "StaffofUnhealing", "res://gd_core/StaffofUnhealing.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__StaffofUnhealing, &Gd__gd_core__StaffofUnhealing::get_static_prop_fn, &Gd__gd_core__StaffofUnhealing::call_static_fn};

void Gd__gd_core__TheFool::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Card::init_fields(gd_ctx);
    this->f_activationParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__TheFool::meta() const { return &META_Gd__gd_core__TheFool; }
gd::GdVal Gd__gd_core__TheFool::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Card::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__TheFool::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__TheFool::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core__Card::get_prop(prop, out);
}
bool Gd__gd_core__TheFool::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__TheFool::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_890: return true;
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Card::has_own_method(m);
}
bool Gd__gd_core__TheFool::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_890: out = fn_cardSecondaryEffectActive(args, argc); return true;
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__TheFool::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__TheFool::fn_cardSecondaryEffectActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_eq(this->f_chainPosition, gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__TheFool::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bonusSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[118])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    {
        gd::GdVal _t644 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_deck, SYM_GEN_cards_1832));
        gd::GdArr* _t645 = (_t644.kind == gd::GdVal::Kind::Arr) ? _t644.arr : nullptr;
        uint32_t _len__t646 = _t645 ? _t645->len : 0u;
        for (uint32_t _t646 = 0; _t646 < _len__t646; ++_t646) {
            gd::GdVal lv_card = _t645->data[_t646];
            (void)([&]() { gd::GdVal _ca[] = {lv_bonusSpeed}; return gd::call_method(gd_ctx, lv_card, SYM_GEN_addSpeed_273, _ca, 1); })();
        }
    }
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cardSecondaryEffectActive_890, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[119])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__TheFool::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Card::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__TheFool(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__TheFool>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__TheFool = {CLS_Gd__gd_core__TheFool, "TheFool", "res://gd_core/TheFool.gd", &META_Gd__gd_core__Card, false, _alloc_Gd__gd_core__TheFool, &Gd__gd_core__TheFool::get_static_prop_fn, &Gd__gd_core__TheFool::call_static_fn};

void Gd__gd_core_items__Card::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_back = gd::GdVal::null();
    this->f_activeFront = gd::GdVal::null();
    this->f_curActivationDelay = gd::GdVal::from_float(0.0);
    this->f_faceUp = gd::GdVal::from_bool(true);
    this->f_activating = gd::GdVal::from_bool(false);
    this->f_chainPosition = gd::gd_neg(gd::GdVal::from_int(1LL));
    this->f_deck = gd::GdVal::null();
    this->f_cardAnimation = gd::GdVal::null();
    this->f_front = gd::GdVal::null();
    this->f_connector = gd::GdVal::null();
    this->f_notInChainMark = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Card::meta() const { return &META_Gd__gd_core_items__Card; }
gd::GdVal Gd__gd_core_items__Card::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Card::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Card::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case gd::SYM_back: out = this->f_back; return true;
        case SYM_GEN_activeFront_878: out = this->f_activeFront; return true;
        case SYM_GEN_curActivationDelay_879: out = this->f_curActivationDelay; return true;
        case SYM_GEN_faceUp_880: out = this->f_faceUp; return true;
        case SYM_GEN_activating_881: out = this->f_activating; return true;
        case SYM_GEN_chainPosition_882: out = this->f_chainPosition; return true;
        case SYM_GEN_deck_883: out = this->f_deck; return true;
        case SYM_GEN_cardAnimation_884: out = this->f_cardAnimation; return true;
        case gd::SYM_front: out = this->f_front; return true;
        case SYM_GEN_connector_885: out = this->f_connector; return true;
        case SYM_GEN_notInChainMark_886: out = this->f_notInChainMark; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Card::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case gd::SYM_back: this->f_back = val; return true;
        case SYM_GEN_activeFront_878: this->f_activeFront = val; return true;
        case SYM_GEN_curActivationDelay_879: this->f_curActivationDelay = gd::gd_coerce_float(val); return true;
        case SYM_GEN_faceUp_880: this->f_faceUp = val; return true;
        case SYM_GEN_activating_881: this->f_activating = val; return true;
        case SYM_GEN_chainPosition_882: this->f_chainPosition = val; return true;
        case SYM_GEN_deck_883: this->f_deck = val; return true;
        case SYM_GEN_cardAnimation_884: this->f_cardAnimation = val; return true;
        case gd::SYM_front: this->f_front = val; return true;
        case SYM_GEN_connector_885: this->f_connector = val; return true;
        case SYM_GEN_notInChainMark_886: this->f_notInChainMark = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Card::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_setFaceUp_887: return true;
        case SYM_GEN_setFaceDown_888: return true;
        case SYM_GEN_updateTexture_889: return true;
        case SYM_GEN_cardSecondaryEffectActive_890: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_prepare_122: return true;
        case SYM_GEN_preCombatStart_124: return true;
        case SYM_GEN_getNextCard_891: return true;
        case SYM_GEN_startActivation_892: return true;
        case SYM_GEN_playActivationAnimation_778: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN_trigger_143: return true;
        case SYM_GEN_combatEnd_131: return true;
        case SYM_GEN_shopEntered_745: return true;
        case SYM_GEN_addToInventory_120: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_notifyChainPosition_894: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_getCardDescription_895: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Card::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_setFaceUp_887: out = fn_setFaceUp(args, argc); return true;
        case SYM_GEN_setFaceDown_888: out = fn_setFaceDown(args, argc); return true;
        case SYM_GEN_updateTexture_889: out = fn_updateTexture(args, argc); return true;
        case SYM_GEN_cardSecondaryEffectActive_890: out = fn_cardSecondaryEffectActive(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_prepare_122: out = fn_prepare(args, argc); return true;
        case SYM_GEN_preCombatStart_124: out = fn_preCombatStart(args, argc); return true;
        case SYM_GEN_getNextCard_891: out = fn_getNextCard(args, argc); return true;
        case SYM_GEN_startActivation_892: out = fn_startActivation(args, argc); return true;
        case SYM_GEN_playActivationAnimation_778: out = fn_playActivationAnimation(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN_trigger_143: out = fn_trigger(args, argc); return true;
        case SYM_GEN_combatEnd_131: out = fn_combatEnd(args, argc); return true;
        case SYM_GEN_shopEntered_745: out = fn_shopEntered(args, argc); return true;
        case SYM_GEN_addToInventory_120: out = fn_addToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_notifyChainPosition_894: out = fn_notifyChainPosition(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_getCardDescription_895: out = fn_getCardDescription(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Card::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Card::fn_setFaceUp(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_faceUp)))) {
        this->f_faceUp = gd::GdVal::from_bool(true);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_setFaceDown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_faceUp)) {
        this->f_faceUp = gd::GdVal::from_bool(false);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_updateTexture(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_faceUp)) {
        if (gd::gd_truth((gd::gd_truth((gd::gd_truth(this->f_deck) ? gd::GdVal::from_bool(gd::gd_truth(this->f_activeFront)) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cardSecondaryEffectActive_890, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        }
        else {
        }
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_cardSecondaryEffectActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(this->f_placed)) {
        return (gd::gd_truth((gd::gd_truth(this->f_deck) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(12LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, lv_item, SYM_GEN_chainPosition_882), this->f_chainPosition))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_item, SYM_GEN_chainPosition_882), gd::gd_neg(gd::GdVal::from_int(1LL))))))))) : gd::GdVal::from_bool(false));
    }
    else {
        return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(12LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_deck_883))))) : gd::GdVal::from_bool(false));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_prepare_122, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_preCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_preCombatStart_124, nullptr, 0, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_99, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_getNextCard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_affected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInAffectedCells_cached_423, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_affected, gd::SYM_empty, nullptr, 0)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(12LL)}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL)), SYM_GEN_hasType_79, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        return gd::get_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL));
    }
    else {
        return gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_startActivation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(this->f_activating) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(this->f_faceUp))))) {
        return gd::GdVal::null();
    }
    this->f_activating = gd::GdVal::from_bool(true);
    this->f_iterationCooldown = gd::gd_coerce_float(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCooldown_102, nullptr, 0));
    this->f_triggerTime = gd::gd_coerce_float(this->f_iterationCooldown);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activateCooldown_98, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(9LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_playActivationAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_aniType = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_activationAni_1717));
    gd::GdVal lv_consume = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(false));
    lv_consume = gd::gd_coerce_bool(lv_consume);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__faceUp = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__faceUp = gd::gd_coerce_bool(lv__faceUp);
    if (gd::gd_truth(lv__faceUp)) {
        if (gd::gd_truth(this->f_faceUp)) {
        }
        else {
        }
    }
    else {
        if (gd::gd_truth(this->f_faceUp)) {
        }
    }
    this->f_faceUp = lv__faceUp;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_trigger(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_activating = gd::GdVal::from_bool(false);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldown_794, _ca, 1); })();
    gd::GdVal lv_nextCard = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNextCard_891, nullptr, 0);
    if (gd::gd_truth(lv_nextCard)) {
        (void)gd::call_method(gd_ctx, lv_nextCard, SYM_GEN_startActivation_892, nullptr, 0);
    }
    this->f_triggerTime = gd::gd_coerce_float(this->f_iterationCooldown);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_99, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doRevealEffect_893, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_combatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_combatEnd_131, nullptr, 0, _out); return _out; })();
    this->f_activating = gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_shopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craft = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_craft = gd::gd_coerce_bool(lv_craft);
    (void)([&]() { gd::GdVal _ca[] = {lv_craft}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_shopEntered_745, _ca, 1, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setFaceUp_887, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_addToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__inventory = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__occupiedCells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__placedByPlayer = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv__placedByPlayer = gd::gd_coerce_bool(lv__placedByPlayer);
    (void)([&]() { gd::GdVal _ca[] = {lv__inventory, lv__occupiedCells, lv__placedByPlayer}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_addToInventory_120, _ca, 3, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_deck = gd::GdVal::null();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateTexture_889, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_notifyChainPosition(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__deck = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__chainPos = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_chainLength = (_argc > 2) ? _args[2] : gd::GdVal::null();
    this->f_chainPosition = lv__chainPos;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_chainPosition, gd::gd_neg(gd::GdVal::from_int(1LL)))))) {
        this->f_deck = gd::GdVal::null();
        if (gd::gd_truth(this->f_placed)) {
        }
    }
    else {
        this->f_deck = lv__deck;
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_chainPosition, gd::gd_sub(lv_chainLength, gd::GdVal::from_int(1LL)))))) {
        }
        else {
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateTexture_889, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_642, _ca, 1, _out); return _out; })();
    return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCardDescription_895, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_getCardDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(this->f_deck)) {
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[0]), ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[1])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_tra_2715, _ca, 1); })(), gd::GdVal::from_str(&battle_string_literals[2]), this->f_chainPosition, gd::GdVal::from_int(0LL), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 5); })()));
    }
    else if (gd::gd_truth(this->f_placed)) {
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[0]), ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[3])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_tra_2715, _ca, 1); })(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_paramColor_2717)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_wrapInColor_2771, _ca, 2); })()));
    }
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Card(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Card>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Card = {CLS_Gd__gd_core_items__Card, "Card", "res://gd_core_items/Card.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Card, &Gd__gd_core_items__Card::get_static_prop_fn, &Gd__gd_core_items__Card::call_static_fn};

void Gd__gd_core_items__Blueberries::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Blueberries::meta() const { return &META_Gd__gd_core_items__Blueberries; }
gd::GdVal Gd__gd_core_items__Blueberries::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Blueberries::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Blueberries::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Blueberries::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Blueberries::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Blueberries::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Blueberries::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Blueberries::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_overflow = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_capped_335, _ca, 2); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_overflow, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Blueberries::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Blueberries(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Blueberries>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Blueberries = {CLS_Gd__gd_core_items__Blueberries, "Blueberries", "res://gd_core_items/Blueberries.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Blueberries, &Gd__gd_core_items__Blueberries::get_static_prop_fn, &Gd__gd_core_items__Blueberries::call_static_fn};

void Gd__gd_core_items__CursedHairComb::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__CursedHairComb::meta() const { return &META_Gd__gd_core_items__CursedHairComb; }
gd::GdVal Gd__gd_core_items__CursedHairComb::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__CursedHairComb::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__CursedHairComb::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__CursedHairComb::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__CursedHairComb::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onAffectedAttacked_1824: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__CursedHairComb::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onAffectedAttacked_1824: out = fn_onAffectedAttacked(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__CursedHairComb::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__CursedHairComb::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedHairComb::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(24LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedHairComb::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_addHealingEfficiency_1182, _ca, 1); })();
    {
        gd::GdVal _t647 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t648 = (_t647.kind == gd::GdVal::Kind::Arr) ? _t647.arr : nullptr;
        uint32_t _len__t649 = _t648 ? _t648->len : 0u;
        for (uint32_t _t649 = 0; _t649 < _len__t649; ++_t649) {
            gd::GdVal lv_weapon = _t648->data[_t649];
            (void)([&]() { gd::GdVal _ca[] = {lv_weapon, gd::GdVal::from_str(&battle_string_literals[120]), gd::GdVal::from_str(&battle_string_literals[121])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedHairComb::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedHairComb::fn_onAffectedAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        gd::GdVal lv_bonusLifesteal = gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[122])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })());
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_ceil(gd::gd_div(gd_ctx, gd::gd_mul(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[107])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), lv_bonusLifesteal)), gd::GdVal::from_float(100.0))), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedHairComb::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__CursedHairComb(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__CursedHairComb>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__CursedHairComb = {CLS_Gd__gd_core_items__CursedHairComb, "CursedHairComb", "res://gd_core_items/CursedHairComb.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__CursedHairComb, &Gd__gd_core_items__CursedHairComb::get_static_prop_fn, &Gd__gd_core_items__CursedHairComb::call_static_fn};

void Gd__gd_core_items__Exclusive__AmuletofAlchemy::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_potionsToTrigger = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_potionTriggerTimer = gd::GdVal::null();
    this->f_delay = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__AmuletofAlchemy::meta() const { return &META_Gd__gd_core_items__Exclusive__AmuletofAlchemy; }
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_amuletColor_2020: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.266667), gd::GdVal::from_float(0.309804), gd::GdVal::from_float(0.960784)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__AmuletofAlchemy::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__AmuletofAlchemy::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_potionsToTrigger_2023: out = this->f_potionsToTrigger; return true;
        case SYM_GEN_potionTriggerTimer_2024: out = this->f_potionTriggerTimer; return true;
        case SYM_GEN_delay_2025: out = this->f_delay; return true;
        case SYM_GEN_amuletColor_2020: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofAlchemy::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_potionsToTrigger_2023: this->f_potionsToTrigger = val; return true;
        case SYM_GEN_potionTriggerTimer_2024: this->f_potionTriggerTimer = val; return true;
        case SYM_GEN_delay_2025: this->f_delay = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__AmuletofAlchemy::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onPotionEmptied_1967: return true;
        case SYM_GEN_triggerNextPotion_2026: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AmuletofAlchemy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onPotionEmptied_1967: out = fn_onPotionEmptied(args, argc); return true;
        case SYM_GEN_triggerNextPotion_2026: out = fn_triggerNextPotion(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofAlchemy::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(11LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t650 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t651 = (_t650.kind == gd::GdVal::Kind::Arr) ? _t650.arr : nullptr;
        uint32_t _len__t652 = _t651 ? _t651->len : 0u;
        for (uint32_t _t652 = 0; _t652 < _len__t652; ++_t652) {
            gd::GdVal lv_item = _t651->data[_t652];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[110]), gd::GdVal::from_str(&battle_string_literals[111])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[113])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::fn_onPotionEmptied(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_potion = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_potion}; return gd::call_method(gd_ctx, this->f_potionsToTrigger, gd::SYM_push_back, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_delay}; return gd::call_method(gd_ctx, this->f_potionTriggerTimer, SYM_GEN_start_1779, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::fn_triggerNextPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_potion = gd::call_method(gd_ctx, this->f_potionsToTrigger, gd::SYM_pop_front, nullptr, 0);
    (void)gd::call_method(gd_ctx, lv_potion, SYM_GEN_triggerPotion_1850, nullptr, 0);
    (void)gd::call_method(gd_ctx, lv_potion, SYM_GEN_miniActivate_470, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_potionTriggerTimer, SYM_GEN_stop_1780, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_potionsToTrigger, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_potionTriggerTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[123]), gd::GdVal::from_str(&battle_string_literals[124]), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_delay = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[125])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__AmuletofAlchemy(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__AmuletofAlchemy>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletofAlchemy = {CLS_Gd__gd_core_items__Exclusive__AmuletofAlchemy, "AmuletofAlchemy", "res://gd_core_items/Exclusive/AmuletofAlchemy.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__AmuletofAlchemy, &Gd__gd_core_items__Exclusive__AmuletofAlchemy::get_static_prop_fn, &Gd__gd_core_items__Exclusive__AmuletofAlchemy::call_static_fn};

void Gd__gd_core_items__Exclusive__ArmoredPowerPuppy::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__PowerPuppy::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ArmoredPowerPuppy::meta() const { return &META_Gd__gd_core_items__Exclusive__ArmoredPowerPuppy; }
gd::GdVal Gd__gd_core_items__Exclusive__ArmoredPowerPuppy::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__PowerPuppy::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ArmoredPowerPuppy::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ArmoredPowerPuppy::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Exclusive__PowerPuppy::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ArmoredPowerPuppy::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Exclusive__PowerPuppy::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ArmoredPowerPuppy::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__PowerPuppy::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ArmoredPowerPuppy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__PowerPuppy::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ArmoredPowerPuppy::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__PowerPuppy::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ArmoredPowerPuppy::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(3LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArmoredPowerPuppy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numFood = gd::GdVal::from_int(0LL);
    gd::GdVal lv_numPets = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t653 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t654 = (_t653.kind == gd::GdVal::Kind::Arr) ? _t653.arr : nullptr;
        uint32_t _len__t655 = _t654 ? _t654->len : 0u;
        for (uint32_t _t655 = 0; _t655 < _len__t655; ++_t655) {
            gd::GdVal lv_item = _t654->data[_t655];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
                lv_numFood = gd::gd_add(gd_ctx, lv_numFood, gd::GdVal::from_int(1LL));
            }
            else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(3LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
                lv_numPets = gd::gd_add(gd_ctx, lv_numPets, gd::GdVal::from_int(1LL));
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_add(gd_ctx, gd::gd_mul(lv_numPets, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0)), gd::gd_mul(lv_numFood, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_267, nullptr, 0))), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArmoredPowerPuppy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__PowerPuppy::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ArmoredPowerPuppy(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ArmoredPowerPuppy>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ArmoredPowerPuppy = {CLS_Gd__gd_core_items__Exclusive__ArmoredPowerPuppy, "ArmoredPowerPuppy", "res://gd_core_items/Exclusive/ArmoredPowerPuppy.gd", &META_Gd__gd_core_items__Exclusive__PowerPuppy, true, _alloc_Gd__gd_core_items__Exclusive__ArmoredPowerPuppy, &Gd__gd_core_items__Exclusive__ArmoredPowerPuppy::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ArmoredPowerPuppy::call_static_fn};

void Gd__gd_core_items__Exclusive__BigBloodthorne::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Greatsword::init_fields(gd_ctx);
    this->f_damPerVampOrSpike = gd::GdVal::null();
    this->f_regenNeeded = gd::GdVal::null();
    this->f_vampirism = gd::GdVal::null();
    this->f_spikes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__BigBloodthorne::meta() const { return &META_Gd__gd_core_items__Exclusive__BigBloodthorne; }
gd::GdVal Gd__gd_core_items__Exclusive__BigBloodthorne::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Greatsword::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__BigBloodthorne::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__BigBloodthorne::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_damPerVampOrSpike_2072: out = this->f_damPerVampOrSpike; return true;
        case SYM_GEN_regenNeeded_942: out = this->f_regenNeeded; return true;
        case SYM_GEN_vampirism_940: out = this->f_vampirism; return true;
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        default: break;
    }
    return Gd__gd_core_items__Greatsword::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BigBloodthorne::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damPerVampOrSpike_2072: this->f_damPerVampOrSpike = val; return true;
        case SYM_GEN_regenNeeded_942: this->f_regenNeeded = val; return true;
        case SYM_GEN_vampirism_940: this->f_vampirism = val; return true;
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Greatsword::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BigBloodthorne::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onVampirismChanged_943: return true;
        case SYM_GEN_onSpikesChanged_944: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Greatsword::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BigBloodthorne::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onVampirismChanged_943: out = fn_onVampirismChanged(args, argc); return true;
        case SYM_GEN_onSpikesChanged_944: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Greatsword::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BigBloodthorne::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Greatsword::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BigBloodthorne::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Greatsword::call_method(gd_ctx, SYM_GEN_onPrepare_123, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[4]), gd::GdVal::from_str(&battle_string_literals[5])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[6]), gd::GdVal::from_str(&battle_string_literals[7])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BigBloodthorne::fn_onVampirismChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, this->f_damPerVampOrSpike)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_162, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BigBloodthorne::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, this->f_damPerVampOrSpike)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_162, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BigBloodthorne::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRegeneration_1233, nullptr, 0), this->f_regenNeeded)))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_regenNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_346, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_vampirism}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BigBloodthorne::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Greatsword::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_damPerVampOrSpike = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[108])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_regenNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[126])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_vampirism = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[127])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[128])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BigBloodthorne(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__BigBloodthorne>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BigBloodthorne = {CLS_Gd__gd_core_items__Exclusive__BigBloodthorne, "BigBloodthorne", "res://gd_core_items/Exclusive/BigBloodthorne.gd", &META_Gd__gd_core_items__Greatsword, true, _alloc_Gd__gd_core_items__Exclusive__BigBloodthorne, &Gd__gd_core_items__Exclusive__BigBloodthorne::get_static_prop_fn, &Gd__gd_core_items__Exclusive__BigBloodthorne::call_static_fn};

void Gd__gd_core_items__Exclusive__BroccoliGoobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Goobert::init_fields(gd_ctx);
    this->f_luck = gd::GdVal::null();
    this->f_luckNeeded = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__BroccoliGoobert::meta() const { return &META_Gd__gd_core_items__Exclusive__BroccoliGoobert; }
gd::GdVal Gd__gd_core_items__Exclusive__BroccoliGoobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__BroccoliGoobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__BroccoliGoobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_luckNeeded_1874: out = this->f_luckNeeded; return true;
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BroccoliGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_luckNeeded_1874: this->f_luckNeeded = val; return true;
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BroccoliGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BroccoliGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BroccoliGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BroccoliGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), this->f_luckNeeded)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BroccoliGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[129])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[130])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[131])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BroccoliGoobert(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__BroccoliGoobert>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BroccoliGoobert = {CLS_Gd__gd_core_items__Exclusive__BroccoliGoobert, "BroccoliGoobert", "res://gd_core_items/Exclusive/BroccoliGoobert.gd", &META_Gd__gd_core_items__Goobert, true, _alloc_Gd__gd_core_items__Exclusive__BroccoliGoobert, &Gd__gd_core_items__Exclusive__BroccoliGoobert::get_static_prop_fn, &Gd__gd_core_items__Exclusive__BroccoliGoobert::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Exclusive__Chess__ChessPiece_PieceColor[] = {{"Black", 0LL}, {"White", 1LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Exclusive__Chess__ChessPiece_PieceColor = {"PieceColor", _ekv_Gd__gd_core_items__Exclusive__Chess__ChessPiece_PieceColor, 2u};
void Gd__gd_core_items__Exclusive__Chess__ChessPiece::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_pieceColor = gd::GdVal::from_int(0);
    this->f_moveCells = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_captured = gd::GdVal::from_bool(false);
    this->f_numCaptures = gd::GdVal::from_int(0);
    this->f_board = gd::GdVal::null();
    this->f_noBoardMark = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Chess__ChessPiece::meta() const { return &META_Gd__gd_core_items__Exclusive__Chess__ChessPiece; }
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_PieceColor_2150: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__Chess__ChessPiece_PieceColor);
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_pieceColor_2135: out = this->f_pieceColor; return true;
        case SYM_GEN_moveCells_2136: out = this->f_moveCells; return true;
        case SYM_GEN_captured_2137: out = this->f_captured; return true;
        case SYM_GEN_numCaptures_2138: out = this->f_numCaptures; return true;
        case SYM_GEN_board_2139: out = this->f_board; return true;
        case SYM_GEN_noBoardMark_2140: out = this->f_noBoardMark; return true;
        case SYM_GEN_PieceColor_2150: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__Chess__ChessPiece_PieceColor); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_pieceColor_2135: this->f_pieceColor = gd::gd_coerce_int(val); return true;
        case SYM_GEN_moveCells_2136: this->f_moveCells = val; return true;
        case SYM_GEN_captured_2137: this->f_captured = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_numCaptures_2138: this->f_numCaptures = gd::gd_coerce_int(val); return true;
        case SYM_GEN_board_2139: this->f_board = val; return true;
        case SYM_GEN_noBoardMark_2140: this->f_noBoardMark = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_affectsEmpty_255: return true;
        case SYM_GEN_setBoard_2141: return true;
        case SYM_GEN_prepare_122: return true;
        case SYM_GEN_getMoveCells_2142: return true;
        case SYM_GEN_getCaptureCells_2143: return true;
        case SYM_GEN_onPieceMoved_2144: return true;
        case SYM_GEN_onPieceCaptured_2145: return true;
        case SYM_GEN_doCapturingEffect_2146: return true;
        case SYM_GEN_onEliminatedBy_2147: return true;
        case SYM_GEN_doEliminatedEffect_2148: return true;
        case SYM_GEN_repositionPiece_2149: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN_onAddToInventory_419: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_discard_764: return true;
        case SYM_GEN_canBeBlocked_1558: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_affectsEmpty_255: out = fn_affectsEmpty(args, argc); return true;
        case SYM_GEN_setBoard_2141: out = fn_setBoard(args, argc); return true;
        case SYM_GEN_prepare_122: out = fn_prepare(args, argc); return true;
        case SYM_GEN_getMoveCells_2142: out = fn_getMoveCells(args, argc); return true;
        case SYM_GEN_getCaptureCells_2143: out = fn_getCaptureCells(args, argc); return true;
        case SYM_GEN_onPieceMoved_2144: out = fn_onPieceMoved(args, argc); return true;
        case SYM_GEN_onPieceCaptured_2145: out = fn_onPieceCaptured(args, argc); return true;
        case SYM_GEN_doCapturingEffect_2146: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_onEliminatedBy_2147: out = fn_onEliminatedBy(args, argc); return true;
        case SYM_GEN_doEliminatedEffect_2148: out = fn_doEliminatedEffect(args, argc); return true;
        case SYM_GEN_repositionPiece_2149: out = fn_repositionPiece(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_onAddToInventory_419: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_discard_764: out = fn_discard(args, argc); return true;
        case SYM_GEN_canBeBlocked_1558: out = fn_canBeBlocked(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(17LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_item, SYM_GEN_pieceColor_2135), this->f_pieceColor)))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_affectsEmpty(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_setBoard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__board = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_board = lv__board;
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_board, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(this->f_placed)) : gd::GdVal::from_bool(false)))) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, this->f_occupiedCells, gd::GdVal::from_int(0LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)gd::call_method(gd_ctx, this->f_moveCells, gd::SYM_clear, nullptr, 0);
    {
        gd::GdVal _t656 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCells_tilemap_408, nullptr, 0));
        gd::GdArr* _t657 = (_t656.kind == gd::GdVal::Kind::Arr) ? _t656.arr : nullptr;
        uint32_t _len__t658 = _t657 ? _t657->len : 0u;
        for (uint32_t _t658 = 0; _t658 < _len__t658; ++_t658) {
            gd::GdVal lv_cell = _t657->data[_t658];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::gd_sub(lv_cell, gd::get_index(gd_ctx, this->f_occupiedCells, gd::GdVal::from_int(0LL))), gd::SYM_round, nullptr, 0)}; return gd::call_method(gd_ctx, this->f_moveCells, gd::SYM_push_back, _ca, 1); })();
        }
    }
    this->f_numCaptures = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_prepare_122, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_getMoveCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_moveCells;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_getCaptureCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_moveCells;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_onPieceMoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_targetCell = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_targetCell}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_onPieceCaptured(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_eliminatedPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_activateEvent = (_argc > 1) ? _args[1] : gd::GdVal::null();
    this->f_numCaptures = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numCaptures, gd::GdVal::from_int(1LL)));
    gd::GdVal lv_targetCell = gd::get_index(gd_ctx, gd::get_prop(gd_ctx, lv_eliminatedPiece, SYM_GEN_occupiedCells_52), gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {lv_eliminatedPiece}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_clearItemCells_1620, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_targetCell, gd::GdVal::from_bool(false), lv_activateEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::null(), gd::GdVal::null(), gd::GdVal::null()})), gd::GdVal::from_str(&battle_string_literals[132])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_pickRandomEngine_1748, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_eliminatedPiece}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCapturingEffect_2146, _ca, 1); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_doCapturingEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_eliminatedPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_onEliminatedBy(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_activateEvent = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(false), lv_activateEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_capturingPiece}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doEliminatedEffect_2148, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_doEliminatedEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_repositionPiece(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toCell = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_toCell}))}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_moveItem_1621, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_state = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::GdVal::from_int(gd::gd_typeof(lv_state)), gd::GdVal::from_int(5))))) {
        gd::GdVal lv_targetCell = lv_state;
        (void)([&]() { gd::GdVal _ca[] = {lv_targetCell}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_repositionPiece_2149, _ca, 1); })();
    }
    else {
        this->f_captured = gd::gd_coerce_bool(lv_state);
        if (gd::gd_truth(this->f_captured)) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_clearItemCells_1620, _ca, 1); })();
        }
        else {
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_642, _ca, 1, _out); return _out; })();
    if (gd::gd_truth((gd::gd_truth(this->f_placed) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_board, gd::GdVal::null())))) : gd::GdVal::from_bool(false)))) {
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[0]), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[133]), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_paramColor_2717)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_wrapInColor_2771, _ca, 2); })()));
    }
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_discard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_discardGems = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    (void)([&]() { gd::GdVal _ca[] = {lv_discardGems}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_discard_764, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_canBeBlocked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    if (gd::gd_truth(gd::gd_in(gd::GdVal::from_str(&battle_string_literals[134]), this->f_name))) {
        this->f_pieceColor = gd::gd_coerce_int(gd::GdVal::from_int(1LL));
    }
    else {
        this->f_pieceColor = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Chess__ChessPiece(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Chess__ChessPiece>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__ChessPiece = {CLS_Gd__gd_core_items__Exclusive__Chess__ChessPiece, "ChessPiece", "res://gd_core_items/Exclusive/Chess/ChessPiece.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Chess__ChessPiece, &Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_static_fn};

void Gd__gd_core_items__Exclusive__ChiliPepper::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ChiliPepper::meta() const { return &META_Gd__gd_core_items__Exclusive__ChiliPepper; }
gd::GdVal Gd__gd_core_items__Exclusive__ChiliPepper::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ChiliPepper::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ChiliPepper::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ChiliPepper::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ChiliPepper::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ChiliPepper::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ChiliPepper::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ChiliPepper::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getHeat_1251, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_356, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ChiliPepper::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ChiliPepper(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ChiliPepper>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ChiliPepper = {CLS_Gd__gd_core_items__Exclusive__ChiliPepper, "ChiliPepper", "res://gd_core_items/Exclusive/ChiliPepper.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Exclusive__ChiliPepper, &Gd__gd_core_items__Exclusive__ChiliPepper::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ChiliPepper::call_static_fn};

void Gd__gd_core_items__Exclusive__DarkRitual::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_boosted = gd::GdVal::from_int(0LL);
    this->f_crystalDescriptor = gd::GdVal::null();
    this->f_debuffs = gd::GdVal::null();
    this->f_vampirism = gd::GdVal::null();
    this->f_darkSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__DarkRitual::meta() const { return &META_Gd__gd_core_items__Exclusive__DarkRitual; }
gd::GdVal Gd__gd_core_items__Exclusive__DarkRitual::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__DarkRitual::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__DarkRitual::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_boosted_2197: out = this->f_boosted; return true;
        case SYM_GEN_crystalDescriptor_2198: out = this->f_crystalDescriptor; return true;
        case SYM_GEN_debuffs_2151: out = this->f_debuffs; return true;
        case SYM_GEN_vampirism_940: out = this->f_vampirism; return true;
        case SYM_GEN_darkSpeed_2199: out = this->f_darkSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DarkRitual::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_boosted_2197: this->f_boosted = val; return true;
        case SYM_GEN_crystalDescriptor_2198: this->f_crystalDescriptor = val; return true;
        case SYM_GEN_debuffs_2151: this->f_debuffs = val; return true;
        case SYM_GEN_vampirism_940: this->f_vampirism = val; return true;
        case SYM_GEN_darkSpeed_2199: this->f_darkSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DarkRitual::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_onBought_455: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onItemRoll_2018: return true;
        case SYM_GEN_onItemRolled_2019: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DarkRitual::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_onBought_455: out = fn_onBought(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemRoll_2018: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_2019: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DarkRitual::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkRitual::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(25LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkRitual::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_boosted;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkRitual::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_data, gd::GdVal::null())))) {
        this->f_boosted = lv_data;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkRitual::fn_onBought(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_boosted = gd::GdVal::from_int(1LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkRitual::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_debuffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictRandomDebuffs_357, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_vampirism}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkRitual::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numDark = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numDark, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_darkSpeed, lv_numDark)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkRitual::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkRitual::fn_onItemRolled(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_descr, this->f_crystalDescriptor)))) {
        this->f_boosted = gd::gd_sub(this->f_boosted, gd::GdVal::from_int(1LL));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkRitual::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_crystalDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[135])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_debuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[136])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_vampirism = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[127])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_darkSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[137])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DarkRitual(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__DarkRitual>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DarkRitual = {CLS_Gd__gd_core_items__Exclusive__DarkRitual, "DarkRitual", "res://gd_core_items/Exclusive/DarkRitual.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__DarkRitual, &Gd__gd_core_items__Exclusive__DarkRitual::get_static_prop_fn, &Gd__gd_core_items__Exclusive__DarkRitual::call_static_fn};

void Gd__gd_core_items__Exclusive__DragonskinBoots::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_hasActivated = gd::GdVal::from_bool(false);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__DragonskinBoots::meta() const { return &META_Gd__gd_core_items__Exclusive__DragonskinBoots; }
gd::GdVal Gd__gd_core_items__Exclusive__DragonskinBoots::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__DragonskinBoots::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__DragonskinBoots::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_hasActivated_1906: out = this->f_hasActivated; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DragonskinBoots::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hasActivated_1906: this->f_hasActivated = gd::gd_coerce_bool(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DragonskinBoots::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onBattleRageStarted_2066: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DragonskinBoots::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_2066: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DragonskinBoots::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonskinBoots::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[39]), gd::GdVal::from_str(&battle_string_literals[138])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(110LL), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeResistChance_1026, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonskinBoots::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_356, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), gd::GdVal::from_bool(true), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonskinBoots::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DragonskinBoots(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__DragonskinBoots>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DragonskinBoots = {CLS_Gd__gd_core_items__Exclusive__DragonskinBoots, "DragonskinBoots", "res://gd_core_items/Exclusive/DragonskinBoots.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__DragonskinBoots, &Gd__gd_core_items__Exclusive__DragonskinBoots::get_static_prop_fn, &Gd__gd_core_items__Exclusive__DragonskinBoots::call_static_fn};

void Gd__gd_core_items__Exclusive__ExtraAngy::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_activated = gd::GdVal::from_bool(false);
    this->f_battleRageDur = gd::GdVal::from_float(0.0);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ExtraAngy::meta() const { return &META_Gd__gd_core_items__Exclusive__ExtraAngy; }
gd::GdVal Gd__gd_core_items__Exclusive__ExtraAngy::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ExtraAngy::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ExtraAngy::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activated_1314: out = this->f_activated; return true;
        case SYM_GEN_battleRageDur_2253: out = this->f_battleRageDur; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ExtraAngy::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1314: this->f_activated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_battleRageDur_2253: this->f_battleRageDur = gd::gd_coerce_float(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ExtraAngy::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_preCombatStart_124: return true;
        case SYM_GEN_onBattleRageStarted_2066: return true;
        case SYM_GEN_onBattleRageEnded_2067: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ExtraAngy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_preCombatStart_124: out = fn_preCombatStart(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_2066: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN_onBattleRageEnded_2067: out = fn_onBattleRageEnded(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ExtraAngy::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraAngy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[39]), gd::GdVal::from_str(&battle_string_literals[138])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[40]), gd::GdVal::from_str(&battle_string_literals[139])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraAngy::fn_preCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_preCombatStart_124, nullptr, 0, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_99, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraAngy::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated)))) {
        this->f_battleRageDur = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[140]), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_event, SYM_GEN_getParam_1575, _ca, 2); })());
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraAngy::fn_onBattleRageEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated)))) {
        this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activateCooldown_98, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraAngy::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dur = gd::gd_div(gd_ctx, gd::gd_mul(this->f_battleRageDur, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[141])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()), gd::GdVal::from_float(100.0));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_dur, gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_startBattleRage_1199, _ca, 4); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraAngy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ExtraAngy(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ExtraAngy>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ExtraAngy = {CLS_Gd__gd_core_items__Exclusive__ExtraAngy, "ExtraAngy", "res://gd_core_items/Exclusive/ExtraAngy.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__ExtraAngy, &Gd__gd_core_items__Exclusive__ExtraAngy::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ExtraAngy::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Exclusive__FrogPrince_FrogState[] = {{"Inactive", 0LL}, {"Active", 1LL}, {"Used", 2LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Exclusive__FrogPrince_FrogState = {"FrogState", _ekv_Gd__gd_core_items__Exclusive__FrogPrince_FrogState, 3u};
void Gd__gd_core_items__Exclusive__FrogPrince::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Toad::init_fields(gd_ctx);
    this->f_frogState = gd::GdVal::from_int(0);
    this->f_activationParticles = gd::GdVal::null();
    this->f_buffTimer = gd::GdVal::null();
    this->f_light = gd::GdVal::null();
    this->f_blind = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__FrogPrince::meta() const { return &META_Gd__gd_core_items__Exclusive__FrogPrince; }
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_FrogState_2277: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__FrogPrince_FrogState);
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Toad::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__FrogPrince::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__FrogPrince::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_frogState_2276: out = this->f_frogState; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_buffTimer_1819: out = this->f_buffTimer; return true;
        case SYM_GEN_light_949: out = this->f_light; return true;
        case SYM_GEN_blind_1911: out = this->f_blind; return true;
        case SYM_GEN_FrogState_2277: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__FrogPrince_FrogState); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Toad::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__FrogPrince::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_frogState_2276: this->f_frogState = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_buffTimer_1819: this->f_buffTimer = val; return true;
        case SYM_GEN_light_949: this->f_light = val; return true;
        case SYM_GEN_blind_1911: this->f_blind = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Toad::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__FrogPrince::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onGainThresholdReached_2274: return true;
        case SYM_GEN_onUseThresholdReached_2275: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_buffEnded_1817: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Toad::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__FrogPrince::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onGainThresholdReached_2274: out = fn_onGainThresholdReached(args, argc); return true;
        case SYM_GEN_onUseThresholdReached_2275: out = fn_onUseThresholdReached(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_buffEnded_1817: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Toad::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__FrogPrince::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Toad::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn_onGainThresholdReached(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_ticks = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_blind, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseBlind_344, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_ticks, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[114])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn_onUseThresholdReached(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_ticks = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_frogState, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_mana, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 2); })();
        gd::GdVal lv_invuDur = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[142])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_invuDur, gd::GdVal::from_obj(this), lv_event}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_makeInvulnerable_1211, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_invuDur}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1779, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Toad::call_method(gd_ctx, SYM_GEN_onPrepare_123, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__frogState = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__frogState, gd::GdVal::from_int(0LL))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__frogState, gd::GdVal::from_int(1LL))))) {
    }
    else {
    }
    this->f_frogState = gd::gd_coerce_int(lv__frogState);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Toad::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[143]), gd::GdVal::from_str(&battle_string_literals[117]), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_blind = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[144])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__FrogPrince(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__FrogPrince>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FrogPrince = {CLS_Gd__gd_core_items__Exclusive__FrogPrince, "FrogPrince", "res://gd_core_items/Exclusive/FrogPrince.gd", &META_Gd__gd_core_items__Exclusive__Toad, true, _alloc_Gd__gd_core_items__Exclusive__FrogPrince, &Gd__gd_core_items__Exclusive__FrogPrince::get_static_prop_fn, &Gd__gd_core_items__Exclusive__FrogPrince::call_static_fn};

void Gd__gd_core_items__Exclusive__HeartoftheCards::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_regen = gd::GdVal::null();
    this->f_mana = gd::GdVal::null();
    this->f_chainPosition = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__HeartoftheCards::meta() const { return &META_Gd__gd_core_items__Exclusive__HeartoftheCards; }
gd::GdVal Gd__gd_core_items__Exclusive__HeartoftheCards::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__HeartoftheCards::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__HeartoftheCards::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        case SYM_GEN_mana_1928: out = this->f_mana; return true;
        case SYM_GEN_chainPosition_882: out = this->f_chainPosition; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__HeartoftheCards::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        case SYM_GEN_mana_1928: this->f_mana = val; return true;
        case SYM_GEN_chainPosition_882: this->f_chainPosition = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__HeartoftheCards::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCardRevealed_2298: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__HeartoftheCards::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCardRevealed_2298: out = fn_onCardRevealed(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__HeartoftheCards::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartoftheCards::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t659 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t660 = (_t659.kind == gd::GdVal::Kind::Arr) ? _t659.arr : nullptr;
        uint32_t _len__t661 = _t660 ? _t660->len : 0u;
        for (uint32_t _t661 = 0; _t661 < _len__t661; ++_t661) {
            gd::GdVal lv_item = _t660->data[_t661];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(12LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[145]), gd::GdVal::from_str(&battle_string_literals[146])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartoftheCards::fn_onCardRevealed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_card = gd::call_method(gd_ctx, lv_event, SYM_GEN_getOrigin_1580, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {this->f_regen, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 2); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_card, SYM_GEN_chainPosition_882), gd::GdVal::from_int(1LL)), this->f_chainPosition)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_mana, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartoftheCards::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[131])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[109])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_chainPosition = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[147])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__HeartoftheCards(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__HeartoftheCards>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__HeartoftheCards = {CLS_Gd__gd_core_items__Exclusive__HeartoftheCards, "HeartoftheCards", "res://gd_core_items/Exclusive/HeartoftheCards.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__HeartoftheCards, &Gd__gd_core_items__Exclusive__HeartoftheCards::get_static_prop_fn, &Gd__gd_core_items__Exclusive__HeartoftheCards::call_static_fn};

void Gd__gd_core_items__Exclusive__Joker::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Card::init_fields(gd_ctx);
    this->f_quads = gd::GdVal::from_int(0LL);
    this->f_triplets = gd::GdVal::from_int(0LL);
    this->f_pairs = gd::GdVal::from_int(0LL);
    this->f_activationParticles = gd::GdVal::null();
    this->f_staminaReduction = gd::GdVal::null();
    this->f_revealsPerQuad = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Joker::meta() const { return &META_Gd__gd_core_items__Exclusive__Joker; }
gd::GdVal Gd__gd_core_items__Exclusive__Joker::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Card::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Joker::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Joker::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_quads_2325: out = this->f_quads; return true;
        case SYM_GEN_triplets_2326: out = this->f_triplets; return true;
        case SYM_GEN_pairs_2327: out = this->f_pairs; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_staminaReduction_2013: out = this->f_staminaReduction; return true;
        case SYM_GEN_revealsPerQuad_2328: out = this->f_revealsPerQuad; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Joker::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_quads_2325: this->f_quads = val; return true;
        case SYM_GEN_triplets_2326: this->f_triplets = val; return true;
        case SYM_GEN_pairs_2327: this->f_pairs = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_staminaReduction_2013: this->f_staminaReduction = val; return true;
        case SYM_GEN_revealsPerQuad_2328: this->f_revealsPerQuad = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Joker::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_countChain_2329: return true;
        case SYM_GEN_notifyChainPosition_894: return true;
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN_getCardDescription_895: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Card::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Joker::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_countChain_2329: out = fn_countChain(args, argc); return true;
        case SYM_GEN_notifyChainPosition_894: out = fn_notifyChainPosition(args, argc); return true;
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN_getCardDescription_895: out = fn_getCardDescription(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Joker::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Joker::fn_countChain(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_quads = gd::GdVal::from_int(0LL);
    this->f_triplets = gd::GdVal::from_int(0LL);
    this->f_pairs = gd::GdVal::from_int(0LL);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_chainPosition, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_counter = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
        {
            gd::GdVal _t662 = gd::gd_iter_seq(gd_ctx.arena, this->f_chainPosition);
            gd::GdArr* _t663 = (_t662.kind == gd::GdVal::Kind::Arr) ? _t662.arr : nullptr;
            uint32_t _len__t664 = _t663 ? _t663->len : 0u;
            for (uint32_t _t664 = 0; _t664 < _len__t664; ++_t664) {
                gd::GdVal lv_i = _t663->data[_t664];
                (void)([&]() { gd::GdVal _ca[] = {lv_counter, gd::get_prop(gd_ctx, gd::get_index(gd_ctx, gd::get_prop(gd_ctx, this->f_deck, SYM_GEN_cards_1832), lv_i), SYM_GEN_descriptor_2)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_dictAdd_1789, _ca, 2); })();
            }
        }
        {
            gd::GdVal _t665 = gd::gd_iter_seq(gd_ctx.arena, lv_counter);
            gd::GdArr* _t666 = (_t665.kind == gd::GdVal::Kind::Arr) ? _t665.arr : nullptr;
            uint32_t _len__t667 = _t666 ? _t666->len : 0u;
            for (uint32_t _t667 = 0; _t667 < _len__t667; ++_t667) {
                gd::GdVal lv_cardType = _t666->data[_t667];
                this->f_quads = gd::gd_add(gd_ctx, this->f_quads, gd::gd_div(gd_ctx, gd::get_index(gd_ctx, lv_counter, lv_cardType), gd::GdVal::from_int(4LL)));
                gd::GdVal lv_rest = gd::gd_mod(gd_ctx, gd::get_index(gd_ctx, lv_counter, lv_cardType), gd::GdVal::from_int(4LL));
                this->f_triplets = gd::gd_add(gd_ctx, this->f_triplets, gd::gd_div(gd_ctx, lv_rest, gd::GdVal::from_int(3LL)));
                lv_rest = gd::gd_mod(gd_ctx, lv_rest, gd::GdVal::from_int(3LL));
                this->f_pairs = gd::gd_add(gd_ctx, this->f_pairs, gd::gd_div(gd_ctx, lv_rest, gd::GdVal::from_int(2LL)));
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Joker::fn_notifyChainPosition(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__deck = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__chainPos = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_chainLength = (_argc > 2) ? _args[2] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv__deck, lv__chainPos, lv_chainLength}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Card::call_method(gd_ctx, SYM_GEN_notifyChainPosition_894, _ca, 3, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countChain_2329, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Joker::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[113])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_pairs, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_pairs}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_gainCritResistStacks_1175, _ca, 1); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_triplets, gd::GdVal::from_int(0LL))))) {
        {
            gd::GdVal _t668 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
            gd::GdArr* _t669 = (_t668.kind == gd::GdVal::Kind::Arr) ? _t668.arr : nullptr;
            uint32_t _len__t670 = _t669 ? _t669->len : 0u;
            for (uint32_t _t670 = 0; _t670 < _len__t670; ++_t670) {
                gd::GdVal lv_item = _t669->data[_t670];
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_neg(this->f_staminaReduction), this->f_triplets)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeStaminaFactor_305, _ca, 1); })();
            }
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_quads, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_legitCards = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
        {
            gd::GdVal _t671 = gd::gd_iter_seq(gd_ctx.arena, this->f_chainPosition);
            gd::GdArr* _t672 = (_t671.kind == gd::GdVal::Kind::Arr) ? _t671.arr : nullptr;
            uint32_t _len__t673 = _t672 ? _t672->len : 0u;
            for (uint32_t _t673 = 0; _t673 < _len__t673; ++_t673) {
                gd::GdVal lv_i = _t672->data[_t673];
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, gd::get_index(gd_ctx, gd::get_prop(gd_ctx, this->f_deck, SYM_GEN_cards_1832), lv_i), SYM_GEN_descriptor_2), this->f_descriptor)))) {
                    (void)([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, gd::get_prop(gd_ctx, this->f_deck, SYM_GEN_cards_1832), lv_i)}; return gd::call_method(gd_ctx, lv_legitCards, gd::SYM_push_back, _ca, 1); })();
                }
            }
        }
        {
            gd::GdVal _t674 = gd::gd_iter_seq(gd_ctx.arena, gd::gd_mul(this->f_quads, this->f_revealsPerQuad));
            gd::GdArr* _t675 = (_t674.kind == gd::GdVal::Kind::Arr) ? _t674.arr : nullptr;
            uint32_t _len__t676 = _t675 ? _t675->len : 0u;
            for (uint32_t _t676 = 0; _t676 < _len__t676; ++_t676) {
                gd::GdVal lv_i = _t675->data[_t676];
                if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_legitCards, gd::SYM_empty, nullptr, 0))))) {
                    gd::GdVal lv_revealedCard = ([&]() { gd::GdVal _ca[] = {lv_legitCards}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_pickRandomElement_1746, _ca, 1); })();
                    (void)gd::call_method(gd_ctx, lv_revealedCard, SYM_GEN_doRevealEffect_893, nullptr, 0);
                    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, lv_legitCards, gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL))))) {
                        (void)([&]() { gd::GdVal _ca[] = {lv_revealedCard}; return gd::call_method(gd_ctx, lv_legitCards, gd::SYM_erase, _ca, 1); })();
                    }
                }
            }
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Joker::fn_getCardDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(this->f_deck)) {
        gd::GdVal lv_counterText = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[148])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_tra_2715, _ca, 1); })();
        gd::GdVal lv_state = gd::GdVal::from_int(0LL);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_pairs, gd::GdVal::from_int(0LL))))) {
            lv_state = gd::GdVal::from_int(1LL);
        }
        else {
            lv_state = gd::GdVal::from_int(2LL);
        }
        lv_counterText = ([&]() { gd::GdVal _ca[] = {lv_counterText, gd::GdVal::from_str(&battle_string_literals[149]), this->f_pairs, lv_state, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 5); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_triplets, gd::GdVal::from_int(0LL))))) {
            lv_state = gd::GdVal::from_int(1LL);
        }
        else {
            lv_state = gd::GdVal::from_int(2LL);
        }
        lv_counterText = ([&]() { gd::GdVal _ca[] = {lv_counterText, gd::GdVal::from_str(&battle_string_literals[150]), this->f_triplets, lv_state, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 5); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_quads, gd::GdVal::from_int(0LL))))) {
            lv_state = gd::GdVal::from_int(1LL);
        }
        else {
            lv_state = gd::GdVal::from_int(2LL);
        }
        lv_counterText = ([&]() { gd::GdVal _ca[] = {lv_counterText, gd::GdVal::from_str(&battle_string_literals[151]), this->f_quads, lv_state, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 5); })();
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[152]), lv_counterText));
    }
    else if (gd::gd_truth(this->f_placed)) {
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[152]), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[3]), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_paramColor_2717)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_wrapInColor_2771, _ca, 2); })()));
    }
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Joker::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Card::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_staminaReduction = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[43])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_revealsPerQuad = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[153])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Joker(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Joker>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Joker = {CLS_Gd__gd_core_items__Exclusive__Joker, "Joker", "res://gd_core_items/Exclusive/Joker.gd", &META_Gd__gd_core_items__Card, true, _alloc_Gd__gd_core_items__Exclusive__Joker, &Gd__gd_core_items__Exclusive__Joker::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Joker::call_static_fn};

void Gd__gd_core_items__Exclusive__LongSpear::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_blockRemoval = gd::GdVal::null();
    this->f_damResistance = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__LongSpear::meta() const { return &META_Gd__gd_core_items__Exclusive__LongSpear; }
gd::GdVal Gd__gd_core_items__Exclusive__LongSpear::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__LongSpear::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__LongSpear::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_blockRemoval_1897: out = this->f_blockRemoval; return true;
        case SYM_GEN_damResistance_2352: out = this->f_damResistance; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__LongSpear::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockRemoval_1897: this->f_blockRemoval = val; return true;
        case SYM_GEN_damResistance_2352: this->f_damResistance = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__LongSpear::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_addToStorageBox_667: return true;
        case SYM_GEN_affectsEmpty_255: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__LongSpear::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_addToStorageBox_667: out = fn_addToStorageBox(args, argc); return true;
        case SYM_GEN_affectsEmpty_255: out = fn_affectsEmpty(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__LongSpear::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__LongSpear::fn_addToStorageBox(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_addImpulse = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_tweenBouncyness = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    lv_tweenBouncyness = gd::gd_coerce_bool(lv_tweenBouncyness);
    gd::GdVal lv_checkCollisions = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_targetPos = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_speed = (_argc > 4) ? _args[4] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_secondCheck = (_argc > 5) ? _args[5] : (gd::GdVal::from_bool(false));
    gd::GdVal lv_curDir = this->f_faceDirection;
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_faceDirection, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_faceDirection, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT)))))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setFaceDirectionInstant_467, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_addImpulse, lv_tweenBouncyness, lv_checkCollisions, lv_targetPos, lv_speed, lv_secondCheck}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_addToStorageBox_667, _ca, 6, _out); return _out; })();
        (void)([&]() { gd::GdVal _ca[] = {lv_curDir}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setFaceDirectionInstant_467, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setFaceDirection_478, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {lv_addImpulse, lv_tweenBouncyness, lv_checkCollisions, lv_targetPos, lv_speed, lv_secondCheck}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_addToStorageBox_667, _ca, 6, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LongSpear::fn_affectsEmpty(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LongSpear::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LongSpear::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_blockRemoval = gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[57])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumEmptyAffectedCells_426, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LongSpear::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_blockRemoval}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeBlock_205, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damResistance)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LongSpear::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_damResistance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[108])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__LongSpear(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__LongSpear>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__LongSpear = {CLS_Gd__gd_core_items__Exclusive__LongSpear, "LongSpear", "res://gd_core_items/Exclusive/LongSpear.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__LongSpear, &Gd__gd_core_items__Exclusive__LongSpear::get_static_prop_fn, &Gd__gd_core_items__Exclusive__LongSpear::call_static_fn};

void Gd__gd_core_items__Exclusive__MegaClover::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_stackTypes = gd::GdVal::null();
    this->f_activated = gd::GdVal::from_bool(false);
    this->f_sales = gd::GdVal::null();
    this->f_luckNeeded = gd::GdVal::from_int(0);
    this->f_numBuffs = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__MegaClover::meta() const { return &META_Gd__gd_core_items__Exclusive__MegaClover; }
gd::GdVal Gd__gd_core_items__Exclusive__MegaClover::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__MegaClover::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__MegaClover::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_stackTypes_1926: out = this->f_stackTypes; return true;
        case SYM_GEN_activated_1314: out = this->f_activated; return true;
        case SYM_GEN_sales_2356: out = this->f_sales; return true;
        case SYM_GEN_luckNeeded_1874: out = this->f_luckNeeded; return true;
        case SYM_GEN_numBuffs_2005: out = this->f_numBuffs; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MegaClover::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stackTypes_1926: this->f_stackTypes = val; return true;
        case SYM_GEN_activated_1314: this->f_activated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_sales_2356: this->f_sales = val; return true;
        case SYM_GEN_luckNeeded_1874: this->f_luckNeeded = gd::gd_coerce_int(val); return true;
        case SYM_GEN_numBuffs_2005: this->f_numBuffs = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MegaClover::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onLuckyChanged_901: return true;
        case SYM_GEN_onSaleRoll_2093: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MegaClover::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onLuckyChanged_901: out = fn_onLuckyChanged(args, argc); return true;
        case SYM_GEN_onSaleRoll_2093: out = fn_onSaleRoll(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__MegaClover::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__MegaClover::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MegaClover::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[154]), gd::GdVal::from_str(&battle_string_literals[155])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MegaClover::fn_onLuckyChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), this->f_luckNeeded)))) : gd::GdVal::from_bool(false)))) {
        this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)([&]() { gd::GdVal _ca[] = {this->f_numBuffs, lv_event, this->f_stackTypes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 3); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_MEGA_CLOVER_PARTICLE_DRAWS_1461)}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_scheduleParticleDraws_1491, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MegaClover::fn_onSaleRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MegaClover::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_sales = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[156])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[157])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_numBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[113])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_stackTypes = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(101LL)}; return gd::call_method(gd_ctx, this->f_stackTypes, gd::SYM_erase, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MegaClover(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__MegaClover>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MegaClover = {CLS_Gd__gd_core_items__Exclusive__MegaClover, "MegaClover", "res://gd_core_items/Exclusive/MegaClover.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__MegaClover, &Gd__gd_core_items__Exclusive__MegaClover::get_static_prop_fn, &Gd__gd_core_items__Exclusive__MegaClover::call_static_fn};

void Gd__gd_core_items__Exclusive__OwlSpirit::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__SpiritCompanion::init_fields(gd_ctx);
    this->f_manaNeeded = gd::GdVal::null();
    this->f_mana = gd::GdVal::null();
    this->f_fatigueMana = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__OwlSpirit::meta() const { return &META_Gd__gd_core_items__Exclusive__OwlSpirit; }
gd::GdVal Gd__gd_core_items__Exclusive__OwlSpirit::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__SpiritCompanion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__OwlSpirit::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__OwlSpirit::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_manaNeeded_1881: out = this->f_manaNeeded; return true;
        case SYM_GEN_mana_1928: out = this->f_mana; return true;
        case SYM_GEN_fatigueMana_2418: out = this->f_fatigueMana; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__OwlSpirit::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaNeeded_1881: this->f_manaNeeded = val; return true;
        case SYM_GEN_mana_1928: this->f_mana = val; return true;
        case SYM_GEN_fatigueMana_2418: this->f_fatigueMana = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__OwlSpirit::has_own_method(gd::SymId m) const {
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
bool Gd__gd_core_items__Exclusive__OwlSpirit::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
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
bool Gd__gd_core_items__Exclusive__OwlSpirit::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__SpiritCompanion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__OwlSpirit::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsBuffs_296, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OwlSpirit::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t677 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t678 = (_t677.kind == gd::GdVal::Kind::Arr) ? _t677.arr : nullptr;
        uint32_t _len__t679 = _t678 ? _t678->len : 0u;
        for (uint32_t _t679 = 0; _t679 < _len__t679; ++_t679) {
            gd::GdVal lv_item = _t678->data[_t679];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_allBuffs_197, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OwlSpirit::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_manaNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 1); })();
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_1420), SYM_GEN_hasFatigueStarted_1329, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_fatigueMana, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 2); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {this->f_mana, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 2); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OwlSpirit::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OwlSpirit::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OwlSpirit::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__SpiritCompanion::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[158])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[109])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_fatigueMana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[159])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__OwlSpirit(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__OwlSpirit>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__OwlSpirit = {CLS_Gd__gd_core_items__Exclusive__OwlSpirit, "OwlSpirit", "res://gd_core_items/Exclusive/OwlSpirit.gd", &META_Gd__gd_core_items__Exclusive__SpiritCompanion, true, _alloc_Gd__gd_core_items__Exclusive__OwlSpirit, &Gd__gd_core_items__Exclusive__OwlSpirit::get_static_prop_fn, &Gd__gd_core_items__Exclusive__OwlSpirit::call_static_fn};

void Gd__gd_core_items__Exclusive__Pot::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_numFood = gd::GdVal::from_int(0);
    this->f_foodPotionSpeed = gd::GdVal::null();
    this->f_heat = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Pot::meta() const { return &META_Gd__gd_core_items__Exclusive__Pot; }
gd::GdVal Gd__gd_core_items__Exclusive__Pot::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Pot::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Pot::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_numFood_2436: out = this->f_numFood; return true;
        case SYM_GEN_foodPotionSpeed_2437: out = this->f_foodPotionSpeed; return true;
        case SYM_GEN_heat_1896: out = this->f_heat; return true;
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Pot::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numFood_2436: this->f_numFood = gd::gd_coerce_int(val); return true;
        case SYM_GEN_foodPotionSpeed_2437: this->f_foodPotionSpeed = val; return true;
        case SYM_GEN_heat_1896: this->f_heat = val; return true;
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Pot::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onPotionTriggered_2438: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Pot::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onPotionTriggered_2438: out = fn_onPotionTriggered(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Pot::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Pot::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(11LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pot::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pot::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_numFood = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, _ca, 1); })());
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_foodPotionSpeed, gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0), this->f_numFood))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    {
        gd::GdVal _t680 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t681 = (_t680.kind == gd::GdVal::Kind::Arr) ? _t680.arr : nullptr;
        uint32_t _len__t682 = _t681 ? _t681->len : 0u;
        for (uint32_t _t682 = 0; _t682 < _len__t682; ++_t682) {
            gd::GdVal lv_item = _t681->data[_t682];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[160]), gd::GdVal::from_str(&battle_string_literals[161])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pot::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pot::fn_onPotionTriggered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__potion = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[114])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[162])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), this->f_numFood))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pot::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_foodPotionSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[137])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[163])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[131])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Pot(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Pot>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Pot = {CLS_Gd__gd_core_items__Exclusive__Pot, "Pot", "res://gd_core_items/Exclusive/Pot.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Pot, &Gd__gd_core_items__Exclusive__Pot::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Pot::call_static_fn};

void Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Goobert::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer::meta() const { return &META_Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer; }
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[144])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_213, _ca, 1); })();
    {
        gd::GdVal _t683 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t684 = (_t683.kind == gd::GdVal::Kind::Arr) ? _t683.arr : nullptr;
        uint32_t _len__t685 = _t684 ? _t684->len : 0u;
        for (uint32_t _t685 = 0; _t685 < _len__t685; ++_t685) {
            gd::GdVal lv_item = _t684->data[_t685];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_267, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer = {CLS_Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer, "RainbowGoobertPyromancer", "res://gd_core_items/Exclusive/RainbowGoobertPyromancer.gd", &META_Gd__gd_core_items__Goobert, true, _alloc_Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer, &Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer::get_static_prop_fn, &Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer::call_static_fn};

void Gd__gd_core_items__Exclusive__Scale::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_regen = gd::GdVal::null();
    this->f_mana = gd::GdVal::null();
    this->f_speedPerGold = gd::GdVal::null();
    this->f_maxGoldDif = gd::GdVal::null();
    this->f_equilibriumSpeed = gd::GdVal::null();
    this->f_leftCounter = gd::GdVal::null();
    this->f_rightCounter = gd::GdVal::null();
    this->f_leftCounterDefaultPos = gd::GdVal::null();
    this->f_rightCounterDefaultPos = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Scale::meta() const { return &META_Gd__gd_core_items__Exclusive__Scale; }
gd::GdVal Gd__gd_core_items__Exclusive__Scale::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Scale::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Scale::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        case SYM_GEN_mana_1928: out = this->f_mana; return true;
        case SYM_GEN_speedPerGold_2350: out = this->f_speedPerGold; return true;
        case SYM_GEN_maxGoldDif_2476: out = this->f_maxGoldDif; return true;
        case SYM_GEN_equilibriumSpeed_2477: out = this->f_equilibriumSpeed; return true;
        case SYM_GEN_leftCounter_2478: out = this->f_leftCounter; return true;
        case SYM_GEN_rightCounter_2479: out = this->f_rightCounter; return true;
        case SYM_GEN_leftCounterDefaultPos_2480: out = this->f_leftCounterDefaultPos; return true;
        case SYM_GEN_rightCounterDefaultPos_2481: out = this->f_rightCounterDefaultPos; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Scale::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        case SYM_GEN_mana_1928: this->f_mana = val; return true;
        case SYM_GEN_speedPerGold_2350: this->f_speedPerGold = val; return true;
        case SYM_GEN_maxGoldDif_2476: this->f_maxGoldDif = val; return true;
        case SYM_GEN_equilibriumSpeed_2477: this->f_equilibriumSpeed = val; return true;
        case SYM_GEN_leftCounter_2478: this->f_leftCounter = val; return true;
        case SYM_GEN_rightCounter_2479: this->f_rightCounter = val; return true;
        case SYM_GEN_leftCounterDefaultPos_2480: this->f_leftCounterDefaultPos = val; return true;
        case SYM_GEN_rightCounterDefaultPos_2481: this->f_rightCounterDefaultPos = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Scale::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_ready_deferred_463: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_getCounterValue_2351: return true;
        case SYM_GEN_getCounterValue2_2482: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_updateScale_2483: return true;
        case SYM_GEN_onAffectedItemAdded_435: return true;
        case SYM_GEN_onAffectedItemRemoved_436: return true;
        case SYM_GEN_onAddToInventory_419: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_updateCounterPositions_2484: return true;
        case SYM_GEN_rotateTo_476: return true;
        case SYM_GEN_onDraggedWithParentEnd_720: return true;
        case SYM_GEN_onCalcTradeChance_1825: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Scale::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_ready_deferred_463: out = fn_ready_deferred(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_getCounterValue_2351: out = fn_getCounterValue(args, argc); return true;
        case SYM_GEN_getCounterValue2_2482: out = fn_getCounterValue2(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_updateScale_2483: out = fn_updateScale(args, argc); return true;
        case SYM_GEN_onAffectedItemAdded_435: out = fn_onAffectedItemAdded(args, argc); return true;
        case SYM_GEN_onAffectedItemRemoved_436: out = fn_onAffectedItemRemoved(args, argc); return true;
        case SYM_GEN_onAddToInventory_419: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_updateCounterPositions_2484: out = fn_updateCounterPositions(args, argc); return true;
        case SYM_GEN_rotateTo_476: out = fn_rotateTo(args, argc); return true;
        case SYM_GEN_onDraggedWithParentEnd_720: out = fn_onDraggedWithParentEnd(args, argc); return true;
        case SYM_GEN_onCalcTradeChance_1825: out = fn_onCalcTradeChance(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Scale::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_ready_deferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_ready_deferred_463, nullptr, 0, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateCounterPositions_2484, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_getCounterValue(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    gd::GdVal lv_gold = gd::GdVal::from_int(0LL);
    if (gd::gd_truth(this->f_placed)) {
        {
            gd::GdVal _t686 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, _ca, 1); })());
            gd::GdArr* _t687 = (_t686.kind == gd::GdVal::Kind::Arr) ? _t686.arr : nullptr;
            uint32_t _len__t688 = _t687 ? _t687->len : 0u;
            for (uint32_t _t688 = 0; _t688 < _len__t688; ++_t688) {
                gd::GdVal lv_item = _t687->data[_t688];
                lv_gold = gd::gd_add(gd_ctx, lv_gold, gd::call_method(gd_ctx, lv_item, SYM_GEN_getPrice_392, nullptr, 0));
            }
        }
    }
    else {
        {
            gd::GdVal _t689 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_nocache_421, _ca, 1); })());
            gd::GdArr* _t690 = (_t689.kind == gd::GdVal::Kind::Arr) ? _t689.arr : nullptr;
            uint32_t _len__t691 = _t690 ? _t690->len : 0u;
            for (uint32_t _t691 = 0; _t691 < _len__t691; ++_t691) {
                gd::GdVal lv_item = _t690->data[_t691];
                lv_gold = gd::gd_add(gd_ctx, lv_gold, gd::call_method(gd_ctx, lv_item, SYM_GEN_getPrice_392, nullptr, 0));
            }
        }
    }
    return lv_gold;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_getCounterValue2(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue_2351, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_c1 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue_2351, nullptr, 0);
    gd::GdVal lv_c2 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue2_2482, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_speedPerGold, gd::gd_min(lv_c1, lv_c2))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(gd::gd_abs(gd::gd_sub(lv_c1, lv_c2)), this->f_maxGoldDif)))) {
        {
            gd::GdVal _t692 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
            gd::GdArr* _t693 = (_t692.kind == gd::GdVal::Kind::Arr) ? _t692.arr : nullptr;
            uint32_t _len__t694 = _t693 ? _t693->len : 0u;
            for (uint32_t _t694 = 0; _t694 < _len__t694; ++_t694) {
                gd::GdVal lv_item = _t693->data[_t694];
                (void)([&]() { gd::GdVal _ca[] = {this->f_equilibriumSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
            }
        }
        {
            gd::GdVal _t695 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, _ca, 1); })());
            gd::GdArr* _t696 = (_t695.kind == gd::GdVal::Kind::Arr) ? _t695.arr : nullptr;
            uint32_t _len__t697 = _t696 ? _t696->len : 0u;
            for (uint32_t _t697 = 0; _t697 < _len__t697; ++_t697) {
                gd::GdVal lv_item = _t696->data[_t697];
                (void)([&]() { gd::GdVal _ca[] = {this->f_equilibriumSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_curRegen = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRegeneration_1233, nullptr, 0);
    gd::GdVal lv_curMana = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_curMana, lv_curRegen)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_curRegen, lv_curMana)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    }
    else {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_flip_1735, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_updateScale(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_c1 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue_2351, nullptr, 0);
    gd::GdVal lv_c2 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue2_2482, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(gd::gd_abs(gd::gd_sub(lv_c1, lv_c2)), this->f_maxGoldDif)))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_c1, lv_c2)))) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_onAffectedItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateScale_2483, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_onAffectedItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateScale_2483, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateScale_2483, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_updateCounterPositions(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_rotateTo(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_targetRotation = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 1) ? _args[1] : (gd::GdVal::from_float(0.15));
    (void)([&]() { gd::GdVal _ca[] = {lv_targetRotation, lv_duration}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_rotateTo_476, _ca, 2, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateCounterPositions_2484, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_onDraggedWithParentEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onDraggedWithParentEnd_720, nullptr, 0, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateCounterPositions_2484, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_onCalcTradeChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[131])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[109])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_speedPerGold = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[137])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_maxGoldDif = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[164])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_equilibriumSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[165])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Scale(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Scale>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Scale = {CLS_Gd__gd_core_items__Exclusive__Scale, "Scale", "res://gd_core_items/Exclusive/Scale.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Scale, &Gd__gd_core_items__Exclusive__Scale::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Scale::call_static_fn};

void Gd__gd_core_items__Exclusive__SlimeTime::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_gooblingDescriptor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SlimeTime::meta() const { return &META_Gd__gd_core_items__Exclusive__SlimeTime; }
gd::GdVal Gd__gd_core_items__Exclusive__SlimeTime::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SlimeTime::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SlimeTime::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_gooblingDescriptor_2498: out = this->f_gooblingDescriptor; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SlimeTime::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_gooblingDescriptor_2498: this->f_gooblingDescriptor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SlimeTime::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onBought_455: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_getGatedDescriptor_956: return true;
        case SYM_GEN_canAffect_global_2014: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SlimeTime::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onBought_455: out = fn_onBought(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getGatedDescriptor_956: out = fn_getGatedDescriptor(args, argc); return true;
        case SYM_GEN_canAffect_global_2014: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SlimeTime::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SlimeTime::fn_onBought(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SlimeTime::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t698 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t699 = (_t698.kind == gd::GdVal::Kind::Arr) ? _t698.arr : nullptr;
        uint32_t _len__t700 = _t699 ? _t699->len : 0u;
        for (uint32_t _t700 = 0; _t700 < _len__t700; ++_t700) {
            gd::GdVal lv_item = _t699->data[_t700];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_global_2014, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null()}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_onItemActivated_938, _ca, 1); })();
            }
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SlimeTime::fn_getGatedDescriptor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__rarity = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return this->f_gooblingDescriptor;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SlimeTime::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(gd::gd_is_type(lv_item, &META_Gd__gd_core_items__Goobert));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SlimeTime::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_gooblingDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[166])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SlimeTime(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SlimeTime>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SlimeTime = {CLS_Gd__gd_core_items__Exclusive__SlimeTime, "SlimeTime", "res://gd_core_items/Exclusive/SlimeTime.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__SlimeTime, &Gd__gd_core_items__Exclusive__SlimeTime::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SlimeTime::call_static_fn};

void Gd__gd_core_items__Exclusive__SpellScrollNature::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_staminaAcc = gd::GdVal::from_float(0.0);
    this->f_staminaNeeded = gd::GdVal::null();
    this->f_stamina = gd::GdVal::null();
    this->f_manaNeeded = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SpellScrollNature::meta() const { return &META_Gd__gd_core_items__Exclusive__SpellScrollNature; }
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollNature::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SpellScrollNature::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SpellScrollNature::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_staminaAcc_2528: out = this->f_staminaAcc; return true;
        case SYM_GEN_staminaNeeded_2529: out = this->f_staminaNeeded; return true;
        case SYM_GEN_stamina_2156: out = this->f_stamina; return true;
        case SYM_GEN_manaNeeded_1881: out = this->f_manaNeeded; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SpellScrollNature::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaAcc_2528: this->f_staminaAcc = gd::gd_coerce_float(val); return true;
        case SYM_GEN_staminaNeeded_2529: this->f_staminaNeeded = val; return true;
        case SYM_GEN_stamina_2156: this->f_stamina = val; return true;
        case SYM_GEN_manaNeeded_1881: this->f_manaNeeded = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SpellScrollNature::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onItemUsedStamina_2530: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SpellScrollNature::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemUsedStamina_2530: out = fn_onItemUsedStamina(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SpellScrollNature::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollNature::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canUseStamina_294, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollNature::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_staminaAcc = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    {
        gd::GdVal _t701 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t702 = (_t701.kind == gd::GdVal::Kind::Arr) ? _t701.arr : nullptr;
        uint32_t _len__t703 = _t702 ? _t702->len : 0u;
        for (uint32_t _t703 = 0; _t703 < _len__t703; ++_t703) {
            gd::GdVal lv_item = _t702->data[_t703];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[167]), gd::GdVal::from_str(&battle_string_literals[168])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollNature::fn_onItemUsedStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_staminaAcc = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_staminaAcc, lv_amount));
    gd::GdVal lv_activating = gd::GdVal::from_bool(false);
    while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_staminaAcc, gd::gd_sub(this->f_staminaNeeded, gd::GdVal::from_float(0.0001)))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_manaNeeded)))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_stamina, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_318, _ca, 2); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
            lv_activating = gd::GdVal::from_bool(true);
        }
        this->f_staminaAcc = gd::gd_coerce_float(gd::gd_sub(this->f_staminaAcc, this->f_staminaNeeded));
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, this->f_staminaAcc, this->f_staminaNeeded), lv_activating}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollNature::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_staminaNeeded = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[169])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[43])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_manaNeeded = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[109])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SpellScrollNature(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SpellScrollNature>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpellScrollNature = {CLS_Gd__gd_core_items__Exclusive__SpellScrollNature, "SpellScrollNature", "res://gd_core_items/Exclusive/SpellScrollNature.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__SpellScrollNature, &Gd__gd_core_items__Exclusive__SpellScrollNature::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SpellScrollNature::call_static_fn};

void Gd__gd_core_items__Exclusive__StoneGloves::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_speedReduction = gd::GdVal::null();
    this->f_damBonusFactor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__StoneGloves::meta() const { return &META_Gd__gd_core_items__Exclusive__StoneGloves; }
gd::GdVal Gd__gd_core_items__Exclusive__StoneGloves::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__StoneGloves::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__StoneGloves::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_speedReduction_2560: out = this->f_speedReduction; return true;
        case SYM_GEN_damBonusFactor_2469: out = this->f_damBonusFactor; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__StoneGloves::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_speedReduction_2560: this->f_speedReduction = val; return true;
        case SYM_GEN_damBonusFactor_2469: this->f_damBonusFactor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__StoneGloves::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onWeaponAttacked_950: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__StoneGloves::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_950: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__StoneGloves::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGloves::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGloves::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t704 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t705 = (_t704.kind == gd::GdVal::Kind::Arr) ? _t704.arr : nullptr;
        uint32_t _len__t706 = _t705 ? _t705->len : 0u;
        for (uint32_t _t706 = 0; _t706 < _len__t706; ++_t706) {
            gd::GdVal lv_weapon = _t705->data[_t706];
            (void)([&]() { gd::GdVal _ca[] = {lv_weapon, gd::GdVal::from_str(&battle_string_literals[120]), gd::GdVal::from_str(&battle_string_literals[170])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGloves::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t707 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t708 = (_t707.kind == gd::GdVal::Kind::Arr) ? _t707.arr : nullptr;
        uint32_t _len__t709 = _t708 ? _t708->len : 0u;
        for (uint32_t _t709 = 0; _t709 < _len__t709; ++_t709) {
            gd::GdVal lv_item = _t708->data[_t709];
            (void)([&]() { gd::GdVal _ca[] = {this->f_speedReduction}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_274, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_damBonusFactor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamageFactor_306, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGloves::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), gd::GdVal::from_bool(true), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 3); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGloves::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speedReduction = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[171])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_damBonusFactor = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[172])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__StoneGloves(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__StoneGloves>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StoneGloves = {CLS_Gd__gd_core_items__Exclusive__StoneGloves, "StoneGloves", "res://gd_core_items/Exclusive/StoneGloves.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__StoneGloves, &Gd__gd_core_items__Exclusive__StoneGloves::get_static_prop_fn, &Gd__gd_core_items__Exclusive__StoneGloves::call_static_fn};

void Gd__gd_core_items__Exclusive__TimeDilator::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_tickI = gd::GdVal::from_int(0);
    this->f_slow = gd::GdVal::null();
    this->f_speedUp = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__TimeDilator::meta() const { return &META_Gd__gd_core_items__Exclusive__TimeDilator; }
gd::GdVal Gd__gd_core_items__Exclusive__TimeDilator::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__TimeDilator::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__TimeDilator::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_tickI_2593: out = this->f_tickI; return true;
        case SYM_GEN_slow_2594: out = this->f_slow; return true;
        case SYM_GEN_speedUp_2595: out = this->f_speedUp; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__TimeDilator::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_tickI_2593: this->f_tickI = gd::gd_coerce_int(val); return true;
        case SYM_GEN_slow_2594: this->f_slow = val; return true;
        case SYM_GEN_speedUp_2595: this->f_speedUp = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__TimeDilator::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_playActivationSound_148: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__TimeDilator::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playActivationSound_148: out = fn_playActivationSound(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__TimeDilator::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__TimeDilator::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_tickI = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    gd::GdVal lv_allItems = gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1302), SYM_GEN_INVENTORY_1093), SYM_GEN_getItems_1603, nullptr, 0), gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_opponent_75), SYM_GEN_INVENTORY_1093), SYM_GEN_getItems_1603, nullptr, 0));
    {
        gd::GdVal _t710 = gd::gd_iter_seq(gd_ctx.arena, lv_allItems);
        gd::GdArr* _t711 = (_t710.kind == gd::GdVal::Kind::Arr) ? _t710.arr : nullptr;
        uint32_t _len__t712 = _t711 ? _t711->len : 0u;
        for (uint32_t _t712 = 0; _t712 < _len__t712; ++_t712) {
            gd::GdVal lv_item = _t711->data[_t712];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isWeapon_82, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_slow}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_274, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TimeDilator::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_slowestCd = gd::GdVal::from_float(0.0);
    gd::GdVal lv_slowestItem = gd::GdVal::null();
    {
        gd::GdVal _t713 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t714 = (_t713.kind == gd::GdVal::Kind::Arr) ? _t713.arr : nullptr;
        uint32_t _len__t715 = _t714 ? _t714->len : 0u;
        for (uint32_t _t715 = 0; _t715 < _len__t715; ++_t715) {
            gd::GdVal lv_item = _t714->data[_t715];
            if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isCooldownActive_96, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
                gd::GdVal lv_cd = gd::call_method(gd_ctx, lv_item, SYM_GEN_getModifiedCooldown_104, nullptr, 0);
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_cd, lv_slowestCd)))) {
                    lv_slowestCd = lv_cd;
                    lv_slowestItem = lv_item;
                }
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {this->f_speedUp}; return gd::call_method(gd_ctx, lv_slowestItem, SYM_GEN_addSpeed_273, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    this->f_tickI = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_tickI, gd::GdVal::from_int(1LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TimeDilator::fn_playActivationSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_pitch = (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::gd_mod(gd_ctx, this->f_tickI, gd::GdVal::from_int(2LL)), gd::GdVal::from_int(0LL)))) ? (gd::GdVal::from_float(1.0)) : (gd::GdVal::from_float(0.7)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TimeDilator::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_slow = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[173])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_speedUp = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[137])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__TimeDilator(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__TimeDilator>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__TimeDilator = {CLS_Gd__gd_core_items__Exclusive__TimeDilator, "TimeDilator", "res://gd_core_items/Exclusive/TimeDilator.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__TimeDilator, &Gd__gd_core_items__Exclusive__TimeDilator::get_static_prop_fn, &Gd__gd_core_items__Exclusive__TimeDilator::call_static_fn};

void Gd__gd_core_items__Exclusive__WarScythe::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_poisonNeeded = gd::GdVal::null();
    this->f_critDamage = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__WarScythe::meta() const { return &META_Gd__gd_core_items__Exclusive__WarScythe; }
gd::GdVal Gd__gd_core_items__Exclusive__WarScythe::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__WarScythe::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__WarScythe::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_poisonNeeded_2613: out = this->f_poisonNeeded; return true;
        case SYM_GEN_critDamage_2614: out = this->f_critDamage; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__WarScythe::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_poisonNeeded_2613: this->f_poisonNeeded = val; return true;
        case SYM_GEN_critDamage_2614: this->f_critDamage = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__WarScythe::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__WarScythe::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__WarScythe::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__WarScythe::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(256LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsStack_86, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WarScythe::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t716 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t717 = (_t716.kind == gd::GdVal::Kind::Arr) ? _t716.arr : nullptr;
        uint32_t _len__t718 = _t717 ? _t717->len : 0u;
        for (uint32_t _t718 = 0; _t718 < _len__t718; ++_t718) {
            gd::GdVal lv_item = _t717->data[_t718];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(108LL), gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveBuffPower_303, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WarScythe::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getPoison_1229, nullptr, 0), this->f_poisonNeeded)))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_poisonNeeded, gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_losePoison_1232, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addCritChancePercent_179, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_critDamage}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addCritSeverity_185, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WarScythe::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_poisonNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[174])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_critDamage = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[175])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__WarScythe(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__WarScythe>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__WarScythe = {CLS_Gd__gd_core_items__Exclusive__WarScythe, "WarScythe", "res://gd_core_items/Exclusive/WarScythe.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__WarScythe, &Gd__gd_core_items__Exclusive__WarScythe::get_static_prop_fn, &Gd__gd_core_items__Exclusive__WarScythe::call_static_fn};

void Gd__gd_core_items__Gems__Amethyst::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Gems__Gem::init_fields(gd_ctx);
    this->f_healReduction = gd::GdVal::null();
    this->f_buffRemoval = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Gems__Amethyst::meta() const { return &META_Gd__gd_core_items__Gems__Amethyst; }
gd::GdVal Gd__gd_core_items__Gems__Amethyst::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_gemColor_995: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.977344), gd::GdVal::from_float(0.8), gd::GdVal::from_int(3LL)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Gems__Amethyst::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Gems__Amethyst::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_healReduction_2152: out = this->f_healReduction; return true;
        case SYM_GEN_buffRemoval_2187: out = this->f_buffRemoval; return true;
        case SYM_GEN_gemColor_995: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Gems__Amethyst::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_healReduction_2152: this->f_healReduction = val; return true;
        case SYM_GEN_buffRemoval_2187: this->f_buffRemoval = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Gems__Amethyst::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_prepareWeapon_982: return true;
        case SYM_GEN_onAttack_2052: return true;
        case SYM_GEN_prepareArmor_983: return true;
        case SYM_GEN_getBaseDescription_990: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Gems__Amethyst::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_prepareWeapon_982: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_onAttack_2052: out = fn_onAttack(args, argc); return true;
        case SYM_GEN_prepareArmor_983: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_getBaseDescription_990: out = fn_getBaseDescription(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Gems__Amethyst::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Gems__Amethyst::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_356, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Amethyst::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_389, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[120]), gd::GdVal::from_str(&battle_string_literals[176])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Amethyst::fn_onAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_buffRemoval, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeRandomBuffs_372, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Amethyst::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0), this->f_healReduction)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_reduceHealingEfficiency_1183, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Amethyst::fn_getBaseDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRarity_236, nullptr, 0), gd::GdVal::from_int(4LL))))) {
        return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[177])}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_tra_2715, _ca, 1); })(), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameters_643, _ca, 2); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN_getBaseDescription_990, _ca, 1, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Amethyst::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_healReduction = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::GdVal::from_float(100.0));
    this->f_buffRemoval = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Gems__Amethyst(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Gems__Amethyst>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Gems__Amethyst = {CLS_Gd__gd_core_items__Gems__Amethyst, "Amethyst", "res://gd_core_items/Gems/Amethyst.gd", &META_Gd__gd_core_items__Gems__Gem, true, _alloc_Gd__gd_core_items__Gems__Amethyst, &Gd__gd_core_items__Gems__Amethyst::get_static_prop_fn, &Gd__gd_core_items__Gems__Amethyst::call_static_fn};

void Gd__gd_core_items__HeroSword::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__HeroSword::meta() const { return &META_Gd__gd_core_items__HeroSword; }
gd::GdVal Gd__gd_core_items__HeroSword::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__HeroSword::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__HeroSword::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__HeroSword::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__HeroSword::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__HeroSword::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__HeroSword::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__HeroSword::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeroSword::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t719 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t720 = (_t719.kind == gd::GdVal::Kind::Arr) ? _t719.arr : nullptr;
        uint32_t _len__t721 = _t720 ? _t720->len : 0u;
        for (uint32_t _t721 = 0; _t721 < _len__t721; ++_t721) {
            gd::GdVal lv_item = _t720->data[_t721];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false), gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, Gd__gd_core_items__HeroSword::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Jump_2736)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeroSword::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__HeroSword(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__HeroSword>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__HeroSword = {CLS_Gd__gd_core_items__HeroSword, "HeroSword", "res://gd_core_items/HeroSword.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__HeroSword, &Gd__gd_core_items__HeroSword::get_static_prop_fn, &Gd__gd_core_items__HeroSword::call_static_fn};

void Gd__gd_core_items__Manathirst::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_manaGained = gd::GdVal::from_int(0);
    this->f_fillingTween = gd::GdVal::null();
    this->f_filling = gd::GdVal::null();
    this->f_fillingGlow = gd::GdVal::null();
    this->f_fillingHeight = gd::GdVal::null();
    this->f_fillingAnimation = gd::GdVal::null();
    this->f_manaNeededForLifesteal = gd::GdVal::null();
    this->f_dam = gd::GdVal::null();
    this->f_mana = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Manathirst::meta() const { return &META_Gd__gd_core_items__Manathirst; }
gd::GdVal Gd__gd_core_items__Manathirst::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Manathirst::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Manathirst::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_manaGained_1931: out = this->f_manaGained; return true;
        case SYM_GEN_fillingTween_1932: out = this->f_fillingTween; return true;
        case SYM_GEN_filling_1933: out = this->f_filling; return true;
        case SYM_GEN_fillingGlow_1934: out = this->f_fillingGlow; return true;
        case SYM_GEN_fillingHeight_1935: out = this->f_fillingHeight; return true;
        case SYM_GEN_fillingAnimation_1936: out = this->f_fillingAnimation; return true;
        case SYM_GEN_manaNeededForLifesteal_1937: out = this->f_manaNeededForLifesteal; return true;
        case SYM_GEN_dam_939: out = this->f_dam; return true;
        case SYM_GEN_mana_1928: out = this->f_mana; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Manathirst::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaGained_1931: this->f_manaGained = gd::gd_coerce_int(val); return true;
        case SYM_GEN_fillingTween_1932: this->f_fillingTween = val; return true;
        case SYM_GEN_filling_1933: this->f_filling = val; return true;
        case SYM_GEN_fillingGlow_1934: this->f_fillingGlow = val; return true;
        case SYM_GEN_fillingHeight_1935: this->f_fillingHeight = val; return true;
        case SYM_GEN_fillingAnimation_1936: this->f_fillingAnimation = val; return true;
        case SYM_GEN_manaNeededForLifesteal_1937: this->f_manaNeededForLifesteal = val; return true;
        case SYM_GEN_dam_939: this->f_dam = val; return true;
        case SYM_GEN_mana_1928: this->f_mana = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Manathirst::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_tweenFilling_1938: return true;
        case SYM_GEN_onManaChanged_1929: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Manathirst::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_tweenFilling_1938: out = fn_tweenFilling(args, argc); return true;
        case SYM_GEN_onManaChanged_1929: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Manathirst::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Manathirst::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_manaGained = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[105]), gd::GdVal::from_str(&battle_string_literals[106])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tweenFilling_1938, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Manathirst::fn_tweenFilling(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_relHeight = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_relHeight = gd::gd_coerce_float(lv_relHeight);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Manathirst::fn_onManaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        this->f_manaGained = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_manaGained, lv_amount));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_manaGained, this->f_manaNeededForLifesteal)))) {
            this->f_manaGained = gd::gd_coerce_int(gd::gd_sub(this->f_manaGained, this->f_manaNeededForLifesteal));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_dam, gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getVampirism_1226, nullptr, 0)), gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[107])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::GdVal::from_float(100.0)), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealLife_329, _ca, 3); })();
        }
        gd::GdVal lv_relHeight = gd::gd_div(gd_ctx, this->f_manaGained, this->f_manaNeededForLifesteal);
        (void)([&]() { gd::GdVal _ca[] = {lv_relHeight}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tweenFilling_1938, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Manathirst::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_mana, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Manathirst::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tweenFilling_1938, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Manathirst::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_manaNeededForLifesteal = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0);
    this->f_dam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[108])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[109])}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Manathirst(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Manathirst>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Manathirst = {CLS_Gd__gd_core_items__Manathirst, "Manathirst", "res://gd_core_items/Manathirst.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Manathirst, &Gd__gd_core_items__Manathirst::get_static_prop_fn, &Gd__gd_core_items__Manathirst::call_static_fn};

void Gd__gd_core_items__RainbowGoobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Goobert::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__RainbowGoobert::meta() const { return &META_Gd__gd_core_items__RainbowGoobert; }
gd::GdVal Gd__gd_core_items__RainbowGoobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__RainbowGoobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__RainbowGoobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__RainbowGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__RainbowGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__RainbowGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__RainbowGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__RainbowGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_213, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 1); })();
    {
        gd::GdVal _t722 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t723 = (_t722.kind == gd::GdVal::Kind::Arr) ? _t722.arr : nullptr;
        uint32_t _len__t724 = _t723 ? _t723->len : 0u;
        for (uint32_t _t724 = 0; _t724 < _len__t724; ++_t724) {
            gd::GdVal lv_item = _t723->data[_t724];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_267, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RainbowGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__RainbowGoobert(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__RainbowGoobert>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__RainbowGoobert = {CLS_Gd__gd_core_items__RainbowGoobert, "RainbowGoobert", "res://gd_core_items/RainbowGoobert.gd", &META_Gd__gd_core_items__Goobert, true, _alloc_Gd__gd_core_items__RainbowGoobert, &Gd__gd_core_items__RainbowGoobert::get_static_prop_fn, &Gd__gd_core_items__RainbowGoobert::call_static_fn};

void Gd__gd_core_items__StrongPestilenceFlask::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__PestilenceFlask::init_fields(gd_ctx);
    this->f_poisonTimer = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__StrongPestilenceFlask::meta() const { return &META_Gd__gd_core_items__StrongPestilenceFlask; }
gd::GdVal Gd__gd_core_items__StrongPestilenceFlask::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__PestilenceFlask::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__StrongPestilenceFlask::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__StrongPestilenceFlask::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_poisonTimer_1995: out = this->f_poisonTimer; return true;
        default: break;
    }
    return Gd__gd_core_items__PestilenceFlask::get_prop(prop, out);
}
bool Gd__gd_core_items__StrongPestilenceFlask::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_poisonTimer_1995: this->f_poisonTimer = val; return true;
        default: break;
    }
    return Gd__gd_core_items__PestilenceFlask::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__StrongPestilenceFlask::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getAffectedItems_420: return true;
        case SYM_GEN_onTriggerPotion_1849: return true;
        case SYM_GEN_poisonTimerTimeout_1996: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__PestilenceFlask::has_own_method(m);
}
bool Gd__gd_core_items__StrongPestilenceFlask::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getAffectedItems_420: out = fn_getAffectedItems(args, argc); return true;
        case SYM_GEN_onTriggerPotion_1849: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_poisonTimerTimeout_1996: out = fn_poisonTimerTimeout(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__PestilenceFlask::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__StrongPestilenceFlask::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__PestilenceFlask::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__StrongPestilenceFlask::fn_getAffectedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    gd::GdVal lv__r = ([&]() { gd::GdVal _ca[] = {lv_color}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__PestilenceFlask::call_method(gd_ctx, SYM_GEN_getAffectedItems_420, _ca, 1, _out); return _out; })();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_ctx, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::GdVal::null())))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv__cp = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCollisionPoints_406, nullptr, 0);
        gd::GdVal lv__rc = ([&]() { gd::GdVal _ca[] = {lv__cp}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCellsForGlobalPositions_401, _ca, 1); })();
        gd::GdVal lv__cc = ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsInInventory_cached_415, _ca, 1); })();
        gd::GdVal lv__names = gd::GdVal::from_str(&battle_string_literals[8]);
        {
            gd::GdVal _t725 = gd::gd_iter_seq(gd_ctx.arena, lv__r);
            gd::GdArr* _t726 = (_t725.kind == gd::GdVal::Kind::Arr) ? _t725.arr : nullptr;
            uint32_t _len__t727 = _t726 ? _t726->len : 0u;
            for (uint32_t _t727 = 0; _t727 < _len__t727; ++_t727) {
                gd::GdVal lv__a = _t726->data[_t727];
                lv__names = gd::gd_add(gd_ctx, lv__names, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv__a, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[178])), ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, lv__a, SYM_GEN_occupiedCells_52)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[179])));
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[180]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1673))), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[181]), ([&]() { gd::GdVal _ca[] = {this->f_faceDirection}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[182])), ([&]() { gd::GdVal _ca[] = {lv__cp}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[183])), ([&]() { gd::GdVal _ca[] = {lv__cc}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, lv__names, gd::GdVal::from_str(&battle_string_literals[184])), ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, lv__r, gd::SYM_size, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    }
    return lv__r;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongPestilenceFlask::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__PestilenceFlask::call_method(gd_ctx, SYM_GEN_onTriggerPotion_1849, _ca, 1, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::call_method(gd_ctx, this->f_poisonTimer, SYM_GEN_start_1779, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongPestilenceFlask::fn_poisonTimerTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongPestilenceFlask::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_poisonTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongPestilenceFlask::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__PestilenceFlask::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_poisonTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[185]), gd::GdVal::from_str(&battle_string_literals[186]), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__StrongPestilenceFlask(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__StrongPestilenceFlask>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__StrongPestilenceFlask = {CLS_Gd__gd_core_items__StrongPestilenceFlask, "StrongPestilenceFlask", "res://gd_core_items/StrongPestilenceFlask.gd", &META_Gd__gd_core_items__PestilenceFlask, true, _alloc_Gd__gd_core_items__StrongPestilenceFlask, &Gd__gd_core_items__StrongPestilenceFlask::get_static_prop_fn, &Gd__gd_core_items__StrongPestilenceFlask::call_static_fn};
